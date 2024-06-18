programme sudoku c’est
 type tGrille = tableau[1..TAILLE, 1..TAILLE] de entier1;
 var grille1 : tGrille;
 numLigne, numColonne, valeur : entier;
début
    chargerGrille(grille1);
    tant que la grille n’est pas pleine2 faire
        afficherGrille(grille1);
        ecrireEcran("Indices de la case ? ");
        saisir(numLigne);
        saisir(numColonne);
        si (grille1[numLigne][numColonne]!=0)alors
            ecrireEcran("IMPOSSIBLE, la case n'est pas libre.");
        sinon
            ecrireEcran("Valeur à insérer ? ");
            saisir(valeur);
            si (possible(grille1, numLigne, numColonne, valeur)) alors
                grille1[numLigne][numColonne] = valeur;
        finsi
        finsi
    finfaire
    ecrireEcran("Grille pleine, fin de partie");
fin