#pragma once
#include "Vertex.h"
#include <vector>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include "Transform.h"
#include "Mesh.h"

enum ShapeType
{
	SPHERE,
	CUBOID,
	PYRAMID,
	TETRAHEDRON
};


class Shape
	: public Transform
{
public:
	Shape() {}
	~Shape() {}

	Shape createShape(
		ShapeType type,
		float size = 1.0,
		float texturing = 2.0f,
		int resolution = 16,
		float width = 0.0f,
		float height = 0.0f,
		float depth = 0.0f);

	// Getters

	inline Mesh & getMesh() { return m_mesh; }
	inline std::vector<Vertex> & getVertices() { return m_vertices; }
	inline float & getSize() { return m_size; }

	void draw();

	// Setters
	void setVertices(std::vector<Vertex> & vertices) { m_vertices = vertices; }
	void setMesh(Mesh & mesh) { m_mesh = mesh; }
	void setSize(float & size) { m_size = size; }
	void setResolution(int & resolution) { m_resolution = resolution; }

private:
	std::vector<Vertex> createPyramid(float size, float texturing);
	std::vector<Vertex> createCuboid(float size, float width, float height, float depth, float texturing);
	std::vector<Vertex> createSphere(float radius, int resolution, bool invertormals = false);
	std::vector<Vertex> createTetrahedron(float size, float texturing);

	glm::vec3 computePlaneNormal(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC);

	Transform m_transform;
	std::vector<Vertex> m_vertices;
	Mesh m_mesh;
	glm::vec3 shapePosition, shapeRotation, shapeScale;
	float m_size;
	int m_resolution;
};

