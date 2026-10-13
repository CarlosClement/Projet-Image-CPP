#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.hpp"

ImageGris intensiteH(ImageGris img) {
    ImageGris sobelH;                   // Declaration tableau 2D

    sobelH = ImageGris(img.size());     // Allocation tableau 2D
   
   
    sobelH[0] = vector<double>(1);      // Valeur arbitraire ayant pour but de passer les test et de correspondre a notre format
    sobelH[0][0] = 0;                   // (Ici le vrai max est inutile car cette fonction renvoie un tableau non conforme au format PGM)
   
   

    for(int ind = 1; ind < sobelH.size(); ind++){  // Allocation sous-tableaux
        sobelH[ind] = vector<double>(img[ind].size());
    }

    for(int j_first = 0; j_first < sobelH[1].size(); j_first++){                 // Traitement spécial pour la première ligne
        sobelH[1][j_first] = 0;
    }

    for(int j_last = 0; j_last < sobelH[sobelH.size() - 1].size(); j_last++){    // Traitement spécial pour la dernière ligne
        sobelH[sobelH.size() - 1][j_last] = 0;
    }


    for(int i = 2; i < sobelH.size()-1; i++){                                    // Traitement pour toutes les lignes intermédiaires
        for(int j = 0; j < sobelH[i].size(); j++){
            if (j == 0) {                                                        // Traitement spécial pour le premier pixel de chaque colonne
                sobelH[i][j] = 0;
            } else if (j == sobelH[i].size() - 1) {                              // Traitement spécial pour le dernier pixel de chaque colonne
                sobelH[i][j] = 0;
            } else {                                                             // Traitement normal
                 sobelH[i][j] = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
            }
        }
    }
    return sobelH;
}

ImageGris intensiteV(ImageGris img) {
    ImageGris sobelV;                   // Declaration tableau 2D

    sobelV = ImageGris(img.size());     // Allocation tableau 2D
   
    sobelV[0] = vector<double>(1);      // Valeur arbitraire ayant pour but de passer les test et de correspondre a notre format
    sobelV[0][0] = 0;                   // (Ici le vrai max est inutile car cette fonction renvoie un tableau non conforme au format PGM)
   
   

    for(int ind = 1; ind < sobelV.size(); ind++){  // Allocation sous-tableaux
        sobelV[ind] = vector<double>(img[ind].size());
    }

    for(int j_first = 0; j_first < sobelV[1].size(); j_first++){                 // Traitement spécial pour la première ligne
        sobelV[1][j_first] = 0;
    }

    for(int j_last = 0; j_last < sobelV[sobelV.size() - 1].size(); j_last++){    // Traitement spécial pour la dernière ligne
        sobelV[sobelV.size() - 1][j_last] = 0;
    }


    for(int i = 2; i < sobelV.size()-1; i++){                                    // Traitement pour toutes les lignes intermédiaires
        for(int j = 0; j < sobelV[i].size(); j++){
            if (j == 0) {                                                        // Traitement spécial pour le premier pixel de chaque colonne
                sobelV[i][j] = 0;
            } else if (j == sobelV[i].size() - 1) {                              // Traitement spécial pour le dernier pixel de chaque colonne
                sobelV[i][j] = 0;
            } else {                                                             // Traitement normal
                 sobelV[i][j] = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
            }
        }
    }
    return sobelV;
}

ImageGris intensite(ImageGris img) {
    ImageGris sobel = ImageGris(img.size());    // Declaration tableau 2D
    ImageGris sobelH = intensiteH(img);         // Calcul et stockage dans un tableau des intensites horizontales
    ImageGris sobelV = intensiteV(img);         // Calcul et stockage dans un tableau des intensites verticales
   
    sobel[0] = vector<double>(1);               //On alloue un tableau pour ajouter le max choisie
   
    sobel[0][0] = 0;                            // On initialise le max a 0 (valeur arbitraire qui sera changee)

    for(int ind = 1; ind < sobel.size(); ind++){  // Allocation sous-tableaux
        sobel[ind] = vector<double>(img[ind].size());
    }    
   
    for(int i = 1; i < sobel.size(); i++){        // Calcul de la norme pour l'intensite de chaque pixel
        for(int j = 0; j < sobel[i].size(); j++){
            sobel[i][j] = sqrt((sobelH[i][j])*(sobelH[i][j])+(sobelV[i][j])*(sobelV[i][j]));
            if(sobel[i][j] > sobel[0][0]){        // Recherche de la valeur max du tableau
                sobel[0][0] = sobel[i][j];
            }
        }
    }
    return sobel;
}
