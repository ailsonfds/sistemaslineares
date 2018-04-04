#include <iostream>
#include <vector>
#include <cmath>
#include <string>

double norma_p(std::vector<double> v, double p){
	double soma = 0;
	for(double& x : v){
		soma += pow(abs(x),p);
	}
	return pow(soma,1.0/p);
}

double norma_inf(std::vector<double> v){
	double max = 0;
	for(double& x : v){
		max = std::max(abs(x),abs(max));
	}
}


int main(int argc, char const *argv[])
{
	double p = std::stod(argv[1]);
	std::vector<double> v({1,3,-2});
	std::string str(v.begin(), v.end());
	std::cout << str << "(" << std::cout.precision(60) << p << ") = " << norma_p(v, p) << std::endl;
	return 0;
}