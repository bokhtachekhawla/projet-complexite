#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Fonction pour calculer la somme d'un tableau
int sumArray(int nums[], int size) {
    int sum = 0,i;
    for ( i = 0; i < size; i++) {
        sum += nums[i];
        // printf("Adding %d to sum, current sum: %d\n", nums[i], sum);
    }
    return sum;
}

// Renvoie true s'il existe un sous-ensemble de `nums[]` avec la somme donnée
bool subsetSum(int nums[], int n, int sum) {
    // printf("subsetSum called with n=%d, sum=%d\n", n, sum);

    if (sum == 0) {
        // printf("Sum is 0, returning true\n");
        return true;
    }

    if (n < 0 || sum < 0) {
        // printf("No elements left or sum is negative, returning false\n");
        return false;
    }

    bool include = subsetSum(nums, n - 1, sum - nums[n]);
    // printf("Including nums[%d]=%d, new sum=%d, result=%d\n", n, nums[n], sum - nums[n], include);

    if (include) {
        return true;
    }

    bool exclude = subsetSum(nums, n - 1, sum);
    // printf("Excluding nums[%d]=%d, result=%d\n", n, nums[n], exclude);

    return exclude;
}

// Renvoie vrai si le tableau donné `nums[0...n-1]` peut être divisé en deux sous-ensembles avec une somme égale
bool partition(int nums[], int size) {
    int sum = sumArray(nums, size);
    // printf("Total sum of array: %d\n", sum);

    if (sum % 2 != 0) {
        // printf("Sum is odd, cannot partition\n");
        return false;
    }

    return subsetSum(nums, size - 1, sum / 2);
}

// Fonction pour remplir le tableau avec des nombres aléatoires
void fillArrayRandomly(int nums[], int size, int maxVal) {
    int i;
    for ( i = 0; i < size; i++) {
        nums[i] =rand() % maxVal;
        // printf("nums[%d] = %d\n", i, nums[i]);
    }
}


// using windows.h for high-resolution performance counter

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

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    bool result = partition(nums, size);

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Time taken: %f seconds\n", elapsed);
    
    if (result) {
        printf("Set can be partitioned\n");
    } else {
        printf("Set cannot be partitioned\n");
    }

    return 0;
}


// using time.h
// int main() {
//     srand(time(0)); // Initialiser le générateur de nombres aléatoires

//     int size, i;
//     printf("Enter the size of the array: ");
//     scanf("%d", &size);

//     int *nums = (int *)malloc(size * sizeof(int));
//     if (nums == NULL) {
//         printf("Memory allocation failed\n");
//         return 1;
//     }

//     fillArrayRandomly(nums, size,100); // Remplir le tableau avec des valeurs aléatoires de 0 a 99

//     // Print the contents of the array
//     // printf("Array contents: ");
//     // for (i = 0; i < size; i++) {
//     //     printf("%d \t ", nums[i]);
//     // }
//     //  printf("\n");

//     // clock_t start, end;
//     // double cpu_time_used;

//     // start = clock();

//     bool result = partition(nums, size);

//     // end = clock();
//     // cpu_time_used = difftime(end, start);
//     // // ((double) (end - start)) / CLOCKS_PER_SEC;

//     // printf("Time taken: %.f seconds\n", cpu_time_used);
    
//     if (result) {
//         printf("Set can be partitioned\n");
//     } else {
//         printf("Set cannot be partitioned\n");
//     }

//     free(nums);

//     return 0;
// }
