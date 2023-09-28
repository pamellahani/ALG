/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graphe.h"
#include "file.h"
#include "fap.h"


psommet_t chercher_sommet (pgraphe_t g, int label)
{
  psommet_t s ;

  s = g ;

  while ((s!= NULL) && (s->label != label))
    {
      s = s->sommet_suivant ;
    }
  return s ;
}

parc_t existence_arc (parc_t l, psommet_t s)
{
  parc_t p = l ;

  while (p != NULL)
    {
      if (p->dest == s)
	return p ;
      p = p->arc_suivant ;
    }
  return p ;
  
}


void ajouter_arc (psommet_t o, psommet_t d, int distance)
{
  parc_t parc ;

  parc = (parc_t) malloc (sizeof(arc_t)) ;

  if (existence_arc (o->liste_arcs, d) != NULL)
    {
      fprintf(stderr, "ajout d'un arc deja existant\n") ;
      exit (-1) ;
    }
  
  parc->poids = distance ;
  parc->dest = d ;
  parc->arc_suivant = o->liste_arcs ;
  o->liste_arcs = parc ;
  return ;
}



// ===================================================================

int nombre_sommets (pgraphe_t g)
{
  psommet_t p = g ;
  int nb = 0 ;

  while (p != NULL)
    {
      nb = nb + 1 ;
      p = p->sommet_suivant ;
    }

  return nb ;
}

int nombre_arcs (pgraphe_t g)
{

  psommet_t p = g ;
  int nb_arcs = 0 ;

  while (p != NULL)
    {
      parc_t l = p->liste_arcs ;

      while (l != NULL)
	{
          nb_arcs = nb_arcs + 1 ;
	  l = l->arc_suivant ;
	}
      
      p = p->sommet_suivant ;
    }
  return nb_arcs ;
}

void init_couleur_sommet (pgraphe_t g)
{
  psommet_t p = g ;

  while (p != NULL)
    {
      p->couleur = 0 ; // couleur indefinie
      p = p->sommet_suivant ; // passer au sommet suivant dans le graphe
    }
  
  return ;
}

int colorier_graphe (pgraphe_t g)
{
  /*
    coloriage du graphe g
    
    datasets
    graphe data/gr_planning
    graphe data/gr_sched1
    graphe data/gr_sched2
  */

  psommet_t p = g ;
  parc_t a ;
  int couleur ;
  int max_couleur = INT_MIN ; // -INFINI
  
  int change ;

  init_couleur_sommet (g) ;
  
  while (p != NULL)
    {
      couleur = 1 ; // 1 est la premiere couleur

      // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

      // Choix de la couleur pour le sommet p
      
      do
	{
	  a = p->liste_arcs ;
	  change = 0 ;
      
	  while (a != NULL)
	    {
	      if (a->dest->couleur == couleur)
		{
		  couleur = couleur + 1 ;
		  change = 1 ;
		} 
	      a = a->arc_suivant ; 
	    }

	} while (change == 1) ;

      // couleur du sommet est differente des couleurs de tous les voisins
      
      p->couleur = couleur ;
      if (couleur > max_couleur)
	max_couleur = couleur ;

      p = p->sommet_suivant ;
    }
  
  return max_couleur ;
}

void afficher_graphe_largeur (pgraphe_t g, int r)
{
    // Vérifier que le sommet de départ existe
    psommet_t s = chercher_sommet(g, r);
    if (s == NULL) {
        printf("Sommet de départ avec le label %d non trouvé\n", r);
        return;
    }
    // Initialiser la file pour stocker les sommets à visiter
    pfile_t file = creer_file();
    enfiler(file, s);
    s->couleur = 1; // marquer le sommet de départ comme visité
    
    // Parcours en largeur
    while (!file_vide(file)) {
        psommet_t sommet = (psommet_t) defiler(file);
        printf("%d ", sommet->label);
        // Parcourir tous les arcs sortants du sommet
        parc_t arc = sommet->liste_arcs;
        while (arc != NULL) {
            psommet_t dest = arc->dest;
            if (dest->couleur == 0) {
                enfiler(file, dest);
                dest->couleur = 1; // marquer le sommet comme visité
            }
            arc = arc->arc_suivant;
        }
    }
    // Réinitialiser les couleurs des sommets
    psommet_t p = g;
    while (p != NULL) {
        p->couleur = 0;
        p = p->sommet_suivant;
    }
    // Détruire la file
    detruire_file(file);
}

