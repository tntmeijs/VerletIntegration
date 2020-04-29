#ifndef GRAPHICS_VERTEX_HPP
#define GRAPHICS_VERTEX_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include <cstddef>

namespace vi
{
	/**
	 * A vertex in a mesh contains a UV coordinate, position, normal, and color
	 */
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_coordinate;
		glm::vec4 color;

		// Useful when calculating offsets
		static constexpr std::size_t POSITION_SIZE_BYTES			= sizeof(glm::vec3);
		static constexpr std::size_t POSITION_COMPONENT_COUNT = 3;

		static constexpr std::size_t NORMAL_SIZE_BYTES				= sizeof(glm::vec3);
		static constexpr std::size_t NORMAL_COMPONENT_COUNT = 3;

		static constexpr std::size_t TEXTURE_COORDINATE_SIZE_BYTES = sizeof(glm::vec2);
		static constexpr std::size_t TEXTURE_COORDINATE_COMPONENT_COUNT = 2;

		static constexpr std::size_t VERTEX_COLOR_SIZE_BYTES		= sizeof(glm::vec4);
		static constexpr std::size_t VERTEX_COLOR_COMPONENT_COUNT = 4;
	};
}

#endif //! GRAPHICS_VERTEX_HPP
