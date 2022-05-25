f = open("Quardinates.txt", "r+")
coors = f.readline()
print(coors)
X = int(coors[:coors.find(';')])
xPos = []
xPos.append(X)
Y = int(coors[coors.find(';')+1:])
yPos = []
yPos.append(Y)
print(yPos)
