/***************************************************************************
* Lab 9 – Multiclass Neural Network
* CMPS 3560 Artificial Intelligence – Spring 2025
* Author: Christian Rodriguez

 layout of program
 * ─────────────
 *   inputs (4 features + bias)  ➜  hidden layer (3 neurons + bias)  ➜  outputs (3 neurons)
 *
 * All neurons use the logistic‑sigmoid activation.  Training is plain stochastic
 * gradient descent (SGD) with a fixed learning‑rate α that optionally doubles
 * after epoch 100 to help escape plateaus.  Each training pass (epoch)
 * prints the mean‑absolute‑deviation (MAD) error across the data set; one row
 * prediction is also shown every 150 samples so you can watch convergence.
 *
 * The code is purposely minimal so that every line corresponds to something we
 * derived by hand in lecture:  dot products for nets, σ′(s) = s(1−s) for the
 * derivative, and weight updates Δw = −α δ x.
**************************************************************************/

#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* ════════════════════════════════════════════════════════════════════
    Hyper‑parameters and compile‑time constants
    ───────────────────────────────────────────────────────────────────*/
constexpr double  ALPHA0      = 0.05;  // starting learning rate α
constexpr size_t  N_IN        = 4 + 1; // four features + one bias input
constexpr size_t  N_HID       = 3 + 1; // three hidden neurons + bias
constexpr size_t  N_OUT       = 3;     // three output classes
constexpr size_t  MAX_EPOCHS  = 1000;  // safety cap – we usually finish sooner

/* ════════════════════════════════════════════════════════════════════
    Data structure for one Iris sample
    ───────────────────────────────────────────────────────────────────*/
struct Sample {
    array<double,N_IN>  x{}; // input vector; index 0 holds the bias (always 1.0)
    array<double,N_OUT> y{}; // one‑hot target vector, e.g. [1,0,0]
};

/* ════════════════════════════════════════════════════════════════════
    Small math helper functions
    ───────────────────────────────────────────────────────────────────*/
inline double sigmoid(double z)          { return 1.0 / (1.0 + exp(-z)); }
inline double sigmoidPrime(double s)     { return s * (1.0 - s); }
inline double xavierLimit(size_t fanIn, size_t fanOut)
{ return sqrt(6.0 / (fanIn + fanOut)); }   // Glorot/Xavier range

/* ════════════════════════════════════════════════════════════════════
    CSV loader – expects rows "f1,f2,f3,f4,label1,label2,label3"
    ───────────────────────────────────────────────────────────────────*/
vector<Sample> loadCsv(const string& path)
{
    ifstream in(path);
    if(!in){ cerr << "cannot open " << path << "\n"; exit(1); }

    vector<Sample> data; string line, tok;
    while(getline(in,line)){
        if(line.empty()) continue;               // skip blank lines
        istringstream ss(line);

        Sample s;  s.x[0] = 1.0;                 // bias input
        // read four features
        for(size_t i = 1; i < N_IN; ++i){
            getline(ss, tok, ',');
            s.x[i] = stod(tok);
        }
        // read three one‑hot label columns
        for(size_t k = 0; k < N_OUT; ++k){
            // last column may have no trailing comma – handle that too
            if(!getline(ss, tok, ',')) tok = ss.str().substr(ss.tellg());
            s.y[k] = stod(tok);
        }
        data.push_back(s);
    }
    return data;
}

/* ════════════════════════════════════════════════════════════════════
    Network weight containers
    ───────────────────────────────────────────────────────────────────
    wHidden[j‑1][i] : weight from input i ➜ hidden neuron j   (j=1..3, i=0..4)
    wOut[k][j]      : weight from hidden j ➜ output neuron k  (k=0..2, j=0..3)
*/
struct Net {
    array<array<double,N_IN>,  N_HID-1> wHidden; // 3 × 5  matrix
    array<array<double,N_HID>, N_OUT  > wOut;    // 3 × 4  matrix
};

/* ------------------------------------------------------------------
    initialise weights with Xavier‑uniform in [−limit, +limit]
-------------------------------------------------------------------*/
void init(Net& net, mt19937& rng)
{
    uniform_real_distribution<double> uh(-xavierLimit(N_IN,  N_HID-1),
                                            xavierLimit(N_IN,  N_HID-1));
    uniform_real_distribution<double> uo(-xavierLimit(N_HID, N_OUT),
                                            xavierLimit(N_HID, N_OUT));
    for(auto& row : net.wHidden) for(double& w : row) w = uh(rng);
    for(auto& row : net.wOut)    for(double& w : row) w = uo(rng);
}

/* ════════════════════════════════════════════════════════════════════
    Forward pass – computes outputs and caches hidden activations
    ───────────────────────────────────────────────────────────────────*/
using VecH = array<double,N_HID>; // hidden activations (+bias 0)
using VecO = array<double,N_OUT>; // output activations

