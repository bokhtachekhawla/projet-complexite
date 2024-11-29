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

# Comment Exécuter le Code

### 1. Installer le Compilateur GCC :
   - Assurez-vous que **GCC** est installé sur votre machine. Si ce n’est pas déjà fait, vous pouvez installer GCC via le gestionnaire de paquets de votre système.
   - Pour vérifier si GCC est installé, exécutez la commande suivante :
     ```bash
     gcc --version
     ```

   Si la commande retourne une version, GCC est installé. Sinon, vous devrez l'installer avant de continuer.

### 2. Compiler le Fichier C :
   - Pour compiler un fichier source C (par exemple, `listedc.c`), utilisez la commande suivante :
     ```bash
     gcc listedc.c -o listedc
     ```
     Cela créera un exécutable nommé `listedc`.

### 3. Exécuter le Programme Compilé :
   - Après la compilation, vous pouvez exécuter le programme compilé avec la commande suivante :
     ```bash
     ./listedc
     ```

### 4. Répéter pour D'autres Fichiers C :
   - Pour compiler et exécuter d'autres fichiers source C, répétez les étapes ci-dessus avec le nom du fichier approprié :
     - Compilation :
       ```bash
       gcc autre_fichier.c -o autre_programme
       ```
     - Exécution :
       ```bash
       ./autre_programme
       ```



## **Description des Fichiers**

| **Nom du Fichier**              | **Description**                                             |
|---------------------------------|-------------------------------------------------------------|
| `TAS_complexite.c`              | Implémentation des tas avec analyse de complexité.         |
| `TAS_exemple.c`                 | Exemple d’utilisation des tas.                             |
| `Tri_par_TAS_complexite.c`      | Analyse du tri par tas avec complexité.                    |
| `Tri_par_TAS_exemple.c`         | Exemple d’utilisation du tri basé sur les tas.             |
| `arbre_binaire_de_recherche.c`  | Implémentation des arbres binaires de recherche.           |
| `arbre_b.c`                     | Implémentation des arbres B (B-Tree).                      |
| `listedc.c`                     | Opérations sur les listes doublement chaînées.             |
