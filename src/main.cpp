#include <stdio.h>
#include "image.h"
#include "bmp.h"
#include "vec.h"
#define _USE_MATH_DEFINES // for C
#include <math.h>
#include <time.h>

#define IMG_WIDTH 1024
#define IMG_HEIGHT 1024
#define NUM_IMAGES 6
#define PIXELS_PER_IMAGE IMG_WIDTH * IMG_HEIGHT

int main() {

  Image imgs[NUM_IMAGES] = {
    Image { IMG_WIDTH, IMG_HEIGHT },
    Image { IMG_WIDTH, IMG_HEIGHT },
    Image { IMG_WIDTH, IMG_HEIGHT },
    Image { IMG_WIDTH, IMG_HEIGHT },
    Image { IMG_WIDTH, IMG_HEIGHT },
    Image { IMG_WIDTH, IMG_HEIGHT },
  };

  // allocate memory for pixels, just one chunk for all 6 image's pixels
  // Pixel struct is 24 bits, not the most efficient, but just ready to dump straight into the bmp file
  Pixel *allPixels = (Pixel *)malloc(PIXELS_PER_IMAGE * NUM_IMAGES * sizeof(Pixel));
  for (int i = 0; i < NUM_IMAGES; ++i) {
    imgs[i].pixels = &allPixels[PIXELS_PER_IMAGE * i];
  }

  Vec3 v3Origin;

  // the positions of each vertex for each plane/image (each side of the cube)
  Vec3 planes[NUM_IMAGES][4] = {
    { // front 0 
      Vec3(1, -1,  1),
      Vec3(1, -1, -1),
      Vec3(1,  1, -1),
      Vec3(1,  1,  1),
    },
    { // back 1
      Vec3(-1, -1, -1),
      Vec3(-1, -1,  1),
      Vec3(-1,  1,  1),
      Vec3(-1,  1, -1),
    },
    { // top 2
      Vec3(-1, 1,  1),
      Vec3( 1, 1,  1),
      Vec3( 1, 1, -1),
      Vec3(-1, 1, -1),
    },
    { // bottom 3
      Vec3(-1, -1, -1),
      Vec3( 1, -1, -1),
      Vec3( 1, -1,  1),
      Vec3(-1, -1,  1),
    },
    { // left 4
      Vec3(-1, -1, 1),
      Vec3( 1, -1, 1),
      Vec3( 1,  1, 1),
      Vec3(-1,  1, 1)
    },
    { // right 5
      Vec3( 1, -1, -1),
      Vec3(-1, -1, -1),
      Vec3(-1,  1, -1),
      Vec3( 1,  1, -1)
    }
  };

  clock_t startTime = clock();

  unsigned char r, g, b;
  Vec3 origX, origY;
  Vec3 pix;
  Pixel p;

  int pixIndex = 0;
  for (int y = 0; y < IMG_HEIGHT; ++y) {
    for (int x = 0; x < IMG_WIDTH; ++x) {
      float xPos = (float)x / IMG_WIDTH;
      float yPos = (float)y / IMG_HEIGHT;
      for (int i = 0; i < NUM_IMAGES; i++) {
        vec3Subtract(planes[i][1], planes[i][0], origX);
        vec3Subtract(planes[i][3], planes[i][0], origY);

        vec3Scale(origX, xPos, origX);
        vec3Scale(origY, yPos, origY);

        vec3Add(origX, origY, pix);

        vec3Add(pix, planes[i][0], pix);

        // normalize the vector (scale it to length of 1.0)
        vec3Scale(pix, 1.0f / vec3Dist(v3Origin, pix), pix);

        r = g = b = 0;

        // examples to play around with
        
        // colors get more intense the further along the axis they are
        if (pix.x >= 0) r = (unsigned char)roundf(pix.x * 255.0f);
        if (pix.y >= 0) b = (unsigned char)roundf(pix.y * 255.0f);
        if (pix.z >= 0) g = (unsigned char)roundf(pix.z * 255.0f);

        // some weird rings
        // b = (unsigned char)roundf(fabsf(sinf(100 * pix.y * M_PI) / 2.0f + .5f) * 255.0f);
        // r = (unsigned char)roundf(fabsf(sinf(50 * pix.x * M_PI) / 2.0f + .5f) * 255.0f);
        
        // something else
        // g = (unsigned char)roundf(fabsf(pix.x) * 255.0f);
        // r = (unsigned char)roundf(fabsf(pix.z) * 255.0f);
        
        // end examples

        p = { b, g, r };
        imgs[i].pixels[pixIndex] = p;
      }

      pixIndex++;
    }
  }

  printf("time to draw all images: %i ms\n\n", clock() - startTime);

  writeBmpFile(&imgs[0], "../output/front.bmp");
  writeBmpFile(&imgs[1], "../output/back.bmp");
  writeBmpFile(&imgs[2], "../output/top.bmp");
  writeBmpFile(&imgs[3], "../output/bottom.bmp");
  writeBmpFile(&imgs[4], "../output/left.bmp");
  writeBmpFile(&imgs[5], "../output/right.bmp");

  return 0;
}