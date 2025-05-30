/* File attività.c
Implementazione ADT "Attivita" e delle relative fz base. 
Autore: Alessia Plaitano 
Data creazione: 22 Maggio 2025 */
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


/* Funzione: nuova_lista_att.
-----------------------------------------------------------------
La funzione crea e restituisce una nuova lista di attività vuota.
-----------------------------------------------------------------
SPECIFICA SINTATTICA: nuova_lista_att(void) -> lista_att
Tipi: lista_att.
SPECIFICA SEMANTICA: nuova_lista_att () -> lista_att
-Side-effect: Nessuno.
-Precondizione: Nessuna, la funzione può essere chiamata in qualsiasi momento;
-Postcondizione: Restituisce una lista vuota (NULL). */
lista_att nuova_lista_att(void){
    return NULL;
}


/* Funzione: test_aggiungi_attivita.
----------------------------------------------------------------------------------------------------------------------------
La funzione legge gli input per l'inserimento di una nuova attività dal file di input tc_input. Ad ogni fase di lettura, se 
si verifica un errore (come la mancanza di dati o dati non validi) viene stampato un messaggio di errore sul file tc_output, 
la memoria eventualmente allocata viene liberata e la funzione restituisce la lista senza modifiche. Altrimenti, la funzione 
scrive un messaggio di successo sul file di output e restituisce la nuova lista aggiornata.
-----------------------------------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: test_aggiungi_attivita(lista_att, FILE*, FILE*) -> lista_att
Tipi: lista_att, FILE*.
SPECIFICA SEMANTICA: test_aggiungi_attivita(l, tc_input, tc_output) -> l
-Side-effect: Scrittura sul file tc_output, allocazione dinamica del nuovo nodo per l’attività e di stringhe, eventuale 
deallocazione in caso di errori, modifica struttura della lista se tutti i dati di input risultano validi.
-Precondizione: l deve rappresentare una lista (anche vuota) valida di attività. I puntatori tc_input e tc_output devono essere 
aperti correttamente, in lettura e scrittura rispettivamente. Il file tc_input deve contenere i dati nel formato atteso: nome 
(non vuoto), corso di appartenenza (non vuoto), descrizione (non vuota), due date formattate con il separatore “-” (per data di 
scadenza e data di inserimento) con valori validi (giorno da 1 a 31, mese da 1 a 12), priorità (intero compreso tra 1 e 3), tempo 
stimato e il tempo già trascorso (numeri interi).
-Postcondizione: Se tutti i dati sono validi e la memoria viene allocata correttamente, la funzione deve inserire la nuova attività
 in testa alla lista e restituire la lista aggiornata. In caso di errore di qualunque tipo (lettura, validazione o allocazione), 
 deve essere stampato un messaggio di errore su tc_output, la memoria eventualmente allocata deve essere liberata e la funzione 
 deve restituire la lista invariata. */
