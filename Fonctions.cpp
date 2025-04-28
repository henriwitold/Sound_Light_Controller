#include "Fonctions.h"
#include "DMX_MIDI.h"
#include "projecteurs.h"
#include "controleurs.h"
#include "melody.h"

int     Valeur_spots[7]; //prend les valeurs que revcoivent les proj
int     Spot[7]; //stocke les valeurs des proj en-dehors des strobe
int     tab_Intensite[4];
int     Intensite1Inter = 0;
int     Intensite2Inter = 0;
int     Intensite3Inter = 0;
int     Intensite4Inter = 0;
int     IntensiteTotale = 0;
int     tempo;  // nombre de demi-temps par seconde
int     Frequence;
int     Couleur;
float   volume = 0.0;
bool    Strobe;



void ChangementValeurs(int val1, int val2, int val3, int val4, int val5, int val6, int val7)
{
	int val[7] = {val1,val2,val3,val4,val5,val6,val7};
	for(int i = 0; i < 7; i++){
        Valeur_spots[i] = val[i];}
    if(val1 < 200){ //ie non strobe
        for(int i = 0; i < 7; i++){
            Spot[i] = Valeur_spots[i];}} //Spot[i] permet de stocker la couleur pour la retrouver après le strobe 
}

char max(char a, char b){
    if (a > b){return a;}
    else {return b;}
}

void MaJProjecteurs(int projecteur) //permet d'appliquer le mode encodé dans Valeur_spots au procteur donné en argument
{  
	for(int i=0; i < 7; i++){
        dmx_data[32+i + 8*projecteur] = Valeur_spots[i];}
}

void attente(int n){
    for(int i = 0; i < n; i++){
        wait_us(10);
        updateDMX();}
}

void RGBColor(char touche)
{
    tempo = 256;
    if(touche == 0x01)
    {   
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],255,0,0);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(0,2);
        else{
            sortieSon.period(1.0/note[0]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x02)
    {   
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],255,127,0);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(1,2);
        else{
            sortieSon.period(1.0/note[1]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x03)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],127,255,0);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(2,2);
        else{
            sortieSon.period(1.0/note[2]/(2 * 1.0));
            sortieSon = volume;}
    }   
    else if(touche == 0x04)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],0,255,0);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(3,2);
        else{
            sortieSon.period(1.0/note[3]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x05)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],255,0,127);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(4,2);
        else{
            sortieSon.period(1.0/note[4]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x06)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],255,127,127);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(5,2);
        else{
            sortieSon.period(1.0/note[5]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x07)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],127,255,127);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(6,2);
        else{
            sortieSon.period(1.0/note[6]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x08)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],0,255,127);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(7,2);
        else{
            sortieSon.period(1.0/note[7]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x09)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],127,0,255);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(8,2);
        else{
            sortieSon.period(1.0/note[8]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x0A)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],127,127,255);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(9,2);
        else{
            sortieSon.period(1.0/note[9]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x0B)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],0,127,127);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(10,2);
        else{
            sortieSon.period(1.0/note[10]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x0C)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],127,127,0);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(11,2);
        else{
            sortieSon.period(1.0/note[11]/(2 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x0D)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],0,0,255);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(5,3);
        else{
            sortieSon.period(1.0/note[5]/(3 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x0E)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],0,127,255);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(6,3);
        else{
            sortieSon.period(1.0/note[6]/(3 * 1.0));
            sortieSon = volume;}
        
    }
    else if(touche == 0x0F)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],127,0,127);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(7,3);
        else{
            sortieSon.period(1.0/note[7]/(3 * 1.0));
            sortieSon = volume;}
    }
    else if(touche == 0x10)
    {
        for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],255,255,255);
            MaJProjecteurs(i);}
        if(midi_data[0] == 0x90)
            joueNote(8,3);
        else{
            sortieSon.period(1.0/note[8]/(3 * 1.0));
            sortieSon = volume;}
    }
}

