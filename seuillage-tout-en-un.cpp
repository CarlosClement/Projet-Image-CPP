#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
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
ImageGris imgGrisTest = {               // Ajout d'un max arbitraire pour simuler notre format
    {255},
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},                                                      
    {158.278, 172.841, 89.0236, 80.0384}
};

/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {50},                               // Ajout d'un max arbitraire pour simuler notre format
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},                                                                              
    {0, 50, 0, 50},
};


/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 * Auteur : nous 2
 * Confiance : 5/5
 **/
ImageGris intensite(ImageGris img) {
    ImageGris sobelH;                   // Declaration tableau 2D

    sobelH = ImageGris(img.size());  // Allocation tableau 2D
   
   
    sobelH[0] = vector<double>(1);   // Valeur arbitraire ayant pour but de passer les test et de correspondre a notre format
    sobelH[0][0] = 0;                // (Ici le vrai max est inutile car cette fonction renvoie un tableau non conforme au format PGM)
   
   

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
   
   
    ImageGris sobel = ImageGris(img.size());  // Declaration tableau 2D
    //ImageGris sobelH = intensiteH(img);       // Calcul et stockage dans un tableau des intensites horizontales
    //ImageGris sobelV = intensiteV(img);       // Calcul et stockage dans un tableau des intensites verticales
   
    sobel[0] = vector<double>(1);             //On alloue un tableau pour ajouter le max choisie
   
    sobel[0][0] = 0;                          // On initialise le max a 0 (valeur arbitraire qui sera changee)

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


/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 * Auteur : Sergiu
 * Confiance : 4/5, il resterait à traiter le cas où il y a des commentaires dans le fichier PGM
 **/
ImageGris lirePGM(string source) {
    ifstream PGM;
    PGM.open(source);
   
    if (not PGM){      // vérifie que PGM est bien ouvert
        throw runtime_error("Fichier non trouve: " + source);
    }
   
    string p1;
    PGM >> p1;        // On elimine la premiere ligne
   
    double i;            // On récupère la largeur, la longueur et le nombre maximum pour un pixel de l'image
   
    PGM >> i;
    double largeur = i;
   
    PGM >> i;
    double longueur = i;  
   
    PGM >> i;
    double Nb_max = i;
   
    ImageGris Gris;      // declaration tableau 2D
   
    Gris = ImageGris(longueur + 1); // Allocation tableau 2D, on rajoute 1 à
                                 //largeur car le premier tableau va contenir
                                 //que le max et non pas les dimensions de l'image binaire
   
    Gris[0] = vector<double>(1);    // Allocation et ajout de la valeur maximale d'un pixel
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
   
    PGM << "P2" << endl;                // Ecriture de la 1ere ligne
    double largeur = ((int)img[1].size());  // Ecriture du nombre maximum pour un pixel de l'image
    double longueur = ((int)img.size()-1);
    double max = ((int)img[0][0]);
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


/// BEGIN renormalise

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 * Auteur : nous 2
 * Confiance : 4/5, le test n'étant pas entièrement clair, nous pensons que la proportionnalité était la voie attendue
 **/
ImageGris renormalise(ImageGris img) {
    double maxi = img[0][0];             // On recupere la valeur max d'un pixel de notre image
   
    /**
    if (maxi > 255 or maxi < 0){
        throw runtime_error("Tableau non conforme car le maximum n'est pas dans l'intervalle souhaitee");
    }
    **/
   
    img[0][0] = 255;                     // On remplace par la valeur du max renormalisé à 255
   
    for(int i = 1; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
                img[i][j] = (255 * img[i][j]) / maxi;     // Calcul de proportionnalité pour attribuer les valeurs renormalisées

        }
    }
   
    return img;
}
   


void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {255},                                        //pour correspondre a notre format
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );
}
   
   
   
   
/// BEGIN seuillage

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir si teinte > seuil
 * Auteur : nous 2
 * Confiance : 5/5, vérification de la valeur du seuil
 **/

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

   
   
   
   
/// BEGIN doubleSeuillage

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 * Auteur : nous 2
 * Confiance : 5/5, vérification de la valeur du seuil
 **/
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
   
   
   
   
   
 
/// BEGIN doubleSeuillageIteratif

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 * Auteur : nous 2
 * Confiance :
 **/

ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    if (nbAmeliorations < 0) {
        throw runtime_error("Le nombre d'iterations doit etre un nombre positif ou nul.");
    }
   
    ImageGris intensite = renormalise(imgIntensite);            // Renormalisation de imgIntensite pour etre dans la bonne plage de valeurs [0,255]
   
    ImageGris temp = seuillage(intensite, seuilFort);           // Obtention d'une image contour avec un seuillage "seuil fort"
   
    //return temp;
   
    for(int k = 0; k < nbAmeliorations; k++){                   // Iterations des doubles seuillages "seuil faible"
        temp = doubleSeuillage(intensite, temp, seuilFaible);
    }
    return temp;
   
}


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255},                            // Ajout d'un max arbitraire pour simuler notre format
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255},                            // Ajout d'un max arbitraire pour simuler notre format
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
   
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 120, 80, 4 ),
                          ImageGris( {
                              {255},               // Ajout d'un max arbitraire pour simuler notre format
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );
   

    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Willis.512.pgm"  )), 110), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;

    ecrirePGM(seuillage(intensite(lirePGM("images/House.256.pgm"  )), 150), "seuillage/House.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Embryos.512.pgm"  )), 170), "seuillage/Embryos.512.pgm"); // Test rajoutes avec seuillages differents
}

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 100), 80), "seuillage_double/Willis.512.pgm");
    //doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 100), 80);
    ecrirePGM(doubleSeuillage(lirePGM("images/Billes.256.pgm"), seuillage(intensite(lirePGM("images/Billes.256.pgm")), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
   
    ecrirePGM(doubleSeuillage(lirePGM("images/House.256.pgm"), seuillage(intensite(lirePGM("images/House.256.pgm")), 150), 80), "seuillage_double/House.256.pgm");
   
    ecrirePGM(doubleSeuillage(lirePGM("images/Embryos.512.pgm"), seuillage(intensite(lirePGM("images/Embryos.512.pgm")), 120), 80), "seuillage_double/Embryos.512.pgm");
}


void doubleSeuillageIteratifTest() {
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 100, 30, 100), "seuillage_double/iteratif_Willis.512.pgm"); // Les seuils etaient 500, 80 auparavant. Nous avons change car: d'apres votre documentation, le seuil fort ne peut pas depasser 255. Nous avions respecte cela et renvoye un runtime_error lorsque la valeur n'etait pas conforme et donc notre fonction ne marchait pas. Nous avons change les seuils pour avoir une image semblable, et nous avons renormalise car sinon cette fonction n'allait servir nulle part et nous trouvions ca etrange
    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
   
}

int main(){
    renormaliseTest();
    seuillageTest();
    doubleSeuillageTest();
    doubleSeuillageIteratifTest();
    return 0;
}