#include <stdlib.h>
#include <stdio.h> 
#include "abr.h"
#include "file.h"

pfile_t creer_file()
{
  pfile_t f = (pfile_t)malloc(sizeof(pfile_t));
  f->tete = 0;
  f->queue = 0;
  return f;
}

int detruire_file(pfile_t f)
{
  free(f);
  return 0;
}

int file_vide(pfile_t f)
{
  if (f->tete == f->queue) // tete = queue => file vide
    return 1;                                    // file vide
  else
    return 0; // file non vide
}

int file_pleine(pfile_t f)
{
    if(f->queue - f->tete +1 == MAX_FILE_SIZE)
        return 1; //file pleine 
    else
        return 0;
}

pnoeud_t defiler(pfile_t f)
{
  if (file_vide(f)==1)
    return NULL;
  else
  {
    pnoeud_t temp = f->Tab[f->tete];
    f->tete = (f->tete + 1) ;
    return temp;
  }
}

int enfiler(pfile_t f, pnoeud_t p)
{
    if(file_pleine(f)==1)
        return -1;
    else
    {
        f->Tab[f->queue] = p; 
        f->queue = f->queue + 1;
        //printf("%d ",f->Tab[f->queue]->cle); 
        return 0;
    }
}