void RGBColorIndividuel(char touche)
{
    if(touche == 0x01)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 255, 0, 0);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[0]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x02)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 255, 0, 0);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[0]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x03)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 255, 0, 0);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[0]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x04)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 255, 0, 0);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[0]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x05)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 0, 255, 0);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[2]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x06)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 0, 255, 0);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[2]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x07)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 0, 255, 0);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[2]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x08)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 0, 255, 0);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[2]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x09)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 0, 0, 255);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[4]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0A)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 0, 0, 255);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[4]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0B)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 0, 0, 255);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[4]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0C)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 0, 0, 255);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[4]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0D)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 255, 255, 255);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[5]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0E)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 255, 255, 255);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[5]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0F)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 255, 255, 255);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[5]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x10)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 255, 255, 255);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[5]/(2 * 1.0));
        sortieSon = volume;
    }
}

void RJOCColorIndividuel(char touche)
{
    if(touche == 0x01)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 0, 255, 255);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[7]/(2 * 1.0));
        sortieSon = volume;
        
    }
    else if(touche == 0x02)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 0, 255, 255);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[7]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x03)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 0, 255, 255);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[7]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x04)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 0, 255, 255);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[7]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x05)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 255, 20, 147);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[9]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x06)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 255, 20, 147);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[9]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x07)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 255, 20, 147);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[9]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x08)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 255, 20, 147);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[9]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x09)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 255, 69, 0);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[11]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0A)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 255, 69, 0);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[11]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0B)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 255, 69, 0);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[11]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0C)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 255, 69, 0);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[11]/(2 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0D)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[0], 255, 215, 0);
        MaJProjecteurs(0);
        sortieSon.period(1.0/note[5]/(3 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0E)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[1], 255, 215, 0);
        MaJProjecteurs(1);
        sortieSon.period(1.0/note[5]/(3 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x0F)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[2], 255, 215, 0);
        MaJProjecteurs(2);
        sortieSon.period(1.0/note[5]/(3 * 1.0));
        sortieSon = volume;
    }
    else if(touche == 0x10)
    {
        ChangementValeurs(10, 0, 0, tab_Intensite[3], 255, 215, 0);
        MaJProjecteurs(3);
        sortieSon.period(1.0/note[5]/(3 * 1.0));
        sortieSon = volume;
    }
}

void Potar1(char potar, char intensite){
    if (potar == 0x01)
    {
        if (intensite < 0x0d){ //teste pour savoir si on est dans le cinquième inférieur
            IntensiteTotale = 0;}
        else{
            IntensiteTotale = (intensite - 0x0d)*2;} //proj monte jusqu'à 127 alors que proj 256
    }
    else if (potar == 0x02)
    {
        if (intensite < 0x0d){
            Intensite1Inter = 0;}
        else{
            Intensite1Inter = (intensite - 0x0d)*2;}
    }
    else if (potar == 0x03)
    {
        if (intensite < 0x0d){
            Intensite2Inter = 0;}
        else{
            Intensite2Inter = (intensite - 0x0d)*2;}
    }
    else if (potar == 0x04)
    {
        if (intensite < 0x0d){
            Intensite3Inter = 0;}
        else{
            Intensite3Inter = (intensite - 0x0d)*2;}
    }
    else if (potar == 0x05)
    {
        if (intensite < 0x0d){
            Intensite4Inter = 0;}
        else{
            Intensite4Inter = (intensite - 0x0d)*2;}
    }
    //le potar 0x01 ie celui à gauche, fixe le minimum d'intensité des 4 proj
    tab_Intensite[0] = max(IntensiteTotale,Intensite1Inter); 
    tab_Intensite[1] = max(IntensiteTotale,Intensite2Inter);
    tab_Intensite[2] = max(IntensiteTotale,Intensite3Inter);
    tab_Intensite[3] = max(IntensiteTotale,Intensite4Inter);

    //
    for(int i = 0; i < 7; i++){
        Valeur_spots[i] = Spot[i];} 
    if (Strobe == false)
    {   
        for (int i = 0; i < 4; i++ )
        {
            Valeur_spots[3] = tab_Intensite[i];
            MaJProjecteurs(i);
        }
    }
    
}

