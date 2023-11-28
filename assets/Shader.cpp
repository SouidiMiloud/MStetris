#include"Shader.h"
#include"../Global.h"


Shader::Shader() {
	int success;
	char infoLog[512];
	GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	programId = glCreateProgram();
	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(programId, 512, NULL, infoLog);
		std::cout << "error " << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader(){}

void Shader::activate() {
	glUseProgram(programId);
}

GLuint Shader::compileShader(const char* shaderSource, GLenum shaderType) {
	int success;
	char infoLog[512];
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "error " << infoLog << std::endl;
	}
	return shader;
}

void Shader::passMatrix(const char* name, const float* matrix) {
	glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, GL_FALSE, matrix);
}

void Shader::passColor(const char* name, Color color) {
	glUniform3fv(glGetUniformLocation(programId, name), 1, color.toFloatPtr());
}