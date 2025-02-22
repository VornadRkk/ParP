import numpy as np
import csv
import pandas as pd
import time
import os

def csvfile_write(csvfile,matrix):
    with open(csvfile,"a",encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(matrix)


def load_matrix_from_csv(file_path):
    return pd.read_csv(file_path, header=None).values

def benchmark_matrix_multiplication(matrix_a, matrix_b, sizes):
    results = {}
    for size in sizes:
        sub_matrix_a = matrix_a[:size, :size]
        sub_matrix_b = matrix_b[:size, :size]
        expected_result_file = os.path.join(f"iteration_{size}", "result.csv")
        expected_result = pd.read_csv(expected_result_file, header=None).values
        start_time = time.time()
        result_matrix = np.dot(sub_matrix_a, sub_matrix_b)
        end_time = time.time()
        elapsed_time = end_time - start_time
        results[size] = elapsed_time
        if np.array_equal(result_matrix, expected_result):
            print(f"Размер {size}x{size}: Результат корректен | Время: {elapsed_time:.6f} секунд")
        else:
            print(f"Размер {size}x{size}: ОШИБКА! Результаты не совпадают")
    
    return results


if __name__ == "__main__":
    #size = 1000000
    random_matrix_one = load_matrix_from_csv("random_matrix_one.csv")
    random_matrix_two = load_matrix_from_csv("random_matrix_two.csv")
    sizes = list(range(100, 1100, 100))
    benchmark_results = benchmark_matrix_multiplication(random_matrix_one,random_matrix_two, sizes)
    #csvfile_write("random_matrix_one.csv",random_matrix_one.reshape(1000,1000))
    #csvfile_write("random_matrix_two.csv",random_matrix_two.reshape(1000,1000))
    