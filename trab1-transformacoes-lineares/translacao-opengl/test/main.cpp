/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#include<math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
//posicao para desenhar
static float x_trans = 0;
static float y_trans = 0;

//verificar qual forma deve ser desenhada
static bool drawCirc = false;
static bool drawRect = false;
static bool drawTri = false;
/* GLUT callback Handlers */
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
}
//definir tamanho
static void resize(int width, int height)
{   glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
//funcao para desenhar circulo utilizando triangle_fan
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3, 0.4, 0.5);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * M_PI * float(ii) / float(num_segments);//angulo

        float x = r * cos(theta);//calcula componente x
        float y = r * sin(theta);//calcula componente y

        glVertex2f(x + cx, y + cy);

    }
    glEnd();
}
static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(x_trans, y_trans, 0);//faz a translacao
    //verifica qual forma deve ser desenhada
    if (drawRect)
    {
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);
        glVertex3f (-2, -2, 0.0);
        glColor3f(0, 1, 0);
        glVertex3f (2, -2, 0.0);
        glColor3f(0, 0, 1);
        glVertex3f (2, 2, 0.0);
        glColor3f(0, 1, 1);
        glVertex3f (-2, 2, 0.0);
    glEnd();
    }

    else if(drawTri)
    {
    glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 0);
        glVertex2f(2.0, 0.0);
        glColor3f(1, 0, 1);
        glVertex2f(-2.0, 0.0);
        glColor3f(0, 1, 0.75);
        glVertex2f(0.0, 2.0);
    glEnd();
    }
    else if(drawCirc)
    {
    DrawCircle(0, 0, 2, 20);
    }
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case 'a':
            x_trans -= 0.5;
            break;
        case 'd':
            x_trans += 0.5;
            break;
        case 's':
            y_trans -= 0.5;
            break;
        case 'w':
            y_trans += 0.5;
            break;
        case 'c':
            x_trans = 0;
            y_trans = 0;
            drawCirc = true;
            drawRect = false;
            drawTri = false;
            break;
        case 'r':
            x_trans = 0;
            y_trans = 0;
            drawRect = true;
            drawCirc = false;
            drawTri = false;
            break;
        case 't':
            x_trans = 0;
            y_trans = 0;
            drawRect = false;
            drawCirc = false;
            drawTri = true;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0,0,0,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
