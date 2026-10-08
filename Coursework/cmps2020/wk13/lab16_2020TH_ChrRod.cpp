#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;     // Save a in a temporary variable
    a = b;            // Set a to b
    b = temp;         // Set b to the original value of a
}

// Function to fill the array with random values between lbounds and ubounds
void fill_array_random(int array[], int size, int lbounds, int ubounds)
{
    for (int i = 0; i < size; i++)
    {
        // Generate a random number between lbounds and ubounds
        array[i] = (rand() % (ubounds - lbounds)) + lbounds;
    }
}

// Function to fill the array with increasing values from 1 to size
void fill_array_inc(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // Fill the array with increasing values starting from 1
        array[i] = i + 1;
    }
}

// Function to fill the array with decreasing values from size to 1
void fill_array_dec(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // Fill the array with decreasing values starting from size
        array[i] = size - 1;
    }
}

//Bubble sort function
void bubble_sort(int array[], int size)
{
    for (int i = 0; i < size-1; i++)               // Loop through each element in the array, except for the last one
    {
        for (int j = 0; j < size - i - 1; j++)     // Loop through each element in the array, except for the last one
        {
            if(array[j] > array[j + 1])            // If the current element is greater than the next one
            {
                swap(array[j], array[j + 1]);      // Swap the current element with the next one
            }
        }
    }

}

// Function to perform insertion sort
void insertion_sort(int array[], int size) {
    // Loop through each element in the array, starting from the second one
    for (int i = 1; i < size; i++) {
        // Set the current element to a variable
        int key = array[i];
        
        // Set a variable to the index of the previous element
        int j = i - 1;
        
        // While the current element is less than the previous element
        while (j >= 0 && array[j] > key) {
            // Move the previous element to the right by one
            array[j + 1] = array[j];
            
            // Decrement the index of the previous element
            j = j - 1;
        }
        
        // Set the current element to its correct position
        array[j + 1] = key;
    }
}


// Function to get the pivot position for Quick Sort
int get_pivot_pos(int array[], int l, int h) {
    // Select three elements: the first, middle, and last elements of the array
    
    int a = array[l];              // first
    int b = array[(l + h) / 2];    // middle
    int c = array[h];              // last

    // Determine the median of the three elements and return its position
    
    if ((a >= b && a <= c) || (a <= b && a >= c))
        return l;                                       // Return the first position if 'a' is the median
    else if ((b >= a && b <= c) || (b <= a && b >= c))
        return (l + h) / 2;                             // Return the middle position if 'b' is the median
    else
        return h;                                       // Return the last position if 'c' is the median
}


// Function to partition the array for Quick Sort
int partition(int array[], int l, int h) {
    // Get the pivot position using the median of three elements
    int pivot_pos = get_pivot_pos(array, l, h);

    // Swap the pivot element with the last element of the array
    swap(array[pivot_pos], array[h]);

    // Initialize the index 'i' to the leftmost element
    int i = l;

    // Partition the array around the pivot element
    for (int j = l; j < h; j++) {
        if (array[j] < array[h]) {
            // If the current element is less than the pivot, swap it with the element at index 'i'
            swap(array[i], array[j]);
            i++;  // Increment 'i' to the next position
        }
    }

    // Swap the pivot element with the element at index 'i'
    swap(array[i], array[h]);

    // Return the final position of the pivot element
    return i;
}

void quick_sort(int array[], int l, int h) {
    // Base case: If the subarray has only one element, it is already sorted
    if (l < h) {
        // Partition the array and get the pivot position
        int p = partition(array, l, h);

        // If the left subarray has 5 or fewer elements, use Insertion Sort
        if (p - l <= 5) {
            insertion_sort(array + l, p - l + 1);
        } else {
            // Recursively sort the left and right subarrays
            quick_sort(array, l, p - 1);
            quick_sort(array, p + 1, h);
        }
    }
}


// Function to display array elements
void show_array(int array[], int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        // Display each element of the array
        cout << array[i] << " ";
    }
    cout << endl;
}


int main()
{
    srand(time(NULL));
    // more code here

    int arraysize;
    cout << "Enter the sample data size: ";
    cin >> arraysize;

    int array[arraysize];

// Bubble Sort
    cout << "Bubble sort (Random) took ";
    fill_array_random(array, arraysize, 1000, 1000000);

    auto start = chrono::steady_clock::now();
    bubble_sort(array, arraysize);
    auto end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << "Bubble sort (Increasing) took ";
    fill_array_inc(array, arraysize);

    start = chrono::steady_clock::now();
    bubble_sort(array, arraysize);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << "Bubble sort (Decreasing) took ";
    fill_array_dec(array, arraysize);

    start = chrono::steady_clock::now();
    bubble_sort(array, arraysize);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << endl;

//Insert Sort
    cout << "Insert sort (Random) took ";
    fill_array_random(array, arraysize, 1000, 1000000);

    start = chrono::steady_clock::now();
    insertion_sort(array, arraysize);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << "Insert sort (Increasing) took ";
    fill_array_inc(array, arraysize);

    start = chrono::steady_clock::now();
    insertion_sort(array, arraysize);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << "Insert sort (Decreasing) took ";
    fill_array_dec(array, arraysize);

    start = chrono::steady_clock::now();
    insertion_sort(array, arraysize);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;


    cout << endl;

// quicksort
    cout << "Quick sort(Random) took ";
    fill_array_random(array, arraysize, 1000, 1000000);

    start = chrono::steady_clock::now();
    quick_sort(array, 0, arraysize-1);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << "Quick sort(Increasing) took ";
    fill_array_inc(array, arraysize);

    start = chrono::steady_clock::now();
    quick_sort(array, 0, arraysize-1);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << "Quick sort(Decreasing) took ";
    fill_array_dec(array, arraysize);

    start = chrono::steady_clock::now();
    quick_sort(array, 0, arraysize-1);
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    cout << endl;

}
