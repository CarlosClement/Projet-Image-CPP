#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.hpp"
#include "pgm.hpp"



ImageGris lirePGM(string source) {
    ifstream PGM;
    PGM.open(source);
   
    if (not PGM){        // vérifie que le fichier est bien ouvert
        throw runtime_error("Fichier non trouve: " + source);
    }
   
    string p1;
    PGM >> p1;           // On elimine la premiere ligne
   
    double i;            // On récupère la largeur, la longueur et le nombre maximum pour un pixel de l'image
   
    PGM >> i;
    double largeur = i;
   
    PGM >> i;
    double longueur = i;  
   
    PGM >> i;
    double Nb_max = i;
   
    ImageGris Gris;                 // declaration tableau 2D
   
    Gris = ImageGris(longueur + 1); // Allocation tableau 2D, on rajoute 1 à
                                    // largeur car le premier tableau va contenir
                                    // le max (et non plus les dimensions de l'image binaire)
   
    Gris[0] = vector<double>(1);    // Allocation et ajout de la valeur maximale d'un pixel dans le 1e tableau
    Gris[0][0] = Nb_max;
         
   
    for(int ind = 1; ind < Gris.size(); ind++){  // Allocation sous-tableaux
        Gris[ind] = vector<double>(largeur);
    }
   
     
     for(int longue = 1; longue < Gris.size(); longue++){              // Initialisation tableaux à                      
         for(int large = 0; large < Gris[longue].size(); large++){     // partir de longue = 1 car le 1e tableau                                        
             PGM >> i;                                                 // contient le max                 
             Gris[longue][large] = i;
         }
     }
    PGM.close();
    return Gris;
}



void ecrirePGM(ImageGris img, string cible) {
    ofstream PGM;      // Création du fichier cible
    PGM.open(cible);
   
    PGM << "P2" << endl;                    // Ecriture de la 1ere ligne
   
                                            // Ecriture des dimensions et du nombre maximum pour un pixel de l'image
    double largeur = ((int)img[1].size());  // La largeur (taille d'une ligne) avec la taille d'une ligne du tableau
    double longueur = ((int)img.size()-1);  // La longueur (nombre de lignes) avec la taille du tableau
    double max = ((int)img[0][0]);          // Le max d'un pixel stocké dans img
    PGM << largeur << ' ' << longueur << endl << max << endl;
   
    for (int longue = 1; longue < img.size(); longue++) {              // Ecriture des pixels avec longue initialisé à 1
        for (int large = 0; large < img[longue].size(); large++) {     // car le premier tableau contient le max
            PGM << ((int)img[longue][large]) << endl;
        }
    }
}



bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[i].size(); j++)                       // Changement du 0 en i pour correspondre a notre format
            if (abs(a[i][j] - b[i][j]) > precision) {          
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}




ImageGris inversePGM(ImageGris img) {
    ImageGris res = ImageGris(img.size());  // Declaration et allocation tableau 2D
   
    res[0] = vector<double>(1);             // Allocation du tableau contenant la valeur maximale d'un pixel
   
    res[0][0] = img[0][0];                  // Nombre max du pixel

    for (int ind = 1; ind < img.size(); ind++) {  // Allocation sous-tableaux
        res[ind] = vector<double>(img[ind].size());
    }
   
    for (int longue = 1; longue < img.size(); longue++) {                       // Parcourt toutes les valeurs des pixels
        for (int large = 0; large < img[longue].size(); large++) {
            res[longue][large] = res[0][0] - img[longue][large];                // Calcul du complementaire de la valeur initiale du pixel
        }                                                                       // et attribue la valeur complementaire au pixel de l'image inversée
    }
    return res;
}

