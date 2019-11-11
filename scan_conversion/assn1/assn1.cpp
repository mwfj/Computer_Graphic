//
//		          Programming Assignment #1
//
//			        Victor Zordan
//
//
//
/***************************************************************************/

/* Include needed files */
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> // The GL Utility Toolkit (Glut) Header
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// #include <vector>
// #include <iostream>
// #include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Eillpse.h"
#include "Circle.h"
#define WIDTH 500
#define HEIGHT 500

int x_last, y_last;
ColorPicker cp(1.0,1.0,1.0); //store the color that the user pick
std::vector<Point> points; //store the history point
std::vector<Shape *> shapes;
char cur_key; //record the current mode.

/***************************************************************************/
// I move this function to Shape.h
// void write_pixel(int x, int y, double intensity)
// /* Turn on the pixel found at x,y */
// {

// 	glColor3f(intensity, intensity, intensity);
// 	glBegin(GL_POINTS);
// 	glVertex3i(x, y, 0);
// 	glEnd();
// }
/***************************************************************************/
void init_window()
/* Clear the image area, and set up the coordinate system */
{
	/* Clear the window */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);
}
/***************************************************************************/
void colorPickerUI(){
	for (int i = 450; i < 500; i++)
	{
		for (int j = 450; j < 500; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(1.0,0.0,0.0));
		}
		for (int j = 400; j < 449; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.0,1.0,0.0));
		}
		for (int j = 350; j < 399; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.0,0.0,1.0));
		}
		for (int j = 300; j < 349; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.16,0.89,0.69));
		}
		for (int j = 250; j < 299; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.77,1.0,0.35));
		}
		for (int j = 200; j < 249; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.17,1.0,0.45));
		}
		for (int j = 150; j < 199; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.5,1.0,0.5));
		}
		for (int j = 100; j < 159; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.13,1.0,0.84));
		}
		for (int j = 50; j < 99; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.17,0.56,0.55));
		}
		for (int j = 0; j < 49; j++)
		{
			Shape *color_shape = new Shape();
			color_shape->write_pixel(i,j,ColorPicker(0.5,0.5,0.6));
		}
	}
	
}
/***************************************************************************/

void display(void) // Create The Display Function
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen
	// write_pixel(x_last, y_last, 1.0);					//<-you can get rid of this call if you like
	// CALL YOUR CODE HERE
	colorPickerUI();
	if (x_last < 450)
	{
		std::cout<<x_last<<std::endl;
		Shape *shape = new Shape(x_last,y_last);
		shape->draw();
		// std::cout << "cur_key: " <<cur_key<< std::endl;
		for (std::vector<Shape *>::const_iterator it = shapes.cbegin(); it != shapes.cend(); it++)
		{
			(*it)->draw();		
		}
	}
	glutSwapBuffers(); // Draw Frame Buffer
}
/***************************************************************************/

