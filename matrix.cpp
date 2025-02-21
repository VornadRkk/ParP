#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <direct.h> 
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<vector<int>> loadCSV(const string& filename) {
    vector<vector<int>> data; 
    ifstream file(filename);  
    string line;
    while (getline(file, line)) { 
        vector<int> row;
        stringstream ss(line);
        string column;
        while (getline(ss, column, ',')) {  
            row.push_back(stoi(column));
        }
        data.push_back(row); 
    }
    file.close();
    return data;
}

void saveCSV(const string& filename, const vector<vector<int>>& matrix) {
    ofstream file(filename);
    for (const auto& row : matrix) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i < row.size() - 1) file << ","; 
        }
        file << "\n";
    }
    file.close();
}

vector<vector<int>> extractSubMatrix(const vector<vector<int>>& matrix, int numRows, int numCols) {
    vector<vector<int>> subMatrix;
    for (int i = 0; i < numRows; i++) {
        vector<int> row;
        for (int j = 0; j < numCols; j++) {
            row.push_back(matrix[i][j]);
        }
        subMatrix.push_back(row);
    }
    return subMatrix;
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    vector<vector<int>> result(A.size(), vector<int>(B[0].size(), 0));
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < B[0].size(); j++) {
            for (size_t k = 0; k < A[0].size(); k++) { 
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

int main() {
    system("chcp 65001");
    vector<vector<int>> random_matrix_one = loadCSV("random_matrix_one.csv");
    vector<vector<int>> random_matrix_two = loadCSV("random_matrix_two.csv");

    for (int i = 1; i * 100 <= 1000; i++) {
        int size = i * 100;
        string dirName = "iteration_" + to_string(size);
        _mkdir(dirName.c_str());
        vector<vector<int>> subMatrix1 = extractSubMatrix(random_matrix_one, size, size);
        vector<vector<int>> subMatrix2 = extractSubMatrix(random_matrix_two, size, size);

        auto start = high_resolution_clock::now();
        vector<vector<int>> result = multiplyMatrices(subMatrix1, subMatrix2);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        saveCSV(dirName + "/result.csv", result);
        ofstream timeFile(dirName + "/execution_time.txt");
        timeFile << "Размер подматрицы: " << size << "x" << size << "\n";
        timeFile << "Время выполнения: " << duration.count() << " мс" << endl;
        timeFile.close();
    }

    return 0;
}
