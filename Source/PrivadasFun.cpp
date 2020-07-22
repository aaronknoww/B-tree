#include "..\Headers\Precom.h"
#include "..\Headers\ArbolB.h"

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

			
		
		return true;
	}
	else  // Se inserta sin desboradar el nodo
	{
		return true;
	}
	return true;//parche
}

// EL ARBOL YA CORRIGE CUANDO SE DESBORDA LA PRIMERA  RAIZ Y SE PUEDEN INSERTAR VALORES EN LOS NODOS HIJOS 
// QUE SE CREARON DESPUES DE EL DESBORDE. FALTA INICIAR CON EL PROCESO DE REPARACION DE CUANDO SE DESBORDAN\
// LOS OTROS HIJOS