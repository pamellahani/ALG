#include "abr.h"
#include "file.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    pfile_t file = creer_file();
    pnoeud_t root = (pnoeud_t)malloc(sizeof(pnoeud_t));
    root->cle = 10;
    root->fgauche = NULL;
    root->fdroite = NULL;
    enfiler(file, root);
    printf ("seg fault not in enfiler\n"); 
    while (!file_vide(file))
    {
        printf ("seg fault not in file_vide \n"); 
        pnoeud_t temp = defiler(file); 
        printf ("seg fault not in defiler\n"); 
        printf("%d ", temp->cle);
    }
    printf ("seg fault not here\n"); 
    detruire_file(file);
    printf ("seg fault not here\n"); 
    return 0;
}