#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Fonction pour créer un nouveau nœud
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour insérer un élément dans l'arbre binaire de recherche
void insert(Node** root, int key) {
    Node* current = *root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (key == current->key) {
            // La clé existe déjà, ne pas insérer
            // printf("%d existe déjà dans l'arbre.\n", key);
            return;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    Node* newNode = createNode(key);
    if (parent == NULL) {
        *root = newNode; // Insérer comme racine
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

// Fonction pour rechercher une clé dans l'arbre
bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (root->key == key) return true;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Fonction pour supprimer un nœud
void delete_node(Node** root, int key) {
    if (*root == NULL) return;

    Node* parent = NULL;
    Node* current = *root;

    // Recherche du nœud à supprimer
    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Key %d does not exist in the tree.\n", key);
        return;
    }

    // Cas 1 : Le nœud à supprimer a deux enfants
    if (current->left != NULL && current->right != NULL) {
        Node* successor = current->right;
        Node* successorParent = current;

        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        current->key = successor->key; // Copier la clé du successeur
        current = successor; // Supprimer le successeur à la place
        parent = successorParent;
    }

    // Cas 2 : Le nœud à supprimer a 0 ou 1 enfant
    Node* child = (current->left != NULL) ? current->left : current->right;

    if (parent == NULL) {
        *root = child; // Suppression de la racine
    } else if (parent->left == current) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    free(current);
}

// Mesure le temps d'insertion
double measure_insert_time(Node** root, int key, LARGE_INTEGER frequency) {
    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);
    insert(root, key);
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e6;
}

// Mesure le temps de recherche
double measure_search_time(Node* root, int key, LARGE_INTEGER frequency) {
    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);
    bool found = search(root, key);
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e6;
}

// Mesure le temps de suppression
double measure_delete_time(Node** root, int key, LARGE_INTEGER frequency) {
    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);
    delete_node(root, key);
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e6;
}

// Fonction pour libérer la mémoire de l'arbre
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    srand((unsigned int)time(NULL));
    LARGE_INTEGER frequency;
    int num_trials = 10;

    if (!QueryPerformanceFrequency(&frequency)) {
        fprintf(stderr, "High-performance counter not supported.\n");
        return 1;
    }

    printf("n\tInsert Time (µs)\tSearch Time (µs)\tDelete Time (µs)\n"); 
    int n, trial , i;
    for ( n = 10000; n <= 100000; n += 20000) {
        double total_time_insert = 0.0;
        double total_time_search = 0.0;
        double total_time_delete = 0.0;

        for ( trial = 0; trial < num_trials; trial++) {
            Node* root = NULL;

            for ( i = 0; i < n; i++) {
                int random_number = rand() % 10000;
                insert(&root, random_number);
            }

            int random_key = rand() % 10000;

            total_time_insert += measure_insert_time(&root, random_key, frequency);
            total_time_search += measure_search_time(root, random_key, frequency);
            total_time_delete += measure_delete_time(&root, random_key, frequency);

            freeTree(root);
        }

        printf("%d\t%.6f\t\t%.6f\t\t%.6f\n",
               n,
               total_time_insert / num_trials,
               total_time_search / num_trials,
               total_time_delete / num_trials);
    }

    return 0;
}
