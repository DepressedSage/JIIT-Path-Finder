
# importing cv2
import cv2
import numpy as np

f = open("coordinates.txt", "r+")
while a:
    coors = f.readline()
    if not coors
        a = False
    X = int(coors[:coors.find(';')])
    Y = int(coors[coors.find(';')+1:])

p = open("Nodes.txt","r+")
imgname = p.readline();
pathVar = imgname[:4]+".png"
print(pathVar)
# Reading an image in default mode
image = cv2.imread('lol.png')

# Window name in which image is displayed
window_name = 'Image'

# Start coordinate, here (0, 0)
# represents the top left corner of image
pts = np.array([],np.int32)


pts = pts.reshape((-1, 1, 2))
isClosed = False
# Blue color in BGR
color = (255, 0, 0)
# Line thickness of 2 px
thickness = 2
# Using cv2.polylines() method
# Draw a Blue polygon with
# thickness of 1 px
image = cv2.polylines(image, [pts],isClosed, color, thickness)
# Displaying the image
while(1):
    cv2.imshow('image', image)
    if cv2.waitKey(20) & 0xFF == 27:
        break
cv2.waitKey(0);
