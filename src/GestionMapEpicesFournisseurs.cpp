#include <Windows.h> // Pour afficher les accents : https://www.youtube.com/watch?v=H3S1aIeZc10
#include <sstream>
#include <string>
#include <stdexcept>
#include "../includes/GestionnairesMaps.h"
using namespace std;

// Cette fonction charge les epices dans le fichier texte jusque dans un map
void chargerEpices(const string &fichier, GestionnaireMap<int, Epice> &gestionnaireEpices)
{
    ifstream file(fichier);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string ID, nom, type, prix, quantite, categorie, fournisseurID;

            getline(ss, ID, ';');
            getline(ss, nom, ';');
            getline(ss, type, ';');
            getline(ss, prix, ';');
            getline(ss, quantite, ';');
            getline(ss, categorie, ';');
            Epice *nouvelleEpice = new Epice(stoi(ID), nom, type, stod(prix), stod(quantite), categorie);
            gestionnaireEpices.ajouter(stoi(ID), *nouvelleEpice); // On ajoute une épice à la liste
            delete nouvelleEpice;                                 // Libere la memoire apres avoir ajouter l'epice
        }
    }
    else
    {
        throw invalid_argument("Impossible d'ouvrir le fichier : " + fichier);
    }
    file.close();
}

// Cette fonction charge les fournisseurs dans le fichier texte jusque dans un map
void chargerFournisseur(const string &fichier, GestionnaireMap<int, Fournisseur> &gestionnaireFournisseur)
{
    ifstream file(fichier);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string ID, nom, prenom, courriel, telephone;

            getline(ss, ID, ';');
            getline(ss, nom, ';');
            getline(ss, prenom, ';');
            getline(ss, courriel, ';');
            getline(ss, telephone, ';');
            Fournisseur *nouveauFournisseur = new Fournisseur(stoi(ID), nom, prenom, courriel, telephone);
            gestionnaireFournisseur.ajouter(stoi(ID), *nouveauFournisseur); // On ajoute un fournisseur à la liste
            delete nouveauFournisseur;                                      // Libere la memoire apres avoir ajouter le fournisseur
        }
    }
    else
    {
        throw invalid_argument("Impossible d'ouvrir le fichier : " + fichier);
    }
    file.close();
}

// Cette fonction affiche un menu et retourne le choix de l'utilisateur
int afficherMenu()
{
    cout << "\n================= MENU PRINCIPAL =================" << endl;
    cout << "1. Ajouter une nouvelle épice" << endl;
    cout << "2. Afficher toutes les épices" << endl;
    cout << "3. Supprimer une épice" << endl;
    cout << "4. Rechercher un fournisseur par courriel" << endl;
    cout << "5. Supprimer un fournisseur" << endl;
    cout << "6. Afficher tous les fournisseurs" << endl;
    cout << "7. Afficher le nombre total d’épices et de fournisseurs" << endl;
    cout << "8. Afficher l’épice avec le prix le plus élevé" << endl;
    cout << "9. Afficher la moyenne des prix des épices" << endl;
    cout << "10. Quitter" << endl;
    cout << "==================================================" << endl;
    cout << "Entrez votre choix : ";
    int choix;
    cin >> choix;
    return choix;
}

// Cette fonction prends le choix de l'utilisateur et exécutes les bonnes fonctions, ensuite le menu est réaffiché si l'utilisateur n'a pas quitté
void interaction(int choix, GestionMapEpice<int, Epice> &gestionnaireEpices, GestionMapFournisseur<int, Fournisseur> &gestionnaireFournisseurs)
{
    if (choix == 10)
    {
        cout << "Au revoir !" << endl;
        return;
    }

    switch (choix)
    {
    case 2:
    { // Afficher toutes les épices
        gestionnaireEpices.afficherTous();
        break;
    }
    case 3:
    { // Supprimer une épice
        int numeroEpice;
        cout << "Entrez le numéro de l'épice à supprimer: ";
        cin >> numeroEpice;
        gestionnaireEpices.supprimer(numeroEpice);
        break;
    }
    case 4:
    { // Rechercher un fournisseur par courriel
        string courrielFournisseur;
        cout << "Entrez le courriel du fournisseur que vous recherchez : ";
        cin >> courrielFournisseur;
        gestionnaireFournisseurs.rechercherUnFournisseurParCourriel(courrielFournisseur);
        break;
    }
    case 5:
    { // Supprimer un fournisseur
        int numeroFournisseur;
        cout << "Entrez le numéro du fournisseur à supprimer: ";
        cin >> numeroFournisseur;
        gestionnaireFournisseurs.supprimer(numeroFournisseur);
        break;
    }
    case 6:
    { // Afficher tous les fournisseurs
        gestionnaireFournisseurs.afficherTous();
        break;
    }
    case 7: // Afficher le nombre total d’épices et de fournisseurs
        cout << "Nombre total d'épices : " << gestionnaireEpices.taille() << endl;
        cout << "Nombre total de fournisseurs : " << gestionnaireFournisseurs.taille() << endl;
        break;
    case 8: // Afficher l’épice avec le prix le plus élevé
        gestionnaireEpices.rechercherEpicePrixPlusEleve();
        break;
    case 9:
    { // Afficher la moyenne des prix des épices
        cout << setprecision(3) << "Moyenne du prix des épices : " << gestionnaireEpices.calculerMoyenneDuPrixDesEpices() << "$" << endl;
        break;
    }

    default: // Ajouter une epice
        string epiceName;
        cout << "Entrez le nom de votre épice : ";
        cin >> epiceName;
        int position = gestionnaireEpices.taille() + 1;
        Epice *nouvelleEpice = new Epice(position, epiceName, "type", 0.0, 0.0, "quantite");
        gestionnaireEpices.ajouter(position, *nouvelleEpice);
        break;
    }

    interaction(afficherMenu(), gestionnaireEpices, gestionnaireFournisseurs);
}

int main()
{
    SetConsoleOutputCP(65001); // Pour afficher les accents : https://www.youtube.com/watch?v=H3S1aIeZc10


    string fichierEpice = "./donnees/epices.txt";
    string fichierFournisseur = "./donnees/fournisseurs.txt";
    GestionMapEpice<int, Epice> gestionnaireEpices;
    GestionMapFournisseur<int, Fournisseur> gestionnaireFournisseurs;

    try{
        chargerEpices(fichierEpice, gestionnaireEpices); //Contient les epices
        chargerFournisseur(fichierFournisseur, gestionnaireFournisseurs); //Contient les fournisseurs
    }
    catch (const invalid_argument &e){
        cerr << e.what() << '\n';
        cout << "Programme terminé." << endl;
        return 0;
    }
    catch (const exception &e)
    {
        cerr << "Une erreur s'est produite : " << e.what() << endl;
        cout << "Programme terminé." << endl;
        return 0;
    }

    interaction(afficherMenu(), gestionnaireEpices, gestionnaireFournisseurs);

    return 0;
}