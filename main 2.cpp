//
//  main.cpp
//  Bezier Curve Test
//
//  Created by Bradley Singer on 2/19/16.
//  Copyright © 2016 Bradley Singer. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

int MainWindow;

// The output stream object
std::ofstream outfile;

// The input stream object
std::ifstream infile;

// Screen Height and Width
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

// Number of total control points
const int NUM_CTRL_POINTS = 16;

// The degree of all bezier curves
const int DEGREE = 3;

// The radius in pixels describing the hitbox for a control point
const int clickRadius = 30;

// The control point index that is clicked on and dragged
int selectPoint = -1;

// Toggle control point guide lines on and off
bool guide_lines = true;

// Output file stream
//std::ofstream outfile;

// The class associates the control points with their "type" of point
class Pnt
{
public:
    // All of our control points for the Bezier curves
    GLfloat ctrlPoints[NUM_CTRL_POINTS][3];
    
    // An array that tells what kind of point each one is for
    // calculating C1 continuity
    // 0 -> end point
    // 1 -> dependent point
    // 2 -> connect point
    int ptype[ NUM_CTRL_POINTS ];
    
    // Constructor
    Pnt(){};
};

// ************** THE OBJECT THAT GLOBALY HOLDS THE CONTROL POINTS **********
Pnt p;

//------------------------------------------------------------	OnDraw()
//
void OnDraw() {
    
//    // Make a new array of control points that preserve C1 continuity
//    // Initialize the array to all 0's
//    GLfloat c1Points[NUM_CTRL_POINTS][3] = {{0},{0},{0}};
    
    // clear the screen & depth buffer
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    
    // clear the previous transform
    glLoadIdentity();
    
    // set the camera position
//    gluLookAt(	1,10,30,	//	eye pos
//              0,0,0,	//	aim point
//              0,1,0);	//	up direction
    
    // ******************** DRAW CURVE 1 *******************
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &p.ctrlPoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    
    GLint i;
    
    glColor3f(1,0,1);
    
    // we will draw lots of little lines to make our curve
    glBegin(GL_LINE_STRIP);
    for(i=0;i!=50;++i) {
        glEvalCoord1f(GLfloat(i) / 50.0);
    }
    glEnd();

    // ******************** DRAW CURVE 2 *******************
    
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &p.ctrlPoints[DEGREE][0]);
    glEnable(GL_MAP1_VERTEX_3);
    
    GLint k;
    
    glColor3f(1,1,1);
    
    // we will draw lots of little lines to make our curve
    glBegin(GL_LINE_STRIP);
    for(k=0;k!=50;++k) {
        glEvalCoord1f(GLfloat(k) / 50.0);
    }
    glEnd();
    
    // ******************** DRAW CURVE 3 *******************
    
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &p.ctrlPoints[DEGREE*2][0]);
    glEnable(GL_MAP1_VERTEX_3);
    
    GLint j;
    
    glColor3f(1,0,0);
    
    // we will draw lots of little lines to make our curve
    glBegin(GL_LINE_STRIP);
    for(j=0;j!=50;++j) {
        glEvalCoord1f(GLfloat(j) / 50.0);
    }
    glEnd();
    
    // ******************** DRAW CURVE 4 *******************
    
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &p.ctrlPoints[DEGREE*3][0]);
    glEnable(GL_MAP1_VERTEX_3);
    
    GLint l;
    
    glColor3f(0,0,1);
    
    // we will draw lots of little lines to make our curve
    glBegin(GL_LINE_STRIP);
    for(l=0;l!=50;++l) {
        glEvalCoord1f(GLfloat(l) / 50.0);
    }
    glEnd();
    
    // ******************** DRAW CURVE 5 *******************
    
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &p.ctrlPoints[DEGREE*4][0]);
    glEnable(GL_MAP1_VERTEX_3);
    
    GLint n;
    
    glColor3f(1,1,0);
    
    // we will draw lots of little lines to make our curve
    glBegin(GL_LINE_STRIP);
    for(n=0;n!=50;++n) {
        glEvalCoord1f(GLfloat(n) / 50.0);
    }
    glEnd();
    
    // draw the Control Vertices
    glColor3f(0,1,0);
    glPointSize(5);
    glBegin(GL_POINTS);
    for(int i=0;i!=NUM_CTRL_POINTS;++i) {
        glVertex3fv( p.ctrlPoints[i] );
    }
    glEnd();
    
    // draw the guide lines of the control points
    if (guide_lines) {
        glColor3f(0,1,1);
        glBegin(GL_LINE_STRIP);
        for(int i=0;i!=NUM_CTRL_POINTS;++i) {
            glVertex3fv( p.ctrlPoints[i] );
        }
        glEnd();
    }
    
    // currently we've been drawing to the back buffer, we need
    // to swap the back buffer with the front one to make the image visible
    glutSwapBuffers();
}


