#include <future>
#include <thread>
#include <vector>
#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;


extern int make_thread;
void merge(vector<int>& array, int l, int m, int r);
void mergeSort(vector<int>& array, int l, int r);
