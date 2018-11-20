import numpy as np
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt

x = np.zeros((50,50))

for i in range(50):
    for j in range(50):
        x[i][j] = i

y = x.transpose()

# inicial

initial = np.genfromtxt("pde_initial.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, initial)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Inital temperature")
fig.savefig("initial.png")
plt.close()

# Todas las graficas

ci1 = np.genfromtxt("pde_ci1.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, ci1)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Closed boundary intermediate 1")
fig.savefig("ci1.png")
plt.close()

ci2 = np.genfromtxt("pde_ci2.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, ci2)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Closed boundary intermediate 2")
fig.savefig("ci2.png")
plt.close()

cf = np.genfromtxt("pde_cf.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, cf)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Closed boundary final")
fig.savefig("cf.png")
plt.close()

oi1= np.genfromtxt("pde_oi1.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, oi1)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Open boundary intermediate 1")
fig.savefig("oi1.png")
plt.close()

oi2 = np.genfromtxt("pde_oi2.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, oi2)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Open boundary intermediate 2")
fig.savefig("oi2.png")
plt.close()

of = np.genfromtxt("pde_of.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, of)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Open boundary final")
fig.savefig("of.png")
plt.close()


pi1= np.genfromtxt("pde_pi1.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, pi1)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Periodic boundary intermediate 1")
fig.savefig("pi1.png")
plt.close()

pi2 = np.genfromtxt("pde_pi2.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, pi2)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Periodic boundary intermediate 2")
fig.savefig("pi2.png")
plt.close()

pf = np.genfromtxt("pde_pf.txt", delimiter = ",")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, pf)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Periodic boundary final")
fig.savefig("pf.png")
plt.close()

# Average

i1 = np.zeros((50,50))
i2 = np.zeros((50,50))
f = np.zeros((50,50))

for i in range(50):
        for j in range(50):
                i1[i][j] = (1.0/3.0)*(ci1[i][j]+ oi1[i][j] + pi1[i][j])
                i2[i][j] = (1.0/3.0)*(ci2[i][j]+ oi2[i][j] + pi2[i][j])
                f[i][j] = (1.0/3.0)*(cf[i][j]+ of[i][j] + pf[i][j])

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, i1)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Average intermediate 1")
fig.savefig("i1.png")
plt.close()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, i2)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Average intermediate 2")
fig.savefig("i2.png")
plt.close()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(x, y, f)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("T")
plt.title("Average final")
fig.savefig("f.png")
plt.close()

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