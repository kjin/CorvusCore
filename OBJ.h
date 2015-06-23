#ifndef _OBJ_H_
#define _OBJ_H_

#include <vector>
#include <iostream>
#include "cocos2d.h"

#define VERTEX_HAS_TEXTURE 1
#define VERTEX_HAS_NORMAL 1

#define REAL float

#define CHAIN_FUNC(f, x) Vertex& f(REAL x) { this->x = x; return *this; }

class OBJ : public cocos2d::Ref
{
public:
	typedef unsigned VertexDeclaration;
	const static VertexDeclaration Position = 1;
	const static VertexDeclaration Texture = 2;
	const static VertexDeclaration Normal = 4;

	static size_t getVertexSizeInBytes(VertexDeclaration vertexDeclaration);

    struct Vertex
    {
    public:
        // Position
        REAL vx;
        REAL vy;
        REAL vz;
        CHAIN_FUNC(set_vx, vx);
        CHAIN_FUNC(set_vy, vy);
        CHAIN_FUNC(set_vz, vz);
        Vertex& set_position(REAL vx, REAL vy, REAL vz) { this->vx = vx; this->vy = vy; this->vz = vz; return *this; }
#if VERTEX_HAS_TEXTURE
        // Texture
        REAL vtx;
        REAL vty;
        CHAIN_FUNC(set_vtx, vtx);
        CHAIN_FUNC(set_vty, vty);
        Vertex& set_texture(REAL vtx, REAL vty) { this->vtx = vtx; this->vty = vty; return *this; }
#else
        Vertex& set_texture(REAL vtx, REAL vty) { return *this; } //NOP
#endif
#if VERTEX_HAS_NORMAL
        // Normal
        REAL vnx;
        REAL vny;
        REAL vnz;
        CHAIN_FUNC(set_vnx, vnx);
        CHAIN_FUNC(set_vny, vny);
		CHAIN_FUNC(set_vnz, vnz);
        Vertex& set_normal(REAL vnx, REAL vny, REAL vnz) { this->vnx = vnx; this->vny = vny; this->vnz = vnz; return *this; }
#else
        Vertex& set_normal(REAL vnx, REAL vny, REAL vnz) { return *this; } //NOP
#endif
    };
    
    struct Triangle
    {
    public:
        unsigned v1;
        unsigned v2;
        unsigned v3;
    };
private:
	VertexDeclaration _vertexDeclaration;
	std::vector<Vertex> _vertices;
	std::vector<Triangle> _triangles;
protected:
	OBJ(VertexDeclaration vertexDeclaration)
		: _vertexDeclaration(vertexDeclaration | Position) // We gotta have position
	{
#if !VERTEX_HAS_TEXTURE
		_vertexDeclaration &= ~Texture;
#endif
#if !VERTEX_HAS_NORMAL
		_vertexDeclaration &= ~Normal;
#endif
	}
public:
	static OBJ* create(VertexDeclaration vertexDeclaration);

	static OBJ* create()
	{
		return create(Position);
	}

	VertexDeclaration getVertexDeclaration() const { return _vertexDeclaration; }

	const std::vector<Vertex>& getVertices() const { return _vertices; }

	const std::vector<Triangle>& getTriangles() const { return _triangles; }

	void setVertexDeclaration(VertexDeclaration vertexDeclaration)
	{
		_vertexDeclaration = vertexDeclaration;
#if !VERTEX_HAS_TEXTURE
		_vertexDeclaration &= ~Texture;
#endif
#if !VERTEX_HAS_NORMAL
		_vertexDeclaration &= ~Normal;
#endif
	}

	void setVertices(const std::vector<Vertex>& vertices) { _vertices = vertices; }

	void setTriangles(const std::vector<Triangle>& triangles) { _triangles = triangles; }

	void addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	// Add quad where v1, v2, v3, and v4 are either cw or ccw.
	void addQuad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex v4)
	{
		addTriangle(v1, v2, v3);
		addTriangle(v1, v3, v4);
	}

	// Add box size (sx, sy, sz) centered at (x, y, z) with a single texcoord.
	void addAABB(REAL x, REAL y, REAL z, REAL sx, REAL sy, REAL sz, REAL vtx, REAL vty);

	// Add box size (sx, sy, sz) centered at (x, y, z).
	void addAABB(REAL x, REAL y, REAL z, REAL sx, REAL sy, REAL sz)
	{
		addAABB(x, y, z, sx, sy, sz, 0, 0);
	}

	// Outputs OBJ as Waveform OBJ file to given stream
	void print(std::ostream& ostr);
};

#undef CHAIN_FUNC

#endif