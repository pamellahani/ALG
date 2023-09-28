
typedef struct a *parc_t ;

/*
  definition des types sommet et pointeur de sommet
  un graphe est constitué d'une liste de sommets
*/

typedef struct s
{
  int        label ; // label du sommet
  parc_t     liste_arcs ; // arcs sortants du sommet
  struct s   *sommet_suivant ; // sommet suivant dans le graphe
  int        couleur ; // couleur du sommet

  int distance; // distance from the source node
  psommet_t predecesseur; // predecessor node in the shortest path
  int visite; // visited flag

} sommet_t, *psommet_t ;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortants d'un sommet sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre a une distance
*/

typedef struct a {
  
                  int         poids ; // poids de l arc
                  psommet_t   dest ;  // pointeur sommet destinataire
                  struct a *  arc_suivant ; // arc suivant
  
} arc_t, *parc_t ;

/*
  pgraphe_t: pointeur vers le premier sommet d'un graphe
*/

#define TAILLE 100 // matrice adjacency
struct graphe
{
  int taille;
  int mat[TAILLE][TAILLE]; 
};

typedef psommet_t pgraphe_t ;

// DEF CHEMIN

typedef struct c{
    psommet_t sommet_init;
    parc_t liste_arcs;
} chemin_t, *pchemin_t;


psommet_t chercher_sommet (pgraphe_t g, int label) ;

void ajouter_arc (psommet_t o, psommet_t d, int distance) ;

int nombre_arcs (pgraphe_t g) ;

int nombre_sommets (pgraphe_t g) ;

void lire_graphe (char * file_name, pgraphe_t *g) ;

void ecrire_graphe (psommet_t p) ;

void ecrire_graphe_colorie (psommet_t p) ;



int colorier_graphe (pgraphe_t g) ;

void afficher_graphe_profondeur (pgraphe_t g, int r) ;

void afficher_graphe_largeur (pgraphe_t g, int r) ;

int algo_dijkstra (pgraphe_t g, int r) ;



//Un chemin élémentaire est un chemin ne passant pas deux fois par un même sommet, c’est à dire un chemin dont tous les sommets sont distincts
int elementaire( pgraphe_t g , chemin_t c ); 

//Un chemin simple est un chemin ne passant pas deux fois par le même arc, c’est à dire un chemin dont tous les arcs sont distincts.
int simple ( pgraphe_t g , chemin_t c) ; 

//Un chemin est dit Eulérien si tous les arcs du graphe sont utilisés dans le chemin.
int eulerien ( pgraphe_t g , chemin_t c); 

//. Un chemin est dit Hamiltonien si tous les sommets du graphe sont utilisés dans le chemin.
int hamiltonien ( pgraphe_t g , chemin_t c); 

//Un graphe est dit Eulérien si il existe au moins un chemin qui soit Eulérien.
int graphe_eulerien(pgraphe_t g);

//Un graphe est dit Hamiltonien si il existe au moins un chemin qui soit Hamiltonien.
int graphe_hamiltonien(pgraphe_t g);

//La distance entre deux sommets x et y est la longueur du plus court chemin entre x et y.
int distance (pgraphe_t g, int x, int y ); 

//L’excentricité d’un sommet est sa distance maximale avec les autres sommets du graphe.
int excentricite (pgraphe_t g, int n); 

//Le diamètre d’un graphe est l’excentricité maximale de ses sommets.
int diametre (pgraphe_t g); 