lista_att test_aggiungi_attivita(lista_att l, FILE *tc_input, FILE *tc_output){
    struct attivita *nuovo=malloc(sizeof(struct attivita));
    if(nuovo == NULL){
        fprintf(tc_output, "Allocazione fallita!\n\n");
        return l;  // l è lista originale.
    }

    struct data data_scadenza, d_inserimento;
    int t_stimato, t_trascorso, priorita;
    char nome[50], descrizione[150], corso_appartenenza[100];
    char buffer[100];

    fprintf(tc_output, "Per inserire una nuova attivita', compila i seguenti campi:\n");

    if(fgets(nome, sizeof(nome), tc_input) == NULL){
        fprintf(tc_output, "Errore nella lettura del nome.\n");
        free(nuovo);
        return l;
    }
    nome[strcspn(nome, "\n")]='\0';
    if(strlen(nome) == 0){
        fprintf(tc_output, "Il campo nome non può essere vuoto!\n");
        free(nuovo);
        return l;
    }
    fprintf(tc_output, "-Nome attivita': %s\n", nome);


    if(fgets(corso_appartenenza, sizeof(corso_appartenenza), tc_input) == NULL){
        fprintf(tc_output, "Errore nella lettura del corso di appartenenza.\n");
        free(nuovo);
        return l;
    }
    corso_appartenenza[strcspn(corso_appartenenza, "\n")]='\0';
    if(strlen(corso_appartenenza) == 0){
        fprintf(tc_output, "Il campo corso di appartenenza non può essere vuoto!\n");
        free(nuovo);
        return l;
    }
    fprintf(tc_output, "-Corso di appartenenza: %s\n", corso_appartenenza);


    if(fgets(descrizione, sizeof(descrizione), tc_input) == NULL){
        fprintf(tc_output, "Errore nella lettura della descrizione.\n");
        free(nuovo);
        return l;
    }
    descrizione[strcspn(descrizione, "\n")]='\0';
    if(strlen(descrizione) == 0){
        fprintf(tc_output, "La descrizione non può essere vuota!\n");
        free(nuovo);
        return l;
    }
    fprintf(tc_output, "-Descrizione: %s\n", descrizione);

    
    while (1){
        //Ciclo iterato finchè non si immette una data valida.
        if(fgets(buffer, sizeof(buffer), tc_input) == NULL){
            fprintf(tc_output, "Errore nella lettura della data di scadenza.\n");
            free(nuovo);
            return l;
        }
        if(sscanf(buffer, "%d-%d-%d", &data_scadenza.giorno, &data_scadenza.mese, &data_scadenza.anno) != 3 ||
            data_scadenza.giorno<1 || data_scadenza.giorno>31 ||
            data_scadenza.mese<1 || data_scadenza.mese>12){
            fprintf(tc_output, "Inserisci una data valida nel formato specificato (gg-mm-aaaa).\n");
        } else {
            break;
        }
    }
    fprintf(tc_output, "-Data di scadenza: %02d-%02d-%04d\n", data_scadenza.giorno, data_scadenza.mese, data_scadenza.anno);

     
    while (1){
        //Ciclo iterato finchè non si immette una data valida.
        if(fgets(buffer, sizeof(buffer), tc_input) == NULL){
            fprintf(tc_output, "Errore nella lettura della data di inserimento.\n");
            free(nuovo);
            return l;
        }
        if(sscanf(buffer, "%d-%d-%d", &d_inserimento.giorno, &d_inserimento.mese, &d_inserimento.anno) != 3 ||
            d_inserimento.giorno<1 || d_inserimento.giorno>31 ||
            d_inserimento.mese<1 || d_inserimento.mese>12){
            fprintf(tc_output, "Inserisci una data valida nel formato specificato (gg-mm-aaaa).\n");
        } else {
            break;
        }
    }
    fprintf(tc_output, "-Data di inserimento: %02d-%02d-%04d\n", d_inserimento.giorno, d_inserimento.mese, d_inserimento.anno);
    nuovo->data_inserimento = d_inserimento; 

 
    while (1){
        //Ciclo iterato finchè non si immette una valore valido.
        if(fgets(buffer, sizeof(buffer), tc_input) == NULL){
            fprintf(tc_output, "Errore nella lettura della priorità.\n");
            free(nuovo);
            return l;
        }
        if(sscanf(buffer, "%d", &priorita) != 1 || priorita < 1 || priorita > 3){
            fprintf(tc_output, "Inserisci un numero valido, compreso tra 1 e 3!\n");
        } else {
            break;
        }
    }
    fprintf(tc_output, "-Priorità: %d\n", priorita);


    if(fgets(buffer, sizeof(buffer), tc_input) == NULL || sscanf(buffer, "%d", &t_stimato) != 1){
        fprintf(tc_output, "Errore nella lettura del tempo stimato.\n");
        free(nuovo);
        return l;
    }
    fprintf(tc_output, "-Tempo stimato per completare l'attivita': %d ore\n", t_stimato);

  
    if(fgets(buffer, sizeof(buffer), tc_input) == NULL || sscanf(buffer, "%d", &t_trascorso) != 1){
        fprintf(tc_output, "Errore nella lettura del tempo gia' trascorso.\n");
        free(nuovo);
        return l;
    }
    fprintf(tc_output, "-Tempo gia' trascorso: %d ore\n", t_trascorso);

    //Allocazione dinamica dei campi stringa.
    nuovo->nome=malloc(strlen(nome) + 1);
    nuovo->descrizione=malloc(strlen(descrizione) + 1);
    nuovo->corso_appartenenza=malloc(strlen(corso_appartenenza) + 1);
    if(!nuovo->nome || !nuovo->descrizione || !nuovo->corso_appartenenza){
        fprintf(tc_output, "Si è verificato un errore nell'inserimento.\n\n");
        free(nuovo->nome);
        free(nuovo->descrizione);
        free(nuovo->corso_appartenenza);
        free(nuovo);
        return l;
    }

    strcpy(nuovo->nome, nome);
    strcpy(nuovo->descrizione, descrizione);
    strcpy(nuovo->corso_appartenenza, corso_appartenenza);
    nuovo->data_scadenza=data_scadenza;
    nuovo->priorita=priorita;
    nuovo->t_stimato=t_stimato;
    nuovo->t_trascorso=t_trascorso;
    nuovo->successivo=l;

    fprintf(tc_output, "\n\nNuova attivita' aggiunta con successo!\n\n");

    return nuovo;
}


