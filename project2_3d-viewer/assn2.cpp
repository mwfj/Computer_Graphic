/**
*		          Programming Assignment #2
*
*			       @author Wufangjie Ma
*
*
**/
/***************************************************************************/

/* Include needed files */
//For MAC
#ifdef __APPLE__ 
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> // The GL Utility Toolkit (Glut) Header
#else 
//For Linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "Vector2f.h"
#include "Vector3f.h"
#include "ObjLoader.h"
#include "Matrix.h"
#include "Point.h"
#include "Shape.h"
#include "Triangle.h"
#define WIDTH 1080
#define HEIGHT 720
#define PI 3.14159265
#define DEGREE 20.000
#define NEGATIVE_DEGREE -20.000
#define MOVE_DISTANCE 30.000
#define NEGATIVE_MOVE_DISTANCE -30.000
#define SCALEUP 1.5
#define SCALEDOWN 0.5
#define PESPECTIVE_D 850.00


int x_last, y_last;

double distance_x = WIDTH/2; // record the distance between current x and original x
double distance_y = HEIGHT/2;// record the distance between current y and original y

bool isTranslation = false;
bool isRotate = false;
bool isScale = false;
bool isPerspective =false;

std::string path_name = "./model1.obj"; // hte path of OBJ file
ObjLoader obj(path_name);
std::vector<Vector3f> obj_vertexs;
std::vector<Vector3f> current_vetexs;
std::vector<int> vertex_index;
// std::vector<Vector3f> normals;
// std::vector<int> normal_indices;

// std::vector<Vector2f> textures;
// std::vector<int> texture_indices;

std::vector<std::vector<double> > diagonal_matrix(4, std::vector<double>(4));
std::vector< std::vector< std::vector<double> > > point_list; //store all the vertex point in Orthogonal mode according to the face information from obj file
std::vector< std::vector< std::vector<double> > > p_point_list; //store all the vertex point in Perspective mode
/***************************************************************************/
void Pespective();
void Normalize();
void move(double,double,double);
void scale(double);
void scale_3d(double, double, double);
// Parse OBJ file
void getOBJData(){

	obj.parsedOBJFile();
	obj.shape_normalize();
	obj_vertexs= obj.getVertex_list();
	vertex_index = obj.get_Vertex_indices();
	point_list = std::vector< std::vector< std::vector<double> > >(
					vertex_index.size(),
					std::vector< std::vector<double> >(4,std::vector<double>(1))
		);

	p_point_list = std::vector< std::vector< std::vector<double> > >(
					vertex_index.size(),
					std::vector< std::vector<double> >(4,std::vector<double>(1))
		);
}

void initialize_matrix(){
	int row = diagonal_matrix.size();
	int col = diagonal_matrix[0].size();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == j)
			{
				diagonal_matrix[i][j] = 1.000;
			}else{
				diagonal_matrix[i][j] = 0;
			}
		}
	}
	// for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < col; j++)
    //     {
    //         std::cout<<diagonal_matrix[i][j]<<", ";
    //     } 
    //     std::cout<<std::endl;
    // }
	
}
// Normalize and move object to the center of the screen
void processPoinstList(){
	
	for (int k = 0; k < vertex_index.size(); k++)
	{
		double x_axis = obj_vertexs[vertex_index[k]-1].getX();
		double y_axis = obj_vertexs[vertex_index[k]-1].getY();
		double z_axis = obj_vertexs[vertex_index[k]-1].getZ();
		double p = 1.000;
		std::vector<std::vector<double> > p_matrix(4, std::vector<double>(1));
		p_matrix[0][0] = x_axis;
		p_matrix[1][0] = y_axis;
		p_matrix[2][0] = z_axis;
		p_matrix[3][0] = 1.000;
		int row = p_matrix.size();
		int col = p_matrix[0].size();
		// std::cout<<"row: "<<row<<", "<<"column: "<<col<<std::endl;
		point_list[k] = p_matrix;

		// for (int i = 0; i < row; i++)
		// {
		// 	for (int j = 0; j < col; j++)
		// 	{
		// 		point_list[k][i][j] = p_matrix[i][j];
		// 		// std::cout<<point_list[k][i][j]<<"	"<<std::endl;
		// 	}
		// 	// std::cout<<std::endl;
			
		// }
		// std::cout<<"--------------------------------------------"<<std::endl;
	}
	Normalize();
	move(WIDTH/2,HEIGHT/2,0.0);
	
}

