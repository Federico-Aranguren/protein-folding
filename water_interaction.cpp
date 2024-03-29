#include <iostream>
#include <cmath>
#include <cstdlib>
#include <random>
#include <vector>
#include <math.h>
using namespace std;

const int n = 20;  //amino types
double matrizj[n][n];

//Declaration of functions
vector<int> posible_move(int a, std::vector<vector<int>> b);
double energy(std::vector<vector<int>> P, double Matriz[n][n]);


int main(int argc, char **argv)
{
    std::cout.setf(std::ios::scientific);
    std::cout.precision(6);
    // declare variables
    int N = atoi(argv[1]); //lenght of the protein
    float T = 10; //Temperatura del medio
    const int steps = atoi(argv[2]); // Number of steps of Montecarlo
    const int simul = atoi(argv[3]); // Number of simulations to run
    vector<vector<int> > Protein;
    vector<vector<int> > InitialProtein;
    double deltaE;

    std::mt19937 genn(int (1)); //seed is fixed
    std::uniform_int_distribution<> distribn(1, n);//Ran int number for amino type

    std::mt19937 genJ(int (2)); //seed is fixed
    std::uniform_real_distribution<> distribJ(-4,-2);//Ran real number for matrix J

    std::random_device rd2;
    std::mt19937 genN(rd2());   //Set random seed for distribution
    std::uniform_int_distribution<> distribN(0, N-1);// Ran int number for the chain

    std::random_device rd4;
    std::mt19937 genP(rd4());   //Set random seed for distribution
    std::uniform_real_distribution<> distribP(0, 1);// Ran real number for set the probability of movement

    std::mt19937 genw(int (3)); //seed is fixed
    std::uniform_int_distribution<> distribw(1, 2);//Ran int number for amino type


    for (int i = 0; i < n; i++) { // Matrix construction
        for (int j = i; j < n; j++){
            matrizj[i][j]=distribJ(genJ)*pow(-1,distribw(genw));
	        matrizj[j][i]=matrizj[i][j];
        }
	    // for (int l = 0; l < n; l++){
	    //     std::cout << matrizj[i][l] << "\t";
	    // }
        // std::cout << "\n";
    }

    for(int i = 0; i < N; i++){ //Amino vector construction
        std::vector<int> amino ={i,0,distribn(genn)};
        InitialProtein.push_back(amino); //Protein construction

    }

    
    double E; 
    vector<vector<int>> Eminprotein;

    for (int s = 0; s < simul; s++){
        Protein = InitialProtein;
        cout << "Ms\t" << "E\n";
        double Emin = 5000;
        for (int ms = 0; ms <= steps; ms++){
            E =  energy(Protein, matrizj);
            int randomposition = distribN(genN);    //Choose random position from random distrib
            vector<vector<int>> aux_vec = Protein;  //Defines an auxiliar vector for determining
            aux_vec[randomposition] = posible_move(randomposition, Protein);    //Take the hypothetical protein when makes a movement
            deltaE = energy(aux_vec, matrizj) - E;   //Defines the delta of energy between a random movement
            if (deltaE <= 0){   //deltaE<=0 means the movement will be done
                Protein = aux_vec;
            }
            else{   //deltaE>0 means the movement has a probability of be done determinated by the boltz factor
                double Boltz_factor = exp(-deltaE/T); //Boltz factor is defined it goes from 0 (when deltaE tends to inf)to 1 (when deltaE=0)
                float prob = distribP(genP); //Probability is calculated based on a normal distrib from 0 to 1
                if (prob <= Boltz_factor){// if prob >= Boltz factor the movement will be done
                    Protein = aux_vec;
                }
            }
            if (E < Emin){
                Emin = E;
                Eminprotein = Protein;
            }
            cout << ms << "\t" << E << "\n";

        }
        cout << "X\t" << "Y\n";    //prints the protein after each montecarlo step

        for (int i=0; i < Eminprotein.size();i++){
            for (int j=0; j < Eminprotein[i].size()-1;j++){
                cout << Eminprotein[i][j] << "\t";
            }
            cout << "\n";
        }
    }
    return 0;
}

