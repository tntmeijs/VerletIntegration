#include "cloth.hpp"
#include "graphics/vertex.hpp"

void vi::Cloth::Generate(const ClothCreateInfo& info)
{
	// Need one more vertex to get the correct number of cells
	// The final cell needs count + 1 vertex to be a whole cell
	m_vertices.reserve((static_cast<std::size_t>(info.horizontal_cell_count) + 1) * (static_cast<std::size_t>(info.vertical_cell_count) + 1));

	// Generate vertices
	for (std::uint32_t y = 0; y <= info.vertical_cell_count; ++y)
	{
		for (std::uint32_t x = 0; x <= info.horizontal_cell_count; ++x)
		{
			Vertex vertex;
			vertex.position = { x, y, 0.0f };
			vertex.color = { x, y, 0.0f, 1.0f };

			m_vertices.push_back(vertex);
		}
	}

	// Add enough indices to form the grid (all zeros)
	m_indices.resize(static_cast<std::size_t>(info.horizontal_cell_count) * static_cast<std::size_t>(info.vertical_cell_count) * 6);
	
	// Generate indices (double for-loop from: https://catlikecoding.com/unity/tutorials/procedural-grid/)
	for (std::uint32_t ti = 0, vi = 0, y = 0; y < info.vertical_cell_count; y++, vi++)
	{
		for (std::uint32_t x = 0; x < info.horizontal_cell_count; x++, ti += 6, vi++)
		{
			std::size_t index = ti;

			m_indices[index] = vi;
			m_indices[index + 3] = m_indices[index + 2] = vi + 1;
			m_indices[index + 4] = m_indices[index + 1] = vi + info.horizontal_cell_count + 1;
			m_indices[index + 5] = vi + info.horizontal_cell_count + 2;
		}
	}
}

const std::vector<vi::Vertex>& vi::Cloth::GetVertices() const
{
	return m_vertices;
}

const std::vector<std::uint32_t>& vi::Cloth::GetIndices() const
{
	return m_indices;
}
