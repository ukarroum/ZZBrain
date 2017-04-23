//
// Created by maddjone on 4/19/17.
//

double * mult(double* M1, double* M2, int n, int m, int k){
    double * mRes = new double[(n*k)]();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; ++j){
            for (int q = 0; q < m; ++q){
                mRes[(i*k)+j]+=M1[i*m+q]*M2[(q*k)+j];
            }
        }
    }
    return mRes;
}


double * sum(double* M1, double* M2, int n, int m){
    double * mRes = new double[(n*m)]();
    for (int i = 0; i < n*m; ++i){
        mRes[i]=M1[i]+M2[i];
    }
    return mRes;
}


double * trans(double* M, int n, int m){
    double * mRes = new double[(n*m)]();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mRes[(i*m)+j]=M[(j*n)+i];
        }
    }
    return mRes;
}


void print(double * M, int n, int m){
    for (int i = 0; i < n*m; ++i){
        cout << "| "<< M[i];
    }
    cout << endl;
}
