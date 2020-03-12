import sys, math, pygame
from pygame.locals import *

class Point3D:
    def __init__(self, x = 0, y = 0, z = 0):
        self.x, self.y, self.z = float(x), float(y), float(z)
    
    # Gira a imagem em relação ao eixo Y
    def rotateY(self, angle):
        rad = angle * math.pi / 180
        cosa = math.cos(rad)
        sina = math.sin(rad)
        z = self.z * cosa - self.x * sina
        x = self.z * sina + self.x * cosa
        return Point3D(x, self.y, 0)

    # Tranforma um ponto 3D para um ponto 2D
    def project(self, win_width, win_height, fov, viewer_distance):
        factor = fov / (viewer_distance + self.z)
        x = self.x * factor + win_width / 2
        y = -self.y * factor + win_height / 2
        return Point3D(x, y, 1)

# Retorna todos os pontos de um circulo
def circlePoints(j = 0, k = 0, r = 1):
    points = []
    for degree in range(360):
        points.append( Point3D(r*math.cos(degree) + j, r*math.sin(degree) + k, -1))
    return points

class Simulation:
    def __init__(self, win_width = 640, win_height = 480, drawType = 1):
        pygame.init()
        self.drawType = drawType
        self.incremets = 1
 
        self.screen = pygame.display.set_mode((win_width, win_height))
        pygame.display.set_caption("Rotation")

        self.vertices = []
 
        self.clock = pygame.time.Clock()
            
        self.angleX, self.angleY, self.angleZ = 0, 0, 0

    # Para desenhar um quadrado
    def drawSquare(self):
        self.vertices = []
        # Draw a square
        i = -1
        while(i<1):
            self.vertices.append(Point3D(-i, 1,-1))
            i+=0.01

        i = 1
        while(i>-1):
            self.vertices.append(Point3D(-1, i,-1))
            i-=0.01

        i = 1
        while(i>-1):
            self.vertices.append(Point3D(1, i,-1))
            i-=0.01

        i = -1
        while(i < 1):
            self.vertices.append(Point3D(i, -1,-1))
            i+=0.01

    # Para desenhar um triângulo com apenas 3 pontos
    def drawTriagle(self):
        self.vertices = []

        i = 1
        while(i>-1):
            self.vertices.append(Point3D(-1, i,-1))
            i-=0.01

        i = -1
        while(i < 1):
            self.vertices.append(Point3D(i, -1,-1))
            i+=0.01
        i = -1
        while(i < 1):
            self.vertices.append(Point3D(i, -i,-1))
            i+=0.01 

    # Para desenhar um circulo
    def drawCircle(self):
        self.vertices = []

        self.vertices = circlePoints()
 
    def run(self):
        if(self.drawType == 1):
            self.drawSquare()
        elif(self.drawType == 2):
            self.drawCircle()
        elif(self.drawType == 3):
            self.drawCircle()
        while 1:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
                elif event.type == pygame.KEYDOWN and event.key == K_ESCAPE:
                    sys.exit()
                elif event.type == pygame.KEYDOWN and event.key == K_1:
                    self.drawSquare()
                elif event.type == pygame.KEYDOWN and event.key == K_2:
                    self.drawTriagle()
                elif event.type == pygame.KEYDOWN and event.key == K_3:
                    self.drawCircle()
                elif event.type == pygame.KEYDOWN and event.key == K_4:
                    self.incremets = not(self.incremets)

            # Time for draw another time
            self.clock.tick(50)
            self.screen.fill((0,0,0))

            for point in self.vertices:
                # Rotate the point around Y axis.
                r = point.rotateY(self.angleY)

                # Transform the point from 3D to 2D
                p = r.project(self.screen.get_width(), self.screen.get_height(), 256, 4)
                x, y = int(p.x), int(p.y)
                self.screen.fill((255,255,255),(x,y,2,2))
                
 
            # self.angleX += 0
            # self.angleZ += 0
            self.angleY += self.incremets 
            pygame.display.flip()
 
if __name__ == "__main__":

    print('''\n1 - Quadrado\n2 - Triângulo\n3 - Circulo\nPressione 'ESC' para sair''')
    
    draw = input()
    Simulation(drawType = int(draw)).run()