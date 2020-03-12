import pygame
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *

from math import sin, cos, pi

import sys

def square():
    vertices = ((1, -1),
                (1,  1),
                (-1, 1,),
                (-1,-1))

    edges = ((0,1),
            (1,2),
            (2,3),
            (3,0))

    glBegin(GL_TRIANGLE_FAN)

    for edge in edges:
        for vertex in edge:
            glVertex2fv(vertices[vertex])
    glEnd()

def triangle():
    vertices = (( 0, 1),
                (-1,-1),
                ( 1,-1))

    edges = ((0,1),
            (1,2),
            (2,0))

    glBegin(GL_TRIANGLE_FAN)

    for edge in edges:
        for vertex in edge:
            glVertex2fv(vertices[vertex])
    glEnd()

def circle(center=(0, 0), radius=1, sectors=60):    
    
    glBegin(GL_TRIANGLE_FAN)
    for i in range(sectors):
        glVertex2d(center[0] + radius*sin(2*i*pi / sectors),
                   center[1] + radius*cos(2*i*pi / sectors))
    glEnd()

def main():
    print('\n1 - Square')
    print('2 - Triangle')
    print('3 - Circle\n')

    fig = int(input())
    while fig not in [1,2,3]:
        fig = int(input())

    pygame.init()
    display = (800,600)
    pygame.display.set_mode(display, DOUBLEBUF|OPENGL)

    rotate = 1

    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)

    glTranslatef(0.0,0.0, -5)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.KEYDOWN and event.key == K_4:
                rotate = not(rotate)
            elif event.type == pygame.KEYDOWN and event.key == K_1:
                fig = 1
            elif event.type == pygame.KEYDOWN and event.key == K_2:
                fig = 2
            elif event.type == pygame.KEYDOWN and event.key == K_3:
                fig = 3
            elif event.type == pygame.KEYDOWN and event.key == K_ESCAPE:
                sys.exit()

        if rotate:
            # glRotatef(0,1,0,0)
            glRotatef(1,0,1,0)
            # glRotatef(0,0,0,1)

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        if fig==1:
            square()
        elif fig==2:
            triangle()
        elif fig==3:
            circle(center=(0, 0), radius=1, sectors=60)
        pygame.display.flip()
        pygame.time.wait(10)


main()
