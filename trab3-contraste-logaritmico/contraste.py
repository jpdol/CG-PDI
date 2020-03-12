import numpy as np
import cv2

#realce logaritmico
def log_enhancement(img):
    for i in range(len(img)):
    	for j in range(len(img[0])):
    		img[i][j] = int((0.15*(np.log(1 + img[i][j])))*255)

    return img

image = cv2.imread('1 - paisagem.jpg') #leitura da imagem

image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY) #transformação da imagem para escala de cinza
cv2.imshow('gray', image)
cv2.imwrite('2 - grayscale.jpg', image)

image = log_enhancement(image) #realce logaritmico
cv2.imshow('log_enhancement', image)
cv2.imwrite('3 - log_enhancement.jpg', image)


cv2.waitKey(0)