/* Funzione: test_rimuovi_attivita.
----------------------------------------------------------------------------------------------
La funzione rimuove una determinata attività dalla lista, che legge dal file di input 
(tc_input). Attraversa la lista (partendo dalla testa l), cercando un nodo in cui il 
campo nome corrisponde al nome letto.
-----------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: test_rimuovi_attivita(lista_att, FILE*, FILE*) -> lista_att
Tipi: lista_att, FILE*.
SPECIFICA SEMANTICA: test_rimuovi_attivita(l, tc_input, tc_output) -> lista_att
-Side-effect: Scrittura sul file tc_output, modifica struttura della lista con relativo 
aggiornamento dei puntatori, deallocazione memoria allocata precedentemente per il nodo eliminato. 
-Precondizione: l deve essere una lista valida (anche se vuota). I puntatori tc_input e tc_output
devono essere aperti correttamente ed essere validi. Il file tc_input deve contenere il nome (come 
stringa) di un’attività da eliminare.
-Postcondizione: Se l'attività con il nome corrispondente è presente, deve essere rimossa dalla 
lista e la memoria allocata per essa liberata; il file tc_output deve registrare un messaggio di 
conferma. Se nessuna attività con il nome fornito viene trovata, la lista deve rimanere invariata 
e deve essere segnalato l’errore sul file tc_output. */
lista_att test_rimuovi_attivita(lista_att l, FILE *tc_input, FILE *tc_output) {
    struct attivita *corrente=l, *precedente=NULL;
    char nome[50];

    //Legge il nome dell'attività da rimuovere dal file di input.
    if(fgets(nome, sizeof(nome), tc_input) == NULL){
        fprintf(tc_output, "Errore nella lettura del nome dell'attività da eliminare.\n");
        return l;
    }
    // Rimuovere il carattere di newline, se presente.
    nome[strcspn(nome, "\n")]=0;

    fprintf(tc_output, "Tentativo di eliminare l'attività: %s\n", nome);

    while(corrente != NULL){
        if(strcmp(corrente->nome, nome) == 0){
            if(precedente == NULL){
                //L'attività da eliminare è la prima della lista.
                l=corrente->successivo;
            } else {
                //L'attività da eliminare è in mezzo alla lista o l'ultima.
                precedente->successivo=corrente->successivo;
            }

            free(corrente->nome);
            free(corrente->corso_appartenenza);
            free(corrente->descrizione);
            free(corrente);

            fprintf(tc_output, "\n\nAttività correttamente rimossa.\n\n\n");
            return l; //Lista aggiornata.
        }

        precedente=corrente;
        corrente=corrente->successivo;
    }

    fprintf(tc_output, "\n\nAttività non trovata in programma.\n\n\n");
    return l; //Lista originale.
}


