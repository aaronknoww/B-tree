#include "../Headers/Precom.h"// precompiledheader
#include "../Headers/ArbolB.h"
#include "../Source/ArbolB.cpp"
#include "../Source/PrivadasFun.cpp"

using namespace std;

int main()
{
	ArbolB<int, double> btree;

	btree.insertar(10, 5.09834);
	btree.insertar(20, 25.09834);
	btree.insertar(30, 51.09834);
	btree.insertar(40, 84.09834);
	btree.insertar(1, 194.09834);

	btree.insertar(50, 50.509834);
	btree.insertar(35, 35.509834);
	btree.insertar(55, 35.509834);
	
	//btree.insertar(60, 65.509834);
	btree.insertar(15, 15.509834);
	btree.insertar(15, 15.509834);



	/*btree.insertar(11, 11.09834);
	btree.insertar(12, 51.09834);
	btree.insertar(31, 81.09834);
	btree.insertar(32, 41.09834);*/

	cout << "\nhello mother fuckers" << endl;
	system("pause > null");
	
	return 0;
}