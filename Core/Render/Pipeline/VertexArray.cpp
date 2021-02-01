#include <gapspch.hpp>
#include <Core/Render/Pipeline/VertexArray.hpp>

namespace gaps
{
	void VertexArray::Submit()
	{
		glGenVertexArrays(1, &vaoId);
		glGenBuffers(1, &vboId);
		if (indexSize)
		{
			glGenBuffers(1, &iboId);
		}

		glBindVertexArray(vaoId);

		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, pVertexData, GL_STATIC_DRAW);

		if (indexSize)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, pIndexData, GL_STATIC_DRAW);
		}

		uint8_t totalAttributeCount = 0u;
		for (size_t i = 0; i < vertexLayoutMap.size(); i++)
		{
			totalAttributeCount += vertexLayoutMap[static_cast<VertexAttributeId>(i)].attributeCount;
		}

		uint32_t count = 0u;
		for (size_t i = 0; i < vertexLayoutMap.size(); i++)
		{
			VertexAttributeId key = static_cast<VertexAttributeId>(i);
			GLenum type = 0u;
			uint64_t size = 0ull;

			switch (vertexLayoutMap[key].attributeType)
			{
			case VertexAttributeType::Float:
				type = GL_FLOAT;
				size = sizeof(float);
				break;
			default:
				break;
			}

			glVertexAttribPointer
			(
				i,
				vertexLayoutMap[key].attributeCount,
				type,
				vertexLayoutMap[key].bNormalized,
				totalAttributeCount * size,
				reinterpret_cast<void*>(count * size)
			);

			glEnableVertexAttribArray(i);
			count += vertexLayoutMap[key].attributeCount;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(vaoId);
	}

	void VertexArray::Draw()
	{
		if (indexSize)
		{
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, vertexSize);
		}
	}

	void VertexArray::Release()
	{
		if (vaoId)
		{
			glDeleteVertexArrays(1, &vaoId);
		}

		if (vboId)
		{
			glDeleteBuffers(1, &vboId);
		}

		if (iboId)
		{
			glDeleteBuffers(1, &iboId);
		}

		pVertexData = nullptr;
		pIndexData = nullptr;
	}

	void VertexArray::SetVertexBufferData(void* pData, uint32_t size, const VertexLayoutMap& vertexLayoutMap)
	{
		if (pData != nullptr && size > 0u && vertexLayoutMap.size() > 0u)
		{
			pVertexData = pData;
			vertexSize = size;
			this->vertexLayoutMap = vertexLayoutMap;
		}
	}

	void VertexArray::SetIndexBufferData(void* pData, uint32_t size)
	{
		if (pData != nullptr && size > 0u)
		{
			pIndexData = pData;
			indexSize = size;
		}
	}

	bool VertexArray::HasIndexBuffer() const noexcept
	{
		return indexSize;
	}
}