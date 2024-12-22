#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Un nœud de B-tree
struct BTreeNode {
    int *keys; //tableau de clés
    int d;     // Degré minimal
    struct BTreeNode **C; // Tableau de pointeurs vers les sous-arbres
    int n;     // Nombre de clés actuellement dans le nœud
    int leaf;  // Vaut 1 si c'est une feuille, sinon 0
};

// Fonction pour créer un nouveau nœud de B-tree
struct BTreeNode* createNode(int d, int leaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->d =d;
    newNode->leaf = leaf;
    newNode->keys = (int*)malloc((2*d - 1) * sizeof(int));
    newNode->C = (struct BTreeNode**)malloc((2*d) * sizeof(struct BTreeNode*));
    newNode->n = 0;
    return newNode;
}

// Fonction pour parcourir l'arbre (affichage)
void traverse(struct BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->C[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->C[i]);
}

// Fonction pour rechercher une clé dans un B-tree
struct BTreeNode* search(struct BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    
    if (i < root->n && root->keys[i] == k)
        return root;

    if (root->leaf)
        return NULL;

    return search(root->C[i], k);
}

// Fonction pour diviser un nœud plein
void splitChild(struct BTreeNode* parent, int i, struct BTreeNode* fullChild) {
    int d = fullChild->d;

    struct BTreeNode* newChild = createNode(d, fullChild->leaf);
    newChild->n = d - 1;
    int j;
    for ( j = 0; j < d-1; j++)
        newChild->keys[j] = fullChild->keys[j + d];

    if (!fullChild->leaf) {
        for ( j = 0; j < d; j++)
            newChild->C[j] = fullChild->C[j + d];
    }

    fullChild->n = d - 1;

    for ( j = parent->n; j >= i+1; j--)
        parent->C[j+1] = parent->C[j];

    parent->C[i+1] = newChild;

    for ( j = parent->n-1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];

    parent->keys[i] = fullChild->keys [d-1];
    parent->n++;
}

// Fonction d'insertion dans un nœud non plein
void insertNonFull(struct BTreeNode* node, int k) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && node->keys[i] > k) {
            node->keys[i+1] = node->keys[i];
            i--;
        }

        node->keys[i+1] = k;
        node->n++;
    } else {
        while (i >= 0 && node->keys[i] > k)
            i--;

        if (node->C[i+1]->n == 2*node->d - 1) {
            splitChild(node, i+1, node->C[i+1]);

            if (node->keys[i+1] < k)
                i++;
        }
        insertNonFull(node->C[i+1], k);
    }
}

// Fonction principale pour insérer une clé dans le B-tree
void insert(struct BTreeNode** root, int k, int d) {
    struct BTreeNode* r = *root;

    if (r->n == 2 *d - 1) {
        struct BTreeNode* s = createNode (d, 0);
        s->C[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, k);
        *root = s;
    } else {
        insertNonFull(r, k);
    }
}