// Pespective mode
void Pespective(){

	for (int k = 0; k < vertex_index.size(); k++)
	{
		p_point_list[k] = point_list[k];	
	}
	
	move(-distance_x,-distance_y,0.0);
	
	for (int k = 0; k < vertex_index.size(); k++)
	{
		// point_list[k] =  m_.dotProduct(p_view_matrix, point_list[k]);
		double temp_z = p_point_list[k][2][0];
		double temp_y = p_point_list[k][1][0];
		double temp_x = p_point_list[k][0][0];
		double temp_p = p_point_list[k][3][0];
		p_point_list[k][0][0] =( (PESPECTIVE_D-150)/(PESPECTIVE_D-temp_z) )*temp_x;
		p_point_list[k][1][0] =( (PESPECTIVE_D-150)/(PESPECTIVE_D-temp_z) )*temp_y;
		p_point_list[k][2][0] =( (PESPECTIVE_D-150)/(PESPECTIVE_D-temp_z) )*temp_z;
		p_point_list[k][3][0] =( (PESPECTIVE_D-150)/(PESPECTIVE_D-temp_z) )*temp_p;
	}
	move(distance_x,distance_y,0.0);
}
// Scale x,y,z with the same value
void scale(double s){
	std::vector<std::vector<double> > scale_m(4, std::vector<double>(4));
	int scale_row = scale_m.size();
	int scale_col = scale_m[0].size();

	for (int i = 0; i < scale_row; i++)
	{
		for (int j = 0; j < scale_col; j++)
		{
			if ((i== 0 && j == 0) || (i== 1 && j == 1) || (i== 2 && j == 2))
			{
				scale_m[i][j] = s;
			}else if(i== 3 && j == 3){
				scale_m[i][j] = 1.000;
			}else{
				scale_m[i][j] = 0;
			}
		}
	}
	
	std::cout<<"--------------------------------------------------"<<std::endl;
	for (int i = 0; i < scale_row; i++)
    {
        for (int j = 0; j < scale_col; j++)
        {
            std::cout<<scale_m[i][j]<<", ";
        } 
        std::cout<<std::endl;
    }
	std::cout<<"--------------------------------------------------"<<std::endl;
	move(-distance_x,-distance_y,0.0);
	Matrix m_;
	if (isPerspective){

		for (int k = 0; k < vertex_index.size(); k++)
		{
			p_point_list[k] =  m_.dotProduct(scale_m, p_point_list[k]);
		}
	}else{

		for (int k = 0; k < vertex_index.size(); k++)
		{
			point_list[k] =  m_.dotProduct(scale_m, point_list[k]);
		}
	}
	move(distance_x,distance_y,0.0);
}
// scale x, y, z with different value
void scale_3d(double x_,double y_, double z_){
	std::vector<std::vector<double> > scale_m(4, std::vector<double>(4));
	int scale_row = scale_m.size();
	int scale_col = scale_m[0].size();

	for (int i = 0; i < scale_row; i++)
	{
		for (int j = 0; j < scale_col; j++)
		{
			if (i== 0 && j == 0)
			{
				scale_m[i][j] = x_;
			}else if(i== 1 && j == 1){

				scale_m[i][j] = y_;
			}else if(i== 2 && j == 2){

				scale_m[i][j] = z_;
			}else if(i== 3 && j == 3){
				scale_m[i][j] = 1.000;
			}else{
				scale_m[i][j] = 0;
			}
		}
	}
	
	std::cout<<"--------------------------------------------------"<<std::endl;
	for (int i = 0; i < scale_row; i++)
    {
        for (int j = 0; j < scale_col; j++)
        {
            std::cout<<scale_m[i][j]<<", ";
        } 
        std::cout<<std::endl;
    }
	std::cout<<"--------------------------------------------------"<<std::endl;
	move(-distance_x,-distance_y,0.0);
	Matrix m_;
	if (isPerspective){

		for (int k = 0; k < vertex_index.size(); k++)
		{
			p_point_list[k] =  m_.dotProduct(scale_m, p_point_list[k]);
		}
	}else{

		for (int k = 0; k < vertex_index.size(); k++)
		{
			point_list[k] =  m_.dotProduct(scale_m, point_list[k]);
		}
	}
	move(distance_x,distance_y,0.0);

}
// Move object
void move(double dx, double dy, double dz){
	std::vector<std::vector<double> > matrix_move(4, std::vector<double>(4,0));
	int move_row = matrix_move.size();
	int move_col = matrix_move[0].size();
	for (int i = 0; i < move_row; i++)
	{
		for (int j = 0; j < move_col; j++)
		{
			if (i == j)
			{
				matrix_move[i][j] = 1;
			}else if(i == 0 && j ==3){
				matrix_move[i][j] = dx;
			}else if(i==1 && j ==3)
			{
				matrix_move[i][j] = dy;
			}else if(i==2 && j ==3)
			{
				matrix_move[i][j] = dz;
			}else{
				matrix_move[i][j] = 0;
			}
		}
	}
	// std::cout<<"--------------------------------------------------"<<std::endl;
	// for (int i = 0; i < move_row; i++)
    // {
    //     for (int j = 0; j < move_col; j++)
    //     {
    //         std::cout<<matrix_move[i][j]<<", ";
    //     } 
    //     std::cout<<std::endl;
    // }
	// std::cout<<"--------------------------------------------------"<<std::endl;
	Matrix m_;
	if (isPerspective){

		for (int k = 0; k < vertex_index.size(); k++)
		{
			p_point_list[k] =  m_.dotProduct(matrix_move, p_point_list[k]);
		}
	}else{

		for (int k = 0; k < vertex_index.size(); k++)
		{
			point_list[k] =  m_.dotProduct(matrix_move, point_list[k]);
		}
	}
}

