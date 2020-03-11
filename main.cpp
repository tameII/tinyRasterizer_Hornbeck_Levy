#include "tgaimage.h"
#include "jojometry.h"
#include "model.h"
#include "iostream"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);
const TGAColor blue   = TGAColor(0, 0,   255,   255);
const TGAColor yellow = TGAColor(255, 255,   0,   255);
const TGAColor cyan   = TGAColor(0, 255,   255,   255);
const TGAColor purple   = TGAColor(255, 0,   255,   255);


const int WIDTH = 800;
const int HEIGHT = 800;
Model *model = NULL;

int main(int argc, char** argv) {
  bool draw_triangle = false;
    if (2==argc) {
      //this option is here to test triangles, it will be removed when it's done 
      if(argv[1][0] == 't'){
	draw_triangle = true;
      }
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }
    TGAColor colors[7];
    colors[0] = white;
    colors[1] = red;
    colors[2] = green;
    colors[3] = blue;
    colors[4] = yellow;
    colors[5] = cyan;
    colors[6] = purple;
    int width = WIDTH;
    int height = HEIGHT;
    int numColor = 0;
    TGAImage image(width, height, TGAImage::RGB);
    if(!draw_triangle){
    
      for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
	Vec3f pf1 = model->vert(face[0]);
        Vec3f pf2 = model->vert(face[1]);
	Vec3f pf3 = model->vert(face[2]);
	//now we have to convert this Vec3f in Vec2i
	int x1 = (pf1.x+1.)*width/2.;
	int y1 = (pf1.y+1.)*height/2.;
	Vec2i p1(x1,y1);
	int x2 = (pf2.x+1.)*width/2.;
	int y2 = (pf2.y+1.)*height/2.;
	Vec2i p2(x2,y2);
	int x3 = (pf3.x+1.)*width/2.;
	int y3 = (pf3.y+1.)*height/2.;
	Vec2i p3(x3, y3);
	triangle(p1,p2,p3, image, colors[numColor]);
	numColor++;
	numColor = numColor%7;
      }
    }
    else{
      Vec2i p1(10,70), p2(50,160), p3(70,80);
      triangle(p1,p2,p3, image, white);
      Vec2i p4(180,50), p5(150,1), p6(70,180);
      triangle(p4,p5,p6, image, red);
      Vec2i p7(180,150), p8(120,160), p9(130,180);
      triangle(p7,p8,p9, image, green);
    }
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
