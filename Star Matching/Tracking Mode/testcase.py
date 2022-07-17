#TEST PARAMETERS------------------------------------

c = 200 #tested values = 1005, 1100, 745
roll = 0.000005
pitch = 0.000002
yaw = 0.000009


#----------------------------------------------------
import numpy as np
from math import *

f = open("SM_Guide_Star.txt", newline='\n')
l = f.readlines()

m=[]
for i in l:
    m.append([float(k) for k in i.split()])


#tested values of c = 1005, 1100
test = [[c, 0, 0]]

f1 = open("SNT_full.txt")
m1 = []
for i in f1.readlines():
    m1.append(i.split())

c-=1
for i in m1[c]:
    j = int(i)
    if j!=0:
        
        cos_theta = float(m[c][1])*float(m[j][1]) + float(m[c][2])*float(m[j][2]) + float(m[c][3])*float(m[j][3])
        v1 = np.array(m[c][1:])
        v2 = np.array(m[j][1:]) * (1/cos_theta)
        v = np.cross(v1, [1,0,0])
        x = np.dot(v2, v)/np.sqrt(np.dot(v,v))
        r = 1/cos_theta
        y = np.sqrt(r**2 - x**2)
        if (x<18.44 and y<18.44):
            test.append([j, round(x/0.036), round(y/0.036)])

for q in test:
    print(q[1], ',', q[2], ',', q[0], ',')

print()
print()

roll = 0.001
pitch = 0.002
yaw = 0.003

k = np.array([roll, pitch, yaw])

new = []
f = 0.036
for q in test:
    u = q[1]*0.036
    v = q[2]*0.036
    e = np.matrix([[u*v/f, -f-u*u/f, v],
                   [f+v*v/f, -u*v/f, -u]])
    d = str(np.matmul(e, k)[0][0]).strip('[').strip(']').split()
    d = [float(p) for p in d]
    if (x<18.44 and y<18.44):
        new.append([q[0], round(q[1]+d[0]/0.036), round(q[2]+d[1]/0.036)])

for q in new:
    print(q[1], ',', q[2], ',', q[0], ',')

print()
print()


new1 = []
f = 0.036
for q in new:
    u = q[1]*0.036
    v = q[2]*0.036
    e = np.matrix([[u*v/f, -f-u*u/f, v],
                   [f+v*v/f, -u*v/f, -u]])
    d = str(np.matmul(e, k)[0][0]).strip('[').strip(']').split()
    d = [float(p) for p in d]
    new1.append([q[0], round(q[1]+d[0]/0.036), round(q[2]+d[1]/0.036)])

for q in new1:
    print(q[1], ',', q[2], ',')#, q[0], ',')


print()
print()
print(len(test))











