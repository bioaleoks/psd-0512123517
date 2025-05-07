//file attività.c
#include <stdio.h>
#include <stdlib.h> //per allocazione dinamica
#include "attività.h"

//def. nodo lista lista_att
struct compito{
    char *nome;
    char *descrizione;
    char data_scadenza[11]; //formato gg-mm-aaaa
    int priorità;
    int t_stimato;
    int t_trascorso;
    struct compito *next;
};

lista_att nuova_lista_att(void){
    return NULL;
};

lista_att nuovo_compito(char *nome, char *descrizione, char *data_scadenza, int priorità, int t_stimato, int t_trascorso, lista_att l){
    struct compito *nuovo;
    nuovo=malloc(sizeof(struct compito));
    if(nuovo==NULL){
        printf("Allocazione fallita!\n");
        exit (EXIT_FAILURE);
    }  
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
    if(data_scadenza!=NULL){  //se è stata inserita correttamente
        strncpy(nuovo->data_scadenza, data_scadenza, sizeof(nuovo->data_scadenza)-1);
    } else {
        printf("C'è un errore nell'inserimento della data di scadenza!\n");
    }
    nuovo->priorità=priorità;
    nuovo->t_stimato=t_stimato;
    nuovo->t_trascorso=t_trascorso;
    nuovo->next=l;
    l=nuovo;
    return l;
}

//Modifica del tempo trascoro di un'attività (in un nodo):
int monitoraggio_progresso(lista_att l,char *nome, int t_trascorso_nuovo){
    struct compito *corrente;
    for(corrente=l; corrente!=NULL; corrente=corrente->next){ //attraverso lista
        if( (strcmp(corrente->nome, nome)== 0)){//cerco nodo che voglio
        corrente->t_trascorso=t_trascorso_nuovo;
        if(corrente->t_stimato>=corrente->t_trascorso) //aggiorna con numeri positivi t_stimato
        corrente->t_stimato=(corrente->t_stimato - t_trascorso_nuovo);
        return 1; //successo modifica
        }
    }
    return 0; //nodo non trovato
}


       





