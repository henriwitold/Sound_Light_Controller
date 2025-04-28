/****************************************************************************/
/*  DMX_MIDI module library                                                 */
/*  Library - DMX_MIDI.cpp file                                             */
/****************************************************************************/
/*  Tested on Nucleo-L476RG                                 */
/****************************************************************************/

#include "DMX_MIDI.h"

/* Entrées - Sorties */
// DMX
Serial      dmx(PA_0, PA_1);
DigitalOut  out_tx(D5);
DigitalOut  start(D4);     //envoie des données
DigitalOut  enableDMX(D6);
// MIDI
Serial      midi(D8, D2);
// Analogiques
AnalogIn    CV_volume(PC_1);
AnalogIn    CV_pitch(PB_0);
AnalogIn    variationR(PC_0);
AnalogIn    variationG(PC_2);
AnalogIn    variationB(PC_3);

/* Variables globales */
char        dmx_data[SAMPLES] = {0};
int         rgb;
// Midi
char        cpt_midi;
char        new_data_midi, new_note_midi;
char        midi_data[3], note_data, velocity_data;
char        control_ch, control_value;
char        maFileAttente;


/* Variation de lumière douce - Projet Arts et Sciences */
const uint8_t vague[360]={
  0,   0,   0,   0,   0,   1,   1,   2,   2,   3,   4,   5,   6,   7,   8,   9, 
 11,  12,  13,  15,  17,  18,  20,  22,  24,  26,  28,  30,  32,  35,  37,  39, 
 42,  44,  47,  49,  52,  55,  58,  60,  63,  66,  69,  72,  75,  78,  81,  85, 
 88,  91,  94,  97, 101, 104, 107, 111, 114, 117, 121, 124, 127, 131, 134, 137, 
141, 144, 147, 150, 154, 157, 160, 163, 167, 170, 173, 176, 179, 182, 185, 188, 
191, 194, 197, 200, 202, 205, 208, 210, 213, 215, 217, 220, 222, 224, 226, 229, 
231, 232, 234, 236, 238, 239, 241, 242, 244, 245, 246, 248, 249, 250, 251, 251, 
252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 
252, 251, 251, 250, 249, 248, 246, 245, 244, 242, 241, 239, 238, 236, 234, 232, 
231, 229, 226, 224, 222, 220, 217, 215, 213, 210, 208, 205, 202, 200, 197, 194, 
191, 188, 185, 182, 179, 176, 173, 170, 167, 163, 160, 157, 154, 150, 147, 144, 
141, 137, 134, 131, 127, 124, 121, 117, 114, 111, 107, 104, 101,  97,  94,  91, 
 88,  85,  81,  78,  75,  72,  69,  66,  63,  60,  58,  55,  52,  49,  47,  44, 
 42,  39,  37,  35,  32,  30,  28,  26,  24,  22,  20,  18,  17,  15,  13,  12, 
 11,   9,   8,   7,   6,   5,   4,   3,   2,   2,   1,   1,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0};

/* Fonction d'initialisation de la liaison DMX */
void initDMX(void){
    dmx.baud(250000);
    dmx.format (8, SerialBase::None, 2);
    enableDMX = 0;
    // Initialisation canaux DMX
    for(int k = 0; k < SAMPLES; k++){
        dmx_data[k] = 0;
    }    
    updateDMX();
} 

/* Fonction de mise à jour de la sortie DMX */
void updateDMX(){
        enableDMX = 1;
        start = 1;      // /start
        out_tx = 0;     // break
        wait_us(88);    
        out_tx = 1;     // mb
        wait_us(8);     
        out_tx = 0;     // break
        start = 0;
        dmx.putc(0);     // Start
        for(int i = 0; i < SAMPLES; i++){
            dmx.putc(dmx_data[i]);     // data
        }
        wait_us(23000); // time between frame  
}

/* Fonction d'initialisation de la liaison MIDI */
void initMIDI(void){
    midi.baud(31250);
    midi.format(8, SerialBase::None, 1);
    midi.attach(&ISR_midi_in, Serial::RxIrq);
}
/* Fonction d'initialisation de la liaison MIDI - version beta */
void initMIDI2(void){
    debug_pc.baud(115200);
    debug_pc.format(8, SerialBase::None, 1);
    debug_pc.attach(&ISR_midi_in2, Serial::RxIrq);
}
/* Detection d'une note reçue en MIDI */
bool isNoteMIDIdetected(void){
    if(new_note_midi == 1)
        return true;
    else
        return false;
}
/* Note reçue en MIDI traitée */
void resetNoteMIDI(void){
    new_note_midi = 0;
}

