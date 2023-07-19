#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <stdexcept>

#include "tuple.h"

class Matrix {
   public:
    int rows, cols;
    double* data;
    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        this->data = new double[rows * cols];
    }
    Matrix(int rows, int cols, double* data) {
        this->rows = rows;
        this->cols = cols;
        this->data = new double[rows * cols];
        for (int i = 0; i < rows * cols; ++i) {
            this->data[i] = data[i];
        }
    }
    double get(int row, int col) { return this->data[row * cols + col]; }
    void set(int row, int col, double value) {
        this->data[row * cols + col] = value;
    }
    Matrix operator*(Matrix other) {
        if (this->cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }
        Matrix result = Matrix(this->rows, other.cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                double sum = 0;
                for (int k = 0; k < this->cols; ++k) {
                    sum += this->get(i, k) * other.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }
    Matrix operator*(double scalar) {
        Matrix result = Matrix(this->rows, this->cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result.set(i, j, this->get(i, j) * scalar);
            }
        }
        return result;
    }
    Matrix operator+(Matrix other) {
        Matrix result = Matrix(this->rows, this->cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result.set(i, j, this->get(i, j) + other.get(i, j));
            }
        }
        return result;
    }
    Matrix operator-(Matrix other) {
        Matrix result = Matrix(this->rows, this->cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result.set(i, j, this->get(i, j) - other.get(i, j));
            }
        }
        return result;
    }
    bool operator==(Matrix other) {
        if (this->rows != other.rows || this->cols != other.cols) {
            return false;
        }
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                if (abs(this->get(i, j) - other.get(i, j)) > Tuple::EPSILON) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(Matrix other) { return !(*this == other); }

    Matrix transpose() {
        Matrix result = Matrix(this->cols, this->rows);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result.set(j, i, this->get(i, j));
            }
        }
        return result;
    }
    Tuple operator*(Tuple tuple) {
        // treat tuple as a 4x1 matrix
        if (this->cols != 4) {
            throw std::invalid_argument("Matrix must be 4x4");
        }
        Matrix result = Matrix(4, 1);
        result.set(0, 0, tuple.x);
        result.set(1, 0, tuple.y);
        result.set(2, 0, tuple.z);
        result.set(3, 0, tuple.w);
        result = (*this) * result;
        return Tuple(result.get(0, 0), result.get(1, 0), result.get(2, 0),
                     result.get(3, 0));
    }

    Matrix submatrix(int row, int col) {
        Matrix result = Matrix(this->rows - 1, this->cols - 1);
        int result_row = 0;
        for (int i = 0; i < this->rows; ++i) {
            if (i == row) {
                continue;
            }
            int result_col = 0;
            for (int j = 0; j < this->cols; ++j) {
                if (j == col) {
                    continue;
                }
                result.set(result_row, result_col, this->get(i, j));
                result_col++;
            }
            result_row++;
        }
        return result;
    }

    double determinant() {
        if (this->cols != this->rows) {
            throw std::invalid_argument("Matrix must be square");
        }
        if (this->cols == 1 && this->rows == 1) {
            return this->get(0, 0);
        }
        if (this->cols == 2 && this->rows == 2) {
            return this->get(0, 0) * this->get(1, 1) -
                   this->get(0, 1) * this->get(1, 0);
        }
        double sum = 0;
        for (int i = 0; i < this->cols; ++i) {
            sum += this->get(0, i) * this->cofactor(0, i);
        }
        return sum;
    }

    double cofactor(int row, int col) {
        double sign = (row + col) % 2 == 0 ? 1 : -1;
        return sign * this->submatrix(row, col).determinant();
    }

    bool isInvertible() { return this->determinant() != 0; }

    Matrix invert() {
        if (!this->isInvertible()) {
            throw std::invalid_argument("Matrix is not invertible");
        }
        double det = this->determinant();
        Matrix result = Matrix(this->rows, this->cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result.set(j, i, this->cofactor(i, j) / det);
            }
        }
        return result;
    }

    void print() {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                std::cerr << this->get(i, j) << " ";
            }
            std::cerr << std::endl;
        }
    }
};

#endif  // !MATRIX