// Fonction pour obtenir le prédecesseur d'une clé dans le sous-arbre gauche
int getPredecessor(struct BTreeNode* node, int idx) {
    struct BTreeNode* cur = node->C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// Fonction pour obtenir le successeur d'une clé dans le sous-arbre droit
int getSuccessor(struct BTreeNode* node, int idx) {
    struct BTreeNode* cur = node->C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

// Fonction pour fusionner deux enfants C[idx] et C[idx+1]
void merge(struct BTreeNode* node, int idx) {
    struct BTreeNode* child = node->C[idx];
    struct BTreeNode* sibling = node->C[idx + 1];
    int d = node ->d;

    child->keys [d - 1] = node->keys[idx];
    int i;
    for ( i = 0; i < sibling->n; ++i)
        child->keys[i + d] = sibling->keys[i];

    if (!child->leaf) {
        for ( i = 0; i <= sibling->n; ++i)
            child->C[i + d] = sibling->C[i];
    }

    for ( i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    for ( i = idx + 2; i <= node->n; ++i)
        node->C[i - 1] = node->C[i];

    child->n += sibling->n + 1;
    node->n--;

    free(sibling);
}

// Fonction principale pour supprimer une clé du B-tree
void removeFromBTree(struct BTreeNode* node, int k) {
    int idx = 0;
    int i;
    while (idx < node->n && node->keys[idx] < k)
        idx++;

    if (idx < node->n && node->keys[idx] == k) {
        // Si le nœud est une feuille
        if (node->leaf) {
            for ( i = idx + 1; i < node->n; ++i)
                node->keys[i - 1] = node->keys[i];
            node->n--;
        } else {
            // Si le nœud n'est pas une feuille
            if (node->C[idx]->n >= node->d) {
                int pred = getPredecessor(node, idx);
                node->keys[idx] = pred;
                removeFromBTree(node->C[idx], pred);
            } else if (node->C[idx + 1]->n >= node->d) {
                int succ = getSuccessor(node, idx);
                node->keys[idx] = succ;
                removeFromBTree(node->C[idx + 1], succ);
            } else {
                merge(node, idx);
                removeFromBTree(node->C[idx], k);
            }
        }
    } else {
        // Si la clé n'est pas trouvée
        if (node->leaf) {
            printf("La clé %d n'est pas présente dans l'arbre.\n", k);
            return;
        }

        int flag = (idx == node->n);

        if (node->C[idx]->n < node->d) {
            if (idx != 0) {
                merge(node, idx - 1);
            } else {
                merge(node, idx);
            }
        }

        if (flag && idx > node->n)
            removeFromBTree(node->C[idx - 1], k);
        else
            removeFromBTree(node->C[idx], k);
    }
}

void freeTree(struct BTreeNode* node) {
    if (node == NULL) return; // Rien à libérer si le nœud est NULL
    int i;
    // Si ce nœud n'est pas une feuille, libérer les sous-arbres enfants
    if (!node->leaf) {
        for ( i = 0; i <= node->n; i++) { // Parcourt tous les enfants
            freeTree(node->C[i]); // Libère récursivement chaque sous-arbre
        }
    }

    // Libération du tableau de clés
    free(node->keys);

    // Libération du tableau des pointeurs vers les sous-arbres
    free(node->C);

    // Libération du nœud lui-même
    free(node);
}

// Programme principal pour tester l'algorithme
int main() {
    srand(time(NULL));
    LARGE_INTEGER frequency, start, end;
    double temps_ecoule;
    double total_time_insert = 0.0;
    double total_time_search = 0.0;
    double total_time_delete = 0.0;
    clock_t debut, fin;
    double t;
    int d = 3; // Degré du B-tree
    int num_trials = 10; 
    int n = 400000;
    /*printf ("donnez le degré de l'arbre : ");
    scanf("%d",&t);*/
    // Initialisation de la fréquence du compteur haute résolution
    QueryPerformanceFrequency(&frequency);
int trial,i;
    for ( trial = 0; trial < num_trials; trial++) {
        struct BTreeNode* root = createNode(d, 1);

        // Insertion de clés
        QueryPerformanceCounter(&start);
        for ( i = 0; i < n; i++) {
            insert(&root, i, d);
        }
        QueryPerformanceCounter(&end);
        temps_ecoule = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart; // Temps en secondes
        total_time_insert += temps_ecoule;
        /*printf("Parcours du B-tree : ");
        traverse(root);
        printf("\n");*/
        // Recherche d'une clé
        int k = n-1;
        QueryPerformanceCounter(&start);
        (search(root, k) != NULL) ? printf("%d est présent\n", k) : printf("%d n'est pas présent\n", k);
        QueryPerformanceCounter(&end);
        temps_ecoule = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e12; // Temps en picosecondes
        total_time_search += temps_ecoule;
  
        // Suppression d'une clé
        k = n - 1;
        if (search(root, k) == NULL) {
            printf("Valeur à supprimer non existante\n");
        } else {
            QueryPerformanceCounter(&start);
            removeFromBTree(root, k);
            QueryPerformanceCounter(&end);
            temps_ecoule = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e12; // Temps en picosecondes
            total_time_delete += temps_ecoule;
        }
        /*printf("Parcours du B-tree apres suppression de %d : ", k);
        traverse(root);
        printf("\n");*/

        // Libération de la mémoire associée à l'arbre
        freeTree(root);
    }

    // Calcul des temps moyens
    printf("Temps moyen d'insertion : %f secondes \n", total_time_insert / num_trials);
    printf("Temps moyen de recherche : %f pico secondes \n", total_time_search / num_trials);
    printf("Temps moyen de suppression : %f pico secondes \n", total_time_delete / num_trials);

    return 0;
}


