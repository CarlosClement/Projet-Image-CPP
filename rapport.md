---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

# Rapport de projet Image

*Les paragraphes en italique comme celui-ci vous donnent des
indications sur le contenu attendu; ils sont à supprimer une fois
votre rapport rédigé*

*Ce rapport pourra servir de support pour votre présentation orale*

*Soyez objectifs et factuels! Vous ne serez pas évalué sur ce que vous
affirmez, mais sur la pertinence et la justesse de ce que vous
affirmez.*

+++ {"tags": []}

## Auteurs

- Clement, Carlos, LDD1IM 1
- Mardare, Sergiu, LDD1IM 2

+++ {"tags": []}

## Résumé du travail effectué

*Pour chaque partie du sujet, décrire brièvement l'avancement de votre
projet. Exemples de réponses: «non traitée», «réalisée, documentée,
testée», «réalisée, sauf 2.3», «réalisée mais non testée», «réalisée
sauf 2.4 pour lequel notre programme ne compile pas». Pour les
questions «Aller plus loin» plus ouvertes, décrire plus en détail ce
que vous avez choisi de réaliser.*

*En plus du rapport, la documentation de chaque fonction dans le code
devra préciser son auteur et votre degré de confiance dans
l'implantation et les éléments factuels motivant cette confiance:
présence de tests, bogues et limitations connus, etc.*

- Partie 1: Realisée, Documentée, Testée
- Partie 2: Realisée, Documentée, Testée
- Partie 3: Realisée, Documentée, Testée sauf "Aller plus loin"
- Partie 4: Realisée, Documentée, Testée
- Partie 5: Realisée, Documentée, Testée
- Partie 6: Realisée, Documentée, Testée sauf "Aller plus loin"

+++

## Démonstration

*Soutenez ce que vous affirmez dans la section précédente au moyen de
quelques exemples **bien choisis**. Vous pourrez par exemple compiler et
lancer certains de vos programmes, lancer des tests, afficher des images.*

*Ci-dessous, nous vous proposons un début de démonstration pour les différentes
parties*

*Ne gardez que des exemples pertinents qui mettent en valeur votre
travail. Inutile de perdre du temps sur le premier programme si vous
avez fait les suivants plus compliqués; l'auditeur se doutera bien que
vous avez réussi à le faire.*

+++

### Partie 1

*Les cellules commençant par `%%bash` sont interprétées comme des
commandes bash, comme dans un terminal* :

```{code-cell} ipython3
%%bash --login
clang++ pbm-affiche.cpp -o pbm-affiche
```

```{code-cell} ipython3
%%bash --login
./pbm-affiche
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley-inverse.pbm")      # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
clang++ pbm-tout-en-un.cpp -o pbm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pbm-tout-en-un
```

### Partie 2

```{code-cell} ipython3
%%bash --login
clang++ pgm-tout-en-un.cpp -o pgm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pgm-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain.pgm")               # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

### Partie 3

```{code-cell} ipython3
%%bash --login
clang++ sobel-tout-en-un.cpp -o sobel-tout-en-un
```

```{code-cell} ipython3
! ./sobel-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{raw-cell}

---------------------------------------------------     SOBEL         ----------------------------------------------------------------------
```

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Baboon.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

+++ {"tags": []}

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée

+++ {"tags": []}

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Embryos.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée

```{raw-cell}

---------------------------------------------------     SEUILLAGE         ----------------------------------------------------------------------
```

```{code-cell} ipython3
%%bash --login
clang++ seuillage-tout-en-un.cpp -o seuillage-tout-en-un
```

```{code-cell} ipython3
:tags: []

! ./seuillage-tout-en-un
```

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

+++ {"tags": []}

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

+++ {"tags": []}

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Embryos.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée

```{raw-cell}

---------------------------------------------------     DOUBLE_SEUILLAGE         ---------------------------------------------------------------
```

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

+++ {"tags": []}

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

+++ {"tags": []}

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Embryos.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée

```{raw-cell}

---------------------------------------------------     DOUBLE_SEUILLAGE_ITERATIF         ------------------------------------------------------
```

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Willis.512.pgm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

### Partie 4

```{code-cell} ipython3
%%bash --login
make pgm-test
```

```{code-cell} ipython3
%%bash --login
./pgm-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/correction/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{code-cell} ipython3
%%bash --login
make sobel-test
```

```{code-cell} ipython3
%%bash --login
./sobel-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
:tags: []

