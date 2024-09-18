#include "extraction_contours.h"


int main(int argc, char *argv[]){
	if (argc != 3){
		printf("%s <fichier.pbm> <fichier_res.txt>\n",argv[0]);
		return 1;
	}
	int i,j;
	FILE *f;
	f= fopen(argv[2], "w");
	
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
	fprintf(f, "%d\n", C.taille);
	
	Cellule_contour *tmp = C.first;
	
	for (i=0; i<C.taille; i++){
		fprintf(f, "\n%d\n", tmp->data.taille);
		
		for (j=0; j< tmp->data.taille; j++){
			fprintf(f, "%.1f %.1f\n", tmp->data.tab[j].x, tmp->data.tab[j].y);
		}		
		tmp = tmp->suiv;
	}

	printf("nombre de contours: %d\nsomme du nombre de segments: %d\n", C.taille, total_points - C.taille);



	return 0;
}
