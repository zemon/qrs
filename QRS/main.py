import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("filtered.txt")
searchback_times = np.loadtxt("sbTime.txt")
searchback_peaks = np.loadtxt("sbPeaks.txt")
times = np.loadtxt("time.txt")
peaks = np.loadtxt("peaks.txt")
threshold1 = np.loadtxt("threshold1.txt")
threshold2 = np.loadtxt("threshold2.txt")

plt.plot(data)
plt.plot(threshold1)
plt.plot(threshold2)
plt.plot(times, peaks, 'o')
plt.plot(searchback_times, searchback_peaks, 'o')
plt.legend(["Data", "Threshold 1", "Threshold 2", "Searchback peak", "Ordinary peak"])
plt.show()
