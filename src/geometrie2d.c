#include "geometrie2d.h"
#include <math.h>

Point set_point(double x, double y){
	 Point P= {x,y};
	 return P;
}

Point add_point(Point A, Point B){
	return set_point(A.x+B.x, A.y+B.y);
}

Vect vect_bipoint(Point A, Point B){
	Vect u = {B.x-A.x, B.y-A.y};
	return u;
}	

Vect vect_x_scalaire(Vect u, int a){
	Vect v = {a*u.x, a*u.y};
	return v;
}

Point point_x_scalaire(Point P, double a){
	return set_point(a*P.x, a*P.y);
}

//calcul du point C(t) d'une courbe de degrée 2
Point Ct_bezier2(Bezier2 B,double t){
	double a = pow((1-t), 2);
	double b = 2*t*(1-t);
	double c = pow(t, 2);
	
	Point Ct;
	//Calucl de C(t):
	Ct= add_point( point_x_scalaire(B.c0, a), point_x_scalaire(B.c1, b));
	Ct= add_point( Ct, point_x_scalaire(B.c2, c));
	
	
	return Ct;
}

//calcul du point C(t) d'une courbe de degrée 3
Point Ct_bezier3(Bezier3 B, double t){
	double a = pow((1-t), 3);
	double b = 3 * t * pow((1-t), 2);
	double c = 3 * pow(t, 2) * (1-t);
	double d = pow(t, 3);
	
	Point Ct;
	//Calucl de C(t):
	Ct= add_point( point_x_scalaire(B.c0, a), point_x_scalaire(B.c1, b));
	Ct= add_point( Ct, point_x_scalaire(B.c2, c));
	Ct= add_point( Ct, point_x_scalaire(B.c3, d));
	
	return Ct;	
}

double produit_scalaire(Vect u, Vect v){
	return u.x*v.x + u.y*v.y;
}

double norme(Vect u){
	return sqrt(pow(u.x,2) + pow(u.y,2));
}

double distance(Point A, Point B){
	return sqrt(pow((A.x - B.x),2) + pow((A.y - B.y),2));
}

double distance_point_seg(Point P, Point A, Point B){
	Vect AP = vect_bipoint(A, P);
	Vect AB = vect_bipoint(A, B);
	Vect BP = vect_bipoint(B, P);
	
	double delta = produit_scalaire(AP, AB) / produit_scalaire(AB, AB);	
	
	if (delta<0)
		return norme(AP);
		
	else if(delta > 1)
		return norme(BP);
		
	else{
		Point Q = {A.x + delta*B.x - delta*A.x, A.y + delta*B.y - delta*A.y};
		return norme(vect_bipoint(Q, P));
	}	
}

//transformer une courbe de degrée 2 en courbe de degrée 3
Bezier3 B2_to_B3(Bezier2 B2){
	double a = 1.0/3.0;

	Bezier3 B3;
	
	B3.c0 = B2.c0;

	//c1' = (c0 + 2c1) / 3
	B3.c1 = point_x_scalaire(add_point( B2.c0, point_x_scalaire(B2.c1, 2.0)), a);
	//c2' = (2c1 +c2) / 3
	B3.c2 = point_x_scalaire(add_point( B2.c2, point_x_scalaire(B2.c1, 2.0)), a);
	
	B3.c3 = B2.c2;
	
	return B3;

}

//distance estimée entre Pi et une courbe de bezier 
double distance_point_bezier2(Point Pi, Bezier2 B, double ti){
	Point Cti = Ct_bezier2(B, ti);
	return distance(Pi, Cti);

}

double distance_point_bezier3(Point Pi, Bezier3 B, double ti){
	Point Cti = Ct_bezier3(B, ti);
	return distance(Pi, Cti);

}

























