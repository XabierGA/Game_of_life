import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
sns.set()
sns.set_style('whitegrid')

cores = [1,2,3,4,5,6,7,8]
times=[13.651585,11.563525,8.871892,8.961773,9.437075,9.385415,9.122429,8.940248] 
speedup_pthread = [1.0 , 1.41 , 1.51 , 1.52 , 1.43 ,1.39 , 1.37 ,1.33]
ambdal = [1/(0.19 + 0.81/x) for x in cores]
mean = [times[0]/times[i] for i in range(len(times))]

plt.figure(num=None, figsize=(8, 6), dpi=80, facecolor='w', edgecolor='k')
plt.plot(cores , mean , 'bo-' , label = "OpenMP")
plt.plot(cores,speedup_pthread , 'ro-' , label = "Pthreads") 
plt.plot(cores , ambdal , 'g--', label = "Amdahl's ")
plt.xlabel("Number of Cores")
plt.ylabel("Speedup")
plt.title("Speedup vs Number of Cores")
plt.legend(loc = 2)
plt.savefig("ambadal.pdf")
plt.show()
