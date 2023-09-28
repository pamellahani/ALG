#include <stdlib.h>
#include <stdio.h>
#include "file.h"

//Precondition : ts les elements de la file sont init a nul.

pfile_t creer_file ()
{
  pfile_t f = malloc(sizeof(file_t));
  for(int i=0; i<MAX_FILE_SIZE; i++) {
    f->Tab[i]=NULL;
  }
  f->tete = 0; 
  f->queue = 0;
  return f;
}

int detruire_file (pfile_t f)
{
  free(f); 
  return 0;
}


int file_vide (pfile_t f)
{
  if (f->tete==f->queue && f->Tab[f->tete]==NULL) return 1;
  else return 0;
}

int file_pleine (pfile_t f)
  {
  if (f->tete==f->queue && f->Tab[f->tete]!=NULL) return 1;
  else return 0;
}

void* defiler (pfile_t f)
  {
  if (file_vide(f)==1)
      return NULL;
  else {
    void* n = f->Tab[f->tete];
    f->Tab[f->tete] = NULL;
    if (f->tete<MAX_FILE_SIZE) {
      f->tete++;
      if (f->tete>=MAX_FILE_SIZE)
        f->tete=0;
      return n;
    }
    return NULL;
  }
}

int enfiler (pfile_t f, void* p)
{
  if (file_pleine(f)==1)
      return 1;
  else {
    if (f->queue<MAX_FILE_SIZE) {
      f->queue++;
      f->Tab[f->queue-1]= p;
      if (f->queue>=MAX_FILE_SIZE)
        f->queue=0;
     return 0;
    }
    return 1;
  }
}

