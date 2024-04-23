#pragma once
#include<vector>

#include"object.h"

#include"camera.h"


class scene
{
public:
	int width = 1280;
	int height = 960;
	camera camera;


	scene()
	{}

	void add(std::shared_ptr<object> object) { objects.push_back(std::move(object)); }

	const std::vector<std::shared_ptr<object> >& get_objects() const { return objects; }

private:
	std::vector<std::shared_ptr<object>> objects;

};