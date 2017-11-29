#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define n 300 //Cantidad de datos observados
#define PI 3.14159265359

//Definicion de funciones, f_modelo, randnormal y de 'likelihood'
double likelihood(double obs[n], double model[n]){
  double suma = 0;
  int i;
  for(i=0;i<n;i++){
    suma = suma + pow((obs[i]-model[i]),2);
  }
  return exp(-(1.0/2.0)*suma);
}

//Distribucion normal usando el metodo de Box-Muller
double randnormal(double mu, double s){
  double u = drand48();
  double v = drand48();
  double Z = sqrt(-2.0*log(u))*cos(2*PI*v);

  return (Z*s + mu);
}

double * v_modelo(double R[n], double Mb, double Md, double Mh){
  double bb = 0.2497;
  double bd = 5.16;
  double ad = 0.3105;
  double ah = 64.3;
  double * v_m = malloc(n*sizeof(double));

  int i;
  for(i=0; i<n; i++){
    double pb = sqrt(Mb) * R[i] / pow((pow(R[i],2)+pow(bb,2)), 0.75);
    double pd = sqrt(Md) * R[i] / pow((pow(R[i],2)+pow(bd+ad,2)), 0.75);
    double ph = sqrt(Mh) / pow((pow(R[i],2)+pow(ah,2)), 0.25);
    v_m[i] = pb + pd + ph;
  }
    
  return v_m;
}

int main(void){

  int i;
  
  //inicializacion de vectores (observados, 'walks' e init)
  double * r_obs = malloc(n*sizeof(double));
  double * v_obs = malloc(n*sizeof(double));
  double * Mb_walk = malloc(n*sizeof(double));
  double * Md_walk = malloc(n*sizeof(double));
  double * Mh_walk = malloc(n*sizeof(double));
  double * l_walk = malloc(n*sizeof(double));
  double * v_init = malloc(n*sizeof(double));
  double * v_prime = malloc(n*sizeof(double));
  
  FILE * data; //Archivo de velocidades observadas
  data = fopen("RadialVelocities.dat","r");
  
  //Lectura de los valores observados
  fscanf(data, "%*[^\n]");  // Read and discard a line
  for (i=0; i<n; i++) //Se inicializa en 1 para saltar titulos de series
    {
      fscanf(data,"%lf %lf\n", &r_obs[i],&v_obs[i]);
    }

  Mb_walk[0] = drand48();
  Md_walk[0] = drand48();
  Mh_walk[0] = drand48();

  v_init = v_modelo(r_obs, Mb_walk[0], Md_walk[0], Mh_walk[0]);
  l_walk[0] = likelihood(v_obs, v_init);

  int iter = 20000; //Numero de iteraciones a realizar
  for(i=0; i<iter; i++){
  }
    
  return 0;
}
