// Texas Hold'em Main.cpp
// Fichier main du jeu de Texas Hold'em.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04
#include "Biblio.h"

int main()
{
	setlocale(LC_ALL, "");
	while (true)
	{
		
		Ronde UneRonde;
		
		UneRonde.DistribuerCartes();
		UneRonde.EvaluerMains();
		UneRonde.DeterminerGagnant();


 		system("pause");
		system("cls");
	}

	return 0;
}