#ifndef IMAGE_H
#define IMAGE_H

// 24-bit pixel
struct Pixel {
  unsigned char b, g, r;
};

struct Image {
  int width;
  int height;
  Pixel *pixels;
};

#endif // IMAGE_H
