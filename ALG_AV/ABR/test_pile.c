#include "abr.h"
#include "file.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    ppile_t stack = creer_pile();
    pnoeud_t node1 = (pnoeud_t)malloc(sizeof(noeud_t));
    node1->cle = 1;
    node1->fgauche = NULL;
    node1->fdroite = NULL;
    pnoeud_t node2 = (pnoeud_t)malloc(sizeof(noeud_t));
    node2->cle = 2;
    node2->fgauche = NULL;
    node2->fdroite = NULL;
    pnoeud_t node3 = (pnoeud_t)malloc(sizeof(noeud_t));
    node3->cle = 3;
    node3->fgauche = NULL;
    node3->fdroite = NULL;

    // push nodes onto stack
    empiler(stack, node1);
    empiler(stack, node2);
    empiler(stack, node3);

    // pop and print nodes from stack
    while (!pile_vide(stack)) {
        pnoeud_t temp = depiler(stack);
        printf("%d ", temp->cle);
    }
    detruire_pile(stack);
    return 0;
}
