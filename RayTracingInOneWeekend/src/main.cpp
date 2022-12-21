#pragma once

#include "Renderer.h"
#include "color.h"

namespace RL {
	#include "raylib.h"
	#define RAYGUI_IMPLEMENTATION
	#include "raygui.h"
}


#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
	using namespace RL;
	Renderer* renderer = new Renderer();

	// image
	const double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = static_cast<int>(image_width / aspect_ratio);
	int samples_per_pixel = 20;
	int max_bounces = 4;

	uint64_t lastTime = 0;
	uint64_t timeElapsed = 0;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "Raytracing");

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		int viewportOffset = 200;

		image_width = GetScreenWidth() - viewportOffset;
		image_height = GetScreenHeight();

		GuiGroupBox(Rectangle{ 10, 10, 180, (float)GetScreenHeight() - 20}, "Render Settings");
		if (GuiButton(Rectangle{ 20, 20, 160, 32 }, "Render"))
		{
			using namespace std::chrono;
			RenderSettings settings(400, 200, 16.0 / 9.0, 20, 4);
			renderer->SetRendererSettings(RenderSettings(GetScreenWidth() - viewportOffset, GetScreenHeight(), 16.0 / 9.0, 20, 4));

			lastTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

			renderer->Render();

			timeElapsed = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - lastTime;
		}
		GuiDrawText(TextFormat("%i ms", timeElapsed), Rectangle{10, (float)GetScreenHeight() - 100, 180, 50}, TEXT_ALIGN_RIGHT, BLACK);
		//std::cout << "Time : " << timeElapsed << std::endl;
		
	

		for (int y = image_height - 1; y >= 0; --y)
		{
			for (int x = 0; x < image_width; x++)
			{
				if (renderer->colorBuffer)
				{
					vec3 c = create_color(renderer->colorBuffer[image_width * y + x], samples_per_pixel);
					Color col;
					col.r = c.x();
					col.g = c.y();
					col.b = c.z();
					col.a = 255;
					DrawPixel(x + viewportOffset, image_height-y, col);
				}
				else 
				{
					DrawPixel(x + viewportOffset, image_height- y, DARKGRAY);
				}
			}
		}
		

		EndDrawing();
	}

	std::cerr << "\Done\n";
}
