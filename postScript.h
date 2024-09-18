FILE *initialiser_fichier(int xmin, int ymin, int xmax, int ymax, char *nom);

void moveto(FILE *f, int x, int y);

void lineto(FILE *f, int x, int y);

void stroke(FILE *f);

void fill(FILE *f);

void curveto(FILE *f, int xc0, int yc0, int xc1, int yc1, int xc2, int yc2);
