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

void initFOC(){
  //enable floating point operations
  MAP_FPULazyStackingEnable();
  MAP_FPUEnable();
  return;
}

// Half of a simplified inverse Park transformation (returns only the Alpha Voltage)
float invParkAlpha(float d, float q, float theta){
  float alpha = 0.0;
  alpha = d*sin(theta) + q*cos(theta);
  return alpha;
}

// Half of a simplified inverse Park transformation (returns only the Beta Voltage)
float invParkBeta(float d, float q, float theta){
  float beta = 0.0;
  beta = -d*cos(theta) + q*sin(theta);
  return beta;
}

// Convert mechanical rotor angle to electrical rotor angle.
float mech2elec(int poles, float thetaMech){
  float thetaElec = 0.0;
  thetaElec = (poles/2)*thetaMech;
  return thetaElec;
}
