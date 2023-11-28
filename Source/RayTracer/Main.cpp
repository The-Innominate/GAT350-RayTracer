#include <iostream>
#include "Renderer.h"
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
	}

	//<shutdown renderer>
	renderer.Shutdown();

		return 0;
}