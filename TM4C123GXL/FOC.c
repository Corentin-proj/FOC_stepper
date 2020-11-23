/**
 * FOC.c
 * Created on: June 8, 2020
 * Author: Corentin Casier
 * Last update: June 8, 2020
 * This code realize the field oriented control.
 * It means that the code compute the voltage for each phase of the stepper motor
 * depending on the angle of the rotor, the number of poles of the rotor and
 * the references of torque and magnetic flux.
 *
 */
#include "FOC.h"

// Lookup table de sin*10000(to work with int instead of float)
// This lookup table is for the first quadrant of sin.
// First quadrant (0 <= X < Pi/2) : sin(X)=sine_array(X)
// Second quadrant (Pi/2 <= X < Pi) : sin(X)=sine_array(Pi-X)
// Third quadrant (Pi <= X < 3Pi/2) : sin(X)=-sine_array(Pi+X)
// Fourth quadrant (3Pi/2 <= X < 2Pi) : sin(X)=-sine_array(-X)
int sine_array[200] = {0,79,158,237,316,395,473,552,631,710,789,867,946,1024,1103,1181,1260,1338,1416,1494,1572,1650,1728,1806,1883,1961,2038,2115,2192,2269,2346,2423,2499,2575,2652,2728,2804,2879,2955,3030,3105,3180,3255,3329,3404,3478,3552,3625,3699,3772,3845,3918,3990,4063,4135,4206,4278,4349,4420,4491,4561,4631,4701,4770,4840,4909,4977,5046,5113,5181,5249,5316,5382,5449,5515,5580,5646,5711,5775,5839,5903,5967,6030,6093,6155,6217,6279,6340,6401,6461,6521,6581,6640,6699,6758,6815,6873,6930,6987,7043,7099,7154,7209,7264,7318,7371,7424,7477,7529,7581,7632,7683,7733,7783,7832,7881,7930,7977,8025,8072,8118,8164,8209,8254,8298,8342,8385,8428,8470,8512,8553,8594,8634,8673,8712,8751,8789,8826,8863,8899,8935,8970,9005,9039,9072,9105,9138,9169,9201,9231,9261,9291,9320,9348,9376,9403,9429,9455,9481,9506,9530,9554,9577,9599,9621,9642,9663,9683,9702,9721,9739,9757,9774,9790,9806,9821,9836,9850,9863,9876,9888,9899,9910,9920,9930,9939,9947,9955,9962,9969,9975,9980,9985,9989,9992,9995,9997,9999,10000,10000};

// usefull values
#define _PI 3.14159265359
#define _PI_2 1.57079632679
#define _PI_3 1.0471975512
#define _2PI 6.28318530718
#define _3PI_2 4.71238898038

void initFOC()
{
  //enable floating point operations
  MAP_FPULazyStackingEnable();
  MAP_FPUEnable();
  return;
}

// function approximating the sine calculation by using fixed size array
// ~40us (float array)
// ~50us (int array)
// precision +-0.005
// it has to receive an angle in between 0 and 2PI
float _sin(float angle)
{
  if(angle < _PI_2)
  {
    return 0.0001*sine_array[_round(126.6873* angle)]; // 199/(pi/2)=126.6873 because : 0.0001*sine_array[200]=sin(pi/2)
  }
  else if(angle < _PI)
  {
    return 0.0001*sine_array[398 - _round(126.6873*angle)];
  }
  else if(angle < _3PI_2)
  {
    return -0.0001*sine_array[-398 + _round(126.6873*angle)];
  }
  else
  {
    return -0.0001*sine_array[796 - _round(126.6873*angle)];
  }
}

// function approximating cosine calculation by using fixed size array
// precision +-0.005
// it has to receive an angle in between 0 and 2PI
float _cos(float angle)
{
  float a_sin = angle + _PI_2;
  a_sin = a_sin > _2PI ? a_sin - _2PI : a_sin;
  return _sin(a_sin);
}


// wrapping radian angle inside [0,2PI]
float _wrapAngle(float angle)
{
  float a = fmod(angle, _2PI);
  return a >= 0 ? a : (a + _2PI);
}

// Half of a simplified inverse Park transformation (returns only the Alpha Voltage)
// the angle theta is in degrees
float invParkAlpha(float d, float q, float theta)
{
  float alpha = 0.0;
  int angle = 0;
  if(theta<90){
    angle = round(theta*200/90);//scale theta for sine_array
    //alpha = d*sin(theta) + q*cos(theta) BUT : cos(X)=sin(Pi/2-X)
    alpha = d*(sine_array[theta]/10000) + q*(sine_array[M_PI-theta]/10000);
  }else if(theta<180){
    angle = round(theta*200/90)-200;//scale theta for sine_array
  }else if(theta<270){
    angle = round(theta*200/90)-400;//scale theta for sine_array

  }else{
    angle = round(theta*200/90)-600;//scale theta for sine_array

  }

  return alpha;
}

// Half of a simplified inverse Park transformation (returns only the Beta Voltage)
// the angle theta is in degrees
float invParkBeta(float d, float q, float theta)
{
  float beta = 0.0;
  //beta = -d*cos(theta) + q*sin(theta) BUT : cos(X)=sin(Pi/2-X)
  beta = -d*(sine_array[M_PI-theta]/10000) + q*(sine_array[theta]/10000);
  return beta;
}

// Convert mechanical rotor angle to electrical rotor angle.
float mech2elec(int poles, float thetaMech)
{
  float thetaElec = 0.0;
  thetaElec = (poles/2)*thetaMech;
  return thetaElec;
}
