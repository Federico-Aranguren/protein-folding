#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <cstdlib>
#include <random>
#include <vector>
#include <math.h>
using namespace std;

double move(int a, std::vector<vector<int>> b);
double energy(double x, int N); // declaration

int main(int argc, char **argv)
{
    std::cout.setf(std::ios::scientific);
    std::cout.precision(6);
    // declare variables
    int N = atoi(argv[1]);
    int n = 20;
    //const int steps = (atoi[2]);
    vector<vector<int> > Protein = {{0,0},{1,0},{1,1}};
    double matrizj[n][n];
    
    
    std::random_device rd;  
    std::mt19937 genn(rd()); 
    std::uniform_int_distribution<> distribn(1, n);//Ran number for amino type

    std::random_device rd1;  
    std::mt19937 genJ(rd1()); 
    std::uniform_real_distribution<> distribJ(-4,-2);//Ran number for matrix J

    std::random_device rd2;
    std::mt19937 genN(rd2());
    std::uniform_int_distribution<> distribN(0, N-1);// Ran number for the chain
    
    int randomposition = distribN(genN);
    
    for (int i = 0; i < n; i++) { // Matrix construction
        for (int j = 0; j < n; j++){
            matrizj[i][j]=distribJ(genJ);
            //std::cout << matrizj[i][j] << " ";
            }
        std::cout << std::endl;
     }

    for(int i = 0; i < N; i++){ //Amino vector construction
        std::vector<int> amino ={i,0,i,distribn(genn)};
        //Protein.push_back(amino); //Protein construction

    }
     for (int i = 0; i < Protein.size(); i++) { //Protein construction
         for (int j = 0; j < Protein[i].size(); j++){
            //std::cout << Protein[i][j] << " ";    
            }
        std::cout << std::endl;
     }
    cout << randomposition << "\n";
    move(randomposition, Protein);

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

double move(int a, std::vector<vector<int>> b) // implementation
{
    
    std::vector<vector<int> > posible_movements{{b[a][0] + 1,b[a][1] + 1},{b[a][0] + 1,b[a][1] -1},{b[a][0] - 1,b[a][1] + 1},{b[a][0] - 1,b[a][1] - 1}};
    cout << b[a][0] << "\t" <<b[a][1] << "\n";
    for (int j = 0; j < b.size(); j++){
        
        if(b[j][0] == b[a][0] + 1 and b[j][1] == b[a][1] + 1){
            posible_movements.erase(posible_movements.begin());
        }
        else if (b[j][0] == b[a][0]+1 and b[j][1] == b[a][1] - 1)

        {
            posible_movements.erase(posible_movements.begin()+1);
        }
        else if (b[j][0] == b[a][0] - 1 and b[j][1] == b[a][1] + 1)
        {
            posible_movements.erase(posible_movements.begin()+2);
        }
        else if (b[j][0] == b[a][0]-1 and b[j][1] == b[a][1] - 1)
        {
            posible_movements.erase(posible_movements.begin()+3);
        }    
    }
    for (int i = 0; i < posible_movements.size(); i++){
        for (int j = 0; j < posible_movements[i].size(); j++){
            cout << posible_movements[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "----------" << "\n";
    for (int i = 0; i < posible_movements.size(); i++){
        if (a != 0 and a != b.size()-1){
            float d1 = sqrt(std::pow(posible_movements[i][0]-b[a+1][0],2)+std::pow(posible_movements[i][1]-b[a+1][1],2));
            float d2 = sqrt(std::pow(posible_movements[i][0]-b[a-1][0],2)+std::pow(posible_movements[i][1]-b[a-1][1],2));
            if (d1 != 1 || d2 != 1){
                posible_movements.erase(posible_movements.begin()+i);
                i = i-1;
            }
        }
        else if (a = b.size()-1){
            float d2 = sqrt(std::pow(posible_movements[i][0]-b[a-1][0],2)+std::pow(posible_movements[i][1]-b[a-1][1],2));
            if (d2 != 1){
                posible_movements.erase(posible_movements.begin()+i);
                i = i-1;
            }
        }
        else{
            float d1 = sqrt(std::pow(posible_movements[i][0]-b[a+1][0],2)+std::pow(posible_movements[i][1]-b[a+1][1],2));
            if (d1 != 1){
                posible_movements.erase(posible_movements.begin()+i);
                i = i-1;
            }
        }
    } 
    for (int i = 0; i < posible_movements.size(); i++){
        for (int j = 0; j < posible_movements[i].size(); j++){
            cout << posible_movements[i][j] << "\t";
        }
        cout << "\n";
    }
    return 0;
}
double energy(double x, int N) // implementation
{
    return 0;
}
