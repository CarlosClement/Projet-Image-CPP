/** @file
 * Structures de données pour représenter des images
 **/

#ifndef _IMAGE_H
#define _IMAGE_H

#include <vector>
#include <stdexcept>
using namespace std;

/// BEGIN Couleur
/** Structure de donnees pour representer un pixel en couleur **/
struct Couleur {
    /** Intensite de rouge **/
    double r;
    /** Intensite de vert **/
    double g;
    /** Intensite de bleu **/
    double b;
};
/// END Couleur


/// BEGIN Image
/** Structure de donnees pour representer une image **/
typedef vector<vector<Couleur> > Image;
/// END Image

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;

#endif