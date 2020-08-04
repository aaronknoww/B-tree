#include "..\Headers\Precom.h"
#include "..\Headers\ArbolB.h"

//---- FUNCIONES PARA INSERTAR Y MANTENER EL PROPIEDADES DEL ARBOL B ----- \\


template<typename KY, typename DT>
bool ArbolB<KY, DT>::_insetarAux(NodoB*& nodo, KY key, DT dato)
{
	if ((nodo->num_hijos == 0) && (nodo->num_claves <= grado))// Hay espacio en el nodo y saber si es nodo hoja
	{//Solo inserta en nodos hojas

		_insertarEnOrden(nodo, key, dato);
		return _revisarCorregirNodo(nodo, key, dato);
		//return true;
	}
	else
	{// Como el nodo tiene hijos hay que buscar por cual nodo se debe de avanzar.

		for (int i = 0; i < nodo->num_claves; i++)// Recorre el arrglo del nodo
		{
			if (nodo->key[i] == key)
				return false;// No acepta claves repetidas
			else if (nodo->key[i] > key)
			{
				_insetarAux(nodo->hijos[i], key, dato);// Se mueve por el hijo que tiene valores menores a la clave
				if (nodo->hijos[i]->num_claves >= grado)// Revisa si hay problemas en el nodo hijo
					return _revisarCorregirNodo(nodo, key, dato);
				else
					return true;
			}
			else if ((nodo->key[i]<key) && (i+1==nodo->num_claves))
			{
				_insetarAux(nodo->hijos[i+1], key, dato);// Se mueve por el hijo siguiente que no tiene clave
				if (nodo->hijos[i+1]->num_claves >= grado)// Revisa si hay problemas en el nodo hijo
					return _revisarCorregirNodo(nodo, key, dato); //para ir revisando en cada nodo hasta llegar a la raiz
				else
					return true;
			}
		}
				
	}
	return false;
}

template<typename KY, typename DT>
bool ArbolB<KY, DT>::_insertarEnOrden(NodoB*& nodo, KY key, DT dato)
{

	if (nodo->num_claves == 0)// El arrglo esta vacio.
	{	
		nodo->key[0] = key;
		nodo->dato[0] = dato;
		nodo->num_claves++;// indica que ya hay una llave y un dato en el arrglo
		return true;
	}
	else// Ya hay elmentos en los arrglos
	{
		for (int i = 0; i < nodo->num_claves; i++)// Revisar cada elemento para saber si hay que recorrer.
		{// Inserta entre elementos.
			if (key == nodo->key[i])// Para no aceptar claves iguales
				return false;
			else if(key < nodo->key[i])// Para saber donde se va insertar y luego recorrer
			{
				for (int j = nodo->num_claves; j > i; j--)
				{
					nodo->key[j] = nodo->key[j - 1];//Se recorre cada elmento a la derecha	
					nodo->dato[j] = nodo->dato[j - 1];//Se recorre cada dato
				}
				nodo->key[i] = key;//Se inserta el elmento manteniendo el arrglo ordenado
				nodo->dato[i] = dato;
				nodo->num_claves++;
				return true;
			}
			else
			{
				//sigue el recorrido
			}
		}

		//Se inserta el elmento en la ultima posision del arreglo.
		nodo->key[nodo->num_claves] = key;
		nodo->dato[nodo->num_claves] = dato;
		nodo->num_claves++;
		return true;
		
	}
	return false;
}

