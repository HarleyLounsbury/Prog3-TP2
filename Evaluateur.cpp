// Evaluateur.cpp
// Définition de classe Evaluateur.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04
#include "Biblio.h"

Evaluateur::Evaluateur(Carte Cartes[7])
{
	// Initialiser les variables pour évaluer.
	for (int i = 0; i < 7; i++)
	{
		LesCartes[i] = Cartes[i];
	}
}

int Evaluateur::GetValeur()
{
	int valeur = 0;

	// Tableau pour compter le nombre de chaque valeur et le nombre de chaque couleur dans la main.
	int tabValeurs[13] = { 0 };
	int tabCouleurs[4] = { 0 };
	for (int i = 0; i < 7; i++)
	{
		tabValeurs[LesCartes[i].G_valeur()]++;
		tabCouleurs[LesCartes[i].G_sorte()]++;
	}

	// Valider les mains de poker. 
	if (contientCouleur(tabValeurs, tabCouleurs, valeur) && contientQuinte(tabValeurs, valeur))
		return valeur;
	else
		// On doît réinitialiser la valeur, car il est possible que la main contient un main couleur ou quinte, et on ne veut pas que 
		// la valeur soit corrompu par le test de quinte-flush. 
		valeur = 0;

	if (contientCarre(tabValeurs, valeur))
		return valeur;
	if (contientFull(tabValeurs, valeur))
		return valeur;
	if (contientCouleur(tabValeurs, tabCouleurs, valeur))
		return valeur;
	if (contientQuinte(tabValeurs, valeur))
		return valeur;
	if (contientBrelan(tabValeurs, valeur))
		return valeur;
	if (contientDeuxPaires(tabValeurs, valeur))
		return valeur;
	if (contientPaire(tabValeurs, valeur))
		return valeur;

	// Si il n'y a pas de main à titre, on doit compter les 5 cartes les plus hautes.
	trier();
	int cartesHautes[5] = { LesCartes[6].G_valeur(), LesCartes[5].G_valeur(), LesCartes[4].G_valeur(), LesCartes[3].G_valeur(), LesCartes[2].G_valeur() };
	
	return attribuerValeur(CARTE_HAUTE, cartesHautes);
}

string Evaluateur::ConvertirValeurEnFrancais(int valeur)
{
	// Décoder la valeur entier et retourner le message approprié.
	string message = "";

	// Décoder la valeur, et afficher le message approprié.
	switch (valeur / 100000000)
	{
	case QUINTE_FLUSH:
		valeur %= 100000000;
		if (valeur / 1000000 / 2 != 3)
			return "Quinte-Flush" + conjonction(valeur / 1000000 / 2) + valeurEnFrancais(valeur / 1000000 / 2)
				+ ", " + valeurEnFrancais(valeur % 1000000 / 10000 / 2)
				+ ", " + valeurEnFrancais(valeur % 10000 / 100 / 2)
				+ ", " + valeurEnFrancais(valeur % 100 / 10 / 2)
				+ ", " + valeurEnFrancais(valeur % 10 / 2);
		return "Quinte-Flush" + conjonction(valeur / 1000000 / 2) + valeurEnFrancais(valeur / 1000000 / 2)
			+ ", " + valeurEnFrancais(valeur % 1000000 / 10000 / 2)
			+ ", " + valeurEnFrancais(valeur % 10000 / 100 / 2)
			+ ", " + valeurEnFrancais(valeur % 100 / 10 / 2)
			+ ", " + valeurEnFrancais(12);
	case CARRE:
		valeur %= 100000000;
		return "Carré " + conjonctionAs(valeur / 10000) + valeurEnFrancais(valeur / 10000) + conjonction(valeur % 100) + valeurEnFrancais(valeur % 100);
	case FULL:
		valeur %= 100000000;
		return "Full-house: brélan " + conjonctionAs(valeur / 10000) + valeurEnFrancais(valeur / 10000) 
			+ ", paire " + conjonctionAs(valeur % 10000 / 100) + valeurEnFrancais(valeur % 10000 / 100);
	case COULEUR:
		valeur %= 100000000;
		return "Couleur" + conjonction(valeur / 1000000) + valeurEnFrancais(valeur / 1000000)
			+ ", " + valeurEnFrancais(valeur % 1000000 / 10000)
			+ ", " + valeurEnFrancais(valeur % 10000 / 100)
			+ ", " + valeurEnFrancais(valeur % 100 / 10)
			+ ", " + valeurEnFrancais(valeur % 10);
	case QUINTE:
		valeur %= 100000000;
		if (valeur / 1000000 != 3)
			return "Quinte" + conjonction(valeur / 1000000) + valeurEnFrancais(valeur / 1000000)
				+ ", " + valeurEnFrancais(valeur % 1000000 / 10000)
				+ ", " + valeurEnFrancais(valeur % 10000 / 100)
				+ ", " + valeurEnFrancais(valeur % 100 / 10)
				+ ", " + valeurEnFrancais(valeur % 10);
		return "Quinte" + conjonction(valeur / 1000000) + valeurEnFrancais(valeur / 1000000)
			+ ", " + valeurEnFrancais(valeur % 1000000 / 10000)
			+ ", " + valeurEnFrancais(valeur % 10000 / 100)
			+ ", " + valeurEnFrancais(valeur % 100 / 10)
			+ ", " + valeurEnFrancais(12);
	case BRELAN:
		valeur %= 100000000;
		return "Brélan " + conjonctionAs(valeur / 10000) + valeurEnFrancais(valeur / 10000) 
			+ conjonction(valeur % 10000 / 100) + valeurEnFrancais(valeur % 10000 / 100)
			+ ", " + valeurEnFrancais(valeur % 100);
	case PAIRE:
		valeur %= 100000000;
		return "Paire " + conjonctionAs(valeur / 1000000) + valeurEnFrancais(valeur / 1000000)
			+ conjonction(valeur % 1000000 / 10000) + valeurEnFrancais(valeur % 1000000 / 10000)
			+ ", " + valeurEnFrancais(valeur % 10000 / 100)
			+ ", " + valeurEnFrancais(valeur % 100);
	case DOUBLE_PAIRE:
		valeur %= 100000000;
		return "Deux paires: paire " + conjonctionAs(valeur / 10000) + valeurEnFrancais(valeur / 10000) +
			" et paire " + conjonctionAs(valeur % 10000 / 100) + valeurEnFrancais(valeur % 10000 / 100) + 
			conjonction(valeur % 100) + valeurEnFrancais(valeur % 100);
	case CARTE_HAUTE:
		return "Carte haute" + conjonction(valeur / 1000000) + valeurEnFrancais(valeur / 1000000)
			+ ", " + valeurEnFrancais(valeur % 1000000 / 10000)
			+ ", " + valeurEnFrancais(valeur % 10000 / 100)
			+ ", " + valeurEnFrancais(valeur % 100 / 10)
			+ ", " + valeurEnFrancais(valeur % 10);
	default: 
		break;
	}

	return message;
}

