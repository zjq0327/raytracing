#pragma once

#include"vec3.h"

class camera
{
public:
	vec3 eyePos = point3(13, 2, 3);
	vec3 lookAt = point3(0, 0, 0);
	vec3 lookUp = vec3(0, 1, 0);
	float vfov = 20;
};