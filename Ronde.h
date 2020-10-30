// Ronde.h 
// En-tête du fichier de classe Ronde.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

class Ronde
{
private:
	Paquet UnPaquet;
	Joueur lesJoueurs[NB_JOUEURS];
	Carte Flop[3];
	Carte Turn;
	Carte River;
	void distribuerCartesAuJoueurs();
	void creerMainsEnJeu();

	// Fonctions d'affichage.
	void ligneDeTirets();
	void afficherCartesDesJoueurs();
	void afficherCartesPubliques(string titre, int nbCartes);

public:
	// Constructeurs.
	Ronde() {};

	// Fonctions du jeu.
	void DistribuerCartes();
	void EvaluerMains();
	void DeterminerGagnant();

};