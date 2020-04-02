#pragma once
#include "CoreLibs.h"

// defines geometry of object in the scene (space ship, ufo, asteroid, etc.)
// geometry is shared among all instances of the same object type
typedef struct MeshGeometry {
    GLuint vertexBufferObject;   // identifier for the vertex buffer object
    GLuint elementBufferObject;  // identifier for the element buffer object
    GLuint vertexArrayObject;    // identifier for the vertex array object
    unsigned int numTriangles;   // number of triangles in the mesh
} MeshGeometry;



class Renderer
{
public:


};
