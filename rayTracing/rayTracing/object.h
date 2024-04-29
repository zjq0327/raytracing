#pragma once
#include "global.h"



#include "aabb.h"

class material;


class hit_record {
public:
	point3 p;
	vec3 normal;
	float t;
	double u;
	double v;
	shared_ptr<material> mat;
	bool front_face;

	void set_face_normal(const ray& r, const vec3& outward_normal) {
		// Sets the hit record normal vector.
		// NOTE: the parameter `outward_normal` is assumed to have unit length.

		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class object
{
public:
	virtual bool hit(const ray& r, interval ray_t, hit_record& rec)const = 0;

	virtual aabb bounding_box() const = 0;

	virtual virtual ~object() = default;



};



