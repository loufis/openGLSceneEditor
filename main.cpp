#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <GLUT/glut.h>
#include "model.h"
#include "glm/vec4.hpp"
#include "shaderManager.h"
#include "scene.h"
using namespace std;


scene* myScene;
int mode;
GLfloat translateX=0, translateZ=0;


void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    //glColor3f(0.9, 0.9, 0.9);
    
    myScene->draw();
    
    glFlush();
}





bool dragging;
int dragOriginX, dragOriginY;
glm::mat4x4 compiledRotationMatrix(1.0);

void mouse_click(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            dragging = true;
            dragOriginX = x;
            dragOriginY = y;
        }
        else
            dragging = false;
    }
}

void mouse_move(int x, int y)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(dragging)
    {

        
        glm::vec4 yRotationAxis(1, 0, 0, 1), xRotationAxis(0, 1, 0, 1);
        yRotationAxis = yRotationAxis* compiledRotationMatrix;
        xRotationAxis = xRotationAxis* compiledRotationMatrix;
        
        
        glRotatef((dragOriginY - y)*0.2, yRotationAxis.x, yRotationAxis.y, yRotationAxis.z);
        glRotatef((dragOriginX - x)*0.2, xRotationAxis.x, xRotationAxis.y, xRotationAxis.z);
        
        glm::mat4x4 temp;
        
        glGetFloatv(GL_MODELVIEW_MATRIX,glm::value_ptr(temp));
        compiledRotationMatrix *= temp;

        
        dragOriginX = x;
        dragOriginY = y;
    }

    glTranslatef(translateX, 0, translateZ);
    glMultMatrixf(glm::value_ptr(compiledRotationMatrix));


    glutPostRedisplay();
}

void keyboardArrowEventHandler(int key, int x, int y){
    if (key == GLUT_KEY_UP)
        translateZ += 100;
    else if (key == GLUT_KEY_DOWN)
        translateZ -= 100;
    else if (key == GLUT_KEY_LEFT)
        translateX += 100;
    else if (key == GLUT_KEY_RIGHT)
        translateX -= 100;
    
    mouse_move(0, 0);
}

void keyboardEventHandler(unsigned char key, int x, int y){
    if (key == 'o')
        myScene->init('o');
    else if (key == 'p')
        myScene->init('p');
    else if (key == 'l')
    {
        string temp;
        getline(cin, temp);
        if (!myScene->loadModel(temp)) cout << "Couldn't load model properly" << endl;
    }
    else if (key == 's')
    {
        myScene->saveState();
    }
    mouse_move(0, 0);
    
}



int main(int argc, char * argv[]) {
    
    string filePath;
    filePath = "/Users/Admin/Documents/openGLobjParser/openGLobjParser/scene";
    
    myScene = new scene(filePath);
    if (!myScene->success)
        cout << "Failed to Locate Scene File or File Had Invalid Format" << endl;
    else
    {
        
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_SINGLE);

        
        glutInitWindowSize(800, 500);
        glutInitWindowPosition(300, 200);
        glutCreateWindow("Object Viewer");
        glutDisplayFunc(draw);
        
        glEnable(GL_DEPTH_TEST);
        
        myScene->init('o');
        
        glutSpecialFunc(keyboardArrowEventHandler);
        glutKeyboardFunc(keyboardEventHandler);


        glutMouseFunc(mouse_click);
        glutMotionFunc(mouse_move);

        shaderManager h;
        h.makeVertexShader("/Users/Admin/Documents/openGLobjParser/openGLobjParser/test.vsh");
        h.makeFragmentShader("/Users/Admin/Documents/openGLobjParser/openGLobjParser/fragTest.fsh");
        GLuint program = h.makeShaderProgram();
         
        glUseProgram(program);
        
        glutMainLoop();

        glDeleteProgram(program);
    }
    
    delete myScene;
    return 0;
}









