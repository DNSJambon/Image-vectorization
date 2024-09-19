#include <stdio.h>
#include <stdlib.h>
#include "type_sequence.h"

//structure Points:
Cellule_Liste_Point *creer_element_liste_Point (Point v)
{
	Cellule_Liste_Point *e1;
	e1 = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point ));
	if (e1==NULL){
	
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	e1->data = v;
	e1->suiv = NULL;
	return e1;
}

Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;
	el = creer_element_liste_Point(e);
	if (L.taille == 0)	
		L.first = L.last = el;

	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while(el)
	{
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Point concatener_liste_Point (Liste_Point Ll, Liste_Point L2)
{
	
	if (Ll.taille == 0) return L2;
	if (L2.taille == 0) return Ll;
	
	Ll.last->suiv = L2.first;
	Ll.last = L2.last; 
	Ll.taille += L2.taille; 
	return Ll;
}

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	T.taille = L.taille;
	
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, "allocation impossible\n");
		exit(-1);
	}
	
	int k = 0;
	Cellule_Liste_Point *el = L.first;
	while (el)
	{
		T.tab[k] = el->data;
		k++;
		el = el->suiv;
	}
	return T;
}

void ecrire_contour(Liste_Point L, FILE *f)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	fprintf(f, "%d\n", nP);
	for (k = 0; k < nP; k++)
	{
		Point P = TP.tab[k];
		fprintf(f, " %.1f %.1f\n", P.x, P.y);
	}
	fprintf(f, "\n");
	free(TP.tab);
}






//Structure contours:
Cellule_contour *creer_element_contour (Tableau_Point t)
{
	Cellule_contour *e1;
	e1 = (Cellule_contour *)malloc(sizeof(Cellule_contour));
	if (e1==NULL){
	
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	e1->data = t;
	
	e1->suiv = NULL;
	return e1;
}

Liste_contours creer_liste_contours_vide()
{

	Liste_contours L = {0, NULL, NULL};
	return L;
}

Liste_contours ajouter_element_liste_contours(Liste_contours C, Tableau_Point t)
{
	Cellule_contour *el;
	el = creer_element_contour(t);
	
	if (C.taille == 0)	
		C.first = C.last = el;

	else
	{
		C.last->suiv = el;
		C.last = el;
	}
	C.taille++;

	return C;
}


Liste_contours supprimer_liste_contours(Liste_contours C)
{
	Cellule_contour *el=C.first;
	
	while(el)
	{
		Cellule_contour *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	C.first = C.last = NULL; C.taille = 0;
	return C;
}










//Structure liste chainée Segments:
Cellule_segment *creer_element_liste_segments(Segment s){
	Cellule_segment *e1;
	e1 = (Cellule_segment *)malloc(sizeof(Cellule_segment));
	if (e1==NULL){
	
		fprintf(stderr, "creer_element_liste_segment : allocation impossible\n");
		exit(-1);
	}
	e1->data = s;
	
	e1->suiv = NULL;
	return e1;
}

Liste_segments creer_liste_segments_vide(){
	Liste_segments L = {0, NULL, NULL};
	return L;
}

Liste_segments ajouter_element_liste_segments(Liste_segments S, Segment s){
	Cellule_segment *el;
	el = creer_element_liste_segments(s);
	
	if (S.taille == 0)	
		S.first = S.last = el;

	else
	{
		S.last->suiv = el;
		S.last = el;
	}
	S.taille++;

	return S;
}

Liste_segments supprimer_liste_segments(Liste_segments S){
	Cellule_segment *el=S.first;
	
	while(el)
	{
		Cellule_segment *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	S.first = S.last = NULL; S.taille = 0;
	return S;
}

Liste_segments concatener_liste_segments (Liste_segments S1, Liste_segments S2){
	if (S1.taille == 0) return S2;
	if (S2.taille == 0) return S1;
	
	S1.last->suiv = S2.first;
	S1.last = S2.last; 
	S1.taille += S2.taille; 
	return S1;
}


//Structure liste chainée de courbes de degré 2:
Cellule_courbe *creer_element_liste_courbes(Bezier2 s){
	Cellule_courbe *e1;
	e1 = (Cellule_courbe *)malloc(sizeof(Cellule_courbe));
	if (e1==NULL){
	
		fprintf(stderr, "creer_element_liste_segment : allocation impossible\n");
		exit(-1);
	}
	e1->data = s;
	
	e1->suiv = NULL;
	return e1;
}

Liste_courbes creer_liste_courbes_vide(){
	Liste_courbes L = {0, NULL, NULL};
	return L;
}

Liste_courbes ajouter_element_liste_courbes(Liste_courbes S, Bezier2 s){
	Cellule_courbe *el;
	el = creer_element_liste_courbes(s);
	
	if (S.taille == 0)	
		S.first = S.last = el;

	else
	{
		S.last->suiv = el;
		S.last = el;
	}
	S.taille++;

	return S;
}

Liste_courbes supprimer_liste_courbes(Liste_courbes S){
	Cellule_courbe *el=S.first;
	
	while(el)
	{
		Cellule_courbe *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	S.first = S.last = NULL; S.taille = 0;
	return S;
}

Liste_courbes concatener_liste_courbes (Liste_courbes S1, Liste_courbes S2){
	if (S1.taille == 0) return S2;
	if (S2.taille == 0) return S1;
	
	S1.last->suiv = S2.first;
	S1.last = S2.last; 
	S1.taille += S2.taille; 
	return S1;
}




//Structure liste chainée de courbes de degré 3:
Cellule_courbe3 *creer_element_liste_courbes3(Bezier3 s){
	Cellule_courbe3 *e1;
	e1 = (Cellule_courbe3 *)malloc(sizeof(Cellule_courbe3));
	if (e1==NULL){
	
		fprintf(stderr, "creer_element_liste_segment : allocation impossible\n");
		exit(-1);
	}
	e1->data = s;
	
	e1->suiv = NULL;
	return e1;
}

Liste_courbes3 creer_liste_courbes3_vide(){
	Liste_courbes3 L = {0, NULL, NULL};
	return L;
}

Liste_courbes3 ajouter_element_liste_courbes3(Liste_courbes3 S, Bezier3 s){
	Cellule_courbe3 *el;
	el = creer_element_liste_courbes3(s);
	
	if (S.taille == 0)	
		S.first = S.last = el;

	else
	{
		S.last->suiv = el;
		S.last = el;
	}
	S.taille++;

	return S;
}

Liste_courbes3 supprimer_liste_courbes3(Liste_courbes3 S){
	Cellule_courbe3 *el=S.first;
	
	while(el)
	{
		Cellule_courbe3 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	S.first = S.last = NULL; S.taille = 0;
	return S;
}

Liste_courbes3 concatener_liste_courbes3 (Liste_courbes3 S1, Liste_courbes3 S2){
	if (S1.taille == 0) return S2;
	if (S2.taille == 0) return S1;
	
	S1.last->suiv = S2.first;
	S1.last = S2.last; 
	S1.taille += S2.taille; 
	return S1;
}





