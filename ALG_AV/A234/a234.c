#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))


int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;
  
  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
} 

int NombreCles (Arbre234 a)
{
  /*
     Retourne le nombre de cles presentes dans l'arbre a
  */
  if (a == NULL) {return 0;}
  else{
    int comp = 0;
    for (int i = 0; i <a->t-1;i++){
      comp++;
    }
    for (int i = 0; i<a->t;i++){
      comp+=NombreCles(a->fils[i]);
    }
    return comp;
  }
  
}

//le max de l'arbre se trouve le plus a droite 
int CleMax (Arbre234 a)
{
  if (a==NULL){
    return -1;
  }
  else if (a->t == 0){
    return a->cles[a->t-1]; 
  }
  else{
    return CleMax(a->fils[a->t]);
  }
}

//le min de l'arbre se trouve le plus a gauche 
int CleMin (Arbre234 a)
{
   if (a==NULL){
    return -1;
  }
  else if (a->t == 0){
    return a->cles[0]; 
  }
  else{
    return CleMin(a->fils[0]);
  }
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  /*
     rechercher si la cle a est presente dans
     l'arbre a. Si oui, retourne le noeud ou se trouve la cle.
  */
  Arbre234 actuel = a; 
  while (actuel !=NULL){
    int i = 0 ; 
    while (i<actuel->t-1 && cle >actuel->cles[i]){ //parcours de l''arbre jusqu'a trouver la cle ou une feuillle (t=0)
      i++; 
    }
    if (cle == actuel->cles[i]){
      return actuel; 
    }
    else if (actuel->t == 0){ //cle n'est pas presente dans l'arbre
      return NULL; 
    }
    else{
      actuel = actuel->fils[i];
    }
  }
  return NULL;
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  /* 
     calculer le nombre de feuilles, de 2-noeuds, 3-noeuds,et 4-noeuds
  */
  Arbre234 courant = a; 
  while (courant!=NULL){
    if (courant->t == 0){
      (*feuilles)++;
    }
    else if (courant->t == 2){
      (*noeud2)++; 
    }
    else if (courant->t == 3 ){
      (*noeud3)++;
    }
    else if (courant->t == 4 ){
      *(noeud4)++;
    }
    for (int i =0 ;i< courant->t; i++){
      AnalyseStructureArbre(courant->fils[i],feuilles, noeud2,noeud3,noeud4); 
    }
    courant = courant->fils[courant->t]; 
  }
}

Arbre234 noeud_max (Arbre234 a)
{
  if (a == NULL){return NULL;}
  Arbre234 actuel = a; 
  while (actuel->t!=0){
    actuel = actuel->fils[actuel->t];
  }
  Arbre234 max = actuel; 
  int sommeMAX = 0 ; 
  while(actuel!=NULL){
    int somme = 0; 
    for (int i = 0 ; i < actuel->t-1; i++){
      somme += actuel->cles[i]; 
    }
    if (somme>sommeMAX){
      sommeMAX = somme; 
      max = actuel;
    }
    actuel = actuel->fils[actuel->t]; 
  }
  return max;
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /* 
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
     
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}




int main (int argc, char **argv)
{
  Arbre234 a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;

  printf ("==== Afficher arbre ====\n") ;
  
  afficher_arbre (a, 0) ;

}
