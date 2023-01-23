/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>

#include "../include/cronologia_consistente.h"
#include "../include/grafo.h"

Grafo armarGrafo(nat n,ListaDatos muertos, ListaDatos conviven){

  Grafo g =crear_grafo(2*n,true);

  for (nat i = 1; i <= n; i++) {//v1.nace->v1.muere
    nat v1nace=i;
    nat v1muere=i+n;
    agregar_vertice(v1nace,g);
    agregar_vertice(v1muere,g);
    agregar_arista(i,i+n,g);
  }

  while (!es_vacia_lista_datos(muertos)) {//aca cargo los vertices del tipo v1muere->v2nace
    nat v1=id1(primer_dato(muertos))+n;
    nat v2=id2(primer_dato(muertos));
    agregar_arista(v1,v2,g);
    muertos=resto_datos(muertos);
  }

  while (!es_vacia_lista_datos(conviven)) {  //aca cargo los vertices del tipo v1nace->v2muerte y v2nace->v1muerte
    nat v1 = id1(primer_dato(conviven));
    nat v2 = id2(primer_dato(conviven));
    agregar_arista(v1,v2+n,g);
    agregar_arista(v2,v1+n,g);
    conviven=resto_datos(conviven);
  }
  return g;
}

void sortopo(Grafo g,bool &ciclo,Lista &topolist,nat n){

  Lista cola=crear_lista();
  int * entrantes= new int[2*n+1];
  for (nat i = 1; i < 2*n+1; i++) {
    entrantes[i]=in_grado(i,g);
    if (entrantes[i]==0) {
      insertar_al_final(i,cola);
    }
  }

  nat k=0;
  while (!es_vacia_lista(cola)) {
    nat u=primero(cola);
    remover_al_inicio(cola);
    Lista ady=adyacentes(u,g);
    comienzo(ady);
    while (existe_actual(ady)) {
      nat act=actual(ady);
      entrantes[act]--;
      if (entrantes[act]==0) {
        insertar_al_final(act,cola);
      }
      act=siguiente(ady);
    }

    //agrego a cr
    k++;
    insertar_al_final(u,topolist);
  }
  ciclo= k!=2*n;
  delete [] entrantes;
  destruir_lista(cola);
}

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  bool existe_cr_consistente = false;

  Cronologia cr = new evento[2*n];
  for(nat k=0;k<2*n;k++){
  	cr[k].id=0;
  	cr[k].tipo=nace;

  }

	Grafo g=armarGrafo(n,tipo1,tipo2);//se crea memoria
  Lista topolist=crear_lista();
  bool ciclo=0;
  sortopo(g,ciclo,topolist,n);

  //imprimir_lista(topolist);
  //imprimir_grafo(g);
  destruir_grafo(g);

  // Determinar si existe o no una cronología consistente con los datos,
  // en caso de existir, construirla en cr
  existe_cr_consistente=!ciclo;
//printf("ciclo es %d\n",ciclo);
  if(existe_cr_consistente) { // si existe, retornarla en cr
    nat k=0;
    while (!es_vacia_lista(topolist)) {
      nat actual=primero(topolist);
      if (actual<=n) {
        cr[k].id=actual;
        cr[k].tipo=nace;
      } else {
        cr[k].id=actual-n;
        cr[k].tipo=muere;
      }
      remover_al_inicio(topolist);
      k++;
    }
    destruir_lista(topolist);
    return cr;
  } else {// si no existe, liberar la memoria asociada a cr y retornar NULL
    destruir_lista(topolist);
    delete[] cr;
    return NULL;
  }

}
