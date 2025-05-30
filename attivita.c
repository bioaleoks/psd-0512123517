/* File attività.c
Implementazione ADT "Attivita" e delle relative fz base. 
Autore: Alessia Plaitano 
Data creazione: 6 Maggio 2025 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"
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


/* Funzione: aggiungi_attivita.
------------------------------------------------------------------------------------------
La funzione alloca dinamicamente una nuova attività e, attraverso gli
input dell'utente, compila i vari campi della struct, assicurandosi che gli input
siano validi (formato data e valore priorità). In caso negativo, chiede all'utente
di re-immetterli. Controlla, inoltre, se l'allocaz. dinamica è avvenuta correttamente.
Prima di terminare, stampa un messaggio di successo (o insuccesso) dell'operazione.
------------------------------------------------------------------------------------------ 
SPECIFICA SINTATTICA: aggiungi_attivita(lista_att) -> lista_att
Tipi: lista_att.
SPECIFICA SEMANTICA: aggiungi_attivita(l) -> nuovo
-Side-effect: Allocazione dinamica della memoria per il nuovo nodo e per le stringhe dei campi 
nome, descrizione, corso_appartenenza, eventuale deallocazione in caso di errore, scrittura sul 
file di output dei messaggi di feedback, modifica della struttura della lista.
-Precondizione: l è una lista di attività valida (che può essere anche vuota). L’input dell’utente
deve rispettare i vincoli richiesti per i vari campi: formato corretto delle date e valore di priorità
compreso tra 1 e 3. 
-Postcondizione: Se l’allocazione dinamica fallisce, la funzione deve restituire NULL e stampare 
un messaggio di errore. Se tutti gli input dell’utente sono validi, deve essere allocata una nuova 
attività che sarà collegata alla lista esistente e restituita come nuova testa della lista. Se l’input 
non è valido, deve essere richiesto nuovamente l’inserimento fino a ottenere un dato corretto, grazie 
all’iterazione dei cicli while. */
lista_att aggiungi_attivita(lista_att l){
    struct attivita *nuovo;
    nuovo=malloc(sizeof(struct attivita));
    if(nuovo==NULL){
        printf("Allocazione fallita!\n\n");
        return NULL;
    } 

    struct data data_scadenza, d_inserimento;
    int t_stimato, t_trascorso, priorita;
    char nome[50], descrizione[150], corso_appartenenza[100];

    printf("Per inserire una nuova attivita', compila i seguenti campi: \n");
    printf("-Nome attivita': ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")]=0;

    printf("-Corso di appartenenza: ");
    fgets(corso_appartenenza, sizeof(corso_appartenenza), stdin);
    corso_appartenenza[strcspn(corso_appartenenza, "\n")]=0;

    printf("-Descrizione: ");
    fgets(descrizione, sizeof(descrizione), stdin);
    descrizione[strcspn(descrizione, "\n")]=0;

    while(1){
        //Il ciclo termina solo se l'utente inserisce una data di scadenza valida.
        printf("-Data di scadenza (formato gg-mm-aaaa): ");
        if(scanf("%d-%d-%d", &data_scadenza.giorno, &data_scadenza.mese, &data_scadenza.anno)!= 3 ||
            data_scadenza.giorno<1 || data_scadenza.giorno>31 || 
            data_scadenza.mese<1 || data_scadenza.mese>12){
            printf("\nData errata: inserisci una data valida nel formato specificato.\n");
            while(getchar()!='\n');
        } else break;
    }

    while(1){
        //Il ciclo termina solo se l'utente inserisce una data di scadenza valida.
        printf("-Data di inserimento (formato gg-mm-aaaa): ");
        if(scanf("%d-%d-%d", &d_inserimento.giorno, &d_inserimento.mese, &d_inserimento.anno)!= 3 ||
            d_inserimento.giorno<1 || d_inserimento.giorno>31 || 
            d_inserimento.mese<1 || d_inserimento.mese>12){
            printf("\nData errata: inserisci una data valida nel formato specificato.\n");
            while(getchar()!='\n');
        } else break;
    }

    while(1){
        //Il ciclo termina solo se l'utente inserisce un valore valido per "priorità".
        printf("-Priorita' (1=bassa, 2=media, 3=alta): ");
        if(scanf("%d", &priorita)!= 1 || priorita<1 || priorita>3){
            printf("\nErrore: inserisci un numero valido compreso tra 1 e 3.\n");
            while(getchar()!='\n');
        } else break;
    }

    printf("-Tempo stimato per completare l'attivita' (in ore): ");
    scanf("%d", &t_stimato);

    printf("-Tempo gia' trascorso (in ore): ");
    scanf("%d", &t_trascorso);
    
    nuovo->nome=malloc(strlen(nome)+1);
    nuovo->descrizione=malloc(strlen(descrizione)+1);
    nuovo->corso_appartenenza=malloc(strlen(corso_appartenenza)+1);

    if(!nuovo->nome || !nuovo->descrizione || !nuovo->corso_appartenenza){
        //Controllo complessivo della memoria allocata dinamicamente.
        printf("\nSi è verificato un errore nell'inserimento.\n\n\n");
        free(nuovo->nome);
        free(nuovo->descrizione);
        free(nuovo->corso_appartenenza);
        free(nuovo);
        return NULL;
    }
    
    strcpy(nuovo->nome,nome);
    strcpy(nuovo->descrizione, descrizione);
    strcpy(nuovo->corso_appartenenza, corso_appartenenza);
    nuovo->data_scadenza=data_scadenza;
    nuovo->priorita=priorita;
    nuovo->t_stimato=t_stimato;
    nuovo->t_trascorso=t_trascorso;
    nuovo->successivo=l;

    printf("\n\nNuova attivita' aggiunta con successo!\n\n\n");
    return nuovo;
}


