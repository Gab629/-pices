#include <map>
#include "../includes/Epice.h"
#include "../includes/Fournisseur.h"

template <typename Key, typename Value>
class GestionnaireMap
{
protected:
    map<Key, Value> data; //Data doit etre accessible dans les enfants (protected)

public:
    //Cette methode ajoute un element dans le map du type que vous desirez
    void ajouter(const Key &cle, const Value &valeur)
    {
        if (data.find(cle) != data.end()) // On verifie que la clee n'existe pas deja
        {
            cerr << "Erreur : Un élément avec cette clé existe déjà." << endl;
            return;
        }

        data[cle] = valeur;
    }

    //Cette methode supprime un element dans le map
    void supprimer(const Key &cle)
    {
        if (data.erase(cle) > 0)
        { 
            
            cout << "Élément supprimé avec succès !" << endl;
        }
        else
        {
            cerr << "Erreur : Aucun élément trouvé avec cette clé." << endl;
        }
    }

    //Cette methode permet d'afficher un element du map
    Value lire(const Key &cle) const
    {
        for (auto pair : data)
        {
            cout << pair.first << " : " << pair.second.afficher() << endl;
        }
    }

    //Cette methode retourne la taille du map, donc le nb d'elements contenus
    size_t taille() const
    {
        return data.size();
    }
};

//Cette classe est un map qui herite de GestionnaireMap et qui implemente les fonctions propres aux epices
template <typename Key, typename Value>
class GestionMapEpice : public GestionnaireMap<int, Epice>
{

public:
    //Cette methode parcours le map et affiche tous ses elements
    void afficherTous() const
    { //https://cplusplus.com/reference/iomanip/setprecision/
        cout << left << setw(5) << "ID" << " | "
             << setw(15) << "Nom" << " | "
             << setw(10) << "Type" << " | "
             << setw(8) << "Prix" << " | "
             << setw(8) << "Quantité" << " | "
             << setw(10) << "Catégorie" << endl;

        cout << string(70, '-') << endl; // https://stackoverflow.com/questions/11843226/multiplying-a-string-by-an-int-in-c

        for (auto pair : data)
        {
            pair.second.afficher();
        }
        cout << "\n\n";
    }

    //Cette methode recherche et retourne l'epice qui coute le plus cher
    Epice rechercherEpicePrixPlusEleve()
    {
        Epice epicePlusCher;
        for (auto pair : data)
        {
            if (epicePlusCher.getPrix() < pair.second.getPrix())
            {
                epicePlusCher = pair.second;
            }
        }
        cout << "Epice la plus chère trouvé : ";
        epicePlusCher.afficher();
        return epicePlusCher;
    }

    //Cette methode calcule la moyenne du prix de toutes les epices
    double calculerMoyenneDuPrixDesEpices()
    {
        double moyenne = 0;
        for (auto pair : data)
        {
            moyenne = moyenne + pair.second.getPrix();
        }
        return moyenne / taille();
    }
};

//Cette classe est un map qui herite de GestionnaireMap et qui implemente les fonctions propres aux fournisseurs
template <typename Key, typename Value>
class GestionMapFournisseur : public GestionnaireMap<int, Fournisseur>
{

public:

    //Cette méthode affiches tous les fournisseurs contenus dans le map en colonnes bien nommés
    void afficherTous() const
    {
        cout << left
             << setw(5) << "ID" << " | "
             << setw(15) << "Nom" << " | "
             << setw(15) << "Prénom" << " | "
             << setw(25) << "Courriel" << " | "
             << setw(12) << "Téléphone" << endl;

        cout << string(80, '-') << endl; //Crée une ligne de 80 -

        for (auto pair : data)
        {
            pair.second.afficher();
        }
        cout << "\n\n";
    }

    //Cette methode recherche et retourne un fournisseur selon son courriel
    Fournisseur rechercherUnFournisseurParCourriel(string courriel)
    {
        for (auto pair : data)
        {
            if (courriel == pair.second.getCourriel())
            {
                cout << "Fournisseur trouvé : " << pair.second.getNom() << " " << pair.second.getPrenom() << endl;
                return pair.second;
            }
        }
        cerr << "Le fournisseur n'a pas été trouvé" << endl;
        return Fournisseur();
    }
};
