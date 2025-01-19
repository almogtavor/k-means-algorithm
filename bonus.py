import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.datasets import load_iris
import numpy as np

def plot_elbow_method():
    iris = load_iris()
    X = iris.data

    inertia = []
    k_values = range(1, 11)

    for k in k_values:
        kmeans = KMeans(n_clusters=k, init='k-means++', random_state=0)
        kmeans.fit(X)
        inertia.append(kmeans.inertia_)

    plt.figure(figsize=(8, 5))
    plt.plot(k_values, inertia, marker='o')
    plt.xlabel('Number of clusters (k)')
    plt.ylabel('Inertia')
    plt.title('Elbow Method for Optimal k')
    
    elbow_k = 3
    plt.annotate(f'Elbow Point', xy=(elbow_k, inertia[elbow_k-1]), 
                 xytext=(elbow_k + 1, inertia[elbow_k-1] + 100), 
                 arrowprops=dict(facecolor='black', shrink=0.05))
    
    plt.savefig('elbow.png')
    plt.show()

if __name__ == "__main__":
    plot_elbow_method()
