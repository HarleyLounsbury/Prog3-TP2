// Joueur.cpp 
// Définition de classe Joueur.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

#include "Biblio.h"

Joueur::Joueur()
{
	valeur = -1;
	points = -1;
}

Carte Joueur::G_carte(int position)
{
	// Retourner la carte spécifié.
	return cartes[position];
}

void Joueur::S_cartes(Carte LaCarte, int position)
{
	// Copier la carte distribué du paquet au joueur.
	cartes[position] = LaCarte;

	return;
}

int Joueur::G_valeur()
{
	return valeur;
}

void Joueur::S_valeur(int valeurEncode)
{
	valeur = valeurEncode;

	return;
}

void Joueur::S_cartesEnJeu(Carte LaCarte, int position)
{
	cartesEnJeu[position] = LaCarte;

	return;
}

Carte* Joueur::G_cartesEnJeu()
{
	return cartesEnJeu;
}

