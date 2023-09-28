#include <stdlib.h>
#include "abr.h"
#include "pile.h"

ppile_t creer_pile ()
{
    ppile_t p = (ppile_t) malloc(sizeof(pile_t));
    p->sommet = -1;
    return p;
}

int detruire_pile (ppile_t p)
{
  free(p); 
  return 0 ;
}  

int pile_vide (ppile_t p)
{
    if(p->sommet == -1)
        return 1;
    else
        return 0;
}

int pile_pleine (ppile_t p)
 {
    if(p->sommet == MAX_PILE_SIZE - 1)
        return 1;
    else
        return 0;
} 

pnoeud_t depiler (ppile_t p)
{
    if(pile_vide(p)==1)
        return NULL;
    else
        return p->Tab[p->sommet--];

}

int empiler (ppile_t p, pnoeud_t pn)
  {
    if(pile_pleine(p)==1)
        return -1;
    else
    {
        p->sommet++;
        p->Tab[p->sommet] = pn;
        return 0;
    }

}
