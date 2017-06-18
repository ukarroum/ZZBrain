# Présentation du projet

**ZZBrain** est un projet qui fut réalisé dans le cadre du module *Projet de deuxième semestre* de la première année à l’*ISIMA*. Il vise à créer une bibliothèque basique permettant la création et l’entrainement d’une classification basée sur les réseaux de neurones, c’est un projet purement pédagogique, et le lecteur intéressé par une bibliothéque pareille trouvera des alternatives bien plus puissantes
telles que : [TensorFlow](https://www.tensorflow.org/) ou [DLib](http://dlib.net/) . Les notations, algorithmes et formules utilisés sont fortement basés sur le cours [Machine Learning](https://www.coursera.org/learn/machine-learning) de Andrew Ng même si ce dernier est principalement proposé en Octave 3 alors que ZZBrain est codé en C++.
Nous utilisons la biblothéque Dlib pour la minimisation de la fonction J(Θ) .

# Instalation

## Debian (et dérivées)


```
    wget http://dlib.net/files/dlib-19.4.tar.bz2

    tar -xjvf file.tar.bz2

    git clone https://github.com/ukarroum/ZZBrain.git

    cd ZZBrain

    cmake .

    make

    ./ZZBrain
```

# Exemples

## XNOR

```cpp
#include <iostream>
#include "lib/ZZNetwork.h"

using namespace std;

int main() {

	int sizes[] = {2, 4, 1};
	int nbLayers = 3;

	double **X = new double*[1000];
	double **Y = new double*[1000];


	for(int i = 0; i < 1000; i++)
	{
		X[i] = new double[2];
		Y[i] = new double[2];
	}


	for(int i = 0; i < 250; i++)
	{
		X[i][0] = 0.0;
		X[i][1] = 0.0;
		Y[i][0] = 1.0;
	}
	for(int i = 250; i < 500; i++)
	{
		X[i][0] = 1.0;
		X[i][1] = 0.0;
		Y[i][0] = 0.0;
	}
	for(int i = 500; i < 750; i++)
	{
		X[i][0] = 0.0;
		X[i][1] = 1.0;
		Y[i][0] = 0.0;
	}
	for(int i = 750; i < 1000; i++)
	{
		X[i][0] = 1.0;
		X[i][1] = 1.0;
		Y[i][0] = 1.0;
	}



	ZZNetwork notNet(sizes, nbLayers, 1000, X, Y);
	notNet.train();

	cout << "xnor(0, 0) = " << notNet.predict(X[0])[0] << endl;
	cout << "xnor(1, 0) = " << notNet.predict(X[300])[0] << endl;
	cout << "xnor(0, 1) = " << notNet.predict(X[600])[0] << endl;
	cout << "xnor(1, 1) = " << notNet.predict(X[900])[0] << endl;

    return 0;

}
```

# Collaborateurs

* [Imad ENNEIYMY](https://github.com/maddxyz)
* [Yassir KARROUM](https://github.com/ukarroum)
