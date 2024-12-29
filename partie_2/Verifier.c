#include <stdio.h>
#include <stdbool.h>

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

// Exemple
int main() {
    // Ensemble principal
    int S[] = {1, 5, 11, 5};
    int taille_S = 4;

    // Deux partitions aléatoires
    int S1[] = {1, 5, 5};
    int taille_S1 = 3;

    int S2[] = {11};
    int taille_S2 = 1;

    // Appeler la fonction de vérification
    if (verifier_partitions(S, taille_S, S1, taille_S1, S2, taille_S2)) {
        printf("Les partitions sont valides.\n");
    } else {
        printf("Les partitions ne sont pas valides.\n");
    }

    return 0;
}
