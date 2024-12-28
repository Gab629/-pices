#include <fstream>
#include <iostream>
#include <iomanip> // Pour setw et left (left aligne a gauche au lieu de droite) https://www.geeksforgeeks.org/setw-function-in-cpp-with-examples/ https://stackoverflow.com/questions/76906585/how-do-the-stdleft-and-stdright-i-o-manipulators-work-and-why-are-they-used
using namespace std;

class Fournisseur
{
private:
    int id;
    string nom;
    string prenom;
    string courriel;
    string telephone;

public:
    // Constructeur
    Fournisseur() : id(0), nom(""), prenom(""), courriel(""), telephone("") {};
    Fournisseur(const int id, const string nom, const string prenom, const string courriel, const string telephone)
        : id(id), nom(nom), prenom(prenom), courriel(courriel), telephone(telephone) {};

    // Destructeur
    ~Fournisseur(){};

    //  Getters
    int getId() const { return id; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getCourriel() const { return courriel; }
    string getTelephone() const { return telephone; }

    //Cette methode affiche le fournisseur dans le terminal
    void afficher()
    {
        cout << setprecision(3) << left
             << setw(5) << id << " | "
             << setw(15) << nom << " | "
             << setw(15) << prenom << " | "
             << setw(25) << courriel << " | "
             << setw(12) << telephone << endl;
    }
};
