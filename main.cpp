#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <cmath>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;


void InsertionSortTest();

void MergeSortTest();

void LomutoQuickSortTest();

void HoareQuickSortTest();
void HoareQuickSortTest_try();

void ThreeWayQuickSortTest();

void CountingSortTest();




int main()
{
    string sortingWay;
    while (cin >> sortingWay)
    {
        if (sortingWay == "insertion")
        {
            InsertionSortTest();
        }
        else if (sortingWay == "merge")
        {
            MergeSortTest();
        }
        else if (sortingWay == "quick-Lomuto")//check random
        {
            LomutoQuickSortTest();
        }
        else if (sortingWay == "quick-Hoare")//check random
        {
            HoareQuickSortTest_try();
        }
        else if (sortingWay == "quick-3way")//check random
        {
            ThreeWayQuickSortTest();
        }

        else if (sortingWay == "counting")
        {
            CountingSortTest();
        }
    }

    return 0;
}








//Insertion Sort//
void insertionSort(vector<int>& arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void InsertionSortTest() 
{
    srand(time(NULL));

    int start, end, repeat;
    cin >> start;
    cin >> end; 
    cin >> repeat;


    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end+1); k++)
    {
       
        double sortingTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            vector<int> InputArray;

            for (int i = 0; i < pow(2, k); i++)
            {
                InputArray.push_back((rand()%1000)+1);
            }

            double sorting_START, sorting_END;
            sorting_START = clock();

            insertionSort(InputArray, pow(2, k));

            sorting_END = clock();
            sortingTotalSpendTime += ((sorting_END - sorting_START) / CLOCKS_PER_SEC);
        }
      
        double sortingAvrgSpendTime = sortingTotalSpendTime / repeat;      
        cout << endl << "Dynamic Array新增2^" << k << "個隨機數後用Insertion Sort排序所有資料所需的時間:" << sortingAvrgSpendTime << " sec" << endl << endl;
    }

}

