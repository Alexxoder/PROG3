/*
  Módulo de implementación de `caminos'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/caminos.h"
#include "../include/grafo.h"
#include "../include/cola.h"
#include "../include/lista.h"
#include <cstddef>

nat* CantCaminos(Grafo G, nat s){

  nat n=max_vertice(G);
  nat * distancia= new nat[n+1];
  nat* Cant_Caminos=new nat[n+1];
  bool* visitado=new bool[n+1];
  for (nat i = 0; i < n+1; i++) {
    distancia[i]=0;
    Cant_Caminos[i]=0;
    visitado[i]=0;
  }
  //parent??
  distancia[s]=0;
  Cant_Caminos[s]=1;
  visitado[s]=1;

  Cola c=crear_cola();
  encolar(s,c);

  while (!es_vacia_cola(c)) {
    nat u=frente(c);
    desencolar(c);
    Lista adyacentes_de_u=adyacentes(u,G);
    while (!es_vacia_lista(adyacentes_de_u)) {
      nat v=primero(adyacentes_de_u);
      if (!visitado[v]) {
        visitado[v]=1;
        encolar(v,c);
        distancia[v]=1+distancia[u];
        Cant_Caminos[v]=Cant_Caminos[u];
      } else {
            if (distancia[u]+1==distancia[v]) {
              Cant_Caminos[v]=Cant_Caminos[v] + Cant_Caminos[u];
            }

      }
      adyacentes_de_u=resto(adyacentes_de_u);
    }

  }
    destruir_cola(c);
    delete [] visitado;
    delete [] distancia;

    return Cant_Caminos;
}
