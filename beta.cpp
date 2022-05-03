#include <iostream>
#include <cmath>
//#include <eigen3/Eigen/Dense>
#include <cstdlib>
#include <random>
#include <vector>
#include <math.h>
using namespace std;

vector<int> posible_move(int a, std::vector<vector<int>> b);
double energy(std::vector<vector<int>> P, double matriz[20][20]); // declaration

int main(int argc, char **argv)
{
    std::cout.setf(std::ios::scientific);
    std::cout.precision(6);
    // declare variables
    int N = atoi(argv[1]);
    int n = 20;
    int T = 1; //Temperatura del medio
    const int steps = atoi(argv[2]);


   // int *matriz;
    //matriz = (int *)calloc( n, n );

    vector<vector<int> > Protein ; //{{0,0,1},{1,0,2},{1,1,3},{0,1,4},{-1,1,5},{-1,0,6},{-1,-1,7},{0,-1,8}};
    double matrizj[20][20];
    double deltaE;
    
    std::random_device rd;  
    std::mt19937 genn(rd()); 
    std::uniform_int_distribution<> distribn(1, n);//Ran int number for amino type

    std::random_device rd1;  
    std::mt19937 genJ(rd1()); 
    std::uniform_real_distribution<> distribJ(-4,-2);//Ran real number for matrix J

    std::random_device rd2;
    std::mt19937 genN(rd2());
    std::uniform_int_distribution<> distribN(0, N-1);// Ran int number for the chain

    std::random_device rd4;
    std::mt19937 genP(rd4());
    std::uniform_real_distribution<> distribP(0, 1);// Ran real number for set the probability of movement
    
    for (int i = 0; i < n; i++) { // Matrix construction
    //   cout <<"------------------------------------------------------------------------------------------------------------------" << "\n";
        for (int j = i; j < n; j++){
            matrizj[i][j]=distribJ(genJ);
	        matrizj[j][i]=matrizj[i][j];
        }
	    // for (int l = 0; l < n; l++){
	    //     std::cout << matrizj[i][l] << "\t";
	    // }
        // std::cout << "\n";
    }

    for(int i = 0; i < N; i++){ //Amino vector construction
        int randamino=distribn(genn);
        std::vector<int> amino ={i,0,randamino};
        Protein.push_back(amino); //Protein construction
        //std::cout << Protein[i]  << "\t";
    }
    // for (int i = 0; i < Protein.size(); i++) { //Protein construction
      //   for (int j = 0; j < Protein[i].size(); j++){
        //    std::cout << Protein[i][j] << " ";
         //   }
        //std::cout << std::endl;
   // }
    
    for (int ms = 0; ms <= steps; ms++){
        double emin=0;
        int randomposition = distribN(genN);
        vector<vector<int>> aux_vec = Protein;
        vector<vector<int>> aux_vecmin = Protein;
        aux_vec[randomposition] = posible_move(randomposition, Protein);
        deltaE = energy(aux_vec, matrizj) - energy(Protein, matrizj);
        if (deltaE <= 0){
            Protein = aux_vec;
        }
        else{
            double Boltz_factor = exp(-deltaE/T);
            float prob = distribP(genP);
            if (prob >= Boltz_factor){
                Protein = aux_vec;
            }
        }
        //cout << "\nProteína: \t";
       if (ms == steps+1 ){
        for (int i=0; i < Protein.size();i++){// Pinta proteina y energia                    ||ms ==int(steps/2) ||ms ==steps             ||ms ==int(steps/2
            //cout << "(";
            for (int j=0; j < Protein[i].size()-1;j++){
                //cout << Protein[i][j]<<",";std::endl;
                //cout << Protein[i][j]<< "\t";//<< energy(Protein, matrizj)<< "\t"<< ms << "\t";
                cout << energy(Protein, matrizj)<< "\t";
            }
            //cout << "),\t";
            cout << "\n";
        }
        cout << "\n";
        cout << "\n";
       }
       //cout << energy(Protein, matrizj)<< "\t"<< ms;
       //cout << "\n";

        if (energy(Protein, matrizj) <emin){
            emin = energy(Protein, matrizj);
            aux_vecmin=Protein;
       }
        if (ms == steps ){
            for (int i=0; i < aux_vecmin.size();i++){// Pinta proteina y energia                    ||ms ==int(steps/2) ||ms ==steps             ||ms ==int(steps/2
            //cout << "(";
                for (int j=0; j < aux_vecmin[i].size()-1;j++){
                cout << aux_vecmin[i][j]<<"\t";
                //cout << Protein[i][j]<< "\t";//<< energy(Protein, matrizj)<< "\t"<< ms << "\t";
                //cout << energy(Protein, matrizj)<< "\t";
            }
            //cout << "),\t";
            cout << "\n";
        }
        cout << "\n";
        cout << "\n";
        }
        }

    return 0;
}

