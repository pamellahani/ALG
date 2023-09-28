typedef struct n {
int cle ;
int bal ; /* balance comprise entre –1 et +1 */
struct n *fgauche, *fdroite ;
} noeud ;

typedef noeud *AVL ;
void afficher_arbre (AVL a, int niveau); 
int hauteur(AVL a);
AVL nouveau_noeud(AVL a, int cle, AVL b); 

AVL rotation_gauche (AVL a); 
AVL rotation_droite (AVL a);
AVL double_rotation_gauche(AVL a); 
AVL double_rotation_droite(AVL a); 
AVL equilibrer(AVL a); 
AVL ajouter_cle(AVL a, int cle); 
void destruction_cle(AVL a);
