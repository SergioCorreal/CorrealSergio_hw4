import numpy as np
import matplotlib.pylab as plt
from sys import argv

print argv[1]
data  = np.genfromtxt(argv[1], delimiter = ",")

x = data[:,0]
y = data[:,1]

f = plt.figure()
plt.plot(x,y)
plt.xlabel("x")
plt.ylabel("y")
plt.show()
plt.close()