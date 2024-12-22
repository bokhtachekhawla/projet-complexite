#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct {
    int n;
    double time_insert;
    double time_search;
    double time_delete;
} results;

int inserer_tas(int A[], int n, int valeur) {
    n = n + 1;
    A[n] = valeur;
    int i = n;
    int temp;

    while (i > 1 && A[i] > A[i / 2]) {
        temp = A[i];
        A[i] = A[i / 2];
        A[i / 2] = temp;
        i = i / 2;
    }
    return n;
}

int recherche_tas(int A[], int n, int valeur) {
    int i;
    for (i = 1; i <= n; i++) {
        if (A[i] == valeur) {
            return i;
        }
    }
    return -1;
}

int supprimer_tas(int A[], int n, int valeur,int index) {

    A[index] = A[n];
    n = n - 1;
    int i = index;
    int temp;

    // Sift up or down to maintain heap property
    while (i > 1 && A[i] > A[i / 2]) {
        temp = A[i];
        A[i] = A[i / 2];
        A[i / 2] = temp;
        i = i / 2;
    }
    while (2 * i <= n) {
        int j = 2 * i;
        if (j < n && A[j] < A[j + 1]) j++;
        if (A[i] >= A[j]) break;
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        i = j;
    }
    return n;
}

void afficher_tas(int A[], int n) {
    int i;
    for (i = 1; i <= n; i++) {
        printf("| %d ", A[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    LARGE_INTEGER frequency, start, end;
    double temps_ecoule;
    int A[10001];
    results res[10];
    int n, random_number, i, t, j, v;
    int num_trials = 100;
    double total_time_insert = 0.0;
    double total_time_search = 0.0;
    double total_time_delete = 0.0;

    if (!QueryPerformanceFrequency(&frequency)) {
        fprintf(stderr, "High-performance counter not supported.\n");
        return 1;
    }

    for (n = 1000; n <= 10000; n += 1000) {
        total_time_insert = 0.0;
        total_time_search = 0.0;
        total_time_delete = 0.0;

        for (j = 0; j < num_trials; j++) {
            t = 0;
            for (i = 0; i < n; i++) {
                random_number = rand();
                t = inserer_tas(A, t, random_number);
            }

            random_number = rand();
            QueryPerformanceCounter(&start);
            t = inserer_tas(A, t, random_number);
            QueryPerformanceCounter(&end);
            temps_ecoule = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e6;
            total_time_insert += temps_ecoule;


            QueryPerformanceCounter(&start);
            v = recherche_tas(A, t, random_number);
            QueryPerformanceCounter(&end);
            temps_ecoule = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e6;
            total_time_search += temps_ecoule;


            QueryPerformanceCounter(&start);
            t = supprimer_tas(A, t, random_number,v);
            QueryPerformanceCounter(&end);
            temps_ecoule = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e6;
            total_time_delete += temps_ecoule;
        }

        res[(n / 1000) - 1].n = n;
        res[(n / 1000) - 1].time_insert = total_time_insert / num_trials;
        res[(n / 1000) - 1].time_search = total_time_search / num_trials;
        res[(n / 1000) - 1].time_delete = total_time_delete / num_trials;

        printf("%d\t%.6f\t%.6f\t%.6f\n", n, res[(n / 1000) - 1].time_insert,
               res[(n / 1000) - 1].time_search, res[(n / 1000) - 1].time_delete);
    }

    return 0;
}
