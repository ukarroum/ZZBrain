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
		/*
		if(std::rand() % 2)
		{
			X[i][0] = 0.0;
			Y[i][0] = 1.0;
			xEq0++;
		}
		else
		{
			X[i][0] = 1.0;
			Y[i][0] = 0.0;
		}
		*/
	}


	/*
	for(int i = 0; i < 500; i++)
	{
		X[i][0] = 0.0;
		Y[i][0] = 1.0;
	}

	for(int i = 500; i < 1000; i++)
	{
		X[i][0] = 1.0;
		Y[i][0] = 0.0;
	}*/

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


	/*
	ZZNetwork notNet(sizes, nbLayers, 1000, X, Y, 0.001);
	notNet.train();

	cout << "not(0) = " << notNet.predict(X[0])[0] << endl;
	cout << "not(1) = " << notNet.predict(X[900])[0] << endl;
	*/

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