// Doing the nomalize operation
void Normalize(){
	std::vector<std::vector<double> > normalize_matrix(4, std::vector<double>(4,0));
	int n_row = normalize_matrix.size();
	int n_col = normalize_matrix[0].size();
	double dx = obj.getCenter().getX();
	double dy = obj.getCenter().getY();
	double dz = obj.getCenter().getZ();
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			if (i == j)
			{
				normalize_matrix[i][j] = 1;
			}else if(i == 0 && j ==3){
				normalize_matrix[i][j] = -dx;
			}else if(i==1 && j ==3)
			{
				normalize_matrix[i][j] = -dy;
			}else if(i==2 && j ==3)
			{
				normalize_matrix[i][j] = -dz;
			}else{
				normalize_matrix[i][j] = 0;
			}
		}
	}
	// std::cout<<"--------------------------------------------------"<<std::endl;
	// for (int i = 0; i < move_row; i++)
    // {
    //     for (int j = 0; j < move_col; j++)
    //     {
    //         std::cout<<matrix_move[i][j]<<", ";
    //     } 
    //     std::cout<<std::endl;
    // }
	// std::cout<<"--------------------------------------------------"<<std::endl;
	Matrix m_;
	for (int k = 0; k < vertex_index.size(); k++)
	{
		point_list[k] =  m_.dotProduct(normalize_matrix, point_list[k]);
	}
}

