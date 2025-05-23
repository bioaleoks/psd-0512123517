/* File attività.c
Implementazione ADT "Attivita" e delle relative fz base. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivitatest.h"
#include "mergesortList.h"

//Def. attivita, nodo della lista lista_att
struct attivita{
    char *nome;
    char *corso_appartenenza;
    char *descrizione;
    struct data data_scadenza;
    struct data data_inserimento;
    int priorita;
    int t_stimato;
    int t_trascorso;
    struct attivita *successivo;
};


// nuova_lista: crea nuova lista di attività vuota.
lista_att nuova_lista_att(void){
    return NULL;
}

lista_att test_aggiungi_attivita(lista_att l, FILE *tc_input, FILE *tc_output){
    struct attivita *nuovo;
    nuovo = malloc(sizeof(struct attivita));
    if (nuovo == NULL) {
        fprintf(tc_output, "Allocazione fallita!\n\n");
        return NULL;
    }

    struct data data_scadenza, d_inserimento;
    int t_stimato, t_trascorso, priorita;
    char nome[50], descrizione[150], corso_appartenenza[100];

    fprintf(tc_output, "Per inserire una nuova attivita', compila i seguenti campi:\n");

    fscanf(tc_input, " %49[^\n]", nome);
    fprintf(tc_output, "- Nome attivita': %s\n", nome);

    fscanf(tc_input, " %99[^\n]", corso_appartenenza);
    fprintf(tc_output, "- Corso di appartenenza: %s\n", corso_appartenenza);

    fscanf(tc_input, " %149[^\n]", descrizione);
    fprintf(tc_output, "- Descrizione: %s\n", descrizione);

    while (fscanf(tc_input, "%d-%d-%d", &data_scadenza.giorno, &data_scadenza.mese, &data_scadenza.anno) != 3 ||
           data_scadenza.giorno < 1 || data_scadenza.giorno > 31 ||
           data_scadenza.mese < 1 || data_scadenza.mese > 12) {
        fprintf(tc_output, "\nData errata: inserisci una data valida nel formato specificato.\n");
    }
    
    fprintf(tc_output, "- Data di scadenza: %02d-%02d-%04d\n", data_scadenza.giorno, data_scadenza.mese, data_scadenza.anno);

    while (fscanf(tc_input, "%d-%d-%d", &d_inserimento.giorno, &d_inserimento.mese, &d_inserimento.anno) != 3 ||
           d_inserimento.giorno < 1 || d_inserimento.giorno > 31 ||
           d_inserimento.mese < 1 || d_inserimento.mese > 12) {
        fprintf(tc_output, "\nData errata: inserisci una data valida nel formato specificato.\n");
    }
    fprintf(tc_output, "- Data di inserimento: %02d-%02d-%04d\n", d_inserimento.giorno, d_inserimento.mese, d_inserimento.anno);

    while (fscanf(tc_input, "%d", &priorita) != 1 || priorita < 1 || priorita > 3) {
        fprintf(tc_output, "\nErrore: inserisci un numero valido compreso tra 1 e 3.\n");
    }
    fprintf(tc_output, "- Priorita': %d\n", priorita);

    fscanf(tc_input, "%d", &t_stimato);
    fprintf(tc_output, "- Tempo stimato per completare l'attivita': %d ore\n", t_stimato);

    fscanf(tc_input, "%d", &t_trascorso);
    fprintf(tc_output, "- Tempo gia' trascorso: %d ore\n", t_trascorso);

    nuovo->nome = malloc(strlen(nome) + 1);
    nuovo->descrizione = malloc(strlen(descrizione) + 1);
    nuovo->corso_appartenenza = malloc(strlen(corso_appartenenza) + 1);

    if (!nuovo->nome || !nuovo->descrizione || !nuovo->corso_appartenenza) {
        fprintf(tc_output, "\nSi è verificato un errore nell'inserimento.\n\n\n");
        free(nuovo->nome);
        free(nuovo->descrizione);
        free(nuovo->corso_appartenenza);
        free(nuovo);
        return NULL;
    }

    strcpy(nuovo->nome, nome);
    strcpy(nuovo->descrizione, descrizione);
    strcpy(nuovo->corso_appartenenza, corso_appartenenza);
    nuovo->data_scadenza = data_scadenza;
    nuovo->priorita = priorita;
    nuovo->t_stimato = t_stimato;
    nuovo->t_trascorso = t_trascorso;
    nuovo->successivo = l;

    fprintf(tc_output, "\n\nNuova attivita' aggiunta con successo!\n\n\n");
    return nuovo;
}


lista_att test_rimuovi_attivita(lista_att l, FILE *tc_input, FILE *tc_output) {
    struct attivita *corrente = l, *precedente = NULL;
    char nome[50];

    // Leggere il nome dell'attività da rimuovere dal file di input
    if (fgets(nome, sizeof(nome), tc_input) == NULL) {
        fprintf(tc_output, "Errore nella lettura del nome dell'attività da eliminare.\n");
        return l;
    }

    // Rimuovere il carattere di nuova linea se presente
    nome[strcspn(nome, "\n")] = 0;

    fprintf(tc_output, "Tentativo di eliminare l'attività: %s\n", nome);

    while (corrente != NULL) {
        if (strcmp(corrente->nome, nome) == 0) {
            if (precedente == NULL) {
                // Caso: l'attività da eliminare è la prima della lista.
                l = corrente->successivo;
            } else {
                // Caso: l'attività da eliminare è in mezzo alla lista o l'ultima.
                precedente->successivo = corrente->successivo;
            }

            free(corrente->nome);
            free(corrente->corso_appartenenza);
            free(corrente->descrizione);
            free(corrente);

            fprintf(tc_output, "\n\nAttività correttamente rimossa.\n\n\n");
            return l; // Lista aggiornata.
        }

        precedente = corrente;
        corrente = corrente->successivo;
    }

    fprintf(tc_output, "\n\nAttività non trovata in programma.\n\n\n");
    return l; // Lista originale.
}

int test_aggiornamento_progresso(lista_att l, FILE *tc_input, FILE *tc_output) {
    struct attivita *corrente;
    int t_trascorso_agg, val, t_stimato_agg, percentuale;
    char nome[50];

    // Leggere il nome dell'attività dal file di input
    if (fgets(nome, sizeof(nome), tc_input) == NULL) {
        fprintf(tc_output, "Errore nella lettura del nome dell'attività.\n");
        return 0;
    }
    nome[strcspn(nome, "\n")] = 0;

    // Leggere il tempo trascorso aggiornato dal file di input
    if (fscanf(tc_input, "%d", &t_trascorso_agg) != 1) {
        fprintf(tc_output, "Errore nella lettura del tempo trascorso.\n");
        return 0;
    }

    for (corrente = l; corrente != NULL; corrente = corrente->successivo) {
        if (strcmp(corrente->nome, nome) == 0) {
            corrente->t_trascorso = t_trascorso_agg;

            if (corrente->t_stimato > corrente->t_trascorso) { 
                percentuale = (corrente->t_trascorso * 100) / corrente->t_stimato;
                fprintf(tc_output, "\nLa tua percentuale di progresso è %d %%\n\n", percentuale);
            } else {
                fprintf(tc_output, "\nIl tempo trascorso è maggiore o uguale al tempo stimato.\n");
                fprintf(tc_output, "Digita 1 se vuoi aggiornare il tempo stimato, altrimenti l'attività sarà considerata completata:\n");

                // Leggere la scelta dell'utente dal file di input
                if (fscanf(tc_input, "%d", &val) != 1) {
                    fprintf(tc_output, "Errore nella lettura della scelta.\n");
                    return 0;
                }

                if (val == 1) {
                    fprintf(tc_output, "\n\nInserisci il nuovo tempo stimato (in ore):\n");

                    // Leggere il nuovo tempo stimato dal file di input
                    if (fscanf(tc_input, "%d", &t_stimato_agg) != 1) {
                        fprintf(tc_output, "Errore nella lettura del tempo stimato aggiornato.\n");
                        return 0;
                    }

                    corrente->t_stimato = t_stimato_agg;
                    fprintf(tc_output, "\nTempo stimato aggiornato!\n");

                    if (corrente->t_stimato > 0) {
                        percentuale = (corrente->t_trascorso * 100) / corrente->t_stimato;
                        fprintf(tc_output, "La tua percentuale di progresso è %d %%\n\n", percentuale);
                    }
                } else {
                    fprintf(tc_output, "\n\nComplimenti, hai completato l'attività con successo!\n\n");
                }
            }
            return 1; // Attività trovata e modificata
        }
    }

    fprintf(tc_output, "\nAttività non trovata.\n\n");
    return 0;
}



/* ordina_per_priorita: attraverso il metodo di ordinamento 
MergeSort, riordina la lista con le attività in base al campo
"priorità", in maniera decrescente, dalla 3 alla 1.*/
void ordina_per_priorita(lista_att *l){
    *l=mergesort_lista(*l);
}


