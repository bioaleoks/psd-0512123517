//file attività.c
#include <stdio.h>
#include <stdlib.h> //per allocazione dinamica
#include <string.h>
#include "attivita.h"

//def. data scadenza
struct data{
    int giorno;
    int mese;
    int anno;
};
//def. nodo lista lista_att
struct attivita{
    char *nome;
    char *corso_appartenenza;
    char *descrizione;
    struct data data_scadenza; //formato gg-mm-aaaa
    int priorita;
    int t_stimato;
    int t_trascorso;
    struct attivita *successivo;
};

//Crea nuova lista attività:
lista_att nuova_lista_att(void){
    return NULL;
};

//Aggiunge 1 attività alla lista:
lista_att nuova_attivita(lista_att l){
    struct attivita *nuovo;
    nuovo=malloc(sizeof(struct attivita));
    if(nuovo==NULL){
        printf("Allocazione fallita!\n");
        exit (EXIT_FAILURE);
    } 
    struct data data_scadenza;
    int t_stimato, t_trascorso, priorita;
    char nome[50], descrizione[150], corso_appartenenza[100];
    printf("Per inserire una nuova attività, compila i seguenti campi: \n");
    printf("-Nome attività: \n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")]=0; // Rimuove \n

    printf("-Corso di appartenenza: \n");
    fgets(corso_appartenenza, sizeof(corso_appartenenza), stdin);
    corso_appartenenza[strcspn(corso_appartenenza, "\n")]=0;

    printf("-Descrizione: \n");
    fgets(descrizione, sizeof(descrizione), stdin);
    descrizione[strcspn(descrizione, "\n")] = 0;

    printf("-Data di scadenza (formato gg-mm-aaaa): \n");
    scanf("%d-%d-%d", &data_scadenza.giorno, &data_scadenza.mese, &data_scadenza.anno);
    
    printf("-Priorità (1=bassa, 2=media, 3=alta): \n");
    scanf("%d", &priorita);

    printf("-Tempo stimato per completare l'attività (in ore): \n");
    scanf("%d", &t_stimato);

    printf("-Tempo già trascorso (in ore): \n");
    scanf("%d", &t_trascorso);
    while(getchar()!='\n');  // pulizia buffer input

    nuovo->nome=malloc(strlen(nome)+1);
    if(nuovo->nome==NULL){
    printf("Allocazione fallita!\n");
    free(nuovo); //via nodo sennò memory leak
    exit (EXIT_FAILURE);
    }
    strcpy(nuovo->nome,nome);  // Copia stringa

    nuovo->descrizione=malloc(strlen(descrizione)+1);
    if(nuovo->descrizione==NULL){
        printf("Allocazione fallita!\n");
        free(nuovo->nome);
        free(nuovo); //senza descrizione, fallisce tutto
        exit (EXIT_FAILURE);
        }
        strcpy(nuovo->descrizione, descrizione); //copia stringa

    nuovo->corso_appartenenza = malloc(strlen(corso_appartenenza) + 1);
    if (nuovo->corso_appartenenza == NULL) {
    printf("Errore di allocazione!\n");
    free(nuovo->nome);
    free(nuovo->descrizione);
    free(nuovo);
    exit(EXIT_FAILURE);
    }
    strcpy(nuovo->corso_appartenenza, corso_appartenenza);

    nuovo->data_scadenza=data_scadenza;
    nuovo->priorita=priorita;
    nuovo->t_stimato=t_stimato;
    nuovo->t_trascorso=t_trascorso;
    nuovo->successivo=l;
    return nuovo;
}

//Rimuove un'attività secondo il nome:
lista_att *elimina_attivita(lista_att l){
    struct attivita corrente=l;
    struct attivita *precedente=NULL;
    char nome[50];
    printf("Inserisci il nome dell'attività da eliminare: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0; // Rimuovi \n
    
    while(corrente != NULL){   //scorre lista
        if(strcmp(corrente->nome, nome)==0){ // Se il nome corrisponde, elimina
            if(precedente == NULL){
                // Il nodo da eliminare è il primo della lista
                *l=corrente->successivo;
            } else{
                // Il nodo da eliminare è in mezzo alla lista
                precedente->successivo=corrente->successivo;
            }
            free(corrente->nome);
            free(corrente->corso_appartenenza);
            free(corrente->descrizione);
            free(corrente);
            return l; //lista aggiornata
        }
        precedente=corrente;
        corrente=corrente->successivo;
    }
    printf("Attività non trovata in programma.\n"); 
    return l; // attività non trovata->restituisce lista originale
}

//Modifica del tempo trascoro di un'attività (in un nodo):
int aggiornamento_progresso(lista_att l){
    struct attivita *corrente;
    int t_trascorso_agg, val, t_stimato_agg, percentuale;
    char nome[50];
    printf("Inserisci il nome dell'attività di cui vuoi aggiornare il progresso: \n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")]=0; // rimuove \n
    printf("Inserisci il tempo trascorso aggiornato (in ore): \n");
    scanf("%d", &t_trascorso_agg);
    while (getchar() != '\n'); // pulizia buffer input

    for(corrente=l; corrente!=NULL; corrente=corrente->successivo){ //attraverso lista
        if((strcmp(corrente->nome, nome)== 0)){//cerco nodo che voglio
            corrente->t_trascorso=t_trascorso_agg;
        if(corrente->t_stimato>=corrente->t_trascorso){ //aggiorna con numeri positivi t_stimato
            corrente->t_stimato=(corrente->t_stimato - t_trascorso_agg);
            percentuale=(corrente->t_trascorso*100)/corrente->t_stimato;
            printf("La tua percentuale di progresso è %d %", percentuale);
        }
        else {
            printf("Il tempo trascorso è maggiore del tempo stimato. \n");
            printf("Digita 1 se vuoi aggiornarlo, altrimenti l'attività sarà considerata completata: \n");
            scanf("%d", &val);
            if(val==1){
                printf("Inserisci il nuovo tempo stimato (in ore): \n");
                scanf("%d", &t_stimato_agg);
                corrente->t_stimato=t_stimato_agg;
                printf("Tempo stimato aggiornato!");
                if(corrente->t_stimato>0){
                percentuale=(corrente->t_trascorso*100)/corrente->t_stimato;
                printf("La tua percentuale di progresso è %d %", percentuale);
                }
            } else printf("Complimenti, hai completato l'attività con successo!");
            }
        return 1; // nodo trovato e modificato
        }
    }
    printf("Attività non trovata.\n");
    return 0;
}

