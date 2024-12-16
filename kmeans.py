import sys
from typing import List
Vector = List[float]

def calc_distance(vector1:Vector,vector2:Vector):
    pass
def argmin(vector:Vector,centroid:Vector):
    pass
def calculate_new_centroid():
    pass
def kmeans(k:int,iterations:int,vectors:List[Vector],epsilon:float=0.001):
    pass

def main():
    if len(sys.argv) !=4:
        print("Usage: python kmeans.py <K> <iterations> <data_path>")
        return
    _,K,iterations,data_path=sys.argv
    print(K,iterations,data_path)

    with open(data_path, "r") as file:
        lines = file.readlines()  
        vectors = len(lines)  
        
        cords_num = len(lines[0].strip().split(",")) 
        
        print("\nFile Contents:")
        for line in lines:
            print(line.strip())  

        all_dots = [[0.0 for _ in range(cords_num)] for _ in range(vectors)]
    with open(data_path, "r") as file:
        
        for j,line in enumerate(file):
            line_arr = line.split(",")

            for i in range (len(line_arr)):
                all_dots[j][i] = round(float(line_arr[i]),4)


    print("\nmatrix:")
    for i in range(vectors):
        for j in range(cords_num):
            print (f"{all_dots[i][j]} ", end="")
        print()
    

if __name__ == "__main__":
    main()