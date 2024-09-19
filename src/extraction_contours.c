#include <stdio.h>
#include <string.h>
#include "extraction_contours.h"
#include "image.h"



// cette fonction prend maintenant également l'image masque en argument
void trouver_pixel_depart(int *x, int *y, Image I,int x_save,int y_save){
	UINT h = hauteur_image(I);
	UINT l = largeur_image(I);

	
	int boucle=1;
	int i,j;
	for (j=y_save; j<=h; j++){	
		if (!boucle)
			break;
		
		//on reprend au bonne endroit verticalement, mais seulemnt lors de la premiere boucle
		if (j==y_save){
			for (i=x_save; i<=l; i++){ 
				if (!boucle)
					break;
				if (get_pixel_image(I, i, j)==1){
					*x = i;
					*y = j;
					boucle=0;
				}
			}
		}
		else{
			for (i=1; i<=l; i++){ 
				if (!boucle)
					break;
				if (get_pixel_image(I, i, j)==1){
					*x = i;
					*y = j;
					boucle=0;
				}
			}
		}
		
	}
		
}


Orientation nouvelle_orientation(int x, int y, Orientation o, Image I){
	//Assignation de pD et pG:
	int pD,pG;
	switch (o){	
		case Est:
			pD = get_pixel_image(I, x+1, y+1);
			pG = get_pixel_image(I, x+1, y);
			break;
		
		case Nord:
			pD = get_pixel_image(I, x+1, y);
			pG = get_pixel_image(I, x, y);
			break;
		
		case Ouest:
			pD = get_pixel_image(I, x, y);
			pG = get_pixel_image(I, x, y+1);
			break;
		
		case Sud:
			pD = get_pixel_image(I, x, y+1);
			pG = get_pixel_image(I, x+1, y+1);
			break;
	}
	
	//decision en fonction de pG et pD
	if (pG == 1){
		switch (o){
			case Nord:
				return Ouest;
				break;
			
			case Ouest:
				return Sud;
				break;
			
			case Sud:
				return Est;
				break;
			
			case Est:
				return Nord;
				break;
		}
	}
	
	if (pD == 0){
		switch (o){
			case Nord:
				return Est;
				break;
			
			case Ouest:
				return Nord;
				break;
			
			case Sud:
				return Ouest;
				break;
			
			case Est:
				return Sud;
				break;
		}
	}
	
	
	return o;
}


Liste_Point countour_from_point(Image I, int x, int y, Image M){
	int x0 = x-1;
	int y0 = y-1;	
	int x1=x0;
	int y1=y0;
	Orientation o = Est;
	Liste_Point L = creer_liste_Point_vide();
	Point e;	
	
	int boucle = 1;
	while (boucle){		
		e.x = x1;
		e.y = y1;
		L = ajouter_element_liste_Point(L, e);
		
		
		switch(o){
			case Est:
				
				x1++;
				set_pixel_image(M, x1, y1+1, 0);
				break;
			
			case Sud:
				y1++;
				break;
			
			case Ouest:
				x1--;
				break;
			
			case Nord:
				y1--;
				break;
		}
		o = nouvelle_orientation(x1, y1, o, I);
			
		
		if ((x1==x0) && (y1==y0) && (o==Est))
			boucle = 0;	

	}
	e.x = x1;
	e.y = y1;
	L = ajouter_element_liste_Point(L, e);
	

	return L;

}

Liste_contours extraction_contours(char *nom_pbm,int *total_points){
	Liste_contours C = creer_liste_contours_vide();
	

	Image I = lire_fichier_image(nom_pbm);
	Image M = masque(I);
	int x,y;
	int x_save=1;
	int y_save=1;
	x=1;
	y=1;
	//detection des contours:
	while (!est_vide(M)){
		
		trouver_pixel_depart(&x, &y, M, x_save, y_save);
		x_save = x; y_save = y;
		Liste_Point L = countour_from_point(I, x, y, M);	
		
		C = ajouter_element_liste_contours(C, sequence_points_liste_vers_tableau(L));
		
		*total_points += L.taille;
			
	}
	return C;
}