//------------------------------------------------------------	OnInit()
//
void OnInit() {
    // enable depth testing
    glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------	OnExit()
//
void OnExit() {
}

//------------------------------------------------------------	OnReshape()
//
void OnReshape(int w, int h)
{
    if (h==0)
        h=1;
    
    // set the drawable region of the window
    glViewport(0,0,w,h);
    
    // set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // just use a perspective projection
//    gluPerspective(45,(float)w/h,0.1,100);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0.0, 100);
    
    //    gluOrtho2D(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // go back to modelview matrix so we can move the objects about
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ------------------------------------------------------------	OnMouseClick()
void OnMouseClick(int button, int state, int xPosition, int yPosition)
{
    // left mouse button down
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        GLuint newX = xPosition;
        GLuint newY = SCREEN_HEIGHT - yPosition;
        printf("Pick location: x = %d   y = %d\n", newX, newY);
        
        // determine which control point is picked
        
        int choiceFound = 0;
        
        for (int i = 0; i < NUM_CTRL_POINTS && !choiceFound; i++)
        {
            // Use globally defined clickRadius
            if ((fabs(p.ctrlPoints[i][0] - newX) <= clickRadius) &&
                (fabs(p.ctrlPoints[i][1] - newY) <= clickRadius))
            {
                selectPoint = i;
                choiceFound = 1;
                std::cout << "Control point " << selectPoint << " was picked." << std::endl;
            }
        }
    }
    
    // left mouse button up
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        selectPoint = -1;
    }
    glutPostRedisplay();
}

// ------------------------------------------------------------	OnMouseMove()
void OnMouseMove(int xPosition, int yPosition)
{
    if (selectPoint > -1)
    {
        GLuint newX = xPosition;
        GLuint newY = SCREEN_HEIGHT - yPosition;
        GLuint orgX = p.ctrlPoints[selectPoint][0];
        GLuint orgY = p.ctrlPoints[selectPoint][1];
        GLuint backX = p.ctrlPoints[selectPoint - 1][0];
        GLuint backY = p.ctrlPoints[selectPoint - 1][1];
        GLuint nextX = p.ctrlPoints[selectPoint + 1][0];
        GLuint nextY = p.ctrlPoints[selectPoint + 1][1];
        
//        std::cout << "New control point " << selectPoint <<
//        " location: x = " << newX << "   y = " << newY << std::endl;
        
        if (p.ptype[selectPoint] == 0) {        // End point
            p.ctrlPoints[selectPoint][0] = newX;
            p.ctrlPoints[selectPoint][1] = newY;
        } else if (p.ptype[selectPoint] == 1) { // Dependent point
            if (p.ptype[selectPoint - 1] == 2) {        // look back, check for connect point
                // move itself
                p.ctrlPoints[selectPoint][0] = newX;
                p.ctrlPoints[selectPoint][1] = newY;
                
                // move the other dependent point
                // 2* center - other dependent
                p.ctrlPoints[selectPoint - 2][0] = (2 * p.ctrlPoints[selectPoint - 1][0])
                                                    - p.ctrlPoints[selectPoint][0];
                p.ctrlPoints[selectPoint - 2][1] = (2 * p.ctrlPoints[selectPoint - 1][1])
                                                    - p.ctrlPoints[selectPoint][1];
            } else if (p.ptype[selectPoint + 1] == 2) { // Look next, check for connect point
                // move itself
                p.ctrlPoints[selectPoint][0] = newX;
                p.ctrlPoints[selectPoint][1] = newY;
                
                // move the other dependent point
                // 2* center - other dependent
                p.ctrlPoints[selectPoint + 2][0] = (2 * p.ctrlPoints[selectPoint + 1][0])
                                                    - p.ctrlPoints[selectPoint][0];
                p.ctrlPoints[selectPoint + 2][1] = (2 * p.ctrlPoints[selectPoint + 1][1])
                                                    - p.ctrlPoints[selectPoint][1];
            } else { // back and next are either dependent or end points
                p.ctrlPoints[selectPoint][0] = newX;
                p.ctrlPoints[selectPoint][1] = newY;
            }
        } else if (p.ptype[selectPoint] == 2) { // Connect point
            // move itself
            p.ctrlPoints[selectPoint][0] = newX;
            p.ctrlPoints[selectPoint][1] = newY;
            
            // move the dependent points around it based on the change in location
            p.ctrlPoints[selectPoint - 1][0] = backX + (newX - orgX);
            p.ctrlPoints[selectPoint - 1][1] = backY + (newY - orgY);
            
            p.ctrlPoints[selectPoint + 1][0] = nextX + (newX - orgX);
            p.ctrlPoints[selectPoint + 1][1] = nextY + (newY - orgY);
        }
        
        glutPostRedisplay();
    }
}

