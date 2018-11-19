import numpy as np
import matplotlib.pylab as plt
from sys import argv
s = [10,20,30,40,50,60,70]

data45  = np.genfromtxt("ode_45.txt", delimiter = ",")
x45 = data45[:,0]
y45 = data45[:,1]  
f = plt.figure()
plt.plot(x45,y45)
plt.xlabel("x")
plt.ylabel("y")
plt.title("45 degrees")
f.savefig("45.png")
plt.close()

f = plt.figure()

for i in s:
    data  = np.genfromtxt("ode_"+str(i)+".txt", delimiter = ",")
    x = data[:,0]
    y = data[:,1]
    plt.plot(x,y, label = i)

plt.xlabel("x")
plt.ylabel("y") 
plt.legend()
f.savefig("otherAngles.png")
plt.close()



