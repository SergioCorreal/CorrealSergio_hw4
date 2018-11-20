#include<iostream>
#include<cmath>
#include<fstream>
#include <iostream>
#include <string.h>
using namespace std;
float v = 1e-4; // [m**2/s] thermal diffusivity guessed value. The value given in homework has dimensional inconsistency
float dt = 100; // [s] this agrees with stability condition
float time = 25000000; // [s] total time
float dx = 1.0; // [m]
float dy = 1.0; // [m]
float L = 50.0; // [m] size of the square side
int N_L = int(L/dx); // t grid
int N_t = int(time/dt); // x or y grid
float eta = v*dt/(2.0*dx*dx); // this should be less than 0.5 (stability condition)

void write_initial(ofstream &initial){
    float T[N_L][N_L]; // T is actual temperature and T_new is future one
    int i,j; 

    for(i = 0; i < N_L; i++)
    {
        for(j = 0; j < N_L; j++)
        {
            
            if (   sqrt( pow((i-25),2)+ pow((j-25),2) ) <= 5.0 ) {
                T[i][j] = 100.0;
                
            }
            
            else
            {
                T[i][j] = 10.0;
            }
            
        }
    }
    // write
    for(i = 0; i < N_L; i++)
    {
        for(j = 0; j < N_L; j++)
        {
            
            if (   j == N_L -1 ) {
                initial << T[i][j] << endl;
            }
            
            else
            {
                initial << T[i][j] << ",";
            }
            
        }
    }
}
/*
boundary 1 is for closed, 2 for opened and 3 for periodic 
*/
void write_evolution(ofstream &i1, ofstream &i2, ofstream &end , int boundary){

    float T[N_L][N_L], T_new[N_L][N_L]; // T is actual temperature and T_new is future one
    int i,j; // I will use i for x-index and j for y-index
    int n; // I will use n for t-index
    float t = 0;
    // Initial condition

    for(i = 0; i < N_L; i++)
    {
        for(j = 0; j < N_L; j++)
        {
            if (   sqrt( pow((i-25),2)+ pow((j-25),2) ) <= 5.0 ) {
                T[i][j] = 100.0;
                T_new[i][j] = 100.0;
            }
            else
            {
                T[i][j] = 10.0;
            }
            
        }
    }
    
    // Evolve
    
    for(n = 0; n < N_t; n++)
    {
        // write
        if (n == 5) {
            for(i = 0; i < N_L; i++)
            {
                for(j = 0; j < N_L; j++)
                {

                    if (   j == N_L -1 ) {
                        i1 << T[i][j] << endl;
                    }

                    else
                    {
                        i1 << T[i][j] << ",";
                    }

                }
            }
        }
        
        else if (n == int(N_t* 2/4)) {
            for(i = 0; i < N_L; i++)
            {
                for(j = 0; j < N_L; j++)
                {

                    if (   j == N_L -1 ) {
                        i2 << T[i][j] << endl;
                    }

                    else
                    {
                        i2 << T[i][j] << ",";
                    }

                }
            }
        }else if (n == N_t -1) {
            for(i = 0; i < N_L; i++)
            {
                for(j = 0; j < N_L; j++)
                {

                    if (   j == N_L -1 ) {
                        end << T[i][j] << endl;
                    }

                    else
                    {
                        end << T[i][j] << ",";
                    }

                }
            }
        }
        
        for(i = 0; i < N_L; i++)
        {
            for(j = 0; j < N_L; j++)
            {
                if (   sqrt( pow((i-25),2)+ pow((j-25),2) ) > 5.0 ) { // Just evolve points out the circle

                    if(i == 0 || i == N_L-1 || j == 0 || j == N_L-1){
                        
                        if (boundary == 1) { // closed frontiers
                            T_new[i][j] = 10.0;
                        }
                        else if (boundary == 2) { // open frontiers
                            T_new[i][0] = T[i][1];
                            T_new[i][N_L-1] = T[i][N_L-2];
                            if (j != 0 && j != N_L-1) {
                                T_new[0][j] = T[1][j];
                                T_new[N_L -1][j] = T[N_L -2][j];
                            }
                        }
                        else if (boundary == 3){ // periodic frontiers
                            
                            if (i == 0) {
                                T_new[0][0]= T[i][j] + eta*(T[i+1][j] + T[N_L-2][j] + T[i][j+1] + T[i][N_L-2] - 4.0*T[i][j] );
                                T_new[0][N_L-1]= T[i][j] + eta*(T[i+1][j] + T[N_L-2][j] + T[i][1] + T[i][j-1] - 4.0*T[i][j] );
                               if (j != 0 && j != N_L-1) {
                                   T_new[0][j]= T[i][j] + eta*(T[i+1][j] + T[N_L-2][j] + T[i][j+1] + T[i][j-1] - 4.0*T[i][j] );
                               }
                               
                            }
                            else if(i == N_L-1){
                                T_new[N_L-1][0]= T[i][j] + eta*(T[1][j] + T[i-1][j] + T[i][j+1] + T[i][N_L -2] - 4.0*T[i][j] );
                                T_new[N_L-1][N_L-1]= T[i][j] + eta*(T[1][j] + T[i-1][j] + T[i][1] + T[i][j-1] - 4.0*T[i][j] );
                               if (j != 0 && j != N_L-1) {
                                   T_new[N_L-1][j]= T[i][j] + eta*(T[1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1] - 4.0*T[i][j] );
                               }
                            }
                            else if (j == 0){
                                if (i != 0 && i != N_L-1) {
                                    T_new[i][0]= T[i][j] + eta*(T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][N_L-2] - 4.0*T[i][j] );
                                }  
                            }
                            else if (j == N_L-1){
                                if (i != 0 && i != N_L-1) {
                                    T_new[i][N_L-1]= T[i][j] + eta*(T[i+1][j] + T[i-1][j] + T[i][N_L-2] + T[i][j-1] - 4.0*T[i][j] );
                                }  
                            }
                        }
                        
                    }
                    else
                    {
                        T_new[i][j] = T[i][j] + eta*(T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1] - 4.0*T[i][j] );
                    }
                }
            }
        }
        // Update
        for(i = 0; i < N_L; i++)
        {
            for(j = 0; j < N_L; j++)
            {
                T[i][j] = T_new[i][j];
            }
        }
        t += dt;
        cout << t << endl;
    }
    
}

int main(){
    /*
    Define the output files:
    c is for closed boundaries, 
    o is for opened,
    and p is for periodic.
    i1 is the firts intermediate state,
    i2 is the second intermediate state,
    f is the final state.
    */
    ofstream INITIAL;
    INITIAL.open("pde_initial.txt");
    
    ofstream ci1, ci2, cf; 
    ci1.open("pde_ci1.txt");
    ci2.open("pde_ci2.txt");
    cf.open("pde_cf.txt");
    
    ofstream oi1, oi2, of; 
    oi1.open("pde_oi1.txt");
    oi2.open("pde_oi2.txt");
    of.open("pde_of.txt");

    ofstream pi1, pi2, pf; 
    pi1.open("pde_pi1.txt");
    pi2.open("pde_pi2.txt");
    pf.open("pde_pf.txt");
    
    
    write_initial(INITIAL);
    write_evolution(ci1, ci2, cf, 1); // calculate closed boundary
    write_evolution(oi1, oi2, of, 2); // calculate open boundary
    write_evolution(pi1,pi2,pf,3);

    INITIAL.close();
    
    ci1.close();
    ci2.close();
    cf.close();

    oi1.close();
    oi2.close();
    of.close();
    
    pi1.close();
    pi2.close();
    pf.close();

    return 0;
}