//------------------------------------------------------------	processMenu()
//This function is called if user clicked a menu entry
//value is the value associated with a menu entry
void processMenu(int value)
{
    if (value == 0)
    {
        glutDestroyWindow(MainWindow);
        exit(0);
    }
    else if (value == 1)
    {
        std::cout << "Save File" << std::endl;
        outfile.open("Hw4Output.txt");
        
        for (int i = 0; i < NUM_CTRL_POINTS; i++) {
            for (int j = 0; j < 3; j++) {
                outfile << p.ctrlPoints[i][j] << " ";
            }
            outfile << "\n";
        }
        
        outfile.close();
    }
    else if (value == 2)
    {
        std::cout << "Load File" << std::endl;
        infile.open("Hw4Output.txt");
        
        for (int i = 0; i < NUM_CTRL_POINTS; i++) {
            for (int j = 0; j < 3; j++) {
                infile >> p.ctrlPoints[i][j];
            }
        }
        
    }
    else if (value == 3)
    {
        std::cout << "Toggle Guide Lines" << std::endl;
        guide_lines = !guide_lines;
        glutPostRedisplay();
    }
}

//------------------------------------------------------------	createMenu()
void createMenu()
{
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Save File", 1);
    glutAddMenuEntry("Load File", 2);
    glutAddMenuEntry("Toggle Guide Lines", 3);
    glutAddMenuEntry("Quit", 0);
    
    //attach menu to window which will be triggered by right button click
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//------------------------------------------------------------	main()
//
int main(int argc,char** argv) {
    
    // Default Points
    GLfloat testPoints[NUM_CTRL_POINTS][3] = {        
        { 504,  64,     0 },
        { 570,  300,    0 },
        { 396,  250,    0 },
        { 219,  138,    0 },
        { 42,   26,     0 },
        { 210,  198,    0 },
        { 139,  268,    0 },
        { 68,   338,    0 },
        { 236,  278,    0 },
        { 272,  388,    0 },
        { 308,  498,    0 },
        { 549,  250,    0 },
        { 520,  408,    0 },
        { 491,  566,    0 },
        { 130,  519,    0 },
        { 29,   480,    0 }
    };
    
    int testType[ NUM_CTRL_POINTS ] = {0,1,1,2,1,1,2,1,1,2,1,1,2,1,1,0};
    
    // initialise the control points
    
    for (int i = 0; i < NUM_CTRL_POINTS; i++) {
        for (int j = 0; j < 3; j++) {
            p.ctrlPoints[i][j] = testPoints[i][j];
        }
    }
    
    for (int i = 0; i < NUM_CTRL_POINTS; i++) {
        p.ptype[i] = testType[i];
    }
    
    // initialise glut
    glutInit(&argc,argv);
    
    // request a depth buffer, RGBA display mode, and we want double buffering
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
    
    // set the initial window size
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    
    glutInitWindowPosition(50,0);
    
    // create the window
    MainWindow = glutCreateWindow("Hw4 - Bezier Curve");
    
    // set the function to use to draw our scene
    glutDisplayFunc(OnDraw);
    
    // set the function to handle changes in screen size
    glutReshapeFunc(OnReshape);
    
    createMenu();
    
    // set the funciton for mouse clicks
    glutMouseFunc(OnMouseClick);
    
    // set the funciton for mouse click and drag
    glutMotionFunc(OnMouseMove);
    
    // run our custom initialisation
    OnInit();
    
    // set the function to be called when we exit
    atexit(OnExit);
    
    // this function runs a while loop to keep the program running.
    glutMainLoop();
    return 0;
}