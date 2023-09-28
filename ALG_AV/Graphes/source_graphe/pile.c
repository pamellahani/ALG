#include <stdlib.h>
#include <stdio.h>
#include "pile.h"

ppile_t creer_pile ()
{
  ppile_t p = malloc(sizeof(pile_t));
  p->sommet = -1; 
  return p;
}

int detruire_pile (ppile_t p)
{
  free(p);
  return 0;
}  

int pile_vide (ppile_t p)
{
  if (p->sommet==-1) return 1;
  else return 0;
}

int pile_pleine (ppile_t p)
 {
  if (p->sommet==MAX_PILE_SIZE-1) return 1;
  else return 0;
} 

void* depiler (ppile_t p)
{
    void* n = p->Tab[p->sommet];
    p->sommet--;
    return n;
}

int empiler (ppile_t p, void* pn)
{
  if (p->sommet>=MAX_PILE_SIZE-1)
    return 1;
  else {
    p->sommet++;
    p->Tab[p->sommet]= pn;
    return 0;
  }
}
