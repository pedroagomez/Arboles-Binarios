#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct
{
    int legajo;
    char nombre[20];
    int edad;
} stPersona;

typedef struct
{
    stPersona dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct
{
    stPersona dato;
    struct nodoLista* siguiente;
} nodoLista;

nodoLista* inicLista()
{
    return NULL;
}
nodoLista* crearNodoLista(stPersona nuevo)
{
    nodoLista* lista=(nodoLista*)malloc(sizeof(nodoLista));
    lista->dato=nuevo;
    lista->siguiente=NULL;

    return lista;
}

nodoLista* agregarPrincipio(nodoLista* lista, nodoLista* nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;
}


///Hacer una función que permita ingresar nuevos nodos manteniendo el árbol ordenado (por legajo).
stPersona cargar()
{
    stPersona aux;
    printf("Ingrese numero de legajo :");
    scanf("%d",&aux.legajo);
    printf("Ingrese nombre : ");
    fflush(stdin);
    gets(aux.nombre);
    printf("Ingrese edad :");
    scanf("%d",&aux.edad);
    return aux;
}
void mostrarGral(nodoArbol* arbol)
{
    printf("================================================= \n");
    printf("Legajo .............................. :%d\n",arbol->dato.legajo);
    printf("Nombre .............................. :%s\n",arbol->dato.nombre);
    printf("Edad   .............................. :%d\n",arbol->dato.edad);
}
void mostrarUnNodo(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarGral(arbol);
    }
}
void mostrarLista(nodoLista* lista)
{
    while(lista)
    {
        mostrarUnNodo(lista);
        lista=lista->siguiente;

    }
}
void mostrarInOrden(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarInOrden(arbol->izq);
        mostrarUnNodo(arbol);
        mostrarInOrden(arbol->der);
    }
}
void mostrarPreOrden(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarUnNodo(arbol);
        mostrarInOrden(arbol->izq);
        mostrarInOrden(arbol->der);
    }
}
void mostrarPostOrden(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarInOrden(arbol->izq);
        mostrarInOrden(arbol->der);
        mostrarUnNodo(arbol);
    }
}
nodoArbol* inicArbol()
{
    return NULL;
}
nodoArbol* crearNodoArbol(stPersona nuevo)
{
    nodoArbol* arbol=(nodoArbol*)malloc(sizeof(nodoArbol));
    arbol->dato=nuevo;
    arbol->der=NULL;
    arbol->izq=NULL;

    return arbol;
}

nodoArbol* insertarEnArbol(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL)
    {
        arbol=nuevo;
    }
    else
    {

        if(nuevo->dato.legajo>arbol->dato.legajo)
        {
            arbol->der=insertarEnArbol(arbol->der,crearNodoArbol(nuevo->dato));
        }
        else
        {
            arbol->izq=insertarEnArbol(arbol->izq,crearNodoArbol(nuevo->dato));
        }
    }
    return arbol;

}

