#include <vector>

using namespace std;

namespace Sort
{
    // selectionSort
    void selectionSort(int* v, int n)
    {
        int minPosition;

        for (int i = 0; i < n - 1; i++)
        {
            minPosition = i;

            for (int j = i + 1; j < n; j++)
            {
                if (v[j] < v[minPosition])
                { 
                    minPosition = j;
                }
            }
        
            if (minPosition > i) { 
                swap(v[minPosition], v[i]);
            }
        }
    }

    // quickSort
    void quickSortInternal(int* v, int start, int end)
    {
        if(start >= end) return;

        int pivot = start;
        int i = start + 1;
        int j = end;
        int tmp;

        while (i <= j)
        {
            while (v[i] < v[pivot] && i <= end) i++;
            while (v[j] >= v[pivot] && j > start) j--;

            if (i >= j) break;

            tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }

        tmp = v[j];
        v[j] = v[pivot];
        v[pivot] = tmp;

        quickSortInternal(v, start, j - 1);
        quickSortInternal(v, j + 1, end);
    }

    void quickSort(int* v, int n)
    {
        int start = 0, end = n - 1;
        quickSortInternal(v, start, end);
    }

    // mergeSort
    void merge(int* v, int start, int mid, int end, int n)
    {
        vector <int> aux(n);
        int i = start;
        int j = mid + 1;
        int k = start;

        while (i <= mid && j <= end)
        {
            if (v[i] < v[j])
                aux[k] = v[i++];
            else
                aux[k] = v[j++];

            k++;
        }

        while (i <= mid)
        {
            aux[k] = v[i++];
            k++;
        }

        while (j <= end)
        {
            aux[k] = v[j++];
            k++;
        }

        for (int i = start; i <= end; i++)
        {
            v[i] = aux[i];
        }
    }

    void mergeSortInternal(int* v, int start, int end, int n)
    {
        if (start < end)
        {
            int m = (start + end) / 2;
            mergeSortInternal(v, start, m, n);
            mergeSortInternal(v, m + 1, end, n);
            merge(v, start, m, end, n);
        }
    }

    void mergeSort(int* v, int n)
    {
        int start = 0, end = n - 1;
        mergeSortInternal(v, start, end, n);
    }

    void insertionSort(int* v, int n)
    {
        int current, pos;

        for (int i = 1; i < n; i++)
        {
            current = v[i]; 
            pos = i;

            while (pos > 0 && v[pos - 1] > current)
            {
                v[pos] = v[pos - 1]; 
                pos--;
            }
		
            if (pos != i)  
                v[pos] = current; 
        }
    }

    void bubbleSort(int* v, int n)
    {
        bool swapped = true;
        int i = 0;

        while (i < n - 1 && swapped)
            {
            swapped = false;
		
            for (int j = n - 1; j > i; j--)
            {
                if (v[j] < v[j - 1]) {
                    swap(v[j], v[j - 1]);
                    swapped = true;
                }
            }
            i++;
        }
    }
}