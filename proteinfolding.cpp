#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <cstdlib>
#include <random>
#include <vector>
using namespace std;

double move(double x, int N);
double energy(double x, int N); // declaration

int main(int argc, char **argv)
{
    std::cout.setf(std::ios::scientific);
    std::cout.precision(6);
    // declare variables
    int N = atoi(argv[1]);
    //const double exact = (argv[2]);


    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 20);//tipo de aminoacido

    std::random_device rd1;  //W
    std::mt19937 gen1(rd1()); //
    std::uniform_real_distribution<> distribucion(-4,-2);//valores para la matriz J


    vector<vector<int> > vec{};
    double matrizj[20][20];


    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++){
            matrizj[i][j]=distribucion(gen1);
            std::cout << matrizj[i][j] << " ";}
        std::cout << std::endl;
     }



    for(int i = 0; i < N; i++){
        std::vector<int> amino ={i,0,i,distrib(gen)};
        vec.push_back(amino);

    }
     for (int i = 0; i < vec.size(); i++) {
         for (int j = 0; j < vec[i].size(); j++){
            std::cout << vec[i][j] << " ";}
        std::cout << std::endl;
     }

    //std::cout<< pos;
    //array = new double [N];
    //delete [] array;
    //delete [] pos;
    //HAGA ALGO CON LAS FUNCIONES
    //move(double x, int N);
    //energy(double x, int N);
     //std::cout << a << std::endl; PARA MOSTAR ALGO EN PANTALLA

     return 0;
}

double move(double x, int N) // implementation
{

    return 0;
}
double energy(double x, int N) // implementation
{
    return 0;
}
