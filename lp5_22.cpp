#include <iostream>
#include <omp.h>
using namespace std;
// function to perform sequential bubble sort
void bubbleSort(int arr[], int n) {
 int i, j, temp;
 for (i = 0; i < n-1; i++) {
 for (j = 0; j < n-i-1; j++) {
 if (arr[j] > arr[j+1]) {
 temp = arr[j];
 arr[j] = arr[j+1];
 arr[j+1] = temp;
 }
 }
 }
}
// function to perform parallel bubble sort using OpenMP
void parallelBubbleSort(int arr[], int n) {
 int i, j, temp;
 #pragma omp parallel for private(i, j, temp)
 for (i = 0; i < n-1; i++) {
 for (j = 0; j < n-i-1; j++) {
 if (arr[j] > arr[j+1]) {
 temp = arr[j];
 arr[j] = arr[j+1];
 arr[j+1] = temp;
 }
 }
 }
}
// function to merge two subarrays in ascending order
void merge(int arr[], int left, int mid, int right) {
 int i, j, k;
 int n1 = mid - left + 1;
 int n2 = right - mid;
 int L[n1], R[n2];
 for (i = 0; i < n1; i++) {
 L[i] = arr[left + i];
 }
 for (j = 0; j < n2; j++) {
 R[j] = arr[mid + 1 + j];
 }
 i = 0;
 j = 0;
 k = left;
 while (i < n1 && j < n2) {
 if (L[i] <= R[j]) {
 arr[k] = L[i];
 i++;
 }
 else {
 arr[k] = R[j];
 j++;
 }
 k++;
 }
 while (i < n1) {
 arr[k] = L[i];
 i++;
 k++;
 }
 while (j < n2) {
 arr[k] = R[j];
 j++;
 k++;
 }
}
// function to perform sequential merge sort
void mergeSort(int arr[], int left, int right) {
 if (left < right) {
 int mid = left + (right - left) / 2;
 mergeSort(arr, left, mid);
 mergeSort(arr, mid+1, right);
 merge(arr, left, mid, right);
 }
}
// function to perform parallel merge sort using OpenMP
void parallelMergeSort(int arr[], int left, int right, int num_threads) {
 if (left < right) {
 int mid = left + (right - left) / 2;
 #pragma omp parallel sections num_threads(2)
 {
 #pragma omp section
 {
 parallelMergeSort(arr, left, mid, num_threads/2);
 }
 #pragma omp section
 {
 parallelMergeSort(arr, mid+1, right, num_threads/2);
 }
 }
 merge(arr, left, mid, right);
 }
}
int main() {
 int n = 10;
 int arr[n];
 // initialize array with random values
 for (int i = 0; i < n; i++) {
        int a;
        cin>>a;
 arr[i] = a;
 }
 // copy array for parallel sorting
 int arr_copy[n];
 for (int i = 0; i < n; i++) {
 arr_copy[i] = arr[i];
 }
 // measure time for sequential bubble sort
 double start_time = omp_get_wtime();
 bubbleSort(arr, n);
 double end_time = omp_get_wtime();
 double sequential_bubble_time = end_time - start_time;
 // measure time for parallel bubble sort
 start_time = omp_get_wtime();
 parallelBubbleSort(arr_copy, n);
 end_time = omp_get_wtime();
 double parallel_bubble_time = end_time - start_time;
 // output results for bubble sort
 cout << "Bubble Sort Results:" << endl;
 cout << "Sequential Time: " << sequential_bubble_time << " seconds" << endl;
 cout << "Parallel Time: " << parallel_bubble_time << " seconds" << endl;
 // reset array for merge sort
 for (int i = 0; i < n; i++) {
        int a;
        cin>>a;
        arr[i] = a;
 }
 // copy array for parallel sorting
 for (int i = 0; i < n; i++) {
 arr_copy[i] = arr[i];
 }
 // measure time for sequential merge sort
 start_time = omp_get_wtime();
 mergeSort(arr, 0, n-1);
 end_time = omp_get_wtime();
 double sequential_merge_time = end_time - start_time;
 // measure time for parallel merge sort
 start_time = omp_get_wtime();
 #pragma omp parallel num_threads(4)
 {
 #pragma omp single
 {
 parallelMergeSort(arr_copy, 0, n-1, omp_get_num_threads());
 }
 }
 end_time = omp_get_wtime();
 double parallel_merge_time = end_time - start_time;
 // output results for merge sort
 cout <<endl << "Merge Sort Results:" << endl;
 cout << "Sequential Time: " << sequential_merge_time << " seconds" << endl;
 cout << "Parallel Time: " << parallel_merge_time << " seconds" << endl;
 return 0;
}
