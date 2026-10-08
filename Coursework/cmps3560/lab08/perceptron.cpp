/***************************************************************************
 *  Lab 8 – Pocketed Perceptron with Per-Epoch Shuffle
 *  CMPS 3560 Artificial Intelligence – Spring 2025
 *  Author: Christian Rodriguez
 **************************************************************************/

#include <array>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ——————— hyper-parameters ———————
constexpr double  ALPHA       = 0.05;   // learning rate α
constexpr size_t  N_FEATS     = 4;      // x₁…x₄
constexpr size_t  VEC_SIZE    = N_FEATS + 1; // +1 for bias x₀
constexpr size_t  MAX_EPOCHS  = 1000;   // max passes over the data

// ——————— data record ———————
struct Sample {
    array<double,VEC_SIZE> x{};  // x₀=1.0, x₁…x₄
    int                    y{};  // −1 or +1
};

// hard limiter activation ⇒ ±1
static inline int hard_limiter(double net) noexcept {
    return net >= 0.0 ? +1 : -1;
}

// load CSV of form: f1,f2,f3,f4,label  (each ∈ ℝ, last is −1/1)
static vector<Sample> load_csv(const string& file) {
    ifstream in(file);
    if (!in) {
        cerr << "Error: cannot open `" << file << "`\n";
        exit(1);
    }
    vector<Sample> data;
    string line, tok;
    while (getline(in,line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        Sample s;
        s.x[0] = 1.0;  // bias input
        for (size_t i = 1; i <= N_FEATS; ++i) {
            if (!getline(ss,tok,',')) {
                cerr << "Parse error on features\n"; exit(1);
            }
            s.x[i] = stod(tok);
        }
        if (!getline(ss,tok,',')) {
            // last token without trailing comma still works
            tok = ss.str().substr(ss.tellg());
        }
        s.y = stoi(tok);
        data.push_back(s);
    }
    return data;
}

// pretty-print weight vector [θ, β₁ … β₄]
static string wstr(const array<double,VEC_SIZE>& w) {
    ostringstream os;
    os << fixed << setprecision(4) << '[';
    for (size_t i = 0; i < VEC_SIZE; ++i) {
        os << w[i] << (i+1<VEC_SIZE ? ", " : "]");
    }
    return os.str();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " iris_full_normalized.csv\n";
        return 1;
    }

    // 1) load + sanity-check
    auto data = load_csv(argv[1]);
    assert(data.size() == 150 && "Expected exactly 150 samples");
    cout << "Loaded " << data.size() << " samples.\n";
    // dump first & last
    {
        auto& A = data.front();
        auto& B = data.back();
        cout << "First row:  [" 
             << A.x[1] << ", " << A.x[2] << ", " 
             << A.x[3] << ", " << A.x[4] << "]  → " << A.y << "\n";
        cout << " Last row:  [" 
             << B.x[1] << ", " << B.x[2] << ", " 
             << B.x[3] << ", " << B.x[4] << "]  → " << B.y << "\n";
    }

    // 2) prepare RNG + initial weights
    mt19937 rng{random_device{}()};
    array<double,VEC_SIZE> w{}, pocket_w{};
    // initialize to small random in [−0.5,0.5]
    uniform_real_distribution<double> init(-0.5,0.5);
    for (double& wi : w) wi = init(rng);
    pocket_w = w;
    size_t pocket_errs = data.size();

    // 3) training with pocket + per-epoch shuffle
    for (size_t epoch = 1; epoch <= MAX_EPOCHS; ++epoch) {
        // shuffle order each epoch
        shuffle(data.begin(), data.end(), rng);

        size_t errors = 0;
        for (auto& s : data) {
            double net = 0;
            for (size_t i = 0; i < VEC_SIZE; ++i)
                net += w[i] * s.x[i];
            int pred = hard_limiter(net);
            if (pred != s.y) {
                ++errors;
                // update all weights, including θ = w[0]
                for (size_t i = 0; i < VEC_SIZE; ++i)
                    w[i] += ALPHA * s.y * s.x[i];
            }
        }

        // pocket if this is best so far
        if (errors < pocket_errs) {
            pocket_errs = errors;
            pocket_w    = w;
        }

        cout << "Epoch " << setw(4) << epoch
             << " | Misclassifications: " << errors << '\n';

        if (errors == 0) {
            cout << "No errors—perfect separation!\n";
            break;
        }
    }

    // 4) report pocket result
    double best_acc = 100.0 * double(data.size() - pocket_errs) / data.size();
    cout << "\nBest (pocket) accuracy: " 
         << fixed << setprecision(2) << best_acc << "%\n";
    cout << "Best weights [θ, β1…β4]: " << wstr(pocket_w) << "\n";

    return 0;
}
