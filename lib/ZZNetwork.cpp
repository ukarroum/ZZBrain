#include "ZZNetwork.h"
#include <ctime>
#include <cstdlib>

ZZNetwork::ZZNetwork(int sizes[], int nbLayers){
    this->nbLayers = nbLayers;
    network = new interLayers[nbLayers - 1];

    if(network) {
        int i = 0;
        do {
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

double *ZZNetwork::predict(int *input) {

}
