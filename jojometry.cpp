//Fichier de geometrie
#include "jojometry.h"
#include <math.h>
#include "iostream"


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
  bool steep = false; 
  if (std::abs(x0-x1)<std::abs(y0-y1)) { 
    std::swap(x0, y0); 
    std::swap(x1, y1); 
    steep = true; 
  }
  //make sure that x0 < X1 
  if (x0>x1) { 
    std::swap(x0, x1); 
    std::swap(y0, y1); 
  } 
  int dx = x1-x0; 
  int dy = y1-y0; 
  int derror2 = std::abs(dy)*2; 
  int error2 = 0; 
  int y = y0;
  int x;
  if (steep) {
    for (x=x0; x<=x1; x++) { 
 
      image.set(y, x, color); 
      error2 += derror2; 
      if (error2 > dx) { 
	y += (y1>y0?1:-1); 
	error2 -= dx*2; 
      } 
    }
  }else{ // !steep
    for(x=x0; x<=x1; x++){
      image.set(x, y, color);
      error2 += derror2;
      if(error2 > dx) {
	y += (y1>y0?1:-1);
	error2 -= dx*2;
      }
    }
  }
}

void triangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage &image, TGAColor color){
  //have to sort the vertices from lower height to highest
  if(p1.v > p2.v) std::swap(p1,p2);
  if(p1.v > p3.v) std::swap(p1,p3);
  if(p2.v > p3.v) std::swap(p2,p3);


  int triangle_height = p3.y-p1.y; 
  for (int y=p1.y; y<=p2.y; y++) { 
    int edge_height = p2.y-p1.y+1; 
    float alpha = (float)(y-p1.y)/triangle_height; 
    float beta  = (float)(y-p1.y)/edge_height; 
    Vec2i A = p1 + (p3-p1)*alpha; 
    Vec2i B = p1 + (p2-p1)*beta; 
    if (A.x>B.x) std::swap(A, B);
    line(A.x, y, B.x, y, image, color);
 
  }

  for (int y=p2.y; y<=p3.y; y++) { 
    int edge_height =  p3.y-p2.y+1; 
    float alpha = (float)(y-p1.y)/triangle_height; 
    float beta  = (float)(y-p2.y)/edge_height; 
    Vec2i A = p1 + (p3-p1)*alpha; 
    Vec2i B = p2 + (p3-p2)*beta; 
    if (A.x>B.x) std::swap(A, B);
    line(A.x, y, B.x, y, image, color);

  } 

  
}

void normalise(Vec3f* vec){
  float length = vec->x*vec->x + vec->y*vec->y + vec->z*vec->z;
  length = sqrt(length);
  vec->x /= length;
  vec->y /= length;
  vec->z /= length;

}
