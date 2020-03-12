#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926535897932384626433832795
#define WIDTH 640
#define HEIGHT 480

float angle = 0;
GLint stencilBits;
GLuint texture[40];

//Specifies the radius of the circle
static int radius = 1;

void init();
void reshape(int, int);
void display();

void freetexture (GLuint texture) {
    glDeleteTextures(1, &texture);
}

loadtextures (const char *filename, float width, float height) {
    GLuint texture;

    unsigned char *data;
    FILE *file;

    file = fopen(filename, "rb");
    if (file == NULL)
        return 0;

    data = (unsigned char*)malloc(width*height*3);
    fread(data, width*height*3, 1, file);

    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    data = NULL;

    return texture;
}

void circle (void) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,texture[0]);

    glTranslatef(0,2.5,0);
    glScalef(2,2,2);

	//Set Drawing Color - Will Remain this color until otherwise specified
	glColor3f(0.2, 0.3, 0.5);  //Some type of blue

	//Begin draw Circle
	glBegin(GL_POLYGON);
		//Change the 6 to 12 to increase the steps (number of drawn points) for a smoother circle
		//Note that anything above 24 will have little affect on the circles appearance
		//Play with the numbers till you find the result you are looking for
		//Value 1.5 - Draws Triangle
		//Value 2 - Draws circle
		//Value 3 - Draws Hexagon
		//Value 4 - Draws Octagon
		//Value 5 - Draws Decagon
		//Notice the correlation between the value and the number of sides
		//The number of sides is always twice the value given this range
		for(double i = 0; i < 2 * PI; i += PI / 48) //<-- Change this Value
			glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();
	//End draw Circle

    glPopMatrix();
}

void mirror (void) {
    glPushMatrix();
    glColor4f(1,1,1,0.7);
    glBindTexture(GL_TEXTURE_2D,texture[1]);

    glTranslatef(0,-2.5,0);
    glScalef(4,2,4);

    glBegin(GL_QUADS);
        glTexCoord2f(1,0);
        glVertex3f(-1,-1,1);
        glTexCoord2f(1,1);
        glVertex3f(-1,1,-0.5);
        glTexCoord2f(0,1);
        glVertex3f(1,1,-0.5);
        glTexCoord2f(0,0);
        glVertex3f(1,-1,1);
    glEnd();

    glPopMatrix();
}

void display (void) {
    glClearStencil(0); //clear the stencil buffer
    glClearDepth(1.0f);
    glClearColor (0.0,0.0,0.0,1);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the buffers
    glLoadIdentity();

    glTranslatef(0, 0, -10);

    //start
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); //disable the color mask
    glDepthMask(GL_FALSE); //disable the depth mask

    glEnable(GL_STENCIL_TEST); //enable the stencil testing

    glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); //set the stencil buffer to replace our next lot of data

    mirror(); //set the data plane to be replaced

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //enable the color mask
    glDepthMask(GL_TRUE); //enable the depth mask

    glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //set the stencil buffer to keep our next lot of data

    glDisable(GL_DEPTH_TEST); //disable depth testing of the reflection

    glPushMatrix();

    glScalef(1.0f, -1.0f, 1.0f); //flip the reflection vertically
    glTranslatef(0,1,0); //translate the reflection onto the drawing plane
    glRotatef(angle,0,1,0); //rotate the reflection

    circle(); //draw the circle as our reflection

    glPopMatrix();

    glEnable(GL_DEPTH_TEST); //enable the depth testing
    glDisable(GL_STENCIL_TEST); //disable the stencil testing
    //end

    glEnable(GL_BLEND); //enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set the blending function

    mirror(); //draw our mirror

    glDisable(GL_BLEND); //disable alpha blending

    glRotatef(angle,0,1,0); //rotate our circle
    circle(); //draw our circle

    glutSwapBuffers();
    angle++;
}

void init (void) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel (GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    texture[0] = loadtextures("texture.raw", 256,256);
    texture[1] = loadtextures("water.raw", 256,256);
}

void reshape (int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL); //add a stencil buffer to the window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Reflection Window");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
