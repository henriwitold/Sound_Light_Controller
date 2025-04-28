/****************************************************************************/
/*  DMX_MIDI module library                                                 */
/****************************************************************************/
/*  Library - controleurs.cpp file                                          */
/*      MIDI notes are from 0 to 127                                        */
/*      MIDI notes are defined as follow :                                  */
/*          * CTL_M(char) : effect on spot ;                                */
/*              + bit 7 :   Dimmer                                          */
/*              + bit 6 :   RED                                             */
/*              + bit 5 :   GREEN                                           */
/*              + bit 4 :   BLUE                                            */
/*              + bit 3 :   WHITE                                           */
/*              + bit 2 :   AMBER                                           */
/*              + bit 1 :   UV                                              */
/*              + bit 0 :   not used yet                                    */
/*          * CTL_L(char) : effect on spot ;                                */
/*              + bit 7 :   Pan                                             */
/*              + bit 6 :   Tilt                                            */
/*              + bit 5 :   Speed                                           */
/*              + bit 4 :   Strobe                                          */
/*              + bit 3 :   not used yet                                    */
/*              + bit 2 :   not used yet                                    */
/*              + bit 1 :   not used yet                                    */
/*              + bit 0 :   not used yet                                    */
/*          * C1 to C16 (char) : value to affect to each type of CTL_M or L */
/*                                                                          */
/*      MIDI control changes CC are from 0 to 127                           */
/*      MIDI controls are defined as follow :   TO DO                            */
/*          * CTL_M(char) : effect on spot ;                                */
/*              + bit 7 :   Dimmer                                          */
/*              + bit 6 :   RED                                             */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*  Tested on Nucleo-L476RG                                 */
/****************************************************************************/

#include    "controleurs.h"

char    notes[MIDI_NOTES_NB][MIDI_NOTES_GROUPS][MIDI_NOTES_CHAN] = {0};

/* Functions */
/* initialisation of notes */
void initController(void){
    for(int j = 0; j < MIDI_NOTES_NB; j++){
        for(int g = 0; g < MIDI_NOTES_GROUPS; g++){
            for(int i = 0; i < MIDI_NOTES_CHAN; i++){
                notes[j][g][i] = 0;
            }
        }
    }
    
    /* Note 0 */
    // Groupe 0
    notes[0][0][MIDI_CTL_CTL_M] = 0b11110000;
    notes[0][0][MIDI_CTL_CTL_L] = 0b00000000;
    notes[0][0][MIDI_CTL_DIM] = 255;
    notes[0][0][MIDI_CTL_GREEN] = 0; 
    notes[0][0][MIDI_CTL_BLUE] = 0; 
    notes[0][0][MIDI_CTL_RED] = 255;  
    // Groupe 1
    notes[0][1][MIDI_CTL_CTL_M] = 0b11110000;
    notes[0][1][MIDI_CTL_CTL_L] = 0b00000000;
    notes[0][1][MIDI_CTL_DIM] = 255;
    notes[0][1][MIDI_CTL_GREEN] = 120; 
    notes[0][1][MIDI_CTL_BLUE] = 0; 
    notes[0][1][MIDI_CTL_RED] = 255;  

    /* Note 1 */
    // Groupe 0
    notes[1][0][MIDI_CTL_CTL_M] = 0b11110000;
    notes[1][0][MIDI_CTL_CTL_L] = 0b00000000;
    notes[1][0][MIDI_CTL_DIM] = 255;
    notes[1][0][MIDI_CTL_BLUE] = 255; 
    notes[1][0][MIDI_CTL_RED] = 255; 
    notes[1][0][MIDI_CTL_GREEN] = 0;
    // Groupe 1    
    notes[1][1][MIDI_CTL_CTL_M] = 0b11110000;
    notes[1][1][MIDI_CTL_CTL_L] = 0b00000000;
    notes[1][1][MIDI_CTL_DIM] = 255;
    notes[1][1][MIDI_CTL_BLUE] = 255; 
    notes[1][1][MIDI_CTL_RED] = 0; 
    notes[1][1][MIDI_CTL_GREEN] = 0;   
    
    /* Note 2 */
    // Groupe 0
    notes[2][0][MIDI_CTL_CTL_M] = 0b11110000;
    notes[2][0][MIDI_CTL_CTL_L] = 0b00000000;
    notes[2][0][MIDI_CTL_DIM] = 255;
    notes[2][0][MIDI_CTL_GREEN] = 255; 
    notes[2][0][MIDI_CTL_BLUE] = 0; 
    notes[2][0][MIDI_CTL_RED] = 0;    
    // Groupe 1    
    notes[2][1][MIDI_CTL_CTL_M] = 0b11110000;
    notes[2][1][MIDI_CTL_CTL_L] = 0b00000000;
    notes[2][1][MIDI_CTL_DIM] = 255;
    notes[2][1][MIDI_CTL_GREEN] = 0; 
    notes[2][1][MIDI_CTL_BLUE] = 50; 
    notes[2][1][MIDI_CTL_RED] = 200;   

}
    
