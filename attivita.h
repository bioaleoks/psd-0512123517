//File attività.h INTERFACCIA ADT: ATTIVITA'

typedef struct attivita *lista_att;

//def. data scadenza
struct data{
    int giorno;
    int mese;
    int anno;
};
//Prototipi fz base:

//Crea nuova lista attività:
lista_att nuova_lista_att(void);

//Aggiunge 1 attività alla lista:
lista_att aggiungi_attivita(lista_att l);

//Rimuove un'attività secondo il nome:
lista_att rimuovi_attivita(lista_att l);

//Modifica del progresso di un'attività (=tempo trascorso in un nodo):
int aggiornamento_progresso(lista_att l);

//ordina lista scompone in 3 liste ognuna con 1 priorità diversa
//e poi le concatena in un'unica lista ordinata da priorità 3 ad 1:
lista_att ordina_per_priorita(lista_att l);

//fz per verificare la scadenza di un'attività:
int scadenza_att(struct data data_scadenza, int giorno_corrente, int mese_corrente, int anno_corrente);

//Stampa punto della situazione progresso attività:
void report_settimanale(lista_att);