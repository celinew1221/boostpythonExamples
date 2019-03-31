import np2mat
import cv2
import numpy as np

img = np.float32(cv2.resize(cv2.imread('../1.png'), (1280, 720)))
np2mat.npch2ch(np.array(img[:,:,0]), np.array(img[:,:,1]), np.array(img[:,:,2]))
newimg = np.transpose(img, (2,0,1))
np2mat.np2ch(newimg)