void mouse(int button, int state, int x, int y)
{
	/* This function I finessed a bit, the value of the printed x,y should
   match the screen, also it remembers where the old value was to avoid multiple
   readings from the same mouse click.  This can cause problems when trying to
   start a line or curve where the last one ended */
	static int oldx = 0;
	static int oldy = 0;
	int mag;

	y *= -1;  //align y with mouse
	y += 500; //ignore
	mag = (oldx - x) * (oldx - x) + (oldy - y) * (oldy - y);
	if (mag > 20)
	{
		printf(" x,y is (%d,%d)\n", x, y);
		if (x>=450)
		{
			if(y>=450 && y<=500){
				cp.setR(1.0);
				cp.setG(0.0);
				cp.setB(0.0);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;
			}
			if(y<450 && y>=400){
				cp.setR(0.0);
				cp.setG(1.0);
				cp.setB(0.0);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;				
			}
			if (y>=350 && y<400)
			{
				cp.setR(0.0);
				cp.setG(0.0);
				cp.setB(1.0);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
			if(y<350 && y>=300){
				cp.setR(0.16);
				cp.setG(0.89);
				cp.setB(0.69);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
			if (y>=250 && y<300)
			{
				cp.setR(0.77);
				cp.setG(1.0);
				cp.setB(0.35);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
			if (y>=200 && y<250)
			{
				cp.setR(0.17);
				cp.setG(1.0);
				cp.setB(0.45);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
			if (y>=150 && y<200)
			{
				cp.setR(0.5);
				cp.setG(1.0);
				cp.setB(0.5);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
			if (y>=100 && y<150)
			{
				cp.setR(0.13);
				cp.setG(1.0);
				cp.setB(0.84);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
			if (y>=50 && y<100)
			{
				cp.setR(0.17);
				cp.setG(0.56);
				cp.setB(0.55);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
			if (y>0 && y<50)
			{
				cp.setR(0.5);
				cp.setG(0.5);
				cp.setB(0.6);
				std::cout<<"the current RGB is:"<<std::endl;
				std::cout<<"R:"<<cp.getR()<<"G:"<<cp.getG()<<"B:"<<cp.getB()<<std::endl;	
			}
		}else{
			points.push_back(Point(x, y));
		}
		
		std::cout << "current points list size: " << points.size() << std::endl;
	}
	oldx = x;
	oldy = y;
	x_last = x;
	y_last = y;
}

/***************************************************************************/
void keyboard(unsigned char key, int x, int y) // Create Keyboard Function
{

	cur_key = key;
	switch (key)
	{
	case 27:	 // When Escape Is Pressed...
		exit(0); // Exit The Program
		break;
	case '1': // stub for new screen
		printf("New screen\n");
		break;
	case 'l':
	{	
		std::cout << "Line mode on!!" << std::endl;
		std::vector<Point> temp_l;
		ColorPicker temp_c_l = cp;
		if (points.size()>=2)
		{	
			temp_l.swap(points);
		}
		Shape *temp_line = new Line(temp_l,temp_c_l);
		shapes.push_back(temp_line);
		// std::cout << "Line mode on!!" << std::endl;
		// points.clear();
		
	}
	break;
	case 'd':
	{
		std::cout << "clear the screen" << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen
		points.clear();
		shapes.clear();
		
	}
	break;
	case 't':
	{
		std::cout << "Triangle mode on!!" << std::endl;
		std::vector<Point> temp_t;
		if (points.size()>=3)
		{
			temp_t.swap(points);
		}
		Shape *temp_triangle = new Triangle(temp_t,cp);
		shapes.push_back(temp_triangle);
		// points.clear();
	}
	break;
	case 'r':
	{
		std::cout << "Rectangle mode on!!" << std::endl;
		std::vector<Point> temp_r;
		if (points.size()>= 2)
		{
			temp_r.swap(points);
		}
		Shape *temp_rectangle = new Rectangle(temp_r,cp);
		shapes.push_back(temp_rectangle);
		// points.clear();
	}
	break;
	case 'c':
	{
		std::cout << "Circle mode on!!" << std::endl;
		std::vector<Point> temp_c;
		if(points.size() >= 2){
			temp_c.swap(points);
		}
		Shape *temp_circle = new Circle(temp_c, cp);
		shapes.push_back(temp_circle);
	}
	break;
	case 'e':
	{
		std::cout << "Eillpse mode on!!" << std::endl;
		std::vector<Point> temp_e;
		if(points.size() >= 2){
			temp_e.swap(points);
		}
		Shape *temp_eillpse = new Eillpse(temp_e, cp);
		shapes.push_back(temp_eillpse);
	}
	break;
	default:
		break;
	}
}
/***************************************************************************/

int main(int argc, char *argv[])
{
	/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the escape key.						 
    */

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Computer Graphics");
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	init_window(); //create_window
	glutMainLoop(); // Initialize The Main Loop
}
