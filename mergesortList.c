/* File mergesortList.c
Implementazione delle funzioni necessarie per la codica del metodo
di ordinamento MergeSort relativo all'ADT "Attività". 
Autore: Alessia Plaitano 
Data creazione: 10 Maggio 2025 */
#include <stdlib.h>
#include "attivita.h"
#include "attivitatest.h"
#include "mergesortList.h"

//Def. attivita, nodo della lista lista_att
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


/* Funzione: trova_meta.
----------------------------------------------------------------------------
La fz trova il punto medio (l'attività posta al centro) della lista e lo 
restituisce. Costituisce il primo passo di MergeSort e di ogni sua chiamata 
ricorsiva. Viene chiamata se la lista passata contiene più di un elemento. 
----------------------------------------------------------------------------
SPECIFICA SINTATTICA: trova_meta(struct attivita*) -> struct attivita*
Tipi: struct attivita*.
SPECIFICA SEMANTICA: trova_meta(head) -> struct attivita*
-Side-effect: Nessuno.
-Precondizione: l è una lista di attività valida (che può essere anche vuota).
-Postcondizione: Se la lista contiene più di un elemento, la funzione deve 
restituire il puntatore all'elemento centrale (punto medio) della lista. Se 
la lista è vuota o contiene un solo elemento, deve essere restituito head. */
struct attivita* trova_meta(struct attivita* head){
    if(head==NULL || head->successivo==NULL) return head;
    struct attivita *lento=head, *veloce=head->successivo;
    while(veloce && veloce->successivo){
        lento=lento->successivo;
        veloce=veloce->successivo->successivo;
    }
    return lento;
}

/* Funzione: unione_liste.
---------------------------------------------------------------------
La funzione unisce due liste ordinate per "priorità". E' la
fase finale del metodo MergeSort e di ogni sua chiamata ricorsiva.
Viene chiamata se la lista passata contiene più di un elemento. 
---------------------------------------------------------------------
SPECIFICA SINTATTICA: unione_liste(struct attivita*, struct attivita*) -> struct attivita*
Tipi: struct attivita*.
SPECIFICA SEMANTICA: unione_liste(lista1, lista2)  -> struct attivita*
-Side-effect: Modifica dei campi puntatore “successivo” del nodo di lista1 oppure di 
lista2 con modifica consequenziale della struttura della lista.
-Precondizione: Le liste lista1 e lista2 devono essere state precedentemente ordinate 
in ordine decrescente rispetto al campo priorità. I puntatori delle liste possono anche 
essere NULL se la lista risulta vuota.
-Postcondizione: Deve essere restituita una lista contenente tutti gli elementi di lista1 
e lista2, ordinati in maniera decrescente secondo priorità. L’unione deve avvenire utilizzando
chiamate ricorsione di sé stessa sulle due sotto-liste. */
struct attivita* unione_liste(struct attivita* lista1, struct attivita* lista2){
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

/* Funzione: mergesort_lista.
----------------------------------------------------------------------------
La funzione restituisce la lista passata riordinata secondo il
parametro "priorità". Si serve di due funzioni trova_meta e unione_list
per effettuare i passi del metodo di ordinamento MergeSort. Inoltre, è 
una fz ricorsiva che presenta, per ogni chiamata, due chiamate a se stessa.
---------------------------------------------------------------------------- 
SPECIFICA SINTATTICA: mergesort_lista(struct attivita*) -> struct attivita*
Tipi: struct attivita*.
SPECIFICA SEMANTICA: mergesort_lista(head) -> struct attività*
-Side-effect: Modifica ricorsiva della struttura della lista in due sottoliste 
separate che vengono poi ricollegate per essere ordinate.
-Precondizione: La lista passata tramite il puntatore head deve essere inizializzata
(può essere vuota) e, se contiene più di un elemento, gli elementi devono avere un 
valore valido per il campo priorita.
-Postcondizione: Deve essere restituita la lista head riordinata in modo tale che gli
elementi siano disposti in ordine decrescente rispetto al campo priorita (con l'elemento
con la priorità più alta in testa). Se la lista è vuota o contiene un solo elemento, allora
deve essere restituita invariata. */
struct attivita* mergesort_lista(struct attivita* head){
    //se la lista è vuota o ha un solo elemento, è considerata già ordinata.
    if(head==NULL || head->successivo==NULL) return head;
    struct attivita* meta=trova_meta(head);
    struct attivita* seconda_meta=meta->successivo;
    meta->successivo=NULL;
    struct attivita* sinistra=mergesort_lista(head);
    struct attivita* destra=mergesort_lista(seconda_meta);
    return unione_liste(sinistra, destra);
}