/* Funzione: test_aggiornamento_progresso.
----------------------------------------------------------------------------------------------------------------------------------
La funzione aggiorna il progresso (tempo già trascorso) di un’attività presente nella lista passata. Legge dal file tc_input il 
nome dell’attività, che servirà per cercare l’attività nella lista. Legge, successivamente, il nuovo valore del tempo trascorso 
(t_trascorso_agg) da utilizzare per l’aggiornamento. Se il tempo stimato (t_stimato) è maggiore del tempo trascorso aggiornato, 
viene calcolata e stampata la percentuale di progresso. Se il tempo trascorso è maggiore o uguale al tempo stimato, viene chiesto 
(sempre leggendo da tc_input) se si intende aggiornare il tempo stimato, digitando il valore 1 se sì, altrimenti un altro.                                            Se l’attività viene trovata e aggiornamenti eseguiti, la funzione restituisce 1. Se si verifica un errore di lettura o l’attività non viene individuata nella lista, viene restituito 0 e viene stampato un messaggio di errore sul file tc_output.
-----------------------------------------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: test_aggiornamento_progresso(lista_att, FILE*, FILE*) -> int
Tipi: lista_att, FILE*, int.
SPECIFICA SEMANTICA: test_aggiornamento_progresso(l, tc_input, tc_output) -> int
-Side-effect: Scrittura sul file tc_output, modifica della struttura lista_att relativa ai campi t_trascorso e t_stimato.
-Precondizione: l deve essere una lista valida (anche vuota). tc_input e tc_output devono essere stati aperti correttamente
 (rispettivamente in lettura e in scrittura). Il file di input tc_input deve contenere i dati formattati in modo tale che ci
  sia il nome dell’attività, un intero (t_trascorso_agg) e, se necessario, ulteriori interi (per la scelta dell’utente e, in 
  caso, per il nuovo tempo stimato).
-Postcondizione: Se l’attività con il nome specificato viene trovata, il suo campo t_trascorso deve essere aggiornato con 
il nuovo valore. In caso di tempo trascorso maggiore o uguale a quello stimato, anche il campo t_stimato potrebbe dover essere 
aggiornato. La funzione deve stampare su tc_output la percentuale di progresso oppure messaggi di errore/conferma relativi 
all’aggiornamento. La funzione restituirà 1 se l’aggiornamento (o il controllo) è andato a buon fine, 0 in caso contrario. */
int test_aggiornamento_progresso(lista_att l, FILE *tc_input, FILE *tc_output) {
    struct attivita *corrente;
    int t_trascorso_agg, val, t_stimato_agg, percentuale;
    char nome[50];

    // Legge il nome dell'attività dal file di input.
    if(fgets(nome, sizeof(nome), tc_input) == NULL){
        fprintf(tc_output, "Errore nella lettura del nome dell'attività!\n");
        return 0;
    }
    nome[strcspn(nome, "\n")]=0;

    // Legge il tempo trascorso aggiornato dal file di input.
    if(fscanf(tc_input, "%d", &t_trascorso_agg) != 1){
        fprintf(tc_output, "Errore nella lettura del tempo trascorso!\n");
        return 0;
    }


    for(corrente=l; corrente != NULL; corrente=corrente->successivo){
        if(strcmp(corrente->nome, nome) == 0){
            corrente->t_trascorso=t_trascorso_agg;

            if(corrente->t_stimato > corrente->t_trascorso){ 
                percentuale= (corrente->t_trascorso * 100) / corrente->t_stimato;
                fprintf(tc_output, "\nLa tua percentuale di progresso è %d %%\n\n", percentuale);
            } else {
                fprintf(tc_output, "\nIl tempo trascorso è maggiore o uguale al tempo stimato.\n");
                fprintf(tc_output, "Digita 1 se vuoi aggiornare il tempo stimato, altrimenti l'attività sarà considerata completata:\n");

                if(fscanf(tc_input, "%d", &val) != 1){
                    fprintf(tc_output, "Errore nella lettura della scelta!\n");
                    return 0;
                }

                if(val == 1){
                    fprintf(tc_output, "\n\nInserisci il nuovo tempo stimato (in ore):\n");

                    if(fscanf(tc_input, "%d", &t_stimato_agg) != 1){
                        fprintf(tc_output, "Errore nella lettura del tempo stimato aggiornato!\n");
                        return 0;
                    }

                    corrente->t_stimato=t_stimato_agg;
                    fprintf(tc_output, "\nTempo stimato aggiornato!\n");

                    if(corrente->t_stimato > 0){
                        percentuale= (corrente->t_trascorso * 100) / corrente->t_stimato;
                        fprintf(tc_output, "La tua percentuale di progresso è %d %%\n\n", percentuale);
                    }
                } else {
                    fprintf(tc_output, "\n\nComplimenti, hai completato l'attività con successo!\n\n");
                }
            }
            return 1; //Attività trovata e modificata.
        }
    }

    fprintf(tc_output, "\nAttività non trovata.\n\n");
    return 0;
}


