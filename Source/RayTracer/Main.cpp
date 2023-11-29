#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Color.h"
#include "Random.h"

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

		bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random01() * canvas.GetSize().x, random01() * canvas.GetSize().y}, {random01(), random01(), random01(), 1});
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}


	//<shutdown renderer>
	renderer.Shutdown();

		return 0;
}