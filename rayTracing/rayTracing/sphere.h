#pragma once

#include"object.h"

#include "vec3.h"

class sphere : public object {
public:
    sphere(point3 _center, double _radius, shared_ptr<material> _material)
        : m_center(_center), radius(_radius), mat(_material), is_moving(false) 
    {
        auto rvec = vec3(radius, radius, radius);
        bbox = aabb(m_center - rvec, m_center + rvec);
    }

    sphere(point3 _center1, point3 _center2, double _radius, shared_ptr<material> _material)
        : m_center(_center1), radius(_radius), mat(_material), is_moving(true)
    {
        center_vec = _center2 - _center1;
        auto rvec = vec3(radius, radius, radius);
        aabb box1(_center1 - rvec, _center1 + rvec);
        aabb box2(_center2 - rvec, _center2 + rvec);
        bbox = aabb(box1, box2);
    }

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec)const override
    {
        point3 center = is_moving ? center_run(r.time()) : m_center;

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

    aabb bounding_box() const override { return bbox; }


private:
    point3 m_center;
    float radius;   
    shared_ptr<material> mat;
    bool is_moving;
    vec3 center_vec; // 运动前后的中心距离
    aabb bbox;


    point3 center_run(double time) const {
        return m_center + time * center_vec;
    }
};
