//File attività.h INTERFACCIA ADT: ATTIVITA'

typedef struct compito *lista_att;
//Prototipi fz base:

//Crea nuova lista attività:
lista_att nuova_lista_att(void);
//Aggiunge 1 attività alla lista:
lista_att nuovo_compito(char titolo, char descrizione, char scadenza, int tempo_stimato, int tempo_trascorso, int priorità, lista_att);
//Modifica del progresso di un'attività (=tempo trascorso in un nodo):
void progresso_compito(lista_att);
//Stampa punto della situazione progresso compiti:
void report_settimanale(lista_att);