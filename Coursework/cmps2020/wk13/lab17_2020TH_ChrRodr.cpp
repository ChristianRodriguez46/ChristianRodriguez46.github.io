#include <iostream>

using namespace std;

// Function to check if array is max-heap
bool is_max_heap(int data[], int count) {
    // Check if each parent node is greater than or equal to its children
    for (int i = 0; i <= (count - 2) / 2; ++i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < count && data[i] < data[left]) return false;
        if (right < count && data[i] < data[right]) return false;
    }
    return true;
}

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the array
void heapify(int data[], int count, int parent) {
    int largest = parent;
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if (left < count && data[left] > data[largest]) largest = left;
    if (right < count && data[right] > data[largest]) largest = right;

    if (largest != parent) {
        swap(&data[parent], &data[largest]);
        heapify(data, count, largest);
    }
}

// Function to build a max-heap from the array
void build_max_heap(int data[], int count) {
    for (int i = count / 2 - 1; i >= 0; --i) {
        heapify(data, count, i);
    }
}

// Function to sort the array using heap sort
void heap_sort(int data[], int count) {
    build_max_heap(data, count);
    for (int i = count - 1; i > 0; --i) {
        swap(&data[0], &data[i]);
        heapify(data, i, 0);
    }
}

// Function to show the contents of the array
void show_array(int data[], int count) {
    for (int i = 0; i < count; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}

int main() {
    int data[1000];
    int count = 0;
    int num;

    while (true) {
        cout << "Enter a number (-1 to stop): ";
        cin >> num;
        if (num == -1) break;
        
        data[count] = num;
        ++count;

        // Rebuild the max-heap after inserting a new element
        build_max_heap(data, count);

        show_array(data, count);
        if (is_max_heap(data, count)) {
            cout << "Array is a verified max-heap" << endl;
        } else {
            cout << "Array is not a max-heap" << endl;
        }
    }

    // Sort the array using heap sort
    heap_sort(data, count);
    cout << "Sorted array: ";
    show_array(data, count);

    return 0;
}