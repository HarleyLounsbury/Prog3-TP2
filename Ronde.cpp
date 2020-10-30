// Ronde.cpp
// Définition de classe Ronde.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

#include "Biblio.h"

void Ronde::DistribuerCartes()
{
	// Réinitialiser le curseur au début du jeu.
	UnPaquet.S_curseur(0);

	// Appels de fonctions du jeu.
	UnPaquet.Brasse();

	distribuerCartesAuJoueurs();

	afficherCartesDesJoueurs();

	afficherCartesPubliques("FLOP", 3);

	afficherCartesPubliques("TURN", 1);

	afficherCartesPubliques("RIVER", 1);

	return;
}

void Ronde::EvaluerMains()
{
	// Créer les mains de 7 cartes de chaque joueur, et évaluer.
	creerMainsEnJeu();

	for (int i = 0; i < NB_JOUEURS; i++)
	{
		Evaluateur Eval(lesJoueurs[i].G_cartesEnJeu());	
		lesJoueurs[i].S_valeur(Eval.GetValeur());
		cout << "Joueur " << i << ": " << Eval.ConvertirValeurEnFrancais(lesJoueurs[i].G_valeur());
	
		cout << endl;
	}
	cout << endl;
}

void Ronde::DeterminerGagnant()
{
	// Trouver la valeur la plus forte.
	int valeurGagnant = 0;
	for (int i = 0; i < NB_JOUEURS; i++)
		if (lesJoueurs[i].G_valeur() > valeurGagnant)
			valeurGagnant = lesJoueurs[i].G_valeur();
	
	// Afficher le gagnant et, dans le cas d'égalités, les autres gagnants.
	for (int i = 0, compteur = 0; i < NB_JOUEURS; i++)
	{
		if (lesJoueurs[i].G_valeur() == valeurGagnant && compteur > 0)
		{
			cout << "Le gagnant est aussi Joueur " << i << endl;
			compteur++;
		}
		if (lesJoueurs[i].G_valeur() == valeurGagnant && compteur == 0)
		{
			cout << "Le gagnant est Joueur " << i << endl;
			compteur++;
		}
	}
	return;
}

void Ronde::distribuerCartesAuJoueurs()
{
	// Distribuer 2 cartes à chaque joueur.
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < NB_JOUEURS; j++)
		{
			lesJoueurs[j].S_cartes(UnPaquet.CarteDistribue(), i);
		}
	}
	return;
}

void Ronde::creerMainsEnJeu()
{
	// Pour créer le tableau des 7 cartes en jeu par joueur.
	for (int i = 0; i < NB_JOUEURS; i++)
	{
		// Chercher les 2 cartes de joueurs.
		lesJoueurs[i].S_cartesEnJeu(lesJoueurs[i].G_carte(0), 0);
		lesJoueurs[i].S_cartesEnJeu(lesJoueurs[i].G_carte(1), 1);

		// Chercher les 5 cartes publiques.
		for (int cartesPublique = NB_JOUEURS * 2, positions = 2; cartesPublique < UnPaquet.G_curseur(); cartesPublique++, positions++)
		{
			lesJoueurs[i].S_cartesEnJeu(UnPaquet.G_lesCartes(cartesPublique), positions);
		}
	}

	return;
}

void Ronde::afficherCartesDesJoueurs()
{
	// Titre pour les cartes des joueurs.
	cout << "Cartes privées des joueurs:" << endl;

	// Afficher les 2 cartes de chaque joueur.
	for (int i = 0; i < NB_JOUEURS; i++)
	{
		cout << "\t" << "Joueur " << i << "\t ";
		lesJoueurs[i].G_carte(0).AfficherCarte();
		cout << "  ";
		lesJoueurs[i].G_carte(1).AfficherCarte();
		cout << endl;
	}
	

	ligneDeTirets();

	return;
}

void Ronde::afficherCartesPubliques(string titre, int nbCartes)
{
	// Afficher les cartes publiques.
	cout << titre << ":" << endl;

	cout << "\t\t";
	for (int i = 0; i < nbCartes; i++)
	{
		UnPaquet.CarteDistribue().AfficherCarte();
		cout << "  ";
	}
	cout << endl;

	ligneDeTirets();

	return;
}

void Ronde::ligneDeTirets()
{
	// Ligne de tirets.
	cout << setw(42) << setfill('-') << "-" << endl;

	return;
}
