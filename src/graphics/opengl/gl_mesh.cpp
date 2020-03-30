#include "gl_mesh.hpp"

bool vi::gl::GLMesh::AllocateMemory(
	const void* const vertex_blob,
	std::size_t vertex_data_size,
	const void* const index_blob,
	std::size_t index_data_size)
{
	vertex_blob;
	vertex_data_size;
	index_blob;
	index_data_size;

	return false;
}

bool vi::gl::GLMesh::UploadToGPU() const
{
	return false;
}

bool vi::gl::GLMesh::DeallocateMemory() const
{
	return false;
}
