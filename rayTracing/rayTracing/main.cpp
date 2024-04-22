#include"render.h"
#include"sphere.h"


int main()
{

	scene world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	renderer r;
	r.render(world);

	return 0;
}