VecO forward(const Net& net, const array<double,N_IN>& x, VecH& hOut)
{
    /* ---- hidden layer ---- */
    hOut[0] = 1.0; // bias activation
    for(size_t j = 1; j < N_HID; ++j){
        double netVal = 0.0;
        for(size_t i = 0; i < N_IN; ++i)
            netVal += net.wHidden[j-1][i] * x[i];
        hOut[j] = sigmoid(netVal);
    }

    /* ---- output layer ---- */
    VecO yhat{};
    for(size_t k = 0; k < N_OUT; ++k){
        double netVal = 0.0;
        for(size_t j = 0; j < N_HID; ++j)
            netVal += net.wOut[k][j] * hOut[j];
        yhat[k] = sigmoid(netVal);
    }
    return yhat; // return by value (small fixed array – cheap)
}

/* ════════════════════════════════════════════════════════════════════
    Back‑propagation & weight update (stochastic GD)
    ───────────────────────────────────────────────────────────────────
    deltaO   = (ŷ − y) σ′        – size 3
    deltaH   = Σ deltaO * wOut   – size 3 (no bias)
    wOut    -= α * deltaO * h
    wHidden -= α * deltaH * x
*/
void sgd(Net& net, const Sample& s, double alpha,
        VecH& hOut, const VecO& yhat)
{
    /* ---- output layer deltas ---- */
    array<double,N_OUT> deltaO;
    for(size_t k = 0; k < N_OUT; ++k)
        deltaO[k] = (yhat[k] - s.y[k]) * sigmoidPrime(yhat[k]);

    /* ---- hidden layer deltas (indices 1..3) ---- */
    array<double,N_HID-1> deltaH{};
    for(size_t j = 1; j < N_HID; ++j){
        double sum = 0.0;
        for(size_t k = 0; k < N_OUT; ++k)
            sum += deltaO[k] * net.wOut[k][j];
        deltaH[j-1] = sum * sigmoidPrime(hOut[j]);
    }

    /* ---- gradient step for output weights ---- */
    for(size_t k = 0; k < N_OUT; ++k)
        for(size_t j = 0; j < N_HID; ++j)
            net.wOut[k][j] -= alpha * deltaO[k] * hOut[j];

    /* ---- gradient step for hidden weights ---- */
    for(size_t j = 1; j < N_HID; ++j)
        for(size_t i = 0; i < N_IN; ++i)
            net.wHidden[j-1][i] -= alpha * deltaH[j-1] * s.x[i];
}

/* ════════════════════════════════════════════════════════════════════
    Evaluation helpers – MAD and accuracy
    ───────────────────────────────────────────────────────────────────*/
double mad(const vector<Sample>& D, Net& net)
{
    double sum = 0.0; VecH h;
    for(const auto& s : D){
        auto yhat = forward(net, s.x, h);
        for(size_t k = 0; k < N_OUT; ++k)
            sum += fabs(s.y[k] - yhat[k]);
    }
    return sum / D.size();
}

double accuracy(const vector<Sample>& D, Net& net)
{
    size_t ok = 0; VecH h;
    for(const auto& s : D){
        auto yhat = forward(net, s.x, h);
        size_t pred  = max_element(yhat.begin(), yhat.end())  - yhat.begin();
        size_t truth = max_element(s.y.begin(),   s.y.end())  - s.y.begin();
        if(pred == truth) ++ok;
    }
    return 100.0 * ok / D.size();
}

/* ════════════════════════════════════════════════════════════════════
    Main – orchestrates data loading, training loop, and reporting
    ───────────────────────────────────────────────────────────────────*/
int main(int argc, char* argv[])
{
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " iris.csv\n";
        return 1;
    }

    /* 1) Load data */
    auto data = loadCsv(argv[1]);
    cout << "Loaded " << data.size() << " samples.\n";

    /* 2) Shuffle once to break any ordering bias */
    mt19937 rng{ random_device{}() };
    shuffle(data.begin(), data.end(), rng);

    /* 3) Build & initialise the network */
    Net net;  init(net, rng);

    /* 4) Training loop */
    VecH h;                // cache for hidden activations
    double alpha = ALPHA0; // current learning rate
    size_t iter  = 0;      // running sample counter

    for(size_t epoch = 1; epoch <= MAX_EPOCHS; ++epoch){

        double totalError = 0.0;
        for(auto& s : data){
            auto yhat = forward(net, s.x, h);
            sgd(net, s, alpha, h, yhat);

            // accumulate 1‑norm error for the epoch summary
            for(size_t k = 0; k < N_OUT; ++k)
                totalError += fabs(s.y[k] - yhat[k]);

            /* Print one sample prediction per full pass (150 rows) */
            ++iter;
            if(iter % data.size() == 0){
                cout << "Epoch " << setw(3) << epoch
                    << ", sample " << setw(3) << iter << ": ["
                    << fixed << setprecision(2)
                    << yhat[0] << ", " << yhat[1] << ", " << yhat[2] << "]\n";
            }
        }

        cout << "Epoch " << setw(3) << epoch
            << " Results: MAD = " << fixed << setprecision(4)
            << (totalError / data.size()) << "\n";

        /* Optional learning‑rate kick after 100 epochs */
        if(epoch == 100) alpha *= 2.0;

        /* Early exit if training accuracy is perfect */
        if(accuracy(data, net) == 100.0){
            cout << "Perfect accuracy reached.\n";
            break;
        }
    }

    cout << "\nFinal training accuracy: "
        << fixed << setprecision(2) << accuracy(data, net) << " %\n";
    return 0;
}
   
 