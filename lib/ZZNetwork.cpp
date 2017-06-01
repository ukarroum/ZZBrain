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
            network[i].weights = new double[ (network[i].nbNodesLayer1 + 1) * network[i].nbNodesLayer2];

            if(network[i].weights)
                for(int j = 0; j < (network[i].nbNodesLayer1 + 1) * network[i].nbNodesLayer2; j++)
                    network[i].weights[j] = std::rand();
            i++;
        }while(i < nbLayers - 1 && network[i - 1].weights);

        if(!network[i - 1].weights) {
            for(int j = i - 2; j >= 0; j++)
                delete[] network[j].weights;
            delete[] network;
        }
    }
    maxNodes++;
}

ZZNetwork::~ZZNetwork() {
    for(int i = 0; i < nbLayers - 1; i++)
        delete[] network[i].weights;
    delete[] network;
}

double ***ZZNetwork::backPropagation(){
    double ***bigDelta = new double**[nbLayers];
    double ***D = new double**[nbLayers];
    double **a = new double*[nbLayers];
    double **err = new double*[nbLayers];
    double *z, *tr, *theta_delta, *gz, *one, *dif, *eltm1;

    if(a && err && bigDelta && D){
        for(int l = 0; l < nbLayers; l++){
            a[l] = new double[maxNodes];
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
            a[0][0] = 1;
            memcpy(a[0] + 1, input[i], network[0].nbNodesLayer1 * sizeof(double));
            for (int l = 1; l < nbLayers; l++) {
                z = mult(network[l - 1].weights, a[l - 1], network[l - 1].nbNodesLayer2, network[l - 1].nbNodesLayer1 + 1, 1);
                a[l] = sigmoid(z, network[l - 1].nbNodesLayer2, 1);
                delete[] z;
            }

            // Calculating Erreur (small delta)

            err[nbLayers - 1] = diff(a[nbLayers - 1], output[i], network[nbLayers - 2].nbNodesLayer2, 1);

            for(int l = nbLayers - 2; l > 0 ; l--){

                tr = trans(network[l].weights, network[l].nbNodesLayer2, network[l].nbNodesLayer1 + 1);
                theta_delta = mult(tr, err[l + 1], network[l].nbNodesLayer1 + 1, network[l].nbNodesLayer2, network[l].nbNodesLayer2);
                one = ones(network[l].nbNodesLayer1);
                dif = diff(one, a[l], network[l].nbNodesLayer1, 1);
                eltm1 = eltMult(a[l], dif, network[l].nbNodesLayer1, 1);
                err[l] = eltMult(theta_delta, eltm1, network[l].nbNodesLayer1, 1);

                delete[] tr;
                delete[] theta_delta;
                delete[] dif;
                delete[] one;
                delete[] eltm1;
            }

            // Calculating bigDelta gradient accumelator;

            for(int l = 0; l < nbLayers - 2; l++){
                tr = trans(a[l],network[l].nbNodesLayer1, 1);
                theta_delta = mult(err[l+1], tr, network[l].nbNodesLayer2, 1, network[l].nbNodesLayer1);
				for(int i = 0; i < network[l].nbNodesLayer2; i++)
					for(int j = 0; j < network[l].nbNodesLayer1; j++)
                		bigDelta[l][i][j] = bigDelta[l][i][j] + theta_delta[i * network[l].nbNodesLayer1 + j];

            }

        }

       // Calculation D the gradient XD

       for(int l=0; l < nbLayers; l++){
          for(int i=0; i < network[l].nbNodesLayer2; i++) {
                for(int j=1; j < network[l].nbNodesLayer1 + 1; j++){
                    D[l][i][j] = bigDelta[l][i][j]/setSize + lambda*network[l].weights[i * network[l].nbNodesLayer2 + j];
                }
                // if j = 0
                D[l][i][0] = bigDelta[l][i][0]/setSize;
           }
       }

	return D;
}

double *ZZNetwork::predict(double *input) {
    double *a = new double[maxNodes + 1];
    double *z;

    if(a) {
        memcpy(a, input, network[0].nbNodesLayer1 * sizeof(double));
        for (int i = 0; i < nbLayers - 1; i++) {
                memmove(a + 1, a, network[i].nbNodesLayer1 * sizeof(double));
                a[0] = 1.0;
                z = mult(network[i].weights, a, network[i].nbNodesLayer2, network[i].nbNodesLayer1 + 1, 1);
                a = sigmoid(z, network[i].nbNodesLayer2, 1);
                delete[] z;
        }
    }

    return a;
}
double ZZNetwork::costFunction(const column_vector& thetas){
    double sum = 0;
    double thetas_sum = 0;
    for(int i = 0; i < setSize; i++){
        for(int k = 0; k < network[nbLayers - 2].nbNodesLayer2; k++){
          cout << "y : " << output[i][k] << endl;
          			cout << "h(x) : " << predict(input[i])[k] << endl;
                if(output[i][k] != predict(input[i])[k])
                    sum += 1e+100;
            //sum += output[i][k]*log(predict(input[i])[k]) + (1 - output[i][k]*log(1 - predict(input[i])[k]));
			cout << "sum " << sum << endl;
		}
	}
    sum /= -setSize;

    for(int i = 0; i < thetas.nr(); i++)
        thetas_sum += thetas(i);

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

	for(int l = 0; l < nbLayers - 1; l++)
		for(int i = 0; i < network[l].nbNodesLayer2; i++)
			for(int j = 0; j < network[l].nbNodesLayer1 + 1; j++, cpt++)
				deriv(cpt) = D[l][i][j];


	return deriv;
}

double foo(column_vector const&) { return {}; }
column_vector fooder(column_vector const&v) { return v; }

void ZZNetwork::train(){
	int size = 0;

	for(int i = 0; i < nbLayers - 1; i++)
		size += (network[i].nbNodesLayer1 + 1)*network[i].nbNodesLayer2;

	column_vector init_theta(size);
	size = 0;
	for(int l = 0; l < nbLayers - 1; l++)
		for(int j = 0; j < network[l].nbNodesLayer2; j++)
			for(int i = 0; i < network[l].nbNodesLayer1 + 1; i++, size++)
				init_theta(size) = network[l].weights[j*(network[l].nbNodesLayer1 + 1) + i];

	find_min(bfgs_search_strategy(), objective_delta_stop_strategy(1e-7),
		[this](column_vector const&v) -> double { return costFunction(v); },
		[this](column_vector const&v) -> column_vector { return costFunctionDerivative(v); },
		init_theta, -1);

	cout << init_theta << endl;

}
