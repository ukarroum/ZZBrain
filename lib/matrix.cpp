//
// Created by maddjone on 4/19/17.
//

#include <iostream>

using namespace std;

/* M1 (n * m) M2 (m * k) */
void mult(double* M1, double* M2, int n, int m, int k, double *mRes){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; ++j)
            for (int q = 0; q < m; ++q)
                mRes[(i*k)+j]+=M1[i*m+q]*M2[(q*k)+j];
}

void mult(double* M, double cst, int n, int m, double *mRes){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; ++j)
            mRes[(i*m)+j]+=cst*M[(i*m)+j];
}


void sum(double* M1, double* M2, int n, int m, double *mRes){
    for (int i = 0; i < n*m; ++i)
        mRes[i]=M1[i]+M2[i];
}


void trans(double* M, int n, int m, double *mRes){
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            mRes[(j*n)+i]=M[(i*m)+j];
}


void print(double * M, int n, int m){
    for (int i = 0; i < n*m; ++i)
        cout << "| "<< M[i];
    cout << endl;
}

void diff(double * M1, double *M2, int n, int m, double *mRes){
    	for (int i = 0; i < n; ++i)
        	for (int j = 0; j < m; ++j)
            	mRes[(i*m)+j]=M1[(i*m)+j]-M2[(i*m)+j];
}

void eltMult(double * M1, double * M2, int n, int m, double *mRes){
    	for (int i = 0; i < n; ++i)
        	for (int j = 0; j < m; ++j)
            	mRes[(i*m)+j]=M1[(i*m)+j]*M2[(i*m)+j];
}

void ones(int n, double *mRes){
    for(int i = 0; i < n; i++)
        mRes[i] = 1;
}
