import numpy as np
import cv2 


img = cv2.imread('1 - malaria-original.jpg', 0) # leitura da imagem em escala de cinza
cv2.imwrite('2 - grayscale.jpg', img)

image = img.copy()


image = cv2.blur(image,(13,13)) # Aplicacao de filtro de suavização por média (opencv)
cv2.imwrite('3.1 - mean-blur.jpg', image)
image = cv2.Canny(image, 10,16) # detector de bordas através do algoritmo de Canny
cv2.imwrite('4.1 - canny-edge-detector.jpg', image)
