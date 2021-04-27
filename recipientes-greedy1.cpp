#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <utility>
//#include <algorithm>
//#include <vector>


float *w;
int *x;
int *solucion;
bool asignado;
int n;
int i,j;
const float R=1.0;
int mejor;
float *suma;
int num_recipientes;


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
//  srand(time(0));
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




    
void recipientes(int k) {
    double suma_local = 0;
    num_recipientes = 1;
    bool recorrido[n];
  
    for(int i=0;i<n;i++)
        recorrido[i]=false;

    for(int i=0;i<n;i++){
        
        if(w[i]+suma_local < R  ){
            suma_local+= w[i];
            solucion[i] = num_recipientes;
            recorrido[i]=true;
        }else{

            num_recipientes++;

            solucion[i]=num_recipientes;
            suma_local=w[i];
        }
    }
}
   




int main(int argc, char * argv[]){
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
    cerr << "Los pesos son: " << endl;
    for (int k = 0; k < n; k++) cerr << " " << w[k] << " ";
    cerr << endl;

    tantes = clock();
    recipientes(0);
    tdespues = clock();
    cout << "tiempo: "<< (double)(tdespues - tantes) / CLOCKS_PER_SEC <<" Tamano: "<<n<< endl;

    cerr << "Se usan " << num_recipientes-1 << " recipientes. La solucion es " <<esvalido()<< endl;
    cerr << "La distribucion es: " << endl;

    for (i = 0; i < n; i++) cerr << " " << w[i] << "  en recipiente "<< solucion[i] << endl;
    cerr << endl;

}