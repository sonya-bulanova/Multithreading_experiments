#include "Merge.h"

int main() {
    
    srand(0);//начальное значение генератора числе
    long arr_size = 400;
    vector<int>array_2(arr_size);
    for (long i = 0; i < arr_size; i++) {
        array_2[i] = rand() % 50;
    }
    //cout << "make_thread - future:" << make_thread << endl;
    unsigned int start_time = clock();// начальное время
    mergeSort(array_2, 0, arr_size - 1);
    unsigned int end_time = clock(); // конечное время
    std::cout << std::endl << "Time if make_thread = future: " << end_time - start_time << endl;
    //for (int x : array) {std::cout << x << " ";};
    //thread
    make_thread = 1;

    srand(0);
    //cout << "make_thread - thread:"<<make_thread << endl;
    vector<int>array_1(arr_size);
    for (long i = 0; i < arr_size; i++) {
        array_1[i] = rand() % 50;
    }
    start_time = clock();// начальное время
    mergeSort(array_1, 0, arr_size - 1);
    end_time = clock(); // конечное время
    std::cout << std::endl << "Time if make_thread = thread: " << end_time - start_time << endl; // искомое время

    make_thread = 0;

    srand(0);
    //cout << "make_thread - main:" << make_thread << endl;
    vector<int>array_0(arr_size);
    for (long i = 0; i < arr_size; i++) {
        array_0[i] = rand() % 50;
    }
    start_time = clock();// начальное время
    mergeSort(array_0, 0, arr_size - 1);
    end_time = clock(); // конечное время
    std::cout << std::endl << "Time if make_thread = main: " << end_time - start_time << endl; // искомое время
    return 0;
}