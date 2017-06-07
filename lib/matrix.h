//
// Created by maddjone on 4/19/17.
//

#ifndef ZZBRAIN_MATRIX_H
#define ZZBRAIN_MATRIX_H
void mult(double* M1, double* M2, int n, int m, int k, double *mRes);
void mult(double* M, double cst, int n, int m, double *mRes);
void sum(double* M1, double* M2, int n, int m, double *mRes);
void trans(double* M, int n, int m, double *mRes);
void diff(double * M1, double *M2, int n, int m, double *mRes);
void eltMult(double * M1, double * M2, int n, int m, double *mRes);
void ones(int n, double *mRes);
void print(double * M, int n, int m);
#endif //ZZBRAIN_MATRIX_H
