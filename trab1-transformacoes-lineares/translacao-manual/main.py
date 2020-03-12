import numpy as np
import cv2
tx = 5
ty = 5
#matriz de translacao que sera multiplicada pela matriz dos elementos
translate_matrix = [[1, 0, tx],
					[0, 1, ty], 
					[0, 0, 1]]
class canvas:
	def __init__(self, w, h):
		self.data = np.zeros((h, w, 3), dtype=np.uint8)#background
		self.w = w
		self.h = h
		#origem dada no centro da area de desenho
		self.origx = w/2
		self.origy = h/2
	def draw(self, form):
		#verifica qual forma deve ser desenhada
		if form == 0:
			self.drawRect(40, 40, self.origx, self.origy)
		elif form == 1:
			self.drawCirc(20, self.origx, self.origy)
		elif form == 2:
			self.drawTri(40, 40, self.origx, self.origy)
	def drawRect(self, w, h, cx, cy):
		#w e h sao as dimensoes do retangulo
		a = np.zeros((self.w, self.h)).astype('uint8')#preenche o background de preto para redesenhar a forma
		self.origx = int(cx)
		self.origy = int(cy)
		for i in range(w):
			for j in range(h):
				a[self.origy+i][self.origx+j] = 255#desenha de branco baseado nas dimensoes fornecidas
		self.data = a
	def drawTri(self, w, h, cx, cy):
		#w e h sao as dimensoes do triangulo
		a = np.zeros((self.w, self.h)).astype('uint8')#preenche o background de preto para redesenhar a forma
		self.origx = int(cx)
		self.origy = int(cy)
		for i in range(w):
			for j in range(h-i):
				a[self.origy+i][self.origx+j] = 255#desenha de branco baseado nas dimensoes fornecidas
		self.data = a
	def drawCirc(self, radius, cx, cy):
		a = np.zeros((self.w, self.h)).astype('uint8')#preenche o background de preto para redesenhar a forma
		y, x = np.ogrid[-radius: radius, -radius: radius] 
		index = x**2 + y**2 <= radius**2
		self.origx = int(cx)
		self.origy = int(cy)
		#print(radius, cx, cy, index)
		a[self.origy-radius:self.origy+radius, self.origx-radius:self.origx+radius][index] = 255#desenha de branco baseado nas dimensoes fornecidas
		self.data = a
	def translate(self, tx, ty):
		translate_matrix[0][2] = tx
		translate_matrix[1][2] = ty
		tmp = np.dot(np.array(translate_matrix), np.array([[self.origx], [self.origy], [1]]))#multiplicacao entre as matrizes.
		self.origx = tmp[0]
		self.origy = tmp[1]

w, h = 512, 512
form = 1
c = canvas(w, h)
print("Informe a forma ser desenhada.\nc para circulo\nr para retangulo\nt para triangulo\n\nPara mover utilize w, a, s ou d.")
#controle de comandos basico
while True:
	command = str(input())
	if command == 'r':
		form = 0
	elif command == 'c':
		form = 1
	elif command == 't':
		form = 2

	if command == 'a':
		c.translate(-tx, 0)
	elif command == 'd':
		c.translate(tx, 0)
	elif command == 'w':
		c.translate(0, -ty)
	elif command == 's':
		c.translate(0, ty)
	
	if command == 'q':
		break
	c.draw(form)
	
	cv2.imshow("img",c.data)
	k = cv2.waitKey(33) & 0xFF
	if k == 27:
		break
