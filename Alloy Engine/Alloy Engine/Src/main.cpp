#include <Windows.h>
#include "DebugSystem.h"
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"


int CALLBACK WinMain(HINSTANCE _app_instance, HINSTANCE _prev_instance, LPSTR _cmd_line, int _cmd_count)
{
	Window window("Alloy Engine", 1024, 576);
	Renderer renderer(window);
	Triangle test_triangle(renderer);

	DebugSystem debugger;
	debugger.CreateConsoleWindow();

	MSG msg = { nullptr };

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		//game update
		renderer.BeginFrame();
		test_triangle.Draw(renderer);
		renderer.EndFrame();
	}

	return 0;
}
