```markdown
# Projet de Base de Données en C Ilyes Miraoui 3SI2

## Description du Projet

Ce projet est une base de données simple en ligne de commande écrite en C. Il permet la gestion de tables avec des opérations classiques telles que la création, l'insertion, la sélection, la mise à jour et la suppression.

## Conception du Système et Choix Techniques

### Structure de Données avec Arbre Binaire

Pour notre système de gestion de base de données, nous avons opté pour une structure d'arbre binaire. Ce choix est motivé par plusieurs facteurs techniques :

- **Efficacité de Recherche et Manipulation** : 
  - L'arbre binaire permet des opérations de recherche, d'insertion et de suppression de données en temps logarithmique, optimisant ainsi les opérations fréquentes sur les données.
  - Cette efficacité est cruciale dans les scénarios où des modifications fréquentes sont nécessaires.

- **Simplicité de Mise en Œuvre** :
  - Cette structure est relativement simple à comprendre et à implémenter, rendant le développement et la maintenance du code plus aisés.
  - Elle s'adapte parfaitement aux opérations récursives courantes dans les applications CRUD (Create, Read, Update, Delete).

- **Scalabilité** :
  - Avec l'augmentation du volume de données, l'arbre binaire continue d'assurer des performances prévisibles et stables, contrairement aux structures linéaires.

### Organisation Modulaire du Code

Le code est structuré de manière modulaire, séparant clairement la gestion des données (comme l'arbre binaire) des interfaces utilisateur et des logiques de commande. Cela facilite la réutilisabilité et la maintenance continue du système.

- **Modularité** : Les modules sont indépendants, permettant des évolutions sans impact sur l'ensemble du système.
- **Lisibilité et Maintenance** : Chaque fichier source est dédié à un composant particulier, favorisant ainsi une meilleure lisibilité et un débogage plus efficace.

## Installation et Compilation

### Installation de MSYS2

1. **Téléchargez et installez [MSYS2](https://www.msys2.org).**
2. **Mettre à jour les paquets :**
   ```bash
   pacman -Syu
   ```

3. **Installer les outils de développement :**
   ```bash
   pacman -S base-devel
   pacman -S mingw-w64-x86_64-gcc
   ```

### Compilation du Projet

#### 1. Avec l’Environnement MSYS2

1. **Ouvrir MSYS2**.
2. **Naviguer jusqu'au Répertoire du Projet :**
   ```bash
   cd "Nom_chemin/class_db-main"
   ```

3. **Compiler le Projet :**
   ```bash
   make
   ```

4. **Exécuter le Programme :**
   ```bash
   ./class_db
   ```

#### 2. Avec MinGW pour un Exécutable Autonome

1. **Ouvrir le Terminal MinGW64 fourni par MSYS2**.
2. **Naviguer jusqu'au Répertoire du Projet :**
   ```bash
   cd "Nom_chemin/class_db-main"
   ```

3. **Compiler le Projet :**
   ```bash
   gcc -std=c11 -Wall -Wextra -O2 -g -o class_db src/*.c
   ```

4. **Exécuter le Programme :**
   ```bash
   ./class_db.exe
   ```

## Architecture du Projet

- **src/repl.c** : Gère l'interface utilisateur et traite les commandes.
- **src/btree.c** : Implémente les structures de données arbre binaire pour le stockage.
- **src/table.c** : Gère la gestion des tables dans la base de données.

## Modules/Fonctions Clés

### repl.c

- `repl()` : Fonction principale pour exécuter le programme en boucle. Lit les entrées utilisateur et exécute les commandes.

### btree.c

- `insert()` : Insère des données dans l'arbre binaire.
- `delete_node()` : Supprime un nœud basé sur un identifiant.

### table.c

- `create_database()` : Initialise une nouvelle base de données.
- `add_table()` : Ajoute une nouvelle table à la base de données.

## Exemples d’Utilisation

- Créer une nouvelle table :
  ```bash
  db > create table utilisateurs
  ```

- Insérer des données :
  ```bash
  db > insert into utilisateurs
  db > nom=John
  db > age=30
  db > end
  ```

- Sélectionner des données :
  ```bash
  db > select from utilisateurs
  ```

## Nettoyage

Pour supprimer les fichiers objets et l'exécutable, utilisez :
```bash
make clean
```

## Remarques

- Assurez-vous d'avoir configuré votre environnement correctement.
- En compilant avec MinGW, vérifiez que toutes les bibliothèques sont incluses.

---

Remplacez `"Nom_chemin/class_db-main"` par le chemin correct vers votre répertoire de projet.

