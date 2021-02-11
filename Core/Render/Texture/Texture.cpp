#include <gapspch.hpp>
#include <Core/Render/Texture/Texture.hpp>
#include <Core/Debugger/Debug.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

MOD("Core.Render.Texture");

namespace gaps
{
	Texture::Texture(TextureDescriptor desc) noexcept
		:
		desc{ std::move(desc) }
	{
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &internalId);
	}

	bool Texture::Load(const std::string& filePath)
	{
		glGenTextures(1, &internalId);
		glBindTexture(GL_TEXTURE_2D, internalId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		int32_t width, height, channelCount;
		uint8_t* pData = stbi_load((DEFAULT_PATH + filePath).c_str(), &width, &height, &channelCount, 0);

		if (pData == nullptr)
		{
			DEBUG_WARN("Texture file doesn't exist!");
			return false;
		}
		else
		{
			if (channelCount == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
			}
			else if (channelCount == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
			}
			else
			{
				DEBUG_WARN("Channel count " + std::to_string(channelCount) + " not supported!");
				return false;
			}
		}

		bLoaded = true;
	}

	void Texture::Bind(uint32_t location)
	{
		if (bLoaded)
		{
			glActiveTexture(GL_TEXTURE0 + location);
			glBindTexture(GL_TEXTURE_2D, internalId);
		}
	}

	const TextureDescriptor& Texture::GetDescriptor() const noexcept
	{
		return desc;
	}

	bool Texture::IsLoaded() const noexcept
	{
		return bLoaded;
	}

	uint32_t Texture::GetInternalId() const noexcept
	{
		return internalId;
	}
}