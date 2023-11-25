#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Node.h"

class Polynomial
{
public:
    Polynomial();
    ~Polynomial();

    void readFromFile(const char *filename);
    void outputPoly();
    double calcPoly(double x);
    static Polynomial *addPoly(Polynomial &poly1, Polynomial &poly2);
    static Polynomial *subPoly(Polynomial &poly1, Polynomial &poly2);

private:
    void insertTerm(int coef, int exp);
    static double calcExp(double x, int exp);

private:
    Node *_head;
};

#endif // POLYNOMIAL_H