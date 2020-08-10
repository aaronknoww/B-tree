#pragma once

#define grado 5 // Es la maxima cantidad de hijos (punteros) que puede tener un arbol.

//M es el grado del arbol B.---------- M-1 es el maximo de claves que puede tener.
// El numero minimo de claves en un nodo es min=[ceil(M)/2]-1; excepto en la raiz, el minimo de punteros M/2 en ambos el redondeo es hacia arriba

template<typename KY, typename DT>
class ArbolB
{
public:
	ArbolB();
	void insertar(KY, DT);
	bool eliminar(KY);
	//void imprimir();
	//~ArbolB();
private:
	class NodoB
	{
	public:
		KY key[grado];
		DT dato[grado];
		NodoB* hijos[grado+1];
		int num_hijos;// para saber si es un nodo hoja y saber si tiene nodos disponibles
		int num_claves; // para saber si hay espacio disponible en las claves
		NodoB()
		{
			for (int i = 0; i < grado; i++)
			{
				key[i] = 0;
				dato[i] = 0;
				hijos[i] = nullptr;

			}
			hijos[grado] = nullptr;// Un puntero extra para poder arreglar el arbol mas facil.
			num_hijos = 0;
			num_claves = 0;
			return;
		};

	};

	NodoB* p_raiz;


	/////// FUNCIONES PRIVADAS NO DISPONIBLES PAR EL USUARIO \\\\\\\\\\

	bool _insetarAux(NodoB*&, KY, DT);// Para poder hacer la funcion recursiva por eso recibe un puntero por refernecia.
	bool _insertarEnOrden(NodoB*&, KY, DT);
	bool _revisarCorregirNodo(NodoB*&, KY, DT);// Revisa cuando inserta
	bool _eliminarAux(NodoB *&, KY);
	int _buscarIndex(NodoB*&, KY);
	bool _eliminarClave(NodoB*& , KY);
	bool _revisarCorregirHijo(NodoB*&, int);// Revisa cuando se borra una clave del arbol
	bool _pedirClave(NodoB*&, int);// Verifica si los hermanos del nodo en problema pueden darle una clave y se la asigna
	bool _fusionar(NodoB*&, int);// Fusiona 2 nodos hermanos mas una clave del nodo padre.
	void _buscaRemplazo(NodoB*&, KY&, DT&); // Busca la clave mas a la derecha del hijo IZQUIERDO.
//	void _imprimirAux(NodoB*&, int);
};
