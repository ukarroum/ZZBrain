#ifndef ZZBRAIN_ZZNETWORK_H
#define ZZBRAIN_ZZNETWORK_H
#define DEFAULT_NB_OF_LAYERS 3

struct interLayers {
    int nbNodesLayer1;
    int nbNodesLayer2;
    double *weights;
};
typedef struct interLayers interLayers;

class ZZNetwork {

public:
    ZZNetwork(int sizes[], int nbLayers);

    operator bool() const {
        return network;
    }
    void train(int **trainingSet, int setSize);
    //void train(double **trainingSet, int nbFeatures, int setSize);
    int * predict(int *input);
    //Test function

public:
    int nbLayers;
    interLayers *network;
};


#endif //ZZBRAIN_ZZNETWORK_H
