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
    int A[5]; 
    int t = 0,i;  
    int valeur, index;

    // Exemple d'insertion
    printf("Insertion des elements 10, 20, 5, 60 dans le tas...\n");
    t = inserer_tas(A, t, 10);
    t = inserer_tas(A, t, 20);
    t = inserer_tas(A, t, 5);
    t = inserer_tas(A, t, 60);
    printf("Tas apres insertion : ");
    afficher_tas(A,t);
    printf("\n");

    // Exemple de recherche
    valeur = 20;
    printf("Recherche de la valeur %d dans le tas...\n", valeur);
    index = recherche_tas(A, t, valeur);
    if (index != -1) {
        printf("Valeur trouvee a l'indice %d.\n\n", index);
    } else {
        printf("Valeur non trouvee.\n");
    }

    // Exemple de suppression
    printf("Suppression de la valeur %d dans le tas...\n", valeur);
    if (index != -1) {
        t = supprimer_tas(A, t, valeur, index);
        printf("Tas apres suppression : ");
        afficher_tas(A,t);
        printf("\n");
    } else {
        printf("Valeur non trouvee, suppression impossible.\n");
    }

    return 0;
}
