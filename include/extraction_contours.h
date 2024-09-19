#include "image.h"
#include "type_sequence.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation;


void trouver_pixel_depart(int *x, int *y, Image I, int x_save, int y_save);


Orientation nouvelle_orientation(int x, int y, Orientation o, Image I);

Liste_Point countour_from_point(Image I, int x, int y, Image M);


Image image_masque(Image I);

Liste_contours extraction_contours(char *nom_pbm, int *total_points);