/* Funzione: rimuovi_attivita.
------------------------------------------------------------------------------------------------------
La funzione chiede all'utente di immettere il nome dell' attività da rimuovere e la ricerca nella 
lista. Distingue i casi: lista vuota o piena (con i sottocasi: elemento da eliminare in 1a posizione 
o in mezzo/in ultima posiz.). A conclusione dell'operazione, stampa un messaggio di successo o 
insuccesso, a seconda del caso verificatosi.
------------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: rimuovi_attivita(lista_att) -> lista_att
Tipi: lista_att.
SPECIFICA SEMANTICA: rimuovi_attivita(l) -> l
-Side-effect: Modifica struttura della lista, deallocazione della memoria precedentemente allocata
dinamicamente per il nodo da rimuovere.
-Precondizioni: l è una lista di attività valida (che può essere anche vuota). L’utente deve inserire 
un nome valido per la ricerca dell’attività.
-Postcondizioni: Se l'attività è presente, deve venire rimossa dalla lista e la lista aggiornata deve 
essere restituita. Se l'attività non è trovata, perché non presente o perché la lista è vuota, la lista 
originale deve essere restituita senza modifiche. In entrambi i casi, è stampato un messaggio per l’utente 
per informarlo riguardo l’esito dell’operazione di rimozione. */
lista_att rimuovi_attivita(lista_att l){
    struct attivita *corrente=l, *precedente=NULL;
    char nome[50];
    printf("Inserisci il nome dell'attivita' da eliminare: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")]=0;
    
    while(corrente != NULL){
        if(strcmp(corrente->nome, nome)==0){
            if(precedente == NULL){
                //Caso: l'attività da eliminare è la prima della lista.
                l=corrente->successivo;
            } else{
                //Caso: l'attività da eliminare è in mezzo alla lista o è l'ultima (in tal caso, gestione implicita).
                //Se è l'ultima: corrente->successivo=NULL, quindi precedente->successivo=NULL.
                precedente->successivo=corrente->successivo;
            }
            free(corrente->nome);
            free(corrente->corso_appartenenza);
            free(corrente->descrizione);
            free(corrente);
            printf("\n\nAttivita' correttamente rimossa.\n\n\n");
            return l; //Lista aggiornata.
        }
        precedente=corrente;
        corrente=corrente->successivo;
    }

    printf("\n\nAttivita' non trovata in programma.\n\n\n");
    return l; //Lista originale.
}


