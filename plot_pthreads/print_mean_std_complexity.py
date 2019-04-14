import numpy as np

matrix = np.loadtxt("time.txt" )

mean = np.mean(matrix)
std = np.std(matrix)
print(mean,std)
