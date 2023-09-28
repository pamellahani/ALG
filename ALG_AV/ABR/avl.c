#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

void afficher_arbre (AVL a, int niveau)
{
  int i ;
  
  if (a != NULL){
	afficher_arbre (a->fdroite,niveau+1) ;
	
	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d[%d] (%d)\n\n", a->cle, a->bal, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}

int hauteur(AVL a){
	if(a==NULL)return -1;
	int hauteur_gauche=0;
	if(a->fgauche!=NULL) hauteur_gauche=hauteur(a->fgauche);
	int hauteur_droite=0;
	if(a->fdroite!=NULL) hauteur_droite=hauteur(a->fdroite);

	if(a->fgauche==NULL && a->fdroite==NULL)return 0;
	if(a->fgauche==NULL) return hauteur_droite+1;
	if(a->fdroite==NULL) return hauteur_gauche+1;
	if(hauteur_droite>hauteur_gauche)return hauteur_droite+1;
	return hauteur_gauche+1;
}

AVL nouveau_noeud(AVL a, int cle, AVL b){
	AVL new=malloc(sizeof(AVL));
 	new->cle=cle;
 	new->fgauche=a;
 	new->fdroite=b;
 	new->bal=0;
 	int hg=hauteur(a), hd=hauteur(b);
 	if(hg!=-1 || hd!=-1){
 		if(hg!=-1 && hd==-1)new->bal=hg+1;
 		else if(hg==-1 && hd!=-1)new->bal=hd+1;
 		else {
 			new->bal=hg-hd;
 		}
 	}
 	if(new->bal>2)new->bal=2;
 	if(new->bal<-2)new->bal=-2;
 	return new;
}
/*
BAL : 
0-> equilibre 
1-> sous arbre droit = h+1 de sous arbre gauche 
-1 -> sous arbre gauche = h+1 de sous arbre droit
2 -> sous arbre droit = h+2 de sous arbre arbre gauche
*/

AVL rotation_gauche(AVL A) {
    if (A==NULL || A->fdroite == NULL)return A;  
    AVL B = A->fdroite ;
    A->fdroite = B->fgauche ;
    B->fgauche = A ;

    // UPDATE BAL 
    // if (B->bal == -1) {
    //     A->bal = 0 ;
    //     B->bal = 0 ;
    // }
    // else{
    //     A->bal=-1;
    //     B->bal=1; 
    // }
    return B;
}

AVL rotation_droite(AVL A) {
    if (A==NULL)return A;
    AVL B = A->fgauche; 
    A->fgauche=B->fdroite; 
    B->fdroite = A ;
    
    // UPDATE BAL
    // if (B->bal == 1) {
    //     A->bal = 0 ;
    //     B->bal = 0 ;
    // }
    // else{
    //     A->bal=1;
    //     B->bal=-1; 
    // }
    return B ;
}

AVL double_rotation_gauche(AVL a){
    a->fdroite = rotation_droite (a->fdroite); 
    return rotation_gauche(a); 
}

AVL double_rotation_droite(AVL a){
    a->fgauche = rotation_gauche (a->fgauche); 
    return rotation_droite(a); 
}

AVL equilibrer(AVL a){
    if (a->bal == 2){
        if (a->fdroite->bal >= 0){
            return rotation_gauche(a);
        }
        else{
            a->fdroite = rotation_droite(a->fdroite); 
            return rotation_gauche(a);
        }
    }
    else if (a->bal == -2){
        if (a->fgauche->bal <= 0){
            return rotation_droite(a);
        }
        else{
            a->fgauche = rotation_gauche(a->fgauche); 
            return rotation_droite(a);
        }
    }
    else return a; 
}

AVL ajouter_cle (AVL a, int cle){
    if (a==NULL) return nouveau_noeud(NULL,cle,NULL); 
    if (cle<a->cle){
        a->fgauche = ajouter_cle(a->fgauche,cle);
    }
    else if (cle > a->cle){
        a->fdroite = ajouter_cle(a->fdroite,cle);
    }
    else{
        return a; 
    }

    //left left case 
    if (a->bal>1 && cle < a->fgauche->cle){
        return rotation_droite(a); 
    }
    //right right case
    if (a->bal < -1 && cle < a->fdroite->cle){
        return rotation_gauche(a); 
    }
    //left right case
    if (a->bal > 1 && cle > a->fgauche->cle){
        a->fgauche = rotation_gauche(a->fgauche); 
        return rotation_droite(a);
    }
    //right left case
    if (a->bal<-1 && cle < a->fdroite->cle){
        a->fdroite = rotation_droite(a->fdroite); 
        return rotation_gauche(a);
    }
    return a; 
}