//File attività.h INTERFACCIA ADT: ATTIVITA'

typedef struct attivita *lista_att;
//Prototipi fz base:

//Crea nuova lista attività:
lista_att nuova_lista_att(void);
//Aggiunge 1 attività alla lista:
lista_att nuova_attivita(const char *nome, const char *descrizione, const char *data_scadenza, int priorita, int t_stimato, int t_trascorso, lista_att l);
//Modifica del progresso di un'attività (=tempo trascorso in un nodo):
int monitoraggio_progresso(lista_att l,char *nome, int t_trascorso_nuovo);
//ordina lista scompone in 3 liste ognuna con 1 priorità diversa
//e poi le concatena in un'unica lista ordinata da priorità 3 ad 1:
lista_att *ordina_per_priorita(lista_att *l);
//Stampa punto della situazione progresso attività:
void report_settimanale(lista_att);