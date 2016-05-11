#ifndef SIMPLE_GP_EXAMPLE_H
#define SIMPLE_GP_EXAMPLE_H


#include "Utils.h"
#include "SimpleExample.h"



#include <iostream>
#include <vector>
#include <string>

using std::vector;


class SimpleGPExample: public SimpleExample
{
public:

	int lifetime;  // How long should each generation live

	

	int lifecycle;          // Timer for cycle of generation
	int recordtime;         // Fastest time to target



	//int diam = 24;          // Size of target
	int width = 640;
	int height = 640;



	SimpleGPExample() : SimpleExample() {}

	~SimpleGPExample()
	{
	}

	void Delete() {
		
	}

	void SetWidthHeight(int w, int h)
	{
		width = w;
		height = h;
	}

	void Initialize() {
		
	}

	void Draw() {
		//	background(255);
		glClear(GL_COLOR_BUFFER_BIT);
		// Draw the start and target locations


		glutSwapBuffers();
		glutPostRedisplay();
	}

	void keyboard(unsigned char key, int x, int y){}
	void keyboardup(unsigned char key, int x, int y){}
	void Special(int key, int x, int y){};
	void mouse(int button, int state, int x, int y){}

	void reshape(GLsizei width, GLsizei height){}

	// Move the target if the mouse is pressed
	// System will adapt to new target
	void mousePressed() {
		//	target.location.x = mouseX;
		//	target.location.y = mouseY;
		//	recordtime = lifetime;
	}

};
#endif