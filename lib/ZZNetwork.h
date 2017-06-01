#ifndef ZZBRAIN_ZZNETWORK_H
#define ZZBRAIN_ZZNETWORK_H
#define DEFAULT_NB_OF_LAYERS 3

#include "misc.h"
#include "matrix.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <dlib/optimization.h>

using namespace std;
using namespace dlib;

struct interLayers {
    int nbNodesLayer1;
    int nbNodesLayer2;
    double *weights;
};
typedef struct interLayers interLayers;

typedef matrix<double, 0, 1> column_vector;

class ZZNetwork {

public:
    ZZNetwork(int sizes[], int nbLayers, int setSize, double **input, double **output, double lambda=0.01);

    void train();
    //void train(double **trainingSet, int nbFeatures, int setSize);
    double * predict(double *input);

	double ***backPropagation();
    double costFunction(const column_vector& thetas);
    const column_vector costFunctionDerivative(const column_vector& thetas);
    //Test function

    operator bool() const {
        return network;
    }

    ~ZZNetwork();

public:
    int nbLayers;
    int maxNodes;
    bool trained;
    int setSize;
    double **input;
    double **output;
    double lambda;
    interLayers *network;
};


#endif //ZZBRAIN_ZZNETWORK_H
