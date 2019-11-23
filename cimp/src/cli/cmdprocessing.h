#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "../load_save/load.h"
#include "../load_save/save.h"
#include "../sdlutils.h"


extern Uint8 R1,G1,B1;

extern int commande;
extern int commandeSelection;
extern Uint8 threshold;
extern long int R,G,B;
extern int valeurN;


/* Traitement des commandes*/
void process_command();
int edit_command(void * arg);

void print_help();
void print_help_edit();

