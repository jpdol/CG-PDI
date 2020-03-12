import pygame
from pygame.locals import *
import sys

from OpenGL.GL import *
from OpenGL.GLU import *

from math import sin, cos, pi

def scale(verticies, f):
	for i in range(len(verticies)):
		for j in range(len(verticies[i])):
			verticies[i][j]*=f

	return verticies

def square(verticies):
 
    edges = (
            (0,1),
            (1,2),
            (2,3),
            (3,0)
            )

    # glBegin(GL_LINES)
    glBegin(GL_TRIANGLE_FAN)

    for edge in edges:
        for vertex in edge:
            glVertex2fv(verticies[vertex])
    glEnd()

def triangle(verticies):
    edges = (
            (0,1),
            (1,2),
            (2,0),
            )

    # glBegin(GL_LINES)
    glBegin(GL_TRIANGLE_FAN)

    for edge in edges:
        for vertex in edge:
            glVertex2fv(verticies[vertex])
    glEnd()

def circle(center=(0, 0), radius=1, sectors=60):    
    # glBegin(GL_LINES)
    glBegin(GL_TRIANGLE_FAN)
    for i in range(sectors):
        glVertex2d(center[0] + radius*sin(2*i*pi / sectors),
                   center[1] + radius*cos(2*i*pi / sectors))
    glEnd()

def main():


    pygame.init()
    display = (800,600)
    pygame.display.set_mode(display, DOUBLEBUF|OPENGL)

    scale1 = 1

    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)

    glTranslatef(0.0,0.0, -5)

    count = 1
    sobe=False

    print()
    print('1 - Square')
    print('2 - Triangle')
    print('3 - Circle')
    print()
    fig = int(input())
    while fig not in [1,2,3]:
        fig = int(input())
    radius = 1
    if fig==1:
        verticies = [
                    [1, -1],
                    [1,  1],
                    [-1, 1],
                    [-1,-1]
                    ]
    elif fig==2:
        verticies = [
                [ 0, 1],
                [-1,-1],
                [ 1,-1],
                ]
    elif fig==3:
    	verticies=[]

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.KEYDOWN and event.key == K_ESCAPE:
                sys.exit()
            elif event.type == pygame.KEYDOWN and event.key == K_1:
                scale1 = not scale1
        
        if scale1:
            if count>=60 or count<=-100:
                sobe = not sobe

            if sobe:
                verticies=scale(verticies,1.01)
                radius*=1.01
                count+=1
            else:
                verticies=scale(verticies,0.99)
                radius*=0.99
                count-=1
        


        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        if fig==1:
            square(verticies)
        elif fig==2:
            triangle(verticies)
        elif fig==3:
            circle(center=(0, 0), radius=radius, sectors=60)
        pygame.display.flip()
        pygame.time.wait(10)


main()