void Evaluateur::permuter(int indice1, int indice2)
{
	// Permuter 2 cartes.
	Carte cTemp;
	cTemp = LesCartes[indice1];
	LesCartes[indice1] = LesCartes[indice2];
	LesCartes[indice2] = cTemp;

	return;
}

void Evaluateur::trier()
{
	// Trier en ordre de valeur croissant pour faciliter des evalutations.
	for (int i = 0; i < 6; i++)
	{
		for (int j = i + 1; j < 7; j++)
		{
			if (LesCartes[i].G_valeur() > LesCartes[j].G_valeur())
			{
				permuter(i, j);
			}
		}
	}

	return;
}

// La plus haute magnitude est pour comparer les titres des mains
// Les autres magnitudes mémorisent le minimum information possible pour comparer 2 mains au même titre. 
int Evaluateur::attribuerValeur(const int MAIN, int valeurCarte)
{
	// Méchanisme pour encoder la meilleure main du joueur.
	int valeur = 0;
	switch (MAIN)
	{
	case CARRE:
	case BRELAN:
		valeur = MAIN * 100000000;
		valeur += valeurCarte * 10000;
		return valeur;
	case PAIRE:
		valeur = MAIN * 100000000;
		valeur += valeurCarte * 1000000;
		return valeur;
	case QUINTE:
		valeur = MAIN * 100000000;
		valeur += valeurCarte * 1000000;
		valeur += (valeurCarte - 1) * 10000;
		valeur += (valeurCarte - 2) * 100;
		valeur += (valeurCarte - 3) * 10;
		if (valeurCarte != 3)
			valeur += (valeurCarte - 4);
		return valeur;
	}
	return valeur;
}

int Evaluateur::attribuerValeur(const int MAIN, int valeur1, int valeur2)
{
	// Méchanism pour encoder les mains quand on a deux valeurs.
	int valeur = 0;
	
	valeur = MAIN * 100000000;
	valeur += valeur1 * 10000;
	valeur += valeur2 * 100;
	return valeur;
		

	return valeur;
}

