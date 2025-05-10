//File mergesortList.h:
//Definizione modulo fz MergeSort relativa all'ADT "Attività".
#include "attivita.h"

/* mergesort_lista: usa il metodo di ordinamento MergeSort
per ordinare una lista. E' una fz ricorsiva che presenta
due chiamate a se stessa, nel ciclo di una sola esecuzione. */
struct attivita* mergesort_lista(struct attivita* head);

//Prototipi delle sotto-funzioni usate nell'implementazione:

// trova_meta: trova il punto medio della lista passata.
struct attivita* trova_meta(struct attivita* head);

// unione_liste: unisce due liste in una sola e la restituisce.
struct attivita* unione_liste(struct attivita* lista1, struct attivita* lista2);

