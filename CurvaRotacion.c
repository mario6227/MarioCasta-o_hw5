#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){

  int n = 300; //Datos en el archivo de observaciones

  //inicializacion de vectores y matriz de soluciones
  double * r_obs = malloc(n*sizeof(double));
  double * v_obs = malloc(n*sizeof(double));
  
  FILE * data; //Archivo de velocidades observadas
  data = fopen("RadialVelocities.dat","r");
  
  //Lectura de la condicion inicial
  int i;
  fscanf(data, "%*[^\n]");  // Read and discard a line
  for (i=0; i<n; i++) //Se inicializa en 1 para saltar titulos de series
    {
      fscanf(data,"%lf %lf\n", &r_obs[i],&v_obs[i]);
    }
  

  
  return 0;
}
