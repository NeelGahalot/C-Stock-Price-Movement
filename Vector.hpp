#pragma once
#include <vector>
#include <ostream>

using namespace std;

typedef vector<double> Vector;

Vector operator+(Vector& V, Vector& W);
Vector operator-(Vector& V, Vector& W);
ostream& operator<<(ostream& out, Vector& V);