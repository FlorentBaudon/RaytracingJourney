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
	int samples_per_pixel = 100;
	int max_bounces = 50;

	uint64_t lastTime = 0;
	uint64_t timeElapsed = 0;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1200, 1000 / aspect_ratio, "Raytracing");

	bool bSamplesEdit = false, bBounceEdit = false;

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
			RenderSettings settings(GetScreenWidth() - viewportOffset, GetScreenHeight(), aspect_ratio, samples_per_pixel, max_bounces);
			renderer->SetRendererSettings(settings);

			lastTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

			renderer->Render();

			timeElapsed = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - lastTime;
		}

		if (GuiValueBox(Rectangle{ 70, 70, 60, 32 }, "Samples", &samples_per_pixel, 0, 500, bSamplesEdit))	bSamplesEdit = !bSamplesEdit;

		if (GuiValueBox(Rectangle{ 70, 120, 60, 32 }, "Bounces", &max_bounces, 0, 500, bBounceEdit) )		bBounceEdit = !bBounceEdit;
		
		GuiDrawText(TextFormat("%i ms", timeElapsed), Rectangle{10, (float)GetScreenHeight() - 100, 180, 50}, TEXT_ALIGN_RIGHT, BLACK);
		
	

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
