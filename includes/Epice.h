#include <fstream>
#include <iostream>
#include <iomanip> // Pour setw et left (left aligne a gauche au lieu de droite) https://www.geeksforgeeks.org/setw-function-in-cpp-with-examples/ https://stackoverflow.com/questions/76906585/how-do-the-stdleft-and-stdright-i-o-manipulators-work-and-why-are-they-used
using namespace std;

//Cette classe représente une epice
class Epice
{
private:
    int id;
    string nom;
    string type;
    double prix;
    double quantite;
    string categorie;

public:
    // Constructeur
    Epice() : id(0), nom(""), type(""), prix(0.0), quantite(0.0), categorie("") {};
    Epice(const int id, const string nom, const string type, const double prix, const double quantite, const string categorie)
        : id(id), nom(nom), type(type), prix(prix), quantite(quantite), categorie(categorie) {};

    //Destructeur
    ~Epice(){};

    // Getters
    int getId() const { return id; }
    string getNom() const { return nom; }
    string getType() const { return type; }
    double getPrix() const { return prix; }
    double getQuantite() const { return quantite; }
    string getCategorie() const { return categorie; }

    //Cette methode affiche l'epice dans le terminal
    void afficher()
    {
        cout << setprecision(3) << left << setw(5) << id << " | "
             << setw(15) << nom << " | "
             << setw(10) << type << " | "
             << setw(8) << prix << "$" << " | "
             << setw(8) << quantite << " | "
             << setw(10) << categorie << endl;
    }
};
