
#ifndef __openGLobjParser__model__
#define __openGLobjParser__model__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLUT/GLUT.h>
using namespace std;
using namespace glm;


class louModel{

    bool normalIncluded;
public:
    glm::mat4x4 transformationMatrix;
    
    bool success;
    string filePath;
    // contains a list of vertices
    vector<GLfloat> vertexList[3];
    vector<vec3> normalList;
    vector<vec3> textureList;
    
    
    
    // contains vector of indices of vertices
    vector<vector<int> > vertexFaceList;
    vector<vector<int> > normalFaceList;
    vector<vector<int> > textureFaceList;
    vector<vec3> neoNormalFaceList;
    
    GLfloat max[3], min[3];
    
    louModel(const string& filename);
    void drawFaces();
    void translateToCenter();
};


#endif