int Evaluateur::attribuerValeur(const int MAIN, int valeurs[])
{
	// Pour bien stocker les 5 valeurs (le plus de valeurs à stocker dans le jeu):
	// On a besoin de savoir les cinq valeurs en ordre pour: 
	//										1. afficher en français
	//										2. déterminer le gagnant
	// L'encodage est un peu particulier pour les mains couleurs.
	// Dans une seule couleur, il peut avoir au maximum 3 cartes qui ont un valeur de 2 chiffres (12, 11, 10, soit as, roi, dame)
	//		et deux cartes qui auront une valeur à un chiffre. On a besoin de 8 chiffres, en plus de celui qui identifie la main, donc, 100,000,000.
	// Donc, les 3 cartes les plus hautes 1: dixaines de millions/millions
	//									  2: centaines de milliers/dixaines de milliers
	//									  3: milliers / centaines
	//		 les 2 autres cartes:		  4: dixaines
	//									  5: les unités.
	// On doit avoir aussi un cas spéciale pour la quinte flush, car il va attribuer des points comme si As = 12, 5, 4, 3, 2
	int valeurTotal = 0;
	valeurTotal = MAIN * 100000000;
	if (valeurs[0] == 12 && valeurs[1] == 3 && valeurs[2] == 2 && valeurs[3] == 1 && valeurs[4] == 0 && MAIN != CARTE_HAUTE)
	{
		valeurTotal += valeurs[1] * 1000000;
		valeurTotal += valeurs[2] * 10000;
		valeurTotal += valeurs[3] * 100;
		valeurTotal += valeurs[4] * 10;

		return valeurTotal;
	}
	valeurTotal += valeurs[0] * 1000000;
	valeurTotal += valeurs[1] * 10000;
	valeurTotal += valeurs[2] * 100;
	valeurTotal += valeurs[3] * 10;
	valeurTotal += valeurs[4];

	return valeurTotal;
}

bool Evaluateur::contientCarre(int tabValeurs[], int& valeur)
{
	// déterminer si il y a 4 d'une valeur dans le tableau.
	for (int i = 0; i < 13; i++)
	{
		if (tabValeurs[i] == 4)
		{
			valeur = attribuerValeur(CARRE, i);
			// Ajouter la valeur de la carte haute.
			valeur += trouverCarteHaute(tabValeurs, i);
			return true;
		}
	}
	return false;
}

bool Evaluateur::contientFull(int tabValeurs[], int& valeur)
{
	// déterminer si il y a 3 d'une valeur dans le tableau.
	for (int i = 12; i >= 0; i--)
	{
		if (tabValeurs[i] == 3)
			// déterminer si il y a 2 d'une valeur dans le tableau.
			for (int j = 12; j >= 0; j--)
			{
				if (tabValeurs[j] == 2)
				{
					valeur = attribuerValeur(FULL, i, j);
					return true;
				}
			}
	}
	return false;
}

bool Evaluateur::contientBrelan(int tabValeurs[], int& valeur)
{
	// déterminer si il y a 3 d'une valeur dans le tableau.
	for (int i = 12; i >= 0; i--)
	{
		if (tabValeurs[i] == 3)
		{
			valeur = attribuerValeur(BRELAN, i);
			// On trouve maintenant les 2 cartes les plus hautes de la main, qui ne sont pas dans le brélan.
			
			valeur += trouverCarteHaute(tabValeurs, i) * 100;
			valeur += trouverCarteHaute(tabValeurs, trouverCarteHaute(tabValeurs, i), i);
			return true;
		}
	}
	return false;
}

bool Evaluateur::contientDeuxPaires(int tabValeurs[], int& valeur)
{
	// déterminer si il y a 2 d'une valeur dans le tableau.
	for (int i = 12; i >= 0; i--)
	{
		if (tabValeurs[i] == 2)
		{
			// Déterminer par la suite s'il y a une autre paire.
			for (int j = 12; j >= 0; j--)
			{
				if (tabValeurs[j] == 2 && j != i)
				{
					valeur = attribuerValeur(DOUBLE_PAIRE, i, j);
					valeur += trouverCarteHaute(tabValeurs, i, j);
					return true;
				}
			}
		}
	}
	return false;
}

