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

    void train(double **input, double **output, int setSize, double lambda=0.01);
    //void train(double **trainingSet, int nbFeatures, int setSize);
    double * predict(double *input);
    //Test function

    operator bool() const {
        return network;
    }

    ~ZZNetwork();

public:
    int nbLayers;
    int maxNodes;
    bool trained;
    interLayers *network;
};


#endif //ZZBRAIN_ZZNETWORK_H
