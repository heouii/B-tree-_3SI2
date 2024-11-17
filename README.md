# README

## Description du Projet

Ce projet est une base de données simple en ligne de commande écrite en C. Il permet la gestion de tables avec des opérations classiques telles que la création, l'insertion, la sélection, la mise à jour et la suppression.

## Configuration Système Requise

- **MSYS2** : Un environnement Unix-like pour Windows.
- **Compilateur GCC** : Utilisé pour compiler le code source C.

## Installation

1. **Installer MSYS2** :
   - Téléchargez et installez MSYS2 depuis [le site officiel](https://www.msys2.org).
   - Suivez les instructions pour configurer et mettre à jour MSYS2.

2. **Mettre à Jour les Paquets** :
   ```bash
   pacman -Syu

3. **Installer les Outils de Développement** :
   ```bash
    pacman -S base-devel
    pacman -S mingw-w64-x86_64-gcc

#Compilation du Projet
##1. Compilation avec l’Environnement MSYS2
**Ouvrir MSYS2** :

Lancez le terminal MSYS2 depuis le menu démarrer.
Naviguer jusqu'au Répertoire du Projet :
    ```bash
    cd "Nom_chemin/class_db-main"

**Compiler le Projet** :
    ```bash
    make

**Exécuter le Programme** :
    ```bash
    ./class_db
 
##2. Compilation avec MinGW pour un Exécutable Autonome
1. **Ouvrir le Terminal MinGW64 fourni par MSYS2** :

Cherchez MSYS2 MinGW 64-bit dans le menu démarrer.
2. **Naviguer jusqu'au Répertoire du Projet** :
    ```bash
    cd "Nom_chemin/class_db-main"

3. **Compiler le Projet** :
    ```bash
    gcc -std=c11 -Wall -Wextra -O2 -g -o class_db src/*.c

4. **Exécuter le Programme** :
    ```bash
    ./class_db.exe

##Nettoyage
1. **Pour supprimer les fichiers objets et l'exécutable, utilisez** :
    ```bash
    make clean

##Remarques
1. **Assurez-vous d'avoir configuré votre environnement correctement.**
3. **En compilant avec MinGW, vérifiez que toutes les bibliothèques sont incluses.**

