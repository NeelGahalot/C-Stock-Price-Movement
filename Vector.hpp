#pragma once
#include <vector>
#include <ostream>

using namespace std;

typedef vector<double> Vector;

Vector operator+(const Vector& V, const Vector& W);
Vector operator-(const Vector& V, const Vector& W);
Vector CalculateReturn(Vector V);
Vector CalculateCumReturn(Vector V);
ostream& operator<<(ostream& out, Vector& V);