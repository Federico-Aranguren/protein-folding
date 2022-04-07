#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <cstdlib>
#include <random>

double move(double x, int N);
double energy(double x, int N); // declaration

int main(int argc, char **argv)
{
    std::cout.setf(std::ios::scientific);
    std::cout.precision(6);
    // declare variables
    int n = atoi(argv[1]);
    //const double exact = (argv[2]);
    //
    //const int size = 10;
    //matriz posiciones
    //double * array;
    //int* pos=new int [n][4];

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 20);





    //A algo aleatorio


    int pos[n][4];
    //for(int i = 0; i < n; i++){
     //   for(int j = 0; j < 4; i++){
      //      if (j==3){
       //         pos[i][j]=i;
        //    }
         //   if (j==4){
         //       pos[i][j]=A;
          //  }
           // pos[i][j]={}








    for(int i = 0; i < n; i++){
        pos[i][0]=i;
        pos[i][1]=0;
        pos[i][2]=i;
        //pos[i][3]=std::rand(20);
        pos[i][3]=distrib(gen);
        std::cout<< pos[i] <<"\t";


    }






    //reserve memory

    std::cout<< pos;
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
