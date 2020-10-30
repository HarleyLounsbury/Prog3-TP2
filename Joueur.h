// Joueur.h 
// En-tête du fichier de classe Joueur.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

class Joueur
{
private:
	Carte cartes[2];
	int valeur;

	int points;
	Carte cartesEnJeu[7];

public:
	Joueur();
	Carte G_carte(int position);
	void S_cartes(Carte LaCarte, int position);

	int G_valeur();
	void S_valeur(int valeurEncode);

	void S_cartesEnJeu(Carte LaCarte, int position);
	Carte* G_cartesEnJeu();
	
};