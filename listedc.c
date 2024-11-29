#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure d'un nœud de la liste doublement chaînee
struct Node {
    long data;
    struct Node* next;
    struct Node* prev;
};

// Fonction pour inserer un element au debut
void insertAtHead(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = *head;

    if (*head != NULL)
        (*head)->prev = newNode;

    *head = newNode;
}

// Fonction pour inserer un element au debut
void insertAttail(struct Node** head, long data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    struct Node* p = *head;
    if (p == NULL) {
        newNode->prev = NULL;
        *head = newNode;
    }
    else {
    while (p->next != NULL)
        p = p->next;

    p->next = newNode;
    newNode->prev = p;
    }
}

// Fonction pour afficher la liste
void displayList(struct Node* node) {
    struct Node* last;
    printf("\nListe dans l'ordre : ");
    while (node != NULL) {
        printf("%d ", node->data);
        last = node;
        node = node->next;
    }
    printf("\n");
}

// Fonction pour supprimer un element
void deleteNode(struct Node** head, long n) {
    if (*head == NULL)
        return;

    struct Node* p = *head;
    if (n == 1){
        *head = p->next;
    }
    else {
    while (n != 1){
        p = p->next;
        n--;
    }
    (p->prev)->next = p->next;
    if(p->next != NULL)
    (p->next)->prev = p->prev;
    }
    free(p);
}


// Fonction de recherche 
long search(struct Node* head, long key) {
    long p= 0;
    struct Node* current = head; 

    while (current != NULL) {
        p++;
        if (current->data == key) { 
            return p;
        }
        current = current->next; 
    }

    return 0;
}

int main() {
    struct Node* head = NULL;
    int v;
    long n;
    long key = 0;
    long pos = 0;
    clock_t debut, fin;
    double t_insert = 0.0, t_search = 0.0, t_delete = 0.0;
    int num_trials = 10; 

    printf("entrez le nombre de noeuds : ");
    scanf("%ld", &n);

    for (int trial = 0; trial < num_trials; trial++) {
        head = NULL; // Réinitialisation de la liste

        // INSERTION AU DÉBUT
        debut = clock();
        for (long i = 0; i < n; i++) {
            insertAtHead(&head, i);
        }
        fin = clock();
        t_insert += ((double)(fin - debut)) / CLOCKS_PER_SEC;
        //displayList(head);

        /*
        2eme choix
            //INSERTION FIN
            debut = clock();
            for(long i =0; i<n; i++) {
                insertAttail(&head,i);
            }
            //displayList(head);
            fin = clock();
            t_insert += ((double)(fin - debut)) / CLOCKS_PER_SEC;
        */


        // RECHERCHE
        pos = 0;
        debut = clock();
        pos = search(head, 0);
        fin = clock();
        t_search += ((double)(fin - debut)) / CLOCKS_PER_SEC;
        if (pos != 0) {
        printf("element %d trouve a la position numero %d.\n", key,pos);
        } else {
            printf("element %d non trouve.\n", key);
        }

        // SUPPRESSION
        pos = search(head, 0); // Rechercher la position de l'élément à supprimer
        if (pos != 0) {
            debut = clock();
            deleteNode(&head, pos);
            fin = clock();
            t_delete += ((double)(fin - debut)) / CLOCKS_PER_SEC;
        } 
        else {
        printf("element %d non trouve.\n", v);
        }
        //displayList(head);

        // Libérer la liste
        while (head != NULL) {
            deleteNode(&head, 1); // Suppression du premier nœud à chaque itération
        }
    }

    // Calcul des temps moyens
    printf("Temps moyen d'insertion : %f secondes\n", t_insert / num_trials);
    printf("Temps moyen de recherche : %f secondes\n", t_search / num_trials);
    printf("Temps moyen de suppression : %f secondes\n", t_delete / num_trials);

    return 0;
}


