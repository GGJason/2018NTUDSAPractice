#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"

Matrix::Matrix(const int& r, const int& c) //constructor
{
	row = r;
	col = c;
	array = new double*[r];
	for (int i = 0 ; i < r ; i ++){
		array[i] = new double[c];
	}
}

Matrix::Matrix(const Matrix& rhs) //copy constructor
{
	row = rhs.row;
	col = rhs.col;
	array = new double*[rhs.row];
	for (int i = 0 ; i < rhs.row ; i ++){
		array[i] = new double[rhs.col];
		for (int j = 0 ; j < rhs.col ; j++){
			array[i][j] = rhs.array[i][j];
		}
	}
}

Matrix::~Matrix() //destructor
{
	for (int i = 0 ; i < row ; i ++){
		delete [] array[i];
	}
	delete [] array;
}

double* & Matrix::operator [](const int& idx) const
{
	return array[idx];
}

Matrix Matrix::operator =(const Matrix& rhs) // assignment constructor
{
	for (int i = 0 ; i < row ; i ++){
		delete [] array[i];
	}
	delete [] array;
	row = rhs.row;
	col = rhs.col;
	array = new double*[rhs.row];
	for (int i = 0 ; i < rhs.row ; i ++){
		array[i] = new double[rhs.col];
		for (int j = 0 ; j < rhs.col ; j++){
			array[i][j] = rhs.array[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator -() const
{
	Matrix m(*this);
	for (int i = 0 ; i < row ; i ++){
		for (int j = 0 ; j < col ; j++){
			m[i][j] = array[i][j] * -1;
		}
	}
	return m;
}

Matrix Matrix::operator +() const
{
	return Matrix(*this);
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
	Matrix m(*this);
	for (int i = 0 ; i < m.row ; i ++){
		for (int j = 0 ; j < m.col ; j++){
			m[i][j] = this->array[i][j] - rhs[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
	Matrix m(*this);
	for (int i = 0 ; i < m.row ; i ++){
		for (int j = 0 ; j < m.col ; j++){
			m[i][j] = this->array[i][j] + rhs[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator *(const Matrix& rhs) const
{
	Matrix m(this->row,rhs.col);
	for (int i = 0 ; i < row ; i++){
		for (int j = 0 ; j < rhs.col ; j++){
			double sum = 0;
			for (int k = 0 ; k < col ; k++){
				sum += array[i][k] * rhs[k][j];
			}
			m[i][j] = sum;
		}
	}
	return m;
}

Matrix Matrix::operator /(const Matrix& rhs) const
{
	return *this * rhs.inverse();
}

Matrix Matrix::inverse() const
{
	Matrix m(row,col*2);
	for (int i = 0 ; i < row ; i++){
		for (int j = 0 ; j < col ; j++){
			m[i][j] = array[i][j];
		}
		m[i][i+col] = 1;
	}
	for (int i = 0 ; i < row ; i++){
		if ( m[i][i] == 0 ){
			for(int j = i+1 ; j < row ; j++){
				if ( m[j][i] != 0 ){
					for (int k = 0 ; k < col * 2 ; k++){
						m[i][k] += m[j][k];
					}
					break;
				}
			}
		}
		double reduce = m[i][i];
		for (int k = i ; k < col * 2; k++){
			m[i][k] /= reduce;
		}
		for (int j = 0 ; j < row; j ++){
			reduce = m[j][i];
			if ( i != j && reduce != 0 ){
				for (int k = i ; k < col * 2; k++){
					m[j][k] -= m[i][k] * reduce;
				}
			}
		}
	}
	Matrix m2(row,col);
	for (int i = 0 ; i < row ; i++){
		for (int j = 0 ; j < col ; j++){
			m2[i][j] = m[i][col+j];
		}
	}
	return m2;
}

void Matrix::read(const char* fn)
{
	int r, c;
	FILE *fp = fopen(fn, "r");
	if(fp == NULL){
		printf("read file [%s] error\n", fn);
		exit(0);
	}
	fscanf(fp, "%d%d", &r, &c);
	Matrix tmp(r, c);
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			fscanf(fp, "%lf", &tmp.array[i][j]);
	fclose(fp);
	*this = tmp;
}

void Matrix::write(const char* fn)
{
	FILE *fp = fopen(fn, "w");
	if(fp == NULL){
		printf("write file [%s] error\n", fn);
		exit(0);
	}
	fprintf(fp, "%d %d\n", row, col);
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			fprintf(fp, "%lf%c", array[i][j], " \n"[j==col-1]);
	fclose(fp);
}

void Matrix::print() const
{
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			printf("%lf%c", array[i][j], " \n"[j==col-1]);
}
