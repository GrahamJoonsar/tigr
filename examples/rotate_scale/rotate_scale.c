// Program to demonstrate the use of the following functions:
// - tigrClone
// - tigrGetRotated
// - tigrGetResized
// - tigrSetResized

#include "tigr.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

int main () {
    Tigr * screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Testing", 0);

    // Or whatever image you would like
    Tigr * img = tigrLoadImage("tigr.png");
    tigrSetResized(&img, 300, 300);
    Tigr * scale_img = tigrClone(img);
    Tigr * rotate_img = tigrClone(img);

    double scale_angle = 3.1415926535/4;
    double dir = 0.01;

    double rotate_angle = 0;

    while (!tigrClosed(screen)) {
        if (scale_angle < 0.01 || scale_angle > 3.1415926535/2 - dir){
            dir *= -1;
            scale_angle += dir;
        }
        scale_angle += dir;
        rotate_angle += 0.01;
        if (rotate_angle > 2*3.1415926535){
            rotate_angle -= 2*3.1415926535;
        }

        tigrClear(screen, tigrRGB(255, 255, 255));

        tigrFree(scale_img);
        tigrFree(rotate_img);
        // get img resized to this specific width and height
        scale_img = tigrGetResized(img, SCREEN_WIDTH * cos(scale_angle), SCREEN_HEIGHT * sin(scale_angle));
        // get img rotated at the angle you pass in
        rotate_img = tigrGetRotated(img, rotate_angle);
        
        tigrBlitAlpha(screen, scale_img, 0, 0, 0, 0, scale_img->w, scale_img->h, 1.0);
        tigrBlitAlpha(screen, rotate_img, SCREEN_WIDTH - (rotate_img->w/2 + 135), SCREEN_HEIGHT - (rotate_img->h/2 + 135), 0, 0, rotate_img->w, rotate_img->h, 1.0);

        tigrUpdate(screen);
    }

    tigrFree(img);
    tigrFree(scale_img);
    tigrFree(rotate_img);
    tigrFree(screen);

    return 0;
}