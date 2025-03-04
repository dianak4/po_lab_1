#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// ������� ��� ���������� ������� ����������� �������
void fillMatrix(vector<vector<int>>& matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = rand() % 100; // ��������� ����� �� 0 �� 99
		}
	}
}

// ������� ��� ���������� ��� ����� � ������������ ������� ������� �������
void computeDiagonalSums(vector<vector<int>>& matrix, int size) {
	for (int i = 0; i < size; ++i) {
		int sum = 0;
		for (int j = 0; j < size; ++j) {
			sum += matrix[i][j];
		}
		matrix[i][i] = sum; // �������� ���� �� ������� ��������
	}
}

int main() {
	srand(time(0)); // ����������� ���������� ���������� �����

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
