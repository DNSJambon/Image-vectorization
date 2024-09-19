#include "extraction_contours.h"
#include <math.h>

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
	int i;
	//test (a)
	printf("test (a):\n");
	Liste_Point C = creer_liste_Point_vide();
	
	Point P0= {5,-4};
	Point P1 = {-1,9};
	
	C = ajouter_element_liste_Point(C, P0);
	C = ajouter_element_liste_Point(C, P1);
	Tableau_Point P = sequence_points_liste_vers_tableau(C);
	
	
	Bezier3 B3 = approx_bezier3(P, 0,1);
	printf("C0 = %.2f,%.2f\nC1 = %.2f,%.2f\nC2 = %.2f,%.2f\nC3 = %.2f,%.2f\n\n", B3.c0.x, B3.c0.y, B3.c1.x, B3.c1.y, B3.c2.x, B3.c2.y,B3.c3.x, B3.c3.y);


	//test (c) n>3
	printf("test (b):\n");
	
	Point Q0= {0,4};
	Point Q1 = {1,9};
	Point Q2 = {-7,2};
	Point Q3 = {0,12};
	Bezier3 B;
	B.c0=Q0; B.c1=Q1; B.c2=Q2; B.c3=Q3;
	
	
	C = creer_liste_Point_vide();
	int n = 15;
	for(i=0; i<=n; i++){
	
		P0 = Ct_bezier3(B, (double) i/n);
		C = ajouter_element_liste_Point(C, P0);
		
	}
	P = sequence_points_liste_vers_tableau(C);
	
	B3= approx_bezier3(P, 0, n);	
	printf("C0 = %.2f,%.2f\nC1 = %.2f,%.2f\nC2 = %.2f,%.2f\nC3 = %.2f,%.2f\n\n", B3.c0.x, B3.c0.y, B3.c1.x, B3.c1.y, B3.c2.x, B3.c2.y,B3.c3.x, B3.c3.y);
	
	

	return 0;
}




