import numpy as np

matrix = np.loadtxt("time.txt" )

mean = np.mean(matrix)
std = np.std(matrix)
print("Length of the vector: " , len(matrix))
print("Mean: ",mean)
print("Std: " ,std)