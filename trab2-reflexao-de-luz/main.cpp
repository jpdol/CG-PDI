#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

double rot_y = 0;
double rot_x = 0;

// Iniciando o Glut
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	// Configurações de iluminação
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// Configurações de cor e intensidade
	GLfloat qaAmbientLight[]	= {0.2, 0.2, 0.2, 1.0};
	GLfloat qaDiffuseLight[]	= {0.8, 0.8, 0.8, 1.0};
	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Configurações de prosição das luzes
	GLfloat qaLightPosition[]	= {.5, .5, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

// Função que será chamada toda vez a tela precisar ser redesenhada
void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);

    glRotatef(rot_x, 1.0, 0.0, 0.0);
    glRotatef(rot_y, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.8f, 0.45f);
    glVertex3f(-1.25f,  0.8f,  1.3f);
    glVertex3f(-1.25f,  0.8f, -1.3f);
    glVertex3f(-1.25f, -1.0f, -1.3f);
    glVertex3f(-1.25f, -1.0f,  1.3f);

    glVertex3f(1.25f,  0.8f, -1.3f);
    glVertex3f(1.25f,  0.8f,  1.3f);
    glVertex3f(1.25f, -1.0f,  1.3f);
    glVertex3f(1.25f, -1.0f, -1.3f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.45f);
    glVertex3f(1.25f, 0.8f, 1.3f);
    glVertex3f(0.0f, 1.75f, 1.3f);
    glVertex3f(-1.25f, 0.8f, 1.3f);
    glVertex3f(-1.25f, -1.0f, 1.3f);
    glVertex3f(1.25f, -1.0f, 1.3f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.25f, 0.8f, -1.3f);
    glVertex3f(0.0f, 1.75f, -1.3f);
    glVertex3f(-1.25f, 0.8f, -1.3f);
    glVertex3f(-1.25f, -1.0f, -1.3f);
    glVertex3f(1.25f, -1.0f, -1.3f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.45f, 0.748f, 1.5f);
    glVertex3f(0.0f, 1.85f, 1.5f);
    glVertex3f(0.0f, 1.75f, 1.5f);
    glVertex3f(1.45f, 0.648f, 1.5f);

    glVertex3f(-1.45f, 0.748f, 1.5f);
    glVertex3f(0.0f, 1.85f, 1.5f);
    glVertex3f(0.0f, 1.75f, 1.5f);
    glVertex3f(-1.45f, 0.648f, 1.5f);

    glVertex3f(1.45f, 0.748f, -1.5f);
    glVertex3f(0.0f, 1.85f, -1.5f);
    glVertex3f(0.0f, 1.75f, -1.5f);
    glVertex3f(1.45f, 0.648f, -1.5f);

    glVertex3f(-1.45f, 0.748f, -1.5f);
    glVertex3f(0.0f, 1.85f, -1.5f);
    glVertex3f(0.0f, 1.75f, -1.5f);
    glVertex3f(-1.45f, 0.648f, -1.5f);

    glColor3f(1.0f, 0.0f, 0.f);
    glVertex3f(1.45f, 0.648f, 1.5f);
    glVertex3f(1.45f, 0.648f, -1.5f);
    glVertex3f(1.45f, 0.748f, -1.5f);
    glVertex3f(1.45f, 0.748f, 1.5f);

    glVertex3f(-1.45f, 0.648f, 1.5f);
    glVertex3f(-1.45f, 0.648f, -1.5f);
    glVertex3f(-1.45f, 0.748f, -1.5f);
    glVertex3f(-1.45f, 0.748f, 1.5f);

    glColor3f(1.0f, 0.0f, 0.2f);
    glVertex3f(1.45f, 0.748f, -1.5f);
    glVertex3f(0.0f, 1.85f, -1.5f);
    glVertex3f(0.0f, 1.85f, 1.5f);
    glVertex3f(1.45f, 0.748f, 1.5f);

    glVertex3f(-1.45f, 0.748f, -1.5f);
    glVertex3f(0.0f, 1.85f, -1.5f);
    glVertex3f(0.0f, 1.85f, 1.5f);
    glVertex3f(-1.45f, 0.748f, 1.5f);

    glColor3f(0.8f, 0.4f, 0.0f);
    glVertex3f(1.45f, 0.648f, -1.5f);
    glVertex3f(0.0f, 1.75f, -1.5f);
    glVertex3f(0.0f, 1.75f, 1.5f);
    glVertex3f(1.45f, 0.648f, 1.5f);

    glVertex3f(-1.45f, 0.648f, -1.5f);
    glVertex3f(0.0f, 1.75f, -1.5f);
    glVertex3f(0.0f, 1.75f, 1.5f);
    glVertex3f(-1.45f, 0.648f, 1.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.33f, 0.63f, 0.36f);
    glVertex3f(-5.0f,  -1.0f,  5.0f);
    glVertex3f(-5.0f,  -1.0f, -5.0f);
    glVertex3f(-5.0f, -1.45f, -5.0f);
    glVertex3f(-5.0f, -1.45f,  5.0f);

    glVertex3f(5.0f,  -1.0f, -5.0f);
    glVertex3f(5.0f,  -1.0f, 5.0f);
    glVertex3f(5.0f, -1.45f, 5.0f);
    glVertex3f(5.0f, -1.45f, -5.0f);

    glVertex3f(5.0f, -1.0f, -5.0f);
    glVertex3f(-5.0f, -1.0f, -5.0f);
    glVertex3f(-5.0f, -1.45f, -5.0f);
    glVertex3f(5.0f, -1.45f, -5.0f);

    glVertex3f(5.0f,  -1.0f, 5.0f);
    glVertex3f(-5.0f, -1.0f, 5.0f);
    glVertex3f(-5.0f, -1.45f, 5.0f);
    glVertex3f(5.0f, -1.45f, 5.0f);

    glColor3f(0.33f, 0.63f, 0.36f);
    glVertex3f(5.0f,  -1.0f, 5.0f);
    glVertex3f(-5.0f, -1.0f, 5.0f);
    glVertex3f(-5.0f, -1.0f, -5.0f);
    glVertex3f(5.0f, -1.0f, -5.0f);

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.4f, 0.8f);
    glVertex3f(-1.25f,  0.6f,  0.65f);
    glVertex3f(-1.25f,  0.6f, -0.65f);
    glVertex3f(-1.25f, -0.6f, -0.65f);
    glVertex3f(-1.25f, -0.6f,  0.65f);

    glVertex3f(1.25f,  0.6f, -0.65f);
    glVertex3f(1.25f,  0.6f,  0.65f);
    glVertex3f(1.25f, -0.6f,  0.65f);
    glVertex3f(1.25f, -0.6f, -0.65f);

    glEnd();

    glLineWidth(7.0f);
    glBegin(GL_LINES);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.25f,  0.6f,  0.65f);
    glVertex3f(-1.25f,  0.6f, -0.65f);

    glVertex3f(-1.25f,  0.6f, -0.62f);
    glVertex3f(-1.25f, -0.6f, -0.62f);

    glVertex3f(-1.25f, -0.6f, -0.75f);
    glVertex3f(-1.25f, -0.6f,  0.75f);

    glVertex3f(-1.25f, -0.6f,  0.62f);
    glVertex3f(-1.25f,  0.6f,  0.62f);

    glVertex3f(1.25f,  0.6f,  0.65f);
    glVertex3f(1.25f,  0.6f, -0.65f);

    glVertex3f(1.25f,  0.6f, -0.62f);
    glVertex3f(1.25f, -0.6f, -0.62f);

    glVertex3f(1.25f, -0.6f, -0.75f);
    glVertex3f(1.25f, -0.6f,  0.75f);

    glVertex3f(1.25f, -0.6f,  0.62f);
    glVertex3f(1.25f,  0.6f,  0.62f);

    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex3f(-1.25f,  0.6f, -0.0f);
    glVertex3f(-1.25f, -0.6f, -0.0f);

    glVertex3f(1.25f,  0.6f, -0.0f);
    glVertex3f(1.25f, -0.6f, -0.0f);

    glVertex3f(-1.25f, -0.2f, -0.65f);
    glVertex3f(-1.25f, -0.2f,  0.65f);

    glVertex3f(-1.25f, 0.2f, -0.65f);
    glVertex3f(-1.25f, 0.2f,  0.65f);

    glVertex3f(1.25f, -0.2f, -0.65f);
    glVertex3f(1.25f, -0.2f,  0.65f);

    glVertex3f(1.25f, 0.2f, -0.65f);
    glVertex3f(1.25f, 0.2f,  0.65f);

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.4f, 0.8f);

    glVertex3f(0.55f, 0.75f, 1.3f);
    glVertex3f(-0.55f, 0.75f, 1.3f);
    glVertex3f(-0.55f, -1.0f, 1.3f);
    glVertex3f(0.55f, -1.0f, 1.3f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.25f, 0.5f, 1.3f);
    glVertex3f(-0.25f, 0.5f, 1.3f);
    glVertex3f(-0.25f, 0.1f, 1.3f);
    glVertex3f(0.25f, 0.1f, 1.3f);

    glEnd();

    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.55f, 0.75f, 1.3f);
    glVertex3f(-0.55f, 0.75f, 1.3f);
    glVertex3f(-0.55f, -1.0f, 1.3f);
    glVertex3f(0.55f, -1.0f, 1.3f);
    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(-0.5f, -1.45f, 2.5f);
    glVertex3f(-0.5f, -1.45f, 2.0f);
    glVertex3f(-0.5f, -1.0f, 2.0f);
    glVertex3f(-0.5f, -1.0f, 2.5f);

    glEnd();

    glutSwapBuffers();
}

// Controles de rotação da figura
void hotKeys( int key, int x, int y ) {

    //  Seta direita - Girar para a direita
    if (key == GLUT_KEY_RIGHT)
        rot_y += 5;

    //  Seta para esquerda - Girar para a esquerda
    else if (key == GLUT_KEY_LEFT)
        rot_y -= 5;

    // Girar para cima
    else if (key == GLUT_KEY_UP)
        rot_x += 5;

    // Girar para baixo
    else if (key == GLUT_KEY_DOWN)
        rot_x -= 5;

    //  Atualiza a tela
    glutPostRedisplay();

}

// Função que reconfigura a tela quando a mesma mudar de tamanho
void reshapeHandler(GLsizei width, GLsizei height) {
    if (height == 0)
        height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("PDI - Projeto 02");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshapeHandler);
    glutSpecialFunc(hotKeys);
    initGL();
    glutMainLoop();

    return 0;
}
