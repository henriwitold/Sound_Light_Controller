/************************************************************************************/
/*  Test DMX512 + MOD-24LR / nrf24L01                                               */
/************************************************************************************/
/*                                                                                  */
/************************************************************************************/
/*  Test réalisé sur Nucléo-L476RG                                                  */
/************************************************************************************/

#include "Fonctions.h"
#include "mbed.h"
#include "DMX_MIDI.h"
#include "projecteurs.h"
#include "controleurs.h"
#include "melody.h"

//TEST

Serial          debug_pc(USBTX, USBRX);
InterruptIn     bp_int(USER_BUTTON);
DigitalOut      debug_out(D13);
PwmOut          sortieSon(PB_1);

// Main
int main() {
    debug_pc.baud(115200); // indique la fréquence d'envoi des données : à indiquer dans TeraTerm
    debug_pc.printf("Test\r\n");

    //Initialisation de nos variables

    bool Allumage = false; //permet de savoir si la LED était précedemment allumée
    char lastInput; //déclare tableau de char de taille 2 qui stockera l'historique des données reçues
    maFileAttente = 0x00;

    // Initialisation périphériques
    initDMX();
    initMIDI();
    //initMIDI2();
    initProjectors();
    //initController();
    PwmOut sortieSon(PB_1);  // la pin PB_1 émettra la mélodie

    ChangementValeurs(15, 0, 0, 100, 0, 127, 127); //à l'allumage les projo s'allument en mode statique bleu océan
    for(int i=0; i<4; i++){
        MaJProjecteurs(i);}

    for (int i; i<4; i++)
        tab_Intensite[i] = 127;
    
    tempo = 250;
    volume = 2*0.5/3840.0;

    while(1)
    {
        if(isNoteMIDIdetected()){ // on détecte si une touche a été activée
            if(!Strobe && midi_data[0] < 0x94 && midi_data[0] != 0x84)
            {
                if(midi_data[0] == 0x90){ //9 appui sur une note //0 Code instru 1 (Pad Bank A) 
                if(lastInput == midi_data[1]) // teste pour savoir si on appuie sur la même touche que précédemment
                    Allumage = !Allumage; 
                else 
                    Allumage = true;
                if(Allumage){
                   RGBColor(midi_data[1]);} //on allume tous les spots avec la couleur souhaitée correspondant à la touche appuyée
                else //on éteint les spots
                {
                    for(int i=0; i<4; i++){
                        ChangementValeurs(10,0,0,0,0,0,0);
                        MaJProjecteurs(i);}
                }

                lastInput = midi_data[1]; // mise à jour de lastInput (seul le Pad Bank A a besoin d'une mémoire c'est pour cela que cette commande n'apparaît que là)
                }
                else if (midi_data[0] == 0x80){ //on lâche la touche donc selon les règles du PadBankA on ne change rien à l'allumage des spots
                }
                else if(midi_data[0] == 0x91){ //9 appui sur une note //1 Code instru 2 (Pad Bank B)
                    RGBColor(midi_data[1]); //on allume tous les spots avec la couleur souhaitée correspondant à la touche appuyée
                }
                else if(midi_data[0] == 0x81){ //on éteint tous les spots lorque la touche est relâchée
                    for(int i=0; i<4; i++){
                        ChangementValeurs(10,0,0,0,0,0,0);
                        MaJProjecteurs(i);}
                        sortieSon = 0.0;
                }
                else if(midi_data[0] == 0x92){ //9 appui sur une note //2 Code instru 3 (Pad Bank C)
                    RGBColorIndividuel(midi_data[1]); //les spots sont commandés de manière individuelle cf commentaire sur RGBColorIndividuel
                }
                else if(midi_data[0] == 0x82){ //on éteint TOUS les spots lorque la touche est relâchée pas voulu à modifier !!!
                    ChangementValeurs(10, 0, 0, 0, 0, 0, 0);
                    MaJProjecteurs(ProjDataVersProjNum(midi_data[1]));
                    sortieSon = 0.0;
                }
                else if(midi_data[0] == 0x93){ //9 appui sur une note //3 Code instru 4 (Pad Bank D)
                    //même fonctionnement que Pad Bank C mais avec des couleurs différentes d'où l'utilisation de RJOCColorIndividuel au lieu de RGBColorIndividuel
                    RJOCColorIndividuel(midi_data[1]); 
                }
                else if(midi_data[0] == 0x83){
                    ChangementValeurs(10, 0, 0, 0, 0, 0, 0);
                    MaJProjecteurs(ProjDataVersProjNum(midi_data[1]));
                    sortieSon = 0.0;
                }                
            }
            else if(midi_data[0] == 0x94)
            {
                while(maFileAttente != 0x00){
                    preset2banqueA(maFileAttente);}
                    debug_pc.printf("%2.2hhx\n\r",maFileAttente);
            }
            else if(midi_data[0] == 0x95)
            {
                preset2banqueB(midi_data[1]);
                debug_pc.printf("%2.2hhx\n\r",midi_data[1]);
            }
            
            debug_pc.printf("%2.2hhx ", midi_data[0]);
            debug_pc.printf("%2.2hhx\n\r", midi_data[1]);


            resetNoteMIDI();
        }

        wait_us(10);
        updateDMX();
    }

}