#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.hpp"

/**
 * Auteur : Nous 2
 * Confiance : 5/5
**/
ImageGris CouleurAuGris( Image img ) {
   
    ImageGris Gris = ImageGris(img.size());                 // Declaration et allocation tableau 2D
   
    for (int ind = 0; ind < Gris.size() ; ind++)
        Gris[ind] = vector<double>(img[ind].size());        // Allocation sous-tableaux
   
    for (int longue = 0; longue < Gris.size() ; longue++){  // Calcul du niveau de gris pour chaque pixel
        for (int large = 0; large < Gris[longue].size() ; large++){
            Gris[longue][large] = 0.2126 * img[longue][large].r + 0.7152 * img[longue][large].g + 0.0722 * img[longue][large].b;
        }
    }
    return Gris;
}


/**
 * Auteur : Nous 2
 * Confiance : 5/5
**/
Image GrisACouleur( ImageGris img ) {
   
    Image Color = Image(img.size());                        // Declaration et allocation tableau 2D
   
    for (int ind = 0; ind < Color.size() ; ind++)
        Color[ind] = vector<Couleur>(img[ind].size());      // Allocation sous-tableaux
   
    for (int longue = 0; longue < Color.size() ; longue++){ // Calcul des valeur de couleur de chaque pixel
        for (int large = 0; large < Color[longue].size() ; large++){
            Color[longue][large].r = img[longue][large];
            Color[longue][large].g = img[longue][large];
            Color[longue][large].b = img[longue][large];
        }
    }
    return Color;
   
}
