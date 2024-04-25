/* INCLUSIONE LIBRERIE*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting_library.h"
#include "sorting_steps_library.h"
#include "testing.h"

/* DEFINIZIONE COSTANTI*/
#define VAR_INDIP 1
#define VAR_DIP   6
#define VAR_TOT   7
#define RECORD    11
#define ARR_DIMENSIONI  {500, 1000, 2000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000}
#define ARR_ATTIBUTI    {"n", "bubble", "select", "insert", "merge", "quick", "heap", NULL}
#define BUBBLE  0
#define SELECT  1
#define INSERT  2
#define MERGE   3
#define QUICK   4
#define HEAP    5

/* DICHIARAZIONE FUNZIONI */
void riempi(int *a[], const int n[]);
int *genera_array(int n);
int scegli_tabella();
int *copia_array(int a[], int n);
void popola_colonna(double col_var[], const int col_n[], int *arr[], int var, int tab);
void calcola_algoritmo(int a[], int n, int var);
double calcola_tempo(int a[], int n, int var);
double calcola_passi(int a[], int n, int var);
void stampa_tabella(const char *HEADER[], const int COL_N[], double col0[], double col1[], double col2[], double col3[], double col4[], double col5[], int tab);
void stampa_header(const char *HEADER[]);

/* DEFINIZIONE FUNZIONE MAIN */
int main()
{
    int tab;    // scelta della tabella da stampare 
    // colonna n: array contenente i valori di n per gli array da ordinare
    const int COL_N[] = ARR_DIMENSIONI;

    // header della tabella: array contenente i nomi degli attributi
    const char *HEADER[] = ARR_ATTIBUTI;

    int *arr[RECORD];     // array contenente tutti gli array da usare per ogni dimensione n
    
    // array contenenti per ogni algoritmo il rispettivo tempo di esecuzione rispetto alla dimensione n dell'array
	double  col_bubble[RECORD],
		    col_select[RECORD],
		    col_insert[RECORD],
		    col_merge[RECORD],
		    col_quick[RECORD],
		    col_heap[RECORD];

    // genera array di array per ogni valore di n
    riempi(arr, COL_N);
    
    // scegli quale tabella stampare
    tab = scegli_tabella();

    // ? SI POTREBBE ANCHE CREARE UNA FUNZIONE CHE CALCOLA DIRETTAMENTE TUTTO (SERVIREBBE UN ARRAY CONTENENTE I 6 ARRAY)
    // popola le colonne delle variabili dipendenti in base alla scelta tab
    popola_colonna(col_bubble, COL_N, arr, BUBBLE, tab);
    popola_colonna(col_select, COL_N, arr, SELECT, tab);
    popola_colonna(col_insert, COL_N, arr, INSERT, tab);
    popola_colonna(col_quick, COL_N, arr, QUICK, tab);
    popola_colonna(col_merge, COL_N, arr, MERGE, tab);
    popola_colonna(col_heap, COL_N, arr, HEAP, tab);

    // stampa tabella in base alla scelta tab
    stampa_tabella(HEADER, COL_N, col_bubble, col_select, col_insert, col_merge, col_quick, col_heap, tab);    
    
    return 0;
}


/* DEFINIZIONI FUNZIONI */

int scegli_tabella()
{
    int tab;
    
    printf("Scegli la tabella da stampare digitando il numero tra le due possibilita' (0, 1):\n"
           "[0] TEMPO DI ESECUZIONE\n"
           "[1] PASSI DI ESECUZIONE\n");
    // ! MANCA IL CONTROLLO
    scanf("%d", &tab);

    return tab;
}

// riempie l'array contenente gli array da ordinare per ogni dimensione
void riempi(int *a[],
            const int COL_N[])
{
    int i;

    // i-esimo array viene generato di dimensione n i-esima
    for (i = 0; i < RECORD; i++)
        a[i] = genera_array(COL_N[i]);
}

// genera un array di dimensione n e restituisce il suo puntatore
int *genera_array(int n)   // dimensione array passata per indirizzo
{
    int i,
        *a,     // array a cui allocheremo memoria
        max;    // valore massimo che puo' assumere l'array [0, max]
    
    // alloca la memoria all'array
    a = (int *)malloc(n * sizeof(int));
    if (a == NULL) 
    {
        printf("Errore: impossibile allocare memoria per l'array.\n");
        exit(EXIT_FAILURE);
    }
    
    // inizializza generatore di numeri a seed sempre diverso
    srand(time(NULL));

    // riempi con numeri pseudocasuali l'array
    for (i = 0, max = 3 * n;
         i < n;
         i++)
        // genera numero tra 0 e max
        a[i] = rand() % max;

    // restituisci l'indirizzo del primo elemento dell'array
    return a;
}

