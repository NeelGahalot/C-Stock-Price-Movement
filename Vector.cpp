#include <ostream>
#include "Vector.hpp"

using namespace std;

Vector operator+(Vector& V, Vector& W) {
    int d = (int)V.size();
    Vector U(d);

    for (int j = 0; j < d; j++) 
        U[j] = V[j] + W[j];

    return U;
}

Vector operator-(Vector& V, Vector& W) {
    int d = (int)V.size();
    Vector U(d);

    for (int j = 0; j < d; j++) 
        U[j] = V[j] - W[j];

    return U;
}

ostream& operator<<(ostream& out, Vector& V) {
    for (Vector::iterator itr = V.begin(); itr != V.end(); itr++)
        out << *itr << " ";

    out << endl;

    return out;
}
