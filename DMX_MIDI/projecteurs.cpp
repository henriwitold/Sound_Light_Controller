/****************************************************************************/
/*  DMX_MIDI module library                                                 */
/****************************************************************************/
/*  Library - projecteurs.cpp file                                          */
/*      Spots are defined as follow :                                       */
/*          * ADR  (uint_16) : DMX first address                            */
/*          * TYPE (char) : (L)yre, (S)canner, (P)ar, (R)gbawu, Stro(B)e    */
/*          * ID   (char) : unique identifier of the spot                   */
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
/*  Tested on Nucleo-L476RG                              */
/****************************************************************************/

#include    "projecteurs.h"
#include    "controleurs.h"

/* Global Variables */
char        projecteurs[PROJ_NB_TOTAL][DMX_PROJ_NB_DATA];
int         groups[MIDI_NOTES_GROUPS];


/* Functions */
/* initialisation of spots */
void initProjectors(void){
    for(int k = 0; k < MIDI_NOTES_GROUPS; k++){
        groups[k] = 0;
    }
    for(int j = 0; j < PROJ_NB_TOTAL; j++){
        for(int i = 0; i < DMX_PROJ_NB_DATA; i++){
            projecteurs[j][i] = 0;
        }
    }
    
    /* LED PARTY Eurolite */
    projecteurs[0][DMX_PROJ_ADR] = 0;
    projecteurs[0][DMX_PROJ_ADR + 1] = 1;
    projecteurs[0][DMX_PROJ_TYPE] = 'R';
    projecteurs[0][DMX_PROJ_ID] = 1;
    projecteurs[0][DMX_PROJ_GROUP] = 1;
    projecteurs[0][DMX_PROJ_DIM] = 5;
    projecteurs[0][DMX_PROJ_RED] = 1;
    projecteurs[0][DMX_PROJ_GRN] = 2;
    projecteurs[0][DMX_PROJ_BLU] = 3;
    projecteurs[0][DMX_PROJ_WHT] = 4;
    projecteurs[0][DMX_PROJ_STB] = 6;
    groups[1] = 0b1;
    /* LED PARTY Eurolite */
    projecteurs[1][DMX_PROJ_ADR] = 0;
    projecteurs[1][DMX_PROJ_ADR + 1] = 9;
    projecteurs[1][DMX_PROJ_TYPE] = 'R';
    projecteurs[1][DMX_PROJ_ID] = 2;
    projecteurs[1][DMX_PROJ_GROUP] = 2;
    projecteurs[1][DMX_PROJ_DIM] = 5;
    projecteurs[1][DMX_PROJ_RED] = 1;
    projecteurs[1][DMX_PROJ_GRN] = 2;
    projecteurs[1][DMX_PROJ_BLU] = 3;
    projecteurs[1][DMX_PROJ_WHT] = 4;
    projecteurs[1][DMX_PROJ_STB] = 6;
    groups[2] = 0b10;
}

/* get adress of a spot with number */
uint16_t getProjAddress(char num){   return ((projecteurs[num][DMX_PROJ_ADR] << 8) + projecteurs[num][DMX_PROJ_ADR + 1]);    }
/* get channel of green of a spot with number */
char getProjGroup(char num){   return projecteurs[num][DMX_PROJ_GROUP];    }
/* get channel of dimmer of a spot with number */
char getProjDimmer(char num){   return projecteurs[num][DMX_PROJ_DIM];    }
/* get channel of red of a spot with number */
char getProjRed(char num){   return projecteurs[num][DMX_PROJ_RED];    }
/* get channel of blue of a spot with number */
char getProjBlue(char num){   return projecteurs[num][DMX_PROJ_BLU];    }
/* get channel of green of a spot with number */
char getProjGreen(char num){   return projecteurs[num][DMX_PROJ_GRN];    }

/* update spots with MIDI notes */ // TO TEST AND FINISH + TEST TIMING
void updateProjFromMidi(char note){
    // Finding Note and Light to update
    for(int grp = 0; grp < MIDI_NOTES_GROUPS; grp++){
        char ctl_M = notes[note][grp][MIDI_CTL_CTL_M];
        char ctl_L = notes[note][grp][MIDI_CTL_CTL_L];
        
        if((ctl_M != 0) || (ctl_L != 0)){
            int spots = groups[grp];
            if(spots != 0){
                // get lights to update
                for(int spot = 0; spot < PROJ_NB_TOTAL; spot++){
                    if((spots & 1) == 1){
                        updateProj(spot, note, grp, ctl_M, ctl_L);
                    }
                    spots = spots >> 1;
                }
            }
        }
    }
}

/* update a spot */ // TO TEST AND FINISH + TEST TIMING
void updateProj(char num, char note, char grp, char ctl_M, char ctl_L){
    char add = getProjAddress(num);  
    
    // Dimmer
    if((ctl_M & MIDI_CTL_DIM_MASK) == MIDI_CTL_DIM_MASK )
        dmx_data[getProjDimmer(num)+add-2] = notes[note][grp][MIDI_CTL_DIM];
    else
        dmx_data[getProjDimmer(num)+add-2] = 0;
    // Red
    if((ctl_M & MIDI_CTL_RED_MASK) == MIDI_CTL_RED_MASK )
        dmx_data[getProjRed(num)+add-2] = notes[note][grp][MIDI_CTL_RED];
    else
        dmx_data[getProjRed(num)+add-2] = 0;
    // Blue
    if((ctl_M & MIDI_CTL_BLUE_MASK) == MIDI_CTL_BLUE_MASK )
        dmx_data[getProjBlue(num)+add-2] = notes[note][grp][MIDI_CTL_BLUE];
    else
        dmx_data[getProjBlue(num)+add-2] = 0;
    // Green
    if((ctl_M & MIDI_CTL_GREEN_MASK) == MIDI_CTL_GREEN_MASK )
        dmx_data[getProjGreen(num)+add-2] = notes[note][grp][MIDI_CTL_GREEN];
    else
        dmx_data[getProjGreen(num)+add-2] = 0;    
}