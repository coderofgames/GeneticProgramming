#ifndef SIMMPLE_EXAMPLE_H
#define SIMPLE_EXAMPLE_H

//#include "SimplePerceptron.h"
#include "Utils.h"
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h


class SimpleExample
{
protected:
	bool m_bDeleted = false;
public:

	SimpleExample(){}
	~SimpleExample(){
		if (m_bDeleted == false)
			this->Delete();
	}

	virtual void Initialize(){}
	virtual void Draw(){};
	virtual void Delete(){};
	virtual void keyboard(unsigned char key, int x, int y){};
	virtual void keyboardup(unsigned char key, int x, int y){};
	virtual void Special(int key, int x, int y){};
	virtual void reshape(GLsizei width, GLsizei height){}
	virtual void mouse(int button, int state, int x, int y){}
};



#endif