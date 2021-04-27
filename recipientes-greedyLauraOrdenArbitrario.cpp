#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <algorithm>

//problema de minimizar el número de recipientes de capacidad R donde almacenar objetos de peso w[k]<=R
//enfoque de fuerza bruta, comprueba todas las posibilidades
//para más de 12 objetos los tiempos se disparan (con 12 aprox minuto y medio, con 13 se va a 21 minutos)

float *pesos;  //Vector pesos con tantas celdas como número de objetos. 
                //Cada celda tiene un peso generado aleatoriamente
int *vrecip;    //Vector de recipientes. 
                //Ejemplo de su contenido: vrecip[0...nobjetos]=1, 4, 2, 1, 3, 1...
int *solucion;  //Vector de recipientes solución
bool asignado;
int nobjetos;  //n es el número de objetos que tienen un peso
int i,j;
const float Recipiente=1.0; //Capacidad total del recipiente
int mejor;  //Mejor número mínimo de recipientes necesarios
float *suma; //El vector suma contiene la suma de los pesos de todos los objetos de cada recipiente.
            // Si el recipiente 1 contiene 0,5 pesos, y el rec 2 tiene 0,75 pesos, el vector suma será:
            // suma[1]=0,5 suma[2]=0,75
            
            //Los objetos estarán repartidos en los recipientes en el vector vrecip
            // vrecip[0..nobjetos] = 1, 3, 2, 4, 1, 3... 
//vector<int> pesosOrdenados;

clock_t tantes;
clock_t tdespues;



double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.  
                  //Este número aleatorio servirá para asignar pesos aleatorios
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}


void generapesos() {

 srand(time(0));
 for (int i = 0; i < nobjetos; i++) {
     double u=uniforme();
     pesos[i]=u;    //Asignamos pesos aleatorios en el vector con los pesos.
  }
}



bool esvalido() { //comprueba la validez de la solucion (si los objetos no sobrepasan la capacidad de los recipientes)
    
 bool valido;   
 for (int j = 0; j < nobjetos; j++) 
    suma[j]=0.0;  //Inicializamos el vector suma en tantas posiciones como nº objetos
    
 for (int i = 0; i < nobjetos; i++) 
    suma[vrecip[i]-1] += pesos[i];     //Sumamos todos los pesos de los objetos de cada recipiente
                                        //El peso del objeto i está en el recipiente número [vrecip[i]-1]
 valido = true;
 
 for (int j = 0; j < nobjetos; j++) {
     if (suma[j] > Recipiente) {  //Si la suma de los pesos supera la capacidad del recipiente, devolvemos false
         valido=false;
         break;
     }
 }    
 return valido;
}    


int cuantosuso() { //Calcula el número de recipientes usados
        
    int numrec = 0;  //número de recipientes
    bool usado;
    int l; //para recorrer el vector de recipientes
    for (int k = 1; k<=nobjetos; k++) { //k recorre el posible número de objetos dentro del recipiente
        usado = false;
        l=0;
        while (!usado && l<nobjetos) 
            if (vrecip[l]==k) {
                usado = true;
                numrec++;  //número de recipientes + 1
            }
            else 
                l++;
    }   
    return numrec;
}


void recipientes(int k) { //Averigua el número de recipientes
    for (int j = 0; j < nobjetos; j++) 
        suma[j]=0.0;  //Inicializamos el vector suma en tantas posiciones como nº objetos
    
    int recipi;
    for (int j=0; j < nobjetos; j++){  //Recorre los pesos
        for (recipi=0; ; recipi++){//Recorre los recipientes
            if (pesos[j] + suma[recipi] <= Recipiente){
                suma[recipi] += pesos[j];
                solucion[j]=recipi;
                break;
            }
           
        }
    }
    
    int sumasize;
    for (int h = 0; ; h++){
        if (suma[h] == 0){
            sumasize = h;
            break;
        }
    }
    mejor = sumasize;
    
    
    /*
    int usados;    
    if (k==nobjetos) {
        if (esvalido()) {  //Si los objetos no superan la capacidad del recipiente
           usados = cuantosuso();  //nº recipientes usado
           if (usados < mejor) {  
               mejor = usados;  //Número mínimo de recipientes
               for (int i = 0; i<nobjetos; i++) 
                   solucion[i]=vrecip[i]; //Vector recipientes solución
           }
        }   
    }
    else {
        for (int j=1; j<=k+1; j++) {
            vrecip[k]=j; 
            recipientes(k+1);
        }  
    }    
*/
}




int main(int argc, char * argv[]) {

    if (argc != 2){
        cerr << "Formato " << argv[0] << " <tamano>" <<  endl;
        return -1;
    }
      
    nobjetos = atoi(argv[1]);  //asignamos el número de objetos

    pesos =  new float[nobjetos];  //Vector de pesos de los objetos. Vector con mismos elementos que números de objetos.
                                //A cada celda del vector le asignaremos un peso. 
    //  assert(pesos);
    vrecip =  new int[nobjetos];
    //  assert(vrecip);
    solucion =  new int[nobjetos];  //Vector de recipientes solución
    //  assert(solucion);  
    suma =  new float[nobjetos]; //Inicializamos variable global
    //  assert(suma);  

    mejor = nobjetos + 1;  //Nº mínimo de recipientes. Inicializamos.
    
    //Imprimimos los pesos
    generapesos();
    cout << "Los pesos son: " << endl;
    for (int k = 0; k < nobjetos; k++) 
        cout << " " << pesos[k] << " " << endl;
    cout << endl;
    /*
    cout << "Los pesos ordenados son: " << endl;
    for (int k = 0; k < nobjetos; k++)
        cout << " " << pesosOrdenados[k] << " " << endl;
    cout << endl;
*/
    //Medimos los tiempos de cálculo
    tantes = clock();            
    recipientes(0);
    tdespues = clock();
    cout << "tiempo: "<< (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

    cout << "Se usan " << mejor << " recipientes" << endl;
    cout << "La distribucion es: " << endl;
    
    for (i = 0; i < nobjetos; i++) 
        cout << " " << pesos[i] << "  en recipiente "<< solucion[i] << endl;
        
    cout << endl;

}