// copia il contenuto di 'a' in un array 'b' che viene generato della dimensione n
int *copia_array(int a[],
                 int n)
{
    int i,
		*b;		// array secondario

	// alloca la memoria all'array secondario
    b = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        b[i] = a[i];
	
	return b;
}

double calcola_tempo(int a[],   // array da ordinare 
                     int n,     // dimensione array
                     int var)   // identificatore funzione di ordinamento
{
    clock_t start,   // inizio cronometro   
            end;     // fine cronometro
    double  tempo_esecuzione;	// tempo di esecuzione per una funzione

    // registra il tempo di inizio
    start = clock();

    // esegui la tua funzione da misurare
    calcola_algoritmo(a, n, var);
            
    // registra il tempo di fine
    end = clock();

    // calcola il tempo trascorso in microsecondi
    tempo_esecuzione = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;  // CCLOCKS_PER_SEC == 1000

    return tempo_esecuzione;
}

// popola una colonna della tabella di una variabile dipendente
void popola_colonna(double col_var[],		// colonna di un variabile dipendente
				 	const int COL_N[], 		// colonna della variabile indipendente (dimensioni)
                    int *arr[],             // array contenente gli array generati per ogni dimensione
				 	int var,                // valore che identifica la variabile dipendente
                    int tab)	            // valore che identifica la tabella scelta        
{   
	int i,
		*arr_appoggio;      // array di appoggio copia dell'array di dimensione n[i]

	for (i = 0; i < RECORD; i++)
	{
		// genera array di appoggio come copia di arr[i]
		arr_appoggio = copia_array(arr[i], COL_N[i]);
        
        // tabella tempo di esecuzione
        if (tab == 0)
            col_var[i] = calcola_tempo(arr_appoggio, COL_N[i], var);
        // tabella numero di passi
        else
		    col_var[i] = calcola_passi(arr_appoggio, COL_N[i], var);
        
        // libera gli array usati per la dimensione n[i]
        free(arr_appoggio);
	}
}

// applica algoritmo di ordinamento scelto da var sull'array a di dimensine n
void calcola_algoritmo(int a[],      // array da ordinare
                       int n,        // dimensione array
                       int var)      // valore che identifica la funzione di ordinamento
{

    switch (var)
    {
    case BUBBLE:
        bubble_sort(a, n);
        break;
    case SELECT:
        selection_sort(a, n);
        break;
    case INSERT:
        insertion_sort(a, n);
        break;
    case MERGE:
        merge_sort(a, 0, n-1);
        break;
    case QUICK:
        quick_sort(a, 0, n-1);
        break;
    case HEAP:
        heap_sort(a, n);
        break;
    default:
        break;
    }
}

// calcola e restituisce la funzione di ordinamento scelta in base al valore di input 'algoritmo'
double calcola_passi(int a[],      // array da ordinare
                     int n,        // dimensione array
                     int var)      // valore che identifica la funzione di ordinamento
{
    double passi;      // passi compiuti per completare ordinamento 

    switch (var)
    {
    case BUBBLE:
        passi = bubble_sort_steps(a, n);
        break;
    case SELECT:
        passi = selection_sort_steps(a, n);
        break;
    case INSERT:
        passi = insertion_sort_steps(a, n);
        break;
    case MERGE:
        passi = merge_sort_steps(a, 0, n-1);
        break;
    case QUICK:
        passi = quick_sort_steps(a, 0, n-1);
        break;
    case HEAP:
        passi = heap_sort_steps(a, n);
        break;
    default:
        break;
    }

    return passi;
}

// funzione per stampare la tabella dei valori
void stampa_tabella(const char *HEADER[],       // intestazione tabella
                    const int COL_N[],          // colonna dimensioni
                    double col0[], double col1[], double col2[], double col3[], double col4[], double col5[],     // colonne algoritmi ordinamento
                    int tab)                    // identificatore tabella
{
	int i;

    printf("\n");
    // tabella tempo di esecuzione
    if (tab == 0)
        printf("TEMPO DI ESECUZIONE (millisecondi)\n");
    // tabella passi di esecuzione
    else
        printf("PASSI DI ESECUZIONE\n");

    // stampa intestazione
    stampa_header(HEADER);

    // stampa colonne
	for (i = 0; i < RECORD; i++)
	    printf("%-10d| %-10.0f| %-10.0f| %-10.0f| %-10.0f| %-10.0f| %-10.0f|\n", COL_N[i], col0[i], col1[i], col2[i], col3[i], col4[i], col5[i]);
}

void stampa_header(const char *HEADER[])
{
    int i;

    // stampa intestazione
    for (i = 0; HEADER[i] != NULL; i++)
        printf("%-10s| ", HEADER[i]);
    printf("\n");
    
    // Stampa della linea di trattini
    for (i = 0; i < VAR_TOT; i++) {
        printf("----------| ");
    }
    printf("\n");
}