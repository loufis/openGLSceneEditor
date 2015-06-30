#include "model.h"

louModel::louModel(const string& filename):transformationMatrix(1.0),normalIncluded(false),filePath(filename){
    
    ifstream inputFile(filename);
    
    if (inputFile.fail())
    {
        success = false;
        return;
    }
    else
    {
        success = true;
        for (int i=0; i<3; i++)
        {
            max[i] = -10000;
            min[i] = 10000;
        }
        
        
        string readLine;
        getline(inputFile, readLine);
        
        while (!inputFile.eof())
        {
            stringstream stream;
            stream.write(readLine.c_str(), readLine.size());
            
            string readPassage;
            stream >> readPassage;
            if (readPassage == "v")
            {
                GLfloat temp;
                stream >> temp;
                if (temp < min[0])
                    min[0] = temp;
                if (temp > max[0])
                    max[0] = temp;
                vertexList[0].push_back(temp);
                stream >> temp;
                if (temp < min[1])
                    min[1] = temp;
                if (temp > max[1])
                    max[1] = temp;
                vertexList[1].push_back(temp);
                stream >> temp;
                if (temp < min[2])
                    min[2] = temp;
                if (temp > max[2])
                    max[2] = temp;
                vertexList[2].push_back(temp);
                
            }
            else if (readPassage == "f")
            {
                int vertexIndex, normalIndex, textureIndex;
                vector <int> pushMeFaceList;
                vector <int> pushMeNormalList;
                vector <int> pushMeTextureList;
                char ignore;
                bool textureIncluded = false;
                stream >> vertexIndex;
                stream.get(ignore);
                if (ignore == '/')
                {
                    textureIncluded = true;
                    stream >> textureIndex;
                    stream.get(ignore);
                    
                    if (ignore == '/')
                    {
                        normalIncluded = true;
                        stream >> normalIndex;
                    }
                }
                
                
                while (!stream.eof())
                {
                    
                    pushMeFaceList.push_back(vertexIndex-1);
                    if (normalIncluded) pushMeNormalList.push_back(normalIndex-1);
                    if (textureIncluded) pushMeTextureList.push_back(textureIndex-1);
                    
                    stream >> vertexIndex;
                    if (textureIncluded)
                    {
                        stream.ignore();
                        stream >> textureIndex;
                        
                        if (normalIncluded)
                        {
                            stream.ignore();
                            stream >> normalIndex;
                        }
                    }
                }
                
                pushMeFaceList.push_back(vertexIndex-1);
                if (normalIncluded) pushMeNormalList.push_back(normalIndex-1);
                if (textureIncluded) pushMeTextureList.push_back(textureIndex-1);
                
                if (!normalIncluded)
                {
                    vec3 norm = normalize(cross
                              (vec3(vertexList[0][pushMeFaceList[2]], vertexList[1][pushMeFaceList[2]], vertexList[2][pushMeFaceList[2]])
                                    -vec3(vertexList[0][pushMeFaceList[1]], vertexList[1][pushMeFaceList[1]],vertexList[2][pushMeFaceList[1]])
                               ,vec3(vertexList[0][pushMeFaceList[1]], vertexList[1][pushMeFaceList[1]], vertexList[2][pushMeFaceList[1]])
                                    -vec3(vertexList[0][pushMeFaceList[0]], vertexList[1][pushMeFaceList[0]], vertexList[2][pushMeFaceList[0]])));
                    
                    neoNormalFaceList.push_back(norm);
                }
                
                stream.ignore();
                vertexFaceList.push_back(pushMeFaceList);
                if (normalIncluded) normalFaceList.push_back(pushMeNormalList);
                if (textureIncluded) textureFaceList.push_back(pushMeTextureList);
            }
            else if (readPassage == "vn")
            {
                GLfloat temp;
                vec3 t;
                stream >> temp;
                t.x = temp;
                stream >> temp;
                t.y = temp;
                stream >> temp;
                t.z = temp;
                
                normalList.push_back(t);
            }
            else if (readPassage == "vt")
            {
                GLfloat temp;
                vec3 t;
                stream >> temp;
                t.x = temp;
                stream >> temp;
                t.y = temp;
                stream >> temp;
                t.z = temp;
                
                textureList.push_back(t);
            }
            
            
            getline(inputFile, readLine);
        }
        
        
    }
    
}

void louModel::translateToCenter()
{
    GLfloat averageCoordinate[3] {0, 0, 0};
    for (int i=0; i<vertexList[0].size(); i++)
    {
        averageCoordinate[0] += vertexList[0][i];
        averageCoordinate[1] += vertexList[1][i];
        averageCoordinate[2] += vertexList[2][i];
    }
    
    averageCoordinate[0] /= vertexList[2].size();
    averageCoordinate[1] /= vertexList[2].size();
    averageCoordinate[2] /= vertexList[2].size();
    
    transformationMatrix[3][0] = -averageCoordinate[0];
    transformationMatrix[3][1] = -averageCoordinate[1];
    transformationMatrix[3][2] = -averageCoordinate[2];
}



void louModel::drawFaces(){
    
    for (int i=0; i<vertexFaceList.size(); i++)
    {
        glBegin(GL_POLYGON);
        if (!normalIncluded)
            for (int j=0; j<vertexFaceList[i].size(); j++)
            {
                
                glVertex3f(vertexList[0][vertexFaceList[i][j]], vertexList[1][vertexFaceList[i][j]], vertexList[2][vertexFaceList[i][j]]);
                glNormal3f(neoNormalFaceList[i].x, neoNormalFaceList[i].y, neoNormalFaceList[i].z);
            }
        else
            for (int j=0; j<vertexFaceList[i].size(); j++)
            {
                glVertex3f(vertexList[0][vertexFaceList[i][j]], vertexList[1][vertexFaceList[i][j]], vertexList[2][vertexFaceList[i][j]]);
                glNormal3f(normalList[normalFaceList[i][j]].x, normalList[normalFaceList[i][j]].y, normalList[normalFaceList[i][j]].z);
            }
        glEnd();
    }
    
    
    
}










