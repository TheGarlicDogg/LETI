#include <iostream>
#include <ctime>
#include <chrono>
#include <conio.h>;
using namespace std;

void bubbleSort(int* arr, int n) {
    for (; n != 1; n--)
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
}
void shakerSort(int* arr, int n) {
    for (; n != 1; n--)
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
    for (int i = n - 2; i > 0; i--) {
        if (arr[i] < arr[i - 1])
            swap(arr[i], arr[i - 1]);
    }
}
void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int current = arr[i];
        int j = i - 1;
        while (j >= 0 && current < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}
void combSort(int* arr, int n) {
    int gap = n;
    while (gap != 1) {
        gap = int(gap / 1.3);
        if (gap < 1)
            gap = 1;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap])
                swap(arr[i], arr[i + gap]);
        }
    }
}
int partition(int* arr, int start, int end) {
    int pivot = arr[end];
    int partitionIndex = start;
    for (int i = start; i < end; i++) {
        if (arr[i] <= pivot) {
            swap(arr[i], arr[partitionIndex]);
            partitionIndex++;
        }
    }
    swap(arr[partitionIndex], arr[end]);
    return partitionIndex;
}
void quickSort(int* arr, int start, int end) {
    if (start < end) {
        int partitionIndex = partition(arr, start, end);
        quickSort(arr, start, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, end);
    }
}

