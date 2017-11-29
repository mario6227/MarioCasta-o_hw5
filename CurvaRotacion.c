#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){

  int n = 300; //Datos en el archivo de observaciones
  int i;
  
  //Definicion de funciones, f_modelo y de 'likelihood'
  double likelihood(double obs[n], double model[n]){
    double suma = 0;
    for(i=0;i<n;i++){
      suma = suma + pow((obs[i]-model[i]),2);
    }
    return exp(-(1.0/2.0)*suma);
  }

  double f_modelo(double R, double Mb, double Md, double Mh){
    double bb = 0.2497;
    double bd = 5.16;
    double ad = 0.3105;
    double ah = 64.3;
    double pb = sqrt(Mb) * R / pow((pow(R,2)+pow(bb,2)), 0.75);
    double pd = sqrt(Md) * R / pow((pow(R,2)+pow(bd+ad,2)), 0.75);
    double ph = sqrt(Mh) / pow((pow(R,2)+pow(ah,2)), 0.25);
    
    return (pb + pd + ph);
  }

  //inicializacion de vectores y matriz de soluciones
  double * r_obs = malloc(n*sizeof(double));
  double * v_obs = malloc(n*sizeof(double));
  
  FILE * data; //Archivo de velocidades observadas
  data = fopen("RadialVelocities.dat","r");
  
  //Lectura de la condicion inicial
  fscanf(data, "%*[^\n]");  // Read and discard a line
  for (i=0; i<n; i++) //Se inicializa en 1 para saltar titulos de series
    {
      fscanf(data,"%lf %lf\n", &r_obs[i],&v_obs[i]);
    }
  

  
  return 0;
}
