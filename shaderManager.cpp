#include "shaderManager.h"


string shaderManager::readFile(const char *filePath) {
    string content;
    ifstream fileStream(filePath);
    
    if(!fileStream.is_open())
        return "";
    
    
    string line = "";
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    
    fileStream.close();
    return content;
}

void shaderManager::makeVertexShader(const char *filePath) {
    
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    const char* cVertexProgram = readFile(filePath).c_str();
    glShaderSource(vertexShaderID, 1, &cVertexProgram, NULL);
    glCompileShader(vertexShaderID);
    
    
    
    GLint infoLogLength;
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    GLchar* strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, strInfoLog);
    
    cout << strInfoLog;
    
    vertexShaders.push_back(vertexShaderID);
}


void shaderManager::makeFragmentShader(const char *filePath) {
    
    
    
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cFragmentProgram = readFile(filePath).c_str();
    glShaderSource(fragmentShaderID, 1, &cFragmentProgram, NULL);
    glCompileShader(fragmentShaderID);
    
    
    GLint infoLogLength;
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    GLchar* strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, strInfoLog);
    
    cout << strInfoLog;
    

    fragmentShaders.push_back(fragmentShaderID);
}


GLuint shaderManager::makeShaderProgram() {
    
    GLuint shaderID = glCreateProgram();
    
    for (int i=0; i<vertexShaders.size(); i++)
        glAttachShader(shaderID, vertexShaders[i]);
    
    for (int i=0; i<fragmentShaders.size(); i++)
        glAttachShader(shaderID, fragmentShaders[i]);
    
    glLinkProgram(shaderID);
    return shaderID;
}







