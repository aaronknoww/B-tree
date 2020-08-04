#include "../Headers/Precom.h"
#include "../Headers/ArbolB.h"

template<typename KY, typename DT>
ArbolB<KY, DT>::ArbolB()
{
	p_raiz = nullptr;
	p_raiz = new NodoB();
	return;
}	

template<typename KY, typename DT>
void ArbolB<KY, DT>::insertar(KY key, DT dato)
{
	_insetarAux(p_raiz, key , dato);
	return;
}

template<typename KY, typename DT>
bool ArbolB<KY, DT>::eliminar(KY key)
{
	if (p_raiz->num_claves != 0)// Revisa que haya elmentos claves en la raiz del arbol.
		return _eliminarAux(p_raiz, key);
	else
		return false;
}


//template<typename KY, typename DT>
//void ArbolB<KY, DT>::imprimir()
//{
//	//int contador= _profundidad(p_raiz);
//	//_imprimirAux(nodo, contador);
//}
