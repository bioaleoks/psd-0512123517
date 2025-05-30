/*File mergesortList.h:
Definizione modulo fz MergeSort relativa all'ADT "Attività".
Autore: Alessia Plaitano 
Data creazione: 10 Maggio 2025 */
#include "attivita.h"
#include "attivitatest.h" //Poichè è un modulo che viene riutilizzato 
                          //per l'attività di testing automatico.


//Prototipi delle funzioni utilizzate per l'ordinamento attraverso MergeSort:


// trova_meta: trova il punto medio della lista ad essa passata.
struct attivita* trova_meta(struct attivita* head);

// unione_liste: unisce due liste in una sola e la restituisce.
struct attivita* unione_liste(struct attivita* lista1, struct attivita* lista2);

/* mergesort_lista: usa il metodo di ordinamento MergeSort
per ordinare una lista. E' una fz ricorsiva che presenta
due chiamate a se stessa, nel ciclo di una sola esecuzione. */
struct attivita* mergesort_lista(struct attivita* head);