#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"
#include "file.h"


#define max(a,b) ((a)>(b)?(a):(b))


int feuille (Arbre_t a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre_t ajouter_noeud (Arbre_t a, Arbre_t n)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;
  
}  

Arbre_t rechercher_cle_arbre (Arbre_t a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre_t ajouter_cle (Arbre_t a, int cle)
{
  Arbre_t n ;
  Arbre_t ptrouve ;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre_t) malloc (sizeof(noeud_t)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}


Arbre_t lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre_t a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

void afficher_arbre (Arbre_t a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
  int i ;
  
  if (a != NULL)
      {
	afficher_arbre (a->fdroite,niveau+1) ;
	
	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d (%d)\n\n", a->cle, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}


int hauteur_arbre_r (Arbre_t a)
{
  if (feuille(a)){
    return 0;
  }
  else{
    return 1 + hauteur_arbre_r(a->fgauche) + hauteur_arbre_r(a->fdroite);
  }
}

int hauteur_arbre_nr (Arbre_t a)
{
  int hauteur = 0;
  if (a == NULL) return 0;

  pfile_t f = creer_file();
  enfiler(f, a);
  enfiler(f, NULL);

  while (!file_vide(f))
  {
    Arbre_t node = defiler(f);
    if (node == NULL)
    {
      hauteur++;
      if (!file_vide(f)) enfiler(f, NULL);
    }
    else
    {
      if (node->fgauche) enfiler(f, node->fgauche);
      if (node->fdroite) enfiler(f, node->fdroite);
    }
  }
  detruire_file(f);
  return hauteur;
}



void parcourir_arbre_largeur (Arbre_t a)
{
  pfile_t file = creer_file();
  enfiler(file, a);
  while(!file_vide(file))
  {
    pnoeud_t temp = defiler(file);
    printf("%d ", temp->cle);
    if(temp->fgauche)
      enfiler(file, temp->fgauche);
    if(temp->fdroite)
      enfiler(file, temp->fdroite);
  }
  detruire_file(file);
  return ;
}

void afficher_nombre_noeuds_par_niveau (Arbre_t a) {

  if (a == NULL) return;
  pfile_t f = creer_file();
  enfiler(f, a);
  int niveau = 1;
  int nb_noeuds_niveau = 1;
  int nb_noeuds_nouveau_niveau = 0;

  while (!file_vide(f)) {
    pnoeud_t noeud = defiler(f);
    nb_noeuds_niveau--;
    printf("%d ", noeud->cle);

    if (noeud->fgauche != NULL) {
      enfiler(f, noeud->fgauche);
      nb_noeuds_nouveau_niveau++;
    }

    if (noeud->fdroite != NULL) {
      enfiler(f, noeud->fdroite);
      nb_noeuds_nouveau_niveau++;
    }

    if (nb_noeuds_niveau == 0) {
      printf("\nNiveau %d: %d noeuds\n", niveau, nb_noeuds_nouveau_niveau);
      nb_noeuds_niveau = nb_noeuds_nouveau_niveau;
      nb_noeuds_nouveau_niveau = 0;
      niveau++;
    }
  }
  detruire_file(f);
}


int nombre_cles_arbre_r (Arbre_t a) {
  if (a == NULL) return 0;
  return 1 + nombre_cles_arbre_r(a->fgauche) + nombre_cles_arbre_r(a->fdroite);
}

int nombre_cles_arbre_nr (Arbre_t a) {

  if (a == NULL) return 0;
  pfile_t f = creer_file();
  enfiler(f, a);
  int nb_cles = 0;

  while (!file_vide(f)) {
    pnoeud_t noeud = defiler(f);
    nb_cles++;
    if (noeud->fgauche != NULL) {
      enfiler(f, noeud->fgauche);
    }
    if (noeud->fdroite != NULL) {
      enfiler(f, noeud->fdroite);
    }
  }
  detruire_file(f);
  return nb_cles;
}

int trouver_cle_min (Arbre_t a) {
  while (a->fgauche != NULL) {
    a = a->fgauche;
  }
  return a->cle;
}

void imprimer_liste_cle_triee_r(Arbre_t a)
{
    if(a != NULL)
    {
      imprimer_liste_cle_triee_r(a->fgauche);
      printf("%d ", a->cle);
      imprimer_liste_cle_triee_r(a->fdroite);
    }
}

void imprimer_liste_cle_triee_nr(Arbre_t a)
{
    if (a == NULL)
        return;

    ppile_t stack = creer_pile();
    Arbre_t current = a;

    while (current != NULL || !pile_vide(stack))
    {
        while (current != NULL)
        {
            empiler(stack, current);
            current = current->fgauche;
        }

        current = depiler(stack);
        printf("%d ", current->cle);
        current = current->fdroite;
    }

    detruire_pile(stack);
}



int arbre_plein (Arbre_t a) {
  if (a == NULL) return 1;
  if (a->fgauche == NULL && a->fdroite != NULL) return 0;
  if (a->fgauche != NULL && a->fdroite == NULL) return 0;
  return arbre_plein(a->fgauche) && arbre_plein(a->fdroite);
}

int arbre_parfait (Arbre_t a) {

  int height = hauteur_arbre_r(a);
  int n = nombre_cles_arbre_r(a);
  return (1 << height) - 1 == n;

}

Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur)
{
  if (a == NULL) {
    return NULL;
  }
  if (a->cle > valeur) {
    Arbre_t node = rechercher_cle_sup_arbre(a->fgauche, valeur);
    return node ? node : a;    // if node != NULL return node else return a
  }
  return rechercher_cle_sup_arbre(a->fdroite, valeur);

}


Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur) {

  if (a == NULL) {
    return NULL;
  }
  if (a->cle < valeur) {
    Arbre_t node = rechercher_cle_inf_arbre(a->fdroite, valeur);
    return node ? node : a;
  }
  return rechercher_cle_inf_arbre(a->fgauche, valeur);
  
}


Arbre_t detruire_cle_arbre (Arbre_t a, int cle) {
  if (a == NULL) {
    return NULL;
  }
  if (a->cle == cle) {
    if (a->fgauche == NULL) {
      return a->fdroite;
    }
    if (a->fdroite == NULL) {
      return a->fgauche;
    }
    Arbre_t next = rechercher_cle_inf_arbre(a->fdroite, cle);
    a->cle = next->cle;
    a->fdroite = detruire_cle_arbre(a->fdroite, next->cle);
    return a;
  }
  if (cle < a->cle) {
    a->fgauche = detruire_cle_arbre(a->fgauche, cle);
  } else {
    a->fdroite = detruire_cle_arbre(a->fdroite, cle);
  }
  return a;
}



Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2) {
  if (!a1 || !a2) return NULL;
  Arbre_t a = malloc(sizeof(noeud_t));
  a->cle = a1->cle;

  if (a2->cle == a1->cle) {
    a->fgauche = intersection_deux_arbres(a1->fgauche, a2->fgauche);
    a->fdroite = intersection_deux_arbres(a1->fdroite, a2->fdroite);
  } else if (a2->cle < a1->cle) {
    a->fgauche = intersection_deux_arbres(a1, a2->fgauche);
  } else {
    a->fdroite = intersection_deux_arbres(a1, a2->fdroite);
  }
  return a;
}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2) {
  if (!a1) return a2;
  if (!a2) return a1;
  Arbre_t a = malloc(sizeof(noeud_t));
  a->cle = a1->cle;
  
  if (a2->cle == a1->cle) {
    a->fgauche = union_deux_arbres(a1->fgauche, a2->fgauche);
    a->fdroite = union_deux_arbres(a1->fdroite, a2->fdroite);
  } else if (a2->cle < a1->cle) {
    a->fgauche = union_deux_arbres(a1->fgauche, a2);
    a->fdroite = union_deux_arbres(a1->fdroite, a2);
  } else {
    a->fgauche = union_deux_arbres(a1, a2->fgauche);
    a->fdroite = union_deux_arbres(a1, a2->fdroite);
  }
  return a;
}


