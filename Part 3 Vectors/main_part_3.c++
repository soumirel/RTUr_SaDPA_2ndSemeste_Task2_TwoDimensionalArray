#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

struct point {
	int x, y;
};

struct edgesInfo {
	vector<point> pointInfo{};
	int intersections = 0;
};

struct triangleInfo {
	vector<point> triagnle{};
	int intersections;
};

void printMenu(vector<vector<int>>& vec);
int correctInputSizes();
void fillVector(vector<vector<int>>& vec, int size, bool isClear);
void printVector(vector<vector<int>>& vec);
bool isIntersect(point A, point B, point C, point D);
int findTriangleArea(point A, point B, point C);
bool isBoundingBox(int с1, int с2, int с3, int с4);
void findAllEdges(vector<vector<int>>& points, vector<vector<point>>& edges);
void findAllIntersections(vector<vector<point>>& edges, vector<edgesInfo>& edges_info);
bool isCoordsEqs(point c1, point c2);
triangleInfo findNeededTriangle(vector<vector<int>>& points, vector<vector<point>>& edges, vector<edgesInfo>& edges_info);
void printTriangle(triangleInfo answer);
bool isSameEdge(point A, point B, point C, point D);


int main() {
	setlocale(LC_ALL, "Russian");
	// Главные переменные
	vector<vector<int>>  points{};
	int numOfPoints;
	//Переменные для пользовательского ввода.
	int userChoice = -1;
	bool userIsClear;
	// Служебные переменные
	vector<vector<point>> edges{};
	vector<edgesInfo> edges_info{};
	triangleInfo answer;

	while (userChoice != 0) { // Главный меню-цикл.
		system("cls");
		printMenu(points);
		cin >> userChoice;
		switch (userChoice) {
		case 1:
			if (!points.empty()) {
				cout << "Вы хотите ввести точки заново или добавить к уже введённым?\n"
					"Чтобы продолжить заполнение - введите 0\n"
					"Чтобы ввести точки заново - введите 1\n"
					"Ваш выбор: ";
				cin >> userIsClear;
			}
			else {
				userIsClear = 1;
			}
			cout << "Введите количество задаваемых точек (натуральное число): ";
			numOfPoints = correctInputSizes();
			cout << "Введите " << numOfPoints * 2 <<  " целочисленных(ую) координат(у) точек в системе oXY (каждые два значения - одна точка)\n";
			fillVector(points, numOfPoints, userIsClear);
			system("pause");
			break;
		case 2:
			answer = findNeededTriangle(points, edges, edges_info);
			if (!(answer.triagnle).empty()) {
				cout << "\nКоординаты треугольника, удовлетворяющего условию:\n"
					"Его стороны пересекаются с максимальным количеством других треугольников.\n";
				printTriangle(answer);
			}
			else {
				cout << "Невозможно найти ответ. :(\n";
			}
			system("pause");
			break;
		case 0:
			cout << "До свидания!\n";
			userChoice = 0;
			system("pause");
			break;
		default:
			cout << "Я не понимаю вас, повторите ввод\n";
			cin.clear();
			system("pause");
			break;
		}
	}
}


void printMenu(vector<vector<int>>& vec) {
	cout << "Практическая работа #2 ИКБО-03-21 Мазанов А.Е. Вариант 17\n\n"
		"Задание 3 - Вектор\n"
		"================Меню================\n";
	if (!vec.empty()) {
		cout << "\nЗаданы точки на плоскости:\n";
		printVector(vec);
		cout << "\n";
	}
	else {
		cout << "\nВектор пуст\n\n";
	}
	cout << "1) Задать точки на плоскости. \n"
		"2) Найти такой треугольник, что его стороны пересекаются с максимальным количеством других треугольников.\n"
		"0) Выход.\n"
		"Ваш выбор: ";
}


