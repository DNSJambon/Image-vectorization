#include <stdio.h>
#include <string.h>
#include "simplification_seg.h"
#include "postScript.h"

void sequence_segments_vers_PS(FILE *f, Liste_segments C,int h){
	int i;
	moveto(f,C.first->data.a.x, h -C.first->data.a.y);
	Cellule_segment *tmp = C.first;
	
	for (i=0; i<C.taille; i++){	
		
		lineto(f, tmp->data.b.x, h -tmp->data.b.y);	
		tmp = tmp->suiv;
	}

	
}

Liste_segments simplif_douglas_peucker(Tableau_Point cont, int j1, int j2, double d){
	int j;
	Liste_segments L = creer_liste_segments_vide();
	
	Segment s;
	s.a= cont.tab[j1];
	s.b = cont.tab[j2];
	
	double dmax = 0;
	int k = j1;
	
	for (j=j1+1; j<=j2; j++){
		double dj = distance_point_seg(cont.tab[j], s.a, s.b);
		
		if (dmax<dj){
			dmax = dj;
			k = j;
		}
	}
	
	if (dmax <= d){
		L = ajouter_element_liste_segments(L, s);
	}
	
	else{
		Liste_segments L1 = simplif_douglas_peucker(cont,j1,k,d);
		Liste_segments L2 = simplif_douglas_peucker(cont,k,j2,d);
		
		L = concatener_liste_segments(L, L1);
		L = concatener_liste_segments(L, L2);
		
		
	}
	
	
	return L;

}



int main(int argc, char* argv[]){
	if (argc!=4){
		printf("%s <fichier_image.pbm> <disatnce seuil> <nom.eps>\n",argv[0]);
		return 1;
	}
	int i;
	float d;
	sscanf(argv[2], "%f", &d);

	//extracion des contours:
	int total_points = 0;
	Image I = lire_fichier_image(argv[1]);
	Liste_contours C = extraction_contours(argv[1], &total_points);
	

	FILE *f;
	f = initialiser_fichier(0, 0, largeur_image(I), hauteur_image(I), argv[3]);
	
	//simplification des contours:
	int total = 0;
	Cellule_contour *tmp= C.first;	
	for (i=0; i<C.taille; i++){
		Liste_segments S = simplif_douglas_peucker(tmp->data, 0, tmp->data.taille-2, d);	
		total += S.taille;
		sequence_segments_vers_PS(f, S, hauteur_image(I));
		tmp = tmp->suiv;
	}
		
	fprintf(f, "0 0 0 setrgbcolor 0.0 setlinewidth\n");
	fill(f);
	fprintf(f, "showpage");
	
	printf("contours: %d\n", C.taille);
	printf("nombre segments avant simplification: %d\n", total_points - C.taille);
	printf("nombre segments apres simplification (d=%f): %d\n",d , total-1);
	
	
	return 0;
}