template<typename KY, typename DT>
bool ArbolB<KY, DT>::_revisarCorregirNodo(NodoB*& nodo, KY key, DT dato)//??????? tengo que borrar key y dato de la funcion
{
	if (nodo->num_claves >= grado)// Hay exceso de claves y por eso hay que arreglar el nodo
	{
		if ((nodo == p_raiz) && (nodo->num_hijos == 0))// Quiere decir que este nodo es la 1era raiz del arbol y no tiene hijos.
		{//!!!!!!funciona!!!!!
			int pivote = 0;
			double grados = static_cast<double>(grado);//Se cambia a double para que se pueda ejecutar correctamente ceil()

			if (grado & 1)
				pivote = static_cast<int>(ceil(grados / 2) - 1.0); // El grado del arbol es impar
				//pivote = static_cast<int>(ceil(grados / 2) - 1.0); // El grado del arbol es impar
			else
				pivote = grado / 2;// El grado del arbol es par


			NodoB* izqnod = p_raiz;
			NodoB* derchonod = new NodoB(); // Crea en memoria un nuevo nodo
			//crea un nuevo nodo raiz
			p_raiz = new NodoB();
			p_raiz->key[0] = izqnod->key[pivote];
			p_raiz->dato[0] = izqnod->dato[pivote];
			p_raiz->hijos[0] = izqnod;//hijo 1
			p_raiz->hijos[1] = derchonod; // hijo 2
			p_raiz->num_claves++;
			p_raiz->num_hijos = +2;

			// Se asignan nuevos valores al nodo derecho
			for (int i = pivote + 1; i < izqnod->num_claves; i++)
			{
				derchonod->key[i - (pivote + 1)] = izqnod->key[i];
				derchonod->dato[i - (pivote + 1)] = izqnod->dato[i];
				derchonod->num_claves++;
			}

			// Se arregla el nodo izquierdo

			izqnod->num_claves = pivote;//
			for (int i = pivote; i < grado; i++)
			{
				izqnod->key[i] = 0;
				izqnod->dato[i] = 0;
			}
			return true;

		}
		else if (nodo->num_hijos == 0)// Indica que el puntero esta en una hoja.
		{
			return false;// para poder subir al nodo padre de esta hoja	
		}

		//return false;
	}
	else if(nodo->num_hijos != 0)//Indica que ya no es una hoja. Aqui solo se accesede llamando la funcion desde un nodo padre
	{
		int badindex=0;
		for (int i = 0; i < nodo->num_claves; i++)// Encuentra el indice del hijo que tiene problema de desborde
		{
			if (nodo->key[i] > key)
			{
				badindex = i;
				break;
			}
			else if ((nodo->key[i] < key) && (i + 1 == nodo->num_claves))
				badindex = i + 1;
		}

		//-------------------SEPARA EL NODO EN CONFLICTO EN DOS NODO Y LE ASIGNA SUS ELEMENTOS CORRESPONDIENTES--\\
		
		int pivote = 0; // indica el indice donde esta el elemento pivote.
		KY keyUp=0; // guarda el valor de la clave que va a subir en el arbol.
		DT datoUp=0;
		double grados = static_cast<double>(grado);//Se cambia a double para que se pueda ejecutar correctamente ceil()

		if (grado & 1)// Con un and se comprueba si es par o impar el el grado
			pivote = static_cast<int>(ceil(grados / 2) - 1.0); // El grado del arbol es impar
		else
			pivote = grado / 2;// El grado del arbol es par

		NodoB* izqnod = nodo->hijos[badindex];// Se reutiliza el nodo existente que se va a dividir.
		NodoB* derchonod = new NodoB(); // Crea en memoria un nuevo nodo

		keyUp= izqnod->key[pivote];// Se obtiene la llave en guardada en el indice pivote
		datoUp = izqnod->dato[pivote];

			// Se asignan nuevos valores al nodo derecho
		for (int i = pivote + 1; i < izqnod->num_claves; i++)
		{
			derchonod->key[i - (pivote + 1)] = izqnod->key[i];
			derchonod->dato[i - (pivote + 1)] = izqnod->dato[i];
			derchonod->num_claves++;
		}

			// Se arregla el nodo izquierdo
		izqnod->num_claves = pivote;//
		for (int i = pivote; i < grado; i++)
		{
			izqnod->key[i] = 0;
			izqnod->dato[i] = 0;
		}

		// Organiza los hijos de los nodos.
		for (int i = pivote + 1; i < grado + 1; i++)
		{
			derchonod->hijos[i - (pivote + 1)] = izqnod->hijos[i];// Hace que los punteros de derecho apunten a los nodos hijos de izq.
			
			if((derchonod->hijos[i - (pivote + 1)])!=nullptr) 
				derchonod->num_hijos++;	//cuenta los hijos del nodo derecho	
			
			if ((izqnod->hijos[i - (pivote + 1)]) != nullptr) // Empieza en la posision cero del arreglo.
				izqnod->num_hijos++;	//cuenta los hijos del nodo izquierdo	
			izqnod->hijos[i] = nullptr;//Deja de apuntar al nodo recien copiado.
		}
		
		
		
		//--------- CORRIGE EL ARBOL DEPENDINDO SI HAY O NO ESPACIO EN EL NODO PADRE----------\
		

		if (nodo->num_claves < (grado-1))// Inserta direccto en el nodo padre porque todavia tiene espacio
		{
			for (int i = grado-1; i > badindex; i--)// Para recorrer los punteros a la derecha y poder conectar los hijos nuevos.
				nodo->hijos[i] = nodo->hijos[i - 1];
			
			nodo->hijos[badindex + 1] = derchonod;// Se concesta el hijo derecho creado en lineas anteriores.
			return _insertarEnOrden(nodo, keyUp, datoUp);
		}
		else if ((nodo->num_claves>=(grado-1)) && (nodo==p_raiz))// DESBORDA LA RAIZ se inserte en un nodo raiz y se desborde. 
		{

			//--------------- DEJA LISTO EL NODO RAIZ RECORRIENDO LOS PUNTEROS HIJOS PARA PODER DIVIDIRLO---------\\
			
			
			for (int i = grado; i > badindex; i--)// Para recorrer los punteros a la derecha y poder conectar los hijos nuevos.
				nodo->hijos[i] = nodo->hijos[i - 1];
			nodo->hijos[badindex + 1] = derchonod;// Se conecta el hijo derecho creado en lineas anteriores.
			_insertarEnOrden(nodo, keyUp, datoUp);


			// --------- SE DIVIDE EL NODO Y SE CREA UNA NUEVA RAIZ ------------------------------\\

			izqnod = p_raiz;// Se reutiliza el nodo existente que se va a dividir.
			derchonod = new NodoB(); // Crea en memoria un nuevo nodo

			keyUp = izqnod->key[pivote];// Se obtiene la llave en guardada en el indice pivote
			datoUp = izqnod->dato[pivote];

			// Se copian los VALORES que le corresponde al nodo derecho
			for (int i = pivote + 1; i < izqnod->num_claves; i++)
			{
				derchonod->key[i - (pivote + 1)] = izqnod->key[i];
				derchonod->dato[i - (pivote + 1)] = izqnod->dato[i];
				derchonod->num_claves++;
			}

			// Se copian los VALORES que le corresponden al nodo izquierdo
			izqnod->num_claves = pivote;
			for (int i = pivote; i < grado; i++)
			{
				izqnod->key[i] = 0;
				izqnod->dato[i] = 0;
			}
			
			for (int i = pivote+1; i < grado+1; i++)
			{
				derchonod->hijos[i - (pivote + 1)] = izqnod->hijos[i];// Hace que los punteros de derecho apunten a los nodos hijos de izq.
				izqnod->hijos[i] = nullptr;//Deja de apuntar al nodo recien copiado.
				derchonod->num_hijos++;
				
			}
			
			//crea un nuevo nodo raiz
			
			p_raiz = new NodoB();// nueva raiz del arbol			
			p_raiz->key[0] = keyUp;
			p_raiz->dato[0] = datoUp;
			p_raiz->hijos[0] = izqnod;//hijo 1
			p_raiz->hijos[1] = derchonod; // hijo 2
			p_raiz->num_claves++;
			p_raiz->num_hijos = +2;

			return true;
		}
		else
		{
			for (int i = grado; i > badindex; i--)// Para recorrer los punteros a la derecha y poder conectar los hijos nuevos.
				nodo->hijos[i] = nodo->hijos[i - 1];
			nodo->hijos[badindex + 1] = derchonod;// Se conecta el hijo derecho creado en lineas anteriores.
			_insertarEnOrden(nodo, keyUp, datoUp);

			return false;

		}
			
		
		return true;
	}
	else  // Se inserta sin desboradar el nodo
	{
		return true;
	}
	return true;//parche
}


