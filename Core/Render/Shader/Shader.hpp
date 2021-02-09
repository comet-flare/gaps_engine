#pragma once

namespace gaps
{
	class Shader final
	{
	public:
		~Shader();

		void Load(const std::string& vertexPath, const std::string& fragmentPath);
		void Use();

		void SetUniform(const std::string& name, bool value) const;
		void SetUniform(const std::string& name, int32_t value) const;
		void SetUniform(const std::string& name, float value) const;
		void SetUniform(const std::string& name, float x, float y) const;
		void SetUniform(const std::string& name, const glm::vec2& v) const;
		void SetUniform(const std::string& name, float x, float y, float z) const;
		void SetUniform(const std::string& name, const glm::vec3& v) const;
		void SetUniform(const std::string& name, float x, float y, float z, float w) const;
		void SetUniform(const std::string& name, const glm::vec4& v) const;
		void SetUniform(const std::string& name, const glm::mat2& m) const;
		void SetUniform(const std::string& name, const glm::mat3& m) const;
		void SetUniform(const std::string& name, const glm::mat4& m) const;

		inline static const std::string DEFAULT_PATH = "Assets/Shaders/";

	private:
		void CheckCompileErrors(uint32_t shaderId, const std::string& type);
		void CheckLinkErrors();

		uint32_t programId = 0u;
	};
}