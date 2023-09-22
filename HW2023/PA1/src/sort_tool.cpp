// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include <cstdlib> // 亂數相關函數 
#include <bits/stdc++.h>  //for swap
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here

    for(int i=1;i<data.size();i++){
        int key=data[i];
        int j=i-1;
        while(j>=0&&data[j]>key){
            data[j+1]=data[j];
            j--;
        }
        data[j+1]=key;
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

    if(low<high){
        int pivot;
        if(flag==0){
            pivot=Partition(data,low,high);
        }
        else{
            pivot=RandomizedPartition(data,low,high);
        }
        QuickSortSubVector(data,low,pivot-1,flag);
        QuickSortSubVector(data,pivot+1,high,flag);
    }
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int pivot=rand()%(high-low+1)+low;
    swap(data[pivot],data[high]);
    pivot = Partition(data,low,high);
    return pivot;
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int pivot=data[high];
    int i=low-1;
    for(int j=low;j<high;j++){
        if(data[j]<=pivot){
            i++;
            swap(data[i],data[j]);
        }
    }
    swap(data[i+1],data[high]);
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    if(low<high){
        int middle1=(low+high)/2;
        int middle2=middle1+1;
        MergeSortSubVector(data,low,middle1);
        MergeSortSubVector(data,middle2,high);
        Merge(data,low,middle1,middle2,high);
    }
    // Hint : recursively call itself
    //        Merge function is needed
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int left=low;
    int right=middle2;
    int temp[high-low+1];
    int i=0;
    while(left<=middle1&&right<=high){
        if(data[left]<=data[right]){
            temp[i]=data[left];
            left++;
        }
        else{
            temp[i]=data[right];
            right++;
        }
        i++;
    }
    while(left<=middle1){
        temp[i]=data[left];
        left++;
        i++;
    }
    while(right<=high){
        temp[i]=data[right];
        right++;
        i++;
    }
    for(int j=0;j<high-low+1;j++){
        data[low+j]=temp[j];
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
    int left=2*root+1; //注意 根節點的index是0，所以左子節點是2*root+1
    int right=2*root+2; //右子節點是2*root+2
    int largest=root;  //先假設root是最大的
    //找出root、left、right中最大的
    if(left<heapSize&&data[left]>data[largest]){
        largest=left;
    }
    if(right<heapSize&&data[right]>data[largest]){
        largest=right;
    }
    if(largest!=root){
        swap(data[root],data[largest]);
        MaxHeapify(data,largest);
    }

}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=data.size()/2-1;i>=0;i--){  //從最後一個有子節點的開始。注意 根節點的index是0。由下往上建立max heap
        MaxHeapify(data,i);
    }
}
