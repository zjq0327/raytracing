#pragma once

#include"global.h"

#include"scene.h"

class renderer
{
public:
    int spp = 10;
    int maxdepth = 10;
    void render(const scene& scene);

private:


    vec3 castRay(const ray& rayIn, int depth, const scene& world);

    inline double linear_to_gamma(double linear_component)
    {
        return sqrt(linear_component);
    }


    void printImage(const scene& scene, const std::vector<vec3>& framebuffer)
    {
        FILE* fp = fopen("binary.ppm", "wb");
        (void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
        for (auto i = 0; i < scene.height * scene.width; ++i) {
            static unsigned char color[3];
            color[0] = framebuffer[i].x();
            color[1] = framebuffer[i].y();
            color[2] = framebuffer[i].z();

            
            color[0] = linear_to_gamma(color[0]);
            color[0] = linear_to_gamma(color[1]);
            color[0] = linear_to_gamma(color[2]);


            color[0] = (char)(255 * clamp(0, 1, framebuffer[i].x()));
            color[1] = (char)(255 * clamp(0, 1, framebuffer[i].y()));
            color[2] = (char)(255 * clamp(0, 1, framebuffer[i].z()));

            fwrite(color, 1, 3, fp);
        }
        fclose(fp);
    }


};