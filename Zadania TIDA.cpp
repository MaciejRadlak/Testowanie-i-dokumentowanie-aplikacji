#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;


void bubbleSortIndex(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void bubbleSortPointer(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int* end = arr + n - i - 1;
        for (int* p = arr; p < end; ++p) {
            if (*p > *(p + 1)) {
                int temp = *p;
                *p = *(p + 1);
                *(p + 1) = temp;
            }
        }
    }
}

#include <iostream>
#include <cstdlib>   
#include <ctime>     

using namespace std;

const int SIZE_1 = 1000;
const int SIZE_2 = 10000;
const int SIZE_3 = 100000;

void generateRandomLists(int list1[], int list2[], int size) {
    for (int i = 0; i < size; i++) {
        int value = rand() % 100000;
        list1[i] = value;
        list2[i] = value;
    }
}

int main() {
    srand(123);

    int list1_1000[SIZE_1], list2_1000[SIZE_1];
    int list1_10000[SIZE_2], list2_10000[SIZE_2];
    int list1_100000[SIZE_3], list2_100000[SIZE_3];

    generateRandomLists(list1_1000, list2_1000, SIZE_1);
    generateRandomLists(list1_10000, list2_10000, SIZE_2);
    generateRandomLists(list1_100000, list2_100000, SIZE_3);

    cout << "------------------------------------\n";

    // ---------------- POINTER ----------------
    auto start = high_resolution_clock::now();
    bubbleSortPointer(list2_1000, 1000);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start).count();

    cout << "Pointer 1000: " << duration << "ms" << endl;

    copy(list1_1000, list1_1000 + SIZE_1, list2_1000);


    start = high_resolution_clock::now();
    bubbleSortPointer(list2_10000, SIZE_2);
    stop = high_resolution_clock::now();
    cout << "Pointer 10000: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    std::copy(list1_10000, list1_10000 + SIZE_2, list2_10000);

    start = high_resolution_clock::now();
    bubbleSortPointer(list2_100000, SIZE_3);
    stop = high_resolution_clock::now();
    cout << "Pointer 100000: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    std::copy(list1_100000, list1_100000 + SIZE_3, list2_100000);

    cout << "------------------------------------\n";

    // ---------------- INDEX ----------------



    start = high_resolution_clock::now();
    bubbleSortIndex(list2_1000, SIZE_1);
    stop = high_resolution_clock::now();
    cout << "Index 1000: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    std::copy(list1_1000, list1_1000 + SIZE_1, list2_1000);

    start = high_resolution_clock::now();
    bubbleSortIndex(list2_10000, SIZE_2);
    stop = high_resolution_clock::now();
    cout << "Index 10000: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    std::copy(list1_10000, list1_10000 + SIZE_2, list2_10000);

    start = high_resolution_clock::now();
    bubbleSortIndex(list2_100000, SIZE_3);
    stop = high_resolution_clock::now();
    cout << "Index 100000: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    cout << "------------------------------------\n";



    return 0;
}