// Rotation object with Z axis
void rotationZ(double degree){
	std::vector< std::vector<double> > rotation_matrix_z(4, std::vector<double>(4));
	int rotation_row = rotation_matrix_z.size();
	int rotation_col = rotation_matrix_z[0].size();
	for (int i = 0; i < rotation_row; i++)
	{
		for (int j = 0; j < rotation_col; j++)
		{
			if ( (i ==0 && j == 0) || (i== 1 && j== 1) )
			{
				rotation_matrix_z[i][j] = cos( (degree*PI)/180 );
			}else if ( (i== 2 && j == 2) || (i == 3 && j == 3) )
			{
				rotation_matrix_z[i][j] = 1;
			}else if(i == 0 && j == 1 ){
				rotation_matrix_z[i][j] = -sin( (degree*PI)/180 );
			}else if(i == 1 && j == 0){
				rotation_matrix_z[i][j] = sin( (degree*PI)/180 );
			}else{
				rotation_matrix_z[i][j] = 0;
			}
		}	
	}
	move(-distance_x,-distance_y,0.0);
	Matrix m_;
	if (isPerspective){

		for (int k = 0; k < vertex_index.size(); k++)
		{
			p_point_list[k] =  m_.dotProduct(rotation_matrix_z, p_point_list[k]);
		}
	}else{

		for (int k = 0; k < vertex_index.size(); k++)
		{
			point_list[k] =  m_.dotProduct(rotation_matrix_z, point_list[k]);
		}
	}
	move(distance_x,distance_y,0.0);

	// std::cout<<"--------------------------------------------------"<<std::endl;
	// for (int i = 0; i < rotation_row; i++)
    // {
    //     for (int j = 0; j < rotation_col; j++)
    //     {
    //         std::cout<<rotation_matrix_z[i][j]<<", ";
    //     } 
    //     std::cout<<std::endl;
    // }
	// std::cout<<"--------------------------------------------------"<<std::endl;
	
}
// Rotation object with X axis
void rotationX(double degree){
	std::vector< std::vector<double> > rotation_matrix_x(4, std::vector<double>(4));
	int rotation_row = rotation_matrix_x.size();
	int rotation_col = rotation_matrix_x[0].size();
	for (int i = 0; i < rotation_row; i++)
	{
		for (int j = 0; j < rotation_col; j++)
		{
			if ( (i ==2 && j == 2) || (i== 1 && j== 1) )
			{
				rotation_matrix_x[i][j] = cos( (degree*PI)/180 );
			}else if ( (i== 0 && j == 0) || (i == 3 && j == 3) )
			{
				rotation_matrix_x[i][j] = 1;
			}else if(i == 1 && j == 2 ){
				rotation_matrix_x[i][j] = -sin( (degree*PI)/180 );
			}else if(i == 2 && j == 1){
				rotation_matrix_x[i][j] = sin( (degree*PI)/180 );
			}else{
				rotation_matrix_x[i][j] = 0;
			}
		}	
	}
	move(-distance_x,-distance_y,0.0);
	Matrix m_;

	if (isPerspective){

		for (int k = 0; k < vertex_index.size(); k++)
		{
			p_point_list[k] =  m_.dotProduct(rotation_matrix_x, p_point_list[k]);
		}
	}else{

		for (int k = 0; k < vertex_index.size(); k++)
		{
			point_list[k] =  m_.dotProduct(rotation_matrix_x, point_list[k]);
		}
	}
	move(distance_x,distance_y,0.0);
	

	// std::cout<<"--------------------------------------------------"<<std::endl;
	// for (int i = 0; i < rotation_row; i++)
    // {
    //     for (int j = 0; j < rotation_col; j++)
    //     {
    //         std::cout<<rotation_matrix_z[i][j]<<", ";
    //     } 
    //     std::cout<<std::endl;
    // }
	// std::cout<<"--------------------------------------------------"<<std::endl;
	
}

