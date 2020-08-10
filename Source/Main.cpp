#include "../Headers/Precom.h"// precompiledheader
#include "../Headers/ArbolB.h"
#include "../Source/ArbolB.cpp"
#include "../Source/PrivadasFun.cpp"

using namespace std;

int main()
{
	ArbolB<int, double> btree;

	

	// Se crea un arbol B de tres niveles
	btree.insertar(10, 51.09834);//inicio de raiz
	btree.insertar(13, 84.09834);
	btree.insertar(15, 194.09834);
	btree.insertar(17, 194.09834);// fin de raiz

	btree.insertar(21, 194.09834);// ----- primer desborde rope la primer raiz

	btree.insertar(14, 14.09834);
	btree.insertar(5, 14.09834);
	btree.insertar(25, 14.09834);
	btree.insertar(30, 30.23404);

	btree.insertar(3, 3.21651); //-----segundo desborde
	btree.insertar(35, 35.21651); //-----tercer desborde

	btree.insertar(2, 2.09834);
	btree.insertar(6, 6.09834);
	
	btree.insertar(7, 7.23404);//-----cuarto desborde


	btree.insertar(27, 27.35414);
	btree.insertar(28, 28.09834);


	btree.insertar(40, 40.09834);//---- raiz y desborde 3 nivel
	
	//---- Fin de la creacion del arbol B

	btree.eliminar(25);// ***??? problemas al eliminar 25  sab 08/08/20

	btree.eliminar(10);
	btree.eliminar(10);



	//con estas lineas se pruebe la eliminacion donde se pide clave al hermano y fusion izq a der.
	/* ya funciona
	btree.insertar(10, 51.09834);
	btree.insertar(13, 84.09834);
	btree.insertar(15, 194.09834);
	btree.insertar(17, 194.09834);
	
	btree.insertar(21, 194.09834);
	
	btree.insertar(14, 14.09834);

	
	btree.eliminar(21);

	btree.eliminar(10);
	btree.eliminar(10);
	*/
	
	



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