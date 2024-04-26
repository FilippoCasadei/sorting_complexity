#include <stdlib.h>
#include "sorting_library.h"

void bubble_sort(int a[], int n)
{
    int tmp,
        i,
        j;

    for (i = 1;
         (i < n);
         i++)
        for (j = n - 1;
             (j >= i);
             j--)
            if (a[j] < a[j - 1])
            {
                tmp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = tmp;
            }
}

void selection_sort(int a[], int n)
{
    int i,
        j,
        indice_min,
        valore_min;
    
    for (i = 0;
         i < n - 1;
         i++)
    {
        for (j = i + 1, indice_min = i, valore_min = a[i];
             j < n;
             j++)
            if (a[j] < valore_min)
            {
                valore_min = a[j];
                indice_min = j;
            }
        if (indice_min != i)
        {
            a[indice_min] = a[i];
            a[i] = valore_min;
        }
    }
}

void insertion_sort(int a[], int n)
{
    int i,
        j,
        ins;
    
    for (i = 1;
         i < n;
         i++)
    {
        for (j = i - 1, ins = a[i];
             (ins < a[j]) && (j >= 0);
             j--)
            {
                a[j + 1] = a[j];
                a[j] = ins;
            }
    }
}

void merge(int a[], int sx, int mx, int dx)
{
    int *b, i, j, k; 
    
    b = (int *)calloc(dx-sx+1, sizeof(int));   

    for (i = sx, j = mx+1, k = 0;
         (i <= mx) && (j <= dx);
         k++)
    {
        if (a[i] < a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
    }

    while (i <= mx)
    {
        b[k] = a[i];
        k++;
        i++;
    }
    while (j <= dx)
    {
        b[k] = a[j];
        k++;
        j++;
    }

    for (k = sx; k <= dx; k++)
        a[k] = b[k-sx];
    
    free(b);
}

void merge_sort(int a[], int sx, int dx)
{
    int mx;

    if (sx < dx)
    {
        mx = (sx + dx) / 2;
        merge_sort(a, sx, mx);
        merge_sort(a, mx+1, dx);
        merge(a, sx, mx, dx);
    }
}

void quick_sort(int a[], int sx, int dx)
{
    int i, j, p, tmp;
    
    // prendiamo il pivot come elemento centrale e continuiamo finche' i non oltrepassa j
    for (i = sx, j = dx, p = a[(sx+dx)/2];
         i <= j;)
    {
        // aggiorna gli indici in base a confronto del loro valore con il pivot
        while (a[i] < p)
            i++;

        while (a[j] > p)
            j--;

        if (i <= j)
        {
            // esegui scambio solo se due elementi sono in posizioni differenti
            if (i < j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            // aggiorna gli indici 
            i++;
            j--;
        }
    }
    // esegui ordinamento sul sottoarray prima di pivot e su quello successivo
    
    // esegui solamente se sottoarray hanno dimensione maggiore di 1
    if (sx < j)
        quick_sort(a, sx, j);
    if (dx > i)
        quick_sort(a, i, dx);
}

// Funzione per scambiare due elementi di un array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funzione per mantenere la proprietà di heap massimo
void heapify(int arr[], int n, int i) {
    int largest = i; // Inizializziamo il più grande come radice
    int left = 2 * i + 1; // Calcoliamo l'indice del figlio sinistro
    int right = 2 * i + 2; // Calcoliamo l'indice del figlio destro

    // Se il figlio sinistro è più grande della radice
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se il figlio destro è più grande del più grande finora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se il più grande non è la radice
    if (largest != i) {
        // Scambiamo la radice con il più grande
        swap(&arr[i], &arr[largest]);
        // Ricorsivamente fare heapify sul sottoalbero colpito
        heapify(arr, n, largest);
    }
}

// Funzione per eseguire heap sort
void heap_sort(int arr[], int n) {
    // Costruiamo un heap (riorganizziamo l'array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Estraiamo uno per uno gli elementi dall'heap
    for (int i = n - 1; i > 0; i--) {
        // Muoviamo la radice corrente alla fine
        swap(&arr[0], &arr[i]);
        // richiamiamo l'heapify sul ridotto heap
        heapify(arr, i, 0);
    }
}