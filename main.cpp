#include <iostream>
#include "lib/ZZNetwork.h"
#include "test/test.h"

using namespace std;

int main() {

	srand (time(NULL));
	int sizes[] = {2, 8, 8, 8, 1};
	int nbLayers = 4;
	int xEq0 = 0;
	double **X = new double*[1000];
	double **Y = new double*[1000];


	for(int i = 0; i < 1000; i++)
	{
		X[i] = new double[2];
		Y[i] = new double[2];
	}


	for(int i = 0; i < 250; i++)
	{
		X[i][0] = 0.0;
		X[i][1] = 1.0;
		Y[i][0] = 0.0;
	}

	for(int i = 250; i < 500; i++)
	{
		X[i][0] = 1.0;
		X[i][1] = 0.0;
		Y[i][0] = 0.0;
	}
	for(int i = 500; i < 750; i++)
	{
		X[i][0] = 0.0;
		X[i][1] = 0.0;
		Y[i][0] = 1.0;
	}

	for(int i = 750; i < 1000; i++)
	{
		X[i][0] = 1.0;
		X[i][1] = 1.0;
		Y[i][0] = 1.0;
	}



	ZZNetwork notNet(sizes, nbLayers, 1000, X, Y, 0.001);
	notNet.train();

	cout << "xnor(0, 1) = " << notNet.predict(X[0])[0] << endl;
	cout << "xnor(1, 0) = " << notNet.predict(X[300])[0] << endl;
	cout << "xnor(0, 0) = " << notNet.predict(X[600])[0] << endl;
	cout << "xnor(1, 1) = " << notNet.predict(X[900])[0] << endl;


    return 0;

}
