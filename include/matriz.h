#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <exception>
#include <cmath>

template<class TYPE>
class Matriz{
	private:	
		std::vector<std::vector<TYPE> > matriz;
		size_t rows = -1, cols = -1;
		char sep = '\t';
		int rank = -1;
		bool numtype_quote = (typeid(int).hash_code() != typeid(TYPE).hash_code() && typeid(size_t).hash_code() != typeid(TYPE).hash_code()
							&& typeid(float).hash_code() != typeid(TYPE).hash_code() && typeid(double).hash_code() != typeid(TYPE).hash_code()
							&& typeid(unsigned).hash_code() != typeid(TYPE).hash_code() && typeid(short).hash_code() != typeid(TYPE).hash_code()
							&& typeid(long double).hash_code() != typeid(TYPE).hash_code() && typeid(long).hash_code() != typeid(TYPE).hash_code());
	public:
		Matriz(size_t rows, size_t cols);
		Matriz(size_t dim);
		void set_rows(size_t rows){ this->rows = rows; resize(rows, this->cols); }
		void set_cols(size_t cols){ this->cols = cols; resize(this->rows, cols); }
		size_t get_rows(){ return rows; }
		size_t get_cols(){ return cols; }
		void resize(size_t rows = 0, size_t cols = 0);
		int get_rank();
		/*!
		 * Be careful when using this method!! Use only if the template type is numerical!!
		 */
		TYPE det() throw ();
		void insert_element_at(TYPE element, size_t row, size_t col);
		Matriz<TYPE>& get_cofactors_matrix(size_t excluded_row, size_t excluded_col);
		std::ostream& write(std::ostream &out = std::cout);
		std::istream& read(std::istream &in = std::cin);

		Matriz<TYPE>& operator*(Matriz<TYPE>& m);
		std::vector<TYPE>& operator[](const size_t i);

		template<class U>
		friend std::istream& operator>>(std::istream &in, Matriz<U> &m);
		template<class U>
		friend std::ostream& operator<<(std::ostream &out, Matriz<U> m);
};

#include "matriz.cpp"
#endif /** __MATRIZ_H__ **/