#include "matriz.h"
#include <fstream>

Matriz<double>& jacobi(Matriz<double>& m, Matriz<double>& x){
	std::cout << "Rodei" << std::endl;
	if (){
		x = *(new Matriz<double>(m.get_rows(), 1))
	}
	if (m.get_rows() == m.get_cols()-1 && m.get_rows() == x.get_rows()){
		Matriz<double> *x2 = new Matriz<double>(m.get_rows(), 1);
		for(size_t i = 0; i < m.get_rows(); i++){
			(*x2)[i][0] = 0.0;
			for (size_t j = 0; j < m.get_cols(); j++){
				if (i != j){
					(*x2)[i][0] += m[i][j]*(x[j][0]);
				}
			}
			(*x2)[i][0] /= m[i][i];
		}
		return jacobi(m, *x2);
	}
}

int main(int argc, const char* argv[]){
	std::fstream fs;
	if(argc == 3){
		fs.open(argv[2], std::fstream::in | std::fstream::out);
	}
	if(fs.is_open()){
		size_t size = 0;
		fs >> size;
		std::cout << "Matriz de ordem " << size << std::endl;
		Matriz<double> *m = new Matriz<double>(size, size+1);
		fs >> *m;
		std::cout << jacobi(*m); 
		fs.close();
	}
	return 0;
}