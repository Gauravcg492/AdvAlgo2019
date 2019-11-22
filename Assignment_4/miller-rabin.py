import random
import matplotlib.pyplot as plot

def MillerRabin(n,k):
  if n <= 3:
    return 1
  if n%2 == 0:
    return 0
  d = n - 1
  r = 0
  while d%2 == 0:
    d = d//2
    r += 1
  for i in range(k):
    a = random.randint(2,n-2)
    x = pow(a,d,n)
    if not (x == 1 or x == n-1):
      j = 0
      while j < r:
        x = pow(x,2,n)
        if (x == n-1):
          j += 1
          break
        j += 1
      if j == r:
        return 0    
  return 1

