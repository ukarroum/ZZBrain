#ifndef ZZBRAIN_ZZNETWORK_H
#define ZZBRAIN_ZZNETWORK_H

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <dlib/optimization.h>
#include "misc.h"
#include "matrix.h"

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
    //Class's constructor, initialise the weights to random values, and make the necessary space allocations.
    ZZNetwork(int sizes[], int nbLayers, int setSize, double **input, double **output, double lambda=0);

    //Train the neural network using the dataset gave to the costructor.
    void train();

    //Perform a forward propagation to calcul the result of a given query.
    double * predict(double *input);

	double ***backPropagation();
    double costFunction(const column_vector& thetas);
    const column_vector costFunctionDerivative(const column_vector& thetas);

    operator bool() const {
        return network;
    }

    ~ZZNetwork();

private:
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