// ----------  FUNCIONES PARA ELIMINAR Y CORREGIR NODO PARA MANTERNER PROPIEDADES DEL ARBOL B -------------\\


template<typename KY, typename DT>
bool ArbolB<KY, DT>::_eliminarAux(NodoB*& nodo, KY clave)// Solo se llama esta funcion si existen elmentos en el arbol
{
	// En el caso de que sea una raiz sin hijos
	if ((p_raiz == nodo) && (nodo->num_hijos == 0))
	{
		int index = 0;
		for (int i = 0; i < nodo->num_claves; i++)// Va recorriendo todo el arreglo.
		{
			if (nodo->key[i] == clave)
			{
				index = i;// Se obtiene la posision del elemento a borrar.
				break;
			}
			else if ((i+1) == nodo->num_claves)// Como en la siguiente iteracion se acaba el for quiere decir que no esta el elemento.
			{
				return false;// no se encontro el elemento que se quiere borrar.
			}

		}

		//------ Borrar y recorrer el arreglo si es necesario--------------\\

		for (int i = index; i < nodo->num_claves; i++)
		{
			nodo->key[i] = nodo->key[i + 1];
			nodo->dato[i] = nodo->dato[i + 1];
		}
		nodo->num_claves--;
		return true;

	}
	else 
	{
		int index = _buscarIndex(nodo, clave);

		if (nodo->key[index] == clave && (p_raiz == nodo)) //RAIZ CON HIJOS
		{
			// Se encontro el elmento en la RAIZ con hijos
			return true;
		}
		else if (nodo->key[index] > clave && (nodo->num_hijos > 0)) // Baja el hijo izquierdo
		{
			// Bajar por el hijo izquierdo

			int indice = _buscarIndex(nodo->hijos[index], clave);// Para buscar en el hijo del nodo.
			if ((nodo->hijos[index]->key[indice] == clave) && (nodo->hijos[index]->num_hijos > 0))// Revisa si la clave se encuentra en el hijo.
			{
				//Se encontro elmento eliminarlo en un NODO con hijos
				return true;
			}
			else if ((nodo->hijos[index]->key[indice] == clave) && (nodo->hijos[index]->num_hijos == 0))// La clave esta en una hoja
			{
				// Se encontro elmento eliminarlo en una HOJA
				_eliminarClave(nodo->hijos[index], clave);// Borra la clave en la hoja
				_revisarCorregirHijo(nodo, index);// se debe mandar nodo padre
				return true;
			}
			else if (nodo->hijos[index]->num_hijos > 0)
			{
				_eliminarAux(nodo->hijos[index], clave);// Baja al siguiente nodo utilizando recursividad

			}
			
		}
		else if (nodo->key[index] < clave && (nodo->num_hijos > 0))// Baja por el hijo mas a la derecha del nodo
		{
			// Baja por el ultimo hijo o hijo mas a la derecha
			
			int indice = _buscarIndex(nodo->hijos[index], clave);// Para buscar en el hijo del nodo.
			if ((nodo->hijos[index]->key[indice] == clave) && (nodo->hijos[index]->num_hijos > 0))// Revisa si la clave se encuentra en el hijo.
			{
				//Se encontro elmento eliminarlo en un NODO con hijos
				return true;
			}
			else if ((nodo->hijos[index]->key[indice] == clave) && (nodo->hijos[index]->num_hijos == 0))// La clave esta en una hoja
			{
				// Se encontro elmento eliminarlo en una HOJA
				_eliminarClave(nodo->hijos[index], clave);// Borra la clave en la hoja
				_revisarCorregirHijo(nodo, index);// se debe mandar nodo padre
				return true;
			}
			else if (nodo->hijos[index]->num_hijos > 0)
			{
				_eliminarAux(nodo->hijos[index], clave);// Baja al siguiente nodo utilizando recursividad

			}
		}
		else
		{
			return false; // No se encontro la clave
		}
	}
	return false;
	
}

