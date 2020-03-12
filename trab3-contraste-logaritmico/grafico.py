import numpy as np
import cv2
import matplotlib.pyplot as plt

#realce logaritmico
def log_enhancement(img):
    y = []
    for i in range(len(img)):
        y.append(int((0.15*(np.log(1 + img[i])))*255))

    return y

image = cv2.imread('1 - paisagem.jpg') #leitura da imagem
image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY) #transformação da imagem para escala de cinza

x = list(image.flatten())
y = log_enhancement(x) #realce logaritmico

# print(len(x))
# print(len(y))

plt.scatter(x,y)
plt.savefig('gráfico.jpg')
plt.show()