//ordina lista scompone in 3 liste ognuna con 1 priorità diversa
//e poi le concatena in un'unica lista ordinata da priorità 3 ad 1:
lista_att ordina_per_priorita(lista_att *l){
    if (l==NULL || (*l)->successivo==NULL){
        return l; // Lista vuota o con un solo elemento, già ordinata
    }
    struct attivita *priorita3=NULL, *priorita2=NULL, *priorita1=NULL;
    struct attivita *corrente=*l;
    // Divisione in tre liste diverse:
    while(corrente!=NULL){
        struct attivita *successivo=corrente->successivo;
        if(corrente->priorita==3){
            corrente->successivo=priorita3;
            priorita3=corrente;
        } else if(corrente->priorita==2){
                corrente->successivo=priorita2;
                priorita2=corrente;
                } else { //priorità=1
                corrente->successivo=priorita1;
                priorita1=corrente;
                }
        corrente=successivo;
    }
    // Concatenazione delle liste: priorità alta -> media -> bassa
    if(priorita3 != NULL){
        corrente=priorita3;
        while(corrente->successivo != NULL){
            corrente=corrente->successivo;
        }
        corrente->successivo=priorita2; //concaten. priorità3 e priorità2
    } else{
        priorita3=priorita2;
    }
    if(priorita3 != NULL){
        corrente=priorita3;
        while(corrente->successivo != NULL){
            corrente=corrente->successivo;
        }
        corrente->successivo=priorita1; //concaten. priorità3-2 e priorità1
    } else {
        priorita3=priorita1;
    }
    *l=priorita3;
    return l; // Lista ordinata rispetto le priorità
}

//fz per verificare la scadenza di un'attività:
int scadenza_att(const char *data_scadenza, int giorno_corrente, int mese_corrente, int anno_corrente){
    int giorno, mese, anno;
    sscanf(data_scadenza, "%d-%d-%d", &giorno, &mese, &anno);
    // Confronto diretto date
    if(anno<anno_corrente) return 1; //scaduta
    if(anno==anno_corrente && mese<mese_corrente) return 1; //scaduta
    if(anno==anno_corrente && mese==mese_corrente && giorno<giorno_corrente) return 1; //scaduta
    return 0; //valida
}

//Stampa punto della situazione progresso attività:
void report_settimanale(lista_att l){
    struct attivita *corrente=l;
    int giorno_corrente, mese_corrente, anno_corrente, scadenza, percentuale;
    printf("Inserisci la data di oggi (formato gg-mm-aaaa): \n");
    scanf("%d-%d-%d",&giorno_corrente,&mese_corrente,&anno_corrente);
    printf("Ecco un report settimanale delle tue attività:\n");
    while(corrente!=NULL){  //attraversa l'intera lista
        printf("Nome: %s\n", corrente->nome);
        printf("Corso di appartenenza: %s\n", corrente->corso_appartenenza);
        printf("Descrizione: %s\n", corrente->descrizione);
        printf("Data di scadenza: %s\n", corrente->data_scadenza);
        printf("Priorità: %d\n", corrente->priorita);
        printf("Tempo stimato: %d ore\n", corrente->t_stimato);
        printf("Tempo trascorso: %d ore\n", corrente->t_trascorso); 
        scadenza=scadenza_att(corrente->data_scadenza, giorno_corrente, mese_corrente, anno_corrente);
        //0 se non è scaduto, 1 se è scaduto
        if(scadenza==1)
           printf("L'attività è scaduta!\n\n");
        else if(corrente->t_stimato==corrente->t_trascorso || corrente->t_stimato==0)
             printf("L'attività è stata completata con successo!\n\n");
        else { 
            percentuale=(corrente->t_trascorso*100)/corrente->t_stimato;
            printf("L'attività è in corso, con una percentuale di completamento %d%!\n\n", percentuale);
        }
        corrente=corrente->successivo;
        }
}