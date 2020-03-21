#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <cstdint>

namespace vi
{
	class Window;

	class Renderer
	{
	public:
		Renderer(const Window& window);

		void Render(const Window& window);
	};
}

#endif //! RENDERER_HPP