void merge(int array[], int const left, int const mid,
    int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // ������� ��������� �������
    int* leftArray = new int[subArrayOne];
    int* rightArray = new int[subArrayTwo];

    // ������� ������ �� ��������� �������
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    int indexOfSubArrayOne = 0; // ��������� ������ ������� ���-�������
    int indexOfSubArrayTwo = 0; // ��������� ������ ������� ���-�������
    int indexOfMergedArray = left; // ��������� ������ ������������ ������� 

    // ��������� ��� ��������� ������� � ����
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

/* ������ ����������� �� ��������������� �������, ���� �� ����� �������  */
void mergeSort(int array[], int const begin, int const end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void createNewArray(int* arr) {
    int const n = 100;
    cout << "��� ������: ";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 199 - 99;
        cout << arr[i] << " ";
    }
    cout << endl;
}
int binarySearch(int* arr, int start, int end, int x)
{
    if (start <= end) {
        int mid = (end - start) / 2 + start;
        if (arr[mid] == x) // ���� ����������� ������� � ���� ����� x
            return 1;
        if (arr[mid] > x) // ���� �����. ������� ������ x, �� ����� x ��������� �����
            return binarySearch(arr, start, mid - 1, x);
        return binarySearch(arr, mid + 1, end, x); // ������ �����. ������� ������ x, �� ���� ����� x ��������� ������
    }
    return -1;
}
int answer = 0;

int drivercode2() {
    setlocale(0, "");
    srand(time(0));

    int const n = 100;
    int arr[n];
    int unsortedArr[n];
    cout << "��� ������: ";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 199 - 99;
        unsortedArr[i] = arr[i];
        cout << arr[i] << " ";
    }
    cout << endl << endl;
    int minnum, maxnum, meannum, counter, result, index1, index2;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> durationMinMaxUnsorted = end - start;
    while (true) {
        cout << "�������� �������� � ��������:\n1. ������� ����� ������\n2. ������������� ������\n3. ����� ������������ � ����������� ������� �������\n4. ������� ������� ��������\n5. ������� ���������� ��������� � ��������������� �������, ������� ������ ���������� �����\n6. ������� ���������� ��������� � ��������������� �������, ������� ������ ���������� �����\n7. ������� ���������� � ���, ���� �� ��������� ����� � �������\n8. �������� ������� �������� �������\n";
        char ch = 50;
        int answer;
        ch = _getch();
        if (ch == 27) {
            break;
        }
        answer = int(ch) - 48;
            switch (answer) {
            case 1:
                createNewArray(arr);
                cout << endl;
                break;
            case 2:
                cout << "�������� ��� ����������:" << endl << "1. Bubble sort" << endl << "2. Shaker sort" << endl << "3. Insertion sort" << endl << "4. Comb sort" << endl << "5. Quick sort" << endl << "6. Merge sort" << endl;
                cin >> answer;
                switch (answer)
                {
                case 1:
                    start = chrono::high_resolution_clock::now();
                    bubbleSort(arr, n);
                    end = chrono::high_resolution_clock::now();
                    break;
                case 2:
                    start = chrono::high_resolution_clock::now();
                    shakerSort(arr, n);
                    end = chrono::high_resolution_clock::now();
                    break;
                case 3:
                    start = chrono::high_resolution_clock::now();
                    insertionSort(arr, n);
                    end = chrono::high_resolution_clock::now();
                    break;
                case 4:
                    start = chrono::high_resolution_clock::now();
                    combSort(arr, n);
                    end = chrono::high_resolution_clock::now();
                    break;
                case 5:
                    start = chrono::high_resolution_clock::now();
                    quickSort(arr, 0, n - 1);
                    end = chrono::high_resolution_clock::now();
                    break;
                case 6:
                    start = chrono::high_resolution_clock::now();
                    mergeSort(arr, 0, n - 1);
                    end = chrono::high_resolution_clock::now();
                    break;
                default:
                    break;
                }
                chrono::duration<float> duration = end - start;
                for (int i = 0; i < n; i++)
                    cout << arr[i] << " ";
                cout << "\n������������� �� " << fixed << duration.count() << " ���." << endl << endl;
                break;
            case 3:
                start = chrono::high_resolution_clock::now();
                minnum = arr[0];
                maxnum = arr[n - 1];
                end = chrono::high_resolution_clock::now();
                duration = end - start;
                cout << "\n������� ����������� � ������������ �����: " << minnum << ", " << maxnum << endl;
                cout << "� ��������������� �� " << fixed << duration.count() * 1000 << " ��. (" << defaultfloat << duration.count() << " ���.)" << endl;
                start = chrono::high_resolution_clock::now();
                minnum = 100;
                maxnum = 0;
                for (int i = 0; i < n; i++) {
                    if (unsortedArr[i] > maxnum) maxnum = arr[i];
                    if (unsortedArr[i] < minnum) minnum = arr[i];
                }
                end = chrono::high_resolution_clock::now();
                duration = end - start;
                cout << "� ����������������� �� " << fixed << duration.count() * 1000 << " ��. (" << defaultfloat << duration.count() << " ���.)" << endl << endl;
                break;
            case 4:
                minnum = arr[0];
                maxnum = arr[n - 1];
                meannum = round((maxnum + minnum) / 2);
                counter = 0;
                for (int i = 0; i < n; i++)
                    if (arr[i] == meannum)
                        counter++;
                cout << "\n������� �������� = " << meannum << ". ��� ����������� � �������: " << counter << endl << endl;
                break;
            case 5:
                cout << "������� �����: ";
                cin >> answer;
                counter = 0;
                for (int i = 0; i < n; i++) {
                    if (arr[i] < answer)
                        counter++;
                    else
                        break;
                }
                cout << "\n��������� ������ " << answer << ": " << counter << endl << endl;
                break;
            case 6:
                cout << "������� �����: ";
                cin >> answer;
                counter = 0;
                for (int i = n - 1; i >= 0; i--) {
                    if (arr[i] > answer)
                        counter++;
                    else
                        break;
                }
                cout << "\n��������� ������ " << answer << ": " << counter << endl << endl;
                break;
            case 7:
                cout << "������� �����, ����� ��������� ��� �������: ";
                cin >> answer;
                start = chrono::high_resolution_clock::now();
                result = binarySearch(arr, 0, n - 1, answer);
                end = chrono::high_resolution_clock::now();
                duration = end - start;
                (result == -1) ? cout << "\n����� " << answer << " �� ���������� � �������" << endl : cout << "\n����� " << answer << " ���������� � �������" << endl;
                cout << "��������� �������� ������� �� " << fixed << duration.count() * 1000 << " ��. (" << defaultfloat << duration.count() << " ���.)" << endl;
                start = chrono::high_resolution_clock::now();
                for (int i = 0; i < n; i++)
                    if (arr[i] == answer)
                        break;
                end = chrono::high_resolution_clock::now();
                duration = end - start;
                cout << "��������� ������� ��������� �� " << fixed << duration.count() * 1000 << " ��. (" << defaultfloat << duration.count() << " ���.)" << endl << endl;
                break;
            case 8:
                while (true) {
                    cout << "������� ��� ������� ���������, ����� �������� �� �������: ";
                    cin >> index1 >> index2;
                    if (index1 < 0 || index1 > n - 1 || index2 < 0 || index2 > n - 1)
                        cout << "������� ������� �������, ���������� ��� ���." << endl;
                    else
                        break;
                }
                start = chrono::high_resolution_clock::now();
                swap(arr[index1], arr[index2]);
                end = chrono::high_resolution_clock::now();
                duration = end - start;
                for (int i = 0; i < n; i++)
                    cout << arr[i] << " ";
                cout << "\n���������� �� " << fixed << duration.count() * 1000 << " ��. (" << defaultfloat << duration.count() << " ���.)" << endl << endl;
                break;
            default:
                return 0;
            }
        }
}