// Paquet.cpp
// Définition de classe Paquet.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

#include "Biblio.h"

Paquet::Paquet()
{
	int curseurTemp = 0;
	// Initialiser le paquet, en ordre.
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			lesCartes[curseurTemp] = Carte(j, i);
			
			curseurTemp++;
		}
	}

	// POUR TESTER MAINS VARIÉES
	// IL faut aussi mettre en commentaire l' appel de la fonction Brasse() en Ronde.cpp, DistribuerCartes()
	/*lesCartes[0] = Carte(0, 0);
	lesCartes[4] = Carte(1, 0);

	lesCartes[1] = Carte(3, 1);
	lesCartes[5] = Carte(7, 1);

	lesCartes[2] = Carte(3, 2);
	lesCartes[6] = Carte(9, 2);

	lesCartes[3] = Carte(11, 3);
	lesCartes[7] = Carte(0, 3);

	lesCartes[8] = Carte(2, 0); 
	lesCartes[9] = Carte(4, 1);
	lesCartes[10] = Carte(6, 2);
	lesCartes[11] = Carte(8, 3);
	lesCartes[12] = Carte(10, 0);*/
	


	curseur = 0;
}

void Paquet::Brasse()
{
	// Brasser le paquet avec l'algorithm le plus simple: chaque carte va changer de place avec une carte choisi aléatoirement.
	// Si on décide que ce n'est pas suffisant, on peut envelopper la boucle dans une autre boucle pour effectuer l'opération plusieurs fois.
	srand((unsigned int)time(NULL));
	Carte cTemp;
	int indiceAPermuter;

	for (int i = 0; i < 52; i++)
	{
		indiceAPermuter = rand() % 52;
		cTemp = lesCartes[i];
		lesCartes[i] = lesCartes[indiceAPermuter];
		lesCartes[indiceAPermuter] = cTemp;
	}

	return;
}

Carte Paquet::CarteDistribue()
{
	avancerCurseur();
	return lesCartes[curseur - 1];
}

void Paquet::avancerCurseur()
{
	// Avancer le curseur. 
	curseur++;
	return;
}

Carte Paquet::G_lesCartes(int position)
{
	return lesCartes[position];
}

int Paquet::G_curseur()
{
	return curseur;
}

void Paquet::S_curseur(int valeur)
{
	curseur = valeur;

	return;
}
