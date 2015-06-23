#include "GenUtils.h"
#include "OBJ.h"
#include <vector>

using namespace cocos2d;
using namespace std;

Mesh* GenUtils::OBJToCocos2dMesh(const OBJ* obj)
{
	OBJ::VertexDeclaration vertexDeclaration = obj->getVertexDeclaration();
	size_t perVertexSize = OBJ::getVertexSizeInBytes(vertexDeclaration) / sizeof(float);

	const vector<OBJ::Vertex>& objVertices = obj->getVertices();
	vector<float> vertices;
	for (unsigned i = 0; i < objVertices.size(); i++)
	{
		if (vertexDeclaration & OBJ::Position)
		{
			vertices.push_back(objVertices[i].vx);
			vertices.push_back(objVertices[i].vy);
			vertices.push_back(objVertices[i].vz);
		}
#if VERTEX_HAS_TEXTURE
		if (vertexDeclaration & OBJ::Texture)
		{
			vertices.push_back(objVertices[i].vtx);
			vertices.push_back(objVertices[i].vty);
		}
#endif
#if VERTEX_HAS_NORMAL
		if (vertexDeclaration & OBJ::Normal)
		{
			vertices.push_back(objVertices[i].vnx);
			vertices.push_back(objVertices[i].vny);
			vertices.push_back(objVertices[i].vnz);
		}
#endif
	}

	const vector<OBJ::Triangle>& objTriangles = obj->getTriangles();
	Mesh::IndexArray indices;
	for (unsigned i = 0; i < objTriangles.size(); i++)
	{
		indices.push_back(objTriangles[i].v1);
		indices.push_back(objTriangles[i].v2);
		indices.push_back(objTriangles[i].v3);
	}

	// Vertex Attributes
	vector<MeshVertexAttrib> attributes;
	MeshVertexAttrib attribute;
	attribute.type = GL_FLOAT; // it's always this
	if (vertexDeclaration & OBJ::Position)
	{
		attribute.vertexAttrib = GLProgram::VERTEX_ATTRIB_POSITION;
		attribute.size = 3;
		attribute.attribSizeBytes = attribute.size * sizeof(float);
		attributes.push_back(attribute);
	}
	if (vertexDeclaration & OBJ::Texture)
	{
		attribute.vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
		attribute.size = 2;
		attribute.attribSizeBytes = attribute.size * sizeof(float);
		attributes.push_back(attribute);
	}
	if (vertexDeclaration & OBJ::Normal)
	{
		attribute.vertexAttrib = GLProgram::VERTEX_ATTRIB_NORMAL;
		attribute.size = 3;
		attribute.attribSizeBytes = attribute.size * sizeof(float);
		attributes.push_back(attribute);
	}

	auto mesh = Mesh::create(vertices, perVertexSize, indices, attributes);
	//mesh->autorelease();
	return mesh;
}

