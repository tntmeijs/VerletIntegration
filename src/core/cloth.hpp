#ifndef CORE_CLOTH_HPP
#define CORE_CLOTH_HPP

#include "glm/vec3.hpp"

#include <cstdint>
#include <vector>

namespace vi
{
	/** Forward declarations */
	struct Vertex;

	/**
	 * Single point in a cloth object, has a mass and a position
	 */
	struct ClothParticle
	{
		/** Mass of a single particle in the cloth */
		float mass;
		
		/** Last known position of this particle */
		glm::vec3 position;
	};

	/**
	 * Links multiple cloth particles together
	 */
	struct ClothFiber
	{
		/** Fiber attachment point A */
		ClothParticle link_start;

		/** Fiber attachment point B */
		ClothParticle link_end;

		/** Distance between cloth particles when no forces act on the cloth */
		float resting_distance;
	};

	/**
	 * All information needed to create a new cloth object
	 */
	struct ClothCreateInfo
	{
		/** Number of cloth particles to create horizontally */
		std::uint32_t horizontal_cell_count;

		/** Number of cloth particles to create vertically */
		std::uint32_t vertical_cell_count;

		/** Total mass of this cloth */
		float total_mass;

		/** Distance between cloth particles when no forces act on the cloth */
		float resting_distance;
	};

	/**
	 * Cloth simulation object
	 */
	class Cloth
	{
	public:
		/**
		 * Create a new cloth object
		 *
		 * @param info	Cloth create information
		 */
		void Generate(const ClothCreateInfo& info);

		/**
		 * Get all vertices needed to render this cloth
		 *
		 * @return Vector of vertices
		 */
		const std::vector<Vertex>& GetVertices() const;

		/**
		 * Get all indices needed to render this cloth
		 *
		 * @return Vector of indices
		 */
		const std::vector<std::uint32_t>& GetIndices() const;

	private:
		/** Fibers that make up the entire cloth */
		std::vector<ClothFiber> m_cloth;

		/** Vertices that represent the cloth */
		std::vector<Vertex> m_vertices;

		/** Indices that tie the vertices together */
		std::vector<std::uint32_t> m_indices;
	};
}

#endif //! CORE_CLOTH_HPP
