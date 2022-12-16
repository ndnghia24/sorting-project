#include "sortingAlgorithms.h"

void selection_sort(int* arr, int n, unsigned long long& comp_count) {
    //comp_count = 0;

    for (int i = 0; ++comp_count && i < n; i++) {
        // Finding the milimum value in the unsorted array
        int temp_min = i;
        for (int j = i + 1; ++comp_count && j < n; j++) {
            if (++comp_count && arr[j] < arr[temp_min])
                temp_min = j;

        }
        // check if the milimum value in the unsorted array is smaller or bigger than ith element
        // if bigger do nothing 
        // else swap ith element with the smallest value in unsorted array
        if (++comp_count && i != temp_min)
            swap(arr[i], arr[temp_min]);
    }
}


void insertion_sort(int* arr, int n, unsigned long long& comp_count) {
    comp_count = 0;
    int key, j;
    for (int i = 1; ++comp_count && i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while ((++comp_count && j >= 0) && (++comp_count && arr[j] > key))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void bubble_sort(int* arr, int n, unsigned long long& comp_count) {
    comp_count = 0; // counting number of comparisons
    for (int i = n - 1; ++comp_count && i > 0; i--) {
        // Move the Biggest Element to last position
        for (int j = 0; ++comp_count && j < i; j++)
            if (++comp_count && arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    }
}


void RebuidHeap(int a[], int n, int pos, unsigned long long& comp_count)
{
    bool isHeap = false;
    int k = pos, i;
    while (!isHeap && (++comp_count && 2 * k + 1 < n))
    {
        i = 2 * k + 1;
        if ((++comp_count && i + 1 < n) && (++comp_count && a[i + 1] > a[i]))
            i++;
        if (++comp_count && a[k] >= a[i])
            isHeap = true;
        else
        {
            swap(a[k], a[i]);
            k = i;
        }
    }
}
void ConstrucHeap(int a[], int n, unsigned long long& comp_count)
{
    int i = n / 2 - 1;
    while (++comp_count && i >= 0)
    {
        RebuidHeap(a, n, i, comp_count);
        i--;
    }
}
void heap_sort(int* arr, int n, unsigned long long& comp_count) {
    comp_count = 0;
    ConstrucHeap(arr, n, comp_count);
    int r = n - 1;
    while (++comp_count && r > 0)
    {
        swap(arr[r], arr[0]);
        RebuidHeap(arr, r, 0, comp_count);
        r--;
    }
}


void merge(int a[], int b[], int na, int nb, int ans[], unsigned long long& comp_count)
{
    int i = 0, j = 0, k = 0;
    int* c = new int[na + nb];
    while ((++comp_count && i < na) && (++comp_count && j < nb))
    {
        if (++comp_count && a[i] < b[j])
        {
            c[k++] = a[i++];
        }
        else
        {
            c[k++] = b[j++];
        }
    }

    while (++comp_count && i < na)
    {
        c[k++] = a[i++];
    }

    while (++comp_count && j < nb)
    {
        c[k++] = b[j++];
    }
    for (int i = 0; ++comp_count && i < k; i++)
    {
        ans[i] = c[i];
    }
    delete[] c;
}
void merge_sort(int* arr, int n, unsigned long long& comp_count) {
    int mid = n / 2;
    if (++comp_count && mid != 0)
    {
        merge_sort(arr, mid, comp_count);
        merge_sort(&arr[mid], n - mid, comp_count);
        merge(arr, &arr[mid], mid, n - mid, arr, comp_count);
    }
}


int Partition(int* a, unsigned long long& comp_count, int low, int high) {

    // using the pivot is a random element between low and high

    int pivotIndex = rand() % (high - low) + low;
    swap(a[pivotIndex], a[low]);

    int index = low;
    // choose the pivot is the first element
    int pivot = low;
    for (int i = index; ++comp_count && i <= high; i++) {
        if (++comp_count && a[i] < a[low]) {
            index++;
            swap(a[i], a[index]);
        }
    }
    swap(a[index], a[pivot]);
    return index;
}
void quick_sort(int* arr, unsigned long long& comp_count, int low, int high) {

    if (++comp_count && low >= high) return;

    // the index of the pivot after partition
    int mid = Partition(arr, comp_count, low, high);

    // Recursion call to sort
    quick_sort(arr, comp_count, low, mid - 1);
    quick_sort(arr, comp_count, mid + 1, high);
}


int GetNumberofDigits_Largest(int* arr, int n, unsigned long long& comp_count) {
    // find max element
    int max = arr[0];
    for (int i = 0; ++comp_count && i < n; i++)
        if (++comp_count && abs(arr[i]) > max) {
            max = abs(arr[i]);
        }
    int result = 1;
    // find nummber is a power of 10 and the nearest larger of the max element in array 
    while (++comp_count && result / max == 0)
        result *= 10;
    // result 
    return result;
}
void radix_sort(int* arr, int n, unsigned long long& comp_count) {
    queue<int> DigitQueue[10];
    int digit = 1;
    int max = GetNumberofDigits_Largest(arr, n, comp_count);

    while (digit <= max) {
        // BASE: If all digits are sorting
        if (++comp_count && digit == max) {
            // Using stack and queue to detach positive and negative number
            stack<int> negative; // handle negative number
            queue<int> positive; // handle positive number

            // Array to stack and queue
            for (int i = 0; ++comp_count && i < n; i++)
                if (++comp_count && arr[i] >= 0)
                    positive.push(arr[i]);
                else
                    negative.push(arr[i]);

            // Stack and queue to Array
            int id_arr = 0;
            while (++comp_count && !negative.empty()) {
                arr[id_arr++] = negative.top(); negative.pop();
            }
            while (++comp_count && !positive.empty()) {
                arr[id_arr++] = positive.front(); positive.pop();
            }
            return; // stop radix-sorting
        }

        // Radix Sorting
        for (int i = 0; ++comp_count && i < n; i++) {
            // Give all elements of array to appropriate digits queue
            // Get index digits queue for each element
            int idQueue = abs(arr[i] / digit) % 10; // idQueue is the digit's value
            // Giving to digits queue
            DigitQueue[idQueue].push(arr[i]);
        }

        for (int idQueue = 0, idArr = 0; ++comp_count && idQueue < 10; idQueue++) { /* 10 la co so cua cac so trong mang*/
            // Return all elements from digits queue to Array
            while (++comp_count && !DigitQueue[idQueue].empty()) {
                arr[idArr++] = DigitQueue[idQueue].front();
                DigitQueue[idQueue].pop();
            }
        }
        // Radix sorting for next digits
        digit *= 10;
    }
}


void shaker_sort(int* arr, int n, unsigned long long& comp_count) {

    comp_count = 0; // counting number of comparisons
    int left = 0;       // left pointer 
    int right = n - 1;  // right pointer
    bool haveSwap;
    while (++comp_count&& left < right) {
        haveSwap = false;
        for (int i = left; ++comp_count && i < right; i++) {
            // Move Max element to right pointer
            if (++comp_count && arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                haveSwap = true;
            }
        }
        if (!haveSwap) return;
        right--; // move right pointer to right-1

        haveSwap = false;
        for (int i = right; ++comp_count && i > left; i--) {
            // Move min element to left pointer
            if (++comp_count && arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                haveSwap = true;
            }
        }
        if (!haveSwap) return;
        left++; // move left pointer to left+1
    }
}


void shell_sort(int* arr, int n, unsigned long long& comp_count) {

    for (int gap = n / 2; ++comp_count && gap >= 1; gap /= 2) {
        // Starting from the biggest gap
        for (int i = 0; ++comp_count && i < n; i++) {
            // for each element from i to n
            // move to its right postion for each gap value
            int temp = arr[i];
            int j = i;
            while ((++comp_count && j >= gap) && (++comp_count && arr[j - gap] > temp)) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}


void counting_sort(int* arr, int n, unsigned long long& comp_count) {

    //find max element to determine the size of count array
    int Maxval = arr[0];
    for (int i = 0; ++comp_count && i < n; i++)
    {
        if (++comp_count && arr[i] > Maxval)
            Maxval = arr[i];
    }

    //setup 
    int* count = new int[++Maxval]{ 0 };
    int* tempArr = new int[n];

    //store the amount of each element
    for (int i = 0; ++comp_count && i < n; i++)
    {
        count[arr[i]]++;
    }

    //the value of each element is the sum of itself and the previous element
    for (int i = 1; ++comp_count && i < Maxval; i++)
    {
        count[i] += count[i - 1];
    }

    // output to temporary array 
    for (int i = n - 1; ++comp_count && i >= 0; i--)
    {
        tempArr[--count[arr[i]]] = arr[i];
    }

    //copy to main array
    for (int i = 0; ++comp_count && i < n; i++)
    {
        arr[i] = tempArr[i];
    }

    //free memory
    delete[] tempArr;
    delete[] count;
}


void flash_sort(int* arr, int n, unsigned long long& comp_count) {
    //set up
#define getNum(x)  (m - 1) * (x - Minval) / (Maxval - Minval)

    int m = 0.45 * 1000;

    int* L = new int[m] {0};


    //classification
    //find max and min elemment
    int Minval = arr[0];
    int Maxval = arr[0];
    for (int i = 0; ++comp_count && i < n; i++)
    {
        if (++comp_count && arr[i] > Maxval)
            Maxval = arr[i];
        if (++comp_count && Minval > arr[i])
            Minval = arr[i];
    }

    for (int i = 0; ++comp_count && i < n; i++)
    {
        ++L[getNum(arr[i])];
    }

    for (int i = 1; ++comp_count && i < m; i++)
    {
        L[i] = L[i - 1] + L[i];
    }
    //permutation
    int count = 0;
    int i = 0;
    while (++comp_count && count < n)
    {
        int k = getNum(arr[i]);
        while (++comp_count && i >= L[k])
        {
            k = getNum(arr[++i]);
        }
        int ban_dau = arr[i];
        while (++comp_count && i != L[k])
        {
            k = getNum(ban_dau);

            int nho = arr[L[k] - 1];

            arr[--L[k]] = ban_dau;
            ban_dau = nho;

            count++;
        }
    }
    //insertion sort for each bucket
    for (int i = 1; ++comp_count && i < m; ++i)
    {
        for (int j = L[i] - 2; ++comp_count && j >= L[i - 1]; --j)
        {
            if (++comp_count && arr[j] > arr[j + 1]) {
                int temp = arr[j];
                int index = j;
                while (++comp_count && temp > arr[index + 1])
                {
                    arr[index] = arr[index + 1];
                    ++index;
                }
                arr[index] = temp;
            }
        }
    }

    delete[] L;
}