#include "core/window.hpp"
#include "graphics/graphics_enums.hpp"
#include "graphics/mesh.hpp"
#include "graphics/renderer.hpp"
#include "utility/literals.hpp"
#include "utility/log.hpp"
#include "utility/timer.hpp"

#include <memory>

constexpr double PHYSICS_MAX_TIME = 0.25;
constexpr double PHYSICS_TIMESTEP = 50_Hz;

// Main loop fixed timestep logic from: https://gafferongames.com/post/fix_your_timestep/
int main()
{
	vi::Window window(1280, 720, "Tahar's Verlet Integration", vi::RenderingBackend::OpenGL);
	auto renderer = vi::Renderer::Create(vi::RenderingBackend::OpenGL);

	if (!renderer)
	{
		LOG_FATAL("Factory did not create a valid renderer object.");
		return -1;
	}

	//#TODO: Move this to a proper input manager
	window.OnKeyPressed = [&window](vi::Keycode key) {
		if (key == vi::Keycode::Escape)
		{
			window.Close();
		}
	};

	// Main loop timer
	vi::Timer timer;
	timer.Reset();

	// Stores "excess" frame time
	double accumulator = 0.0;

	// Attempt to initialize the renderer
	if (!renderer->Initialize(window.GetWidth(), window.GetHeight()))
	{
		LOG_FATAL("Renderer initialized unsuccessfully.");
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////
	// GRAPHICS API ABSTRATION TEST
	//////////////////////////////////////////////////////////////////////////

	float points[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	auto mesh = renderer->CreateMesh();
	mesh->AllocateMemory(points, sizeof(points), nullptr, 0);
	mesh->UploadToGPU();

	//////////////////////////////////////////////////////////////////////////
	// GRAPHICS API ABSTRATION TEST
	//////////////////////////////////////////////////////////////////////////

	// The engine will run until the window needs to close
	while (window.IsOpen())
	{
		window.PollInput();
		//#TODO: peek messages and handle user input

		double frame_time = timer.Duration();
		timer.Reset();

		// Prevent the physics from spiraling out of control when there is a massive lag spike during a frame
		if (frame_time > PHYSICS_MAX_TIME)
		{
			frame_time = PHYSICS_MAX_TIME;
		}

		// Enforce a fixed physics update step
		accumulator += frame_time;
		while (accumulator >= PHYSICS_TIMESTEP)
		{
			//#TODO: physics with a delta-time of PHYSICS_TIMESTEP seconds

			// Remove however many seconds of frame time was used to perform this update
			accumulator -= frame_time;
		}

		// Preset to the screen whenever we can using the interpolation to render the physics at the correct location
		double interpolation = accumulator / PHYSICS_TIMESTEP;
		interpolation;	// prevents an unused parameter warning

		//#TODO: render with interpolation
		renderer->PreRender();
		renderer->Render();
		renderer->PostRender();

		window.NextFrame();

		// Loop timer needs to update after all logic is done
		timer.Tick();
	}

	mesh->DeallocateMemory();

    return 0;
}
