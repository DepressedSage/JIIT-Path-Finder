
# importing cv2
import cv2
import numpy as np
import os

pos = []
buildingName = {}
with open("coordinates.txt", encoding = 'utf-8') as f:
    while(f.readline()):
        Coords = f.readline()
        if ";" not in Coords:
            continue
        Bname,x,y = Coords.split(";")
        x = int(x)
        y = int(y)
        if Bname in buildingName:
            buildingName[Bname].append((x,y))
        else:
            buildingName[Bname] = [(x,y)]

for x in buildingName.keys():
    Coords = buildingName[x]
    Coords = np.array(Coords,np.int32)
    imgname = cv2.imread(x+".png")
    Coords = Coords.reshape((-1, 1, 2))
    image = cv2.polylines(imgname, [Coords] ,False, (255,0,0) , 10)
    while(1):
        cv2.imshow('image', image)
        if cv2.waitKey(0) & 0xFF == 'q':
            break

cv2.destroyAllWindows()

