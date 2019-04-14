import numpy as np
import matplotlib.pyplot as plt
#import seaborn as sns
#sns.set()
#sns.set_style('whitegrid')

cores = np.loadtxt('number_of_cores.txt')

time = np.loadtxt("data.txt")
mean = []
std = []
for i in range(len(time)):
	mean.append(time[i][0])
	std.append(time[i][1])
mean = [mean[0]/mean[i] for i in range(len(mean))]
print(cores)
print(mean)
fig = plt.figure(num=None, figsize=(14, 9), dpi=80, facecolor='w', edgecolor='k')
#plt.errorbar(cores , mean , xerr = 0, yerr = std , fmt = 'ro' , ecolor = 'r' , markersize = 10 , label = "Measured times")
plt.plot(cores , mean , 'bo-' , label = "Experimental Points")
plt.xlabel("Number of Cores")
plt.ylabel("Speedup")
plt.legend(loc = 2)
plt.title("Speedup versus number of cores")
print("Type a name for the figure with .pdf extension")
name = input()
plt.savefig(name)
plt.show(True)