vector<int> posible_move(int a, std::vector<vector<int>> b) // implementation
{

    std::vector<vector<int> > posible_movements{{b[a][0] + 1,b[a][1] + 1,b[a][2]},{b[a][0] + 1,b[a][1] -1,b[a][2]},{b[a][0] - 1,b[a][1] + 1,b[a][2]},{b[a][0] - 1,b[a][1] - 1,b[a][2]}};
    // cout << a << "\n";
    // cout << b[a][0] << "\t" <<b[a][1] << "\n";
    for (int j = 0; j < b.size(); j++){
        
        if(b[j][0] == b[a][0] + 1 and b[j][1] == b[a][1] + 1){
            posible_movements[0][0]=-1000;
            posible_movements[0][1]=-1000;
        }
        else if (b[j][0] == b[a][0]+1 and b[j][1] == b[a][1] - 1){
            posible_movements[1][0]=-1000;
            posible_movements[1][1]=-1000;
        }
        else if (b[j][0] == b[a][0] - 1 and b[j][1] == b[a][1] + 1){
            posible_movements[2][0]=-1000;
            posible_movements[2][1]=-1000;
        }
        else if (b[j][0] == b[a][0]-1 and b[j][1] == b[a][1] - 1){
            posible_movements[3][0]=-1000;
            posible_movements[3][1]=-1000;
        }    
    }
    //cout << "Sin tener en cuenta la longitud" << "\n"<< a << "\n" << b[a][0] << "\t"<< b[a][1]<< "\n";
    //for (int i = 0; i < posible_movements.size(); i++){<< "\t"
    //    cout << "\n";
    //}
    // cout << "----------" << "\n";
    for (int i = 0; i < posible_movements.size(); i++){
        if (a != 0 && a != b.size()-1){
            float d1 = sqrt(std::pow(posible_movements[i][0]-b[a+1][0],2)+std::pow(posible_movements[i][1]-b[a+1][1],2));
            float d2 = sqrt(std::pow(posible_movements[i][0]-b[a-1][0],2)+std::pow(posible_movements[i][1]-b[a-1][1],2));
            if (d1 != 1 || d2 != 1){
                posible_movements[i][0]=-1000;
                posible_movements[i][1]=-1000;
            }
        }
        else if (a == b.size()-1){
            float d2 = sqrt(std::pow(posible_movements[i][0]-b[a-1][0],2)+std::pow(posible_movements[i][1]-b[a-1][1],2));
            if (d2 != 1){
                posible_movements[i][0]=-1000;
                posible_movements[i][1]=-1000;
            }
        }
        else if(a == 0){
            float d1 = sqrt(std::pow(posible_movements[i][0]-b[a+1][0],2)+std::pow(posible_movements[i][1]-b[a+1][1],2));
            if (d1 != 1){
                posible_movements[i][0]=-1000;
                posible_movements[i][1]=-1000;
            }
        }
    }
    for (int k = 0; k < posible_movements.size();k++){
        while (posible_movements[k][0]==-1000 && posible_movements[k][1]==-1000){
	        posible_movements.erase(posible_movements.begin()+k);
            k = 0;
        }
    }
    //cout << "amino choosen:\t"<< a << "\n";
    if (!posible_movements.empty()){
        std::random_device rd3;
        std::mt19937 genpm(rd3());
        std::uniform_int_distribution<> distribpm(0, posible_movements.size()-1);// Ran number for posible movements
        int randommov = distribpm(genpm);
        //cout << "Posible movement:\t" << randommov << "\n" << "Posible_movements:" << "\t";
       // for (int i = 0; i < posible_movements.size(); i++){
        //    for (int j = 0; j < posible_movements[i].size(); j++){
                //cout << posible_movements[i][j] << "\t";
      //  }
            //cout << "\nvector posible_mov:\t";
      //  }
        //for (int i = 0; i < posible_movements[randommov].size(); i++){
         //   cout <<posible_movements[randommov][i] << "\t";
        //}
        //cout << "\n";
        return posible_movements[randommov];
    }
    else{
        return b[a];
    }
}
double energy(std::vector<vector<int>> P,double Matriz[20][20]){// implementation
    double E = 0;

    for (int i = 0; i < P.size(); i++){//se situa en un aminoácido
        //cout << i << "\n" << P[i][0] << "\t" << P[i][1] << "\n";
        //cout << "---------------" << "\n";
        std::vector<vector<int> > closest_amino{{P[i][0] + 1,P[i][1],0},{P[i][0],P[i][1] + 1,0},{P[i][0] - 1,P[i][1], 0},{P[i][0],P[i][1]-1, 0}};
        for (int j = 0; j < closest_amino.size(); j++){//se situa en las posiciones cercanas del i.esimo aminoácido
            for (int l = 0; l < P.size(); l++){//Revisa si algun amino está en la posicion j-esima de closest_position
                if (P[l][0] == closest_amino[j][0] && P[l][1] == closest_amino[j][1]){
                    if (l == i+1 || l == i-1){
                        closest_amino[j][0]=-1000;
                        closest_amino[j][1]=-1000;
                    }

                    else{
                        closest_amino[j][2]=P[l][2];
                        break;
                    }
                }
            }
            if (closest_amino[j][2]==0){
                closest_amino[j][0]=-1000;
                closest_amino[j][1]=-1000;
            }
        }
        for (int k = 0; k < closest_amino.size();k++){
            while (closest_amino[k][0]==-1000 && closest_amino[k][1]==-1000){
                closest_amino.erase(closest_amino.begin()+k);
                k = 0;
            }
        }
	    // for (int t =0; t < closest_amino.size(); t++){
	    //     cout << closest_amino[t][0] << "\t"<< closest_amino[t][1] << "\t"<< closest_amino[t][2] << "\n";
	    // }
	//cout << "|||||||||||||||||" << "\n";
	for (int y = 0; y < closest_amino.size(); y++){
        //cout << "//////" << "\t" <<Matriz[i][closest_amino[y][2]-1] << "\n"; 
        E = E + (Matriz[i][closest_amino[y][2]-1])/2;
	}
	
    }
    //cout << "La energía es:" << E << "\n";
    return E;
}
