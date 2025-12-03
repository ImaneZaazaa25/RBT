Arbre Rouge-Noir - Insertion de mots depuis un fichier

Description
Ce programme implémente un arbre rouge-noir (Red-Black Tree) pour stocker et organiser des mots lus depuis un fichier texte. L'arbre rouge-noir est une structure de données auto-équilibrée qui garantit des opérations de recherche, d'insertion et de suppression en temps logarithmique.

Structure du projet
Structure principale : Arbre binaire de recherche avec propriétés rouge-noir

Langage : C++

Fichier source : main.cpp

Fonctionnalités
Lecture de mots depuis un fichier texte

Insertion automatique dans un arbre rouge-noir

Équilibrage automatique de l'arbre (rotations et corrections de couleur)

Affichage des mots en ordre alphabétique

Gestion des couleurs des nœuds (rouge/noir) selon les propriétés RBT

Structure de données
Structure Cel
Représente un nœud de l'arbre rouge-noir :

val : le mot (string)

couleur : ROUGE ou NOIR (enum Couleur)

gauche : pointeur vers le fils gauche

droite : pointeur vers le fils droit

parent : pointeur vers le nœud parent

Enumération Couleur
ROUGE (0)

NOIR (1)

Fonctions principales
creerCel(string val)
Crée un nouveau nœud rouge avec le mot donné.

insererCel(Cel* root, string val)
Insère un nouveau mot dans l'arbre rouge-noir et corrige les propriétés si nécessaire.

correctionInsertion(Cel* root, Cel* pt)
Corrige les violations des propriétés rouge-noir après une insertion.

rotationGauche() et rotationDroite()
Effectuent les rotations nécessaires pour équilibrer l'arbre.

parcoursInfixe(Cel* racine)
Affiche les mots en ordre alphabétique (parcours infixe).

insererDepuisFichier(const string& nomFichier)
Lit un fichier texte et insère tous les mots dans l'arbre rouge-noir.
