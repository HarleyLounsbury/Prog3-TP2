// Biblio.h 
// En-tête du fichier de références.
// 
// Auteur: Harley Lounsbury
// Date: 2019-10-04

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

const int NB_JOUEURS = 4;

#include "Carte.h"
#include "Paquet.h"
#include "Joueur.h"
#include "Evaluateur.h"
#include "Ronde.h"

// Convention pour les mains.
const int QUINTE_FLUSH	= 9;
const int CARRE			= 7;
const int FULL			= 6;
const int COULEUR		= 5;
const int QUINTE		= 4;
const int BRELAN		= 3;
const int DOUBLE_PAIRE	= 2;
const int PAIRE			= 1;
const int CARTE_HAUTE	= 0;
