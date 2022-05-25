
# importing cv2
import cv2

f = open("Quardinates.txt", "r+")
coors = f.readline()
X = int(coors[:coors.find(';')])
xPos = []
xPos.append(X)
Y = int(coors[coors.find(';')+1:])
yPos = []
yPos.append(Y)

p = open("Nodes.txt","r+")
imgname = p.readline();
pathVar = imgname[:4]+".png"
print(pathVar)
# Reading an image in default mode
image = cv2.imread(pathVar)

# Window name in which image is displayed
window_name = 'Image'

# Start coordinate, here (0, 0)
# represents the top left corner of image
start_point = (0, 0)

# End coordinate, here (250, 250)
# represents the bottom right corner of image
end_point = (250, 250)

# Green color in BGR
color = (0, 255, 0)

# Line thickness of 9 px
thickness = 1

# Using cv2.line() method
# Draw a diagonal green line with thickness of 9 px
image = cv2.line(image, start_point, end_point, color, thickness)

# Displaying the image
cv2.imshow(window_name, image)
cv2.waitKey(0);
