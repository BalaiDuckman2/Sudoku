/**
 * \file sudoku.c
 * \brief Programme permettant de jouer au jeu de Sudoku.
 * \author Corre
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/**
 *\def TAILLE_FICHIER
 *\brief Taille du nom de fichier
 * 
 */
#define TAILLE_FICHIER = 30; 

/**
 * \def N
 * \brief Taille d'une sous-grille 
 * 
 */
#define N = 3; 

/**
 * \def DEBUT
 * \brief Début de l'indice 
 * 
 */
#define DEBUT = 0; 

/**
 * \def TAILLE
 * \brief Taille de la grille 
 * 
 */
#define TAILLE 9 

/**
 * \typedef tGrille
 * \brief Type représentant la grille de Sudoku.
 */
typedef int tGrille[TAILLE][TAILLE];

/**
 * \fn void chargerGrille(tGrille grille)
 * \brief Charge une grille de Sudoku à partir d'un fichier binaire.
 * \param grille La grille de Sudoku à remplir.
 */
void chargerGrille(tGrille grille);

/**
 * \fn void affichegrille(tGrille grille)
 * \brief Affiche la grille de Sudoku.
 * \param grille La grille de Sudoku à afficher.
 */
void affichegrille(tGrille grille);

/**
 * \fn void saisir(int *valeur)
 * \brief Saisit une valeur entière depuis l'entrée standard.
 * \param valeur Pointeur vers la variable où stocker la valeur saisie.
 */
void saisir(int *valeur);

/**
 * \fn bool possible(tGrille grille, int ligne, int colonne, int valeur)
 * \brief Vérifie si une valeur peut être placée dans une case donnée de la grille.
 * \param grille La grille de Sudoku.
 * \param ligne L'indice de la ligne.
 * \param colonne L'indice de la colonne.
 * \param valeur La valeur à vérifier.
 * \return True si la valeur peut être placée, False sinon.
 */
bool possible(tGrille grille, int ligne, int colonne, int valeur);

/**
 * \fn bool grilleComplete(tGrille grille)
 * \brief Vérifie si la grille de Sudoku est complète.
 * \param grille La grille de Sudoku.
 * \return True si la grille est complète, False sinon.
 */
bool grilleComplete(tGrille grille);

/**
 * \fn int main()
 * \brief Fonction principale du programme.
 * \return EXIT_SUCCESS en cas de succès.
 */
int main() {
    tGrille grille1;
    int numLigne, numColonne, valeur;

    chargerGrille(grille1);
    while (!grilleComplete(grille1)) {
        affichegrille(grille1);
        printf("Choix de la colonne(1-9):\n");
        saisir(&numColonne);
        printf("Choix de la ligne(1-9):\n");
        saisir(&numLigne);
        if (grille1[numLigne - 1][numColonne - 1] != 0) {
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        } else {
            printf("Valeur à insérer(1-9):\n");
            saisir(&valeur);
            if (possible(grille1, numLigne, numColonne, valeur)) {
                grille1[numLigne - 1][numColonne - 1] = valeur;
            } else {
                printf("valeur déjà mise\n");
            }
        }
    }
    printf("Grille pleine, fin de partie");
    return EXIT_SUCCESS;
}

void chargerGrille(tGrille grille){
   char nomFichier[TAILLE_FICHIER];
   FILE * f;
   printf("Nom du fichier : ");
   scanf("%s", nomFichier);
   f = fopen(nomFichier, "rb");
   if (f==NULL)
   {
      printf("\n ERREUR sur le fichier %s\n", nomFichier);
   } 
   else 
   {
      fread(grille, sizeof(int), TAILLE*TAILLE, f);
   }
   fclose(f);
}   

void affichegrille(tGrille grille){
   printf("    1  2  3   4  5  6   7  8  9\n");
   printf("  +---------+---------+---------+");

   for(int ligne=DEBUT; ligne<TAILLE; ligne++){
      printf("\n%d |",ligne+1);
      for(int collone=DEBUT; collone <TAILLE;collone++){
         if(grille[ligne][collone]==0){
            printf(" . ");
         }else{
            printf(" %d ",grille[ligne][collone]);
         }
         if(collone==2 || collone ==5){
            printf("|");
         }   
      }
      printf("|");
      if(ligne==2 || ligne ==5){
            printf("\n  +---------+---------+---------+");
         }

   }
   printf("\n  +---------+---------+---------+\n");

}

void saisir(int *valeur){
   char ch[10];
   float x;
   int y;
   bool fin=false;
   while(fin==false){
      scanf("%s", ch);
      if (sscanf(ch, "%f", &x)!=0)
      {
         if(x<1 || x>10){
            printf("saisir un chiffre entre 1 et 9 :\n");
         }
         else{
            y=x;
            if(x==y)
            {
               *valeur = x;
               fin=true;
            }
            else{
               printf("saisir un chiffre entre 1 et 9 sans virgule :\n");
            }
         }
      }
      else{
         printf("erreur ce n'est pas un chiffre \n");
      }
   }
}

bool possible(tGrille grille,int ligne,int colonne,int valeur){
   bool fin = true;
   int i;
   int j;
   int recupi;
   int recupj;
   bool finboucle = false;

   i=DEBUT;
   while(fin ==true && i < TAILLE){
      
      if(valeur == grille[ligne-1][i] || valeur == grille[i][colonne-1]){
         
         fin = false;
      }
      i++;
   }
   if(fin==true)
   {
      i=3;
      while (finboucle==false && i<=9)
      {
         j = 3;
         while (finboucle==false && j<=8)
         {
            if (ligne < i && colonne < j)
            {
               recupi = i;
               while(finboucle == false && i >= recupi-2)
               {
                  recupj = j;
                  while (finboucle==false && j >= recupj-2)
                  {
                     if (valeur==grille[i-1][j-1])
                     {
                        fin = false;
                        finboucle =true;
                     }
                        j=j-1;
                     }
                     j = recupj;
                     i=i-1;
                  }
               
               finboucle = true;
            }
            j=j+3;
         }
         i=i+3;
      }

      
   }
   return fin;
}

bool grilleComplete(tGrille grille){
   bool fin = true;
   int ligne=DEBUT;
   int collone=DEBUT;
   while(ligne<=TAILLE && fin == true)
   {
      while(collone<=TAILLE && fin == true)
      {
         if(grille[ligne][collone]==0)
         {
            fin = false;
         }
         collone++;
      }
      ligne++;
      collone=DEBUT;
   }
   return fin;
}
