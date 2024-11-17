# Nom de l'exécutable
TARGET = class_db

# Compilateur à utiliser
CC = gcc

# Drapeaux de compilation
CFLAGS = -std=c11 -Wall -Wextra -O2 -g

# Répertoire source
SRC_DIR = src

# Fichiers sources
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/repl.c $(SRC_DIR)/btree.c $(SRC_DIR)/table.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Génération de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des fichiers objets
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers compilés
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
