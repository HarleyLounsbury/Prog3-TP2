// Carte.h 
// En-tête du fichier de classe Carte.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

class Carte
{
private:
	int valeur;
	int sorte;
	char determinerCouleur();

public:
	Carte();
	Carte(int val, int sor);

	void AfficherCarte();
	int G_valeur();
	int G_sorte();
};