int ProjDataVersProjNum(char touche)
{
    if (touche == 0x01 or touche== 0x05 or touche== 0x09 or touche== 0x0D){ 
         return(0);}
    else if (touche == 0x02 or touche== 0x06 or touche== 0x0A or touche== 0x0E){
         return(1);}
    else if (touche == 0x03 or touche== 0x07 or touche== 0x0B or touche== 0x0F){
         return(2);}
    return(3);
}

void Potar2(char potar, char intensite){
	if(potar == 0x06){//commande du potar6
    //le potar6 commande la fréquence du strobe
		if(intensite < 0x0d) //teste si dans le cinquième inférieure
        { //donc pas de strobe on allume comme précédemment
			Strobe = false;
            for(int i = 0; i < 7; i++){
                Valeur_spots[i] = Spot[i];}
            for (int i = 0; i < 4; i++){
            Valeur_spots[3] = tab_Intensite[i];
            MaJProjecteurs(i);}}
        else if(intensite >= 0x0d)
        {
			Strobe = true;
			Frequence = intensite * 2;
            ChangementValeurs(201, Couleur, Frequence, 0, 0, 0, 0); //code du strobe
            for (int i = 0; i < 4; i++)
                MaJProjecteurs(i);
        
		}
	}
	if(potar == 0x07) //commande du potar7
    //le potar7 commande la couleur du strobe: 
    // quand on change la valeur de l'emplacement couleur dans les données qu'on envoie il y a 2 modes
    // inférieur à 40 pour cent, les couleurs changent régulièrement plus ou moins vite
    //supérieur à 40 pour cent, la couleur reste fixe quand on augmente le potar la couleur change: rouge, vert, bleu, jaune, bleu lagoon, change tous les 10 pour cent
		Couleur = intensite;
        if (Strobe == true)
        {
            ChangementValeurs(201, Couleur, Frequence, 0, 0, 0, 0);
            for (int i = 0; i < 4; i++)
                MaJProjecteurs(i);
        }
    if(potar == 0x08)
    {
        volume = intensite*0.5/3840.0;
    }
        
}

void Potar3(char potar, char intensite)
{
    if(potar == 0x03)
    {
        volume = intensite*0.5/3840.0;
    }
    if(potar == 0x02)
    {
        tempo = 127 + intensite*4;
    }
}

// fréquence associée à chaque note
// do, do#, ré, ré#, mi, fa, fa#, sol, sol#, la, la#, si
float note[12]= {65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98.00, 103.83, 110.00, 116.54, 123.47};

// chaque note de la mélodie comporte 3 paramètres:
// note (de 0 à 11:  0 pour do, 1 pour do#, etc)
// octave (1 à 3)
// durée (1 pour croche, 2 pour noire, 3 noire pointée, 4 pour blanche askip)



void joueNote (int laNote, int octave)
{
    sortieSon.period(1.0/note[laNote]/(octave * 1.0));
    sortieSon = volume; //rapport cyclique 50% :  volume maximal
    wait_us(1000000*2*.9*60.0/tempo); 
    sortieSon=0.0; // rapport cyclique 0%:  volume nul
    wait_us(1000000*2*.1*60.0/tempo); // court silence entre deux notes consécutives
}

/*
int getNum(char ch)
{
    int num = 0;
    if (ch >= '0' && ch <= '9') {
        num = ch - 0x30;
    }
    else {
        switch (ch) {
        case 'A':
        case 'a':
            num = 10;
            break;
        case 'B':
        case 'b':
            num = 11;
            break;
        case 'C':
        case 'c':
            num = 12;
            break;
        case 'D':
        case 'd':
            num = 13;
            break;
        case 'E':
        case 'e':
            num = 14;
            break;
        case 'F':
        case 'f':
            num = 15;
            break;
        default:
            num = 0;
        }
    }
    return num;
}*/