bool Evaluateur::contientPaire(int tabValeurs[], int& valeur)
{
	// déterminer si il y a 2 d'une valeur dans le tableau.
	for (int i = 12; i >= 0; i--)
	{
		if (tabValeurs[i] == 2)
		{
			int cartesHautes[3];
			valeur = attribuerValeur(PAIRE, i);
			// Il faut chercher les 3 cartes les plus hautes qui ne sont pas dans le paire.
			trier();
			for (int j = 6; j >= 0; j--)
			{
				if (LesCartes[j].G_valeur() != i)
				{
					valeur += LesCartes[j].G_valeur() * 10000;
					for (int k = j - 1; k >= 0; k--)
					{
						if (LesCartes[k].G_valeur() != i)
						{
							valeur += LesCartes[k].G_valeur() * 100;
							for (int l = k - 1; l >= 0; l--)
							{
								if (LesCartes[l].G_valeur() != i)
								{
									valeur += LesCartes[l].G_valeur();
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool Evaluateur::contientQuinte(int tabValeurs[], int& valeur)
{
	// Déterminer qu'il y a 5 valeurs qui se suivent. 
	for (int i = 12; i >= 4; i--)
	{
		if (tabValeurs[i] >= 1
			&& tabValeurs[i - 1] >= 1
			&& tabValeurs[i - 2] >= 1
			&& tabValeurs[i - 3] >= 1
			&& tabValeurs[i - 4] >= 1)
		{
			// On a juste besoin de passer la carte avec la valeur la plus haute pour déduire les autres.
			valeur += attribuerValeur(QUINTE, i);
			return true;
		}
			// Vérifier la roue (As en étant la plus petite valeur)
		else if (tabValeurs[12] >= 1
			&& tabValeurs[3] >= 1
			&& tabValeurs[2] >= 1
			&& tabValeurs[1] >= 1
			&& tabValeurs[0] >= 1)
		{
			valeur += attribuerValeur(QUINTE, 3);
			return true;
		}
	}
	return false;
}

bool Evaluateur::contientCouleur(int tabValeurs[], int tabCouleurs[], int& valeur)
{
	// Déterminer s'il y a 5 couleurs pareilles.
	// Dû au fait qu'il faut aussi mémoriser les 5 cartes couleur avec les plus hautes valeurs, ceci implique mulitple boucles imbriquées.
	// Les noms de variables dans les boucles sont, alors, plus déscriptifs qu'ailleurs dans le projet. 
	for (int couleur = 0; couleur < 4; couleur++)
	{
		if (tabCouleurs[couleur] == 5)
		{
			int valeursCartesCouleur[5];
			// Déterminer la valeur de chaque carte de la couleur gagnante, de la plus haute valeur à la plus petite.
			trier();
			for (int indiceCarteAStocker = 6, indiceStockage = 0; indiceCarteAStocker >= 0; indiceCarteAStocker--)
			{
				if (LesCartes[indiceCarteAStocker].G_sorte() == couleur)
				{
					valeursCartesCouleur[indiceStockage] = LesCartes[indiceCarteAStocker].G_valeur();
					indiceStockage++;
				}
			}
			// Ici on a maintenant les 5 valeurs les plus hautes des cartes avec la couleur gagnante.
			// Ajouter la valeur au lieu d'affection. Important quand on valide couleur et quinte, car quinte flush va retourner vrai aux deux validations. 
			valeur += attribuerValeur(COULEUR, valeursCartesCouleur);
			return true;
		}
	}
	return false;
}

int Evaluateur::trouverCarteHaute(int tabValeurs[])
{
	// Retourner la valeur de la carte le plus fort.
	for (int i = 12; i >= 0; i--)
	{
		if (tabValeurs[i] > 0)
		{
			return i;
		}
	}
	return 0;
}

int Evaluateur::trouverCarteHaute(int tabValeurs[], int valeurConnu)
{
	// Retourner la carte haute qui n'est pas une carte déjà connu.
	for (int i = 12; i >= 0; i--)
	{
		if (tabValeurs[i] > 0 && i != valeurConnu)
			return i;
	}
	return -1;
}

int Evaluateur::trouverCarteHaute(int tabValeurs[], int valeurConnu1, int valeurConnu2)
{
	// Retourner la carte haute qui n'est pas une carte déjà connu.
	for (int i = 12; i >= 0; i--)
	{
		if (tabValeurs[i] > 0 && i != valeurConnu1 && i != valeurConnu2)
			return i;
	}
	return -1;
}

string Evaluateur::valeurEnFrancais(int valeur)
{
	// Retourner la valeur en français de la carte.
	switch (valeur)
	{
	case 0:
		return "deux";
	case 1: 
		return "trois";
	case 2:
		return "quatre";
	case 3: 
		return "cinq";
	case 4:
		return "six";
	case 5:
		return "sept";
	case 6:
		return "huit";
	case 7:
		return "neuf";
	case 8:
		return "dix";
	case 9:
		return "valet";
	case 10:
		return "dame";
	case 11:
		return "roi";
	case 12: 
		return "as";
	}

	return "Un erreur s'est produit: Cartes\n";
}

string Evaluateur::conjonction(int valeurAVenir)
{
	// Pour les partiularités de la langue française.
	switch (valeurAVenir)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 11:
		return " au ";
	case 10:
		return " à la ";
	case 12:
		return " à l'";
	}

	return "Un erreur s'est produit: conjonction\n";
}

string Evaluateur::conjonctionAs(int valeurAVenir)
{
	// Pour les partiularités de la langue française.
	if (valeurAVenir == 12)
		return "d'";
	return "de ";
}
