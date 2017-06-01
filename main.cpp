#include <iostream>
#include "lib/ZZNetwork.h"
#include "test/test.h"

using namespace std;

int main() {

	int sizes[] = {1, 1};
	int nbLayers = 2;

	double **X = new double*[2];
	double **Y = new double*[2];

	for(int i = 0; i < 2; i++)
	{
		X[i] = new double[1];
		Y[i] = new double[1];
	}
	X[0][0] = 0.0;
	Y[0][0] = 1.0;

	X[1][0] = 1.0;
	Y[1][0] = 0.0;

	ZZNetwork notNet(sizes, nbLayers, 2, X, Y, 0.01);
	notNet.train();

	cout << "not(0)" << notNet.predict(X[0])[0] << endl;
	cout << "not(1)" << notNet.predict(X[1])[0] << endl;
/*
	int sizes[] = {2, 1};
	int nbLayers = 2;

	double **X = new double*[4];
	double **Y = new double*[4];

	for(int i = 0; i < 4; i++)
	{
		X[i] = new double[2];
		Y[i] = new double[1];
	}
	X[0][0] = 0.0;
	X[0][1] = 1.0;
	Y[0][0] = 0.0;

	X[1][0] = 1.0;
	X[1][1] = 0.0;
	Y[1][0] = 0.0;

	X[2][0] = 0.0;
	X[2][1] = 0.0;
	Y[2][0] = 0.0;

	X[3][0] = 1.0;
	X[3][1] = 1.0;
	Y[3][0] = 1.0;

	ZZNetwork andNet(sizes, nbLayers, 4, X, Y, 0.01);
	andNet.train();

*/
    return 0;

}
