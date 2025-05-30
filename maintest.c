/*File maintest.c
Interfaccia software per la gestione dello studio per testing automatico.
Autore: Alessia Plaitano 
Data creazione: 22 Maggio 2025 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivitatest.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Errore: nessun file specificato!\n");
        return 1;
    }

    FILE *tc_input = fopen(argv[1], "r");
    FILE *oracolo = fopen(argv[2], "r");
    FILE *risultato = fopen(argv[3], "r+");
    FILE *tc_output = fopen("TC_OUTPUT.txt", "w"); // Creazione automatica del file di output.

    if (!tc_input) {
        printf("Errore nell'apertura del file di input: %s\n", argv[1]);
        return 1;
    }
    if (!oracolo) {
        printf("Errore nell'apertura del file oracolo: %s\n", argv[2]);
        fclose(tc_input);
        return 1;
    }
    if (!tc_output) {
        printf("Errore nella creazione del file di output TC_OUTPUT.txt.\n");
        fclose(tc_input);
        fclose(oracolo);
        return 1;
    }
    if (!risultato) {
        printf("Errore nell'apertura del file %s.\n", argv[3]);
        fclose(tc_input);
        fclose(oracolo);
        fclose(tc_output);
        return 1;
    }

    lista_att l = nuova_lista_att();
    int scelta;

    while (fscanf(tc_input, "%d", &scelta) == 1) {
        int ch;

        // Saltiamo il resto della riga dopo aver letto la scelta
        while ((ch = fgetc(tc_input)) != '\n' && ch != EOF);

        // Eseguiamo la funzione corrispondente alla scelta
        switch (scelta) {
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

        // Lettura delle righe dopo la funzione
        char riga[256];
        while (fgets(riga, sizeof(riga), tc_input)) {
            // Se troviamo una riga completamente vuota, esci dal ciclo
            if (riga[0] == '\n' || riga[0] == '\0') {
                break;
            }
            printf("%s", riga);
        }

        // Controlliamo se siamo arrivati alla fine del file
        if(feof(tc_input)){
            break;
        }
    }

    fclose(tc_output);
    verifica_test(argv[2], argv[3]);
    fclose(tc_input);
    fclose(oracolo);
    fclose(risultato);
    libera_memoria(&l);

    return 0;
}