template<typename KY, typename DT> //Fucion que regresa el indice donde esta la clave o por donde podria estar
int ArbolB<KY, DT>::_buscarIndex(NodoB*& nodo, KY clave)
{
	int index = 0; //Para encontrar el indice donde se puede encontrar la clave que se busca
	for (int i = 0; i < nodo->num_claves; i++)
	{// Va recorriendo todo el arreglo.

		if (nodo->key[i] == clave)//Se encontro el elemento 
		{
			index = i;// Se obtiene la posision del elemento a borrar.
			return i;
		}
		else if (nodo->key[i] > clave)// La clave que se busca debe de estar en los hijos menores de esa clave
		{
			index = i;
			return i;

		}
		else if ((i + 1) == nodo->num_claves)// Como en la siguiente iteracion se acaba el for quiere decir que no esta el elemento.
		{
			return index = i + 1;

		}

	}
	return index;
}

template<typename KY, typename DT>
bool ArbolB<KY, DT>::_eliminarClave(NodoB*& hoja, KY clave)// Esta funcion recibe la hoja donde se encuentra la clave a borrar.
{
	int index = _buscarIndex(hoja, clave);
	if (hoja->key[index]==clave)
	{
		hoja->key[index] = 0;
		hoja->dato[index] = 0;
		
		for (int i = index; i < hoja->num_claves; i++)
		{
			hoja->key[i] = hoja->key[i + 1];
			hoja->dato[i] = hoja->dato[i + 1];
			
		}
		hoja->num_claves--;
		return true;
	}
	else
		return false;
}

template<typename KY, typename DT>
bool ArbolB<KY, DT>::_revisarCorregirHijo(NodoB*& padre, int index)// Resive el nodo padre y el indice del nodo a revisar
{
	double grados = static_cast<double>(grado);//Se cambia a double para que se pueda ejecutar correctamente ceil()
	int minimo = ceil(grados / 2) - 1;
			
	if (padre->hijos[index]->num_claves >= minimo)// Indica que las propiedades del arbol estan correctas.
		return true; 
	else// No hay claves suficientes en el nodo
	{
		_pedirClave(padre, index);
		return true;
	}
	return false;
}

