#include <iostream>
#include "lib/ZZNetwork.h"

using namespace std;

int main() {
    int sizes[] = {2, 1};
    int nbLayers = 2;
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
    }
    else
        cout << "Too Bad" << endl;
    return 0;
}