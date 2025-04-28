#ifndef     FONCTIONS_H_INCLUDED
#define     FONCTIONS_H_INCLUDED

#include "mbed.h"

/*
Attention à bien utiliser notre version de la bibliothèque DMX
Nous avons modifié dans DMX_MIDI.cpp la fonction ISR_midi_in afin de détecter plus d’instruments et modifié maFileAttente dans le preset 2 cf fonction preset2BanqueA pour plus de détails 
*/


// Variables globales
extern  int     Valeur_spots[]; // extern permet de rendre la variable globale, c'est-à-dire utilisable dans Fonctions.ccp uniquement
extern  int     Spot[];
extern  int     tab_Intensite[4];
extern  int     IntensiteTotale;
extern  int     tempo;
extern  int     Frequence;
extern  int     Couleur;
extern  int     Intensite1Inter;
extern  int     Intensite2Inter;
extern  int     Intensite3Inter;
extern  int     Intensite4Inter;
extern  PwmOut  sortieSon;
extern  float   note[12];
extern  float   volume;
extern  bool    Strobe;



// Mise à jour du projo numéro "projecteur" (les valeurs sont comprises dans Valeur_spots)
/*
 * MajProjecteurs: Met à jour l'éclairement des projecteurs
 * 	ENTREES :
 *		le projecteur concerné (numéroté de 0 à 3 de droite à gauche)
 * 	SORTIE :
 * 		Aucune valeur en sortie, la couleur des projecteurs a juste changé
	
    Explications sur l'affectation des Valeur_spots : 
 * 	Chaque projecteur est codé sur 8 bits. Celui tout à droite, numéroté 0, est représenté par les bits 32 à 40 
    (le fonctionnement des bits 32 à 39 est indiqué en notice, le 40ème bit est libre).
    Le projecteur 1 représenté par les bits 41 à 48, projecteur 2 de 49 à 57
 */
 void MaJProjecteurs(int projecteur);


/*
 * ChangementValeurs: Initialise un vecteur Valeur_spots qui permet de choisir le mode de fonctionnement du projo, stocke ses valeurs dans le cas où ce n'est pas
 un strobe afin qu'en arrêtant le potard strobe on retrouve la couleur qui le précédait
 * 	ENTREES :
 *		les entiers à mettre dans Valeur_spots
 * 	SORTIE :
 * 		Aucune Valeur_spots étant une variable globale
	
    Explications sur les modes du projo (cf p28 notice projo)
        Valeurs_spots[0] code le mode de fonctionnement du projo et détermine donc l'utilité de Valeurs_spots[1] à [6]
        Si Valeur_spots[0] vaut 10:
            Valeurs_spots[1] et [2] non exploités
            Valeurs_spots[3] overall brightness entre 0 et 255 vaut le conteneu de la variable Intensité définie dans le m ain
	        Valeurs_spots[4] [5] [6] chacun entre 0 et 255 code respectivement pour rouge vert bleu
  	    Si Valeur_spots[0] contient un entier entre 101 et 150 fade effect
	        Valeur_spots[2] permet de choisir une couleur avec un entier entre 0 et 255
	        Valeur_spots[3] vitesse du fade 
	        Valeur_spots[4] à [6] non exploités
        Si Valeur_spots[0] contient un entier entre 201 et255 strobe effect
	        Valeur_spots[2] permet de choisir une couleur avec un entier entre 0 et 255
	        Valeur_spots[3] vitesse du strobe
	        Valeur_spots[4] à [6] non exploités

 */
void ChangementValeurs(int val1, int val2, int val3, int val4, int val5, int val6, int val7);


// Crée un template RGB pour tous les spots
/*
 * RGBColor: Commande l’éclairement des projecteurs, la couleur des 4 projecteurs est déterminée par la touche sur laquelle on a appuyé 
 * 	ENTREES :
 *		la touche appuyée

 * 	SORTIE :
 * 		Aucune, RGBColor fait appel aux fonctions ChangementsValeurs et MaProjecteur pour modifier l’éclairement en place

_____________________________________________________
|            |            |            |            |
|    Bleu    |    Bleu    |  Magenta   |   Blanc    |
|            | Electrique |            |            |
_____________________________________________________
|            |            |            |            |
|   Violet   | Gris-bleu  | Bleu Océan |    Kaki    |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|Rose Fuchsia|  Rose Pâle | Bleu clair |    Cyan    |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|   Rouge    |   Orange   | Vert clair |    Vert    |
|            |            |            |            |
_____________________________________________________     
*/
void RGBColor(char touche);


/*
 * RGBColorIndividuel: Modifie l’éclairement des projecteurs en fonction de la touche sur laquelle on a appuyé, dans ce programme, une touche commande un unique projecteur
 * 	ENTREES :
 *		la touche appuyée

 * 	SORTIE :
 * 		Aucune, RGBColorIndividuel fait appel aux fonctions ChangementsValeurs et MaJProjecteur pour modifier l’éclairement en place

_____________________________________________________
|            |            |            |            |
|   Blanc0   |   Blanc1   |   Blanc2   |   Blanc3   |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|   Bleu0    |   Bleu1    |   Bleu2    |   Bleu3    |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|   Vert0    |   Vert1    |   Vert2    |   Vert3    |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|   Rouge0   |   Rouge1   |   Rouge2   |   Rouge3   |
|            |            |            |            |
_____________________________________________________
*/
void RGBColorIndividuel(char touche);


