import numpy as np
import csv

def csvfile_write(csvfile,matrix):
    with open(csvfile,"a",encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(matrix)

if __name__ == "__main__":
    size = 1000000
    random_matrix_one = np.random.randint(0,255,size)
    random_matrix_two = np.random.randint(0,255,size)
    csvfile_write("random_matrix_one.csv",random_matrix_one.reshape(1000,1000))
    csvfile_write("random_matrix_two.csv",random_matrix_two.reshape(1000,1000))

    
    