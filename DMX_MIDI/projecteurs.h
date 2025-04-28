/****************************************************************************/
/*  DMX_MIDI module library                                                 */
/****************************************************************************/
/*  Library - projecteurs.h file                                            */
/*      Spots are defined as follow :                                       */
/*          * TYPE (char) : (L)yre, (S)canner, (P)ar, (R)gbawu, Stro(B)e    */
/*          * ID   (char) : unique identifier of the spot                   */
/*          * ADR  (uint_16) : DMX first address                            */
/*          * GROUP(char) : group of the spots                              */
/*                                                                          */
/*          * DIM  (char) : channel used for DIMMER         - 0 if not used */
/*                                                                          */
/*          * RED  (char) : channel used for RED color      - 0 if not used */
/*          * GRN  (char) : channel used for GREEN color    - 0 if not used */
/*          * BLU  (char) : channel used for BLUE color     - 0 if not used */
/*          * WHT  (char) : channel used for WHITE color    - 0 if not used */
/*          * AMB  (char) : channel used for AMBER color    - 0 if not used */
/*          * UV   (char) : channel used for UV color       - 0 if not used */
/*                                                                          */
/*          * PAN  (char) : channel used for PAN moves      - 0 if not used */
/*          * TIL  (char) : channel used for TILT moves     - 0 if not used */
/*          * SPD  (char) : channel used for SPEED setup    - 0 if not used */
/*          * STB  (char) : channel used for STROBE function- 0 if not used */
/*                                                                          */
/****************************************************************************/
/*  Tested on Nucleo-L476RG                             */
/****************************************************************************/

#ifndef     PROJECTEURS_H_INCLUDED
#define     PROJECTEURS_H_INCLUDED

#include    "mbed.h"
#include    "DMX_MIDI.h"
#include    "controleurs.h"

#define     PROJ_NB_TOTAL       32

#define     DMX_PROJ_NB_DATA    16

#define     DMX_PROJ_ADR        0
#define     DMX_PROJ_TYPE       2
#define     DMX_PROJ_ID         3
#define     DMX_PROJ_GROUP      4
#define     DMX_PROJ_DIM        5
#define     DMX_PROJ_RED        6
#define     DMX_PROJ_GRN        7
#define     DMX_PROJ_BLU        8
#define     DMX_PROJ_WHT        9
#define     DMX_PROJ_AMB        10
#define     DMX_PROJ_UV         11
#define     DMX_PROJ_PAN        12
#define     DMX_PROJ_TIL        13
#define     DMX_PROJ_SPD        14
#define     DMX_PROJ_STB        15

/* Global Variables */
extern      char        projecteurs[PROJ_NB_TOTAL][DMX_PROJ_NB_DATA];

/* Functions */
/* initialisation of spots */
void initProjectors(void);

/* get adress of a spot with number */
uint16_t getProjAddress(char num);
/* get channel of green of a spot with number */
char getProjGroup(char num);
/* get channel of dimmer of a spot with number */
char getProjDimmer(char num);
/* get channel of red of a spot with number */
char getProjRed(char num);
/* get channel of blue of a spot with number */
char getProjBlue(char num);
/* get channel of green of a spot with number */
char getProjGreen(char num);
/* update spots */
void updateProjFromMidi(char  note);
/* update a spot */
void updateProj(char num, char note, char grp, char ctl_M, char ctl_L);

#endif