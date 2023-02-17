#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cmath>
using namespace std;

long long int C = 0, M = 0, depth = 0;

void PrintInfo(long long int e, double dur) {//вывод информиции
	if (e == 8) {
		cout << "сравнения: " << C << "\tперемещения: " << M << endl;
	}
	else if (e > 8) {
		long long int fэ_n, fа_n;
		fэ_n = C + M;
		if (M != 0) {
			fа_n = e * e;
		}
		else {
			fа_n = e;
		}
		double T_n = dur / 1000000000;
		cout << C << setw(18) << M << setw(18) << fэ_n << setw(18) << round(T_n * 10000) / 10000 << setw(18) << depth << endl;
		depth = 0;
		C = 0;
		M = 0;
	}
}

void merge(int arr[], int l, int mid, int r)//сортировка методом простого двухфазного двухпутевого слияния
{
	int i, j, k;
	int n1 = mid - l + 1;
	int n2 = r - mid;
	int* L = new int[n1];
	int* R = new int[n2];
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		C++;
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		M++;
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = R[j];
		M++;
		j++;
		k++;
	}
}

void MergeSort(int arr[], int l, int r)//слияние подмассивов
{
	depth++;
	if (l < r)
	{
		int mid = l + (r - l) / 2;
		MergeSort(arr, l, mid);
		MergeSort(arr, mid + 1, r);
		merge(arr, l, mid, r);
	}
}

void WorstSort(int* arr, int e)//обртаная сортировка
{
	int sv;
	for (int i = 0; i < e - 1; i++) {
		for (int j = i + 1; j < e; j++) {
			if (arr[i] < arr[j]) {
				sv = arr[i];
				arr[i] = arr[j];
				arr[j] = sv;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int question;
	int Myarr[8];
	int buf[8];
	srand(time(0));
	cout << "+-----------------------------------------------------------------------------------------------------------------+" << endl;
	cout << "|Мещеряков Андрей ИКБО-15-19                                                                                      |" << endl;
	cout << "|Практическая работа №3 Рекурсивный алгоритм сортировки массивов методом простого двухфазного двухпутевого слияния|" << endl;
	cout << "+-----------------------------------------------------------------------------------------------------------------+" << endl;
	cout << "ввод массива вручную (1)/автоматический ввод массива (2): ";
	cin >> question;
	if (question == 1) {
		cout << "введите массив:";
		for (int i = 0; i < 8; i++)
		{
			cout << "[" << i << "]= ";
			cin >> Myarr[i];
		}
		cout << "сортирвка методом простого двухфазного двухпутевого слияния: ";
		MergeSort(Myarr, 0 , 7);
		cout << "\nотсортированы массив: ";
		for (int i = 0; i < 8; i++) {
			cout << Myarr[i] << " ";
		}
		cout << endl;
		PrintInfo(8, 0);

	}
	else if (question == 2) {
		long long int e;
		for (e = 60000; e <= 100000; e += 10000) {
			int* Autoarr = new int[e];
			int* buf = new int[e];
			for (int i = 0; i < e; i++) {
				Autoarr[i] = rand();
			}
			cout << "___________________________________________________________________________________________________________________\n";
			cout << "n= " << e << setw(15) << "C" << setw(19) << "M" << setw(22) << "fэ(n)" << setw(18) << "T(n)" << setw(19) << "depth\n";
			cout << "-------------------------------------------------------------------------------------------------------------------\n";
			cout << "средний случай" << setw(15);
			auto start_time = chrono::high_resolution_clock::now();
			MergeSort(Autoarr, 0, e - 1);
			auto stop_time = chrono::high_resolution_clock::now();
			chrono::duration<double, nano> dur = stop_time - start_time;
			PrintInfo(e, dur.count());
			cout << "-------------------------------------------------------------------------------------------------------------------\n";
			cout << "наилучший случай" << setw(13);
			start_time = chrono::high_resolution_clock::now();
			MergeSort(Autoarr, 0, e - 1);
			stop_time = chrono::high_resolution_clock::now();
			dur = stop_time - start_time;
			PrintInfo(e, dur.count());
			cout << "-------------------------------------------------------------------------------------------------------------------\n";
			cout << "наихудший случай" << setw(13);
			WorstSort(Autoarr, e);
			start_time = chrono::high_resolution_clock::now();
			MergeSort(Autoarr, 0, e - 1);
			stop_time = chrono::high_resolution_clock::now();
			dur = stop_time - start_time;
			PrintInfo(e, dur.count());
		}
	}
}