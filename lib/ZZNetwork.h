#ifndef ZZBRAIN_ZZNETWORK_H
#define ZZBRAIN_ZZNETWORK_H

struct interLayers {
    int nbNodesLayer1;
    int nbNodesLayer2;
    double *weights;
};
typedef struct interLayers interLayers;

class ZZNetwork {

    ZZNetwork(int inputSize, int outputSize = 1);
    ZZNetowrk(int sizes[], int nbLayers);

    //void train();
    //Predict function
    //Test function

    int nbLayers;
    interLayers *network;
};


#endif //ZZBRAIN_ZZNETWORK_H
