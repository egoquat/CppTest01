//#include "CodingTestBFS01.h"
//
//int main()
//{
//    vvecs dots = { {0, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 0}, {1, 1, 1, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0, 1, 1} };
//    solution(dots);
//    std::cout << "Hello World!\n";
//}


#include <algorithm>

#include "AllSort.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <functional>

#include "Profiler.h"

using namespace std;

int GetRand(int min, int max, int except = -1)
{
    int num = except;
    while (num == except)
    {
        num = min + (rand() % (max - min + 1));
    }
    return num;
}

void Shuffle(int* nums, int n = 10)
{
    for (int t = 0; t < 10; ++t)
    {
        srand(time(nullptr));
        for (int i = 0; i < n; ++i)
        {
            int n01 = i, n02 = GetRand(0, n - 1, i);
            swap(nums[n01], nums[n02]);
        }
    }
}

void copyTo(int* to, int* from, int amount = sizeof(int) * 10)
{
    memcpy(to, from, amount);
}

bool IsOrdered(int* v, int n)
{
    bool isOrder = true;
    for (int i = 1; i < n; ++i)
    {
        if (v[i-1] > v[i])
        {
            isOrder = false;
            break;
        }
    }
    if (isOrder == false)
    {
        cout << "error, not ordered." << endl;
    }
    return isOrder;
}

int main()
{
    const int Cnt = 10;
    srand(time(nullptr));
    int rNums[Cnt], nums[Cnt];
    for (int i = 0; i < Cnt; ++i)
    {
        rNums[i] = GetRand(1, 1000);
    }
    
    Profiler prof;
    double elapsed;
    const int CntTest = 10000;

    struct SortResult
    {
        function<void(int*, int)> FSort = nullptr;
        string NameSort;
        double elapsed = 0;
    };

    SortResult* results = new SortResult[]
    {
        SortResult{ Sort::insertionSort, "insertionSort", 0 },
        SortResult{ Sort::selectionSort, "selectionSort", 0 },
        SortResult{ Sort::bubbleSort, "bubbleSort", 0 },
        SortResult{ Sort::mergeSort, "mergeSort", 0 },
        SortResult{ Sort::quickSort, "quickSort", 0 }
    };
    
    prof.start();
    for (int i = 0; i < CntTest; ++i)
    {
        copyTo(nums, rNums);
        Sort::insertionSort(nums, Cnt);
        IsOrdered(nums, Cnt);
    }
    elapsed = prof.stop();
    results[0].elapsed = elapsed;
    cout << "sort elapsed second : " << elapsed << "/insertionSort" << endl;
    
    prof.start();
    for (int i = 0; i < CntTest; ++i)
    {
        copyTo(nums, rNums);
        Sort::selectionSort(nums, Cnt);
        IsOrdered(nums, Cnt);
    }
    elapsed = prof.stop();
    results[1].elapsed = elapsed;
    cout << "sort elapsed second : " << elapsed << "/selectionSort" << endl;

    prof.start();
    for (int i = 0; i < CntTest; ++i)
    {
        copyTo(nums, rNums);
        Sort::bubbleSort(nums, Cnt);
        IsOrdered(nums, Cnt);
    }
    elapsed = prof.stop();
    results[2].elapsed = elapsed;
    cout << "sort elapsed second : " << elapsed << "/bubbleSort" << endl;

    prof.start();
    for (int i = 0; i < CntTest; ++i)
    {
        copyTo(nums, rNums);
        Sort::mergeSort(nums, Cnt);
        IsOrdered(nums, Cnt);
    }
    elapsed = prof.stop();
    results[3].elapsed = elapsed;
    cout << "sort elapsed second : " << elapsed << "/mergeSort" << endl;

    prof.start();
    for (int i = 0; i < CntTest; ++i)
    {
        copyTo(nums, rNums);
        Sort::quickSort(nums, Cnt);
        IsOrdered(nums, Cnt);
    }
    elapsed = prof.stop();
    results[4].elapsed = elapsed;
    cout << "sort elapsed second : " << elapsed << "/quickSort" << endl;

    sort(results, results + 4, [](const SortResult& a, const SortResult& b)
    {
        return a.elapsed < b.elapsed;
    });
    
    cout << "items 10, 5 sort, fastest sort: " << results[0].NameSort << endl;

    cout << "" << endl;

    results[0].FSort(nums, Cnt);
    cout << "---- end." << endl;

    delete[] results;
}