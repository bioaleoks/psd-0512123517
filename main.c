/*File main.c
Interfaccia utente per il software per la gestione dello studio. 
Autore: Alessia Plaitano 
Data creazione: 26 Aprile 2025 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"
/* Non è incluso il file "mergesortList.h" poichè non è usato in
maniera esplicita nel main, ma da fz definite nel file "attivita.h",
che contiene già l'inclusione per "mergesortList.h". */

int main(void){
    lista_att l=nuova_lista_att();
    int scelta;
    char c;
    
    do{
        
        printf("\033[H\033[J");

        printf("*************************************\n");
        printf(" Pianifica e monitora il tuo studio!\n");
        printf("*************************************\n");
        printf("1. Aggiungi nuova attivita'.\n");
        printf("2. Elimina un'attivita'.\n");
        printf("3. Aggiorna il progresso di un'attivita'.\n");
        printf("4. Stampa un report settimanale delle tue attivita'.\n");
        printf("0. Per uscire dal programma.\n");
        printf("Inserisci il numero corrispondente alla tua scelta: ");
        scanf("%d", &scelta);

        while((c=getchar())!='\n');    
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch(scelta){
            case 1: l=aggiungi_attivita(l);
                    break;
            case 2: l=rimuovi_attivita(l);
                    break;
            case 3: aggiornamento_progresso(l);
                    break;
            case 4: report_settimanale(&l);
                    break;
            case 0: printf("Chiusura programma in corso... \n");
                    break;    
            default: printf("Scelta non valida, riprova.\n");
        }
        
        while((getchar())!='\n');
        
        //Pulizia schermo prima della prossima scelta dell'utente.
        printf("\nPremi un tasto per continuare...\n"); 
        getchar();
       

    } while(scelta!=0);

    libera_memoria(&l);
    return 0;
}