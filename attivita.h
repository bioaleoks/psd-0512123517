/* File attivita.h
Definizione interfaccia ADT "Attività" e prototipi 
delle fz dell'insieme base. */
typedef struct attivita *lista_att;

#ifndef attivita_h
#define attivita_h
struct data {
    int giorno;
    int mese;
    int anno;
};

#endif

//Prototipi dell'insieme delle funzioni di base:

/* nuova_lista: crea nuova lista vuota di attività.
Non richiede un'interazione con l'utente. */
lista_att nuova_lista_att(void);

/* aggiungi_attivita: aggiunge un'attività alla lista,
secondo le informazioni inserite dall'utente. */
lista_att aggiungi_attivita(lista_att l);

/* rimuovi_attivita: rimuove un'attività 
selezionata dall'utente dalla lista. */
lista_att rimuovi_attivita(lista_att l);

/* aggiornamento_progresso: permette all'utente di aggiornare i 
campi "tempo trascorso" e "tempo stimato" di un'attività, 
calcolandone anche la relativa percentuale di progresso. */
int aggiornamento_progresso(lista_att l);

/* ordina_per_priorita: ordina la lista delle attività in base al
parametro "priorità", dal grado 3 al grado 1, usando l'algoritmo
di ordinamento MergeSort. Viene usata dalla fz report_settimale,
senza un uso esplicito da parte dell'utente. */
void ordina_per_priorita(lista_att *l);

/* scandeza_att: stabilisce se un'attività ha superato la data di scadenza, 
confrontandola con la data di fine settimana, ricevuta in input dall'utente.
E' una fz non usata espicitamente dall'utente ma usata dalla fz report_settimanale. */
int scadenza_att(struct data data_scadenza, struct data fine_sett);

/* report_settimanale: stampa, per ogni attività inserita entro la settimana
selezionata, i relativi campi e mostra se esse sono state completate, sono in
corso oppure sono scadute, in relazione alla data inserita dall'utente. */
void report_settimanale(lista_att *l);

/* libera_memoria: libera la memoria allocata dinamicamente per ogni 
attività della lista. Non è usata dall'utente e viene chiamata prima 
che l'esecuzione del programma termini. */
void libera_memoria(lista_att *l);