/* Funzione: ordina_per_priorita.
----------------------------------------------------------------------------------------------
Attraverso il metodo di ordinamento MergeSort, la fz riordina la lista con le attività 
in base al campo "priorità", in maniera decrescente, dalla 3 alla 1.
----------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: ordina_per_priorita(lista_att*) -> void
Tipi: lista_att*.
SPECIFICA SEMANTICA: ordina_per_priorita(l) -> void
-Side-effect: riordinamento della struttura della lista tramite l’algoritmo MergeSort.
-Precondizione: Il puntatore l deve essere inizializzato (anche se la lista è vuota). Le attività presenti 
nella lista, se esistenti, devono contenere un campo "priorità" valido.
-Postcondizione: La lista puntata da l deve essere modificata in modo tale da risultare ordinata in ordine 
decrescente secondo il campo "priorità". La funzione non deve restituisce alcun valore, poiché l'ordinamento 
è effettuato grazie alla sostituzione del puntatore alla lista con quello restituito dalla funzione mergesort_lista. */
void ordina_per_priorita(lista_att *l){
    *l=mergesort_lista(*l);
}


/* Funzione: scadenza_att.
------------------------------------------------------------------------------------------------------
La funzione attraverso una serie di confronti tra due struct data, data_scadenza e fine_sett, 
definisce, per ogni attività, se è scaduta oppure no. Viene usata nella funzione report_settimanale.
La fz restituisce 1 se l'attività è scaduta, altrimenti 0. 
------------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: scadenza_att(struct data, struct data) -> int
Tipi: struct data, int.
SPECIFICA SEMANTICA: scadenza_att(data_scadenza, fine_sett) -> int
-Side-effect: Nessuno.
-Precondizione: data_scadenza e fine_sett devono contenere valori validi (essere date corrette).
-Postcondizione: Se data_scadenza risulta precedente a fine_sett, l’attività è scaduta e la funzione dovrà 
restituire 1. Viceversa, l’attività sarà considerata in corso e la funzione restituirà 0. */
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


