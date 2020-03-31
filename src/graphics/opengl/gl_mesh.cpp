#include "gl_mesh.hpp"
#include "graphics/vertex.hpp"
#include "utility/log.hpp"

bool vi::gl::GLMesh::AllocateMesh(const MeshCreateInfo& info)
{
	m_has_indices = (info.index_data != nullptr);
	GenerateBuffers();

	glBindVertexArray(m_vao);
	
	// Vertex data
	m_vertex_count = info.vertex_data_size / sizeof(info.vertex_data[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, info.vertex_data_size, info.vertex_data, MeshUsageToOpenGLFlag(info.usage));

	// The order of these attributes is important, see "src/graphics/mesh.hpp" for more information
	glVertexAttribPointer(0, Vertex::POSITION_COMPONENT_COUNT,				GL_FLOAT, GL_FALSE, Vertex::POSITION_SIZE_BYTES,			reinterpret_cast<void*>(0));
	glVertexAttribPointer(1, Vertex::VERTEX_COLOR_COMPONENT_COUNT,			GL_FLOAT, GL_FALSE, Vertex::VERTEX_COLOR_SIZE_BYTES,		reinterpret_cast<void*>(Vertex::POSITION_SIZE_BYTES));
	glVertexAttribPointer(2, Vertex::TEXTURE_COORDINATE_COMPONENT_COUNT,	GL_FLOAT, GL_FALSE, Vertex::TEXTURE_COORDINATE_SIZE_BYTES,	reinterpret_cast<void*>(Vertex::POSITION_SIZE_BYTES + Vertex::VERTEX_COLOR_SIZE_BYTES));
	glVertexAttribPointer(3, Vertex::NORMAL_COMPONENT_COUNT,				GL_FLOAT, GL_FALSE, Vertex::NORMAL_SIZE_BYTES,				reinterpret_cast<void*>(Vertex::POSITION_SIZE_BYTES + Vertex::VERTEX_COLOR_SIZE_BYTES + Vertex::TEXTURE_COORDINATE_SIZE_BYTES));

	//#TODO: Allow vertex attributes to be disabled
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// Index data
	if (m_has_indices)
	{
		m_index_count = info.index_data_size / sizeof(info.index_data[0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.index_data_size, info.index_data, MeshUsageToOpenGLFlag(info.usage));
	}

	// Unbind all buffers to decrease the chances of keeping a buffer unintentionally bound in subsequent OpenGL calls
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_has_indices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	return true;
}

bool vi::gl::GLMesh::DeallocateMesh() const
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);

	if (m_has_indices)
	{
		glDeleteBuffers(1, &m_ebo);
	}

	return true;
}

void vi::gl::GLMesh::RecordDrawCommands() const
{
	glBindVertexArray(m_vao);

	if (m_has_indices)
	{
		// Draw using an index buffer
		glDrawElements(GL_TRIANGLES, static_cast<std::uint32_t>(m_index_count), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		// Draw without an index buffer
		glDrawArrays(GL_TRIANGLES, 0, static_cast<std::uint32_t>(m_vertex_count));
	}
}

void vi::gl::GLMesh::GenerateBuffers()
{
	// VAO
	glGenVertexArrays(1, &m_vao);

	// VBO
	glGenBuffers(1, &m_vbo);

	// EBO
	if (m_has_indices)
	{
		glGenBuffers(1, &m_ebo);
	}
}

GLenum vi::gl::GLMesh::MeshUsageToOpenGLFlag(MeshUsage usage) const
{
	switch (usage)
	{
		case vi::MeshUsage::MeshAlwaysStatic:
			return GL_STATIC_DRAW;
			break;
		case vi::MeshUsage::MeshOccasionalUse:
			return GL_STREAM_DRAW;
			break;
		case vi::MeshUsage::MeshDynamicUpdate:
			return GL_DYNAMIC_DRAW;
			break;
		default:
			LOG_WARN("Invalid mesh usage enum value specified. Unable to derrive OpenGL buffer usage. GL_STATIC_DRAW will be used.");
			return GL_STATIC_DRAW;
			break;
	}
}
