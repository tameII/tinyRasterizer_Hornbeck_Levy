#include "tgaimage.h"
#include "jojometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
	line(50, 5, 80, 40, image, white);
	line(5, 10, 90, 100, image, red);
	line(10, 5, 100, 90, image, white);
	line(10, 100, 5, 90, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
