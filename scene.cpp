#include "scene.h"

scene::scene(const string& filename):filePath(filename)
{
    ifstream inputFile(filename);
    success = false;
    
    if (inputFile.fail())
        return;

    while (!inputFile.eof())
    {
        string modelPath;
        float x,y,z;
        getline(inputFile, modelPath);
        louModel* newModel = new louModel(modelPath);
        
        if (!newModel->success)
            return;
        
        modelList.push_back(newModel);
        inputFile >> x >> y >> z;
        
        newModel->transformationMatrix = glm::mat4x4(1.0);
        newModel->transformationMatrix[3][0] = x;
        newModel->transformationMatrix[3][1] = y;
        newModel->transformationMatrix[3][2] = z;
        
        inputFile.ignore();
    }
            
    success = true;

}

void scene::draw()
{
    for (int i=0; i<modelList.size(); i++)
    {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelList[i]->transformationMatrix));
        modelList[i]->drawFaces();
        glPopMatrix();
    }

}

void scene::init(const char& command)
{
    glClearColor (0.282353,0.2,0.564706, 0.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    
    GLfloat maxRotatingBorders = 0;
    
    for (int i=0; i<modelList.size(); i++)
    {
        maxRotatingBorders =
                    std::max(maxRotatingBorders,
                    std::max(std::max(abs(modelList[i]->min[0]),abs(modelList[i]->max[0]))+modelList[i]->transformationMatrix[3][0],
                    std::max(std::max(abs(modelList[i]->min[1]),abs(modelList[i]->max[1]))+modelList[i]->transformationMatrix[3][1],
                             std::max(abs(modelList[i]->min[2]),abs(modelList[i]->max[2]))+modelList[i]->transformationMatrix[3][2])));
    }
    
    if (command == 'o')
        glOrtho(-maxRotatingBorders, maxRotatingBorders, -maxRotatingBorders, maxRotatingBorders, maxRotatingBorders, -maxRotatingBorders);
    
    if (command == 'p')
    {
        gluPerspective(90, 1, 1, 2*maxRotatingBorders);
        
        gluLookAt(0, 0, maxRotatingBorders,
                0, 0, 0,
              0, -1, 0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool scene::loadModel(const string &filename)
{
    louModel* newModel = new louModel(filename);
    if (newModel->success)
    {
        modelList.push_back(newModel);
        return true;
    }
    return false;
}

void scene::saveState()
{
    ofstream outputFile(filePath);
    for (int i=0; i<modelList.size()-1; i++)
    {
        outputFile << modelList[i]->filePath << endl << modelList[i]->transformationMatrix[3][0] << ' ' << modelList[i]->transformationMatrix[3][1] << ' ' << modelList[i]->transformationMatrix[3][2] << endl;
    }
    outputFile << modelList[modelList.size()-1]->filePath << endl << modelList[modelList.size()-1]->transformationMatrix[3][0] << ' ' << modelList[modelList.size()-1]->transformationMatrix[3][1] << ' ' << modelList[modelList.size()-1]->transformationMatrix[3][2] << endl;
}

scene::~scene()
{
    for (int i=0; i<modelList.size(); i++)
        delete modelList[i];
}











