/* File mergesortList.c
Implementazione delle funzioni necessarie per la codica del metodo
di ordinamento MergeSort relativo all'ADT "Attività". */
#define ATTIVITA_INTERNA
#include <stdlib.h>
#include "attivita.h"
#include "mergesortList.h"

struct attivita{
    char *nome;
    char *corso_appartenenza;
    char *descrizione;
    struct data data_scadenza;
    int priorita;
    int t_stimato;
    int t_trascorso;
    struct attivita *successivo;
};

/* trova_meta: trova il punto medio (l'attività posta
al centro) della lista e lo restituisce. Costituisce il primo
passo di MergeSort e di ogni sua chiamata ricorsiva. Viene
chiamata se la lista passata contiene più di un elemento. */
struct attivita* trova_meta(struct attivita* head){
    if(head==NULL || head->successivo==NULL) return head;
    struct attivita *lento=head, *veloce=head->successivo;
    while(veloce && veloce->successivo){
        lento=lento->successivo;
        veloce=veloce->successivo->successivo;
    }
    return lento;
}

/* unione_liste: unisce due liste ordinate per "priorità". E' la
fase finale del metodo MergeSort e di ogni sua chiamata ricorsiva.
Viene chiamata se la lista passata contiene più di un elemento. */
struct attivita* unione_liste(struct attivita* lista1, struct attivita* lista2) {
    if(lista1==NULL) return lista2;
    if(lista2==NULL) return lista1;
    if(lista1->priorita >= lista2->priorita){
        lista1->successivo=unione_liste(lista1->successivo, lista2);
        return lista1;
    } else{
        lista2->successivo=unione_liste(lista1, lista2->successivo);
        return lista2;
    }
}

/* mergesort_lista: restituisce la lista passata riordinata secondo il
parametro "priorità". Si serve di due funzioni trova_meta e unione_list
per effettuare i passi del metodo di ordinamento MergeSort. Inoltre, è 
una fz ricorsiva che presenta, per ogni chiamata, due chiamate a se stessa. */
struct attivita* mergesort_lista(struct attivita* head) {
    //se la lista è vuota o ha un solo elemento, è considerata già ordinata.
    if(head==NULL || head->successivo==NULL) return head;
    struct attivita* meta=trova_meta(head);
    struct attivita* seconda_meta=meta->successivo;
    meta->successivo=NULL;
    struct attivita* sinistra=mergesort_lista(head);
    struct attivita* destra=mergesort_lista(seconda_meta);
    return unione_liste(sinistra, destra);
}