#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Matrix{
public:
    Matrix() {
        num_rows = 0;
        num_cols = 0;
    }

    Matrix(int new_num_rows, int new_num_cols) {
        Reset(new_num_rows, new_num_cols);
    }

    void Reset(int new_num_rows, int new_num_cols) {
        if (new_num_rows < 0 || new_num_cols < 0) {
            throw out_of_range("Out of range");
        } else if (new_num_rows == 0 || new_num_cols == 0) {
            num_rows = 0;
            num_cols = 0;
        } else {
            num_rows = new_num_rows;
            num_cols = new_num_cols;
        }
        matx.assign(num_rows, vector<int>(num_cols, 0));
    }

    int At(int row, int col) const{
        /* if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) {
            throw out_of_range("Out of range");
        } */
        return matx.at(row).at(col);
    }

    int& At(int row, int col) {
        /* if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) {
            throw out_of_range("Out of range");
        } */
        return matx.at(row).at(col);
    } 

    int GetNumRows() const{
        return num_rows;
    }
    int GetNumColumns() const{
        return num_cols;
    }

private:
    int num_rows;
    int num_cols;
    vector<vector<int>> matx;
};

istream& operator>>(istream& stream, Matrix& m) {
    int rows, cols;
    stream >> rows >> cols;
    m.Reset(rows, cols); 
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < cols; ++j) {
            stream >> m.At(i,j);
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& m) {
    int rows = m.GetNumRows();
    int cols =  m.GetNumColumns();
    stream << m.GetNumRows() << " " << m.GetNumColumns() << "\n";
    for (int i{}; i < m.GetNumRows(); ++i ){
        for (int j{}; j < m.GetNumColumns(); ++j) {
            stream << m.At(i, j) << " ";
        }
        stream << "\n";
    }
    return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
        for (int i{}; i < lhs.GetNumRows(); ++i) {
            for (int j{}; j < lhs.GetNumColumns(); ++j) {
                if (lhs.At(i,j) != rhs.At(i,j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
        throw invalid_argument("Invalid argument");
    }
    int rows = lhs.GetNumRows();
    int cols = lhs.GetNumColumns();
    Matrix m(rows, cols);
    for (int i=0; i < rows; ++i) {
        for (int j=0; j < cols; ++j) {
            m.At(i,j) = lhs.At(i,j) + rhs.At(i,j);
        }
    }
    return m;
}


int main() 
{
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;

	return 0;
}