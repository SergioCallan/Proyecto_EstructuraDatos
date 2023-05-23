#include <iostream>
using namespace std;

int menuPrincipal(){
	int opc;
	cout<< "\tBienvenido al gestor medico\n";
	cout<< "\t1. Pacientes\n";
	cout<< "\t2. Medicos\n";
	cout<< "\t3. Salir\n";
	cin>> opc;
	return opc;
}

void menuPaciente(){
	int opc;
	do{
		cout<< "1. Registrar Paciente\n";
		cout<< "2. Buscar, modificar o borrar historial medico\n";
		cout<< "3. Regresar\n";
	} while(opc!=3);
}

void menuMedico(){
	int opc;
	do{
		cout<< "1. Registrar Personal\n";
		cout<< "2. Registrar Medicinas\n";
		cout<< "3. Crear citas\n";
		cout<< "4. Editar citas\n";
		cout<< "5. Eliminar cita\n";
		cout<< "6. Generar prescripcion\n";
		cout<< "7. Regresar\n";
	} while(opc!=7);
	
}

int main(){
	int opc;
	do{
		opc=menuPrincipal();
		switch(opc){
			case 1:{
				menuPaciente();
				break;
			}
			case 2:{
				menuMedico();
				break;
			}
		}
	} while(opc!=3);
	cout<< "Gracias por usar el sistema de gestion\n";
}
