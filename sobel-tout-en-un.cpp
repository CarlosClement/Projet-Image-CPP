#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {255},                       // Ajout d'un max arbitraire pour simuler notre format
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 * Auteur : Sergiu
 * Confiance : 4/5, il resterait à traiter le cas où il y a des commentaires dans le fichier PGM
 **/
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
    //Gris[0][0] = largeur;
    //Gris[0][1] = longueur;
    Gris[0][0] = Nb_max;
         
   
    for(int ind = 1; ind < Gris.size(); ind++){  // Allocation sous-tableaux
        Gris[ind] = vector<double>(largeur);
    }
   
     
     for(int longue = 1; longue < Gris.size(); longue++){              // Initialisation tableaux à                      
         for(int large = 0; large < Gris[longue].size(); large++){     // partir de longue = 1 car le 1e tableau                                        
             PGM >> i;                                                 // contient le max
             //cout << i << endl;                    
             Gris[longue][large] = i;
         }
     }
    PGM.close();
    return Gris;
}




/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 * Auteur : nous 2
 * Confiance : 5/5, en partant du principe que les paramètres rentrés sont conformes
 **/
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


/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
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



/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 * Auteur : nous 2
 * Confiance : 5/5 en partant du principe que les paramètres sont conformes, et fonction conforme à notre format
 **/
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


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 * Auteur : nous 2
 * Confiance : 5/5 en partant du principe que les paramètres sont conformes, et fonction conforme à notre format
 **/
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



/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 * Auteur : nous 2
 * Confiance : 5/5 en partant du principe que les paramètres sont conformes, et fonction conforme à notre format
 **/
ImageGris intensite(ImageGris img) {
/**    ImageGris sobelH;                   // Declaration tableau 2D

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
            } else {
                 sobelH[i][j] = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
            }
        }
    }
   
   
   
   
   
   
    ImageGris sobelV;                   // Declaration tableau 2D

    sobelV = ImageGris(img.size());  // Allocation tableau 2D
   
    sobelV[0] = vector<double>(1);   // Valeur arbitraire ayant pour but de passer les test et de correspondre a notre format
    sobelV[0][0] = 0;                // (Ici le vrai max est inutile car cette fonction renvoie un tableau non conforme au format PGM)

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
            } else {
                 sobelV[i][j] = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
            }
        }
    }
   
   
**/
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
            //cout << sobel[0][0] << endl;
            //cout << sobel[i][j] << endl;
            if(sobel[i][j] > sobel[0][0]){        // Recherche de la valeur max du tableau
                sobel[0][0] = sobel[i][j];
                //cout << sobel[0][0] << endl;
            }
        }
    }
    return sobel;
}


void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0},                            // Ajout d'un max arbitraire pour simuler notre format
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
   
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0},                            // Ajout d'un max arbitraire pour simuler notre format
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
 
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {423.593},                      // Ajout du maximum du tableau pour simuler notre format
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
   
    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/Willis.512.pgm" )), "sobel/Willis.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");
   
   
    //cout << (intensiteH(lirePGM("images/Willis.512.pgm" ))).size() << endl;
   
}



int main(){
    //cout << "bonjour" << endl;
    //intensite(imgGrisTest);
    testSobel();
    return 0 ;
}
