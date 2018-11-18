#include<iostream>
#include<cmath>
#include<fstream>
#include <iostream>
using namespace std;
float pi = 3.14159265358979323846;

//parameters

float g = 10.0; // [m/s**2]
float c = 0.2;// [adimensional]
float m = 0.2; // [Kg]
float v_i = 300.0; // [m/s] inital velocity
float x1_i = 0.0; // [m] initial x-position
float x2_i = v_i*cos(pi/4.0); // initial x velocity
float y1_i = 0.0; // [m] initial y-position
float y2_i = v_i*sin(pi/4.0); // initial y velocity
float dt = 0.00001; // [s] time step 


//functions

// this function returns the speed at time t
float v(float x2, float y2){
    return sqrt(pow(x2,2)+ pow(y2,2));
}

/*
    x1' = fx1_prime(x2) = x2
*/
float fx1_prime(float x2){
    return x2;
}

/*
    x2' = fx2_prime(x2) = –(c/m)*v*x2
*/
float fx2_prime(float x2, float y2){
    return -(c/m)*v(x2, y2)*x2;
}

/*
    y1' = fy1_prime(y2) = y2
*/
float fy1_prime(float y2){
    return y2;
}

/*
    y2' = fy2_prime(x2, y2) = -g -(c/m)*v*y2
*/
float fy2_prime(float x2, float y2){
    return -g-(c/m)*v(x2,y2)*y2;
}

/*
    4th order Runge Kutta. The method returns the nexts x-posotion, x-velocity, y-position and y-velocity in that order.
*/
float * rk4(float x1, float x2, float y1, float y2){
    static float resp[4];

    //first step
    float fx1_prime_begining = fx1_prime(x2);
    float fx2_prime_begining = fx2_prime(x2, y2);
    float fy1_prime_begining = fy1_prime(x2);
    float fy2_prime_begining = fy2_prime(x2, y2);

    //second step
    float fx1_prime_middle1 = fx1_prime(x2+(dt/2.0)*fx2_prime_begining);
    float fx2_prime_middle1 = fx2_prime(x2+(dt/2.0)*fx2_prime_begining, y2+(dt/2.0)*fy2_prime_begining);
    float fy1_prime_middle1 = fy1_prime(y2+(dt/2.0)*fy2_prime_begining);
    float fy2_prime_middle1 = fy2_prime(x2+(dt/2.0)*fx2_prime_begining, y2+(dt/2.0)*fy2_prime_begining);

    //third step
    float fx1_prime_middle2 = fx1_prime(x2+(dt/2.0)*fx2_prime_middle1);
    float fx2_prime_middle2 = fx2_prime(x2+(dt/2.0)*fx2_prime_middle1, y2+(dt/2.0)*fy2_prime_middle1);
    float fy1_prime_middle2 = fy1_prime(y2+(dt/2.0)*fy2_prime_middle1);
    float fy2_prime_middle2 = fy2_prime(x2+(dt/2.0)*fx2_prime_middle1, y2+(dt/2.0)*fy2_prime_middle1);

    //fourth step
    float fx1_prime_end = fx1_prime(x2+dt*fx2_prime_middle2);
    float fx2_prime_end = fx2_prime(x2+dt*fx2_prime_middle2, y2+dt*fy2_prime_middle2);
    float fy1_prime_end = fy1_prime(y2+dt*fy2_prime_middle2);
    float fy2_prime_end = fy2_prime(x2+dt*fx2_prime_middle2, y2+dt*fy2_prime_middle2);

    //average
    float avgfx1_prime = (1.0/6.0)*(fx1_prime_begining + 2.0*fx1_prime_middle1 + 2.0*fx1_prime_middle2 + fx1_prime_end);
    float avgfx2_prime = (1.0/6.0)*(fx2_prime_begining + 2.0*fx2_prime_middle1 + 2.0*fx2_prime_middle2 + fx2_prime_end);
    float avgfy1_prime = (1.0/6.0)*(fy1_prime_begining + 2.0*fy1_prime_middle1 + 2.0*fy1_prime_middle2 + fy1_prime_end);
    float avgfy2_prime = (1.0/6.0)*(fy2_prime_begining + 2.0*fy2_prime_middle1 + 2.0*fy2_prime_middle2 + fy2_prime_end);

    // advance
    float x1_new = x1 + dt * avgfx1_prime;
    float x2_new = x2 + dt * avgfx2_prime;
    float y1_new = y1 + dt * avgfy1_prime;
    float y2_new = y2 + dt * avgfy2_prime;

    // save values
    resp[0] = x1_new;
    resp[1] = x2_new;
    resp[2] = y1_new;
    resp[3] = y2_new;

    return resp;
}

//-----------------------------------------------------------------------------------------
int main(){
    // file where data will be saved
    ofstream FILE;
    FILE.open("ode_data.txt");

    // initialize values and pointers
    float *p, *px, *pvx, *py, *pvy;
    float t, x, vx, y, vy;

    t = 0.0;
    x = x1_i;
    vx = x2_i;
    y = y1_i;
    vy = y2_i;

    px = &x;
    pvx = &vx;
    py = &y;
    pvy = &vy;

    while (y > -0.01){  //y > 0.0){
        //print current values
        FILE << *px << "," << *py << endl;
        
        // calculate next positions and velocities
        p = rk4(*px,*pvx,*py,*pvy);
      
        // update
        *px = *p;
        *pvx = *(p+1);
        *py = *(p+2);
        *pvy = *(p+3);
        t = t + dt;
        cout << y << endl;
        
    }
    return 0;
}
//-----------------------------------------------------------------------------------------