/* Funzione: aggiornamento_progresso
-------------------------------------------------------------------------------------------------
La funzione permette di aggiornare il campo "t_trascorso" della struct attività e ne stampa 
il progresso percentuale rispetto a "t_stimato". Se i due campi risultano uguali, fa scegliere 
all'utente se reputare l'attività completata o aggiornare il campo "t_stimato", stampandone la 
nuova percentuale. 
-------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: aggiornamento_progresso(lista_att) -> int
Tipi: lista_att, int.
SPECIFICA SEMANTICA: aggiornamento_progresso(l)-> int
-Side-effect: Modifica dei campi t_trascorso, ed eventualmente t_stimato, dell’attività selezionata.
-Precondizione: l è una lista di attività valida (che può essere anche vuota). L'utente deve immettere un nome valido
per la ricerca dell'attività da aggiornare e valori int validi per t_trascorso_agg (e, se richiesto, per t_stimato_agg).
-Postcondizione: Se l'attività indicata viene trovata nella lista, il campo t_trascorso deve essere aggiornato e, se 
necessario, deve essere aggiornato anche il campo t_stimato, sempre su scelta dell’utente; in entrambi i casi, viene 
stampata la percentuale del progresso, calcolata implicitamente dalla funzione. Se l’attività viene trovata e ne è 
eseguito l’aggiornamento, la funzione deve restituire 1. Se l’attività non viene trovata, la funzione non deve modificare 
la lista e deve restituire 0. */
int aggiornamento_progresso(lista_att l){
    struct attivita *corrente;
    int t_trascorso_agg, val, t_stimato_agg, percentuale;
    char nome[50];
    printf("Inserisci il nome dell'attivita' di cui vuoi aggiornare il progresso: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")]=0;
    printf("Inserisci il tempo trascorso aggiornato (in ore): ");
    scanf("%d", &t_trascorso_agg);

    for(corrente=l; corrente!=NULL; corrente=corrente->successivo){
        if((strcmp(corrente->nome, nome)== 0)){
            corrente->t_trascorso=t_trascorso_agg;
            if(corrente->t_stimato > corrente->t_trascorso){ 
               //Aggiorna con numeri positivi il valore t_stimato.
               percentuale=(corrente->t_trascorso*100)/corrente->t_stimato;
               printf("\nLa tua percentuale di progresso e' %d %%\n\n\n", percentuale);
            }
            else {
                printf("\nIl tempo trascorso e' maggiore o uguale del tempo stimato.\n");
                printf("Digita 1 se vuoi aggiornare il tempo stimato, altrimenti l'attivita' sara' considerata completata: \n");
                scanf("%d", &val);
                if(val==1){
                    printf("\n\nInserisci il nuovo tempo stimato (in ore): \n");
                    scanf("%d", &t_stimato_agg);
                    corrente->t_stimato=t_stimato_agg;
                    printf("\nTempo stimato aggiornato!\n");
                    if(corrente->t_stimato>0){
                       percentuale=(corrente->t_trascorso*100)/corrente->t_stimato;
                       printf("La tua percentuale di progresso e' %d %%\n\n\n", percentuale);
                    }
                } else printf("\n\nComplimenti, hai completato l'attivita' con successo!\n\n\n");
            }
        return 1; //Attività trovata e modificata.
        }
    }
    printf("\nAttivita' non trovata.\n\n\n");
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


