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
