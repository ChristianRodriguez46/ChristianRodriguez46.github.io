#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

/*
*	Function that reads data from a CSV into a 2-D array.
*/
using namespace std;
template <size_t rows, size_t cols>
void readCSV(double(&array)[rows][cols], char* filename) {
	ifstream file(filename);

	for (size_t row = 0; row < rows; ++row)
	{
		string line;
		getline(file, line);

		if (!file.good())
			break;

		stringstream iss(line);

		for (size_t col = 0; col < cols; ++col)
		{
			string val;
			getline(iss, val, ',');

			stringstream convertor(val);
			convertor >> array[row][col];
		}
	}
}

/*
*	Function that displays data values
*/
template <size_t rows, size_t cols>
void displayValues(double(&array)[rows][cols]) {
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; col++) {
			cout << array[row][col] << ' ';
		}

		cout << endl;
	}
}


int main(int argc, char* argv[])
{
	// error handling
	if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const size_t num_samples = 100; // Based on lab description (rows)
    const size_t num_features = 2;  // Petal length and species label (columns)
    double iris_data[num_samples][num_features];	//[rows][columns]

    // Read data from CSV
    readCSV(iris_data, argv[1]);

    // Array to store predictions
    int predicted_labels[num_samples];
    int correct_count = 0;

    // Apply expert system rule
	// iris_data[row][column]
    for (size_t i = 0; i < num_samples; ++i) {
        double petal_length = iris_data[i][0];					//Gets the petal values only
        int ground_truth = iris_data[i][1];	//is used to see it it was correct

        // Expert rule
		//condition of 1.6-1.7 yields the best performance
        if (petal_length > 1.6) {
            predicted_labels[i] = 2; // Iris Virginica
        } else {
            predicted_labels[i] = 1; // Iris Versicolor
        }

        // Compare predicted label with ground truth
        if (predicted_labels[i] == ground_truth) {
            correct_count++;
        }
    }

    // Display results
    cout << "Predictions vs Ground Truth:\n";
    for (size_t i = 0; i < num_samples; ++i) {
        cout << "Sample " << i + 1 << ": Predicted = " << predicted_labels[i]
             << ", Actual = " << static_cast<int>(iris_data[i][1]) << endl;
    }

    // Compute and display accuracy
    double accuracy = (static_cast<double>(correct_count) / num_samples) * 100;
    cout << "Accuracy: " << accuracy << "%\n";

	return 0;
}