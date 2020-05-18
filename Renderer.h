#pragma once
#include "CoreLibs.h"
#include "cube.h"
#include "GameManager.h"
#include "ShaderManager.h"

// defines geometry of object in the scene (space ship, ufo, asteroid, etc.)
// geometry is shared among all instances of the same object type
typedef struct MeshGeometry {
    GLuint vertexBufferObject;   // identifier for the vertex buffer object
    GLuint elementBufferObject;  // identifier for the element buffer object
    GLuint vertexArrayObject;    // identifier for the vertex array object
    unsigned int numTriangles;   // number of triangles in the mesh
} MeshGeometry;

// parameters of individual objects in the scene (e.g. position, size, speed, etc.)
typedef struct Object {
    glm::vec3 position;
    float     size;
    bool      visible;

    std::string shaderName;

} Object;

class Renderer
{
public:


    //TODO zavislost na game manageru
    static void drawObject(Object& obj, MeshGeometry& mesh, Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
    {
        glUseProgram(0);

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), obj.position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(obj.size));
        //modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 0, 1));

        // send matrices to the vertex & fragment shader
        setTransformUniform(shader.PVMmatrixLocation, modelMatrix, viewMatrix, projectionMatrix);

        // draw geometry
        glBindVertexArray(mesh.vertexArrayObject);
        glDrawElements(GL_TRIANGLES, mesh.numTriangles * 3, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glUseProgram(0);
    }
    static bool initOpenGL(int winWidth, int winHeight)
    {
        //GLew init
        if (glewInit() != GLEW_OK)
        {
            fprintf(stderr, "Failed to init GLEW.\n");
            return false;
        }

        // Get info of GPU and supported OpenGL version
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

        glViewport(0, 0, winWidth, winHeight);
        glClearColor(0.0, 0.8, 0.3, 1.0);
        glEnable(GL_DEPTH_TEST); // Depth Testing

        //glDepthFunc(GL_LEQUAL); - bad thingies, mybe play wif later
        //glDisable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        return true;
    }
private:
    static void setTransformUniform(GLint PVMmatrixLocation, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
        glm::mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(PVMmatrixLocation, 1, GL_FALSE, glm::value_ptr(PVM));
    }
};
