#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

// Функція для заповнення матриці випадковими числами
void fillMatrix(vector<vector<int>>& matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = rand() % 100; // Генерація чисел від 0 до 99
		}
	}
}

// Функція для обчислення суми рядка та встановлення значення головної діагоналі
void computeRowSum(vector<vector<int>>& matrix, int row, int size) {
	int sum = 0;
	for (int j = 0; j < size; ++j) {
		sum += matrix[row][j];
	}
	matrix[row][row] = sum; // Записуємо суму на головну діагональ
}

// Функція для виводу матриці
void printMatrix(const vector<vector<int>>& matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

// Функція для запуску обчислень із заданою кількістю потоків
void runWithThreads(vector<vector<int>>& matrix, int size, int numThreads) {
	auto start = chrono::high_resolution_clock::now();

	vector<thread> threads;
	int rowsPerThread = max(1, size / numThreads);

	for (int i = 0; i < numThreads; ++i) {
		for (int j = i * rowsPerThread; j < min((i + 1) * rowsPerThread, size); ++j) {
			threads.emplace_back(computeRowSum, ref(matrix), j, size);
		}
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;

	cout << "Threads: " << numThreads << " | Elapsed time: " << elapsed.count() << " seconds" << endl;
}

int main() {
	srand(time(0)); // Ініціалізація генератора випадкових чисел

	int size;
	cout << "Enter matrix size: ";
	cin >> size;

	vector<vector<int>> matrix(size, vector<int>(size));
	fillMatrix(matrix, size);

	unsigned int physicalCores = thread::hardware_concurrency() / 2;
	unsigned int logicalCores = thread::hardware_concurrency();

	vector<int> threadCounts = { max(1, (int)physicalCores / 2), (int)physicalCores, (int)logicalCores,
								(int)logicalCores * 2, (int)logicalCores * 4, (int)logicalCores * 8, (int)logicalCores * 16 };

	for (int numThreads : threadCounts) {
		vector<vector<int>> tempMatrix = matrix; // Копіюємо вихідну матрицю
		runWithThreads(tempMatrix, size, numThreads);
	}

	return 0;
}
