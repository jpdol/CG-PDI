import numpy as np
import cv2


#abre a imagem e converte para escala em cinza
def convolve(image, kernel):
    output = np.zeros(image.shape)
    image_row, image_col = image.shape
    #determina tamanho do filtro
    filter_row, filter_col = kernel.shape
    #variaveis para padding
    pad_height = int((filter_row - 1) / 2)
    pad_width = int((filter_col - 1) / 2)
    #coloca 0 nas extremidades da matriz
    padded_image = np.zeros((image_row + (2 * pad_height), image_col + (2 * pad_width)))
    padded_image[pad_height:padded_image.shape[0] - pad_height, pad_width:padded_image.shape[1] - pad_width] = image

    #convolucao
    for row in range(image_row):
        for col in range(image_col):
            output[row, col] = np.sum(kernel * padded_image[row:row + filter_row, col:col + filter_col])
    return output

def blur(image, filter_size = 9):
    
    #cria o filtro do blur
    kernel = np.ones((filter_size,filter_size),np.float32)/(filter_size* filter_size)

    return convolve(image, kernel)

#salva imagem apos aplicacao do filtro
def sobel_filters(img):
    Kx = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], np.float32)
    Ky = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]], np.float32)
    
    Ix = convolve(img, Kx)
    Iy = convolve(img, Ky)
    
    G = np.hypot(Ix, Iy)
    G = G / G.max() * 255
    theta = np.arctan2(Iy, Ix)
    
    return (G, theta)

def non_max_suppression(img, D):
    M, N = img.shape
    Z = np.zeros((M,N), dtype=np.int32)
    angle = D * 180. / np.pi
    angle[angle < 0] += 180

    for i in range(1,M-1):
        for j in range(1,N-1):
            try:
                q = 255
                r = 255
                
               #angle 0
                if (0 <= angle[i,j] < 22.5) or (157.5 <= angle[i,j] <= 180):
                    q = img[i, j+1]
                    r = img[i, j-1]
                #angle 45
                elif (22.5 <= angle[i,j] < 67.5):
                    q = img[i+1, j-1]
                    r = img[i-1, j+1]
                #angle 90
                elif (67.5 <= angle[i,j] < 112.5):
                    q = img[i+1, j]
                    r = img[i-1, j]
                #angle 135
                elif (112.5 <= angle[i,j] < 157.5):
                    q = img[i-1, j-1]
                    r = img[i+1, j+1]

                if (img[i,j] >= q) and (img[i,j] >= r):
                    Z[i,j] = img[i,j]
                else:
                    Z[i,j] = 0

            except IndexError as e:
                pass
    
    return Z

def threshold(img, lowThresholdRatio=0.05, highThresholdRatio=0.09):
    
    highThreshold = img.max() * highThresholdRatio;
    lowThreshold = highThreshold * lowThresholdRatio;
    
    M, N = img.shape
    res = np.zeros((M,N), dtype=np.int32)
    
    weak = np.int32(25)
    strong = np.int32(255)
    
    strong_i, strong_j = np.where(img >= highThreshold)
    zeros_i, zeros_j = np.where(img < lowThreshold)
    
    weak_i, weak_j = np.where((img <= highThreshold) & (img >= lowThreshold))
    
    res[strong_i, strong_j] = strong
    res[weak_i, weak_j] = weak
    
    return (res, weak, strong)

def hysteresis(img, weak, strong=255):
    M, N = img.shape  
    for i in range(1, M-1):
        for j in range(1, N-1):
            if (img[i,j] == weak):
                try:
                    if ((img[i+1, j-1] == strong) or (img[i+1, j] == strong) or (img[i+1, j+1] == strong)
                        or (img[i, j-1] == strong) or (img[i, j+1] == strong)
                        or (img[i-1, j-1] == strong) or (img[i-1, j] == strong) or (img[i-1, j+1] == strong)):
                        img[i, j] = strong
                    else:
                        img[i, j] = 0
                except Execption as e:
                    print(e)
    return img



image = cv2.imread('1 - malaria-original.jpg')
image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
image = blur(image)
cv2.imwrite('output_blured_9x9.jpg', image)
gradientMat, thetaMat =  sobel_filters(image)
cv2.imwrite('output_sobel.jpg', gradientMat)
nonMaxImg = non_max_suppression(gradientMat, thetaMat)
cv2.imwrite('output_nonMaxImg.jpg', nonMaxImg)
thresholdImg = threshold(nonMaxImg)
cv2.imwrite('output_thresholdImg.jpg', thresholdImg[0])
img_final = hysteresis(thresholdImg[0], thresholdImg[1], thresholdImg[2])

cv2.imwrite('output9x9.jpg', img_final)