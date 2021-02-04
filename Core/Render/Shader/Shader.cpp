#include <gapspch.hpp>
#include <Core/Render/Shader/Shader.hpp>
#include <Core/Debugger/Debug.hpp>

MOD("Core.Render.Shader");

namespace gaps
{
	Shader::~Shader()
	{
		glDeleteProgram(programId);
	}

	void Shader::Load(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;

		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragmentPath);

			std::stringstream vertexShaderStream;
			std::stringstream fragmentShaderStream;

			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();

			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			DEBUG_WARN("Shader file coudn't be read succesfully!");
		}

		const char* vertexShaderCode = vertexCode.c_str();
		const char* fragmentShaderCode = fragmentCode.c_str();

		uint32_t vertexId = 0u;
		uint32_t fragmentId = 0u;

		vertexId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexId, 1, &vertexShaderCode, nullptr);
		glCompileShader(vertexId);
		CheckCompileErrors(vertexId, "Vertex");

		fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentId, 1, &fragmentShaderCode, nullptr);
		glCompileShader(fragmentId);
		CheckCompileErrors(fragmentId, "Fragment");

		programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);
		glLinkProgram(programId);
		CheckLinkErrors();

		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
	}

	void Shader::Use()
	{
		glUseProgram(programId);
	}

	void Shader::SetUniform(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(programId, name.c_str()), static_cast<int32_t>(value));
	}

	void Shader::SetUniform(const std::string& name, int32_t value) const
	{
		glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
	}

	void Shader::SetUniform(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
	}

	void Shader::SetUniform(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(programId, name.c_str()), x, y);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec2& v) const
	{
		glUniform2fv(glGetUniformLocation(programId, name.c_str()), GL_TRUE, &v[0]);
	}

	void Shader::SetUniform(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec3& v) const
	{
		glUniform3fv(glGetUniformLocation(programId, name.c_str()), GL_TRUE, &v[0]);
	}

	void Shader::SetUniform(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(programId, name.c_str()), x, y, z, w);
	}

	void Shader::SetUniform(const std::string& name, const glm::vec4& v) const
	{
		glUniform4fv(glGetUniformLocation(programId, name.c_str()), GL_TRUE, &v[0]);
	}

	void Shader::SetUniform(const std::string& name, const glm::mat2& m) const
	{
		glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &m[0][0]);
	}

	void Shader::SetUniform(const std::string& name, const glm::mat3& m) const
	{
		glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &m[0][0]);
	}

	void Shader::SetUniform(const std::string& name, const glm::mat4& m) const
	{
		glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &m[0][0]);
	}

	void Shader::CheckCompileErrors(uint32_t shaderId, const std::string& type)
	{
		int32_t success = 0;
		char infoLog[1024];

		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
			DEBUG_WARN(type + " Shader compilation failed. InfoLog:\n" + std::string(infoLog));
		}
	}

	void Shader::CheckLinkErrors()
	{
		int32_t success = 0;
		char infoLog[1024];

		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, 1024, nullptr, infoLog);
			DEBUG_WARN("Linking failed. InfoLog:\n" + std::string(infoLog));
		}
	}
}