#include<iostream>
#include<cmath>
#include<fstream>
#include <iostream>
using namespace std;
float v = 1e-4; // [m**2/s] thermal diffusivity guessed value. The value given in homework has dimensional inconsistency
float dt = 100; // [s] this agrees with stability condition
float time = 2500; // [s] total time
float dx = 1.0; // [m]
float dy = 1.0; // [m]
float L = 50.0; // [m] size of the square side
int N_L = int(L/dx); // t grid
int N_t = int(time/dt); // x or y grid
float n = v*dt/(2.0*dx*dx); // this should be less than 0.5 (stability condition)

void calculate_and_write(ofstream &file, string boundary){
    float T[N_L][N_L], T_new[N_L][N_L]; // T is actual temperature and T_new is future one
    
}

int main(){
    
    return 0;
}