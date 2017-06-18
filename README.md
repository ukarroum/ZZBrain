#Présentation du projet

**ZZBrain** est un projet qui fut réalisé dans le cadre du module *Projet de deuxième semestre* de la première année à l’*ISIMA*. Il vise à créer une bibliothèque basique permettant la création et l’entrainement d’une classification basée sur les réseaux de neurones, c’est un projet purement pédagogique, et le lecteur intéressé par une bibliothéque pareille trouvera des alternatives bien plus puissantes
telles que : [TensorFlow](https://www.tensorflow.org/) ou [DLib](http://dlib.net/) . Les notations, algorithmes et formules utilisés sont fortement basés sur le cours [Machine Learning](https://www.coursera.org/learn/machine-learning) de Andrew Ng même si ce dernier est principalement proposé en Octave 3 alors que ZZBrain est codé en C++.
Nous utilisons la biblothéque Dlib pour la minimisation de la fonction J(Θ) .

#Instalation

## Debian (et dérivées)

Télécharger la bibliothéque DLib.

```
    wget http://dlib.net/files/dlib-19.4.tar.bz2
    ```

```
    tar -xjvf file.tar.bz2
    ```
```
    git clone https://github.com/ukarroum/ZZBrain.git
    ```

```
    cd ZZBrain
    ```


# Collaborateurs

* Imad ENNEIYMY(https://github.com/maddxyz)
* Yassir KARROUM(https://github.com/ukarroum)

## Functions:
### Matrix functions:
* Multiplication (n,m).
* Transpose.
* Sum.

### Neural Network functions:
* Diffrent constructors.
* Trainer.
* Tester.
* Predicter.

### Misc:
* Sigmoid function.

## Example :

```
#include <iostream>
#include "lib/ZZNetwork.h"

using namespace std;

int main() {
    int sizes[] = {4, 5, 1};
    int nbLayers = 3;
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
```
