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
    printf("0. Per uscire dal programma.\n");
    printf("Inserisci il numero corrispondente alla tua scelta: ");
    scanf("%d", &scelta);
    
    while ((c=getchar())!='\n'); // pulizia input buffer.     
    system("clear");

    switch(scelta){
        case 1: aggiungi_attivita(l);
                break;
        case 2: rimuovi_attivita(l);
                break;
        case 3: aggiornamento_progresso(l);
                break;
        case 4: report_settimanale(l);
                break;
        case 0: printf("Chiusura programma in corso... \n");
                break;    
        default: printf("Scelta non valida, riprova.\n");
    }
    } while(scelta!=0);

    //libera memoria allocata dinamicamente della lista:
    libera_memoria(&l);
    return 0;
}