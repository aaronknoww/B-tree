#include "../Headers/Precom.h"// precompiledheader
#include "../Headers/ArbolB.h"
#include "../Source/ArbolB.cpp"
#include "../Source/PrivadasFun.cpp"

using namespace std;

int main()
{
	ArbolB<int, double> btree;

	
	btree.insertar(10, 51.09834);
	btree.insertar(13, 84.09834);
	btree.insertar(15, 194.09834);
	btree.insertar(17, 194.09834);
	
	btree.insertar(21, 194.09834);
	
	btree.insertar(14, 14.09834);

	
	btree.eliminar(21);// hay error debo de seguir depurando esta funcion.

	//??? PROBAR ELIMINAR EN HOJA CUANDO NECESITA PEDIR PRESTADO
	//?? PARA ESTO DEBO DE INGRESAR MAS ELMENTOS
	btree.eliminar(25);
	
	



	//btree.insertar(5, 15.509834);
	//btree.insertar(25, 25.509834);
	//btree.insertar(25, 25.509834);



	/*btree.insertar(11, 11.09834);
	btree.insertar(12, 51.09834);
	btree.insertar(31, 81.09834);
	btree.insertar(32, 41.09834);*/

	cout << "\nhello mother fuckers" << endl;
	system("pause > null");
	
	return 0;
}