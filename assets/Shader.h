#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

struct Color;

class Shader
{
public:
	Shader();
	~Shader();
	void activate();
	GLuint compileShader(const char* shader, GLenum shaderType);
	void passMatrix(const char* name, const float* matrix);
	void passColor(const char* name, Color color);

	GLuint programId;

private:
	const char* vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec2 position;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * vec4(position, 0, 1);
		}
	)";
	const char* fragmentShaderSource = R"(
		#version 330 core
		uniform vec3 color;
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(color, 1);
		}
	)";
};

#endif // !SHADER_H
