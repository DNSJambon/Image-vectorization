#include "extraction_contours.h"




Liste_courbes simplif_douglas_peucker(Tableau_Point cont, int j1, int j2, double d);

void sequence_courbes_vers_PS(FILE *f, Liste_courbes C, int h);

Bezier2 approx_bezier2(Tableau_Point C, int j1, int j2);
