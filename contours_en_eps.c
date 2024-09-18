#include "extraction_contours.h"
#include "postScript.h"

void sequence_contours_vers_PS(FILE *f, seq_contour C, int h){
	int i,j;
	Cellule_contour *tmp = C.first;
	
	for (i=0; i<C.taille; i++){
		moveto(f,tmp->data.tab[0].x, h - tmp->data.tab[0].y);
		
		for (j=0; j< tmp->data.taille; j++){		
			lineto(f, tmp->data.tab[j].x, h - tmp->data.tab[j].y);
		}		
		tmp = tmp->suiv;
	}

	fprintf(f, "0 0 0 setrgbcolor 0.0 setlinewidth\n");
	fill(f);
	fprintf(f, "showpage");
	
}



int main(int argc, char *argv[]){
	if (argc != 3){
		printf("%s : <fichier.pbm> <fichier_image.eps>\n",argv[0]);
		return 1;
	}
	
	
	Liste_contours C = creer_liste_contours_vide();
	int total_points=0;
	Image I = lire_fichier_image(argv[1]);
	Image M = masque(I);
	int x; int y;
	int x_save=1;
	int y_save=1;
	x=1;
	y=1;
	
	//detection des contours:
	while (!est_vide(M)){
		int x,y;
		trouver_pixel_depart(&x, &y, M, x_save, y_save);
		x_save = x; y_save = y;
		Liste_Point L = countour_from_point(I, x, y, M);
		C = ajouter_element_liste_contours(C, sequence_points_liste_vers_tableau(L));
		
		total_points += L.taille;
		
	
	}
	
	//Postscript:
	FILE *f;
	f = initialiser_fichier(0, 0, largeur_image(I), hauteur_image(I), argv[2]);
	sequence_contours_vers_PS(f, C, hauteur_image(I));
	
	printf("nombre de contours: %d\nsomme du nombre de segments: %d\n", C.taille, total_points - C.taille);

	


	return 0;
}
