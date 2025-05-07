#include <iostream>
using namespace std;
#include <vector>

class HeapProcessor {
private:
    vector<float> arr;  // vector instead of raw pointer

    void conv_to_heap(int n, int i) {
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            conv_to_heap(n, largest);
        }
    }

public:
    void readMarks() {
        int n;
        cout << "Enter the No. of SE Students: ";
        cin >> n;

        arr.resize(n);  // resize vector
        for (int i = 0; i < n; i++) {
            cout << "Enter the marks of Student " << i+1 << ": ";
            cin >> arr[i];
        }
    }

    void sortHeap() {
        int n = arr.size(); 
        for (int i = n/2 - 1; i >= 0; i--)
            conv_to_heap(n, i);

        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            conv_to_heap(i, 0);
        }
    }

    void displayResults() {
        int n = arr.size();
        cout << "Minimum Marks are: " << arr[0] << endl;
        cout << "Maximum Marks are: " << arr[n-1] << endl;

        cout << "Sorted Array is: ";
        for (float mark : arr)
            cout << mark << " ";
        cout << endl;
    }
};
int main() {
    HeapProcessor hp;
    hp.readMarks();
    hp.sortHeap();
    hp.displayResults();
    return 0;
}
