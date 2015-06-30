#ifndef __openGLobjParser__scene__
#define __openGLobjParser__scene__

#include <vector>
#include <string>
#include <fstream>
#include <GLUT/glut.h>
#include "glm/mat4x4.hpp"
#include "model.h"
using namespace std;

class scene {
private:
    vector<louModel*> modelList;
public:
    bool success;
    string filePath;
    
    scene(const string& filename);
    ~scene();
    void init(const char& command);
    void draw();
    void saveState();
    bool loadModel(const string& filename);
};

#endif 