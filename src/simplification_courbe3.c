#include <stdio.h>
#include <string.h>
#include <math.h>
#include "simplification_courbe3.h"
#include "postScript.h"


void sequence_courbes_vers_PS(FILE *f, Liste_courbes3 C,int h){
	int i;
	moveto(f,C.first->data.c0.x, h -C.first->data.c0.y);
	Cellule_courbe3 *tmp = C.first;
	
	for (i=0; i<C.taille; i++){	
		Bezier3 B3 = tmp->data;
		curveto(f, B3.c1.x, h - B3.c1.y, B3.c2.x, h - B3.c2.y, B3.c3.x, h - B3.c3.y);	
		tmp = tmp->suiv;
	}	
}

//algorithme de simplification en Bezier3:
Liste_courbes3 simplif_douglas_peucker(Tableau_Point cont, int j1, int j2, double d){
	int n = j2 - j1;
	int j; int i; double ti; double dj;
	Liste_courbes3 L = creer_liste_courbes3_vide();
	
	Bezier3 B = approx_bezier3(cont, j1, j2);
	
	double dmax=0;
	int k = j1;
	
	for (j=j1+1; j<=j2; j++){
		i = j-j1;
		ti = (float) i/ (float)n;
		
		dj = distance_point_bezier3(cont.tab[j], B, ti);
		if (dmax<dj){
			dmax = dj;
			k = j;
		}
	}
	
	if (dmax<=d){
		L = ajouter_element_liste_courbes3(L, B);
	}
	else{
		Liste_courbes3 L1 = simplif_douglas_peucker(cont,j1,k,d);
		Liste_courbes3 L2 = simplif_douglas_peucker(cont,k,j2,d);
		
		L = concatener_liste_courbes3(L, L1);
		L = concatener_liste_courbes3(L, L2);
	}
	return L;
	
}

// focntion pour gamma(k) 
double g(double k, double n){
	return 6*pow(k,4) - 8*n*pow(k,3) + 6*pow(k,2) - 4*n*k + pow(n,4) - pow(n,2);
}

Bezier3 approx_bezier3(Tableau_Point P, int j1, int j2){
	double n = j2-j1;
	int i;
	Point C1; 
	Point C2;
	
	//C0 = Pj1  et  C3 = Pj2:
	Bezier3 B;	
	B.c0 = P.tab[j1];
	B.c3 = P.tab[j2];
	
	if (n<3){
		Bezier2 B2;
		B2.c0 = B.c0;
		B2.c2 = B.c3;
		B2.c1 = point_x_scalaire(add_point(P.tab[j1], P.tab[j2]), 0.5);
		
		B = B2_to_B3(B2);
		}
		
	else{
		//alpha, beta, delta et gamma:
		double a = (-15*pow(n,3)+5*pow(n,2)+2*n+4) / (3*(n+2)*(3*pow(n,2)+1));
		double b = (10*pow(n,3)-15*pow(n,2)+n+2) / (3*(n+2)*(3*pow(n,2)+1));
		double d = 70*n / (3*(pow(n,2)-1)*(pow(n,2)-4)*(3*pow(n,2)+1));
		
		//somme des y(i) P(i+j1):	
		Point somme1= {0,0};
		for (i=1; i<n; i++){
			somme1 = add_point(somme1, point_x_scalaire(P.tab[j1+i], g((float)i, n)));
		}	
		
		//somme des y(n-i) P(i+j1):	
		Point somme2= {0,0};
		for (i=1; i<n; i++){
			somme2 = add_point(somme2, point_x_scalaire(P.tab[j1+i], g((float)(n-i), n)));
		}	
		
	
		//C1:
		C1 = point_x_scalaire(P.tab[j1], a);
		C1 = add_point(C1, point_x_scalaire(somme1, d ));
		C1 = add_point(C1, point_x_scalaire(P.tab[j2], b));
		
		//C2:
		C2 = point_x_scalaire(P.tab[j1], b);
		C2 = add_point(C2, point_x_scalaire(somme2, d ));
		C2 = add_point(C2, point_x_scalaire(P.tab[j2], a));
	 	
	 	B.c2 = C2;
		B.c1 = C1;
	 }
		
	
	return B;

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
		Liste_courbes3 S = simplif_douglas_peucker(tmp->data, 0, tmp->data.taille-1, d);	
		total += S.taille;
		sequence_courbes_vers_PS(f, S, hauteur_image(I));
		tmp = tmp->suiv;
	}
	
	fprintf(f, "0 0 0 setrgbcolor 0.0 setlinewidth\n");
	fill(f);
	fprintf(f, "showpage");
	
	printf("contours: %d\n", C.taille);
	printf("nombre segments avant simplification: %d\n", total_points - C.taille);
	printf("nombre courbes apres simplification (d=%f): %d\n",d , total);
	
	
	return 0;
}




