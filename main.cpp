#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*****************************************************************************************
 Nom de structure : Cel
 Description : Représente un nœud de l'arbre rouge-noir (mots).
*****************************************************************************************/
enum Couleur { ROUGE, NOIR };

struct Cel {
    string val;        // Valeur (le mot)
    Couleur couleur;   // Couleur du nœud
    Cel* gauche;
    Cel* droite;
    Cel* parent;
};

/*****************************************************************************************
 Nom de fonction : creerCel
 Description : Crée un nouveau nœud rouge avec le mot donné.
 Entrée : string val
 Sortie : pointeur vers le nouveau nœud.
*****************************************************************************************/
Cel* creerCel(string val) {
    Cel* nouveau = new Cel;
    nouveau->val = val;
    nouveau->couleur = ROUGE; // nouveau nœud toujours rouge
    nouveau->gauche = nullptr;
    nouveau->droite = nullptr;
    nouveau->parent = nullptr;
    return nouveau;
}

/*****************************************************************************************
 Rotations gauche/droite pour RBT
*****************************************************************************************/
Cel* rotationGauche(Cel* root, Cel* x) {
    Cel* y = x->droite;
    x->droite = y->gauche;
    if (y->gauche != nullptr) y->gauche->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->gauche) x->parent->gauche = y;
    else x->parent->droite = y;
    y->gauche = x;
    x->parent = y;
    return root;
}

Cel* rotationDroite(Cel* root, Cel* x) {
    Cel* y = x->gauche;
    x->gauche = y->droite;
    if (y->droite != nullptr) y->droite->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->gauche) x->parent->gauche = y;
    else x->parent->droite = y;
    y->droite = x;
    x->parent = y;
    return root;
}

Cel* correctionInsertion(Cel* root, Cel* pt) {
    Cel* parent_pt = nullptr;
    Cel* grand_parent_pt = nullptr;

    while (pt != root && pt->parent->couleur == ROUGE) {
        parent_pt = pt->parent;
        grand_parent_pt = parent_pt->parent;

        if (parent_pt == grand_parent_pt->gauche) {
            Cel* uncle = grand_parent_pt->droite;
            if (uncle != nullptr && uncle->couleur == ROUGE) {
                grand_parent_pt->couleur = ROUGE;
                parent_pt->couleur = NOIR;
                uncle->couleur = NOIR;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->droite) {
                    root = rotationGauche(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                root = rotationDroite(root, grand_parent_pt);
                swap(parent_pt->couleur, grand_parent_pt->couleur);
                pt = parent_pt;
            }
        } else {
            Cel* uncle = grand_parent_pt->gauche;
            if (uncle != nullptr && uncle->couleur == ROUGE) {
                grand_parent_pt->couleur = ROUGE;
                parent_pt->couleur = NOIR;
                uncle->couleur = NOIR;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->gauche) {
                    root = rotationDroite(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                root = rotationGauche(root, grand_parent_pt);
                swap(parent_pt->couleur, grand_parent_pt->couleur);
                pt = parent_pt;
            }
        }
    }
    root->couleur = NOIR;
    return root;
}

/*****************************************************************************************
 Nom de fonction : insererCel
 Description : Insère un nouveau mot dans l'arbre rouge-noir.
*****************************************************************************************/
Cel* insererCel(Cel* root, string val) {
    Cel* pt = creerCel(val);

    // Recherche de la position d'insertion
    Cel* parent = nullptr;
    Cel* current = root;
    while (current != nullptr) {
        parent = current;
        if (val < current->val) {
            current = current->gauche;
        } else {
            current = current->droite;
        }
    }

    // Insertion du nouveau nœud
    pt->parent = parent;
    if (parent == nullptr) {
        root = pt; // L'arbre était vide
    } else if (val < parent->val) {
        parent->gauche = pt;
    } else {
        parent->droite = pt;
    }

    // Correction des propriétés rouge-noir
    return correctionInsertion(root, pt);
}

/*****************************************************************************************
 Nom de fonction : parcoursInfixe
 Description : Affiche les mots en ordre alphabétique avec couleur.
*****************************************************************************************/
void parcoursInfixe(Cel* racine) {
    if (racine != nullptr) {
        parcoursInfixe(racine->gauche);
        // Décommentez la ligne suivante pour afficher les mots avec leur couleur
        //cout << racine->val << " (" << (racine->couleur == ROUGE ? "R" : "N") << ")" << endl;
        parcoursInfixe(racine->droite);
    }
}

/*****************************************************************************************
 Nom de fonction : insererDepuisFichier
*****************************************************************************************/
Cel* insererDepuisFichier(const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << nomFichier << endl;
        return nullptr;
    }

    Cel* racine = nullptr;
    string mot;


    cout << "Insertion des mots depuis le fichier " << nomFichier << " :\n";

    while (fichier >> mot) {
        racine = insererCel(racine, mot);
       // cout << "Mot inséré : " << mot << " (" << compteur << ")" << endl;
    }

    fichier.close();
    return racine;
}

/*****************************************************************************************
 Fonction principale
*****************************************************************************************/
int main() {
    string nomFichier = "test1.txt";

    cout << "=== Arbre Rouge-Noir - Insertion depuis fichier ===\n";
    Cel* racine = insererDepuisFichier(nomFichier);

    if (racine == nullptr) {
        cout << "Aucun mot inséré. Vérifiez le fichier " << nomFichier << endl;
        return 1;
    }

    cout << "\n=== Mots dans l'ordre alphabétique avec couleur ===\n";
    parcoursInfixe(racine);

    return 0;
}
