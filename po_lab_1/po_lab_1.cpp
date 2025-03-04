#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Функція для заповнення матриці випадковими числами
void fillMatrix(vector<vector<int>>& matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = rand() % 100; // Генерація чисел від 0 до 99
		}
	}
}

// Функція для обчислення сум рядків і встановлення значень головної діагоналі
void computeDiagonalSums(vector<vector<int>>& matrix, int size) {
	for (int i = 0; i < size; ++i) {
		int sum = 0;
		for (int j = 0; j < size; ++j) {
			sum += matrix[i][j];
		}
		matrix[i][i] = sum; // Записуємо суму на головну діагональ
	}
}

int main() {
	srand(time(0)); // Ініціалізація генератора випадкових чисел

	int size;
	cout << "Enter matrix size: ";
	cin >> size;

	vector<vector<int>> matrix(size, vector<int>(size));

	auto start = chrono::high_resolution_clock::now();

	fillMatrix(matrix, size);
	computeDiagonalSums(matrix, size);

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;

	cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;

	return 0;
}
