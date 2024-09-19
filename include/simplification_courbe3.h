#include "extraction_contours.h"




Liste_courbes3 simplif_douglas_peucker(Tableau_Point cont, int j1, int j2, double d);

void sequence_courbes_vers_PS(FILE *f, Liste_courbes3 C, int h);

double g(double k,double n);

Bezier3 approx_bezier3(Tableau_Point C, int j1, int j2);