/*
Elle marque le sommet courant comme visité, affiche son label, puis parcourt tous 
les arcs sortants de ce sommet et récursivement visite les sommets connectés qui n'ont 
pas encore été visités.
*/
void parcours_profondeur(psommet_t s, int* visite, int r) {
  visite[s->label] = 1;
  printf("%d ", s->label);

  parc_t arc = s->liste_arcs;
  while (arc != NULL) {
    psommet_t dest = arc->dest;
    if (!visite[dest->label]) {
      parcours_profondeur(dest, visite, r);
    }
    arc = arc->arc_suivant;
  }
}

void afficher_graphe_profondeur(pgraphe_t g, int r) {
  int visite[nombre_sommets(g)];
  for (int i = 0; i < nombre_sommets(g); i++) {
    visite[i] = 0;
  }
  parcours_profondeur(chercher_sommet(g, r), visite, r);
  printf("\n");
}

int algo_dijkstra (pgraphe_t g, int r)
{
  int n = 0; // number of vertices
  pgraphe_t s = g;

  while (s != NULL) {
    n++;
    s->couleur = 0;
    s->distance = INT_MAX;
    s->predecesseur = NULL;
    s = s->sommet_suivant;
  }

  fap file = creer_fap_vide();
  g[r].distance = 0;
  file = inserer(file, &g[r], 0);

  while (!est_fap_vide(file)) {
      psommet_t u = (psommet_t)file->element;
      file = extraire(file, NULL, NULL);

      if (u->couleur == 0) {
          u->couleur = 1;

          parc_t p = u->liste_arcs;
          while (p != NULL) {
              psommet_t v = p->dest;
              if (v->couleur == 0) {
                  int d = u->distance + p->poids;
                  if (d < v->distance) {
                      v->distance = d;
                      v->predecesseur = u;
                      file = inserer(file, v, d);
                  }
              }
              p = p->arc_suivant;
          }
      }
  }

  detruire_fap(file);
  return 0 ;
}

// ======================================================================


int degre_sortant_sommet (pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs sortants 
    du sommet n dans le graphe g
  */ 

    int count = 0;
    parc_t p = s->liste_arcs;
    while (p != NULL) {
        count++;
        p = p->arc_suivant;
    }
    return count;
}

int degre_entrant_sommet (pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs entrants 
    dans le noeud n dans le graphe g
  */ 

  int count = 0;
  psommet_t sommet = g;
  while (sommet != NULL) {
      parc_t p = sommet->liste_arcs;
      while (p != NULL) {
          if (p->dest == s) {
            count++;
          }
          p = p->arc_suivant;
      }
      sommet = sommet->sommet_suivant;
   }
  return count;

}

int degre_maximal_graphe (pgraphe_t g)
{
  /*
    Max des degres des sommets du graphe g
  */

    int max = 0;
    psommet_t s = g;
    while (s != NULL) {
        int degre = degre_sortant_sommet(g, s);
        if (degre > max) {
            max = degre;
        }
        s = s->sommet_suivant;
    }
    return max;
}


int degre_minimal_graphe (pgraphe_t g)
{
  /*
    Min des degres des sommets du graphe g
  */

   int min = INT_MAX;
    psommet_t s = g;
    while (s != NULL) {
        int degre = degre_sortant_sommet(g, s);
        if (degre < min) {
            min = degre;
        }
        s = s->sommet_suivant;
    }
    return min;
}


