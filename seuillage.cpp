#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
#include <fstream>
#include "image.hpp"
#include "sobel.hpp"

ImageGris renormalise(ImageGris img) {
    double maxi = img[0][0];             // On recupere la valeur max d'un pixel de notre image
   
    img[0][0] = 255;                     // On remplace par la valeur du max renormalisé à 255
   
    for(int i = 1; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
                img[i][j] = (255 * img[i][j]) / maxi;     // Calcul de proportionnalité pour attribuer les valeurs renormalisées

        }
    }
   
    return img;
}


ImageGris seuillage(ImageGris img, int seuil) {
   
    if(seuil < 0 or seuil > 255){
        throw runtime_error("Le seuil n'est pas compris dans l'intervalle [0,255]");
    }
   
    img[0][0] = 255;       // Nouvelle valeur max d'un pixel
   
    for(int i = 1; i < img.size(); i ++){
        for(int j = 0; j < img[i].size(); j++){
           
            if(img[i][j] <= seuil){
                img[i][j] = 255;
               
            } else{
                img[i][j] = 0;
            }
        }
    }
    return img;
}



ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
   
    ImageGris img = ImageGris(imgIntensite.size());       // Declaration et Allocation tableau 2D
   
    if(seuil < 0 or seuil > 255){
        throw runtime_error("Le seuil n'est pas compris dans l'intervalle [0,255]");
    }
   
    img[0] = vector<double>(1);                           // Allocation et ajout de la valeur maximale d'un pixel dans le 1e tableau
    img[0][0] = 255;
   
    for(int ind = 1; ind < img.size(); ind++){            // Allocation sous-tableaux
       img[ind] = vector<double>(imgIntensite[ind].size());
    }
   
    for(int j_first = 0; j_first < img[1].size(); j_first++){            // Traitement spécial pour la première ligne
        img[1][j_first] = 255;
    }
   
    for(int j_last = 0; j_last < img[img.size()-1].size(); j_last++){    // Traitement spécial pour la dernière ligne
        img[img.size()-1][j_last] = 255;
    }
   
    for(int i = 2; i < img.size()-1; i ++){                              // Traitement pour toutes les lignes intermédiaires
        //cout << i << endl;
        for(int j = 0; j < img[i].size(); j++){
            //cout << j << endl;
            if(j == 0){                                                  // Traitement spécial pour le premier pixel de chaque colonne
                img[i][j] = 255;
            }
            else if(j == img[i].size()-1){                               // Traitement spécial pour le dernier pixel de chaque colonne
                img[i][j] = 255;
            }
            else if(imgIntensite[i][j] > seuil and (imgContour[i-1][j-1] == 0 or imgContour[i-1][j] == 0 or imgContour[i-1][j+1] == 0 or imgContour[i][j-1] == 0 or imgContour[i][j+1] == 0 or imgContour[i+1][j-1] == 0 or imgContour[i+1][j] == 0 or imgContour[i+1][j+1] == 0)){    
                img[i][j] = 0;                                           // Traitement normal
            } else{
                img[i][j] = 255;
            }
        }
    }
    return img;
}



ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    if (nbAmeliorations < 0) {
        throw runtime_error("Le nombre d'iterations doit etre un nombre positif ou nul.");
    }
   
    ImageGris intensite = renormalise(imgIntensite);            // Renormalisation de imgIntensite pour etre dans la bonne plage de valeurs [0,255]
   
    ImageGris temp = seuillage(intensite, seuilFort);           // Obtention d'une image contour avec un seuillage "seuil fort"
    
    for(int k = 0; k < nbAmeliorations; k++){                   // Iterations des doubles seuillages "seuil faible"
        temp = doubleSeuillage(intensite, temp, seuilFaible);
    }
    
    return temp;
}

