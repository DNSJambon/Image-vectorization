#include "extraction_contours.h"




Liste_segments simplif_douglas_peucker(Tableau_Point cont, int j1, int j2, double d);

void sequence_segments_vers_PS(FILE *f, Liste_segments C, int h);
