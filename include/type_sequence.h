#include"geometrie2d.h"
#include<stdio.h>
#include<stdlib.h>

//structure liste chainée de Points:
typedef struct Cellule_Liste_Point_
{
	Point data;
	struct Cellule_Liste_Point_ *suiv;
} Cellule_Liste_Point ;

typedef struct Liste_Point_
{
	unsigned int taille;
	Cellule_Liste_Point *first;
	Cellule_Liste_Point *last;

} Liste_Point ;
	typedef Liste_Point Contour;

typedef struct Tableau_Point_
{
	unsigned int taille;
	Point *tab;
} Tableau_Point ;

Cellule_Liste_Point *creer_element_liste_Point (Point v);

Liste_Point creer_liste_Point_vide();

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point (Liste_Point Ll, Liste_Point L2);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

void ecrire_contour(Liste_Point L, FILE *f);






//structure liste chainée de countours:
typedef struct Cellule_contour_
{
	Tableau_Point data;
	struct Cellule_contour_ *suiv;
} Cellule_contour ;

typedef struct Liste_contours_
{
	unsigned int taille;
	Cellule_contour *first;
	Cellule_contour *last;

} Liste_contours ;
	typedef Liste_contours seq_contour;


Cellule_contour *creer_element_contour (Tableau_Point t);

Liste_contours creer_liste_contours_vide();

Liste_contours ajouter_element_liste_contours(Liste_contours C, Tableau_Point t);

Liste_contours supprimer_liste_contours(Liste_contours C);






//structure liste chainée de segments:
typedef struct Cellule_segment_
{
	Segment data;
	struct Cellule_segment_ *suiv;
} Cellule_segment ;

typedef struct Liste_segments_
{
	unsigned int taille;
	Cellule_segment *first;
	Cellule_segment *last;

} Liste_segments ;
	typedef Liste_segments seq_segments;

Cellule_segment *creer_element_liste_segments(Segment s);

Liste_segments creer_liste_segments_vide();

Liste_segments ajouter_element_liste_segments(Liste_segments S, Segment s);

Liste_segments supprimer_liste_segments(Liste_segments S);

Liste_segments concatener_liste_segments (Liste_segments S1, Liste_segments S2);



//structure liste chainée de courbes de degrée 2:
typedef struct Cellule_courbe_
{
	Bezier2 data;
	struct Cellule_courbe_ *suiv;
} Cellule_courbe ;

typedef struct Liste_courbe_
{
	unsigned int taille;
	Cellule_courbe *first;
	Cellule_courbe*last;

} Liste_courbes ;
	typedef Liste_courbes seq_courbes;

Cellule_courbe *creer_element_liste_courbe(Bezier2 b);

Liste_courbes creer_liste_courbes_vide();

Liste_courbes ajouter_element_liste_courbes(Liste_courbes B, Bezier2 b);

Liste_courbes supprimer_liste_courbes(Liste_courbes B);

Liste_courbes concatener_liste_courbes (Liste_courbes B1, Liste_courbes B2);



//structure liste chainée de courbes de degrée 3:
typedef struct Cellule_courbe3_
{
	Bezier3 data;
	struct Cellule_courbe3_ *suiv;
} Cellule_courbe3 ;

typedef struct Liste_courbe3_
{
	unsigned int taille;
	Cellule_courbe3 *first;
	Cellule_courbe3 *last;

} Liste_courbes3 ;
	typedef Liste_courbes3 seq_courbes3;

Cellule_courbe3 *creer_element_liste_courbe3(Bezier3 b);

Liste_courbes3 creer_liste_courbes3_vide();

Liste_courbes3 ajouter_element_liste_courbes3(Liste_courbes3 B, Bezier3 b);

Liste_courbes3 supprimer_liste_courbes3(Liste_courbes3 B);

Liste_courbes3 concatener_liste_courbes3 (Liste_courbes3 B1, Liste_courbes3 B2);

