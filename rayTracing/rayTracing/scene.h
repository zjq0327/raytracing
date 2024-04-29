#pragma once
#include<vector>

#include"object.h"

#include"camera.h"


class scene
{
public:
	int width = 400;
	int height = 300;
	camera camera;


	scene()
	{}

	scene(shared_ptr<object> object) { add(object); }

	void add(std::shared_ptr<object> object) 
	{ 
		bbox = aabb(bbox, object->bounding_box());
		objects.push_back(std::move(object));
	}

	const std::vector<std::shared_ptr<object> >& get_objects() const { return objects; }

private:
	std::vector<std::shared_ptr<object>> objects;
	aabb bbox;
};