%%bash --login
make seuillage-test
```

```{code-cell} ipython3
%%bash --login
./seuillage-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
:tags: []

%%bash --login
make TIN
```

```{code-cell} ipython3
:tags: []

%%bash --login
./TIN -s images/Willis.512.pgm sobel/Willis.512.pgm
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

### Partie 5

*A compléter*

```{code-cell} ipython3
%%bash --login
clang++ ppm.cpp ppm-test.cpp -o ppm-test
```

```{code-cell} ipython3
! ./ppm-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("images/Baboon.512.ppm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/Baboon.512.ppm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
:tags: []

%%bash --login
clang++ gris-couleurs.cpp gris-couleurs-test.cpp pgm.cpp ppm.cpp -o gris-couleurs-test
```

```{code-cell} ipython3
:tags: []

! ./gris-couleurs-test
```

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Baboon.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

### Partie 6

*A compléter*

```{code-cell} ipython3
:tags: []

%%bash --login
make all
```

```{code-cell} ipython3
:tags: []

%%bash --login
make superpixel-test
```

```{code-cell} ipython3
:tags: []

%%bash --login
./superpixel-test
```

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Willis.512.ppm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
:tags: []

# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Billes.256.ppm")        # charge l'image
im.resize((512*im.width // im.height, 512))  # affiche l'image avec une taille donnée
```

## Organisation du travail

*Décrire en quelques phrases comment vous vous êtes organisés pour
travailler sur le projet: nombre d'heures consacrées au projet,
répartition du travail dans le binôme, moyens mis en œuvre pour
collaborer, etc. Si vous avez bénéficié d'aide (en dehors de celle
de vos enseigants), précisez le.*

+++

Temps mis a deux: 30h

+ Travail en commun a la Bibliotheque Universitaire, jeu de passe passe

+ Utilistation d'un ecran pour projeter le PC et voir le code facilement

+ Tableau Velleda pour visualiser les problemes et imaginer les solutions (Tres utile pour la partie 3 et la partie 6 notamment)

+ Mise en commun du travail et entraide avec les autres etudiants lors des seances de TP, et aide des enseignants

+++

## Prise de recul

*Décrire en quelques phrases les difficultés rencontrées, ce que vous
avez appris à l'occasion du projet, le cas échéant comment vous vous y
prendriez si vous aviez à le refaire.*

+++

Difficultes:
+ Probleme de format handicapant (Nous ne sommes pas partis du principe que le max du tableau est la valeur max d'un pixel) qui nous a pousse a changer les tests (bcp de temps perdu) <-- (Accord d'un charge de TD/organisateur)
+ Problemes avec certains tests du projet (ex: seuillageDoubleIteratifTest avec des seuils > 255 / renormaliseTest qui n'etait pas entierement clair sur ce que la fonction devait faire (proportionnalite ou non)) qui nous a aussi fait perdre du temps
+ Problemes avec "TIN.cpp" 

Ce qu'on appris:
+ Etre rigoureux quand on code
+ Apprendre a deboguer et a tester petit a petit
+ Optimiser parfois le code

Ce qu'on aurait fait differemment:
+ Nous sommes assez satisfaits de notre methode de travail

+++

## Extraits de codes

+++

+ Partie 3:

+++ {"tags": []}

Fonction intensite: meilleurs resultats que dans correction: recherche du max dans tout le tableau qui nous donne une image avec moins d'interferences

+++

+ Partie 6:

+++ {"tags": []}

Fonction SuperPixel: resultats un peu meileurs et plus utiles: dans la correction, si on zoom, il manque des contours sur les bords de l'image, ce qui peut etre genant si on veut traiter l'image par la suite (ex: remplissage)

+++

+ Exemple de code optimise:

Optimisation du code dans la partie 1.5:

    for (int longue = 1; longue < img.size(); longue++) {  
        for (int large = 0; large < img[longue].size(); large++) {
            if (img[longue][large] == 0) {
                res[longue][large] = 1;
            } else if (img[longue][large] == 1) {
                res[longue][large] = 0; }
            }  
        }
        

    for (int longue = 1; longue < img.size(); longue++) {               
            for (int large = 0; large < img[longue].size(); large++) {
                res[longue][large] = 1 - img[longue][large];                 
            }                                                                
        }

```{code-cell} ipython3

```
