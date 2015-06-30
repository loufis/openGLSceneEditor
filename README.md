#openGLSceneEditor:

- This project consists of 3 main classes that encapsulate it's functionality:

	- louModel: 
			- A class that parses and stores data about a model from any obj file, including normals and texture coordinates. If the normals aren't present in the file, it takes the surface normal as the normal for each vertex. It also has a matrix that stores any transformations that are to be done on this model alone, such as translation.
			
			- translateToCenter() loads the transformation matrix with one that translates the object's center to the origin of the world space.

			- drawFaces() simply makes the calls to the openGL functions necessary to draw the model.

	- shaderManager: 

			- A singleton class that facilitates loading and running shaders. It is a simple class that has methods for creating vertex and fragment shaders and adding them to the pipeline. It's API is very straightforward as demonstrated in the main() function.

	- scene:

			- A singleton class that stores information about the current scene and provides an interface for adding models to the scene, saving the new scene state to the original scene file loaded and switching camera modes dynamically. The information it parses from the scene file is simply the path to the obj files to be loaded, and the x,y,z coordinates of their center.

- main.cpp demonstrates how to use the API of the scene and shader manager classes. It also contains event handlers for
the mouse to rotate the camera, for the arrow keys to navigate through the scene, and certain character keys to call
methods in the scene class.


####Screenshot Samples:

![Loading a new model into the scene](http://imgur.com/wncPjDQ.png)
![Orthographic view](http://imgur.com/dBtyoAZ.png)
![Perspective view](http://imgur.com/X6YgoOf.png)
![Specular light 1](http://imgur.com/u8mGHBr.png)
![Specular light 2](http://imgur.com/nRGDBb9.png)
