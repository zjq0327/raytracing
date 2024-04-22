#pragma once

#include"object.h"

#include "vec3.h"

class sphere : public object {
public:
    sphere(point3 _center, float _radius) : center(_center), radius(_radius) {}


    virtual bool hit(const ray& r, float& tnear, hit_record& rec)const override
    {
        vec3 oc = r.origin() - center;
        float a = r.direction().length_squared();
        float b = 2* dot(oc, r.direction());
        float c = oc.length_squared() - radius * radius;
        
        float t0, t1;

        if (!solveQuadratic(a, b, c, t0, t1)) return false;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;

        tnear = t0;
        rec.t = t0;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);


        return true;
    }

private:
    point3 center;
    float radius;
};