OBJ* GenUtils::Cocos2dMeshToOBJ(const Mesh* mesh)
{
	const MeshVertexData* vertexData = mesh->getMeshIndexData()->getMeshVertexData();

	// get attributes
	OBJ::VertexDeclaration vertexDeclaration = OBJ::Position;
	int numAttributes = vertexData->getMeshVertexAttribCount();
	for (int attrib = 0; attrib < numAttributes; attrib++)
	{
		auto attribute = vertexData->getMeshVertexAttrib(attrib);
		switch (attribute.vertexAttrib)
		{
		case GLProgram::VERTEX_ATTRIB_POSITION:
			vertexDeclaration |= OBJ::Position;
			break;
		case GLProgram::VERTEX_ATTRIB_TEX_COORD:
			vertexDeclaration |= OBJ::Texture;
			break;
		case GLProgram::VERTEX_ATTRIB_NORMAL:
			vertexDeclaration |= OBJ::Normal;
			break;
		}
	}

	//get vertices
	vector<OBJ::Vertex> vertices;
	// Number of vertices
	int numVertices = vertexData->getVertexBuffer()->getVertexNumber();
	// Size of vertex in floats (# attribute fields)
	int vertexSize = vertexData->getVertexBuffer()->getSizePerVertex() / sizeof(float);
	// Pointer to VBO
	auto vertexVBO = vertexData->getVertexBuffer()->getVBO();
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	// Pointer to mapped vertex buffer
	float* vPtr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	for (int i = 0; i < numVertices; i++)
	{
		OBJ::Vertex vertex;
		int j = 0;
		for (int attrib = 0; attrib < numAttributes; attrib++)
		{
			auto attribute = vertexData->getMeshVertexAttrib(attrib);
			switch (attribute.vertexAttrib)
			{
			case GLProgram::VERTEX_ATTRIB_POSITION:
				assert(attribute.size >= 3);
				vertex.set_vx(vPtr[i * vertexSize + j]).set_vy(vPtr[i * vertexSize + j + 1]).set_vz(vPtr[i * vertexSize + j + 2]);
				break;
			case GLProgram::VERTEX_ATTRIB_TEX_COORD:
				assert(attribute.size >= 2);
				vertex.set_vtx(vPtr[i * vertexSize + j]).set_vty(vPtr[i * vertexSize + j + 1]);
				break;
			case GLProgram::VERTEX_ATTRIB_NORMAL:
				assert(attribute.size >= 3);
				vertex.set_vnx(vPtr[i * vertexSize + j]).set_vny(vPtr[i * vertexSize + j + 1]).set_vnz(vPtr[i * vertexSize + j + 2]);
				break;
			}
			j += attribute.size;
		}
		vertices.push_back(vertex);
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// triangles
	vector<OBJ::Triangle> triangles;
	const MeshIndexData* indexData = mesh->getMeshIndexData();
	// Number of indices
	int numIndices = indexData->getIndexBuffer()->getIndexNumber();
	// Number of triangles
	assert(numIndices % 3 == 0);
	int numTriangles = numIndices / 3;
	// Whether indices are shorts or ints
	auto indexFormat = indexData->getIndexBuffer()->getType();
	// Index buffer identifier
	auto indexVBO = indexData->getIndexBuffer()->getVBO();
	glBindBuffer(GL_ARRAY_BUFFER, indexVBO);
	// Pointer to mapped index buffer
	void* ivPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	// Short pointer
	unsigned short* iusPtr = (unsigned short*)ivPtr;
	// Int pointer
	unsigned int* iuiPtr = (unsigned int*)ivPtr;
	for (int i = 0; i < numTriangles; i++)
	{
		OBJ::Triangle triangle;
		if (indexFormat == IndexBuffer::IndexType::INDEX_TYPE_SHORT_16)
		{
			triangle.v1 = iusPtr[3 * i];
			triangle.v2 = iusPtr[3 * i + 1];
			triangle.v3 = iusPtr[3 * i + 2];
		}
		else // int
		{
			triangle.v1 = iuiPtr[3 * i];
			triangle.v2 = iuiPtr[3 * i + 1];
			triangle.v3 = iuiPtr[3 * i + 2];
		}
		triangles.push_back(triangle);
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	OBJ* obj = OBJ::create();
	obj->setVertices(vertices);
	obj->setTriangles(triangles);
	obj->setVertexDeclaration(vertexDeclaration);
	return obj;
}

Mesh* GenUtils::CreateGeometryInstancedMesh(int numInstances, int verticesPerInstance, const vector<int>& instanceTriangulation, const Vec2* texCoords)
{
	vector<float> vertices;
	for (unsigned i = 0; i < numInstances; i++)
	{
		for (unsigned j = 0; j < verticesPerInstance; j++)
		{
			vertices.push_back(0);
            vertices.push_back(i);
            vertices.push_back(j);
            vertices.push_back(texCoords[i].x);
            vertices.push_back(texCoords[i].y);
		}
	}

	Mesh::IndexArray indices;
	for (unsigned i = 0; i < numInstances; i++)
	{
		for (unsigned j = 0; j < instanceTriangulation.size(); j++)
		{
			indices.push_back(i * verticesPerInstance + instanceTriangulation[j]);
		}
	}

	// Vertex Attributes
	vector<MeshVertexAttrib> attributes;
	MeshVertexAttrib attribute;
	attribute.type = GL_FLOAT; // it's always this
	attribute.vertexAttrib = GLProgram::VERTEX_ATTRIB_POSITION;
	attribute.size = 3;
	attribute.attribSizeBytes = attribute.size * sizeof(float);
	attributes.push_back(attribute);

	attribute.vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
	attribute.size = 2;
	attribute.attribSizeBytes = attribute.size * sizeof(float);
	attributes.push_back(attribute);
	auto mesh = Mesh::create(vertices, 5, indices, attributes);
	//mesh->autorelease();
	return mesh;
}
