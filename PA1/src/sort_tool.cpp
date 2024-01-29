// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int length = data.size();
    for (int i=1 ; i<length ; ++i){
        int key = data[i];
        int j = i-1;
        while(j>-1 && data[j] > key){
            data[j+1] = data[j];
            j -= 1;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if (flag == 0) {
        if (low >= high) {
            return;
        }
        int q = Partition(data, low, high);
        QuickSortSubVector(data, low, q, 0);
        QuickSortSubVector(data, q+1, high, 0);
    } else {
        if (low >= high) {
            return;
        }
        int q = RandomizedPartition(data, low, high);
        QuickSortSubVector(data, low, q, 1);
        QuickSortSubVector(data, q+1, high, 1);
    }
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    srand(time(0));
    int random = (rand() % (high-low+1)) + low;
    swap(data[random], data[low]);
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function

    int pivot= data[low];
    int right_ptr = high;
    int left_ptr = low;
    while (true) {
        while(data[left_ptr] < pivot){
            left_ptr += 1;
        }
        while(data[right_ptr] > pivot){
            right_ptr -= 1;
        }
        if (left_ptr < right_ptr){
            int temp = data[right_ptr];
            data[right_ptr] = data[left_ptr];
            data[left_ptr] = temp;
            left_ptr += 1;
            right_ptr -= 1;
        } else {
            return right_ptr;
        }
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low == high){
        return;
    }
    int middle = (low + high)/2;
    MergeSortSubVector(data, low, middle);
    MergeSortSubVector(data, middle+1, high);
    Merge(data, low, middle, high);
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int length_L = middle - low + 1;
    int length_R = high - middle;

    int L[length_L] = {};
    int R[length_R] = {};

    for (int i=0 ; i<length_L ; ++i){
        L[i] = data[low + i];
    }
    for (int i=0 ; i<length_R ; ++i){
        R[i] = data[middle + 1 + i];
    }

    int L_ptr = 0;
    int R_ptr = 0;

    for (int i=0 ; i<high-low+1 ; ++i){
        if (L_ptr != length_L && R_ptr != length_R){
            if (L[L_ptr] <= R[R_ptr]){
                data[low+i] = L[L_ptr];
                L_ptr += 1;  
            } else {
                data[low+i] = R[R_ptr];
                R_ptr += 1;
            }
        } else if (L_ptr == length_L){
            data[low+i] = R[R_ptr];
            R_ptr += 1;
        } else {
            data[low+i] = L[L_ptr];
            L_ptr += 1; 
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left_child = root * 2;
    int right_child = root * 2 + 1;
    int max = root;
    if (left_child < heapSize && data[left_child] > data[max]){
        max = left_child;
    } 
    if (right_child < heapSize && data[right_child] > data[max]){
        max = right_child;
    }

    if (max != root){
        swap(data[max], data[root]);
        MaxHeapify(data, max);
    } else {
        return;
    }

}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i=heapSize/2 ; i>=0 ; --i){
        MaxHeapify(data, i);
    }
}