/* Funzione: report_settimanale.
-----------------------------------------------------------------------------------------------
La funzione chiede all'utente di immettere la settimana corrente, con
un controllo di validità. Considera il caso lista vuota e lista con almeno un'attività.
Attraversando la lista, per ogni attività, ne stampa i campi e, attraverso il valore
restituito dalla fz scadenza_att, definisce se queste sono in corso, complete o scadute.
Attenzione: la fz stamperà solo le attività inserite entro la fine della settimana immessa. 
------------------------------------------------------------------------------------------------
SPECIFICA SINTATTICA: report_settimanale(lista_att*) -> void
Tipi: lista_att.
SPECIFICA SEMANTICA: report_settimanale(*l) -> void
-Side-effect: Modifica struttura della lista (ordinamento), eventuale aggiunta di un nodo su scelta dell’utente.
-Precondizione: Il puntatore l deve essere inizializzato (la lista passata può essere vuota oppure contenere una 
o più attività). Le strutture data_inserimento e data_scadenza devono contenere valori validi. L’utente deve 
immettere le date nel formato corretto (gg-mm-aaaa) con valori validi (giorno da 1 a 31 e mese da 1 a 12).
-Postcondizione: Se la lista è vuota, la funzione deve chiedere all'utente se vuole inserire una nuova attività, 
aggiornando eventualmente la lista. La funzione deve effettuare una serie di stampe a video, in ordine di priorità 
decrescente (grazie alla chiamata a ordina_per_priorita), delle attività inserite entro la data limite specificata 
(fine_sett). Per ogni attività stampata, deve esserne indicato lo stato tra scaduta, in corso o completata. Non deve 
restituire nessun valore. */
void report_settimanale(lista_att* l){
    ordina_per_priorita(l);
    struct attivita *corrente=*l;
    struct data inizio_sett, fine_sett;
    int val, scadenza, percentuale;

    while(1){
        //Il ciclo termina solo se l'utente inserisce una data valida.
        printf("Inserisci il primo giorno della settimana (formato gg-mm-aaaa): ");
        if(scanf("%d-%d-%d", &inizio_sett.giorno, &inizio_sett.mese, &inizio_sett.anno)!= 3 ||
            inizio_sett.giorno<1 || inizio_sett.giorno>31 ||
            inizio_sett.mese<1 || inizio_sett.mese>12){
            printf("\nData non valida, inseriscine un'altra nel formato specificato.\n");
            while(getchar()!='\n');
        } else break;
    }

    while(1){
        //Il ciclo termina solo se l'utente inserisce una data valida.
        printf("Inserisci l'ultimo giorno della settimana (formato gg-mm-aaaa): ");
        if(scanf("%d-%d-%d", &fine_sett.giorno, &fine_sett.mese, &fine_sett.anno)!= 3 ||
            fine_sett.giorno<1 || fine_sett.giorno>31 ||
            fine_sett.mese<1 || fine_sett.mese>12){
            printf("\nData non valida, inseriscine un'altra nel formato specificato.\n");
            while(getchar()!='\n');
        } else break;
    }

    if(corrente==NULL){ //Lista vuota.
        printf("\nNessuna attivita' trovata per questa settimana!\n");
        printf("Digita 1 se vuoi inserirne una adesso, altrimenti 0 per uscire: \n\n"); 
        scanf("%d", &val); 
        while(getchar()!='\n'); 
        if(val==1){ 
           *l=aggiungi_attivita(*l); 
           corrente=*l; 
        } else{ 
           return; 
        } 
    }
    
    printf("\n************************************************************************************************************");
    printf("\nEcco un report settimanale delle attivita' inserite entro questa settimana, ordinate per priorita' maggiore!");
    printf("\n************************************************************************************************************\n\n");
    while(corrente!=NULL){
        //Se l'attività è stata aggiunta entro il giorno di fine settimana, stampala.
        if (corrente->data_inserimento.anno<fine_sett.anno ||
            (corrente->data_inserimento.anno==fine_sett.anno && corrente->data_inserimento.mese<fine_sett.mese) ||
            (corrente->data_inserimento.anno==fine_sett.anno && corrente->data_inserimento.mese==fine_sett.mese && 
            corrente->data_inserimento.giorno<=fine_sett.giorno)){

            printf("Nome: %s\n", corrente->nome);
            printf("Corso di appartenenza: %s\n", corrente->corso_appartenenza);
            printf("Descrizione: %s\n", corrente->descrizione);
            printf("Data di scadenza: %d-%d-%d\n", corrente->data_scadenza.giorno, corrente->data_scadenza.mese, corrente->data_scadenza.anno);
            printf("Data di inserimento: %d-%d-%d\n", corrente->data_inserimento.giorno, corrente->data_inserimento.mese, corrente->data_inserimento.anno);
            printf("Priorita': %d\n", corrente->priorita);
            printf("Tempo stimato: %d ore\n", corrente->t_stimato);
            printf("Tempo trascorso: %d ore\n", corrente->t_trascorso); 

            scadenza=scadenza_att(corrente->data_scadenza, fine_sett);
            //scadenza=0 se non è scaduta l'attività, altrimenti 1.

           if(scadenza==1)
                printf("L'attivita' e' scaduta!\n\n");
            else if(corrente->t_stimato==corrente->t_trascorso || corrente->t_stimato==0)
                    printf("L'attivita' e' stata completata con successo!\n\n");
                 else { 
                    percentuale=(corrente->t_trascorso*100)/corrente->t_stimato;
                    printf("L'attivita' e' in corso, con una percentuale di completamento %d %%!\n\n", percentuale);
                }
        }
           
        corrente=corrente->successivo;
        }
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