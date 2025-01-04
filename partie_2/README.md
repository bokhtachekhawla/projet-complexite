# **Partie 02**

Cette partie contient des fichiers pour resolsu le probleme np complet de partition vérifier si c'est le cas est valide.

## Fichiers

- `projet2_randomvalues.c` : Ce fichier contient le code pour générer un vecteur aléatoire, partitionner le vecteur en deux sous-vecteurs avec des sommes égales, et vérifier la validité de la partition.

## Instructions

### Compilation

Pour compiler le fichier `projet2_randomvalues.c`, utilisez la commande suivante :

```sh
gcc -o random projet2_randomvalues.c

```
Execuction 
```sh
./random 

```

## Fonctionnalités
### Génération de Vecteurs Aléatoires :

Le programme génère un vecteur de taille spécifiée avec des valeurs aléatoires comprises entre 0 et 99.
### Partition du Vecteur :

Le programme partitionne le vecteur en deux sous-vecteurs avec des sommes égales, si possible.
### Vérification de la Partition :

Le programme vérifie si les deux sous-vecteurs sont disjoints et si leur union correspond au vecteur original.
### Mesure du Temps d'Exécution :

Le programme mesure le temps d'exécution des fonctions de partition et de vérification.


### Exemple de Sortie : 
Enter the size of the array: 10
Array contents: 9 26 91 31 67 24 37 10 65 66
Time taken for partition: 0.000002 seconds
Set can be partitioned
S1: 9 26 91 31 67
S2: 24 37 10 65 66
Sum of S1: 224
Sum of S2: 224
Size of S1 is odd
Size of S2 is even
Time taken for verifier_partitions: 0.000001 seconds
Les partitions sont valides.