void changementsValeurs_puis_MaJ4Proj(int r, int g, int b){

      for(int i=0; i<4; i++){
            ChangementValeurs(10,0,0,tab_Intensite[i],r ,g ,b);
            MaJProjecteurs(i);}

}

void preset2banqueA(char touche)
{    
    if (touche == 0x01){
        changementsValeurs_puis_MaJ4Proj(127,0,127);
        attente(7 - tempo / 100);
        maFileAttente = 0x00;
        joueNote(0,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,0);
        attente(7 - tempo / 100);
        joueNote(4,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,127);
        attente(7 - tempo / 100);
        joueNote(7,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
    }
    if (touche == 0x02){ 
        changementsValeurs_puis_MaJ4Proj(255,69,0);
        attente(7 - tempo / 100);
        joueNote(2,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,255,255);
        attente(7 - tempo / 100);
        joueNote(6,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,255);
        attente(7 - tempo / 100);
        joueNote(9,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);  
    }
    if (touche == 0x03){ 
        changementsValeurs_puis_MaJ4Proj(127,255,0);
        attente(7 - tempo / 100);
        maFileAttente = 0x00;
        joueNote(4,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,255,255);
        attente(7 - tempo / 100);
        joueNote(8,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,127,255);
        attente(7 - tempo / 100);
        joueNote(11,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
    }
    if (touche == 0x04){
        changementsValeurs_puis_MaJ4Proj(0,255,0);
        attente(7 - tempo / 100);
        joueNote(5,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,255);
        attente(7 - tempo / 100);
        joueNote(9,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,255);
        attente(7 - tempo / 100);
        joueNote(0,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
    }
    if (touche == 0x05){
        changementsValeurs_puis_MaJ4Proj(127,0,127);
        attente(7 - tempo / 100);
        joueNote(0,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,0);
        attente(7 - tempo / 100);
        joueNote(4,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,127);
        attente(7 - tempo / 100);
        joueNote(7,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0, 0, 255);
        attente(7 - tempo / 100);
        joueNote(0,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
    }
    if (touche == 0x06){
        changementsValeurs_puis_MaJ4Proj(255,69,0);
        attente(7 - tempo / 100);
        joueNote(2,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,255,255);
        attente(7 - tempo / 100);
        joueNote(6,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,255);
        attente(7 - tempo / 100);
        joueNote(9,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,0,255);
        attente(7 - tempo / 100);
        joueNote(2,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
    }
    if (touche == 0x07){
        changementsValeurs_puis_MaJ4Proj(127,255,0);
        attente(7 - tempo / 100);
        joueNote(4,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,255,255);
        attente(7 - tempo / 100);
        joueNote(8,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,127,255);
        attente(7 - tempo / 100);
        joueNote(11,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,0,127);
        attente(7 - tempo / 100);
        joueNote(5,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
    }
    if (touche == 0x08){
        changementsValeurs_puis_MaJ4Proj(0,255,0);
        attente(7 - tempo / 100);
        joueNote(5,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,255,255);
        attente(7 - tempo / 100);
        joueNote(9,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,255);
        attente(7 - tempo / 100);
        joueNote(0,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,127,127);
        attente(7 - tempo / 100);
        joueNote(5,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x09){
        changementsValeurs_puis_MaJ4Proj(127,0,127);
        attente(7 - tempo / 100);
        joueNote(0,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,0);
        attente(7 - tempo / 100);
        joueNote(3,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,127);
        attente(7 - tempo / 100);
        joueNote(7,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x0A){
        changementsValeurs_puis_MaJ4Proj(255,69,0);
        attente(7 - tempo / 100);
        joueNote(2,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,255,0);
        attente(7 - tempo / 100);
        joueNote(5,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,255);
        attente(7 - tempo / 100);
        joueNote(9,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x0B){
        changementsValeurs_puis_MaJ4Proj(27,255,0);
        attente(7 - tempo / 100);
        joueNote(4,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,127);
        attente(7 - tempo / 100);
        joueNote(7,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,127,255);
        attente(7 - tempo / 100);
        joueNote(11,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x0C){
        changementsValeurs_puis_MaJ4Proj(0,255,0);
        attente(7 - tempo / 100);
        joueNote(5,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,255,255);
        attente(7 - tempo / 100);
        joueNote(8,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,255);
        attente(7 - tempo / 100);
        joueNote(0,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x0D){
        changementsValeurs_puis_MaJ4Proj(127,0,127);
        attente(7 - tempo / 100);
        joueNote(0,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,0);
        attente(7 - tempo / 100);
        joueNote(3,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,127);
        attente(7 - tempo / 100);
        joueNote(7,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,255);
        attente(7 - tempo / 100);
        joueNote(0,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x0E){
        changementsValeurs_puis_MaJ4Proj(255,69,0);
        attente(7 - tempo / 100);
        joueNote(2,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,255,0);
        attente(7 - tempo / 100);
        joueNote(5,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,255);
        attente(7 - tempo / 100);
        joueNote(9,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,0,255);
        attente(7 - tempo / 100);
        joueNote(2,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x0F){
        changementsValeurs_puis_MaJ4Proj(127,255,0);
        attente(7 - tempo / 100);
        joueNote(4,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,255,127);
        attente(7 - tempo / 100);
        joueNote(7,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,127,255);
        attente(7 - tempo / 100);
        joueNote(11,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,0,127);
        attente(7 - tempo / 100);
        joueNote(4,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
     }
    if (touche == 0x10){
        changementsValeurs_puis_MaJ4Proj(0,255,0);
        attente(7 - tempo / 100);
        joueNote(5,2);
        maFileAttente = 0x00;
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(127,127,255);
        attente(7 - tempo / 100);
        joueNote(8,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,255);
        attente(7 - tempo / 100);
        joueNote(0,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(255,127,127);
        attente(7 - tempo / 100);
        joueNote(4,2);
        attente(7 - tempo / 100);
        changementsValeurs_puis_MaJ4Proj(0,0,0);
    }
    if (touche >= 0x11)
        maFileAttente = 0x00;
    debug_pc.printf("File d'attente : %2.2hhx\n\r", maFileAttente);
}

void preset2banqueB(char touche)
{
    if(touche == 0x01)
        joueMelodie(11, clairlune, clairluneRGB);
    else if(touche == 0x02)
        joueMelodie(15, supop, supopRGB);
    else if(touche == 0x03)
        joueMelodie(8, symphonie, symphonieRGB);
    else if(touche == 0x04)
        joueMelodie(7, mario, marioRGB);
    else if(touche == 0x05)
        joueMelodie(20, megalovania, megalovaniaRGB);
    else if(touche == 0x06)
        joueMelodie(5, thriller, thrillerRGB);
    else if(touche == 0x07)
        joueMelodie(9, christmas, christmasRGB);
    else if(touche == 0x08)
        joueMelodie(6, papanoel, papanoelRGB);
    else if(touche == 0x09)
        joueMelodie(8, wakemeup, wakemeupRGB);
    else if(touche == 0x0A)
        joueMelodie(16, rickroll, rickrollRGB);
    else if(touche == 0x0B)
        joueMelodie(9, marcheimp, marcheimpRGB);
    else if(touche == 0x0C)
        joueMelodie(16, starwars, starwarsRGB);
    else if(touche == 0x0D)
        joueMelodie(10, jurassic, jurassicRGB);
    else if(touche == 0x0E)
        joueMelodie(17, panthrose, panthroseRGB);
    else if(touche == 0x0F)
        joueMelodie(10, simpson, simpsonRGB);
    else if(touche == 0x10)
        joueMelodie(10, gadget, gadgetRGB);
}