int correctInputSizes() {
	int inputValue;
	while (!(cin >> inputValue) || inputValue < 1) {
		cout << "Ошибка! Вы нарушили допустимый ввод. Введите коректное значение: \n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return inputValue;
}


void fillVector(vector<vector<int>>& vec, int size, bool isClear) {
	if (isClear) {
		vec.clear();
	}
	int tempPoint;
	for (int i = 0; i < size; i++){
		vector <int> tempVec;
		for (int j = 0; j < 2; j++){
			cin >> tempPoint;
			tempVec.push_back(tempPoint);
		}
		vec.push_back(tempVec);
	}
}


void printTriangle(triangleInfo answer) {
	for (int i = -1; i < 3; i++) {
		for (int j = -1; j < 3; j++) {
			if (i == -1 || i == 2) {
				cout << setw(5) << setfill('-') << "-";
			}
			else {
				if (j == -1) {
					if (i == 0) {
						cout << "X: ";
					}
					else if (i == 1) {
						cout << "Y: ";
					}
				}
				else {
					if (i == 0) {
						cout << setw(5) << setfill(' ') << (answer.triagnle[j].x);
					}
					else {
						cout << setw(5) << setfill(' ') << (answer.triagnle[j].y);
					}
				}
			}
		}
		cout << "\n";
	}
	cout << "Количество пересечений с отрезками у этого треугольника (включая общие точки): " << answer.intersections << "\n";
	cout << "Это наибольшее количество пересечений с отрезками\n"
		"Следовательно этот треугольник пересекается с макс-ным кол-вом других треугольников.\n\n";
}


void printVector(vector<vector<int>>& vec) {
	int size = vec.size();
	for (int i = -1; i < 3; i++){
		for (int j = -1; j < size; j++){
			if (i == -1 || i == 2) {
				cout << setw(6) << setfill('=') << "=";
			}
			else {
				if (j == -1) {
					if (i == 0) {
						cout << "X: ";
					}
					else {
						cout << "Y: ";
					}
				}
				else {
					cout << setw(5) << setfill(' ') << vec[j][i];
					cout << "|";
				}
			}
		}
		cout << "\n";
	}
}


bool isIntersect(point A, point B, point C, point D) {
	return isBoundingBox(A.x, B.x, C.x, D.x) &&
		isBoundingBox(A.y, B.y, C.y, D.y) &&
		findTriangleArea(A, B, C) * findTriangleArea(A, B, D) <= 0 &&
		findTriangleArea(C, D, A) * findTriangleArea(C, D, B) <= 0 &&
		(!isSameEdge(A, B, C, D));
}


int findTriangleArea(point A, point B, point C) {
	return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

bool isBoundingBox(int с1, int с2, int с3, int с4) {
	if (с1 > с2) {
		swap(с2, с1);
	}
	if (с3 > с4) {
		swap(с3, с4);
	}
	return (max(с1, с3) <= min(с2, с4));
}


bool isSameEdge(point A, point B, point C, point D) {
	if (A.x == C.x && A.y == C.y && B.x == D.x && B.y == D.y) {
		return true;
	}
	return false;
}


void findAllEdges(vector<vector<int>>& points, vector<vector<point>>& edges) {
	vector<point> tempVec{};
	for (int i = 0; i < points.size(); i++) {
		for (int j = i + 1; j < points.size(); j++){
			tempVec.clear();
			tempVec.push_back({ points[i][0], points[i][1] });
			tempVec.push_back({ points[j][0], points[j][1] });
			edges.push_back(tempVec);
		}
	}

}


void findAllIntersections(vector<vector<point>>& edges, vector<edgesInfo>& edges_info) {
	vector<point> tempEdge(2);
	int tempIntersections = 0;
	for (int i = 0; i < edges.size(); i++) {
		tempIntersections = 0;
		tempEdge.clear();
		tempEdge.push_back(edges[i][0]);
		tempEdge.push_back(edges[i][1]);
		for (int j = 0; j < edges.size(); j++){
			tempIntersections += isIntersect(tempEdge[0], tempEdge[1], edges[j][0], edges[j][1]);
		}
		edges_info.push_back({ tempEdge, tempIntersections });
	}
}


bool isCoordsEqs (point c1, point c2) {
	if (c1.x == c2.x && c1.y == c2.y) {
		return true;
	}
	return false;
}


triangleInfo findNeededTriangle(vector<vector<int>>& points, vector<vector<point>>& edges, vector<edgesInfo>& edges_info) {
	findAllEdges(points, edges);
	findAllIntersections(edges, edges_info);
	int tempIntersections = 0;
	int maxIntersections = 0;
	vector<point> neededTriangle;
	point samepoint;
	point anotherPoint1;
	point anotherPoint2;
	bool p0Eqp0, p0Eqp1, p1Eqp0, p1Eqp1;
	for (int i = 0; i < edges_info.size(); i++){
		for (int j = i + 1; j < edges_info.size(); j++){
			samepoint = {};
			p0Eqp0 = p0Eqp1 = p1Eqp0 = p1Eqp1 = false;
			for (int k = j + 1; k < edges_info.size(); k++){
				p0Eqp0 = isCoordsEqs((edges_info[i]).pointInfo[0], (edges_info[j]).pointInfo[0]);
				p0Eqp1 = isCoordsEqs((edges_info[i]).pointInfo[0], (edges_info[j]).pointInfo[1]);
				p1Eqp0 = isCoordsEqs((edges_info[i]).pointInfo[1], (edges_info[j]).pointInfo[0]);
				p1Eqp1 = isCoordsEqs((edges_info[i]).pointInfo[1], (edges_info[j]).pointInfo[1]);
				if (p0Eqp0 || p0Eqp1 || p1Eqp0 || p1Eqp1) {
					if (p0Eqp0) {
						samepoint = (edges_info[i]).pointInfo[0];
						anotherPoint1 = (edges_info[i]).pointInfo[1];
						anotherPoint2 = (edges_info[j]).pointInfo[1];
					}
					if (p0Eqp1) {
						samepoint = (edges_info[i]).pointInfo[0];
						anotherPoint1 = (edges_info[i]).pointInfo[1];
						anotherPoint2 = (edges_info[j]).pointInfo[0];
					}
					if (p1Eqp0) {
						samepoint = (edges_info[i]).pointInfo[1];
						anotherPoint1 = (edges_info[i]).pointInfo[0];
						anotherPoint2 = (edges_info[j]).pointInfo[1];
					}
					if (p1Eqp1) {
						samepoint = (edges_info[i]).pointInfo[1];
						anotherPoint1 = (edges_info[i]).pointInfo[0];
						anotherPoint2 = (edges_info[j]).pointInfo[0];
					}
					if (isCoordsEqs(samepoint, (edges_info[k]).pointInfo[0])) {
						tempIntersections = (edges_info[i]).intersections +
							(edges_info[j]).intersections +
							(edges_info[k]).intersections;
					}
					if (tempIntersections > maxIntersections) {
						maxIntersections = tempIntersections;
						neededTriangle.clear();
						neededTriangle.push_back(samepoint);
						neededTriangle.push_back(anotherPoint1);
						neededTriangle.push_back(anotherPoint2);
					}
				}	
			}
		}
	}
	return { neededTriangle, maxIntersections - 6};
}