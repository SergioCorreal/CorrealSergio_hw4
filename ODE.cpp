#include<iostream>
#include<cmath>
#include<fstream>
#include <iostream>
#include <string>
using namespace std;
float pi = 3.14159265358979323846;

//parameters

float g = 10.0; // [m/s**2]
float c = 0.2;// [adimensional]
float m = 0.2; // [Kg]
float v_i = 300.0; // [m/s] inital velocity
float x1_i = 0.0; // [m] initial x-position
float y1_i = 0.0; // [m] initial y-position
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
/*
This function solves the ODE and save results in an input file. 
The method also returns the range of the parabolic motion.
*/
float calculate_and_write(ofstream &file, float theta){

    // initialize values and pointers
    float x2_i = v_i*cos(theta); // initial x velocity
    float y2_i = v_i*sin(theta); // initial y velocity

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
    
    int counts = 0;

    while (y > -0.01){  //y > 0.0){
        //print current values
        file << *px << "," << *py << endl;
        
        // calculate next positions and velocities
        p = rk4(*px,*pvx,*py,*pvy);
      
        // update
        *px = *p;
        *pvx = *(p+1);
        *py = *(p+2);
        *pvy = *(p+3);
        t = t + dt;
        counts += 1;
    }
    return *px - x1_i; 
}
//-----------------------------------------------------------------------------------------
int main(){

    int maxAngle = 45;
    float angles[] = {pi/4.0, pi/18.0, pi/9.0, pi/6.0, 2.0*pi/9.0, 5.0*pi/18.0, pi/3.0, 7.0*pi/18.0};

    ofstream FILE0;
    ofstream FILE1;
    ofstream FILE2;
    ofstream FILE3;
    ofstream FILE4;
    ofstream FILE5;
    ofstream FILE6;
    ofstream FILE7;
    
    FILE0.open("ode_45.txt");
    FILE1.open("ode_10.txt");
    FILE2.open("ode_20.txt");
    FILE3.open("ode_30.txt");
    FILE4.open("ode_40.txt");
    FILE5.open("ode_50.txt");
    FILE6.open("ode_60.txt");
    FILE7.open("ode_70.txt");

    float maxRange = calculate_and_write(FILE0, pi/4.0);
    float range;

    for(int i =1; i<8; i++){
        if(i == 1){
		range = calculate_and_write(FILE1, pi/18.0);
		if(range > maxRange){
			maxRange = range;
			maxAngle = 10;
		}		
	}
        else if(i == 2){
		range = calculate_and_write(FILE2, pi/9.0);
		if(range > maxRange){
			maxRange = range;
			maxAngle = 20;
		}
	}
        else if(i == 3){
		range = calculate_and_write(FILE3, pi/6.0);
		if(range > maxRange){
			maxRange = range;
			maxAngle = 30;
		}
	}
        else if(i == 4){
		range = calculate_and_write(FILE4, 2.0*pi/9.0);
		if(range > maxRange){
			maxRange = range;
			maxAngle = 40;
		}
	}
	else if(i == 5){
		range = calculate_and_write(FILE5, 5.0*pi/18.0);
		if(range > maxRange){
			maxRange = range;
			maxAngle = 50;
		}
	}
	else if(i == 6){
		range = calculate_and_write(FILE6, pi/3.0);
		if(range > maxRange){
			maxRange = range;
			maxAngle = 60;
		}
	}
	else{
		range = calculate_and_write(FILE7, 7.0*pi/18.0);
		if(range > maxRange){
			maxRange = range;
			maxAngle = 70;
		}
	}      
    }

    cout << "El maximo rango fue " << maxRange << " m y corresponde al angulo " << maxAngle << endl;
    return 0;
}
//-----------------------------------------------------------------------------------------



