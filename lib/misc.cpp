//
// Created by maddjone on 4/19/17.
//

#include <cmath>
#include "misc.h"

double sigmoid(double x){
    return 1/(1 + exp(-x));
}
double* sigmoid(double* M, int n, int m){

    double *res = new double[n * m];
    for(int i = 0; i < n*m; i++)
        res[i] = sigmoid(M[i]);
    return res;
}
