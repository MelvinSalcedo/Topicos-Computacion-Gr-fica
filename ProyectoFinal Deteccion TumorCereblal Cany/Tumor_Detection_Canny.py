import matplotlib.image as mpimg
import matplotlib.pyplot as plt 
import os
import stepsTDC as ced
from PIL import Image

def convertFormatImage(dir_name = 'input/Asco/'):
    for filename in os.listdir(dir_name):
        if os.path.isfile(dir_name + '/' + filename):
            img = Image.open(dir_name + '/' + filename)
            nameFile=filename.split('.tiff')
            print(nameFile[0])
            
            NI=Image.new("RGB",img.size,(255,255,255))
            NI.paste(img,(0,0));
            
            NI.save('output/Asco_b/'+ nameFile[0]+".jpg")
        
            
    
    
def rgb2gray(rgb):

    r, g, b = rgb[:,:,0], rgb[:,:,1], rgb[:,:,2]
    gray = 0.2989 * r + 0.5870 * g + 0.1140 * b

    return gray

def load_data(dir_name = 'Tumor/'):    
    
    for filename in os.listdir(dir_name):
        if os.path.isfile(dir_name + '/' + filename):
            
            print(filename)
            img = mpimg.imread(dir_name + '/' + filename)
            img = rgb2gray(img)
            #imgs=img
            #imgs.append(img)
            detector = ced.cannyEdgeDetector(img, sigma=15, kernel_size=5, lowthreshold=0.001, highthreshold=0.095, weak_pixel=100)

            imgs_final = detector.detect()
            
            visualize(img,filename, 'gray')
            
            visualize(imgs_final,filename, 'gray')

def visualize(imgs,name, format=None, gray=False):
    i=0;
    plt.figure(figsize=(20, 40))
    if imgs.shape[0] == 3:
        imgs = imgs.transpose(1,2,0)
    plt_idx = i+1
    plt.subplot(2, 2, plt_idx)
    plt.imshow(imgs, format)

    #image = imread("output/0.png")
    #negative = 255 - imgs
    
    negative = imgs
    mpimg.imsave('Salida/'+name,negative, cmap='Greys_r', vmin=0, vmax=1)
    
#______________________________________________________________
#convertFormatImage()
imgs = load_data()
