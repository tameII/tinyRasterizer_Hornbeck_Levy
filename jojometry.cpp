//Fichier de geometrie
#include "jojometry.h"


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
  for (int x=x0; x<=x1; x++) { 
    float t = (x-x0)/(float)(x1-x0); 
    int y = y0*(1.-t) + y1*t; 
    image.set(x, y, color); 
  } 
 
 
}
