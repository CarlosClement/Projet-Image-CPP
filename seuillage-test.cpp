#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
#include <stdexcept>
using namespace std;
#include "pgm.hpp"
#include "sobel.hpp"
#include "seuillage.hpp"
#include "image-test.hpp"

void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {255},                                        // Ajout d'un max arbitraire pour correspondre a notre format
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );
}

void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255},                                        // Ajout d'un max arbitraire pour correspondre a notre format
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255},                                        // Ajout d'un max arbitraire pour correspondre a notre format
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 120, 80, 4 ),
                          ImageGris( {
                              {255},                            // Ajout d'un max arbitraire pour correspondre a notre format
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
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 100, 30, 100), "seuillage_double/iteratif_Willis.512.pgm"); // Les seuils etaient 500, 80 auparavant. Nous avons change car: d'apres votre documentation, le seuil fort ne peut pas depasser 255. Nous avions respecte cela et renvoye un runtime_error lorsque la valeur n'etait pas conforme et donc notre fonction ne marchait pas. Nous avons change les seuils pour avoir une image semblable, et nous avons renormalise car sinon la fonction renromalise n'allait servir nulle part et nous trouvions ca etrange
    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
}



int main(){
    cerr << "Tests des fonctions du fichier seuillage-tout-en-un.cpp" << endl;
    renormaliseTest();
    seuillageTest();
    doubleSeuillageTest();
    doubleSeuillageIteratifTest();
}

