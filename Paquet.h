// Paquet.h 
// En-tête du fichier de classe Paquet.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

class Paquet
{
private:
	Carte lesCartes[52];
	int curseur;
	void avancerCurseur();

public:
	Paquet();
	void Brasse();
	Carte CarteDistribue();

	Carte G_lesCartes(int position);
	int G_curseur();
	void S_curseur(int valeur);
};
