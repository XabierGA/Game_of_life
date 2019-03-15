import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.optimize import curve_fit
sns.set()
sns.set_style('whitegrid')
time = np.loadtxt("data.txt")
data_N = np.loadtxt("numbers.txt")
mean = []
std = []
for i in range(len(time)):
	mean.append(time[i][0])
	std.append(time[i][1])

def function(x,a ,b,c):
    return a*x*np.log(b*x)+c

param , popt = curve_fit(function, data_N , mean)

residuals = np.zeros(len(data_N))
for i in range(len(data_N)):
	residuals[i] = mean[i] - function(data_N[i] , *param)

ss_res = np.sum(residuals**2)
ss_tot = np.sum((mean - np.mean(mean))**2)

r_squared = 1 - (ss_res/ss_tot)

print("Fitting function to a*x*log(b*x)+c \n \n")
print("Values of the coefficients: \n")
print("A ::---> %f",param[0] , "+-" , np.sqrt(np.diag(popt)[0]))
print("B ::---> %f",param[1] , "+-" , np.sqrt(np.diag(popt)[1]))
print("C ::---> %f",param[2] , "+-" , np.sqrt(np.diag(popt)[2]))


print("\n \n")
print("Value of R^2 :::-->", r_squared)
print("\n \n")

figure = plt.figure(num = None, figsize=(15,12),dpi = 80 , facecolor = 'w' , edgecolor = 'k')

plt.errorbar(data_N , mean , xerr = 0, yerr = std , fmt = 'ro' , ecolor = 'r' , markersize = 10 , label = "Measured times")
numbers = np.linspace(min(data_N) , max(data_N) , 10000)
y_fit = []
for i in range(len(numbers)):
	y_fit.append(function(numbers[i] , *param))
plt.plot(numbers , y_fit , 'c-' , label = "$n log(n)$ fit")
plt.ylabel("Time (s)")
plt.title("Complexity analysis of the Barnes-Hut algorithm")
plt.xlabel("N")
plt.legend(loc=2)
print("Input a name with .pdf extension for the image")
name = input()
plt.savefig(name)
plt.show(True) 
