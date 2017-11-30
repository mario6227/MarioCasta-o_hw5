#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define n 300 //Cantidad de datos observados
#define PI 3.14159265359

//Definicion de funciones, f_modelo, randnormal y de 'likelihood'
long double likelihood(double obs[n], double model[n]){
  double suma = 0.0;
  int i;
  for(i=0;i<n;i++){
    suma = suma + pow((obs[i]-model[i]) / 100.0,2.0);
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
    double pb = sqrt(Mb) * R[i] / pow((pow(R[i],2.0)+pow(bb,2.0)), 0.75);
    double pd = sqrt(Md) * R[i] / pow((pow(R[i],2.0)+pow(bd+ad,2.0)), 0.75);
    double ph = sqrt(Mh) / pow((pow(R[i],2.0)+pow(ah,2.0)), 0.25);
    v_m[i] = pb + pd + ph;
  }
    
  return v_m;
}

int main(void){

  int i;
  int iter = 50000; //Numero de iteraciones a realizar
  
  //inicializacion de vectores (observados, 'walks' e init)
  double * r_obs = malloc(n*sizeof(double));
  double * v_obs = malloc(n*sizeof(double));
  double * Mb_walk = malloc(iter*sizeof(double));
  double * Md_walk = malloc(iter*sizeof(double));
  double * Mh_walk = malloc(iter*sizeof(double));
  double * l_walk = malloc(iter*sizeof(double));
  double * v_init = malloc(n*sizeof(double));
  double * v_prime = malloc(n*sizeof(double));
  
  FILE * data; //Archivo de velocidades observadas
  data = fopen("RadialVelocities.dat","r");

  FILE * sol; //Archivo de velocidades observadas
  sol = fopen("parametros.txt","w");
  
  //Lectura de los valores observados
  fscanf(data, "%*[^\n]");  // Read and discard a line
  for (i=0; i<n; i++) 
    {
      fscanf(data,"%lf %lf\n", &r_obs[i],&v_obs[i]);
    }

  Mb_walk[0] = drand48();
  Md_walk[0] = drand48();
  Mh_walk[0] = drand48();

  v_init = v_modelo(r_obs, Mb_walk[0], Md_walk[0], Mh_walk[0]);
  l_walk[0] = likelihood(v_obs, v_init);

  for(i=0; i<iter; i++){
    //La desviacion estandar mas apropiada para cada distribucion se determino de manera empirica
    double Mb_prime = randnormal(Mb_walk[i], 4.0);
    double Md_prime = randnormal(Md_walk[i], 400.0);
    double Mh_prime = randnormal(Mh_walk[i], 400.0);

    v_init = v_modelo(r_obs, Mb_walk[i], Md_walk[i], Mh_walk[i]);
    v_prime = v_modelo(r_obs, Mb_prime, Md_prime, Mh_prime);

    long double l_init = likelihood(v_obs, v_init);
    long double l_prime = likelihood(v_obs, v_prime);

    double alpha = l_prime / l_init;
    //fprintf(sol, "%f \n", l_walk[i]);
    if(alpha >= 1.0){
      Mb_walk[i+1] = Mb_prime;
      Md_walk[i+1] = Md_prime;
      Mh_walk[i+1] = Mh_prime;
      l_walk[i+1] = l_prime;
    } else {
      double beta = drand48();
      if(beta <= alpha){
	Mb_walk[i+1] = Mb_prime;
	Md_walk[i+1] = Md_prime;
	Mh_walk[i+1] = Mh_prime;
	l_walk[i+1] = l_prime;
      } else {
	Mb_walk[i+1] = Mb_walk[i];
	Md_walk[i+1] = Md_walk[i];
	Mh_walk[i+1] = Mh_walk[i];
	l_walk[i+1] = l_walk[i];
      }
    }
      
  }

  //Se determina la posicion de maxima likelihood
  double max = l_walk[0];
  int index = 0;
  for(i=1; i<iter; i++){
    if(l_walk[i] >= max){
      max = l_walk[i];
      index = i;
    }
  }

  //Documento que se leera en python
  fprintf(sol, "%f %f %f", Mb_walk[index], Md_walk[index], Mh_walk[index]);

  //Se imprimen los resultados en consola
  printf("Mb: %lf\n", Mb_walk[index]);
  printf("Md: %lf\n", Md_walk[index]);
  printf("Mh: %lf\n", Mh_walk[index]);
    
  return 0;
}