//Merge Sort//
const int Max = 10000;
void Merge(vector<int>& Array, int front, int mid, int end) {

    // 利用 std::vector 的constructor, 
    // 把array[front]~array[mid]放進 LeftSub[]
    // 把array[mid+1]~array[end]放進 RightSub[]
    std::vector<int> LeftSub(Array.begin() + front, Array.begin() + mid + 1),
        RightSub(Array.begin() + mid + 1, Array.begin() + end + 1);

    LeftSub.insert(LeftSub.end(), Max);      // 在LeftSub[]尾端加入值為 Max 的元素
    RightSub.insert(RightSub.end(), Max);    // 在RightSub[]尾端加入值為 Max 的元素

    int idxLeft = 0, idxRight = 0;

    for (int i = front; i <= end; i++) {

        if (LeftSub[idxLeft] <= RightSub[idxRight]) {
            Array[i] = LeftSub[idxLeft];
            idxLeft++;
        }
        else {
            Array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
}

void MergeSort(vector<int>& array, int front, int end) {
    // front與end為矩陣範圍
    if (front < end) {                   // 表示目前的矩陣範圍是有效的
        int mid = (front + end) / 2;         // mid即是將矩陣對半分的index
        MergeSort(array, front, mid);    // 繼續divide矩陣的前半段subarray
        MergeSort(array, mid + 1, end);    // 繼續divide矩陣的後半段subarray
        Merge(array, front, mid, end);   // 將兩個subarray做比較, 並合併出排序後的矩陣
    }
}


void MergeSortTest()
{
    srand(time(NULL));

    int start, end, repeat;
    cin >> start;
    cin >> end;
    cin >> repeat;


    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {

        double sortingTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            vector<int> InputArray;

            for (int i = 0; i < pow(2, k); i++)
            {
                InputArray.push_back((rand() % 1000) + 1);
            }

            double sorting_START, sorting_END;
            sorting_START = clock();

            MergeSort(InputArray, 0, pow(2, k)-1);

            sorting_END = clock();
            sortingTotalSpendTime += ((sorting_END - sorting_START) / CLOCKS_PER_SEC);
        }

        double sortingAvrgSpendTime = sortingTotalSpendTime / repeat;
        cout << endl << "Dynamic Array新增2^" << k << "個隨機數後用Merge Sort排序所有資料所需的時間:" << sortingAvrgSpendTime << " sec" << endl << endl;
    }

}



//Randomized Quick Sort//



//Lomuto

void mySwap(int* i, int* j)
{
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

int LomutoPartition(vector<int> arr, int l, int r)
{
    //int pivot = arr[r];//ASK random or not
    
    int pivot = arr[l + rand() % (r - l)];
    swap(arr[r], pivot);
    

    int i = l;
    for (int j = l; j < r; ++j) {
        if (arr[j] < pivot) {
            mySwap(&arr[i], &arr[j]);
            ++i;
        }
    }
    mySwap(&arr[i], &arr[r]);
    return i;
}

void QuickSort_L(vector<int> arr, int l, int r)
{
    if (l >= r)
        return;

    int i = LomutoPartition(arr, l, r);

    QuickSort_L(arr, l, i - 1);
    QuickSort_L(arr, i + 1, r);
}




void LomutoQuickSortTest()
{
    srand(time(NULL));

    int start, end, repeat;
    cin >> start;
    cin >> end;
    cin >> repeat;


    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {

        double sortingTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            vector<int> InputArray;

            for (int i = 0; i < pow(2, k); i++)
            {
                InputArray.push_back((rand() % 1000) + 1);
            }

            double sorting_START, sorting_END;
            sorting_START = clock();

            QuickSort_L(InputArray, 0, pow(2, k) - 1);

            sorting_END = clock();
            sortingTotalSpendTime += ((sorting_END - sorting_START) / CLOCKS_PER_SEC);
        }

        double sortingAvrgSpendTime = sortingTotalSpendTime / repeat;
        cout << endl << "Dynamic Array新增2^" << k << "個隨機數後用Quick Sort排序(Lomuto Partition)所需的時間:" << sortingAvrgSpendTime << " sec" << endl << endl;
    }

}





//Hoare1


int HoarePartition(vector<int> arr, int low, int high)
{
    int pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true) {

        // Find leftmost element greater than
        // or equal to pivot
        do {
            i++;
        } while (arr[i] < pivot);

        // Find rightmost element smaller than
        // or equal to pivot
        do {
            j--;
        } while (arr[j] > pivot);

        // If two pointers met
        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

// Generates Random Pivot, swaps pivot with
// end element and calls the partition function
// In Hoare partition the low element is selected
// as first pivot
int partition_r_H(vector<int> arr, int low, int high)
{
    // Generate a random number in between
    // low .. high
    srand(time(NULL));
    int random = low + rand() % (high - low);

    // Swap A[random] with A[high]
    swap(arr[random], arr[low]);

    return HoarePartition(arr, low, high);
}

// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low  --> Starting index,
// high  --> Ending index
void QuickSort_H(vector<int> arr, int low, int high)
{
    if (low < high) {
        // pi is partitioning index, 
        // arr[p] is now at right place
        int pi = partition_r_H(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        QuickSort_H(arr, low, pi);
        QuickSort_H(arr, pi + 1, high);
    }
}




void HoareQuickSortTest()
{
    srand(time(NULL));

    int start, end, repeat;
    cin >> start;
    cin >> end;
    cin >> repeat;


    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {

        double sortingTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            vector<int> InputArray;

            for (int i = 0; i < pow(2, k); i++)
            {
                InputArray.push_back((rand() % 1000) + 1);
            }

            double sorting_START, sorting_END;
            sorting_START = clock();

            QuickSort_H(InputArray, 0, pow(2, k) - 1);

            sorting_END = clock();
            sortingTotalSpendTime += ((sorting_END - sorting_START) / CLOCKS_PER_SEC);
        }

        double sortingAvrgSpendTime = sortingTotalSpendTime / repeat;
        cout << endl << "Dynamic Array新增2^" << k << "個隨機數後用Quick Sort排序(Hoare Partition)所需的時間:" << sortingAvrgSpendTime << " sec" << endl << endl;
    }

}


//Partitioning using Hoare's partition scheme.

int partitionHoare(vector<int>inputHoare, int lowerboundIndex, int upperboundIndex)

{

    int pivot = inputHoare[lowerboundIndex];

    int startIndex = lowerboundIndex - 1;

    int endIndex = upperboundIndex + 1;



    while (true)

    {

        // Finding the first element from the left that's greater than or 

        // equal to the pivot.

        do

        {

            startIndex++;

        } while (inputHoare[startIndex] < pivot);



        // Finding the first element from the right that's element smaller 

        // than or equal to the pivot.

        do {

            endIndex--;

        } while (inputHoare[endIndex] > pivot);



        // If the left index and right index meet or cross each other, 

        // partition returns the index of the right index that now 

        // represents a smaller index than the left index. That is, it

        // returns the endIndex.

        if (startIndex >= endIndex)

            return endIndex;

        // If start and end index have not met or crossed each other, we've 

        // found an inversion so we swap the two values.

        swap(inputHoare[startIndex], inputHoare[endIndex]);

    }

}



//Implementing quick sort using Hoare's partition.

void quickSortHoare(vector<int>inputHoare, int lowerboundIndex, int upperboundIndex)

{

    if (lowerboundIndex < upperboundIndex) {

        //Partitioning puts the element inputHoare[partitionIndex] at its 

        //rightful place.

        int partitionIndex = partitionHoare(inputHoare, lowerboundIndex, upperboundIndex);

        // Sorting the subarray till the partition element. It contains  

        // elements lower than the partition element.

        quickSortHoare(inputHoare, lowerboundIndex, partitionIndex);

        // Sorting the subarray after the partition element. It contains 

        // elements larger than the partition element.

        quickSortHoare(inputHoare, partitionIndex + 1, upperboundIndex);

    }

}



void HoareQuickSortTest_try()
{
    srand(time(NULL));

    int start, end, repeat;
    cin >> start;
    cin >> end;
    cin >> repeat;


    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {

        double sortingTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            vector<int> InputArray;

            for (int i = 0; i < pow(2, k); i++)
            {
                InputArray.push_back((rand() % 1000) + 1);
            }

            double sorting_START, sorting_END;
            sorting_START = clock();

            quickSortHoare(InputArray, 0, pow(2, k) - 1);

            sorting_END = clock();
            sortingTotalSpendTime += ((sorting_END - sorting_START) / CLOCKS_PER_SEC);
        }

        double sortingAvrgSpendTime = sortingTotalSpendTime / repeat;
        cout << endl << "Dynamic Array新增2^" << k << "個隨機數後用Quick Sort排序(Hoare Partition_try)所需的時間:" << sortingAvrgSpendTime << " sec" << endl << endl;
    }

}




//Three Way


int* ThreeWayPartition(vector<int>& a, int l, int r)
{
    
    int* m = new int[2];

    int x = a[l];

    int j = l;
    int k = l;

    for (int i = l + 1; i <= r; i++) {

        if (a[i] < x) {
            j++;
            k++;
            swap(a[i], a[j]);
        }
        else if (a[i] == x)
        {
            k++;
            swap(a[i], a[k]);
        }
    }
    swap(a[l], a[j]);
    m[0] = j;
    m[1] = k;
    return m;
    
}


void RandomizedQuickSort_3(vector<int>& a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);

    swap(a[l], a[k]);

    int* m = new int[2];

    m = ThreeWayPartition(a, l, r);

    RandomizedQuickSort_3(a, l, m[0] - 1);
    RandomizedQuickSort_3(a, m[1], r);

}


