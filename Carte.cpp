// Carte.cpp
// Définition de classe Carte.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

#include "Biblio.h"

Carte::Carte()
{
	// Valeurs d'initialisation pour enlever les avertissements de compilation.
	valeur = -1;
	sorte = -1;
}

Carte::Carte(int val, int sor)
{
	valeur = val;
	sorte = sor;
}

void Carte::AfficherCarte()
{
	// Afficher la carte à l'écran.
	int valeurAffichage = valeur + 2;
	if (valeurAffichage < 10)
	{
		cout << valeurAffichage << " de " << determinerCouleur();
		return;
	}

	switch (valeurAffichage)
	{
	case 10:
		cout << "D de " << determinerCouleur();
		break;
	case 11:
		cout << "J de " << determinerCouleur();
		break;
	case 12:
		cout << "Q de " << determinerCouleur();
		break;
	case 13:
		cout << "K de " << determinerCouleur();
		break;
	case 14: 
		cout << "A de " << determinerCouleur();
		break;
	default: 
		break;
	}

	return;
}

char Carte::determinerCouleur()
{
	// Determiner le couleur de carte selon la sorte.
	char couleur = 'X';

	switch (sorte)
	{
	case 0:
		couleur = 'P';
		break;
	case 1:
		couleur = 'T';
		break;
	case 2:
		couleur = 'C';
		break;
	case 3:
		couleur = 'H';
		break;
	default:
		break;
	}

	return couleur;
}

int Carte::G_valeur()
{
	return valeur;
}

int Carte::G_sorte()
{
	return sorte;
}