/* scadenza_att: attraverso una serie di confronti tra due struct data,
data_scadenza e fine_sett, definisce, per ogni attività, se è scaduta
oppure no. Viene usata nella funzione report_settimanale.
La fz restituisce 1 se l'attività è scaduta, altrimenti 0. */
int scadenza_att(struct data data_scadenza, struct data fine_sett){
    if(data_scadenza.anno < fine_sett.anno) return 1;
    else if(data_scadenza.anno == fine_sett.anno){
            if(data_scadenza.mese<fine_sett.mese)
            return 1;
            else if(data_scadenza.mese == fine_sett.mese){
                    if(data_scadenza.giorno < fine_sett.giorno)
                    return 1;
                }
        }
    return 0;
}


void test_report_settimanale(lista_att* l, FILE *tc_input, FILE *tc_output) {
    ordina_per_priorita(l);
    struct attivita *corrente = *l;
    struct data inizio_sett, fine_sett;
    int val, scadenza, percentuale;

    // Lettura del primo giorno della settimana
    if (fscanf(tc_input, "%d-%d-%d", &inizio_sett.giorno, &inizio_sett.mese, &inizio_sett.anno) != 3 ||
        inizio_sett.giorno < 1 || inizio_sett.giorno > 31 ||
        inizio_sett.mese < 1 || inizio_sett.mese > 12) {
        fprintf(tc_output, "Errore: Data di inizio settimana non valida.\n");
        return;
    }

    // Lettura dell'ultimo giorno della settimana
    if (fscanf(tc_input, "%d-%d-%d", &fine_sett.giorno, &fine_sett.mese, &fine_sett.anno) != 3 ||
        fine_sett.giorno < 1 || fine_sett.giorno > 31 ||
        fine_sett.mese < 1 || fine_sett.mese > 12) {
        fprintf(tc_output, "Errore: Data di fine settimana non valida.\n");
        return;
    }

    if (corrente == NULL) { // Lista vuota
        fprintf(tc_output, "\nNessuna attività trovata per questa settimana!\n");
        fprintf(tc_output, "Digita 1 se vuoi inserirne una adesso, altrimenti 0 per uscire:\n");

        // Lettura della scelta dell'utente dal file di input
        if (fscanf(tc_input, "%d", &val) != 1) {
            fprintf(tc_output, "Errore nella lettura della scelta.\n");
            return;
        }

        if (val == 1) {
            *l = test_aggiungi_attivita(*l, tc_input, tc_output);
            corrente = *l;
        } else {
            return;
        }
    }

    fprintf(tc_output, "\nEcco un report settimanale delle attività inserite entro questa settimana, ordinate per priorità maggiore:\n\n");

    while (corrente != NULL) {
        // Se l'attività è stata aggiunta entro il giorno di fine settimana, stampala.
        if (corrente->data_inserimento.anno < fine_sett.anno ||
            (corrente->data_inserimento.anno == fine_sett.anno && corrente->data_inserimento.mese < fine_sett.mese) ||
            (corrente->data_inserimento.anno == fine_sett.anno && corrente->data_inserimento.mese == fine_sett.mese &&
             corrente->data_inserimento.giorno <= fine_sett.giorno)) {

            fprintf(tc_output, "Nome: %s\n", corrente->nome);
            fprintf(tc_output, "Corso di appartenenza: %s\n", corrente->corso_appartenenza);
            fprintf(tc_output, "Descrizione: %s\n", corrente->descrizione);
            fprintf(tc_output, "Data di scadenza: %02d-%02d-%04d\n", corrente->data_scadenza.giorno, corrente->data_scadenza.mese, corrente->data_scadenza.anno);
            fprintf(tc_output, "Data di inserimento: %02d-%02d-%04d\n", corrente->data_inserimento.giorno, corrente->data_inserimento.mese, corrente->data_inserimento.anno);
            fprintf(tc_output, "Priorità: %d\n", corrente->priorita);
            fprintf(tc_output, "Tempo stimato: %d ore\n", corrente->t_stimato);
            fprintf(tc_output, "Tempo trascorso: %d ore\n", corrente->t_trascorso);

            scadenza = scadenza_att(corrente->data_scadenza, fine_sett);

            if (scadenza == 1) {
                fprintf(tc_output, "L'attività è scaduta!\n\n");
            } else if (corrente->t_stimato == corrente->t_trascorso || corrente->t_stimato == 0) {
                fprintf(tc_output, "L'attività è stata completata con successo!\n\n");
            } else {
                percentuale = (corrente->t_trascorso * 100) / corrente->t_stimato;
                fprintf(tc_output, "L'attività è in corso, con una percentuale di completamento %d %%!\n\n", percentuale);
            }
        }

        corrente = corrente->successivo;
    }
}

