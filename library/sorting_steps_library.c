#include "sorting_steps_library.h"

// Bubble Sort
double bubble_sort_steps(int arr[], int n)
{
    int tmp,
        i,
        j;
    double steps = 0;

    steps++; // i=1
    for (i = 1; i < n; i++)
    {
        steps += 3; // j=n-1, i<n, i++
        for (j = n - 1; j >= i; j--)
        {
            steps += 3; // j>=i, j--, if
            if (arr[j] < arr[j - 1])
            {
                steps += 3; // swap
                tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
            }
        }
        steps++; // j>=i false
    }
    steps++; // i<n false

    return steps;
}

// Selection Sort
double selection_sort_steps(int arr[], int n)
{
    int tmp,
        i,
        j,
        min_index;
    double steps = 0;

    steps++; // i=0
    for (i = 0; i < n - 1; i++)
    {
        min_index = i;
        steps += 3; // j=i+1, min_index=i, i++
        for (j = i + 1; j < n; j++)
        {
            steps += 3; // j<n, j++, if
            if (arr[j] < arr[min_index])
            {
                steps++; // min_index=j
                min_index = j;
            }
        }
        steps += 2; // j<n false, if
        if (min_index != i)
        {
            steps += 3; // swap
            tmp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = tmp;
        }
    }
    steps++; // i<n-1 false

    return steps;
}

// Insertion Sort
double insertion_sort_steps(int arr[], int n)
{
    int tmp,
        i,
        j;
    double steps = 0;

    steps++; // i=1
    for (i = 1; i < n; i++)
    {
        tmp = arr[i];
        j = i - 1;
        steps += 3; // tmp=arr[i], j=i-1, i++
        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j--;
            steps += 3; // j>=0 && arr[j]>tmp, j--, arr[j+1]=arr[j]
        }
        arr[j + 1] = tmp;
        steps += 2; // j
    }
    steps++;            // i<n false

    return steps;
}

// Merge Sort
double merge_sort_steps(int arr[], int l, int r)
{
    int m;
    double steps = 0;
    
    steps++;    // if
    if (l < r) {
        m = l + (r - l) / 2;
        steps ++; // m=l+(r-l)/2

        steps += merge_sort_steps(arr, l, m); // Left half
        steps += merge_sort_steps(arr, m + 1, r); // Right half
        steps += merge_steps(arr, l, m, r); // Merge
    }

    return steps;
}

double merge_steps(int arr[], int l, int m, int r)
{
    int i, j, k, n1, n2;
    double steps = 0;
    
    n1 = m - l + 1;
    n2 = r - m;
    int L[n1], R[n2];
    
    steps += 3;
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
        steps += 3; // L[i] = arr[l + i], i<n1, i++
    }
    steps++; // i<n1 false

    steps++;    // j=0
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
        steps += 3; // R[j] = arr[m + 1 + j], j < n2, j++
    }
    steps++; // j<n2 false

    i = 0;
    j = 0;
    k = l;
    steps += 3; // i=0, j=0, k=l

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
            steps += 3; // arr[k] = L[i], i++, if
        }
        else
        {
            arr[k] = R[j];
            j++;
            steps += 3; // arr[k] = R[j], j++, else
        }
        k++;
        steps++; // k++
    }
    steps++; // i<n1 || j<n2 false

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        steps += 4; // arr[k] = L[i], i++, k++
    }
    steps++; // i<n1 false

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        steps += 4; // arr[k] = R[j], j++, k++
    }
    steps++; // j<n2 false

    return steps;
}

// Quick Sort
double quick_sort_steps(int arr[], int low, int high) {
    int pi;
    double steps = 0;
    
    steps++; // if
    if (low < high) {
        pi = partition_steps(arr, low, high, &steps);
        steps++;
        steps += quick_sort_steps(arr, low, pi - 1); // Ricorsione per la parte sinistra
        steps += quick_sort_steps(arr, pi + 1, high); // Ricorsione per la parte destra
    }
    return steps;
}

int partition_steps(int arr[], int low, int high, double *steps) {
    int pivot, i, j, tmp;

    pivot = arr[high];
    i = low - 1;
    (*steps) += 3;
    for (j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            (*steps) += 5; // i++, swap
        }
        (*steps) += 3; // if, j++, j<=high-1
    }
    tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    (*steps) += 3; // swap
    return (i + 1);
}

// Heap Sort
void heapify_steps(int arr[], int n, int i, double *steps)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
    {
        largest = l;
        (*steps)++;
    }

    if (r < n && arr[r] > arr[largest])
    {
        largest = r;
        (*steps)++;
    }

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify_steps(arr, n, largest, steps);
        (*steps)++;
    }
}

double heap_sort_steps(int arr[], int n)
{
    double steps = 0;
    
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_steps(arr, n, i, &steps);

    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify_steps(arr, i, 0, &steps);
    }
    
    return steps;
}
