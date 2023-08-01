# pragma once
#include <math.h>
#include <iostream>

// most of these are self-explanatory

class vec3 {
public:
    double dimensions[3];

    // User-defined constructor
    vec3(){
      dimensions[0]=0;
      dimensions[1]=0;
      dimensions[2]=0;
  }

  // User parametrized constructor Defined
  vec3(double x, double y, double z){
      dimensions[0]=x;
      dimensions[1]=y;
      dimensions[2]=z;

    }

    // Getter functions
    double x() const { return dimensions[0]; }
    double y() const { return dimensions[1]; }
    double z() const { return dimensions[2]; }

    void getData() {
        std::cout << dimensions[0] << std::endl;
        std::cout << dimensions[1] << std::endl;
        std::cout << dimensions[2] << std::endl;
    }

    double getLength() {
        return sqrt(dimensions[0] * dimensions[0] + dimensions[1] * dimensions[1] +
                    dimensions[2] * dimensions[2]);
    }

    // this function normailizes a vector between 1-0 in a specific way
    void zeroOneNormazilize(){
      for( int i =0;i<3;i++){
        if(dimensions[i]>1){
        dimensions[i]=1;
        }
        if(dimensions[i]<0){
        dimensions[i]=0;
        }
      }
    }
    // Setter functions
    vec3& operator+=(const vec3 &v) {
        dimensions[0] += v.dimensions[0];
        dimensions[1] += v.dimensions[1];
        dimensions[2] += v.dimensions[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        dimensions[0] *= t;
        dimensions[1] *= t;
        dimensions[2] *= t;
        return *this;
    }

};

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.dimensions[0] + v.dimensions[0], u.dimensions[1] + v.dimensions[1],
              u.dimensions[2] + v.dimensions[2]);
}
inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.dimensions[0] - v.dimensions[0], u.dimensions[1] - v.dimensions[1],
              u.dimensions[2] - v.dimensions[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.dimensions[0] * v.dimensions[0], u.dimensions[1] * v.dimensions[1],
              u.dimensions[2] * v.dimensions[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
  return vec3(t * v.dimensions[0], t * v.dimensions[1], t * v.dimensions[2]);
}
inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}
inline double dot(const vec3 &u, const vec3 &v) {
  return u.dimensions[0] * v.dimensions[0] + u.dimensions[1] * v.dimensions[1] +
         u.dimensions[2] * v.dimensions[2];
}
inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.dimensions[1] * v.dimensions[2] - u.dimensions[2] * v.dimensions[1],
              u.dimensions[2] * v.dimensions[0] - u.dimensions[0] * v.dimensions[2],
              u.dimensions[0] * v.dimensions[1] -
                  u.dimensions[1] * v.dimensions[0]);
}
inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}
inline vec3 normalize(vec3 v) {
    return v / v.getLength();}
inline vec3 unit_vector(vec3 v) {
    return v / v.getLength();
}
class ray {
    public:
        ray() {}
        ray(const vec3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}
        void setDirection(vec3 d){dir=d;}
        void setOrigin(vec3 o){orig=o;}
        vec3 origin() const  { return orig; }
        vec3 direction() const { return dir; }

        vec3 at(double t) const {
            return orig + t*dir;
        }

    public:
        vec3 orig;
        vec3 dir;
};
struct object{
  vec3 pos;
  double radius;
  vec3 ambinet;
  vec3 diffuse;
  vec3 specular;
  double shiny;
  double reflection;
  double distance;
} ;
struct light{
  vec3 pos;
  vec3 ambinet;
  vec3 diffuse;
  vec3 specular;

} ;



