#pragma once
#include<string>
#include<glad/glad.h>
namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader,const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompilled() { return m_isCompilled; }
		void use()const;
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