#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For high precision timing

// Afficher le tas
void afficher_tas(int A[], int n) {
    int i;
    for (i = 1; i <= n; i++) {
        printf("| %d ", A[i]);
    }
    printf("|\n");
}

// Fonction pour insérer un élément dans un tas (O(log n))
int inserer_tas(int A[], int t, int valeur) {
    t = t + 1;
    A[t] = valeur;
    int i = t, temp;
    while (i > 1 && A[i] > A[i / 2]) { // Maintenir la propriété de tas maximal
        temp = A[i];
        A[i] = A[i / 2];
        A[i / 2] = temp;
        i = i / 2;
    }
    return t;
}

// Construction d'un tas avec O(n log n)
void construire_tas(int init[], int A[], int n) {
    int t = 0, i;
    for (i = 0; i < n; i++) {
        t = inserer_tas(A, t, init[i]);
    }
}

// Fonction pour rétablir la propriété de tas (tasifier) en O(log n)
void entasser(int A[], int n, int i) {
    int max = i;
    int gauche = 2 * i;
    int droite = 2 * i + 1;

    if (gauche <= n && A[gauche] > A[max])
        max = gauche;

    if (droite <= n && A[droite] > A[max])
        max = droite;

    if (max != i) {
        int temp = A[i];
        A[i] = A[max];
        A[max] = temp;
        entasser(A, n, max);
    }
}

// Construction d'un tas en O(n)
void construire_tas_n(int init[], int A[], int n) {
    int i;
    for (i = 1; i <= n; i++) { // O(n)
        A[i] = init[i - 1];
    }
    for (i = n / 2; i >= 1; i--) { // O(log(n))
        entasser(A, n, i);
    }
}

// Suppression du maximum dans un tas en O(log n)
int supprimer_max_tas(int A[], int n) {
    int max_value = A[1];
    A[1] = A[n]; // Remplacer la racine par le dernier élément
    n = n - 1;
    entasser(A, n, 1); // Rétablir la propriété de tas O(log(n))
    return max_value;
}

// Fonction pour trier un tableau en utilisant un tas
void construire_tab_trie(int T[], int n) {
    int i;
    for (i = n; i >= 1; i--) {
        int max_value = supprimer_max_tas(T, i);
        T[i] = max_value;
    }
}

int main() {
    int init[10001], A1[10001], A2[10001];
    LARGE_INTEGER frequency, start, end;
    double t_construct_nlogn, t_construct_n, t_sort_nlogn, t_sort_n, total_timen, total_timenlogn;
    int n;

    // Get the frequency of the high-resolution performance counter
    QueryPerformanceFrequency(&frequency);

    printf("N | Construct O(n log n) | Sort O(n log n) | Total O(n log n) | Construct O(n) | Sort O(n log n) | Total O(n)\n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for (n = 1000; n <= 10000; n += 1000) {
        // Generate random initial array
        srand(time(NULL));
        int i;
        for (i = 0; i < n; i++) {
            init[i] = rand() % 10000;
        }

        // Construct heap using O(n log n)
        QueryPerformanceCounter(&start);
        construire_tas(init, A1, n);
        QueryPerformanceCounter(&end);
        t_construct_nlogn = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        // Sort the heap constructed with O(n log n)
        QueryPerformanceCounter(&start);
        construire_tab_trie(A1, n);
        QueryPerformanceCounter(&end);
        t_sort_nlogn = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        total_timenlogn = t_construct_nlogn + t_sort_nlogn;

        // Construct heap using O(n)
        QueryPerformanceCounter(&start);
        construire_tas_n(init, A2, n);
        QueryPerformanceCounter(&end);
        t_construct_n = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        // Sort the heap constructed with O(n)
        QueryPerformanceCounter(&start);
        construire_tab_trie(A2, n);
        QueryPerformanceCounter(&end);
        t_sort_n = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        total_timen = t_construct_n + t_sort_n;

        // Print the results in microseconds
        printf("%d | %.2f ms       | %.2f ms   | %.2f ms   | %.2f ms       | %.2f ms   | %.2f ms\n",
               n, t_construct_nlogn, t_sort_nlogn, total_timenlogn, t_construct_n, t_sort_n, total_timen);
    }

    return 0;
}