void verifica_test(char *file_oracolo, char *risultato) {
    FILE *oracolo = fopen(file_oracolo, "r");
    FILE *output = fopen("tc_output.txt", "r"); // Usa il file di output generato automaticamente
    FILE *testsuite_file = fopen(risultato, "r+"); // Apri in lettura e scrittura

    if (!oracolo || !output || !testsuite_file) {
        printf("Errore nell'apertura dei file.\n");
        return;
    }

    // 🔍 Estrai il numero del test case dal nome del file di input
    char test_case[20];  
    sscanf(file_oracolo, "%[^_]_", test_case); // Legge "TC1" da "TC1_oracolo.txt"

    // 🔄 Confronta i file per determinare SUCCESSO o FALLIMENTO
    char riga_oracolo[256], riga_output[256];
    int successo = 1;

    while (fgets(riga_oracolo, sizeof(riga_oracolo), oracolo) &&
           fgets(riga_output, sizeof(riga_output), output)) {
        if (strcmp(riga_oracolo, riga_output) != 0) {
            successo = 0;
            break;
        }
    }

    if (!feof(oracolo) || !feof(output)) {
        successo = 0;
    }

    fclose(oracolo);
    fclose(output);

    // 🔎 Cerca la riga corretta nel file testsuite e aggiorna direttamente il risultato
    char buffer[1024];
    long pos;
    while (fgets(buffer, sizeof(buffer), testsuite_file)) {
        if (strncmp(buffer, test_case, strlen(test_case)) == 0) {
            // Trova la posizione attuale nel file e torna indietro per sovrascrivere la riga
            pos = ftell(testsuite_file) - strlen(buffer);
            fseek(testsuite_file, pos, SEEK_SET);
            fprintf(testsuite_file, "%s %s\n", test_case, successo ? "SUCCESSO" : "FALLIMENTO");
            fflush(testsuite_file); // Assicura che i dati vengano scritti immediatamente
            break; // Aggiornamento effettuato, interrompe la ricerca
        }
    }

    fclose(testsuite_file);
}




/* libera_memoria: dealloca tutta la memoria dinamica
occupata dalle attività della lista per evitare memory
leak, prima del termine di esecuzione della fz main. */
void libera_memoria(lista_att *l){
    struct attivita *corrente=*l;
    while(corrente!=NULL){
    struct attivita *temp=corrente;
    corrente=corrente->successivo;
    free(temp->nome);
    free(temp->descrizione);
    free(temp->corso_appartenenza);
    free(temp);
    }
    *l=NULL; //Evita futuri accessi non validi.
}