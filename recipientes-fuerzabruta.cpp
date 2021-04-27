#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
//#include <algorithm>
//#include <vector>

//problema de minimizar el número de recipientes de capacidad R donde almacenar objetos de peso w[k]<=R
//enfoque de fuerza bruta, comprueba todas las posibilidades
//para más de 12 objetos los tiempos se disparan (con 12 aprox minuto y medio, con 13 se va a 21 minutos)

float *w;
int *x;
int *solucion;
bool asignado;
int n;
int i,j;
const float R=1.0;
int mejor;
float *suma;

clock_t tantes;
clock_t tdespues;

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}


void generapesos() {

 srand(10);
 for (int i = 0; i < n; i++) {
     double u=uniforme();
     w[i]=u;
  }
}

bool esvalido() { //comprueba la validez de la solucion, si los objetos no sobrepasan la capacidad de los recipientes
    
 bool valido;   
 for (int j = 0; j < n; j++) suma[j]=0.0;
 for (int i = 0; i < n; i++) suma[x[i]-1]+=w[i];
 valido = true;
 for (int j = 0; j < n; j++) 
     if (suma[j] > R) {
         valido=false;
         break;
     }
 return valido;
}    


int cuantosuso() {
    
int numrec = 0;
bool usado;
int l;
for (int k = 1; k<=n; k++) {
    usado = false;
    l=0;
    while (!usado && l<n) 
        if (x[l]==k) {
            usado = true;
            numrec++;
        }
        else l++;
}   
return numrec;
}


void recipientes(int k) { //cambiar
    
int usados;    
if (k==n) {
    if (esvalido()) {
       usados = cuantosuso();
       if (usados < mejor) {
           mejor = usados;
           for (int i = 0; i<n; i++) solucion[i]=x[i];
       }
    }   
}
else {
      for (int j=1; j<=k+1; j++) {
          x[k]=j; 
          recipientes(k+1);
      }  
}    

}


int main(int argc, char * argv[])
{
  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <tamano>" <<  endl;
      return -1;
    }
  n = atoi(argv[1]);

    w =  new float[n];
    //  assert(w);
    x =  new int[n];
    //  assert(x);
    solucion =  new int[n];
    //  assert(solucion);  
    suma =  new float[n];
    //  assert(suma);  

    mejor=n+1;
    generapesos();
    cout << "Los pesos son: " << endl;
    for (int k = 0; k < n; k++) cout << " " << w[k] << " ";
    cout << endl;

    tantes = clock();
    recipientes(0);
    tdespues = clock();
    cout << "tiempo: "<< (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

    cout << "Se usan " << mejor << " recipientes" << endl;
    cout << "La distribucion es: " << endl;
    for (i = 0; i < n; i++) cout << " " << w[i] << "  en recipiente "<< solucion[i] << endl;
    cout << endl;

}
