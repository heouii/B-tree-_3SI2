<<<<<<< HEAD
=======
Voici une structure de `README.md` basée sur ce que nous avons discuté pour votre projet de base de données en C :

---

>>>>>>> 3e40578dfe5deb5245f79d36cac6075f8caee00c
# Projet de Base de Données en C

## Description du Projet

Ce projet est une base de données simple en ligne de commande écrite en C. Il permet la gestion de tables avec des opérations classiques telles que la création, l'insertion, la sélection, la mise à jour et la suppression.

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