/*
 * RGBColorIndividuel: Modifie l’éclairement des projecteurs en fonction de la touche sur laquelle on a appuyé, dans ce programme, une touche commande un unique projecteur
 *  ENTREES :
 *      la touche appuyée
 *  SORTIE :
 *      Aucune, RGBColorIndividuel fait appel aux fonctions ChangementsValeurs et MaJProjecteur pour modifier l’éclairement en place
_____________________________________________________
|            |            |            |            |
|   Jaune0   |   Jaune1   |   Jaune2   |   Jaune3   |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|  Orange0   |  Orange1   |  Orange2   |  Orange3   |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|  Magenta0  |  Magenta1  |  Magenta2  |  Magenta3  |
|            |            |            |            |
_____________________________________________________
|            |            |            |            |
|   Cyan0    |   Cyan1    |   Cyan2    |   Cyan3    |
|            |            |            |            |
_____________________________________________________    
 */
void RJOCColorIndividuel(char touche);


/*
 * Potar1: 
 * 	ENTREES :
 *		potar: adresse du potar qui a changé
 *      intensite: valeur que ce potard prend
 * 	SORTIE :
 * 		Aucune 
	
    Explications: permet de commander l'intensité golbale en posant un minimum grâce au potar 1
    permet de commander individuellement les intensités avec les potar 2 à 5
    Pour pouvoir éteindre un proj il faut mettre le potar 1 dans le cinquième inférieure, puis descendre dans son cinquième inférieur le potar

 */
void Potar1(char potar, char intensite);


/*
 * ProjDateVersProjNum: Permet dans les modes C et D d'associer à une touche le proj
 * 	ENTREES :
 *		midi_data[1] de la forme 0x.... où ... coresspond au numéro de la touche
 * 	SORTIE :
 * 		0, 1, 2 ou 3 selon le proj auquel la touche ca correspond
*/
int ProjDataVersProjNum(char touche);


/*
 * Potar2: 
 * 	ENTREES :
 *		potar: adresse du potar qui a changé
 *      intensite: valeur que ce potard prend
 * 	SORTIE :
 * 		Aucune 
	
    Explications: 
    (intensite est  un nom de variable trompeur)
    le potar 6 commande la fréquence du strobe
    le potar 7 sa couleur  couleur changeantes en-dessous de 40%, au-dessus couleurs stationnaires
 */
void Potar2(char potar, char intensite);


/*
 * Potar3: 
 * 	ENTREES :
 *		potar: le numéro du potar
 *      intensite: la valeur que prend le potar
 * 	SORTIE :
 * 		Aucune modifie les valeurs globales du vol et du tempo
*   Explications:
*       le potar 6 règle le volume
*       le potar 7 règle le tempo
 */
void Potar3(char potar, char intensite);


/*
 * JoueNote : Permet de produire une note
 *  ENTREES :
 *      int octave : l'octave de la note (il y en a 3)
        int laNote : indique quelle note entre do et si est jouée
 *  SORTIE :
 *      Aucune
    Expication:
    production d'une note
    utilise la variable volume définit par le potar 3
*/
void joueNote(int laNote, int octave);


/*
 * changementValeurs_puis_MaJ4Proj : Permet d'actualiser la couleur des 4 projecteurs
 *  ENTREES :
 *      int r, int g, int b: le code rgb de la couleur à appliquer aux 4 projecteurs
 *  SORTIE :
 *      Aucune, modification en place de la couleur des proj
*/
void changementValeurs_puis_MaJ4Proj(int r, int g, int b) ;


/*
 * max : Détermine le maximum entre 2 valeurs en héxadécimal
 *  ENTREES :
 *      char a, char b: les valeurs en héxadécimal à comparer
 *  SORTIE :
 *      la valeur maximale en héxadécimal (char)
*/
char max(char a, char b);


/*
 * attente: 
 *  ENTREES :
 *      un  entier qui définit le temps d'attente n*10 microseconde
 *  SORTIE :
 *      aucune 
 *     Les projecteurs ont besoin de recevoir une information toutes 
 *  les 10 ms sans quoi ils s’éteignent, donc la fonction attente 
 *  maintient le projecteur allumé dans la dernière couleur qu’on 
 *  lui a demandé 
 */
void attente(int n);


/*
 *preset2banqueA: 
 *  ENTREES :
 *      la toucheappuyée
 *  SORTIE :
		Aucune
	Explications :
	Allume les projecteurs dans l’enchaînement de couleur 
    correspondant à la touche appuyée (tous les proj ont toujours 
    la même couleur)
	Si on appuie sur une autre touche ou de nouveau sur la même 
    touche avant que la séquence lumineuse précédente ne soit finie 
    alors la séquence associée à la nouvelle touche est jouée à la 
    suite de celle en cours. 
	Cet enchaînement est implantée grâce à la variable maFileAttente 
    qui stocke la valeur de la deuxième touche appuyée (attention si 
    on appuie sur plus de deux touches à la suite seul les deux 
    premières seront jouées).
	Afin de stocker la deuxième note jouée dans maFileAttente nous 
    avons modifié dans DMX_MIDI.cpp la fonction ISR_midi_in	
	Nous effaçons de la file d’attente la note après avoir allumée 
    la première couleur de sa séquence, ainsi nous évitons de 
    détecter deux fois un appui long. 
 */
void preset2banqueA(char touche);


/*
 *preset2banqueA: 
 *  ENTREES :
 *      la toucheappuyée
 *  SORTIE :
		Aucune
    Explication :
    Chaque touche est asignée à une mélodie qui sera jouée, la mélodie est
    accompagnée d'une succession de lumières prédéfinies pour allier le côté
    BeatBox au Light contenu dans notre sujet
*/       
void preset2banqueB(char touche);
#endif