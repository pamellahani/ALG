#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    AVL a = nouveau_noeud(NULL, 4, NULL);
	printf("Arbre a : hauteur=%d\n", hauteur(a));
	afficher_arbre(a, 0);

	AVL b = nouveau_noeud(a, 6, NULL);
	printf("Arbre b : hauteur=%d\n", hauteur(b));
	afficher_arbre(b, 0);

	AVL c = nouveau_noeud(b, 8, nouveau_noeud(NULL, 9, NULL));
	printf("Arbre c : hauteur=%d\n", hauteur(c));
	afficher_arbre(c, 0);

	AVL d = nouveau_noeud(nouveau_noeud(NULL, 1, NULL), 10, nouveau_noeud(nouveau_noeud(NULL, 12, NULL), 14, nouveau_noeud(nouveau_noeud(NULL, 16, NULL), 18, nouveau_noeud(NULL, 20, NULL))));
	printf("Arbre d : hauteur=%d\n", hauteur(d));
	afficher_arbre(d, 0);

	printf("Arbre e : rotation a gauche de d :\n");
	AVL e = rotation_gauche(d);
	afficher_arbre(e, 0);

	AVL f = nouveau_noeud(nouveau_noeud(nouveau_noeud(nouveau_noeud(NULL, 1, NULL), 7, nouveau_noeud(NULL, 8, NULL)), 9, nouveau_noeud(NULL, 10, NULL)), 12, nouveau_noeud(NULL, 14, NULL));
	printf("Arbre f : hauteur=%d\n", hauteur(f));
	afficher_arbre(f, 0);

	printf("Arbre g : rotation a droite de f :\n");
	AVL g = rotation_droite(f);
	afficher_arbre(g, 0);

    AVL h = nouveau_noeud(nouveau_noeud(nouveau_noeud(nouveau_noeud(NULL,1,NULL),2,NULL),3,nouveau_noeud(NULL,4,NULL)),5,nouveau_noeud(nouveau_noeud(nouveau_noeud(NULL,7,nouveau_noeud(NULL,8,nouveau_noeud(NULL,9,NULL))),10,nouveau_noeud(nouveau_noeud(NULL,11,nouveau_noeud(NULL,12,NULL)),13,NULL)),20,nouveau_noeud(nouveau_noeud(NULL,22,nouveau_noeud(NULL,23,NULL)),24,NULL)));
	printf("Arbre h : hauteur=%d\n", hauteur(h));
	afficher_arbre(h, 0);

	printf("Arbre i : double rotation a gauche de h :\n");
	AVL i = double_rotation_gauche(h);
	afficher_arbre(i, 0);

	AVL j = nouveau_noeud(nouveau_noeud(nouveau_noeud(NULL,1,nouveau_noeud(nouveau_noeud(NULL,2,NULL),3,NULL)),4,nouveau_noeud(nouveau_noeud(NULL,5,nouveau_noeud(nouveau_noeud(NULL,6,NULL),7,NULL)),8,nouveau_noeud(nouveau_noeud(NULL,9,nouveau_noeud(NULL,10,NULL)),11,NULL))),12,nouveau_noeud(nouveau_noeud(NULL,13,nouveau_noeud(NULL,14,NULL)),15,NULL));
	printf("Arbre j : hauteur=%d\n", hauteur(j));
	afficher_arbre(j, 0);

	printf("Arbre k : double rotation a droite de j :\n");
	AVL k = double_rotation_droite(j);
	afficher_arbre(k, 0);

	printf("Arbre l : reequilibrage de j :\n");
	AVL l = equilibrer(j);
	afficher_arbre(l, 0);

	printf("insertion de 16 dans l :\n");
	AVL m = ajouter_cle(l, 16);
	afficher_arbre(m, 0);

    return 0;
  
}