// Rotation object with Y axis
void rotationY(double degree){
	std::vector< std::vector<double> > rotation_matrix_y(4, std::vector<double>(4));
	int rotation_row_y = rotation_matrix_y.size();
	int rotation_col_y = rotation_matrix_y[0].size();
	for (int i = 0; i < rotation_row_y; i++)
	{
		for (int j = 0; j < rotation_col_y; j++)
		{
			if ( (i ==0 && j == 0) || (i== 2 && j== 2) )
			{
				rotation_matrix_y[i][j] = cos( degree*PI/180 );
			}else if ( (i ==1 && j == 1) || (i == 3 && j == 3) )
			{
				rotation_matrix_y[i][j] = 1;
			}else if(i == 0 && j == 2 ){
				rotation_matrix_y[i][j] = -sin( (degree*PI)/180 );
			}else if(i == 2 && j == 0){
				rotation_matrix_y[i][j] = sin(  (degree*PI)/180);
			}else{
				rotation_matrix_y[i][j] = 0;
			}
		}	
	}
	move(-distance_x,-distance_y,0.0);
	Matrix m_;
	if (isPerspective){
		for (int k = 0; k < vertex_index.size(); k++)
		{
			p_point_list[k] =  m_.dotProduct(rotation_matrix_y, p_point_list[k]);
		}
	}else{
		for (int k = 0; k < vertex_index.size(); k++)
		{
			point_list[k] =  m_.dotProduct(rotation_matrix_y, point_list[k]);
		}
	}
	
	move(distance_x,distance_y,0.0);
	// move(HEIGHT/2,WIDTH/2,0.0);
	
	// std::cout<<"--------------------------------------------------"<<std::endl;
	// for (int i = 0; i < rotation_row_y; i++)
    // {
    //     for (int j = 0; j < rotation_col_y; j++)
    //     {
    //         std::cout<<rotation_matrix_y[i][j]<<", ";
    //     } 
    //     std::cout<<std::endl;
    // }
	// std::cout<<"--------------------------------------------------"<<std::endl;
	
}

void init_window()
/* Clear the image area, and set up the coordinate system */
{

	/* Clear the window */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);
}

/***************************************************************************/

void write_pixel(int x, int y, double intensity)
/* Turn on the pixel found at x,y */
{

	glColor3f(intensity, intensity, intensity);
	glBegin(GL_POINTS);
	glVertex3i(x, y, 0);
	glEnd();
}

//***************************************************************************/

void display(void) // Create The Display Function
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen

	// write_pixel(x_last, y_last, 1.0); //<-you can get rid of this call if you like
	// CALL YOUR CODE HERE
	Point p1,p2,p3;
	if (!isPerspective)
	{
		for (int i = 0; i < vertex_index.size(); i+=3)
		{		
			p1.setX(point_list[i][0][0]);
			p1.setY(point_list[i][1][0]);
			p2.setX(point_list[i+1][0][0]);
			p2.setY(point_list[i+1][1][0]);
			p3.setX(point_list[i+2][0][0]);
			p3.setY(point_list[i+2][1][0]);
			
			// std::cout<<"P1: "<<"x:"<< p1.getX()<<"	"<<"y: "<<p1.getY()<<std::endl;
			// std::cout<<"P2: "<<"x:"<< p2.getX()<<"	"<<"y: "<<p2.getY()<<std::endl;
			// std::cout<<"P3: "<<"x:"<< p3.getX()<<"	"<<"y: "<<p3.getY()<<std::endl;
			// std::cout<<"--------------------------------------------------"<<std::endl;
			// std::cout<<"distance_X: "<<distance_x<<",	"<<"distance_Y: "<<distance_y<<std::endl;
			// std::cout<<"--------------------------------------------------"<<std::endl;
			Triangle temp_triangle(p1,p2,p3);
			temp_triangle.draw();
		}
	}else{
		for (int i = 0; i < vertex_index.size(); i+=3)
		{		
			p1.setX(p_point_list[i][0][0]);
			p1.setY(p_point_list[i][1][0]);
			p2.setX(p_point_list[i+1][0][0]);
			p2.setY(p_point_list[i+1][1][0]);
			p3.setX(p_point_list[i+2][0][0]);
			p3.setY(p_point_list[i+2][1][0]);
			
			// std::cout<<"P1: "<<"x:"<< p1.getX()<<"	"<<"y: "<<p1.getY()<<std::endl;
			// std::cout<<"P2: "<<"x:"<< p2.getX()<<"	"<<"y: "<<p2.getY()<<std::endl;
			// std::cout<<"P3: "<<"x:"<< p3.getX()<<"	"<<"y: "<<p3.getY()<<std::endl;
			// std::cout<<"--------------------------------------------------"<<std::endl;
			// std::cout<<"distance_X: "<<distance_x<<",	"<<"distance_Y: "<<distance_y<<std::endl;
			// std::cout<<"--------------------------------------------------"<<std::endl;
			Triangle temp_triangle(p1,p2,p3);
			temp_triangle.draw();
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
	}
	oldx = x;
	oldy = y;
	x_last = x;
	y_last = y;
}

