# Skybox/Cubemap Maker
This is a fun little project I worked on to generate some skyboxes that could be used in 3D applications/game engines. It's not too sophisticated at the moment and just dumps out six, uncompressed BMP files for each face of the inside of a cube. The code treats the skybox as 2x2x2 cube with the origin at the center. We loop over each pixel and then find that pixel's position in 3D space on the given face of an image. We then normalize the pixel's position so that it's distance from center of cube is 1. Another way to say this, is like projecting the pixel onto a sphere with a radius of 1 (a sphere that fits perfectly inside of our cube). With our new sphere-projected pixel position, we can then figure out a color for the pixel. For example, the further along the x-axis the pixel is, the more red we can make it.

The below example taken directly from the code:

    if (pix.x >= 0) r = pix.x * 255.0f;  // further along x = more red
    if (pix.y >= 0) b = pix.y * 255.0f;  // further along y = more blue
    if (pix.z >= 0) g = pix.z * 255.0f;  // further along z = more green

Since we're mapping the pixel to a sphere to figure out it's color, we will end up with a smooth, seamless blend from image to image when viewed in a 3D application. In other words, you won't be able to tell that you're actually looking at the inside of a cube, it will look like a sphere instead. There are a couple other examples in the code that do some other cool shading things.

The code is in the `src` directory and the images it spits out go to the `output` directory. BMP files are included in the output directory in this repo. I'm not including any specific instructions for compiling or running this project.