typedef struct Vecteur {
	double x,y;
}Vect;


typedef struct Point_ {
	double x,y;
}Point;

typedef struct Segment_ {
	Point a;
	Point b;
}Segment;

typedef struct bezier2_ {
	Point c0;
	Point c1;
	Point c2;
}Bezier2;

typedef struct bezier3_ {
	Point c0;
	Point c1;
	Point c2;
	Point c3;
}Bezier3;


Point set_point(double x, double y);

Point add_point(Point A, Point B);

Vect vect_bipoint(Point A, Point B);

Vect vect_x_scalaire(Vect u, int a);

Point point_x_scalaire(Point P, double a);

Point Ct_bezier2(Bezier2, double t);

Point Ct_bezier3(Bezier3, double t);

double produit_scalaire(Vect u, Vect v);

double norme(Vect u);

double distance(Point A, Point B);

double distance_point_seg(Point P, Point A, Point B);

Bezier3 B2_to_B3(Bezier2 B);

double distance_point_bezier2(Point Pi, Bezier2 B, double ti);

double distance_point_bezier3(Point Pi, Bezier3 B, double ti);



