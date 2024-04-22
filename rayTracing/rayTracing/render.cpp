#include"render.h"



bool trace(const ray& r, hit_record& record, const std::vector<std::shared_ptr<object>>& objects)
{

	float minTnear = infinity;
	bool isTrace = false;

	int count = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		float tnear;
		hit_record tmpRecord;
		if (objects[i]->hit(r, tnear, tmpRecord) == true)
		{
			isTrace = true;
			if (tnear < minTnear)
			{
				minTnear = tnear;
				record = tmpRecord;
				count++;

			}

		}
	}


	return isTrace;
}



// 开始支持光线弹射了
vec3 castRay(const ray& rayIn, const scene& world)
{
	const std::vector<std::shared_ptr<object>>& objects = world.get_objects();
	hit_record record;
	bool isTrace = trace(rayIn, record, objects);

	// 光线打到物体
	// 打到光源停止还没写 TODO
	if (isTrace == true)
	{
		return 0.5 * (record.normal + vec3(1, 1, 1));

	}

	vec3 unit_direction = unit_vector(rayIn.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}


void renderer::render(const scene& scene)
{
	std::vector<vec3> framebuffer(scene.width * scene.height);

	const camera& camera = scene.camera;
	const vec3& center = camera.eyePos;
	float imageAspectRatio = scene.width / (float)scene.height;

	float focal_length = (camera.eyePos - camera.lookAt).length();
	float theta = degrees_to_radians(scene.camera.vfov);
	float h = tan(theta / 2);
	float viewport_height = 2 * h * focal_length;
	float viewport_width = viewport_height * imageAspectRatio;

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	vec3 w = normalize(camera.eyePos - camera.lookAt);
	vec3 u = normalize(cross(camera.lookUp, w));
	vec3 v = cross(w, u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u = viewport_width * u;
	vec3 viewport_v = -viewport_height * v;

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	vec3 pixel_delta_u = viewport_u / scene.width;
	vec3 pixel_delta_v = viewport_v / scene.height;

	// Calculate the location of the upper left pixel.
	vec3 viewport_upper_left = center
		- (focal_length * w) - viewport_u / 2 - viewport_v / 2;
	vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	int curbuf = 0;
	// 打入光线
	for (int j = 0; j < scene.height; j++)
	{
		for (int i = 0; i < scene.width; i++)
		{
			for (int k = 0; k < spp; k++)
			{
				vec3 pixelCenter = pixel00_loc + pixel_delta_u * (i - 0.5 + random_float())
					+ pixel_delta_v * (j - 0.5 + random_float());
				vec3 direction = normalize(pixelCenter - center);

				ray r(center, direction);

				framebuffer[curbuf] += castRay(r, scene);
			}
			framebuffer[curbuf] = framebuffer[curbuf] / spp;
			curbuf++;
		}
	}

	// 写入文件中
	printImage(scene, framebuffer);
}