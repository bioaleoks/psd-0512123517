/* File attività.c
Implementazione ADT "Attivita" e delle relative fz base. */
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


// nuova_lista: crea nuova lista di attività vuota.
lista_att nuova_lista_att(void){
    return NULL;
}


/* aggiungi_attivita: alloca dinamicamente una nuova attività e, attraverso gli
input dell'utente, compila i vari campi della struct, assicurandosi che gli input
siano validi (formato data e valore priorità). In caso negativo, chiede all'utente
di re-immetterli. Controlla, inoltre, se l'allocaz. dinamica è avvenuta correttamente.
Prima di terminare, stampa un messaggio di successo (o insuccesso) dell'operazione. */
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


/* rimuovi_attivita: chiede all'utente di immettere il nome dell'
attività da rimuovere e la ricerca nella lista. Distingue i casi: 
lista vuota o piena (con i sottocasi: elemento da eliminare in 1a
posizione o in mezzo/in ultima posiz.). A conclusione dell'operazione, 
stampa un messaggio di successo o insuccesso, a seconda del caso verificatosi. */
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


/* aggiornamento_progresso: permette di aggiornare il campo "t_trascorso"
della struct attività e ne stampa il progresso percentuale rispetto a "t_stimato". 
Se i due campi risultano uguali, fa scegliere all'utente se reputare l'attività 
completata o aggiornare il campo "t_stimato", stampandone la nuova percentuale. */
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


/* report_settimanale: chiede all'utente di immettere la settimana corrente, con
un controllo di validità. Considera il caso lista vuota e lista con almeno un'attività.
Attraversando la lista, per ogni attività, ne stampa i campi e, attraverso il valore
restituito dalla fz scadenza_att, definisce se queste sono in corso, complete o scadute.
Attenzione: la fz stamperà solo le attività inserite entro la fine della settimana immessa. */
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

    printf("\nEcco un report settimanale delle attivita' inserite entro questa settimana, ordinate per priorita' maggiore!\n\n");

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