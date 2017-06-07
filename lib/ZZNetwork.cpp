#include "ZZNetwork.h"

ZZNetwork::ZZNetwork(int sizes[], int nbLayers, int setSize, double **input, double **output, double lambda){

    srand (time(NULL));

    this->setSize = setSize;
    this->input = input;
    this->output = output;
    this->lambda = lambda;
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
            //network[i].nbNodesLayer1 + 1 to include the biais weights
            network[i].weights = new double[ (network[i].nbNodesLayer1 + 1) * network[i].nbNodesLayer2];

            if(network[i].weights){
                for(int j = 0; j < (network[i].nbNodesLayer1 + 1) * network[i].nbNodesLayer2; j++){
                    //weights are initialised in the interval : [-r;r] (r = 4*sqrt(6/(nbNodesLayer1(including biais nodes) + nbNodesLayer2)))
                    //This interval will work only for sigmoid function (as activation function)
                    //There is a possibility that in the future we may change activation function, this line will need to be changed
                    double r = 4*sqrt(6.0/(network[i].nbNodesLayer1 + 1 + network[i].nbNodesLayer2));
                    network[i].weights[j] = (std::rand() / (RAND_MAX + 1.0))*2*r - r ;
                }
            }
            i++;
        }while(i < nbLayers - 1 && network[i - 1].weights);

        if(!network[i - 1].weights) {
            //If we can't alloc enough memory for a layer we need to free
            //the previous ones
            for(int j = i - 2; j >= 0; j++)
                delete[] network[j].weights;
            delete[] network;
        }
    }
    //Incremented to include bias node
    maxNodes++;
}

void ZZNetwork::train(){

    /* Creation of the initial theta column vector using the values in the network
        To use Dlib minimisation functions we need to use their data structure
        it can be costy if we have a large network, but we don't really have a choice
        */
	int size = 0;

	for(int i = 0; i < nbLayers - 1; i++)
		size += (network[i].nbNodesLayer1 + 1)*network[i].nbNodesLayer2;

	column_vector init_theta(size);

	size = 0;
	for(int l = 0; l < nbLayers - 1; l++)
		for(int j = 0; j < network[l].nbNodesLayer2; j++)
			for(int i = 0; i < network[l].nbNodesLayer1 + 1; i++, size++)
				init_theta(size) = network[l].weights[j*(network[l].nbNodesLayer1 + 1) + i];

    /* Minimisation of the cost function using a quasi-newtonien method (BFGS) */
	find_min(bfgs_search_strategy(), objective_delta_stop_strategy(1e-7),
		[this](column_vector const&v) -> double { return costFunction(v); },
		[this](column_vector const&v) -> column_vector { return costFunctionDerivative(v); },
		init_theta, -1);

}

double *ZZNetwork::predict(double *input) {

    double *a = new double[maxNodes];
    double *z = new double[maxNodes];

    if(a) {

        /* Perform a forward propagation to calculate the output value of the network
            for a given value as input */
        memcpy(a, input, network[0].nbNodesLayer1 * sizeof(double));
        for (int i = 0; i < nbLayers - 1; i++) {
                /* Add the bias node */
                memmove(a + 1, a, network[i].nbNodesLayer1 * sizeof(double));
                a[0] = 1.0;
                mult(network[i].weights, a, network[i].nbNodesLayer2, network[i].nbNodesLayer1 + 1, 1, z);
                sigmoid(z, network[i].nbNodesLayer2, 1, a);
        }
    }
    delete[] z;
    return a;
}

double ZZNetwork::costFunction(const column_vector& thetas){
    int cpt = 0;

    for(int i = 0; i < nbLayers - 1; i++)
		for(int j = 0; j < (network[i].nbNodesLayer1 + 1)*(network[i].nbNodesLayer2); j++, cpt++)
			network[i].weights[j] = thetas(cpt);


    double sum = 0, thetas_sum = 0;

    for(int i = 0; i < setSize; i++)
        for(int k = 0; k < network[nbLayers - 2].nbNodesLayer2; k++)
            sum += output[i][k]*log(predict(input[i])[k]) + (1 - output[i][k])*log(1 - predict(input[i])[k]);

    sum /= -setSize;

    for(int i = 0; i < thetas.nr(); i++)
        thetas_sum += thetas(i)*thetas(i);

    sum += (lambda/(2*setSize))*thetas_sum;

    return sum;
}

const column_vector ZZNetwork::costFunctionDerivative(const column_vector& thetas)
{
	int cpt = 0;
	double ***D;
	column_vector deriv(thetas.nr());

	for(int i = 0; i < nbLayers - 1; i++)
		for(int j = 0; j < (network[i].nbNodesLayer1 + 1)*(network[i].nbNodesLayer2); j++, cpt++)
			network[i].weights[j] = thetas(cpt);

	D = backPropagation();
	cpt = 0;

	for(int l = 0; l < nbLayers - 1; l++){
		for(int i = 0; i < network[l].nbNodesLayer2; i++)
			for(int j = 0; j < network[l].nbNodesLayer1 + 1; j++, cpt++)
				deriv(cpt) = D[l][i][j];
        for(int i = 0; i < maxNodes; i++)
            delete[] D[l][i];
        delete[] D[l];
    }

	return deriv;
}