/***************************************************************************/
void keyboard(unsigned char key, int x, int y) // Create Keyboard Function
{

	switch (key)
	{
	case 27:	 // When Escape Is Pressed...
		exit(0); // Exit The Program
		break;
	case 't':
		if (isScale)
		{
			isScale = false;
		}
		if (isRotate)
		{
			isRotate = false;
		}
		isTranslation = true;
		std::cout<<"Translation Mode On!!!"<<std::endl;
		break;
	case 'r':
		if(isTranslation){
			isTranslation = false;
		}
		if (isScale){
			isScale = false;
		}
		isRotate = true;
		std::cout<<"Rotation Mode On!!!"<<std::endl;
		break;

	case 'e':
		if(isTranslation){
			isTranslation = false;
		}
		if (isRotate)
		{
			isRotate = false;
		}
		isScale = true;
		std::cout<<"Scale Mode On!!!"<<std::endl;
		break;
		
	case '1': // stub for new screen
		printf("New screen\n");
		break;
	case 'w':
		if(isTranslation){
			move(0.0, MOVE_DISTANCE, 0.0);
			distance_y+=MOVE_DISTANCE;
		}else if(isRotate)
		{
			rotationX(DEGREE);
			// rotationZ(DEGREE);
		}else if(isScale)
		{
			scale(SCALEUP);
		}

		break;
	case 's':
		if(isTranslation){
			move(0.0, NEGATIVE_MOVE_DISTANCE, 0.0);
			distance_y+=NEGATIVE_MOVE_DISTANCE;
		}else if (isRotate)
		{
			// rotationZ(NEGATIVE_DEGREE);
			rotationX(NEGATIVE_DEGREE);
		}else if(isScale)
		{
			scale(SCALEDOWN);
		}
		
		break;
	case 'd':
		if(isTranslation){
			move(MOVE_DISTANCE, 0.0, 0.0);
			distance_x +=MOVE_DISTANCE;
		}else if(isRotate)
		{
			rotationY(NEGATIVE_DEGREE);
			// rotationZ(DEGREE);
		}
		
		break;
	case 'a':
		if(isTranslation){
			move(NEGATIVE_MOVE_DISTANCE, 0.0, 0.0);
			distance_x+=NEGATIVE_MOVE_DISTANCE;
		}else if(isRotate){
			rotationY(DEGREE);
			// rotationZ(NEGATIVE_DEGREE);
		}
		break;
	case 'v':
		if(!isPerspective){

			Pespective();
			std::cout<<"Pespective Mode On!!!"<<std::endl;
			isPerspective =true;
		}else{
			std::cout<<"Pespective Mode Off!!!"<<std::endl;
			isPerspective =false;
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
   using the escape key.						  */
	getOBJData();
	initialize_matrix();
	processPoinstList();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Computer Graphics");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	std::cout<< WIDTH<<"," <<HEIGHT<<std::endl;
	
	init_window(); //create_window

	glutMainLoop(); // Initialize The Main Loop
}