nodoArbol* cargarArbolPorOrden(nodoArbol* arbol)
{
    char continuar='s';
    stPersona aux;
    while(continuar=='s')
    {
        aux=cargar();
        arbol=insertarEnArbol(arbol,crearNodoArbol(aux));
        printf("Desea continuar?\n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    return arbol;
}

nodoLista* deArbolAlista(nodoArbol* arbol, nodoLista* lista)
{
    if(arbol)
    {
        lista=deArbolAlista(arbol->izq,lista);
        lista=agregarPrincipio(lista,crearNodoLista(arbol->dato));
        lista=deArbolAlista(arbol->der,lista);
    }
    return lista;
}

nodoArbol* buscarNodoPorLegajo(nodoArbol* arbol, int legajo)
{
    nodoArbol* aux=NULL;
    if(arbol)
    {
        if(arbol->dato.legajo==legajo)
        {
            aux=arbol;
        }
        else
        {
            if(arbol->dato.legajo>legajo)
            {
                aux=buscarNodoPorLegajo(arbol->izq,legajo);

            }
            else
            {
                aux=buscarNodoPorLegajo(arbol->der,legajo);

            }
        }
    }
    return aux;
}
nodoArbol* buscarNodoPorNombre(nodoArbol* arbol, char nombre[])
{
    nodoArbol* aux=NULL;
    if(arbol)
    {
        if(strcmpi(arbol->dato.nombre,nombre)==0)
        {
            aux=arbol;
        }
        else
        {
            aux=buscarNodoPorNombre(arbol->izq,nombre);
            if(aux==NULL)
            {
                aux=buscarNodoPorNombre(arbol->der,nombre);

            }
        }
    }
    return aux;
}

int alturaArbol(nodoArbol* arbol)
{
    int alturaIzq=0, alturaDer=0,total=0;
    if(arbol)
    {
        alturaIzq=alturaArbol(arbol->izq);
        alturaDer=alturaArbol(arbol->der);
        if(alturaDer>alturaIzq)
        {
            total=alturaDer+1;
        }
        else
        {
            total=alturaIzq+1;
        }
    }
    return total;
}

int cantidadDeNodos(nodoArbol* arbol)
{
    int cantidad=0;
    if(arbol)
    {
        /*cantidad++;
        cantidad+=cantidadDeNodos(arbol->izq);
        cantidad+=cantidadDeNodos(arbol->der);*/

        cantidad=1+cantidadDeNodos(arbol->izq)+ cantidadDeNodos(arbol->der);
    }
    return cantidad;
}

int cantidadDeHojasDeUnArbol(nodoArbol* arbol)
{
    int cantidad=0;
    if(arbol)
    {
        if(arbol->izq == NULL && arbol->der==NULL)
        {
            cantidad++;
        }
        cantidad+=cantidadDeHojasDeUnArbol(arbol->izq);
        cantidad+=cantidadDeHojasDeUnArbol(arbol->der);
    }
    return cantidad;
}



int cantidadDeNiveles(nodoArbol* arbol)
{
    int rta=0;
    int mayor;
    if(arbol==NULL)
    {
        rta=0;
    }
    else
    {
        if(arbol->der==NULL && arbol->der==NULL)
        {
            rta=1;
        }
        else
        {
            int izq=cantidadDeNiveles(arbol->izq);
            int der=cantidadDeNiveles(arbol->der);
            if(izq>der)
            {
                mayor=izq;
            }
            else
            {
                mayor=der;
            }
        }
    }
    return 1+mayor;
}

int main()
{
    char continuar='s';
    int opcion;
    nodoArbol* arbol=inicArbol();
    nodoLista* lista=inicLista();

    do
    {
        printf("Bienvenido ..... \n");
        printf("[1]Cargar arbol por orden \n");
        printf("[2]Mostrar InOrden, PostOrden, PreOrden \n");
        printf("[3]Pasar de arbol a lista \n");
        printf("[4]Funcion que busque nodo por legajo y lo retorne \n");
        printf("[5]Hacer una funcion que busque un nodo por nombre \n");
        printf("[6]Hacer una funcion que calcule la altura que tiene el arbol \n");
        printf("[7]Hacer una funcion que calcule la cantidad de nodos del arbol \n");
        printf("[8]Hacer una funcion que calcule la cantidad de hojas del arbol\n");
        printf("[9]Hacer una funcion que borre un nodo de un arbol \n");

        printf("Elija una opcion\n");

        scanf("%d",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
        {

            arbol=cargarArbolPorOrden(arbol);
            break;
        }
        case 2:
        {
            printf("\nMuestro en orden : \n");
            mostrarInOrden(arbol);
            printf("\nMuestro pre orden : \n");
            mostrarPreOrden(arbol);
            printf("\nMuestro post Orden : \n");
            mostrarPostOrden(arbol);
            break;
        }
        case 3:
        {
            arbol=cargarArbolPorOrden(arbol);
            lista=deArbolAlista(arbol,lista);
            mostrarLista(lista);
            break;
        }
        case 4:
        {
            int legajo;
            arbol=cargarArbolPorOrden(arbol);
            nodoLista* aux=inicLista();
            printf("Ingrese legajo :");
            scanf("%d",&legajo);
            aux=buscarNodoPorLegajo(arbol,legajo);
            mostrarUnNodo(aux);
            break;

        }
        case 5:
        {
            char nombre[10];
            arbol=cargarArbolPorOrden(arbol);
            nodoLista* aux=inicLista();
            printf("Ingrese un nombre :");
            fflush(stdin);
            gets(nombre);
            aux=buscarNodoPorNombre(arbol,nombre);
            mostrarUnNodo(aux);
            break;
        }
        case 6:
        {
            int altura;
            arbol=cargarArbolPorOrden(arbol);
            mostrarInOrden(arbol);
            altura=alturaArbol(arbol);
            printf("La altura del arbol es :%d",altura);
            break;
        }
        case 7:
        {
            int cantidad;
            arbol=cargarArbolPorOrden(arbol);
            mostrarInOrden(arbol);
            cantidad=cantidadDeNodos(arbol);
            printf("\nLa cantidad de nodos es :%d",cantidad);
            break;

        }
        case 8:
        {
            int cantidadHojas;
            arbol=cargarArbolPorOrden(arbol);
            mostrarInOrden(arbol);
            cantidadHojas=cantidadDeHojasDeUnArbol(arbol);
            printf("\nLa cantidad de nodos hoja (nodos que no tienen hijos) es :%d",cantidadHojas);
            break;
        }

        }

        printf("\nDesea volver al menu principal?");
        fflush(stdin);
        scanf("%c",&continuar);
        system("cls");




    }
    while(continuar=='s');


}
