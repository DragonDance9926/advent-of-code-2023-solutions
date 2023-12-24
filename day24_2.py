import numpy as np
from sympy import Symbol
from sympy import solve_poly_system

handle = open("input.txt","r")

shards = []
for line in handle:
  pos, vel = line.strip().split(" @ ")
  px,py,pz = pos.split(", ")
  vx,vy,vz = vel.split(", ")
  shards.append((int(px),int(py),int(pz),int(vx),int(vy),int(vz)))

x = Symbol('x')
y = Symbol('y')
z = Symbol('z')
vx = Symbol('vx')
vy = Symbol('vy')
vz = Symbol('vz')

equations = []
t_syms = []
for idx,shard in enumerate(shards[:3]):
  x0,y0,z0,xv,yv,zv = shard
  t = Symbol('t'+str(idx))
  eqx = x + vx*t - x0 - xv*t
  eqy = y + vy*t - y0 - yv*t
  eqz = z + vz*t - z0 - zv*t

  equations.append(eqx)
  equations.append(eqy)
  equations.append(eqz)
  t_syms.append(t)

result = solve_poly_system(equations,*([x,y,z,vx,vy,vz]+t_syms))
print(result[0][0]+result[0][1]+result[0][2])
