#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>


using namespace std;
const int maxRows = 1000;
const int maxColumns = 1000;


int main() {
	setlocale(LC_ALL, "Russian");
	// ������� ����������
	double arrayA[maxRows][maxColumns]{};
	int aRows, aCols;
	double arrayB[maxRows][maxColumns]{};
	int bRows, bCols;
	double arrayC[maxRows][maxColumns]{};
	int cRows, cCols;

	//���������� ��� ����������������� �����.
	int userChoice = 1;


	// ��������� ����������
	double specialArray[maxRows][maxColumns];
	int specRows, specCols;
	bool is_ArrA_Filled = false;
	bool is_ArrB_Filled = false;
	bool is_ArrC_Filled = false;

	while (userChoice != 0) { // ������� ����-����.
		cin >> userChoice;
		switch (userChoice) {
		case 1:  // ���������� 1�� �������
			arrFillingHub(*arrayA, aRows, aCols, is_ArrA_Filled, userChoice);
			break;
		case 2:  // ���������� 2�� �������
			arrFillingHub(*arrayB, bRows, bCols, is_ArrB_Filled, userChoice);
			break;
		case 3:  // ���������� 3�� �������
			arrFillingHub(*arrayC, cRows, cCols, is_ArrC_Filled, userChoice);
			break;
		default:
			cout << "� �� ������� ���, ��������� ����\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
			break;
		}
	}
	return 0;
}


void arrFillingHub(double* arr, int& rows, int& columns, bool& filledSignal, int arrNumber) {
	int typeOfFilling;

	cout << " === ���������� " << arrNumber << "�� ������� === "
		"������� ������ ������� � ������� MxN,"
		"��� M - ��� - �� �����, N - ��� - �� ��������\n"
		"(������ �������� �� ������ ��������� 1000";
	cout << "�����: ";
	rows = correctInputSizes();
	cout << "��������: ";
	columns = correctInputSizes();
	cout << "�������� ��� ����������:\n"
		"������� 1, ����� ��������� ������ ����. �������,\n"
		"������� 2, ����� ��������� ������� � ����������.\n"
		"��� �����: ";
	cin >> typeOfFilling;
	if (typeOfFilling == 1 || typeOfFilling == 2) {
		fillArray(arr, rows, columns, typeOfFilling);
		filledSignal = true;
	}
	else {
		cout << "������! ���������� ����: 1 ��� 2.\n";
	}
	system("pause");
}


int correctInputSizes() {
	int inputValue;
	while (!(cin >> inputValue) || inputValue > 1000 || inputValue < 1) {
		cout << "������! �� �������� ���������� ����. ������� ��������� ��������: \n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return inputValue;
}


void fillArray(double* array, int rows, int columns, int generateType) {
	if (generateType == 1) {
		randomFilling(array, rows, columns);
	}
	else {
		keyboardFilling(array, rows, columns);
	}
}


double getRandomNumber(int min, int max) {
	srand(time(0));
	return (double)(rand()) / RAND_MAX * (max - min) + min;
}


void randomFilling(double* array, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			array[i * rows + columns] = getRandomNumber(-1000, 1000);
		}
	}
}


void keyboardFilling(double* array, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cin >> array[i * rows + columns];
		}
	}
}


void printArrays(double* a1, double* a2, double* a3, int r1, int c1, int r2, int c2, int r3, int c3, bool f1, bool f2, bool f3) {
	int maxR = max(r1, r2, r3);
	int maxC = max(c1, c2, c3);
	for (int i = 0; i < maxR + 1; i++) {
		for (int j = 0; j <= 3 * maxC + 1; j++) {
			if (i == 0 || i == maxR + 1) {
				cout << "=";
			}
			else {
				if (j < maxC) {
					if (c1 < maxC && ) {
						cout << a1[i * c1 + j] << " ";
					}
					else {
						cout << "* ";
					}
				}
				if (j == maxC) {
					cout << " ";
				}
				if (j > maxC && j <= 2 * maxC) {
					if (j <= c2 && f1) {
						cout << a2[i * c2 + j] << " ";
					}
					else {
						cout << "* ";
					}
				}
				if (j == 2 * maxC + 1) {
					cout << " ";
				}
				if (j > 2 * maxC + 1) {
					if (j <= 2 * maxC + c3 && f1) {
						cout << a3[i * c3 + j] << " ";
					}
					else {
						cout << "* ";
					}
				}
			}

		}
	}




}
