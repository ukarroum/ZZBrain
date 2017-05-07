//
// Created by maddjone on 4/19/17.
//

#ifndef ZZBRAIN_MATRIX_H
#define ZZBRAIN_MATRIX_H
double * mult(double* M1, double* M2, int n, int m, int k);
double * sum(double* M1, double* M2, int n, int m);
double * trans(double* M, int n, int m);
void print(double * M, int n, int m);
#endif //ZZBRAIN_MATRIX_H