int independant (pgraphe_t g)
{
  /* Les aretes du graphe n'ont pas de sommet en commun */

   psommet_t s1 = g;
    while (s1 != NULL) {
        psommet_t s2 = s1->sommet_suivant;
        while (s2 != NULL) {
            parc_t p = s1->liste_arcs;
            while (p != NULL) {
                if (p->dest == s2) {
                    return 0;
                }
                p = p->arc_suivant;
            }
            s2 = s2->sommet_suivant;
        }
        s1 = s1->sommet_suivant;
    }
    return 1;
}



int complet (pgraphe_t g)
{
  /* Toutes les paires de sommet du graphe sont jointes par un arc */

    psommet_t s1 = g;
    while (s1 != NULL) {
        psommet_t s2 = s1->sommet_suivant;
        while (s2 != NULL) {
            parc_t p = s1->liste_arcs;
            int arete_trouvee = 0;
            while (p != NULL) {
                if (p->dest == s2) {
                    arete_trouvee = 1;
                    break;
                }
                p = p->arc_suivant;
            }
            if (!arete_trouvee) {
                return 0;
            }
            s2 = s2->sommet_suivant;
        }
        s1 = s1->sommet_suivant;
    }
    return 1;
}

int regulier (pgraphe_t g)
{
  /* 
     graphe regulier: tous les sommets ont le meme degre
     g est le ponteur vers le premier sommet du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
  */
    int degre_reference = degre_sortant_sommet(g, g);
    psommet_t s = g;
    while (s != NULL) {
        int degre = degre_sortant_sommet(g, s);
        if (degre != degre_reference) {
            return 0;
        }
        s = psommet_suivant(g, s);
      }
      return 1;
}


//============================== FCT SUR CHEMIN (ELEM/SIMPLE/LONGUEUR) ==============================

int elementaire( pgraphe_t g , chemin_t c ){
 // Vérifier que les sommets de la liste des arcs du chemin sont distincts
    psommet_t sommet_precedent = c.sommet_init;
    parc_t p = c.liste_arcs;
    while (p != NULL) {
        psommet_t sommet_suivant = p->dest;
        if (sommet_suivant == sommet_precedent) {
            return 0;
        }
        sommet_precedent = sommet_suivant;
        p = p->arc_suivant;
    }
    return 1;
}

int simple (pgraphe_t g, chemin_t c){
  psommet_t s= c.sommet_init; 
  while (c.liste_arcs != NULL){
    psommet_t s_suiv = c.liste_arcs->dest; 
    if (s_suiv == s){
      // sommet suivant est identique aau sommet courant donc pas simple
      return 0; 
    }
    parc_t p = c.liste_arcs->arc_suivant; 
    while (p!=NULL)
    {
      if (p->dest == s_suiv) return 0; 
      p =p->arc_suivant; 
    }
    s=s_suiv; 
    c.liste_arcs=c.liste_arcs->arc_suivant; 
  }
  return 1; 
}

int eulerien (pgraphe_t g, chemin_t c){ 
  parc_t p = g->liste_arcs; 
  while (p!=NULL){
    psommet_t src = p; 
    psommet_t dest=p->dest; 
    
    // check if the arc is present in chemin 
    parc_t parcours = c.liste_arcs; 
    int trouve = 0; 
    while (parcours != NULL){
      if (parcours && parcours->dest == dest){
        trouve = 1; 
        return; 
      }
      parcours = parcours->arc_suivant;

    }
    // Si l'arc n'est pas présent dans le chemin, retourner 0
        if (!trouve) {
            return 0;
        }
        
        p = p->arc_suivant;
  }
}

