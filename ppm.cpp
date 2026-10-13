#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "image.hpp"
#include "ppm.hpp"

/**
 * Auteur : Nous 2
 * Confiance : 4/5, il resterait à traiter le cas où il y a des commentaires dans le fichier PPM
**/
Image lirePPM(string source) {
    ifstream PPM;
    PPM.open(source);
   
    if (not PPM){        // vérifie que le fichier est bien ouvert
        throw runtime_error("Fichier non trouve: " + source);
    }
   
    string p1;
    PPM >> p1;           // On elimine la premiere ligne
   
    double i;            // On récupère la largeur, la longueur et le nombre maximum pour un pixel de l'image
   
    PPM >> i;
    double largeur = i;
   
    PPM >> i;
    double longueur = i;  
   
    PPM >> i;
    double Nb_max = i;
   
    Image Color;                 // declaration tableau 2D
   
    Color = Image(longueur); // Allocation tableau 2D, on rajoute 1 à
                                    // largeur car le premier tableau va contenir
                                    // le max (et non plus les dimensions de l'image binaire)
    /**
    Color[0] = vector<double>(3);    // Allocation et ajout de la valeur maximale d'un pixel dans le 1e tableau
    Color[0][0] = Nb_max;
    Color[0][1] = 0;
    Color[0][2] = 0;  
    **/
         
   
    for(int ind = 0; ind < Color.size(); ind++){  // Allocation sous-tableaux
        Color[ind] = vector<Couleur>(largeur);
    }
   
     
     for(int longue = 0; longue < Color.size(); longue++){              // Initialisation tableaux à                      
         for(int large = 0; large < Color[longue].size() * 3; large++){     // partir de longue = 1 car le 1e tableau                                        
             PPM >> i;                                                 // contient le max                
             if (large % 3 == 0)
                 Color[longue][large / 3].r = i;
             else if (large % 3 == 1)
                 Color[longue][large / 3].g = i;
             else if (large % 3 == 2)
                 Color[longue][large / 3].b = i;
         }
     }
    PPM.close();
    return Color;
}


/**
 * Auteur : Nous 2
 * Confiance : 5/5, en partant du principe que les paramètres rentrés sont conformes
**/
void ecrirePPM(Image img, string cible) {
    ofstream PPM;      // Création du fichier cible
    PPM.open(cible);
   
    PPM << "P3" << endl;                    // Ecriture de la 1ere ligne
   
                                            // Ecriture des dimensions et du nombre maximum pour un pixel de l'image
    double largeur = ((int)img[1].size());  // La largeur (taille d'une ligne) avec la taille d'une ligne du tableau
    double longueur = ((int)img.size());  // La longueur (nombre de lignes) avec la taille du tableau

    PPM << largeur << ' ' << longueur << endl << "255" << endl;
   
    for (int longue = 0; longue < img.size(); longue++) {              // Ecriture des pixels avec longue initialisé à 1
        for (int large = 0; large < img[longue].size(); large++) {     // car le premier tableau contient le max
            PPM << ((int)img[longue][large].r) << " " << ((int)img[longue][large].g) << " " << ((int)img[longue][large].b) << endl;
        }
    }
}
