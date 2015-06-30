#ifndef __openGLobjParser__shaderManager__
#define __openGLobjParser__shaderManager__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <GLUT/GLUT.h>
using namespace std;


class shaderManager{
    vector<GLuint> vertexShaders, fragmentShaders;
    
public:
    string readFile(const char* filePath);
    void makeVertexShader(const char *filePath);
    void makeFragmentShader(const char *filePath);
    GLuint makeShaderProgram();
};




#endif