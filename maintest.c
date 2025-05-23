// File maintest.c
// Interfaccia software per la gestione dello studio per testing automatico.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivitatest.h"

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Errore: nessun file specificato!\n");
        return 1;
    }

    FILE *tc_input = fopen(argv[1], "r");
    FILE *oracolo = fopen(argv[2], "r");
    FILE *risultato = fopen(argv[3], "r+");
    FILE *tc_output = fopen("TC_OUTPUT.txt", "w"); // Creazione automatica del file di output

    if(tc_input == NULL){
        printf("Errore nell'apertura del file di input: %s\n", argv[1]);
        return 1;
    }

    if(oracolo == NULL){
        printf("Errore nell'apertura del file oracolo: %s\n", argv[2]);
        fclose(tc_input);
        return 1;  
    }

    if(tc_output == NULL){
        printf("Errore nella creazione del file di output TC_OUTPUT.txt.\n");
        fclose(tc_input);
        fclose(oracolo);
        return 1;
    }

    if(risultato == NULL){
        printf("Errore nell'apertura del file %s.\n", argv[3]);
        fclose(tc_input);
        fclose(oracolo);
        fclose(tc_output);
        return 1;
    }
    
    lista_att l = nuova_lista_att();
    int scelta;

    while(fscanf(tc_input, "%d", &scelta) == 1){
        system("cls");

        switch(scelta) {
            case 1: l = test_aggiungi_attivita(l, tc_input, tc_output);
                    break;
            case 2: l = test_rimuovi_attivita(l, tc_input, tc_output);
                    break;
            case 3: test_aggiornamento_progresso(l, tc_input, tc_output);
                    break;
            case 4: test_report_settimanale(&l, tc_input, tc_output);
                    break;
            case 0: fprintf(tc_output, "Chiusura programma in corso...\n");
                    break;
            default: fprintf(tc_output, "Scelta non valida, riprova.\n");
        }
    }

    verifica_test(argv[2], argv[3]);
    
    fclose(tc_input);
    fclose(tc_output);
    fclose(risultato);
    libera_memoria(&l);
    return 0;
}
