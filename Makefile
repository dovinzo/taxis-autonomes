# Spécifie que les règles clean, clean_test, test, test_liste et all ne sont pas des fichiers
.PHONY: clean

#===============================================================================#
#                                Variables                                      #
#===============================================================================#

# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c99

# Répertoire des fichiers binaire
BIN_DIR = bin

# Répertoire des fichiers data
DATA_DIR = data

# Répertoire des fichiers include
INCLUDE_DIR = include

# Répertoire des fichiers objet
OBJ_DIR = obj

# Répertoire des fichiers source
SRC_DIR = src

# Liste des fichiers source (module)
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Liste des fichiers objet (issu d'un module)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nom de l'exécutable principal
EXEC = $(BIN_DIR)/simulation-taxis-autonomes

#===============================================================================#
#                                   Règles                                      #
#===============================================================================#

# Règle par défaut
all: $(EXEC)

# Règle de construction de l'exécutable principal
$(EXEC): $(OBJS) $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

# Règle de construction des fichiers objet (issu d'un module)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction du fichier objet $(OBJDIR)/main.o
$(OBJ_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets et l'exécutable principal
clean:
	rm -f $(OBJS) $(OBJ_DIR)/moteur.o $(EXEC)
