#include <iostream>
#include "../lib/ZZNetwork.h"
#include "test.h"

using namespace std;

void test(){
    /* Predict's test */
    cout << "Test of the Predict function" << endl;
    cout << "============================" << endl;

    test_predict();
}
void test_predict(){

    cout << "\tFunctions with no hidden layer" << endl;
    cout << "\t==============================" << endl;
    test_network_and();
    test_network_or();
    test_network_not();

    cout << "\tFunctions with 1 hidden layer" << endl;
    cout << "\t==============================" << endl;
    test_network_xnor();
}
void test_network_and(){
    int *sizes;
    int nbLayers;
    bool correct = true;

    double *X;
    double *Y;

    nbLayers = 2;
    sizes = new int[nbLayers];

    sizes[0] = 2;
    sizes[1] = 1;

    ZZNetwork andNet(sizes, nbLayers);

    andNet.network[0].weights[0] = -30.0;
    andNet.network[0].weights[1] = +20.0;
    andNet.network[0].weights[2] = +20.0;

    X = new double[sizes[0]];

    X[0] = 0.0;
    X[1] = 0.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] < 0.5;
    delete[] Y;

    X[0] = 0.0;
    X[1] = 1.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] < 0.5;
    delete[] Y;

    X[0] = 1.0;
    X[1] = 0.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] < 0.5;
    delete[] Y;

    X[0] = 1.0;
    X[1] = 1.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] > 0.5;
    delete[] Y;

    delete[] sizes;
    delete[] X;

    cout << "AND : ";

    if(correct)
        cout << "\033[1;32m" << "Working" << "\033[0m" << endl;
    else
        cout << "\033[1;31m" << "Not Working !" << "\033[0m" << endl;
}
void test_network_or(){
    int *sizes;
    int nbLayers;
    bool correct = true;

    double *X;
    double *Y;

    nbLayers = 2;
    sizes = new int[nbLayers];

    sizes[0] = 2;
    sizes[1] = 1;

    ZZNetwork andNet(sizes, nbLayers);

    andNet.network[0].weights[0] = -10.0;
    andNet.network[0].weights[1] = +20.0;
    andNet.network[0].weights[2] = +20.0;

    X = new double[sizes[0]];

    X[0] = 0.0;
    X[1] = 0.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] < 0.5;
    delete[] Y;

    X[0] = 0.0;
    X[1] = 1.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] > 0.5;
    delete[] Y;

    X[0] = 1.0;
    X[1] = 0.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] > 0.5;
    delete[] Y;

    X[0] = 1.0;
    X[1] = 1.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] > 0.5;
    delete[] Y;

    delete[] sizes;
    delete[] X;

    cout << "OR : ";

    if(correct)
        cout << "\033[1;32m" << "Working" << "\033[0m" << endl;
    else
        cout << "\033[1;31m" << "Not Working !" << "\033[0m" << endl;
}
void test_network_not(){
    int *sizes;
    int nbLayers;
    bool correct = true;

    double *X;
    double *Y;

    /* AND function */
    nbLayers = 2;
    sizes = new int[nbLayers];

    sizes[0] = 1;
    sizes[1] = 1;

    ZZNetwork andNet(sizes, nbLayers);

    andNet.network[0].weights[0] = +10.0;
    andNet.network[0].weights[1] = -20.0;

    X = new double[sizes[0]];

    X[0] = 0.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] > 0.5;
    delete[] Y;

    X[0] = 1.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] < 0.5;
    delete[] Y;

    delete[] sizes;
    delete[] X;

    cout << "NOT : ";

    if(correct)
        cout << "\033[1;32m" << "Working" << "\033[0m" << endl;
    else
        cout << "\033[1;31m" << "Not Working !" << "\033[0m" << endl;
}

void test_network_xnor(){
    int *sizes;
    int nbLayers;
    bool correct = true;

    double *X;
    double *Y;

    nbLayers = 3;
    sizes = new int[nbLayers];

    sizes[0] = 2;
    sizes[1] = 2;
    sizes[2] = 1;

    ZZNetwork andNet(sizes, nbLayers);

    andNet.network[0].weights[0] = -30.0;
    andNet.network[0].weights[1] = +20.0;
    andNet.network[0].weights[2] = +20.0;
    andNet.network[0].weights[3] = 10.0;
    andNet.network[0].weights[4] = -20.0;
    andNet.network[0].weights[5] = -20.0;

    andNet.network[1].weights[0] = -10.0;
    andNet.network[1].weights[1] = +20.0;
    andNet.network[1].weights[2] = +20.0;


    X = new double[sizes[0]];

    X[0] = 0.0;
    X[1] = 0.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] > 0.5;
    delete[] Y;

    X[0] = 0.0;
    X[1] = 1.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] < 0.5;
    delete[] Y;

    X[0] = 1.0;
    X[1] = 0.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] < 0.5;
    delete[] Y;

    X[0] = 1.0;
    X[1] = 1.0;
    Y = andNet.predict(X);
    correct = correct && Y[0] > 0.5;
    delete[] Y;

    delete[] sizes;
    delete[] X;

    cout << "XNOR : ";

    if(correct)
        cout << "\033[1;32m" << "Working" << "\033[0m" << endl;
    else
        cout << "\033[1;31m" << "Not Working !" << "\033[0m" << endl;
}

