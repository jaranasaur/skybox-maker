#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define _USE_MATH_DEFINES // for C
#include <math.h>
#include "image.h"

struct BmpFileHeader {
  // const char sig[2] = {'B','M'};
  int fileSize;
  int reserved = 0;
  int pixelArrayOffset = 54;
  int dibHeaderSize = 40;
  int imgWidth; // pixels
  int imgHeight; // pixels
  short planes = 1;
  short bitsPerPixel = 24;
  int compression = 0;
  int imgSize; // num bytes of pixel array
  int xPixelsPerMeter = 0;
  int yPixelsPerMeter = 0;
  int colorTable = 0;
  int importantColorCount = 0;
};

// nasty hardcoded 24 bit bmp, but works for now
void writeBmpFile(Image * img, const char *filePath) {
  BmpFileHeader bfh;
  bfh.imgWidth = img->width;
  bfh.imgHeight = img->height;
  int size = img->width * img->height;
  int widthOffset = img->width % 4;
  if (!widthOffset) {
    bfh.imgSize = size * 3;
  } else {
    bfh.imgSize = size * 3 + img->height * (4 - widthOffset);
  }
  bfh.fileSize = bfh.pixelArrayOffset + bfh.imgSize;
  // printf("offset: %i\n", bfh.pixelArrayOffset);
  // printf("size: %i\n", bfh.imgSize);
  // printf("fileSize: %i\n", bfh.fileSize);

  FILE *f = fopen(filePath, "wb");
  fwrite("BM", 2, 1, f);
  fwrite(&bfh, sizeof(bfh), 1, f);
  for (int i = 0; i < size; i += 1) {
    fwrite(img->pixels + i, 3, 1, f);
  }
  fclose(f);
}

#endif // BMP_H
