#include <iostream>
#include "lib/ZZNetwork.h"

using namespace std;

int main() {

	/*
		Exemple d'utilisation du réseau pour un NOT 
	*/
	
	
	/*
 		1ere couche : Entrée (0 ou 1)
		2eme couche : Not(Entrée) (0 ou 1)
		Pas de hidden layer 
	*/
    int sizes[] = {1, 1};
    int nbLayers = 2;

	/* 
 * 		X	:	Entrée
 * 		Y	:	Résultat Attendu 
 *
 * 		X	Y
 * 		0	1
 * 		1	0
 * 		*/
    double **X = new double*[1];
    double **Y = new double*[1];

    for(int i = 0; i < 2; i++)
    {
        X[i] = new double[2];
        Y[i] = new double;
    }

    X[0][0] = 0.0;
    X[1][0] = 1.0;

    Y[0][0] = 1.0;
    Y[1][0] = 0.0;

    double *A;

	/* Initialisation du réseau (pour le moments les poids sont alétaroires) */
    ZZNetwork net(sizes, nbLayers);

    if(net){
        cout << "Created" << endl;
        cout << net.nbLayers << endl;
        for(int i = 0; i < nbLayers - 1; i++)
        {
            for(int j = 0; j < net.network[i].nbNodesLayer1*net.network[i].nbNodesLayer2; j++)
                cout << net.network[i].weights[j] << " ";
            cout << endl;
        }

        cout << "Training the network" << endl;
        cout << "====================" << endl;
        //net.network[0].weights[0] = 10.0;
        //net.network[0].weights[1] = -20.0;

        net.train(X, Y, 2);

        cout << "Predicting" << endl;
        A = net.predict(X[1]);
        cout << *A << endl;

    }
    else
        cout << "Too Bad" << endl;
    return 0;
}
