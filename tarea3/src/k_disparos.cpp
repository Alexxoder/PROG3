/*6309536*/
/*
  Módulo de implementación de `k_disparos'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>

#include "../include/k_disparos.h"

typedef struct nodoLista * Tlista;
  struct nodoLista{
  int dato;
  Tlista siguiente;
};

nat max(int n, int m){
    if (n>=m) {
      return n;
    } else return m;
  }

Estrategia* k_disparos(nat* precios, nat n, nat k)
{
  Estrategia* ret = new Estrategia;
  ret->cant_intervalos = 0;
  ret->intervalos = NULL;
  ret->ganancia_max = 0;
  // Determinar la mejor estrategia

  //printf("n es %d\n",n);
  //printf("k es %d\n",k);
  //crear e inicializar la matriz

  int ** M= new int*[k+1];
    for (nat i = 0; i < k+1; i++) {
      M[i]=new int[n];
    }
    for (nat i = 0; i < k+1; i++) {
      for (nat j = 0; j < n; j++) {
      M[i][j]=0;
      }
    }


  for (nat j = 1; j < k+1; j++) {
    int maxval=-999999;
    for (nat i = 1; i < n; i++) {
      maxval=max(maxval,-precios[i]+M[j-1][i-1]);
      //printf("maxval es %d\n",maxval);
      M[j][i]=max(M[j][i-1],precios[i+1]+maxval);
    }
  }

//imprimir la matriz
/*
    for (nat i = 0; i < k+1; i++) {
      for (nat j = 0; j < n; j++) {
        printf("|%d",M[i][j]);
      }
      printf("|");
      printf("\n");
    }
*/

    /*
    ret->intervalos=new Intervalo[cant];
    for (nat i = 0; i < cant; i++) {
      ret->intervalos[i].inicio=0;
      ret->intervalos[i].fin=0;
    }
*/
    //printf(" cant es %d\n",ret->cant_intervalos);

    int ganancia=0;
    int filas=k;
    int cols=n-1;
    int dif=0;
    nat cant=0;
    Tlista list=NULL;
    //printf("M[k][n-1] es %d\n",M[k][n-1] );

    while (cols!=0 && ganancia!=M[k][n-1]) {

      while (M[filas][cols]==M[filas-1][cols]) {
        filas--;
      }

      if (M[filas][cols]==M[filas][cols-1]) {//si no hay una transaccion
        while (M[filas][cols]==M[filas][cols-1]) {//recorro esa fila hasta encontrar la transaccion
          cols--;
        }
        ganancia+=precios[cols+1]; //calculo la ganancia, es decir compro
        dif=M[filas][cols]-precios[cols+1];//calculo la diferencia
        Tlista nuevo = new nodoLista;
        nuevo->dato=cols+1;
        nuevo->siguiente=list;
        list=nuevo;
        cant++;
      } else {
        ganancia+=precios[cols+1];
        dif=M[filas][cols]-precios[cols+1];
        Tlista nuevo = new nodoLista;
        nuevo->dato=cols+1;
        nuevo->siguiente=list;
        list=nuevo;
        cant++;
      }
      filas--;
      cols--;
      int x=M[filas][cols]-precios[cols+1];
      while (x!=dif) {
        cols--;
        x=M[filas][cols]-precios[cols+1];
      }
      ganancia-=precios[cols+1];//vendo
      Tlista nuevo = new nodoLista;
      nuevo->dato=cols+1;
      nuevo->siguiente=list;
      list=nuevo;
    }

    //imprimo la lista
    Tlista q= list;
    /*
    while (q!=NULL) {
        printf("%d\n",q->dato);
        q=q->siguiente;
      }

    q=list;
    */
    //creo el arreglo intervalos;
    //printf("cant es %d\n",cant);
    ret->cant_intervalos=cant;
    Intervalo *arrayinter=new Intervalo[cant];

    nat i=0;
    //cargar el arreglo;
    while (q!=NULL && i<cant ) {
      //printf(" dato que cargo es %d\n",q->dato);
      arrayinter[i].inicio=q->dato;
      q=q->siguiente;
      //printf(" dato que cargo es %d\n",q->dato);
      arrayinter[i].fin=q->dato;
      q=q->siguiente;
      i++;
    }
    /*
    for (nat i = 0; i < cant; i++) {
      printf("inicio es %d %d\n",i,arrayinter[i].inicio);
      printf("fin es %d %d\n",i,arrayinter[i].fin);
    }
    */
    ret->intervalos=arrayinter;
    ret->ganancia_max=1000*ganancia;
    //printf("cargo el valor %d\n",ret->ganancia_max );
     q=list;
     Tlista p;

  while (q!=NULL) {
    p=q;
    q=q->siguiente;
    delete p;
  }

  //delete list;
  list=NULL;

  for (nat i = 0; i < k+1; i++) {//liberar el arreglo de punteros pa
    delete [] M[i];
  }

    delete [] M;
    M=NULL;
  return ret;
}
