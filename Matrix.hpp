#pragma once
#include <vector>
#include <iostream>
#include "Vector.hpp"

using namespace std;

typedef vector<Vector> Matrix;

Vector operator*(const Matrix& C, const Vector& V);
Vector operator*(const double& a, const Vector& V);
Vector operator*(const Vector& V, const Vector& W);
Vector operator+(const double& a, const Vector& V);
Vector operator+(const Vector& V, const Vector& W);
Vector exp(const Vector& V);
double operator^(const Vector& V, const Vector& W);	// scalar operator
ostream& operator << (ostream& out, Matrix& W);		// Overload cout for Matrix
