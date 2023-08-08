#include <iostream>
#include <pthread.h>
#include <thread>
#include <vector>
#include <algorithm>

void ArraySum(int array[], int size, int & sum_sub){
  for (int i = 0; i < size; i++){
    sum_sub += array[i];
  }
  std::cout << sum_sub << std::endl;
}

int main() {
  srand (time(NULL));

  int size_of_array;
  std::cout << "Enter array size..." << std::endl;
  std::cin >> size_of_array;
  int parts;
  std::cout << "Enter number of threads..." << std::endl;
  std::cin >> parts;
  int small_arrays = (int)size_of_array / parts + 1; //кол-во элементов в массивах, которые будут передаваться потокам
  // +1 отвечает за то, что большой массив может иметь не кратное parts кол-во элементов

  std::cout << "Processing the array..." << std::endl;

  int ** user_array = new int * [parts];
  for (int i = 0; i < parts; i++){
    user_array[i] = new int [small_arrays];
    for (int j = 0; j < small_arrays; j++){
      if (i * small_arrays + j < size_of_array){
        user_array[i][j] = rand() % size_of_array + 1;
      } else {
        user_array[i][j] = 0;
      }
    }
  }

  for (int i = 0; i < parts; i++){
    for (int j = 0; j < small_arrays; j++){
      std::cout << user_array[i][j] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << "Processing multithreading..." << std::endl;
  int * sum_subarray = new int [parts]; //будем помещать вычисленные суммы в динамический массив
  std::vector<std::thread> threads; //вектор потоков
  for (int i = 0; i < parts; i++){
    std::thread thr(ArraySum, user_array[i], small_arrays, std::ref(sum_subarray[i]));
    threads.push_back(std::move(thr));
  }

  std::for_each(threads.begin(), threads.end(), [] (std::thread &t) { t.join(); }); //ждем все потоки

  int full_sum = 0; //вычисляем окончательное значение
  for (int i = 0; i < parts; i++){
    full_sum += sum_subarray[i];
  }

  std::cout << "Final result is: " << full_sum << std::endl;

  delete [] user_array;
  delete [] sum_subarray;
  return 0;
}
