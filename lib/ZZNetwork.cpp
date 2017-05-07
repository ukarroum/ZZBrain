#include "ZZNetwork.h"
#include "misc.h"
#include "matrix.h"
#include <ctime>
#include <cstdlib>
#include <cstring>

ZZNetwork::ZZNetwork(int sizes[], int nbLayers){
    this->nbLayers = nbLayers;
    maxNodes = sizes[0];
    trained = false;
    network = new interLayers[nbLayers - 1];

    if(network) {
        int i = 0;
        do {
            if(maxNodes < sizes[i])
                maxNodes = sizes[i];
            network[i].nbNodesLayer1 = sizes[i];
            network[i].nbNodesLayer2 = sizes[i + 1];
            network[i].weights = new double[network[i].nbNodesLayer1 * network[i].nbNodesLayer2];

            if(network[i].weights)
                for(int j = 0; j < network[i].nbNodesLayer1 * network[i].nbNodesLayer2; j++)
                    network[i].weights[j] = rand();
            i++;
        }while(i < nbLayers - 1 && network[i - 1].weights);

        if(!network[i - 1].weights) {
            for(int j = i - 2; j >= 0; j++)
                delete[] network[j].weights;
            delete[] network;
        }
    }
}

ZZNetwork::~ZZNetwork() {
    for(int i = 0; i < nbLayers - 1; i++)
        delete[] network[i].weights;
    delete[] network;
}

void train(int **input, int **output, int setSize){
    double ***bigDelta = new double**[nbLayers];
    double **a = new double*[nbLayers];
    double **err = new double*[nbLayers];
    double *z;

    if(a && err && bigDelta){
        for(int i = 0; i < nbLayers; i++){
            a[i] = new double[maxNodes];
            err[i] = new double[maxNodes];

            bigDelta[i] = new double*[maxNodes];
            for(int j = 0; j < maxNodes; j++){
                bigDelta[i][j] = new double[maxNodes];
            }
        }

        for(int i = 0; i < setSize; i++) {
            //Forward Propagation
            memcpy(a[0], input[i], network[0].nbNodesLayer1);
            for (int l = 0; l < nbLayers - 2; l++) {
                for (int k = 0; k < network[l].nbNodesLayer2; k++) {
                    z = mult(network[l].weights, a[l], network[l].nbNodesLayer2, network[l].nbNodesLayer1, 1);
                    a[l + 1] = sigmoid(z, network[l].nbNodesLayer2, 1);
                    delete[] z;
                }
            }

            err[nbLayers - 1] = diff(a[nbLayers - 1], output[i], network[nbLayers - 2].nbNodesLayer2, 1);
            for(int l = nbLayers - 2; l > 1; l--){
                err[l] = eltMul(mul(trans(network[l].weights), err[l + 1], network[l].nbNodesLayer1, network[l].nbNodesLayer2, network[l + 1].nbNodesLayers2), eltMul(a[l], diff(ones(network[l + 1].nbNodesLayers2), a[l], network[l + 1].nbNodesLayers2), 1), network[l + 1].nbNodesLayers2, 1);
            }


        }
    }


}
double *ZZNetwork::predict(int *input) {
    double *a = new double[maxNodes];
    double *z;

    if(a) {
        memcpy(a, input, network[0].nbNodesLayer1);
        for (int i = 0; i < nbLayers - 1; i++) {
            for (int j = 0; j < network[i].nbNodesLayer2; j++) {
                z = mult(network[i].weights, a, network[i].nbNodesLayer2, network[i].nbNodesLayer1, 1);
                a = sigmoid(z, network[i].nbNodesLayer2, 1);
                delete[] z;
            }
        }
    }

    return a;
}
