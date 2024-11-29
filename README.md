# **Projet Complexité**

Ce dépôt contient des implémentations et des exemples de divers algorithmes et structures de données, notamment les tas, les arbres binaires de recherche, les arbres B et les listes doublement chaînées, dans le cadre du projet d'analyse de la complexité.

## **Table des Matières**
1. [Aperçu du Projet](#aperçu-du-projet)
2. [Fonctionnalités](#fonctionnalités)
3. [Comment Cloner le Projet](#comment-cloner-le-projet)
4. [Comment Exécuter le Code](#comment-exécuter-le-code)
5. [Description des Fichiers](#description-des-fichiers)

---

## **Aperçu du Projet**

Ce projet inclut :
- **Algorithmes de tri basés sur les tas** : Analyse et implémentation du tri par tas.
- **Arbres Binaires de Recherche (Binary Search Tree)** : Implémentation des arbres binaires pour des opérations de recherche efficaces.
- **Arbres B (B-Tree)** : Gestion des structures avancées pour des systèmes de bases de données et de fichiers.
- **Listes Doublement Chaînées** : Gestion et parcours de listes chaînées efficacement.

---

## **Fonctionnalités**
- Analyse et comparaison de la complexité des algorithmes.
- Implémentation des structures de données fondamentales pour des performances optimisées.
- Fichiers source `.c` prêts à être exécutés pour tester et apprendre.

---

## **Comment Cloner le Projet**

1. **Vérifiez que Git est installé** :
   - Vérifiez si Git est installé en exécutant :
     ```bash
     git --version
     ```
     Si ce n’est pas le cas, téléchargez et installez Git depuis [le site officiel de Git](https://git-scm.com/).

2. **Clonez le dépôt** :
   - Exécutez la commande suivante dans votre terminal :
     ```bash
     git clone https://github.com/bokhtachekhawla/projet-complexite.git
     ```

3. **Accédez au répertoire** :
   ```bash
   cd projet-complexite

## **Comment Exécuter le Code**

### 1. Installez le compilateur GCC :
    - Assurez-vous que GCC est installé en exécutant la commande suivante :
     ```bash
     git --version
     ```

### 2. Compilez un fichier :
    - Par exemple, pour compiler le code de liste doublement chainée, exécutez : :
     ```bash
     gcc listedc.c -o listedc
     ```

### 3. Exécutez le programme compilé :
    - Une fois le fichier compilé, exécutez le programme généré :
     ```bash
     ./listedc
     ```

### 4. ERépétez pour d'autres fichiers :
    - Utilisez les mêmes étapes pour compiler et exécuter d'autres fichiers .c

## **Description des Fichiers**

| **Nom du Fichier**              | **Description**                                             |
|---------------------------------|-------------------------------------------------------------|
| `TAS_complexite.c`              | Implémentation des tas avec analyse de complexité.         |
| `TAS_exemple.c`                 | Exemple d’utilisation des tas.                             |
| `Tri_par_TAS_complexite.c`      | Analyse du tri par tas avec complexité.                    |
! `Tri_par_TAS_exemple.c`         | Exemple d’utilisation du tri basé sur les tas.             |
| `arbre_binaire_de_recherche.c`  | Implémentation des arbres binaires de recherche.           |
| `arbre_b.c`                     | Implémentation des arbres B (B-Tree).                      |
| `listedc.c`                     | Opérations sur les listes doublement chaînées.             |