int hamiltonien (pgraphe_t g, chemin_t c){
  int nb_sommets_chemin =1; //le sommet de depart du chemin c->sommet_init
  init_couleur_sommet(g);
  c.sommet_init->couleur =1 ; // on marque le sommet visite par le chemin c->sommet_init
  
  for(parc_t arc_courant = c.liste_arcs; arc_courant != NULL ; arc_courant = arc_courant->arc_suivant) {
    if (arc_courant->dest->couleur==0) { // on marque chaque sommet
      nb_sommets_chemin++;
      arc_courant->dest->couleur=1;
    }
    else if (arc_courant->dest->couleur==1) { //on a déjà vu ce sommet avant = pas hamiltonien
      return 0;
    }
  }
  // si chaque sommet du chemin n'est vu qu'une fois et 
  //qu'on en a vu autant qu'il y a de sommets dans le graphe on renvoit 1.
  return nb_sommets_chemin==nombre_sommets(g);
}



// un graphe est eurelien ssi le graphe est connexe et les degres des sommets sont pairs 
int graphe_eurelien (pgraphe_t g){
  psommet_t s = g; 
  while (s!= NULL){
    if (degre_sortant_sommet(g,s)%2 != 0){
      return 0; //si un sommet a un degre impair, le graphe n'est pas eurelien
    }
    s = s->sommet_suivant; 
  } 
  return 1; 
}

// un graphe est hamiltonien ssi il a n sommets (n>=3)et chaque sommet a un degre d'au moins n/2 
// theoreme de Dirac 
int graphe_hamiltonien(pgraphe_t g){
  int n = nombre_sommets(g); 
  psommet_t s =g; 
  while(s!=NULL){
    /*
    Le degré entrant d'un sommet est le nombre d'arcs qui arrivent à ce sommet, tandis que le degré
    sortant est le nombre d'arcs qui partent de ce sommet. En sommant ces deux quantités, on obtient
    le degré total du sommet dans le graphe orienté.
    */
    int degre = degre_entrant_sommet(g,s)+degre_sortant_sommet(g,s); 
    if (degre < n/2){
      return 0; 
    }
    s = s->sommet_suivant; 
  }
  return 1; 
}

// utilisation de l'algoruthme de Dijkstra 
int distance(pgraphe_t g, int x, int y)
{
  // Initialisation des sommets
  pgraphe_t s = g;
  while (s != NULL) {
      s->couleur = 0;
      s->distance = INT_MAX;
      s->predecesseur = NULL;
      s = s->sommet_suivant;
  }

  // Initialisation de la file de priorité
  fap file = creer_fap_vide();
  g[x].distance = 0;
  file = inserer(file, &g[x], 0);

  // Application de l'algorithme de Dijkstra
  while (!est_fap_vide(file)) {
      psommet_t u = (psommet_t)file->element;
      file = extraire(file, NULL, NULL);

      if (u->couleur == 0) {
          u->couleur = 1;

          if (u == &g[y]) {
              detruire_fap(file);
              return u->distance;
          }

          parc_t p = u->liste_arcs;
          while (p != NULL) {
              psommet_t v = p->dest;
              if (v->couleur == 0) {
                  int d = u->distance + p->poids;
                  if (d < v->distance) {
                      v->distance = d;
                      v->predecesseur = u;
                      file = inserer(file, v, d);
                  }
              }
              p = p->arc_suivant;
          }
      }
  }

  detruire_fap(file);
  return -1; // Pas de chemin entre les sommets x et y
}

int excentricite (pgraphe_t g, int n){ 
  // n = distance maximale obtenue 
  algo_dijkstra(g, n);
  int max_dist = 0;
  psommet_t s = g;
  while (s != NULL) {
      if (s->distance > max_dist) {
          max_dist = s->distance;
      }
      s = s->sommet_suivant;
  }
  return max_dist;
}

int diametre(pgraphe_t g) {
    int max_ecc = 0;
    psommet_t s = g;
    while (s != NULL) {
        int ecc = excentricite(g, s->label);
        if (ecc > max_ecc) {
            max_ecc = ecc;
        }
        s = s->sommet_suivant;
    }
    return max_ecc;
}
/*
  placer les fonctions de l'examen 2017 juste apres
*/
