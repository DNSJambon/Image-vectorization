#include <stdio.h>
#include "postScript.h"

FILE *initialiser_fichier(int x_min,int y_min,int x_max,int y_max,char *nom){
    FILE *f;
    f=fopen(nom,"w");
    fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n%%%%BoundingBox: %d %d %d %d\n",x_min,y_min,x_max,y_max);
    return f;
}

void stroke(FILE *f){
    fprintf(f, "stroke\n");
}

void fill(FILE *f){
    fprintf(f, "fill\n");
}

void moveto(FILE *f, int x, int y){
	fprintf(f, "%d %d moveto\n",x ,y);

}

void lineto(FILE *f, int x, int y){
	fprintf(f, "%d %d lineto\n",x ,y);
}

void curveto(FILE *f, int xc0, int yc0, int xc1, int yc1, int xc2, int yc2){
	fprintf(f, "%d %d %d %d %d %d curveto\n",xc0, yc0, xc1, yc1, xc2, yc2);
}
