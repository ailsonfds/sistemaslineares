#include "matriz.h"

template<class TYPE>
void teste(Matriz<TYPE> m1){
	std::cout << "det (" << std::endl << m1 << ") = " << std::endl;
	std::cout << m1.det() << std::endl;	
}

int main(int argc, char const *argv[]){
	try{
		Matriz<double> m1(4);
		Matriz<double> m2(4);
		std::cout.precision(8);
		for (size_t i = 0; i < m1.get_rows(); ++i){
			for (size_t j = 0; j < m1.get_cols(); ++j){
				m1[i][j] = i+j;
			}
		}
		teste(m1);
		for (size_t i = 0; i < m1.get_rows(); ++i){
			for (size_t j = 0; j < m1.get_cols(); ++j){
				m1.insert_element_at(sin(i+j)*(i+j),i,j);
			}
		}
		teste(m1);
		for (size_t i = 0; i < m2.get_rows(); ++i){
			for (size_t j = 0; j < m2.get_cols(); ++j){
				m2.insert_element_at(i+j,i,j);
			}
		}
		teste(m2);
		for (size_t i = 0; i < m2.get_rows(); ++i){
			for (size_t j = 0; j < m2.get_cols(); ++j){
				m2.insert_element_at(sin(i+j)*(i+j),i,j);
				// std::cout << m2[i][j] << " ";
			}
			// std::cout << std::endl;
		}
		teste(m2);
		std::cout << "Testando multiplicação de matrizes..." << std::endl;
		std::cout << m1 << "*\n" << m2 << std::endl;
		Matriz<double> m3 = m1*m2;
		for (size_t i = 0; i < m3.get_rows(); ++i){
			for (size_t j = 0; j < m3.get_cols(); ++j){
				// m2.insert_element_at(sin(i+j)*(i+j),i,j);
				std::cout << m3[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	} catch(std::exception& e){
		std::cout << e.what();
	} catch(std::string& e){
		std::cout << e << std::endl;
	}
	return 0;
}