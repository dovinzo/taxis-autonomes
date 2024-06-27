# Taxis Autonomes

**Taxis Autonomes** est un projet réalisé dans le cadre du cours Algorithmique de deuxième année de la formation ingénieur Mathématiques Appliquées et Calcul Scientifique (MACS) à Sup Galilée (https://www.sup-galilee.univ-paris13.fr/index.php/formation/macs/).

L'objectif du projet est de simuler un système de gestion d'une flotte de véhicules autonomes.

Ce projet a été réalisé en langage C.

## Table des matières

- [Informations générales](#informations-générales)
- [Sujet](#sujet)
- [Installation](#installation)
- [Compilation](#compilation)
- [Exécution](#exécution)
- [Structure](#structure)
- [Explication](#explication)
- [À Faire](#à-faire)
- [Auteurs](#auteurs)
- [Licence](#licence)

## Informations générales

- **Date de création**: 13 mai 2024
- **Auteur(s)**: Kelvin LEFORT
- **Sujet**: Simulation d'un système de gestion d'une flotte de véhicules autonomes.
- **Version**: 1.0.0

## Sujet

Pour plus d'informations sur le sujet, ouvrez le document PDF `sujet.pdf`.

## Installation

1. Clonez le dépôt
```bash
git clone https://github.com/kelvinlefort/taxis-autonomes.git
```

## Compilation

1. Mettez-vous dans le répertoire courant.
2. Exécutez la commande suivante
```bash
make
```

**Remarque**: Lors de la compilation, il y aura deux warnings qui vont s'afficher. Ce n'est pas important.

## Exécution

1. Le format d'exécution du programme est
```bash
nom_programme fichier_réseau_routier.txt fichier_flotte.txt fichier_appels.txt
```
**Exemple**: Exécutez la commande suivante
```bash
bin/simulation-taxis-autonomes data/01-rete.txt data/01-veicoli.txt data/01-chiamate.txt
```

2. Pour supprimer l'exécutable et les fichiers objets, exécutez la commande suivante
```bash
make clean
```

## Structure

1. **`bin/`**: Contient l'exécutable.
2. **`data/`**: Contient les données (réseau routier, appels, flotte, résultats attendus).
3. **`include/`**: Contient les fichiers d'en-tête C (i.e. fichiers .h).
4. **`obj/`**: Contient les fichiers objets.
5. **`out/`**: Contient les données produits par la simulation si besoin.
6. **`src/`**: Contient le code source du projet (i.e. fichiers .c).
7. **`Makefile`**: Sert à la compilation.
8. **`main.c`**: Point d'entrée de la simulation.


## Explication

1. **`appels.c`**: Gère les appels.
2. **`clients.c`**: Gère les clients.
3. **`element_01.c`**: Définit le type `Element_01` (qui correspond à un évènement) et une relation d'ordre sur ce type.
4. **`element_02.c`**: Définit le type `Element_02` (qui correspond à un sommet) et une relation d'ordre sur ce type.
5. **`file_attente.c`**: Gère la file d'attente devant la station de recharge.
6. **`flotte.c`**: Gère la flotte de taxis autonomes.
7. **`gestionnaire_evenements.c`**: S'occupe de la gestion des évènements discrets.
8. **`graphe.c`**: Gère le réseau routier, par exemple le calcul du plus court chemin avec l'algorithme de Dijkstra.
9. **`liste_01.c`**: Conçoit la struture d'une liste d'éléments de type `Element_01`.
10. **`liste_02.c`**: Conçoit la struture d'une liste d'éléments de type `Element_02`.
11. **`matrice.c`**: Conçoit la structure d'une matrice.
12. **`voyages.c`**: Gère les voyages.
13. **`main.c`**: Point d'entrée qui initialise et lance la simulation.

## À Faire

1. Le calcul du gain surestimé.

## Auteurs

- **Kelvin LEFORT** - Étudiant en charge du projet - [kelvinlefort](https://github.com/kelvinlefort)

## Licence

Ce projet est sous aucune licence, faîtes-en ce que vous voulez à condition de me citer !