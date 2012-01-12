/*
 *  Matrix.h
 *  
 *
 *  Created by Fabian Torres on 11/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MMatrixATRIZ_H
#define Matrix_H

#include <iostream>
#include <time.h>

using namespace std;

template <class T>
class Matrix
{
private:
    T mayor_,menor_,moda_,ele,**matr1;
    int dim_Matrix;
public:
    int fils,cols;
    T escalar;
	
    Matrix();
    Matrix(int,int);
    Matrix(const Matrix &m);//constructor copia
	
	void llenar(int fil, int col,T val);
	void imprimir();
	T accesar(int fil, int col);
	
    Matrix<T> operator+ (const Matrix &matr2);
    Matrix<T> operator- (const Matrix &matr2);
    Matrix<T> operator* (const Matrix &matr2);
	
    void eliminar();
	
    ~Matrix();
protected:
};

#endif // Matrix_H

//Constructor por defecto
template<typename T>
Matrix<T>::Matrix()
{
	fils=4;
	cols=4;
}

//Constructor copia
template<typename T>
Matrix<T>::Matrix(const Matrix &m)
{
	*this = m;
}

//Constructor por parametro
template<typename T>
Matrix<T>::Matrix(int fils_ , int cols_)
{
	fils = fils_;
	cols = cols_;
	matr1 = new T*[fils];
	for(int i=0;i<fils;i++){
		matr1[i] = new T[cols];
	}
}

template<typename T>
void Matrix<T>::llenar(int fil, int col,T val)
{
	matr1[fil][col]=val;
	mayor_= matr1[0][0];
	menor_= matr1[0][0];
}

//Imprimir Matrix
template<typename T>
void Matrix<T>::imprimir()
{
	for(int i=0;i<fils;i++){
		for(int j=0;j<cols;j++){
			cout << matr1[i][j] << " ";
		}
		cout << endl << endl;
	}
	cout << endl << endl;
}

template<typename T>
T Matrix<T>::accesar(int fil, int col)
{
	return matr1[fil][col];
}

//Suma de matrices con sobrecarga de operadores
template<typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix &matr2)
{
	Matrix matresult(fils,cols);
	for (int i=0;i<fils;i++){
		for (int j=0;j<cols;j++){
			matresult.matr1[i][j] = matr1[i][j] + matr2.matr1[i][j];
		}
	}
	return matresult;
}

//Resta de matrices con sobrecarga de operadores
template<typename T>
Matrix<T> Matrix<T>::operator- (const Matrix &matr2)
{
	Matrix matresult(fils,cols);
	for (int i=0;i<fils;i++){
		for (int j=0;j<cols;j++){
			matresult.matr1[i][j] = matr1[i][j] - matr2.matr1[i][j];
		}
	}
	return matresult;
}

//Multiplicacion de matrices con sobrecarga de operadores
template<typename T>
Matrix<T> Matrix<T>::operator* (const Matrix &matr2)
{
	Matrix matresult(fils,matr2.cols);
	T total;
	for (int i=0;i<fils;i++){
		for (int j=0;j<matr2.cols;j++){
			for(int k=0;k<cols;k++){
				total += (matr1[i][k] * matr2.matr1[k][j]);
				//para mostrar lo que pasa
				/*cout << "(" << matr1[i][k] << " * " << matr2.matr1[k][j] << ")";
				 if(k<cols-1){
				 cout << " + ";
				 } else {
				 cout << " = " << total;//despues del ultimo muestro la suma
				 }*/
			}
			//cout << endl;
			matresult.matr1[i][j] = total;
			total = 0;//para limpiar el total sumado arriba
		}
	}
	return matresult;
}

template<typename T>
void Matrix<T>::eliminar()
{
	for(int i=0;i<fils;i++){
		delete[] matr1[i];
	}
	delete[] matr1;
}

template<typename T>
Matrix<T>::~Matrix(){}