/* Detection d'un controle reçu en MIDI */
bool isCCMIDIdetected(void){
    if(new_data_midi == 1)
        return true;
    else
        return false;
}
/* Controle reçu en MIDI traité */
void resetCCMIDI(void){
    new_data_midi = 0;
}

/* Renvoie la note reçue sur la liaison MIDI */
void resendNoteMIDI(void){
    midi.putc(MIDI_NOTE_ON);
    midi.putc(note_data);
    midi.putc(127);
}

/* Renvoie la note reçue sur la liaison MIDI - version beta */
void resendNoteMIDI2(void){
    debug_pc.putc(MIDI_NOTE_ON);
    debug_pc.putc(note_data);
    debug_pc.putc(127);
}
/* Joue une note sur la liaison MIDI */
void playNoteMIDI(char note, char velocity){
    midi.putc(MIDI_NOTE_ON);
    midi.putc(note);
    midi.putc(velocity);
}
/* Joue une note sur la liaison MIDI - version beta */
void playNoteMIDI2(char note, char velocity){
    debug_pc.printf("%x %x \r\n", note, velocity);
}

/* Stoppe une note sur la liaison MIDI */
void stopNoteMIDI(char note, char velocity){
    midi.putc(MIDI_NOTE_OFF);
    midi.putc(note);
    midi.putc(velocity);
}

/* Fonction d'appel à une variation de lumière en fonction d'un angle
    @out : R G B au format 24 bits
*/
int sineLED(int angle)
{
    return (vague[(angle+120)%360] << 16) + (vague[angle] << 8) + vague[(angle+240)%360];
}


/* Fonction d'interruption sur MIDI */
void ISR_midi_in(void){
    debug_out = !debug_out;
    char data = midi.getc();
    if(data >= 128)
        cpt_midi = 0;
    else
        cpt_midi++;
    midi_data[cpt_midi] = data;
    if(cpt_midi == 2){
        cpt_midi = 0;
        if((midi_data[0] >= 0x90 && midi_data[0] <= 0x95) || (midi_data[0] >= 0x80 && midi_data[0] <= 0x85)){
            if (midi_data[0] <= 0x95 && midi_data[0] != 0x84 && midi_data[0] != 0x94){
                new_note_midi = 1;
                note_data = midi_data[1];
                velocity_data = midi_data[2];
                maFileAttente = 0x00;
            }
            if(midi_data[0] == 0x94 && maFileAttente == 0x00){
                new_note_midi = 1;
                maFileAttente = midi_data[1];
            }
        }
        else{
            if(midi_data[0] >= 0xB0 && midi_data[0] <= 0xB5){
                new_data_midi = 1;
                control_ch = midi_data[1];
                control_value = midi_data[2];
                if(midi_data[0] == 0xB4){ //tous les potar sont codés comme instrument b4, vérif pas très utile normalement sur le preset EHI2M
                    if(midi_data[1] <= 0x05) //potar 1 à 5 commendent l'intensité via la fonction Po
                    {
                        Potar1(midi_data[1], midi_data[2]);
                    }
                    else if(midi_data[1] <= 0x08)
                    {
                        Potar2(midi_data[1], midi_data[2]);
                    }
                    resetCCMIDI();
                }
                if (midi_data[0] == 0xB5){
                    Potar3(midi_data[1], midi_data[2]);
                    resetCCMIDI();
                }
                debug_pc.printf("Potar");
                debug_pc.printf("%2.2hhx ", midi_data[1]);
                debug_pc.printf("%2.2hhx\n\r", midi_data[2]);
            }
        }
    }
}
/* Fonction d'interruption sur MIDI - version beta */
void ISR_midi_in2(void){
    debug_out = !debug_out;
    char data = debug_pc.getc();
    if(data >= 128)
        cpt_midi = 0;
    else
        cpt_midi++;
    midi_data[cpt_midi] = data;
    if(cpt_midi == 2){
        cpt_midi = 0;
        if(midi_data[0] == MIDI_NOTE_ON){ // || (midi_data[0] == MIDI_NOTE_OFF)){
            new_note_midi = 1;
            note_data = midi_data[1];
            velocity_data = midi_data[2];
        }
        else{
            if(midi_data[0] == MIDI_CC){
                new_data_midi = 1;
                control_ch = midi_data[1];
                control_value = midi_data[2];
            }
        }
    }
}