/* Funzione: test_report_settimanale.
--------------------------------------------------------------------------------------------------------------
La funzione genera un report settimanale delle attività contenute in una lista, ordinandole per priorità. 
Viene letta la data di inizio settimana da tc_input e validata (controllando che il giorno sia compreso 
fra 1 e 31 e il mese fra 1 e 12). Analogamente, viene letta e validata anche la data di fine settimana.
Se la lista risulta vuota (cioè non sono presenti attività), la funzione chiede all’utente, tramite tc_input, 
se desidera inserire una nuova attività. Per ogni attività presente nella lista e registrata non oltre il 
giorno di fine settimana vengono stampati su tc_output tutti i dettagli e ne viene verificato lo stato 
(completata/in corso/scaduta), grazie alla funzione scadenza_att.
--------------------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: test_report_settimanale(lista_att*, FILE*, FILE*) -> void
Tipi: lista_att*, FILE*.
SPECIFICA SEMANTICA: test_report_settimanale(l, tc_input, tc_output) -> void
-Side-effect: Scrittura sul file tc_output, eventuale allocazione dinamica di un nuovo nodo per la lista (su scelta 
dell’utente), riordinamento struttura della lista tramite la funzione ordina_per_priorita.
-Precondizione: l deve fare riferimento a una lista valida (che può essere vuota). I file puntati da tc_input e 
tc_output devono essere stati aperti correttamente in lettura e scrittura. I valori di input relativi alle date devono 
essere del formato previsto (ad es. "giorno-mese-anno") e con valori numerici validi.
-Postcondizione: Se la lista era vuota, deve essere chiesto all’utente se vuole inserire una nuova attività, tramite 
la funzione test_aggiungi_attivita. Deve essere stampato un report dettagliato su tc_output per le attività registrate 
entro la data di fine settimana, ordinate per priorità. La funzione non deve restituire un valore, ma il report e gli 
eventuali messaggi di errore o interazione devono essere scritti su tc_output. */
void test_report_settimanale(lista_att* l, FILE *tc_input, FILE *tc_output) {
    ordina_per_priorita(l);
    struct attivita *corrente=*l;
    struct data inizio_sett, fine_sett;
    int val, scadenza, percentuale;

    if(fscanf(tc_input, "%d-%d-%d", &inizio_sett.giorno, &inizio_sett.mese, &inizio_sett.anno) != 3 ||
        inizio_sett.giorno<1 || inizio_sett.giorno>31 ||
        inizio_sett.mese<1 || inizio_sett.mese>12){
        fprintf(tc_output, "Data di inizio settimana non valida!\n");
        return;
    }

    
    if(fscanf(tc_input, "%d-%d-%d", &fine_sett.giorno, &fine_sett.mese, &fine_sett.anno) != 3 ||
        fine_sett.giorno<1 || fine_sett.giorno>31 ||
        fine_sett.mese<1 || fine_sett.mese>12){
        fprintf(tc_output, "Data di fine settimana non valida!\n");
        return;
    }

    if(corrente == NULL){  //Se la lista è vuota.
        fprintf(tc_output, "\nNessuna attività trovata per questa settimana!\n");
        fprintf(tc_output, "Digita 1 se vuoi inserirne una adesso, altrimenti 0 per uscire:\n");

        if(fscanf(tc_input, "%d", &val) != 1){
            fprintf(tc_output, "Errore nella lettura della scelta.\n");
            return;
        }

        if(val == 1){
            *l=test_aggiungi_attivita(*l, tc_input, tc_output);
            corrente=*l;
        } else {
            return;
        }
    }

    fprintf(tc_output, "\n**********************************************************************************************************");
    fprintf(tc_output, "\nEcco un report settimanale delle attività inserite entro questa settimana, ordinate per priorità maggiore:\n");
    fprintf(tc_output, "**********************************************************************************************************\n\n");

    while(corrente != NULL){
        // Se l'attività è stata aggiunta entro il giorno di fine settimana, stampala.
        if(corrente->data_inserimento.anno < fine_sett.anno ||
            (corrente->data_inserimento.anno == fine_sett.anno && corrente->data_inserimento.mese < fine_sett.mese) ||
            (corrente->data_inserimento.anno == fine_sett.anno && corrente->data_inserimento.mese == fine_sett.mese &&
             corrente->data_inserimento.giorno <= fine_sett.giorno)){


            fprintf(tc_output, "-Nome: %s\n", corrente->nome);
            fprintf(tc_output, "-Corso di appartenenza: %s\n", corrente->corso_appartenenza);
            fprintf(tc_output, "-Descrizione: %s\n", corrente->descrizione);
            fprintf(tc_output, "-Data di scadenza: %02d-%02d-%04d\n", corrente->data_scadenza.giorno, corrente->data_scadenza.mese, corrente->data_scadenza.anno);
            fprintf(tc_output, "-Data di inserimento: %02d-%02d-%04d\n", corrente->data_inserimento.giorno, corrente->data_inserimento.mese, corrente->data_inserimento.anno);
            fprintf(tc_output, "-Priorità: %d\n", corrente->priorita);
            fprintf(tc_output, "-Tempo stimato: %d ore\n", corrente->t_stimato);
            fprintf(tc_output, "-Tempo trascorso: %d ore\n", corrente->t_trascorso);

            scadenza=scadenza_att(corrente->data_scadenza, fine_sett);

            if(scadenza == 1){
                fprintf(tc_output, "L'attività è scaduta!\n\n");
            } else if(corrente->t_stimato == corrente->t_trascorso || corrente->t_stimato == 0){
                fprintf(tc_output, "L'attività è stata completata con successo!\n\n");
            } else{
                percentuale= (corrente->t_trascorso * 100) / corrente->t_stimato;
                fprintf(tc_output, "L'attività è in corso, con una percentuale di completamento: %d %%!\n\n", percentuale);
            }
        }

        corrente=corrente->successivo;
    }
}


