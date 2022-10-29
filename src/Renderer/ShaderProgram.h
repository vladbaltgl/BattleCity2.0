#pragma once
#include<string>
#include<glad/glad.h>
#include<glm/mat4x4.hpp>
namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader,const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompilled() { return m_isCompilled; }
		void use()const;
		void setInt(const std::string& name, const GLint value);
		void setMatrix4(const std::string& name, const glm::mat4& matrix);
		
		bool createShader(const std::string& source,const GLenum shaderType,  GLuint&shader_ID);
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram)noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram)noexcept;

	private:
		bool m_isCompilled = false;
		GLuint m_ID = 0;
	};

}