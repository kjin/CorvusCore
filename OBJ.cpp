#include "OBJ.h"

using namespace std;
using namespace cocos2d;

#define QUAD_HELPER(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4) addQuad(v1.set_position(x1, y1, z1).set_texture(vtx, vty), v2.set_position(x2, y2, z2).set_texture(vtx, vty), v3.set_position(x3, y3, z3).set_texture(vtx, vty), v4.set_position(x4, y4, z4).set_texture(vtx, vty))

OBJ* OBJ::create(VertexDeclaration vertexDeclaration)
{
	OBJ* obj = new OBJ(vertexDeclaration);
	obj->autorelease();
	return obj;
}

size_t OBJ::getVertexSizeInBytes(VertexDeclaration vertexDeclaration)
{
	size_t size = 0;
	if (vertexDeclaration & Position)
	{
		size += 3 * sizeof(REAL);
	}
	if (vertexDeclaration & Texture)
	{
		size += 2 * sizeof(REAL);
	}
	if (vertexDeclaration & Normal)
	{
		size += 3 * sizeof(REAL);
	}
	return size;
}

void OBJ::addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	// Calculate normals.
	// The results will be ignored if !VERTEX_HAS_NORMAL
	Vec3 vec1(v1.vx, v1.vy, v1.vz);
	Vec3 vec2(v2.vx, v2.vy, v2.vz);
	Vec3 vec3(v3.vx, v3.vy, v3.vz);
	Vec3 normal(vec2 - vec1);
	normal.cross(vec3 - vec1);
	normal.normalize();

	Triangle t;
	t.v1 = _vertices.size();
	_vertices.push_back(v1);
	_vertices[t.v1].set_normal(normal.x, normal.y, normal.z);
	t.v2 = _vertices.size();
	_vertices.push_back(v2);
	_vertices[t.v2].set_normal(normal.x, normal.y, normal.z);
	t.v3 = _vertices.size();
	_vertices.push_back(v3);
	_vertices[t.v3].set_normal(normal.x, normal.y, normal.z);
	_triangles.push_back(t);
}

void OBJ::addAABB(REAL x, REAL y, REAL z, REAL sx, REAL sy, REAL sz, REAL vtx, REAL vty)
{
	Vertex v1, v2, v3, v4;
	float x1 = x - sx / 2;
	float x2 = x + sx / 2;
	float y1 = y - sy / 2;
	float y2 = y + sy / 2;
	float z1 = z - sz / 2;
	float z2 = z + sz / 2;
	QUAD_HELPER(x1, y1, z1, x1, y2, z1, x2, y2, z1, x2, y1, z1);
	QUAD_HELPER(x1, y1, z2, x2, y1, z2, x2, y2, z2, x1, y2, z2);
	QUAD_HELPER(x1, y1, z1, x2, y1, z1, x2, y1, z2, x1, y1, z2);
	QUAD_HELPER(x1, y2, z1, x1, y2, z2, x2, y2, z2, x2, y2, z1);
	QUAD_HELPER(x1, y1, z1, x1, y1, z2, x1, y2, z2, x1, y2, z1);
	QUAD_HELPER(x2, y1, z1, x2, y2, z1, x2, y2, z2, x2, y1, z2);
}

void OBJ::print(std::ostream& ostr)
{
	if (_vertexDeclaration & Position) // Always true, but for the sake of consistency
	{
		for (size_t i = 0; i < _vertices.size(); i++)
		{
			ostr << "v " << _vertices[i].vx << " " << _vertices[i].vy << " " << _vertices[i].vz << std::endl;
		}
	}
#if VERTEX_HAS_TEXTURE
	if (_vertexDeclaration & Texture)
	{
		for (size_t i = 0; i < _vertices.size(); i++)
		{
			ostr << "vt " << _vertices[i].vtx << " " << _vertices[i].vty << std::endl;
		}
	}
#endif
#if VERTEX_HAS_NORMAL
	if (_vertexDeclaration & Normal)
	{
		for (size_t i = 0; i < _vertices.size(); i++)
		{
			ostr << "vn " << _vertices[i].vnx << " " << _vertices[i].vny << " " << _vertices[i].vnz << std::endl;
		}
	}
#endif
	for (size_t i = 0; i < _triangles.size(); i++)
	{
#if VERTEX_HAS_TEXTURE && VERTEX_HAS_NORMAL
		// Position, normal + texture
		if (!(_vertexDeclaration & ~(Position | Texture | Normal)))
		{
			ostr << "f " << (_triangles[i].v1 + 1) << "/" << (_triangles[i].v1 + 1) << "/" << (_triangles[i].v1 + 1) <<
				" " << (_triangles[i].v2 + 1) << "/" << (_triangles[i].v2 + 1) << "/" << (_triangles[i].v2 + 1) <<
				" " << (_triangles[i].v3 + 1) << "/" << (_triangles[i].v3 + 1) << "/" << (_triangles[i].v3 + 1) << std::endl;
		}
#endif
#if VERTEX_HAS_TEXTURE
		// Just position + texture
		if (!(_vertexDeclaration & ~(Position | Texture)))
		{
			ostr << "f " << (_triangles[i].v1 + 1) << "/" << (_triangles[i].v1 + 1) <<
				" " << (_triangles[i].v2 + 1) << "/" << (_triangles[i].v2 + 1) <<
				" " << (_triangles[i].v3 + 1) << "/" << (_triangles[i].v3 + 1) << std::endl;
		}
#endif
#if VERTEX_HAS_NORMAL
		// Just position + normal
		if (!(_vertexDeclaration & ~(Position | Normal)))
		{
			ostr << "f " << (_triangles[i].v1 + 1) << "//" << (_triangles[i].v1 + 1) <<
				" " << (_triangles[i].v2 + 1) << "//" << (_triangles[i].v2 + 1) <<
				" " << (_triangles[i].v3 + 1) << "//" << (_triangles[i].v3 + 1) << std::endl;
		}
#endif
		// Just position
		if (!(_vertexDeclaration & ~Position))
		{
			ostr << "f " << (_triangles[i].v1 + 1) << " " << (_triangles[i].v2 + 1) << " " << (_triangles[i].v3 + 1) << std::endl;
		}
	}
}

#undef QUAD_HELPER
