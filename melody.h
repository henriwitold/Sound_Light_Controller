#ifndef MELODY_H_INCLUDED
#define MELODY_H_INCLUDED

#include "mbed.h"
#include "Fonctions.h"

extern  int tempo;  // nombre de demi-temps par seconde
extern  float   note[12];
extern  PwmOut  sortieSon;

extern  int clairlune[11][3];
extern  int clairluneRGB[11][3];
extern  int supop[15][3];
extern  int supopRGB[15][3];
extern  int symphonie[8][3];
extern  int symphonieRGB[8][3];
extern  int mario[7][3];
extern  int marioRGB[7][3];
extern  int ymca[4][3];
extern  int ymcaRGB[4][3];
extern  int thriller[5][3];
extern  int thrillerRGB[5][3];
extern  int christmas[9][3];
extern  int christmasRGB[9][3];
extern  int papanoel[6][3];
extern  int papanoelRGB[6][3];
extern  int wakemeup[8][3];
extern  int wakemeupRGB[8][3];
extern  int rickroll[16][3];
extern  int rickrollRGB[16][3];
extern  int marcheimp[9][3];
extern  int marcheimpRGB[9][3];
extern  int starwars[16][3];
extern  int starwarsRGB[16][3];
extern  int jurassic[10][3];
extern  int jurassicRGB[10][3];
extern  int panthrose[17][3];
extern  int panthroseRGB[17][3];
extern  int simpson[10][3];
extern  int simpsonRGB[10][3];
extern  int gadget[10][3];
extern  int gadgetRGB[10][3];

void joueMelodie(int n, int melodie[n][3], int couleurs[n][3]);

#endif
