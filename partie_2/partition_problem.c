#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX 100

// Fonction pour vérifier si une partition est possible et trouver les sous-ensembles
bool isPartitionPossible(int arr[], int n, int sum, bool dp[MAX][MAX]) {
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true; // somme 0 possible avec n'importe quel nombre d'éléments
    }
    for (int i = 1; i <= sum; i++) {
        dp[0][i] = false; // somme non nulle impossible avec 0 éléments
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][sum];
}

// Fonction pour reconstruire les sous-ensembles
void findSubsets(int arr[], int n, int sum, bool dp[MAX][MAX]) {
    if (!dp[n][sum]) {
        printf("Erreur : aucune partition possible.\n");
        return;
    }

    int i = n, j = sum;
    int sum1 = 0, sum2 = 0;
    bool selected[MAX] = {false};

    // Premier sous-ensemble
    printf("Sous-ensemble 1 : ");
    while (i > 0 && j > 0) {
        if (!dp[i - 1][j]) { // Si cet élément est inclus dans la solution
            printf("%d ", arr[i - 1]);
            selected[i - 1] = true;
            sum1 += arr[i - 1];
            j -= arr[i - 1];
        }
        i--;
    }
    printf("\nSomme du sous-ensemble 1 : %d\n", sum1);

    // Deuxième sous-ensemble
    printf("Sous-ensemble 2 : ");
    for (int k = 0; k < n; k++) {
        if (!selected[k]) {
            printf("%d ", arr[k]);
            sum2 += arr[k];
        }
    }
    printf("\nSomme du sous-ensemble 2 : %d\n", sum2);

    // Vérification finale
    if (sum1 != sum2) {
        printf("Erreur : les sous-ensembles ne respectent pas la condition de sommes égales.\n");
    }
}

// Fonction principale
void canPartition(int arr[], int n) {
    int totalSum = 0;

    // Calcul de la somme totale
    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
    }
    printf("Somme totale : %d\n", totalSum);

    if (totalSum % 2 != 0) {
        printf("Non, l'ensemble ne peut pas être partitionné en deux sous-ensembles de sommes égales.\n");
        return;
    }

    int halfSum = totalSum / 2;
    bool dp[MAX][MAX] = {false};

    if (isPartitionPossible(arr, n, halfSum, dp)) {
        printf("Oui, l'ensemble peut être partitionné en deux sous-ensembles de sommes égales.\n");
        findSubsets(arr, n, halfSum, dp);
    } else {
        printf("Non, l'ensemble ne peut pas être partitionné en deux sous-ensembles de sommes égales.\n");
    }
}


// Programme principal
int main() {
    //int arr[10];
    srand(time(NULL));
    /*
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }
    */
    int arr [] ={1, 5, 11, 5,4,2,3,50, 3 , 100 ,50};
    printf("Tableau généré : ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int n = sizeof(arr) / sizeof(arr[0]);
    canPartition(arr, n);

    return 0;
}