/* Funzione: verifica_test.
-------------------------------------------------------------------------------------------------------------------
La funzione confronta il contenuto del file oracolo e del file di output. Il confronto avviene riga per riga, 
rimuovendo da ciascuna riga i caratteri di fine linea (\r e \n). Se tutte le righe risultano identiche (compresa 
l’assenza di righe extra in uno dei due file), il test viene considerato “SUCCESSO” altrimenti “FALLIMENTO”. 
Successivamente, la funzione estrae la parte iniziale del nome del file oracolo e scrive, in modalità append, 
una riga nel file “risultato”.
--------------------------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: verifica_test(char*, char*) -> void
Tipi: char*.
SPECIFICA SEMANTICA: verifica_test(file_oracolo, risultato) -> void
-Side-effect: Scrittura sul file indicato da “risultato” ed eventuale scrittura sul file di output per messaggi di errore.
-Precondizione: Il file oracolo indicato deve esistere ed essere accessibile in lettura. Analogamente per il file "TC_OUTPUT.txt”. 
Il file indicato da “risultato” deve poter essere aperto in modalità append per scrittura.
-Postcondizione: Se il contenuto dei due file confrontati è identico, deve essere scritto su risultato il messaggio indicante 
il successo, altrimenti viene scritto un messaggio di fallimento. Tutti i file aperti dovranno essere correttamente chiusi alla 
fine della funzione. In caso di errore nell’apertura di uno dei file, viene stampato un messaggio di errore sullo standard output 
e la funzione termina senza apportare modifiche al file di “risultato”. */
void verifica_test(char *file_oracolo, char *risultato) {
    FILE *f_oracolo=fopen(file_oracolo, "r");
    FILE *f_output=fopen("TC_OUTPUT.txt", "r");

    if(!f_oracolo || !f_output){
        printf("Errore nell'apertura dei file oracolo o output.\n");
        if (f_oracolo) fclose(f_oracolo);
        if (f_output) fclose(f_output);
        return;
    }
    
    //Confronto riga per riga.
    int successo=1;
    char buf_oracolo[1024], buf_output[1024];
    while (1){
        char *riga_oracolo=fgets(buf_oracolo, sizeof(buf_oracolo), f_oracolo);
        char *riga_output=fgets(buf_output, sizeof(buf_output), f_output);
        
        //Se entrambe le letture hanno successo, confronta le stringhe.
        if (riga_oracolo && riga_output){

            buf_oracolo[strcspn(buf_oracolo, "\r\n")]='\0';
            buf_output[strcspn(buf_output, "\r\n")]='\0';

            if(strcmp(buf_oracolo, buf_output) != 0){
                successo=0;
                break;
            }
        }
        //Se entrambe hanno finito contemporaneamente, esci.
        else if(!riga_oracolo && !riga_output){
            break;
        }
        //Se uno solo dei due file è terminato, i file sono differenti.
        else {
            successo=0;
            break;
        }
    }

    fclose(f_oracolo);
    fclose(f_output);

    char tc[20];
    sscanf(file_oracolo, "%[^_]", tc);

    FILE *f_risultato=fopen(risultato, "a");
    if(f_risultato == NULL){
        printf("Errore nell'apertura del file!\n");
        return;
    }

    fprintf(f_risultato, "%s: %s\n", tc, successo ? "SUCCESSO" : "FALLIMENTO");
    fclose(f_risultato);
}


/* Funzione: libera_memoria.
------------------------------------------------------------------------------------------
La funzione dealloca tutta la memoria dinamica occupata dalle attività della 
lista per evitare memory leak, prima del termine di esecuzione della fz main.
------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: libera_memoria(lista_att*) -> void
Tipi: lista_att*.
SPECIFICA SEMANTICA: libera_memoria(l) -> void
-Side-effect: Deallocazione memoria di ogni nodo della lista, incluse le stringhe allocate 
dinamicamente in ciascun nodo (nome, descrizione, corso di appartenenza), modifica puntatore 
della lista a NULL.
-Precondizione: Il puntatore l deve essere inizializzato (la lista può essere vuota o piena).
-Postcondizione: Tutta la memoria dinamica allocata per ogni attività della lista deve essere 
stata correttamente rilasciata. Il puntatore alla lista deve puntare a NULL, rendendo la lista
non più accessibile. */
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