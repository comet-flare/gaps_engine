#pragma once

namespace gaps
{
	struct TextureDescriptor final
	{
		uint32_t width = 0u;
		uint32_t height = 0u;
		bool bGenerateMipmap = true;
	};

	class Texture final
	{
	public:
		explicit Texture(const TextureDescriptor& desc = {}) noexcept;
		~Texture();

		bool Load(const std::string& filePath);
		void Bind(uint32_t location = 0u);

		const TextureDescriptor& GetDescriptor() const noexcept;
		bool IsLoaded() const noexcept;
		uint32_t GetInternalId() const noexcept;

		inline static const std::string DEFAULT_PATH = "Assets/Textures/";

	private:
		TextureDescriptor desc = {};
		bool bLoaded = false;
		uint32_t internalId = 0u;
	};
}