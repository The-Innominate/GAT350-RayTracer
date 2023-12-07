#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Color.h"
#include "Random.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"

using namespace std;

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void CornellBox(Scene& scene, const Canvas& canvas);
void FinalScene(Scene& scene, const Canvas& canvas);

int main(int, char**)
{
	const int width = 400;
	const int height = 300;
	const int samples = 200;
	const int depth = 6;

		//<create renderer>
		//<initialize renderer>
		//<create renderer window with size of 400, 300>
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("RayTracer", width, height);

	Canvas canvas(width, height, renderer);
	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

	FinalScene(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void CornellBox(Scene& scene, const Canvas& canvas)
{
	//This will be the Cornell Box scene
	//It will have a floor, ceiling, and 4 walls
	//The floor and ceiling will be Lambertian
	//The walls will be Lambertian
	//It will have a reflective sphere and a lambertain cube
	//The ceiling will have an emmisive light
	//The right wall will be green
	//The left wall will be red
	//The back wall will be white
	//The floor will be white
	//The ceiling will be white

	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(triangle));

	auto sphere = std::make_unique<Sphere>(glm::vec3{ 0, 0.5f, 0 }, 0.5f, std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.1f));
	scene.AddObject(std::move(sphere));

	auto ceiling = std::make_unique<Plane>(glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 5.0f));
	scene.AddObject(std::move(ceiling));

	auto leftWall = std::make_unique<Plane>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(leftWall));

	auto rightWall = std::make_unique<Plane>(glm::vec3{ 2, 0, 0 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0, 1, 0 }));
	scene.AddObject(std::move(rightWall));

	auto backWall = std::make_unique<Plane>(glm::vec3{ 0, 0, -2 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(color3_t{ 1, 1, 1 }));
	scene.AddObject(std::move(backWall));

	auto floor = std::make_unique<Plane>(glm::vec3{ 0, 0, 2 }, glm::vec3{ 0, 0, -1 }, std::make_shared<Lambertian>(color3_t{ 1, 1, 1 }));
	scene.AddObject(std::move(floor));
}

void FinalScene(Scene& scene, const Canvas& canvas)
{
	//This will be a combination of scene 1 and 2
	//It will have a floor, spheres randomly placed, and a cube + triangle
	//The cube and triangle will be a mesh
	//The cube will be reflective
	//The triangle will be emissive

	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(triangle));
}

