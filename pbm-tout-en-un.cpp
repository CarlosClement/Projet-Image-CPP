#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

/// BEGIN ImageNB

/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;

/// END ImageNB


/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 * Auteur : Sergiu
 * Confiance : 4/5, il resterait à traiter le cas où il y a des commentaires dans le fichier PBM
 **/
ImageNB lirePBM(string source) {
    ifstream PBM;
    PBM.open(source);
   
    if (not PBM){      // vérifie que le fichier est bien ouvert
        throw runtime_error("Fichier non trouve: " + source);
    }
   
    string p1;
    PBM >> p1;        // On elimine la premiere ligne
   
    int i;            // On récupère la largeur et la longueur de l'image
   
    PBM >> i;
    int largeur = i;
   
    PBM >> i;
    int longueur = i;  
   
    ImageNB BIN;      // declaration tableau 2D
   
    BIN = ImageNB(longueur);     // Affectation tableau 2D, (on ne rajoute plus 1 à
                                 //longueur car le premier tableau ne va plus contenir
                                 //les dimensions de l'image binaire)
   
    //////////////////////////////////////////////////////////////////
   /**
    BIN[0] = vector<int>(2);    // Allocation et ajout des dimensions
    BIN[0][0] = largeur;                                                    
    BIN[0][1] = longueur;
    **/    
   //////////////////////////////////////////////////////////////////
   
    for(int ind = 0; ind < BIN.size(); ind++){  // Affectation sous-tableaux
        BIN[ind] = vector<int>(largeur);
    }
   
     
     for(int longue = 0; longue < BIN.size(); longue++){              // Initialisation tableaux                        
         for(int large = 0; large < BIN[longue].size(); large++){     // (à partir de longue = 0 car le 1e tableau                                        
             PBM >> i;                                                // ne contient plus les dimensions)
             BIN[longue][large] = i;
         }
     }
    PBM.close();
    return BIN;
}



/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 * Auteur : Sergiu
 * Confiance : 5/5, en partant du principe que les paramètres rentrés sont conformes (bonnes dimensions pour img, cible valable comme nom de fichier...)
 * Suggestion : Si l'on veut, on pourrait garder le commentaire d'un ficher dans img et le réecrire dans notre nouveau fichier cible
 **/

void ecrirePBM(ImageNB img, string cible) {
    ofstream PBM;                 // Création du fichier cible
    PBM.open(cible);
   
    PBM << "P1" << endl;          // Ecriture de la 1ere ligne
   
                                  // Ecriture des dimensions de l'image
    int largeur = img[0].size();  // La largeur (taille d'une ligne) avec la taille d'une ligne du tableau
    int longueur = img.size();    // La longueur (nombre de lignes) avec la taille du tableau
    PBM << largeur << ' ' << longueur << endl;
   
   
    for (int longue = 0; longue < img.size(); longue++) {              // Ecriture des pixels
        for (int large = 0; large < img[longue].size(); large++) {    
            PBM << img[longue][large] << endl;
        }
    }
}



/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 * Auteur : Sergiu
 * Confiance : 5/5, en partant du principe que les paramètres sont conformes
 **/

void affichePBM(ImageNB img)  {
       
    for (int longue = 0; longue < img.size(); longue++) {           // Parcourt toutes les valeurs des pixels
        for (int large = 0; large < img[longue].size(); large++) {
            if (img[longue][large] == 0) {                          // Vérifie si le pixel vaut 0 ou 1
                cout << ' ';
            } else if (img[longue][large] == 1) {
                cout << '@'; }
            }
            cout << endl;    
        }
}



/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 * Auteur : nous 2
 * Confiance : 5/5, en partant du principe que les paramètres sont conformes.
 **/

ImageNB inversePBM(ImageNB img) {

    ImageNB res = ImageNB(img.size());  // Declaration et allocation tableau 2D
   
    //////////////////////////////////////////
    //res[0] = vector<int>(2);  // Allocation du tableau contenant les dimensions
   
    // On copie les dimensions
    //res[0][0] = img[0][0];   // largeur
    //res[0][1] = img[0][1];   // longueur
    //////////////////////////////////////////
   
   
    for (int ind = 0; ind < img.size(); ind++) {  // Allocation sous-tableaux
        res[ind] = vector<int>(img[ind].size());
    }
   
    for (int longue = 0; longue < img.size(); longue++) {               // Parcourt toutes les valeurs des pixels
        for (int large = 0; large < img[longue].size(); large++) {
            res[longue][large] = 1 - img[longue][large];                 // Calcul du complementaire de la valeur initiale du pixel
        }                                                                // et attribue la valeur complementaire au pixel de l'image inversée
    }
    return res;
}



void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
    affichePBM(lirePBM("images/smiley.pbm"));
    affichePBM(inversePBM(lirePBM("images/smiley.pbm")));
   
    //cout << "NE PAS OUBLIER DE COMMENTER" << endl;
    //affichePBM(lirePBM("pbm/cercle.pbm"));
   
}



int main(){
    testLirePBM();
    return 0;
}