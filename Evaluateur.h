// Evaluateur.h 
// En-tête du fichier de classe Evaluateur.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

class Evaluateur
{
private:
	Carte LesCartes[7];

	void permuter(int indice1, int indice2);
	void trier();

	int attribuerValeur(const int MAIN, int valeurCarte);
	int attribuerValeur(const int MAIN, int valeur1, int valeur2);
	int attribuerValeur(const int MAIN, int valeurs[]);

	   
	bool contientCarre(int tabValeurs[], int& valeur);
	bool contientFull(int tabValeurs[], int& valeur);
	bool contientBrelan(int tabValeurs[], int& valeur);
	bool contientDeuxPaires(int tabValeurs[], int& valeur);
	bool contientPaire(int tabValeurs[], int& valeur);
	bool contientQuinte(int tabValeurs[], int& valeur);
	bool contientCouleur(int tabValeurs[], int tabCouleurs[], int& valeur);

	int trouverCarteHaute(int tabValeurs[]);
	int trouverCarteHaute(int tabValeurs[], int valeurConnu);
	int trouverCarteHaute(int tabValeurs[], int valeurConnu1, int valeurConnu2);

	string valeurEnFrancais(int valeur);
	string conjonction(int valeurAVenir);
	string conjonctionAs(int valeurAVenir);
	

public:
	Evaluateur(Carte Cartes[7]);
	int GetValeur();
	string ConvertirValeurEnFrancais(int valeur);

};
