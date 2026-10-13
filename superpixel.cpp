#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.hpp"

using namespace std;     // rajouter
#include <iostream>
#include <fstream>

/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
double distancePoints(Point p, Point c) {
   
    if(p.size() != c.size())                   // Vérification des tailles des 2 points
        throw runtime_error("Vos points n'ont pas la meme taille");
       
    double dist = 0;                
    for(int i = 0; i < p.size(); i++){        // Calcul du carré de la distance euclidienne
        dist += (p[i] - c[i]) * (p[i] - c[i]);
    }
    return sqrt(dist);
}


/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
double distanceAEnsemble(Point p, EnsemblePoints C) {
   
    // On initialise la distance minimum comme la distance entre p et le premier point de C
   
    if(p.size() != C[0].size())               // Vérification des tailles des 2 points
            throw runtime_error("Votre premier point n'a pas la meme taille que p");
       
    double mini = distancePoints(p, C[0]);
   
    for (int i = 1; i < C.size(); i++){
       
        if (p.size() != C[i].size()){        // Vérification des tailles des 2 points
            throw runtime_error("Votre point" + to_string(i+1) + "n'a pas la meme taille que p");
        }
       
        double dist = distancePoints(p, C[i]);
        if (dist < mini){                   // On regarde si cette distance est plus petite que le minimum actuel
            mini = dist;
        }      
    }
    return mini;
}


/**
 * Auteur : nous 2
 * Confiance : 5/5, nous avons corrige notre code initial pour utiliser distanceAEnsemble comme indique
**/
int plusProcheVoisin(Point p, EnsemblePoints C) {
   
    // On initialise la distance minimum comme la distance entre p et le premier point de C
    /**
    if(p.size() != C[0].size())               // Vérification des tailles des 2 points
            throw runtime_error("Votre premier point n'a pas la meme taille que p");
   **/
   
    //double mini = distancePoints(p, C[0]);
    //int ind = 0;
    
    int ind;
    double mini = distanceAEnsemble(p, C);
   
    for (int i = 0; i < C.size(); i++){
       
        if (p.size() != C[i].size()){        // Vérification des tailles des 2 points
            throw runtime_error("Votre point" + to_string(i+1) + "n'a pas la meme taille que p");
        }
       
        double dist = distancePoints(p, C[i]);
       
        if (dist == mini){                   // On regarde si cette distance est egale au minimum
            //mini = dist;
            ind = i;
        }      
    }
    return ind;
}


/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
   
    if (k < 0 or k > C.size() - 1)         // Vérification que l'entier k correspond bien à un indice de point de C
        throw runtime_error("L'entier entree ne correspond pas a un point de l'ensemble C");
   
    EnsemblePoints res = {};
   
    for(int i = 0; i < P.size(); i++){    // On regarde le plus proche voisin de chaque point de P
        if(k == plusProcheVoisin(P[i],C)){
            res.push_back(P[i]);
        }
    }
    return res;
}


/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
Point barycentre(EnsemblePoints Q) {
   
    Point res = Point(Q[0].size());              // Declaration et allocation tableau
   
    for (int i = 0; i < Q.size() ; i++){        
        if ( res.size() != Q[i].size() )         // Verification de la taille des points de Q
            throw runtime_error("Tous les points n'ont pas la meme taille !");
       
        for (int j = 0; j < Q[i].size(); j++){   // On somme d'abord toutes les coordonnées des points de Q
            res[j] += Q[i][j];
        }
    }
   
    for (int moy = 0; moy < res.size(); moy++){  // Puis on les divise par le nombre de points pour calculer la moyenne
        res[moy] = res[moy] / Q.size();
    }
   
    return res;
}


/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
   
    EnsemblePoints res = EnsemblePoints(C.size());            // Declaration et allocation tableau 2D
   
    /**
    for (int compt = 1; compt <= nbAmeliorations; compt++){
        for (int i = 0; i <= P.size(); i++){
            sousEnsemble(C,P,i);
        }
    **/
   
    for (int compt = 0; compt < nbAmeliorations; compt++){   // Nombre d'itérations
        for (int j = 0; j < res.size(); j++)                 // Pour tous les points de C, on:
            res[j] = barycentre(sousEnsemble(P,C,j));        // 1) Determine les points p de P tel que C[j] est le plus proche voisin de p dans C
                                                             // 2) Calcule le barycentre de ces ensembles de points
    }
       
    return res;
}

   


EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
   
    EnsemblePoints res = {};                   // Declaration et allocation tableau 2D
   
   
    for (double i = 0; i < img.size(); i += mu){             // On ne parcourt plus les lignes de 1 en 1, mais de mu en mu
       
        for (double j = 0; j < img[i].size(); j += mu){      // On ne parcourt plus les pixels des lignes de 1 en 1, mais de mu en mu
           
            //res.push_back(lambda * (img[i][j].r + img[i][j].g + img[i][j].b));
            vector<double> tmp = {i, j, lambda*img[i][j].r, lambda*img[i][j].g, lambda*img[i][j].b};  // Creation des coordonnes du point en dimension 5
            res.push_back(tmp);
        }
    }
    return res;
}


/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
   
    EnsemblePoints pivots = pivotSuperPixel(img, lambda, mu);   // On recupere les points pivots de img
   
    EnsemblePoints image = pivotSuperPixel(img, lambda, 1);     // On recupere les coordonnes en dimension 5 des points de l'image avec la meme fonction, mais en allant de 1 en 1
   
    /**
    for (int i = 0; i < img.size(); i++){
        for (int j = 0; j < img[i].size(); j++){
            //res.push_back(lambda * (img[i][j].r + img[i][j].g + img[i][j].b));
            vector<double> tmp = {lambda*img[i][j].r, lambda*img[i][j].g, lambda*img[i][j].b};
            image.push_back(tmp);
        }
    }
    **/
   
    EnsemblePoints res = FAST_KMoyenne(image, pivots, nbAmeliorations);   // On applique l'algorithme des K-Moyenne sur les points correspondant à l’image et avec les points pivots

    return res;    
}


/**
 * Auteur : nous 2
 * Confiance : 5/5
**/
Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
   
    Image res = Image(img.size());                       // Declaration et allocation tableau 2D
   
    for (int ind = 0; ind < img.size(); ind++)           // Allocation sous-tableaux
        res[ind] = vector<Couleur>(img[ind].size());
   
    //EnsemblePoints pivot = pivotSuperPixel(img, lambda, mu);
    EnsemblePoints pixel = superPixels(img,lambda,mu, nbAmeliorations);   // On determine les superpixels de img
    int Pilote;                         
    Point point_image;
                                                                          // Etape 1 : Calcul des couleurs de chaque pixel
    for (int i = 0; i < img.size(); i++){                                 
        for (int j = 0; j < img[i].size(); j++){
            
            point_image = {i,j,lambda*img[i][j].r,lambda*img[i][j].g,lambda*img[i][j].b}; // Coordonnes en dimension 5 du pixel de img
            Pilote = plusProcheVoisin(point_image, pixel);                                // On determine le point pilote le plus proche du pixel actuel
           
            
            res[i][j].r = pixel[Pilote][2] / lambda;           // Pour le rouge, il est stocke au 3e emplacement des coordonnes 5D du point pilote. 
                                                               // On divise par lambda pour retomber sur la couleur
            res[i][j].g = pixel[Pilote][3] / lambda;           // Pour le vert, il est stocke au 4e emplacement des coordonnes 5D du point pilote. 
            res[i][j].b = pixel[Pilote][4] / lambda;           // Pour le bleu, il est stocke au 5e emplacement des coordonnes 5D du point pilote. 
        }
    }
 
                                                                        // Etape 2 : On determine les contours
    for (int i = 0; i < img.size() - 1; i++){                           // Traitement de toutes les lignes sauf la derniere        
        for (int j = 0; j < img[i].size(); j++){  
                
        if (j == img[i].size() - 1){                                    // Traitement special de la derniere colonne 
            if(res[i][j].r != res[i+1][j].r or res[i][j].g != res[i+1][j].g or res[i][j].b != res[i+1][j].b){   // On ne regarde que la couleur du pixel en dessous
                res[i][j].r = 0;
                res[i][j].g = 0;
                res[i][j].b = 255;
            }        
        }else{                                                         // Traitement normal
            if(res[i][j].r != res[i+1][j].r or res[i][j].g != res[i+1][j].g or res[i][j].b != res[i+1][j].b or res[i][j].r != res[i][j+1].r or res[i][j].g != res[i][j+1].g or res[i][j].b != res[i][j+1].b){               // On regarde la couleur du pixel a droite et en dessous
                res[i][j].r = 0;
                res[i][j].g = 0;
                res[i][j].b = 255;
            }
        }
        }
    }
    
    for(int j_last = 0; j_last < img[img.size()-1].size()-1; j_last++){  // Traitement separe de la derniere ligne, et sans le dernier pixel
        
        if(res[img.size()-1][j_last].r != res[img.size()-1][j_last+1].r or res[img.size()-1][j_last].g != res[img.size()-1][j_last+1].g or res[img.size()-1][j_last].b != res[img.size()-1][j_last+1].b){          // On ne regarde que la couleur du pixel a droite
            res[img.size()-1][j_last].r = 0;
            res[img.size()-1][j_last].g = 0;
            res[img.size()-1][j_last].b = 255;
        }
    }
    return res;
}
    




// Ecrire votre code ici (????????????????)