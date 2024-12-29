#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>


// Fonction pour calculer la somme des éléments d'un tableau
int somme(int tableau[], int taille) {
    int total = 0,i;
    for ( i = 0; i < taille; i++) {
        total += tableau[i];
    }
    return total;
}

// Fonction pour vérifier si deux ensembles sont disjoints
bool verifier_intersection(int S1[], int taille_S1, int S2[], int taille_S2) {
    int i,j;
    for ( i = 0; i < taille_S1; i++) {
        for ( j = 0; j < taille_S2; j++) {
            if (S1[i] == S2[j]) {
                return false; // Si un élément commun est trouvé
            }
        }
    }
    return true; // Pas d'éléments communs
}

// Fonction pour vérifier si l'union de S1 et S2 correspond à S
bool verifier_union(int S[], int taille_S, int S1[], int taille_S1, int S2[], int taille_S2) {
    int marqueurs[100] = {0} , i; // Tableau de comptage (assume des valeurs ≤ 100)

    // Marquer les éléments de S
    for ( i = 0; i < taille_S; i++) {
        marqueurs[S[i]]++;
    }

    // Soustraire les éléments de S1
    for ( i = 0; i < taille_S1; i++) {
        marqueurs[S1[i]]--;
    }

    // Soustraire les éléments de S2
    for ( i = 0; i < taille_S2; i++) {
        marqueurs[S2[i]]--;
    }

    // Vérifier si tous les marqueurs sont à zéro
    for ( i = 0; i < 100; i++) {
        if (marqueurs[i] != 0) {
            return false;
        }
    }
    return true;

    //Complexité temporelle: O(n), où n est la taille du plus grand tableau parmi S, S1 et S2.
}

// Fonction principale pour vérifier les partitions
bool verifier_partitions(int S[], int taille_S, int S1[], int taille_S1, int S2[], int taille_S2) {
    // Vérifier si les sommes des partitions sont égales
    if (somme(S1, taille_S1) != somme(S2, taille_S2)) {
        return false;
    }

    // Vérifier si les deux partitions sont disjointes
    if (!verifier_intersection(S1, taille_S1, S2, taille_S2)) {
        return false;
    }

    // Vérifier si l'union des deux partitions correspond à l'ensemble original
    if (!verifier_union(S, taille_S, S1, taille_S1, S2, taille_S2)) {
        return false;
    }

    return true; // Toutes les conditions sont satisfaites
    //Complexité temporelle: O(n), où n est la taille du plus grand tableau parmi S, S1 et S2.
}

void fillArrayRandomly(int nums[], int size, int maxVal) {
    int i;
    for ( i = 0; i < size; i++) {
        nums[i] = rand() % maxVal;
    }
    // Complexité temporelle: O(n), où n est la taille du tableau.
}
// Function to calculate the sum of an array
int sumArray(int nums[], int size) {
    int sum = 0,i;
    for ( i = 0; i < size; i++) {
        sum += nums[i];
    }
    return sum;
    //Complexité temporelle: O(n), où n est la taille du tableau.
}

int main() {
    srand(time(0)); // Initialize the random number generator

    // Generate random size for S
    int taille_S = rand() % 10 + 1; // Random size between 1 and 10
    int S[taille_S];
    fillArrayRandomly(S, taille_S, 100); // Fill S with random values between 0 and 99
    int i;
    // Print the contents of S
    printf("S: ");
    for ( i = 0; i < taille_S; i++) {
        printf("%d ", S[i]);
    }
    printf("\n");

    // Calculate and print the sum of S
    int sum_S = sumArray(S, taille_S);
    printf("Sum of S: %d\n", sum_S);

    // Print if the size of S is even or odd
    printf("Size of S is %s\n", (taille_S % 2 == 0) ? "even" : "odd");


    // Generate random size for S1 and S2
    int taille_S1 = rand() % (taille_S / 2) + 1; // Random size between 1 and taille_S/2
    int taille_S2 = taille_S - taille_S1; // Ensure S1 and S2 together cover S

    int S1[taille_S1];
    int S2[taille_S2];
     for ( i = 0; i < taille_S1; i++) {
        S1[i] = S[i];
    }
    for ( i = 0; i < taille_S2; i++) {
        S2[i] = S[taille_S1 + i];
    }

    // Print the contents of S1 and S2
    printf("S1: ");
    for ( i = 0; i < taille_S1; i++) {
        printf("%d ", S1[i]);
    }
    printf("\n");

    printf("S2: ");
    for ( i = 0; i < taille_S2; i++) {
        printf("%d ", S2[i]);
    }
    printf("\n");
    // Calculate and print the sum of S1 and S2
    int sum_S1 = sumArray(S1, taille_S1);
    int sum_S2 = sumArray(S2, taille_S2);
    printf("Sum of S1: %d\n", sum_S1);
    printf("Sum of S2: %d\n", sum_S2);

    // Print if the size of S1 and S2 is even or odd
    printf("Size of S1 is %s\n", (taille_S1 % 2 == 0) ? "even" : "odd");
    printf("Size of S2 is %s\n", (taille_S2 % 2 == 0) ? "even" : "odd");

// Measure the time taken by verifier_partitions
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    bool result = verifier_partitions(S, taille_S, S1, taille_S1, S2, taille_S2);

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Time taken: %f seconds\n", elapsed);

    // Call the verification function
    if (result) {
        printf("Les partitions sont valides.\n");
    } else {
        printf("Les partitions ne sont pas valides.\n");
    }

    return 0;
}

