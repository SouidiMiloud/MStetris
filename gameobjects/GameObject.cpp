#include"GameObject.h"



GameObject::GameObject() {

}

GameObject::~GameObject() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void GameObject::setup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Position), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Position), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GameObject::render() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GameObject::fillIndices(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4) {
	
	fillIndices(v1, v2, v3);
	fillIndices(v1, v3, v4);
}

void GameObject::fillIndices(unsigned int v1, unsigned int v2, unsigned int v3) {
	indices.push_back(v1);
	indices.push_back(v2);
	indices.push_back(v3);
}

void GameObject::addVertex(Position pos) {
	vertices.push_back(pos);
}

int GameObject::getVerticesSize() {
	return vertices.size();
}