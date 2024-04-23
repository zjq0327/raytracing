#pragma once

#include"object.h"

#include "vec3.h"

class sphere : public object {
public:
    sphere(point3 _center, double _radius, shared_ptr<material> _material)
        : center(_center), radius(_radius), mat(_material) {}


    virtual bool hit(const ray& r, interval ray_t, hit_record& rec)const override
    {
        vec3 oc = r.origin() - center;
        float a = r.direction().length_squared();
        float b = 2* dot(oc, r.direction());
        float c = oc.length_squared() - radius * radius;
        
        float t0, t1;

        if (!solveQuadratic(a, b, c, t0, t1)) return false;
        if (!ray_t.surrounds(t0)) t0 = t1;
        if (!ray_t.surrounds(t0)) return false;

        rec.t = t0;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;


        return true;
    }

private:
    point3 center;
    float radius;
    shared_ptr<material> mat;
};
