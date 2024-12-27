
#include <stdio.h>
#include <stdbool.h>

// Fonction pour calculer la somme d'un tableau
int sumArray(int nums[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += nums[i];
    }
    return sum;
}

// Renvoie true s'il existe un sous-ensemble de `nums[]` avec la somme donnée
bool subsetSum(int nums[], int n, int sum) {
    // renvoie vrai si la somme devient 0 (sous-ensemble trouvé)
    if (sum == 0) {
        return true;
    }

    // cas de base : il ne reste plus d'éléments ou la somme devient négative
    if (n < 0 || sum < 0) {
        return false;
    }

    // Cas 1. Inclure l'élément actuel `nums[n]` dans le sous-ensemble
    bool include = subsetSum(nums, n - 1, sum - nums[n]);

    // renvoie vrai si nous obtenons un sous-ensemble en incluant l'élément courant
    if (include) {
        return true;
    }

    // Cas 2. Exclure l'élément actuel `nums[n]` du sous-ensemble
    bool exclude = subsetSum(nums, n - 1, sum);

    // renvoie vrai si nous obtenons un sous-ensemble en excluant l'élément actuel
    return exclude;
}

// Renvoie vrai si le tableau donné `nums[0...n-1]` peut être divisé en deux sous-ensembles avec une somme égale
bool partition(int nums[], int size) {
    int sum = sumArray(nums, size);

    // renvoie vrai si la somme est paire et que le tableau peut être divisé
    if (sum % 2 != 0) {
        return false;
    }

    return subsetSum(nums, size - 1, sum / 2);
}

int main() {
    // Entrée : un ensemble d'éléments
    int nums[] = { 7, 3, 1, 5, 4 };
    int size = sizeof(nums) / sizeof(nums[0]); //nombre d'elems dans le tableau

    if (partition(nums, size)) {
        printf("Set can be partitioned\n");
    } else {
        printf("Set cannot be partitioned\n");
    }

    return 0;
}

/*
//AFFICHAGE DES DEUX SOUS ENSEMBLES
#include <stdio.h>
#include <stdbool.h>

// Fonction pour calculer la somme d'un tableau
int sumArray(int nums[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += nums[i];
    }
    return sum;
}

// Fonction récursive pour trouver un sous-ensemble avec la somme donnée
bool subsetSum(int nums[], int n, int sum, int subset[], int* subsetSize) {
    if (sum == 0) {
        return true; // Sous-ensemble trouvé
    }
    if (n < 0 || sum < 0) {
        return false; // Pas de solution possible
    }

    // Inclure l'élément actuel dans le sous-ensemble
    subset[*subsetSize] = nums[n];
    (*subsetSize)++;
    if (subsetSum(nums, n - 1, sum - nums[n], subset, subsetSize)) {
        return true;
    }

    // Exclure l'élément actuel du sous-ensemble
    (*subsetSize)--;
    if (subsetSum(nums, n - 1, sum, subset, subsetSize)) {
        return true;
    }

    return false;
}

// Fonction principale pour vérifier la partition et afficher les sous-ensembles
bool partition(int nums[], int size) {
    int sum = sumArray(nums, size);

    // Vérifier si la somme totale est paire
    if (sum % 2 != 0) {
        return false;
    }

    int target = sum / 2;
    int subset1[size], subset1Size = 0;

    // Trouver un sous-ensemble avec la somme égale à la moitié de la somme totale
    if (subsetSum(nums, size - 1, target, subset1, &subset1Size)) {
        // Afficher le premier sous-ensemble
        printf("Subset 1: ");
        for (int i = 0; i < subset1Size; i++) {
            printf("%d ", subset1[i]);
        }
        printf("\n");

        // Trouver les éléments restants pour le deuxième sous-ensemble
        bool used[size];
        for (int i = 0; i < size; i++) {
            used[i] = false;
        }
        for (int i = 0; i < subset1Size; i++) {
            for (int j = 0; j < size; j++) {
                if (nums[j] == subset1[i] && !used[j]) {
                    used[j] = true;
                    break;
                }
            }
        }

        printf("Subset 2: ");
        for (int i = 0; i < size; i++) {
            if (!used[i]) {
                printf("%d ", nums[i]);
            }
        }
        printf("\n");
        return true;
    }

    return false;
}

int main() {
    int nums[] = {7, 1, 5, 4,3};
    int size = sizeof(nums) / sizeof(nums[0]);

    if (partition(nums, size)) {
        printf("The set can be partitioned into two subsets with equal sum.\n");
    } else {
        printf("The set cannot be partitioned into two subsets with equal sum.\n");
    }

    return 0;
}
*/