template<typename KY, typename DT>
bool ArbolB<KY, DT>::_pedirClave(NodoB*& padre, int index)
{
	int izq = 0;
	int der = index + 1; // Como hay una clave extra en el lado dercho del arreglo de hijos no hay problema

	if (index < 1)// Verifica para evitar salirse del indice del arrglo de hijos
		izq = 0;
	else
		izq = index - 1;
	
	double grados = static_cast<double>(grado);//Se cambia a double para que se pueda ejecutar correctamente ceil()
	int minimo = ceil(grados / 2) - 1;

	if ((index>0)&&(padre->hijos[izq]->num_claves>minimo)) // El hermano izquierdo entrega clave
	{
		// Se puede hacer el prestamo del hermano izquierdo al nodo en problemas.

		_insertarEnOrden(padre->hijos[index], padre->key[izq], padre->dato[izq]); // Inserta la clave que va a bajar del padre.
		padre->key[izq] = padre->hijos[izq]->key[padre->hijos[izq]->num_claves - 1];// Sube la clave mas a la dercha del hijo izquierdo.
		padre->dato[izq] = padre->hijos[izq]->dato[padre->hijos[izq]->num_claves - 1];// Sube el dato mas a la dercha del hijo izquierdo.
		
		padre->hijos[izq]->key[padre->hijos[izq]->num_claves - 1] = 0;
		padre->hijos[izq]->dato[padre->hijos[izq]->num_claves - 1] = 0;
		padre->hijos[izq]->num_claves--; //Resta una clave al hijo izquierdo con esto se elimina la clave
		
		
		//Recorre los hijos del nodo en problemas una posision a la derecha
		for (int i = ((padre->hijos[index]->num_claves)-1); i > 0 ; i--)
			padre->hijos[index]->hijos[i] = padre->hijos[index]->hijos[i - 1];
		
		padre->hijos[index]->hijos[0] = padre->hijos[izq]->hijos[padre->hijos[izq]->num_claves]; //Copia los hijos que pudiera tener esa clave
		padre->hijos[izq]->hijos[padre->hijos[izq]->num_claves] = nullptr;
		// Se usa el num_claves sin restarle 1, debido a que en la linea anterior ya se ha realizado la resta.
		return true;
	}
	else if ((index<(grado-1)) && (padre->hijos[der]->num_claves > minimo))//El hermano derecho entrega la clave
	{
		if ((padre->num_claves < 2) || (padre->num_claves >= grado - 1))
			der--;// En el caso de estar despues de la ultima clave del arreglo, se regresa una posision.
				
		_insertarEnOrden(padre->hijos[index], padre->key[der], padre->dato[der]); // Inserta la clave que va a bajar del padre.
		
		padre->key[der] = padre->hijos[index+1]->key[0];// Sube la clave mas a la izquierda del hijo derecho.
		padre->dato[der] = padre->hijos[index+1]->dato[0];// Sube el dato mas a la izquierda del hijo derecho.
		
		padre->hijos[index]->hijos[padre->hijos[index]->num_claves - 1] = padre->hijos[index+1]->hijos[0]; //Copia el hijo mas a la izquierda del hermano derecho.

		padre->hijos[index+1]->num_claves--; //Resta una clave al hijo derecho con esto se elimina la clave
		
			// Recorre los elmentos del hijo derecho una posision a la izquierda
		for (int i = 0; i < (padre->hijos[index+1]->num_claves); i++)
		{
			padre->hijos[index + 1]->key[i] = padre->hijos[index + 1]->key[i + 1];
			padre->hijos[index + 1]->dato[i] = padre->hijos[index + 1]->dato[i + 1];
			padre->hijos[index + 1]->hijos[i] = padre->hijos[index + 1]->hijos[i + 1];
		}

		return true;
	}
	else
	{
		// No se puede pedir prestado a los hermanos no tienen las claves suficientes
		return false;
	}
	
}

//template<typename KY, typename DT>
//void ArbolB<KY, DT>::_imprimirAux(NodoB*& nodo, int contador)// Solo se manda llamar esta funcion si hay elementos en el arbol
//{
//	
//	
//		if (nodo->hijos[0]==nullptr) // Solo existe la raiz.
//		{
//			_imprimrArreglo(nodo);// Solo debe de imprimir el arrglo de claves
//		}
//
//}

