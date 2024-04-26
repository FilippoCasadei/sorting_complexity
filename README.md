# Sorting_complexity

Progetto personale durante lo studio di "Algoritmi e Strutture Dati" incentrato sulla complessità degli algoritmi di ordinamento per array.


### OBIETTIVO

L'obiettivo era quello di avere un modo per visualizzare la complessità degli algoritmi di ordinamento per gli array tramite la creazione di una tabella.


### ALGORITMI DI ORDINAMENTO

* Bubble sort
* Selection sort
* Insertion sort
* Merge sort
* Quick sort
* Heap sort



### TABELLE

Le tabelle sono formate da:

* *intestazione*

  * array di stringhe contenenti il nome di ogni variabile
* 7 *colonne* di dati (ogni colonna viene trattata come un array)

  * Dimensione array [N]: variabile indipendente costante che può essere modificata in base alla scelta personale
  * 6 algoritmi di ordinamento: variabili dipendenti dalla variabile N
* NOTA: il numero di *record* dipende dalla dimensione scelta per la colonna N


Le due tabelle, che è possibile creare, si basano sui seguenti criteri scelti per calcolare la complessità:

1. Tempo di esecuzione
2. Passi base eseguiti dall'algoritmo


*Esempio di tabella*

**TEMPO DI ESECUZIONE (ms) / PASSI ESEGUITI**

|  n  | bubble | select | insert | merge | quick | heap |
| :--: | ------ | ------ | ------ | ----- | ----- | ---- |
| 500 |        |        |        |       |       |      |
| 1000 |        |        |        |       |       |      |
| 2000 |        |        |        |       |       |      |
| 5000 |        |        |        |       |       |      |
| ... |        |        |        |       |       |      |



### PROGAMMI

Sono stati implementati due programmi simili per la realizzazione del progetto:

###### sorting_complexity.c

* fa scegliere all'utente di quale delle due tabelle è interessato
* popola le colonne in base al metodo scelto dall'utente
* stampa nel terminale la tabella richiesta

###### sorting_complexity_csv.c

* popola le colonne in base al tempo di esecuzione
* stampa la tabella nel file "tempo.csv" nella formattazione "valori separati da virgola"
* popola le colonne in base ai passi base eseguiti
* stampa la tabella nel file "passi.csv"


### LIBRERIE

###### sorting_library.h

* Contiene le sei funzioni di ordinamento.

###### sorting_steps_library.h

* Contiene le sei funzioni di ordinamento che restituiscono la variabile "steps" che viene aggiornata ad ogni passo base eseguito durante la funzione.

###### testing.h

* Contiene la funzione per la stampa degli array utilizzata durante il periodo di testing e debugging.
