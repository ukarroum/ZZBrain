//
// Created by maddjone on 4/19/17.
//

double * mult(double* M1, double* M2, int n, int m, int k){
    double mRes = new double[(n*k)]();
    for (int i = 0; i < n; i+k) {
        for (int j = 0; j < k; ++j){
            for (int q = 0; q < m; ++q){
                mRes[(i*m)+j]+=M1[i*m+q]*M2[(q*k)+j];
            }
        }
    }
    return mRes;
}

void print(double * M, int n, int m){
    for (int i = 0; i < n*m; ++i){
        cout << "| "<< M[i];
    }
}
