#include <iostream>
#include "util/b.h"
#include <math.h>

double hit_sphere(struct object o,  ray r) {
    vec3 oc = r.origin() - o.pos;
    // auto a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(oc, r.direction());
    double c = dot(oc, oc) - o.radius*o.radius;
    double discriminant = b*b - 4*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        double f=(-b - sqrt(discriminant) ) / (2.0);
        double g=(-b + sqrt(discriminant) ) / (2.0);
        return f;}
}
object *neareset_obj(struct object o[], ray r, int l){
    double ar[l];
    for( int i=0;i<l;i++){
        ar[i]=hit_sphere(o[i],r);
    }
    struct object *nearest=NULL;
    double min_distance=10000;
    for( int indx=0;indx<l;indx++){
        if (ar[indx]>0 ){
            min_distance=ar[indx];
            
            nearest=&o[indx];
            nearest->distance=ar[indx];
        }
    }
    return nearest;
}

// return reflected vector given incidental vec and normal vec
vec3 reflected(vec3 vec, vec3 axis){
    return vec - 2*dot(vec, axis)*axis;
}
int main() {
    int objLength=4;

    struct object objList[4]={
    {vec3(0,-9000,0),8995,vec3(0.1,1,0.5),vec3(0.6,0.6,0.6),vec3(1,1,1),150,1},
    
    {vec3(-4, 5, -10), 7,vec3(0.1, 0, 0.1),vec3(0.7, 0, 0.7),vec3(1,1,1),100,0.5},
    {vec3(5, 3, -4),  3,   vec3(0, 0.1, 0),  vec3(0, 0.6, 0),  vec3(1,1,1),100,0.5},
    {vec3(0, 1, 0),  1,  vec3(0.1, 0, 0),  vec3(0.7, 0, 0),  vec3(1,1,1),100,0.5},
    
    }; // all objectes in the enviroment
    
    struct light lit={vec3(-120,75,120),vec3(1,1,1),vec3(1,1,1),vec3(1,1,1)};// light source


    // intitalizing  up the screen
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera info
    double viewport_height = 8.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 2;


    vec3 camera (0, 1, 2);

    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);


    vec3 topLeft = camera - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    int maxDepth=3;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        double x=double(j)/(double)image_height;
        for (int i = 0; i < image_width; ++i) {

            double y=double(i)/(double)image_width;

            vec3 pixelLocation=topLeft +x*vertical+ y*horizontal;// pixel location relative to the bottom left corner

            vec3 origin = camera;

            vec3 direction=normalize(pixelLocation-camera);
            double reflection = 1;
            vec3 color(0,0,0);
            ray r(camera, direction);

            for( int ec =0; ec<maxDepth;ec++){
                object *ac =neareset_obj(objList,r,objLength);
                if (!ac){
                    break;
                }
                vec3 intersection=origin+ ac->distance*direction; 
           
                vec3 surfaceNormal=normalize(intersection - ac->pos);//normal vector at point of intersection
                vec3 shifted_point = intersection + 1e-4 * surfaceNormal; // shifting the intersection slightly for technical purposes
                 vec3 intersection_to_light = normalize(lit.pos - shifted_point);// vec pointing to light from the intersection point

                ray lRay(shifted_point,intersection_to_light);// new ray that points to the light from intersection
                double lRayDistance=(lit.pos-intersection).getLength();

                object *bc =neareset_obj(objList,lRay,objLength);// checking if the new ray intersects anyting
                if ( bc && bc->distance <lRayDistance){
                    break;
                }

                // the following calculation follows the Blinn-Phong reflection model equations
                vec3 illumination(0,0,0);

                illumination += ac->ambinet*lit.ambinet;

                illumination += (dot(intersection_to_light, surfaceNormal))*(ac->diffuse * lit.diffuse) ;

                vec3 intersection_to_camera = normalize(origin - intersection);
                vec3 bz = normalize(intersection_to_light + intersection_to_camera);
                illumination += (pow(dot(surfaceNormal, bz) , (ac->shiny / 4)))* (ac->specular * lit.specular); 

                // color reflection
                color += reflection*illumination;
                reflection *= ac->reflection;
                origin=shifted_point;

                direction=normalize(reflected(direction, surfaceNormal));
                r.setDirection(direction);
                r.setOrigin(shifted_point);
            }

            color.zeroOneNormazilize();
            // final color
            int ir =255*color.x();
            int ig =255*color.y();
            int ib =255*color.z();
                
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';

        }
    }
}

