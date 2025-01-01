#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Fonction pour calculer la somme d'un tableau
int sumArray(int nums[], int size) {
    int sum = 0, i;
    for (i = 0; i < size; i++) {
        sum += nums[i];
    }
    return sum;
}

// Fonction pour calculer la somme des éléments d'un tableau
int somme(int tableau[], int taille) {
    int total = 0, i;
    for (i = 0; i < taille; i++) {
        total += tableau[i];
    }
    return total;
}

// Renvoie true s'il existe un sous-ensemble de `nums[]` avec la somme donnée
bool subsetSum(int nums[], int n, int sum, int subset[], int *subsetSize) {
    if (sum == 0) {
        return true;
    }
    if (n < 0 || sum < 0) {
        return false;
    }
    if (subsetSum(nums, n - 1, sum - nums[n], subset, subsetSize)) {
        subset[(*subsetSize)++] = nums[n];
        return true;
    }
    return subsetSum(nums, n - 1, sum, subset, subsetSize);
}

// Renvoie vrai si le tableau donné `nums[0...n-1]` peut être divisé en deux sous-ensembles avec une somme égale
bool partition(int nums[], int size, int S1[], int *taille_S1, int S2[], int *taille_S2) {
    int sum = sumArray(nums, size);
    if (sum % 2 != 0) {
        return false;
    }
    int halfSum = sum / 2;
    *taille_S1 = 0;
    *taille_S2 = 0;
    int i,j;
    bool found;
    bool found;
    if (subsetSum(nums, size - 1, halfSum, S1, taille_S1)) {
        for ( i = 0; i < size; i++) {
             found = false;
            for ( j = 0; j < *taille_S1; j++) {
                if (nums[i] == S1[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                S2[(*taille_S2)++] = nums[i];
            }
        }
        return true;
    }
    return false;
}

// Fonction pour remplir le tableau avec des valeurs aléatoires
void fillArrayRandomly(int nums[], int size, int maxVal) {
    int i;

    for ( i = 0; i < size; i++) {
        nums[i] = rand() % maxVal;
    }
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
    int marqueurs[100] = {0}; // Tableau de comptage (assume des valeurs ≤ 100)
    int i;
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
}

int main() {
    srand(time(0)); // Initialiser le générateur de nombres aléatoires

    int size, i;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *nums = (int *)malloc(size * sizeof(int));
    if (nums == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    fillArrayRandomly(nums, size, 100); // Remplir le tableau avec des nombres aléatoires entre 0 et 99

    // Print the contents of the array
    printf("Array contents: ");
    for (i = 0; i < size; i++) {
        printf("%d \t ", nums[i]);
    }
    printf("\n");

    int *S1 = (int *)malloc(size * sizeof(int));
    int *S2 = (int *)malloc(size * sizeof(int));
    int taille_S1 = 0, taille_S2 = 0;

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    bool result = partition(nums, size, S1, &taille_S1, S2, &taille_S2);

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Time taken: %f seconds\n", elapsed);

    if (result) {
        printf("Set can be partitioned\n");

        // Print the contents of S1 and S2
        printf("S1: ");
        for (i = 0; i < taille_S1; i++) {
            printf("%d ", S1[i]);
        }
        printf("\n");

        printf("S2: ");
        for (i = 0; i < taille_S2; i++) {
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

        // Validate the partitions
        // if (verifier_partitions(nums, size, S1, taille_S1, S2, taille_S2)) {
        //     printf("Les partitions sont valides.\n");
        // } else {
        //     printf("Les partitions ne sont pas valides.\n");
        // }

        QueryPerformanceCounter(&start);

        bool valid_partitions = verifier_partitions(nums, size, S1, taille_S1, S2, taille_S2);

        QueryPerformanceCounter(&end);
        double verify_elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

        printf("Time taken for verifier_partitions: %f seconds\n", verify_elapsed);
    } else {
        printf("Set cannot be partitioned\n");
    }

    free(nums);
    free(S1);
    free(S2);

    return 0;
}

