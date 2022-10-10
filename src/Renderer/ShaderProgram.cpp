#include "ShaderProgram.h"
#include<iostream>
namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vertexShaderID;
		if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
			std::cerr << "VERTEX SHADER compile time error" << std::endl;
			return;
		}
		GLuint fragmentShaderID;
		if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			std::cerr << "VERTEX SHADER compile time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);
		GLint succes;
		glGetProgramiv(m_ID, GL_LINK_STATUS,&succes);
		if (!succes) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR:SHADER: Link time error:\n" << infoLog << std::endl;
		}
		else {
			m_isCompilled = true;
		}
		


		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

	}


	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType,  GLuint& shader_ID) {
	
		shader_ID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shader_ID, 1, &code, nullptr);
		glCompileShader(shader_ID);

		GLint succes;
		glGetShaderiv(shader_ID,GL_COMPILE_STATUS,&succes);
		if (!succes)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shader_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR:SHADER: Compile time error:\n" << infoLog << std::endl;
			return false;
		}

			return true;


	
	};

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_ID);
	}
	

	void ShaderProgram::use()const{
		glUseProgram(m_ID);
	}
	ShaderProgram& ShaderProgram::operator= (ShaderProgram&& shaderProgram)noexcept{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompilled = shaderProgram.m_isCompilled;
		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompilled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram)noexcept {
		m_ID = shaderProgram.m_ID;
		m_isCompilled = shaderProgram.m_isCompilled;
		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompilled = false;
	}
}
