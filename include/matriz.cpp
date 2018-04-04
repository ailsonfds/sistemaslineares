#ifndef __MATRIZ_CPP__
#define __MATRIZ_CPP__

#include "matriz.h"

template<class TYPE>
Matriz<TYPE>::Matriz(size_t rows, size_t cols){
	this->rows = rows;
	this->cols = cols;
	this->matriz.resize(rows);
	for (size_t i = 0; i < rows; ++i){
		this->matriz[i].resize(cols);
	}
}


template<class TYPE>
Matriz<TYPE>::Matriz(size_t dim){
	this->rows = dim;
	this->cols = dim;
	this->matriz.resize(dim);
	for (size_t i = 0; i < dim; ++i){
		this->matriz[i].resize(dim);
	}
}

template<class TYPE>
void Matriz<TYPE>::resize(size_t rows, size_t cols){
	set_rows(rows);
	set_cols(cols);
	this->matriz.resize(rows);
	for (size_t i = 0; i < rows; ++i){
		this->matriz[i].resize(cols);
	}
}

template<class TYPE>
int Matriz<TYPE>::get_rank(){
	if (rows != cols) return -1;
	int rank = (int)rows;
	bool blank_line = true;
	for(size_t i=0; i<rows; i++){
		for(size_t j=0; j<rows; j++){
			if(matriz[i][j] != 0) blank_line = false;
		}
		if(blank_line) rank--;
		blank_line = true;
	}
	return rank;
}

template<class TYPE>
TYPE Matriz<TYPE>::det() throw (){
	if (numtype_quote){
		throw std::bad_typeid();
	}
	if((rows == cols && rows >= 0)){
		TYPE det = 0;
		if(rows == 1){
			det = matriz[0][0];
			return det;
		} else {
			for (size_t i = 0; i < rows; ++i){ 
				TYPE tmp = (this->get_cofactors_matrix(i,0)).det();
				det += tmp*pow(-1,i)*matriz[i][0];
			}
			return det;
		}
	}
	return -1;
}

template<class TYPE>
void Matriz<TYPE>::insert_element_at(TYPE element, size_t row, size_t col){
	matriz[row][col] = element;
}

template<class TYPE>
Matriz<TYPE>& Matriz<TYPE>::get_cofactors_matrix(size_t excluded_row, size_t excluded_col){
	size_t c_rows = this->rows - 1;
	size_t c_cols = this->cols - 1;
	size_t i_c = 0, j_c = 0;
	Matriz<TYPE> *cof = new Matriz<TYPE>(c_rows, c_cols);
	for (size_t i = 0; i < rows; ++i){
		if(i != excluded_row){
			for (size_t j = 0; j < cols; ++j){
				if (j != excluded_col && i_c < c_rows && j_c < c_cols){
					(*cof)[i_c][j_c++] = matriz[i][j];
				}
			}
			j_c = 0;
			i_c++;
		}
	}
	return *cof;
}

template<class TYPE>
Matriz<TYPE>& Matriz<TYPE>::operator*(Matriz<TYPE>& m){
	if (this->cols == m.rows){
		Matriz<TYPE>* result = new Matriz<TYPE>(this->rows, m.cols);
		for (size_t i = 0; i < this->rows; ++i){
			for(size_t j = 0; j < m.cols; ++j){
				for(size_t k = 0; k < m.rows; ++k){
					(*result)[i][j] += ((*this)[i][k])*(m[k][j]);
				}
			}
		}
		return *result;
	}
}

template<class TYPE>
std::vector<TYPE>& Matriz<TYPE>::operator[](const size_t i){
	return matriz[i];
}

template<class TYPE>
std::ostream& Matriz<TYPE>::write(std::ostream& out){
	out << *this;
	return out;
}

template<class TYPE>
std::istream& Matriz<TYPE>::read(std::istream& in){
	in >> *this;
	return in;
}

template<class U>
std::istream& operator>>(std::istream &in, Matriz<U> &m){
	size_t col = -1;
	std::string str;
	m.matriz.clear();
	while(std::getline(in, str)){
		// std::cout << str.size() << " | " << str << std::endl;
		if(str.empty()){
			continue;
		}
		std::istringstream input(str);
		std::vector<U> line;
		U element;
		while(std::getline(input, str, m.sep)){
			if(str.empty()) continue;
			std::istringstream in_results(str);
			in_results >> element;
			if(!str.empty())line.push_back(element);
			str.clear();
		}
		if(col == (size_t) -1 && line.size() != 0){
			col = line.size();
		} else if(line.size() != col){
			std::cerr << "ERRO!! Not a valid Enter" << std::endl;
			abort();
		}
		m.matriz.push_back(line);
	}
	m.rows = m.matriz.size();
	m.cols = m.matriz[0].size();
	in.clear();
	return in;
}

template<class U>
std::ostream& operator<<(std::ostream &out, Matriz<U> m){
	for(size_t i = 0; i < m.matriz.size(); i++){
		for(size_t j = 0; j < m.matriz[i].size() - 1; j++){
			out << m.matriz[i][j] << m.sep;
		}
		out << m.matriz[i][m.matriz[i].size() - 1] << std::endl;
	}
	return out;
}

#endif /** __MATRIZ_CPP__ **/