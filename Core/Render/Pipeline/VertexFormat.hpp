#pragma once

namespace gaps
{
	enum class VertexAttributeId
	{
		Position,
		Color,
		TexCoord,
		Count
	};

	enum class VertexAttributeType
	{
		Float,
		Count
	};

	struct VertexLayout final
	{
		uint8_t attributeCount = 0u;
		VertexAttributeType attributeType = VertexAttributeType::UNINITIALIZED;
		bool bNormalized = false;
	};

	using VertexLayoutMap = std::unordered_map<VertexAttributeId, VertexLayout>;
}