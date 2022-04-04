#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <cstdlib>

double move(double x, int N);
double energy(double x, int N); // declaration

int main(int argc, char **argv)
{
    std::cout.setf(std::ios::scientific);
    std::cout.precision(6);
    // declare variables
    const double N = (argv[1]);
    const double exact = (argv[2]);
    //
    const int size = 10;
    //matriz posiciones
    double * array;
    double* pos=new double [n]{0.0};
    //reserve memory
    array = new double [N];
    delete [] array;
    delete [] pos;
    //HAGA ALGO CON LAS FUNCIONES
    move(double x, int N);
    energy(double x, int N);



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
