//file attività.c
#include <stdio.h>
#include <stdlib.h> //per allocazione dinamica
#include <string.h>
#include "attivita.h"

//def. nodo lista lista_att
struct attivita{
    char *nome;
    char *corso_appartenenza;
    char *descrizione;
    char data_scadenza[11]; //formato gg-mm-aaaa
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
lista_att nuova_attivita(const char *nome, const char *descrizione, const char *data_scadenza, int priorita, int t_stimato, int t_trascorso, lista_att l){
    struct attivita *nuovo;
    nuovo=malloc(sizeof(struct attivita));
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
    nuovo->priorita=priorita;
    nuovo->t_stimato=t_stimato;
    nuovo->t_trascorso=t_trascorso;
    nuovo->successivo=l;
    l=nuovo;
    return l;
}

//Rimuove un'attività secondo il nome:
lista_att elimina_attivita(lista_att l, const char *nome){
    struct attivita *corrente=l;
    struct attivita *precedente=NULL;
    while(corrente != NULL){
        if (strcmp(corrente->nome, nome)==0){ // Se il nome corrisponde, elimina
            if (precedente == NULL) {
                // Il nodo da eliminare è il primo della lista
                l=corrente->successivo;
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
    printf("Attività non trovata.\n"); 
    return l; // attività non trovata->restituisce lista originale
}

//Modifica del tempo trascoro di un'attività (in un nodo):
int monitoraggio_progresso(lista_att l,char *nome, int t_trascorso_nuovo){
    struct attivita *corrente;
    for(corrente=l; corrente!=NULL; corrente=corrente->successivo){ //attraverso lista
        if( (strcmp(corrente->nome, nome)== 0)){//cerco nodo che voglio
        corrente->t_trascorso=t_trascorso_nuovo;
        
        if(corrente->t_stimato>=corrente->t_trascorso) //aggiorna con numeri positivi t_stimato
        corrente->t_stimato=(corrente->t_stimato - t_trascorso_nuovo);
        return 1; //successo modifica
        }
    }
    return 0; //nodo non trovato
}

//ordina lista scompone in 3 liste ognuna con 1 priorità diversa
//e poi le concatena in un'unica lista ordinata da priorità 3 ad 1:
lista_att *ordina_per_priorita(lista_att *l){
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