double ***ZZNetwork::backPropagation(){
    double ***bigDelta = new double**[nbLayers];
    double ***D = new double**[nbLayers];
    double **a = new double*[nbLayers];
    double **z = new double*[nbLayers];
    double **err = new double*[nbLayers];
    double *tr, *theta_delta, *gz, *one, *dif, *eltm1;

    if(a && err && bigDelta && D){
        for(int l = 0; l < nbLayers; l++){
            a[l] = new double[maxNodes];
            z[l] = new double[maxNodes];
            err[l] = new double[maxNodes];

            D[l] = new double*[maxNodes];
            bigDelta[l] = new double*[maxNodes];
            for(int i = 0; i < maxNodes; i++){
                bigDelta[l][i] = new double[maxNodes];
                D[l][i] = new double[maxNodes];
                for(int j=0; j < maxNodes; j++){
                    bigDelta[l][i][j] = 0;
                }
            }
        }
    }

        for(int i = 0; i < setSize; i++) { // m = setSize //
            //Forward Propagation
            memcpy(a[0], input[i], network[0].nbNodesLayer1 * sizeof(double));
            for (int l = 1; l < nbLayers; l++) {
                memmove(a[l - 1] + 1, a[l - 1], network[l - 1].nbNodesLayer1 * sizeof(double));
                a[l - 1][0] = 1;
                z[l] = mult(network[l - 1].weights, a[l - 1], network[l - 1].nbNodesLayer2, network[l - 1].nbNodesLayer1 + 1, 1);
                a[l] = sigmoid(z[l], network[l - 1].nbNodesLayer2, 1);
            }


            // Calculating Erreur (small delta)

            err[nbLayers - 1] = diff(a[nbLayers - 1], output[i], network[nbLayers - 2].nbNodesLayer2, 1);

            for(int l = nbLayers - 2; l > 0 ; l--){

                tr = trans(network[l].weights, network[l].nbNodesLayer2, network[l].nbNodesLayer1 + 1);
                theta_delta = mult(tr, err[l + 1], network[l].nbNodesLayer1 + 1, network[l].nbNodesLayer2, 1);
                one = ones(network[l].nbNodesLayer1 + 1);
                memmove(z[l] + 1, z[l], network[l].nbNodesLayer1 * sizeof(double));
                z[l][0] = 1.0;
                dif = diff(one, sigmoid(z[l], network[l].nbNodesLayer1 + 1, 1), network[l].nbNodesLayer1 + 1, 1);
                eltm1 = eltMult(sigmoid(z[l], network[l].nbNodesLayer1 + 1, 1), dif, network[l].nbNodesLayer1 + 1, 1);
                err[l] = eltMult(theta_delta, eltm1, network[l].nbNodesLayer1 + 1, 1) + 1;

                delete[] tr;
                delete[] theta_delta;
                delete[] dif;
                delete[] one;
                delete[] eltm1;
            }


            // Calculating bigDelta gradient accumelator;

            for(int l = 0; l < nbLayers - 1; l++){
                //int lim = (l == nbLayers - 2)?network[l].nbNodesLayer2:(network[l].nbNodesLayer2 + 1);
                tr = trans(a[l],network[l].nbNodesLayer1 + 1, 1);
                theta_delta = mult(err[l+1], tr, network[l].nbNodesLayer2, 1, network[l].nbNodesLayer1 + 1);

				for(int k = 0; k < network[l].nbNodesLayer2; k++)
					for(int j = 0; j < network[l].nbNodesLayer1 + 1; j++)
                		bigDelta[l][k][j] = bigDelta[l][k][j] + theta_delta[k * (network[l].nbNodesLayer1 + 1) + j];
            }
        }

       // Calculation D the gradient XD

       for(int l=0; l < nbLayers - 1; l++){
          for(int i=0; i < network[l].nbNodesLayer2; i++) {
                D[l][i][0] = bigDelta[l][i][0]/setSize;
                for(int j=1; j < network[l].nbNodesLayer1 + 1; j++)
                    D[l][i][j] = bigDelta[l][i][j]/setSize + lambda*network[l].weights[i * (network[l].nbNodesLayer1 + 1) + j];
                delete[] bigDelta[l][i];
           }
           delete[] bigDelta[l];
       }

	return D;
}

ZZNetwork::~ZZNetwork() {
    for(int i = 0; i < nbLayers - 1; i++)
        delete[] network[i].weights;
    delete[] network;
}
