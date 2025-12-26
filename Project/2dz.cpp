#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

void quicksort(int* arr, int begin, int end);

int main() {
    const int n = 100;
    nanoseconds time1, time2, time3, time4, time5, timeUns, timeSort, timeSwap;

    int arrOriginal[n];
    int arrBubbleS[n];
    int arrShakerS[n];
    int arrGnomeS[n];
    int arrCombS[n];
    int arrQuickS[n];
    int choice;

    do {
        cout << "Task Number: ";
        cin >> choice;
        switch (choice) {
        case 0:
            cout << "Stop program" << endl;
            break;
        case 1: {
            srand(time(0));
            for (int i = 0; i < n; i++) {
                int num = rand() % 199 - 99;
                arrOriginal[i] = num;
                arrBubbleS[i] = arrShakerS[i] = arrGnomeS[i] = arrCombS[i] = arrQuickS[i] = num;
            }
            break;
        }

        case 2: {
            //Bubble Sort
            auto start = steady_clock::now();
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (arrBubbleS[j] > arrBubbleS[j + 1]) {
                        swap(arrBubbleS[j], arrBubbleS[j + 1]);
                    }
                }
            }
            auto end = steady_clock::now();
            time1 = duration_cast<nanoseconds>(end - start);
            cout << "Sorted Array: ";
            for (int i = 0; i < n; i++)
                cout << arrBubbleS[i] << " ";
            cout << endl;
            //Shaker Sort
            start = steady_clock::now();
            int left = 0;
            int right = n - 1;
            while (left <= right) {
                for (int i = left; i < right; ++i) {
                    if (arrShakerS[i] > arrShakerS[i + 1]) swap(arrShakerS[i], arrShakerS[i + 1]);
                }
                --right;

                for (int i = right; i > left; --i) {
                    if (arrShakerS[i] < arrShakerS[i - 1]) swap(arrShakerS[i], arrShakerS[i - 1]);
                }
                ++left;
            }
            end = steady_clock::now();
            time2 = duration_cast<nanoseconds>(end - start);
            //Gnome Sort
            start = steady_clock::now();
            int i = 0;
            while (i < n) {
                if (i == 0 || arrGnomeS[i - 1] <= arrGnomeS[i]) {
                    ++i;
                }
                else {
                    swap(arrGnomeS[i], arrGnomeS[i - 1]);
                    --i;
                }
            }
            end = steady_clock::now();
            time3 = duration_cast<nanoseconds>(end - start);
            //Comb Sort
            start = steady_clock::now();
            const double shrink = 1.247;
            int gap = n;
            bool swapped = true;
            while (gap > 1 || swapped) {
                gap = static_cast<int>(gap / shrink);
                if (gap < 1) gap = 1;
                swapped = false;
                for (int i = 0; i + gap < n; ++i) {
                    if (arrCombS[i] > arrCombS[i + gap]) {
                        swap(arrCombS[i], arrCombS[i + gap]);
                        swapped = true;
                    }
                }
            }
            end = steady_clock::now();
            time4 = duration_cast<nanoseconds>(end - start);
            //Quick Sort
            start = steady_clock::now();
            quicksort(arrQuickS, 0, n - 1);
            end = steady_clock::now();
            time5 = duration_cast<nanoseconds>(end - start);

            cout << "Time of Bubble sort: " << time1.count() << endl;
            cout << "Time of Shaker sort: " << time2.count() << endl;
            cout << "Time of Gnome sort: " << time3.count() << endl;
            cout << "Time of Comb sort: " << time4.count() << endl;
            cout << "Time of Quick sort: " << time5.count() << endl;
            break;
        }

        case 3: {
            auto start = steady_clock::now();
            int minUnsorted = arrOriginal[0];
            int maxUnsorted = arrOriginal[0];
            for (int i = 0; i < n; ++i) {
                if (maxUnsorted < arrOriginal[i]) maxUnsorted = arrOriginal[i];
                if (minUnsorted > arrOriginal[i]) minUnsorted = arrOriginal[i];
            }
            auto end = steady_clock::now();
            timeUns = duration_cast<nanoseconds>(end - start);
            cout << "Min: " << minUnsorted << " Max: " << maxUnsorted << " Time of search in uns arr: " << timeUns.count() << endl;

            start = steady_clock::now();
            int min_sorted = arrBubbleS[0];
            int max_sorted = arrBubbleS[n - 1];
            end = steady_clock::now();
            timeSort = duration_cast<nanoseconds>(end - start);
            cout << "Min: " << min_sorted << " Max: " << max_sorted << " Time of search in sort arr: " << timeSort.count() << endl;
            break;
        }

        case 4: {
            int avrNum = (arrBubbleS[0] + arrBubbleS[n - 1]) / 2;
            int count = 0;
            cout << "Average Number: " << avrNum << endl;
            auto start = steady_clock::now();
            for (int i = 0; i < n; i++) {
                if (arrOriginal[i] == avrNum) {
                    cout << i;
                    count += 1;
                }
            }
            auto end = steady_clock::now();
            timeUns = duration_cast<nanoseconds>(end - start);
            cout << "Time of Unsort: " << timeUns.count() << endl;
            cout << "Count: " << count << endl;

            start = steady_clock::now();
            int l = 0;
            int r = n - 1;
            int m;
            int lBorder = -1;
            int rBorder = -1;
            while (l <= r) {
                m = (l + r) / 2;
                if (arrBubbleS[m] >= avrNum) {
                    if (arrBubbleS[m] == avrNum) lBorder = m;
                    r = m - 1;
                }
                else l = m + 1;
            }
            l = 0;
            r = n - 1;
            while (l <= r) {
                m = (l + r) / 2;
                if (arrBubbleS[m] <= avrNum) {
                    if (arrBubbleS[m] == avrNum) rBorder = m;
                    l = m + 1;
                }
                else r = m - 1;
            }
            if (lBorder != -1) {
                for (int i = lBorder; i <= rBorder; i++) {
                    cout << i << " ";
                }
            }
            end = steady_clock::now();
            timeSort = duration_cast<nanoseconds>(end - start);
            cout << "Time of Sort: " << timeSort.count() << endl;
            cout << "Count: " << (lBorder != -1 ? (rBorder - lBorder + 1) : 0) << endl;
            break;
        }

        case 5: {
            int a;
            cout << "Enter number a: ";
            cin >> a;
            int l = 0;
            int r = n - 1;
            int countless = n;
            while (l <= r) {
                int m = (l + r) / 2;
                if (arrBubbleS[m] >= a) {
                    countless = m;
                    r = m - 1;
                }
                else { l = m + 1; }
            }
            cout << "element less than " << a << ": " << countless << endl;
            break;
        }

        case 6: {
            int b;
            cout << "Enter number b: ";
            cin >> b;
            int l = 0;
            int r = n - 1;
            int lastLess = -1;
            int countmore;
            while (l <= r) {
                int m = (l + r) / 2;
                if (arrBubbleS[m] <= b) {
                    lastLess = m;
                    l = m + 1;
                }
                else r = m - 1;
            }
            if (lastLess == -1) {
                countmore = n;
            }
            else {
                countmore = n - (lastLess + 1);
            }
            cout << "element more than " << b << ": " << countmore << endl;
            break;
        }

        case 7: {
            int l = 0;
            int r = n - 1;
            int c;
            cout << "Enter number to search: ";
            cin >> c;
            auto start = steady_clock::now();
            bool found = false;
            while (l <= r) {
                int m = (l + r) / 2;
                if (arrBubbleS[m] == c) {
                    found = true;
                    break;
                }
                if (arrBubbleS[m] > c)
                    r = m - 1;
                else
                    l = m + 1;
            }
            auto end = steady_clock::now();
            timeSort = duration_cast<nanoseconds>(end - start);
            if (found)
                cout << "number exists" << endl;
            else cout << "number doesn`t exists" << endl;
            cout << "Time by binary search: " << timeSort.count() << endl;

            start = steady_clock::now();
            found = false;
            for (int i = 0; i < n; i++) {
                if (arrBubbleS[i] == c)
                    found = true;
            }
            end = steady_clock::now();
            timeUns = duration_cast<nanoseconds>(end - start);
            if (found)
                cout << "number exists" << endl;
            else cout << "number doesn`t exists" << endl;
            cout << "Time by usual enumeration: " << timeUns.count() << endl;
            break;
        }

        case 8: {
            int ind1, ind2;
            cout << "Enter indexes to swap: " << endl;
            cin >> ind1 >> ind2;
            if (ind1 < 0 || ind1 >= n || ind2 < 0 || ind2 >= n) {
                cout << "Invalid indexes" << endl;
            }
            else {
                auto start = steady_clock::now();
                swap(arrBubbleS[ind1], arrBubbleS[ind2]);
                auto end = steady_clock::now();
                timeSwap = duration_cast<nanoseconds>(end - start);
                cout << "Swap time: " << timeSwap.count() << endl;
            }
            cout << "Array after swap: ";
            for (int i = 0; i < n; i++) {
                cout << arrBubbleS[i] << " ";
            }
            break;
        }
        case 9:
            int min1, min2, max1, max2;
            if (arrOriginal[0] < arrOriginal[1]) {
                min1 = arrOriginal[0]; min2 = arrOriginal[1];
                max1 = arrOriginal[1]; max2 = arrOriginal[0];
            }
            else {
                min1 = arrOriginal[1]; min2 = arrOriginal[0];
                max1 = arrOriginal[0]; max2 = arrOriginal[1];
            }
            for (int i = 2; i < n - 1; i += 2) {
                int num1 = arrOriginal[i];
                int num2 = arrOriginal[i + 1];

                if (num1 > num2) {
                    swap(num1, num2);
                }
                if (num1 < min1) {
                    min2 = min1;
                    min1 = num1;
                }
                else if (num1 < min2) {
                    min2 = num1;
                }
                if (num2 > max1) {
                    max2 = max1;
                    max1 = num2;
                }
                else if (num2 > max2) {
                    max2 = num2;
                }
            }
            cout << "Two Max: " << min1 << ", " << min2 << endl;
            cout << "Two Min: " << max1 << ", " << max2 << endl;
            break;
        default:
            break;
        }
    } while (choice != 0);

    return 0;
}

void quicksort(int* arr, int begin, int end) {
    if (begin >= end) return;

    int left = begin;
    int right = end;
    int mid = arr[(left + right) / 2];

    while (left <= right) {
        while (arr[left] < mid) left++;
        while (arr[right] > mid) right--;

        if (left <= right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    if (begin < right) quicksort(arr, begin, right);
    if (left < end) quicksort(arr, left, end);
}