vector<int> posible_move(int a, std::vector<vector<int>> b) // implementation
{
    // Posible movemets is created based on the diagonal points around the random amino a
    std::vector<vector<int> > posible_movements;
    std::vector<int> aux_pm;
    if(a != 0 && a!= b.size()-1){
        for (int k = 1; k >= -1; k -= 2){
            for (int l = 1;l >= -1; l-= 2){
                aux_pm={b[a][0]+k,b[a][1]+l,b[a][2]};
                bool b1 = false;
                float d1 = sqrt(pow(aux_pm[0]-b[a+1][0],2)+pow(aux_pm[1]-b[a+1][1],2));
                float d2 = sqrt(pow(aux_pm[0]-b[a-1][0],2)+pow(aux_pm[1]-b[a-1][1],2));
                if (d1 == 1.0 && d2 ==1.0){
                    b1 = true;
                    for (int j = 0; j < b.size(); j++){
                        if (aux_pm[0] == b[j][0] && aux_pm[1] == b[j][1]){
                            b1 = false;
                            break;
                        }            
                    }
                }
                if (b1 == true){
                    posible_movements.push_back(aux_pm);
                }
                aux_pm.clear();
            }
        }
    }
    else if (a == 0){
        for (int k = 1; k >= -1; k -= 2){
            for (int l = 1;l >= -1; l-= 2){
                aux_pm={b[a][0]+k,b[a][1]+l,b[a][2]};
                bool b1 = false;
                float d1 = sqrt(pow(aux_pm[0]-b[a+1][0],2)+pow(aux_pm[1]-b[a+1][1],2));
                if (d1 == 1.0){
                    b1 = true;
                    for (int j = 0; j < b.size(); j++){
                        if (aux_pm[0] == b[j][0] && aux_pm[1] == b[j][1]){
                            b1 = false;
                            break;
                        }
                    }
                }
                if (b1 == true){
                    posible_movements.push_back(aux_pm);
                }
                aux_pm.clear();
            }
        }
    }
    else if(a == b.size()-1){
        for (int k = 1; k >= -1; k -= 2){
            for (int l = 1;l >= -1; l-= 2){
                aux_pm={b[a][0]+k,b[a][1]+l,b[a][2]};
                    bool b1 = false;
                    float d2 = sqrt(pow(aux_pm[0]-b[a-1][0],2)+pow(aux_pm[1]-b[a-1][1],2));
                    if (d2 == 1.0){
                        b1 = true;
                        for (int j = 0; j < b.size(); j++){
                            if (aux_pm[0] == b[j][0] && aux_pm[1] == b[j][1]){
                                b1 = false;
                                break;
                            }
                        }
                    }
                    if(b1 == true){
                        posible_movements.push_back(aux_pm);                       
                    }
                aux_pm.clear();
            }    
        }    
    }
    // // Posible movemets is created based on the diagonal points around the random amino a
    // std::vector<vector<int> > posible_movements{{b[a][0] + 1,b[a][1] + 1,b[a][2]},{b[a][0] + 1,b[a][1] -1,b[a][2]}
    // ,{b[a][0] - 1,b[a][1] + 1,b[a][2]},{b[a][0] - 1,b[a][1] - 1,b[a][2]}};
    // for (int j = 0; j < b.size(); j++){ //check if there's an amino occupying some posible movement
    //     if(b[j][0] == b[a][0] + 1 and b[j][1] == b[a][1] + 1){  //marks the occupied position
    //         posible_movements[0][0]=-1000;
    //         posible_movements[0][1]=-1000;
    //     }
    //     else if (b[j][0] == b[a][0]+1 and b[j][1] == b[a][1] - 1){  //marks the occupied position
    //         posible_movements[1][0]=-1000;
    //         posible_movements[1][1]=-1000;
    //     }
    //     else if (b[j][0] == b[a][0] - 1 and b[j][1] == b[a][1] + 1){    //marks the occupied position
    //         posible_movements[2][0]=-1000;
    //         posible_movements[2][1]=-1000;
    //     }
    //     else if (b[j][0] == b[a][0]-1 and b[j][1] == b[a][1] - 1){  //marks the occupied position
    //         posible_movements[3][0]=-1000;
    //         posible_movements[3][1]=-1000;
    //     }
    // }
    // for (int i = 0; i < posible_movements.size(); i++){ //checks if a posible movement that alters the protein lenght
    //     if (a != 0 && a != b.size()-1){
    //         float d1 = sqrt(std::pow(posible_movements[i][0]-b[a+1][0],2)+std::pow(posible_movements[i][1]-b[a+1][1],2));
    //         float d2 = sqrt(std::pow(posible_movements[i][0]-b[a-1][0],2)+std::pow(posible_movements[i][1]-b[a-1][1],2));
    //         if (d1 != 1 || d2 != 1){
    //             posible_movements[i][0]=-1000;
    //             posible_movements[i][1]=-1000;
    //         }
    //     }
    //     else if (a == b.size()-1){  //The function on the extremes must be redefined
    //         float d2 = sqrt(std::pow(posible_movements[i][0]-b[a-1][0],2)+std::pow(posible_movements[i][1]-b[a-1][1],2));
    //         if (d2 != 1){
    //             posible_movements[i][0]=-1000;
    //             posible_movements[i][1]=-1000;
    //         }
    //     }
    //     else if(a == 0){
    //         float d1 = sqrt(std::pow(posible_movements[i][0]-b[a+1][0],2)+std::pow(posible_movements[i][1]-b[a+1][1],2));
    //         if (d1 != 1){
    //             posible_movements[i][0]=-1000;
    //             posible_movements[i][1]=-1000;
    //         }
    //     }
    // }
    // for (int k = 0; k < posible_movements.size();k++){  //Removes the marked movements
    //     while (posible_movements[k][0]==-1000 && posible_movements[k][1]==-1000){
	//         posible_movements.erase(posible_movements.begin()+k);
    //         k = 0;
    //     }
    // }
    // cout << "------------------------------------\n";
    // cout << a << "\n";
    // cout << b[a][0] << b[a][1] << b[a][2] << "\n";
    // for (int i = 0; i < posible_movements.size(); i++){
    //     for (int j = 0; j < posible_movements[i].size();j++){
    //         cout << posible_movements[i][j] << "\t";
    //     }
    //     cout << "\n";
    //}
    if (!posible_movements.empty()){    //If there's a posible movement we select a random one
        std::random_device rd3;
        std::mt19937 genpm(rd3());
        std::uniform_int_distribution<> distribpm(0, posible_movements.size()-1);// Ran number for posible movements
        int randommov = distribpm(genpm);
        return posible_movements[randommov];    //The function returns a random posible movement
    }
    else{
        return b[a];    //If theres no posible movements the function returns the original position for the amino selected
    }
}
double energy(std::vector<vector<int>> P,double Matriz[n][n]){// implementation
    double E = 0;
    std::vector<vector<int>> closest_amino;
    std::vector<vector<int>> aux_ca;
    for (int i = 0; i < P.size(); i++){//se situa en un aminoácido
        for (int l = 1; l >= -1; l -= 2){
            aux_ca.push_back({P[i][0]+l,P[i][1],0});
            aux_ca.push_back({P[i][0],P[i][1]+l,0});
            for (int t = 0; t < aux_ca.size(); t++){
                for (int u = 0; u < P.size();u++){
                    if (P[u][0] == aux_ca[t][0] && P[u][1] == aux_ca[t][1]){
                        if(u != i-1 && u!= i+1){
                            aux_ca [t][2] = P[u][2];
                            closest_amino.push_back(aux_ca[t]);
                            break;
                        }
                    }
                }
            }
            aux_ca.clear();        
        }
	    for (int y = 0; y < closest_amino.size(); y++){
            E = E + (Matriz[P[i][2]][closest_amino[y][2]-1])/2;   //Energy is calculated 
	    }
        closest_amino.clear();
    }
    return E;   
    //The function returns the value of the energy
    // for (int i = 0; i < P.size(); i++){//se situa en un aminoácido
    //     std::vector<vector<int> > closest_amino{{P[i][0] + 1,P[i][1],0},{P[i][0],P[i][1] + 1,0},{P[i][0] - 1,P[i][1], 0},{P[i][0],P[i][1]-1, 0}};
    //     for (int j = 0; j < closest_amino.size(); j++){//se situa en las posiciones cercanas del i.esimo aminoácido
    //         for (int l = 0; l < P.size(); l++){//Revisa si algun amino está en la posicion j-esima de closest_position
    //             if (P[l][0] == closest_amino[j][0] && P[l][1] == closest_amino[j][1]){
    //                 if (l == i+1 || l == i-1){  //If the amino that is close is connected to the amino selected we discard it
    //                     closest_amino[j][0]=-1000;
    //                     closest_amino[j][1]=-1000;
    //                 }

    //                 else{
    //                     closest_amino[j][2]=P[l][2]; //The amino type of the aminoacid is saved
    //                     break;
    //                 }
    //             }
    //         }
    //         if (closest_amino[j][2]==0){    //If there's no closest amino we discard it
    //             closest_amino[j][0]=-1000;
    //             closest_amino[j][1]=-1000;
    //         }
    //     }
    //     for (int k = 0;k < closest_amino.size();k++){   //Aminos marked to be erased are erased
    //         while (closest_amino[k][0]==-1000 && closest_amino[k][1]==-1000){
    //             closest_amino.erase(closest_amino.begin()+k);
    //             k = 0;
    //         }
    //     }
	// for (int y = 0; y < closest_amino.size(); y++){
    //     E = E + (Matriz[P[i][2]][closest_amino[y][2]-1])/2;   //Energy is calculated
	// }

    // }
    // return E;   //The function returns the value of the energy
}
