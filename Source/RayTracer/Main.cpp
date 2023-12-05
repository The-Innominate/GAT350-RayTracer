#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Color.h"
#include "Random.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

using namespace std;

//int main(int argc, char* argv[])
//{
//	cout << "Hello World!" << endl;
//}

int main(int, char**)
{
	std::cout << "hello world!\n";

		//<create renderer>
		//<initialize renderer>
		//<create renderer window with size of 400, 300>
	Renderer renderer = Renderer();
	renderer.Initialize();
	renderer.CreateWindow("RayTracer", 400, 300);
	Canvas canvas(400, 300, renderer);
	Scene scene(20); // sky color could be set with the top and bottom color

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (std::rand() % 2 == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		//auto sphere = <create the sphere with the material>;
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-5, 5), random(-5, 5), random(-5, -10) }, random(0.5, 2), material);
		scene.AddObject(std::move(sphere));
	}


	scene.SetCamera(camera);

	// render scene 

	/*for (int i = 0; i < 10; i++) {
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-5, 5), random(-5, 5), random(-5, -10)}, random(0.5, 2), material);
		scene.AddObject(std::move(sphere));
	}*/

	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 50);
	canvas.Update();

	bool quit = false;
	while (!quit){
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}
		// create objects -> add to scene

		//renderer.PresentCanvas(canvas);
		//canvas.Clear({ 0, 0, 0, 1 });
		//for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random01() * canvas.GetSize().x, random01() * canvas.GetSize().y}, {random01(), random01(), random01(), 1});
		//canvas.Update();

		renderer.PresentCanvas(canvas);
	}


	//<shutdown renderer>
	renderer.Shutdown();

		return 0;
}