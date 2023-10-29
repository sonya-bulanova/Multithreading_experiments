#include "Merge.h"

int make_thread = 2;

void merge(vector<int>&array, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;

    // создаем временные массивы

    std::vector<int> left(nl);
    std::vector<int> right(nr);

    // копируем данные во временные массивы
    for (int i = 0; i < nl; i++)
        left[i] = array[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = array[m + 1 + j];

    int i = 0, j = 0;
    int k = l;  // начало левой части

    while (i < nl && j < nr) {
        // записываем минимальные элементы обратно во входной массив
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        }
        else {
            array[k] = right[j];
            j++;
        }
        k++;
    }
    // записываем оставшиеся элементы левой части
    while (i < nl) {
        array[k] = left[i];
        i++;
        k++;
    }
    // записываем оставшиеся элементы правой части
    while (j < nr) {
        array[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& array, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        if (make_thread==2)
        {
            future<void> t1 = async(std::launch::async, mergeSort, std::ref(array), l, m); future<void> t2 = async(std::launch::async, mergeSort, std::ref(array), m + 1, r);
            t1.wait(); t2.wait();
            merge(array, l, m, r);
        }
        else if (make_thread == 1)
        {
            thread t1(mergeSort, std::ref(array), l, m);thread t2(mergeSort, std::ref(array), m + 1, r);t1.join();t2.join();
            merge(array, l, m, r);
        }
        else {
            mergeSort(array, l, m);
            mergeSort(array, m + 1, r);
            merge(array, l, m, r);
        };
    }
}