void ThreeWayQuickSortTest()
{
    srand(time(NULL));

    int start, end, repeat;
    cin >> start;
    cin >> end;
    cin >> repeat;


    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {

        double sortingTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            vector<int> InputArray;

            for (int i = 0; i < pow(2, k); i++)
            {
                InputArray.push_back((rand() % 1000) + 1);
            }

            double sorting_START, sorting_END;
            sorting_START = clock();

            RandomizedQuickSort_3(InputArray, 0, pow(2, k) - 1);

            sorting_END = clock();
            sortingTotalSpendTime += ((sorting_END - sorting_START) / CLOCKS_PER_SEC);
        }

        double sortingAvrgSpendTime = sortingTotalSpendTime / repeat;
        cout << endl << "Dynamic Array新增2^" << k << "個隨機數後用Randomized Quick Sort排序(Three Way Partition)所需的時間:" << sortingAvrgSpendTime << " sec" << endl << endl;
    }

}









//Counting Sort//
void CountSort(vector<int> arr, int n)
{

    // Map to store the frequency
    // of the array elements
    map<int, int> freqMap;
    for (auto i = arr.begin(); i != arr.end(); i++) {
        freqMap[*i]++;
    }

    int i = 0;

    // For every element of the map
    for (auto it : freqMap) {

        // Value of the element
        int val = it.first;

        // Its frequency
        int freq = it.second;
        for (int j = 0; j < freq; j++)
            arr[i++] = val;
    }

}

void CountingSortTest()
{
    srand(time(NULL));

    int start, end, repeat;
    cin >> start;
    cin >> end;
    cin >> repeat;


    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {

        double sortingTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            vector<int> InputArray;

            for (int i = 0; i < pow(2, k); i++)
            {
                InputArray.push_back((rand() % 1000) + 1);
            }

            double sorting_START, sorting_END;
            sorting_START = clock();

            CountSort(InputArray, pow(2, k));

            sorting_END = clock();
            sortingTotalSpendTime += ((sorting_END - sorting_START) / CLOCKS_PER_SEC);
        }

        double sortingAvrgSpendTime = sortingTotalSpendTime / repeat;
        cout << endl << "Dynamic Array新增2^" << k << "個隨機數後用Counting Sort排序所有資料所需的時間:" << sortingAvrgSpendTime << " sec" << endl << endl;
    }

}

