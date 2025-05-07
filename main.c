#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"

int main(void){
    lista_att l=nuova_lista_att();
    int scelta;
    char c;
    
    do{
    printf("Pianifica e monitora il tuo studio!\n");
    printf("1. Aggiungi nuova attività.\n");
    printf("2. Elimina un'attività.\n");
    printf("3. Aggiorna il progresso di un'attività.\n");
    printf("4. Stampa un report settimanale delle tue attività.\n");
    printf("0. Per uscire dal programma.");
    printf("Inserisci il numero corrispondente alla tua scelta: ");
    scanf("%d", &scelta);

    // pulizia input buffer.     
    while ((c = getchar()) != '\n');
    system("clear");

    switch(scelta){
        case 1:
            
            l=nuova_attivita(const char *nome, const char *descrizione, const char *data_scadenza, int priorita, int t_stimato, int t_trascorso, lista_att l);
        break; }
        case 2:

        case 3:

        case 4:

        case 0:
    
        default: 
    }

    //libera memoria:

    return 0;
}