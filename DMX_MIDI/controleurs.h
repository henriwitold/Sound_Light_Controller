/****************************************************************************/
/*  DMX_MIDI module library                                                 */
/****************************************************************************/
/*  Library - controleurs.h file                                            */
/*      MIDI notes are from 0 to 127                                        */
/*          and MIDI CC controls are from 128 to 512                        */
/*      MIDI controls are defined as follow :                               */
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
/*                                                                          */
/****************************************************************************/
/*  Tested on Nucleo-L476RG                              */
/****************************************************************************/
/* Next upgrade : include CC controls */

#include    "mbed.h"
#include    "DMX_MIDI.h"

#define     MIDI_CONTROLS_NB        128
#define     MIDI_NOTES_NB           128
#define     MIDI_NOTES_GROUPS       16
#define     MIDI_NOTES_CHAN         18

#define     MIDI_CTL_CTL_M          0
#define     MIDI_CTL_CTL_L          1
#define     MIDI_CTL_DIM            2
#define     MIDI_CTL_RED            3
#define     MIDI_CTL_GREEN          4
#define     MIDI_CTL_BLUE           5
#define     MIDI_CTL_WHITE          6
#define     MIDI_CTL_AMBER          7
#define     MIDI_CTL_UV             8
#define     MIDI_CTL_M0             9
#define     MIDI_CTL_PAN            10
#define     MIDI_CTL_TILT           11
#define     MIDI_CTL_SPEED          12
#define     MIDI_CTL_STROBE         13
#define     MIDI_CTL_L3             14
#define     MIDI_CTL_L2             15
#define     MIDI_CTL_L1             16
#define     MIDI_CTL_L0             17

#define     MIDI_CTL_DIM_MASK       0b10000000
#define     MIDI_CTL_RED_MASK       0b01000000
#define     MIDI_CTL_GREEN_MASK     0b00100000
#define     MIDI_CTL_BLUE_MASK      0b00010000
#define     MIDI_CTL_WHITE_MASK     0b00001000
#define     MIDI_CTL_AMBER_MASK     0b00000100
#define     MIDI_CTL_UV_MASK        0b00000010
#define     MIDI_CTL_M0_MASK        0b00000001
#define     MIDI_CTL_PAN_MASK       0b10000000
#define     MIDI_CTL_TILT_MASK      0b01000000
#define     MIDI_CTL_SPEED_MASK     0b00100000
#define     MIDI_CTL_STROBE_MASK    0b00010000
#define     MIDI_CTL_L3_MASK        0b00001000
#define     MIDI_CTL_L2_MASK        0b00000100
#define     MIDI_CTL_L1_MASK        0b00000010
#define     MIDI_CTL_L0_MASK        0b00000001

/* Global variables */
/* controls : [number of possible notes values in MIDI][number of groups of light][number of commands] */
extern      char        notes[MIDI_NOTES_NB][MIDI_NOTES_GROUPS][MIDI_NOTES_CHAN];

/* Functions */
/* initialisation of controls */
void initController(void);