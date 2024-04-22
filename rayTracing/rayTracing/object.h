#pragma once

#include"global.h"

class hit_record {
public:
	point3 p;
	vec3 normal;
	float t;

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


	virtual bool hit(const ray& r, float& tnear, hit_record& rec)const = 0;

	virtual virtual ~object() = default;

};



