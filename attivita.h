//File attività.h INTERFACCIA ADT: ATTIVITA'

typedef struct attivita *lista_att;
//Prototipi fz base:

//Crea nuova lista attività:
lista_att nuova_lista_att(void);

//Aggiunge 1 attività alla lista:
lista_att nuova_attivita(const char *nome, const char *descrizione, const char *data_scadenza, int priorita, int t_stimato, int t_trascorso, lista_att l);

//Rimuove un'attività secondo il nome:
lista_att elimina_attivita(lista_att l, const char *nome);

//Modifica del progresso di un'attività (=tempo trascorso in un nodo):
int monitoraggio_progresso(lista_att l,char *nome, int t_trascorso_nuovo);

//ordina lista scompone in 3 liste ognuna con 1 priorità diversa
//e poi le concatena in un'unica lista ordinata da priorità 3 ad 1:
lista_att *ordina_per_priorita(lista_att *l);

//fz per verificare la scadenza di un'attività:
int scadenza_att(const char *data_scadenza, int giorno_corrente, int mese_corrente, int anno_corrente);

//Stampa punto della situazione progresso attività:
void report_settimanale(lista_att);