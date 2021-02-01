#pragma once

#include "VertexFormat.hpp"

namespace gaps
{
	class VertexArray final
	{
	public:
		void Submit();
		void Bind();
		void Draw();
		void Release();

		void SetVertexBufferData(void* pData, uint32_t size, const VertexLayoutMap& vertexLayoutMap);
		void SetIndexBufferData(void* pData, uint32_t size);

		bool HasIndexBuffer() const noexcept;

	private:
		uint32_t vaoId = 0u; // vertex array object's id
		uint32_t vboId = 0u; // vertex buffer object's id
		uint32_t iboId = 0u; // index buffer object's id
		uint32_t vertexSize = 0u;
		uint32_t indexSize = 0u;
		void* pVertexData = nullptr;
		void* pIndexData = nullptr;
		VertexLayoutMap vertexLayoutMap = {};
	};
}