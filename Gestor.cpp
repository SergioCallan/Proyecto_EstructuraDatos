#include <iostream>
using namespace std;

struct Fecha{
	int dd;
	int mm;
	int yyyy;
};

struct Hora{
	int seg;
	int min;
};

struct Cita{
	int idmedico;
	int id;	
	int idpaciente;
	int dia;
	int mes;
	int anio;
	int hora;
	int min;
	struct Cita *sgte;
};

typedef struct Cita *TpCita;

TpCita crearCita(){
	system("cls");
	TpCita n= NULL;
	n= new(struct Cita);
	cout<< "Ingresar id de Medico: ";
	cin>> n->idmedico;
	cout<< "Ingresar id de Paciente: ";
	cin>> n->idpaciente;
	cout<< "Ingresar fecha(dd/mm/yyyy): ";
	cin >> n->dia;
	cin >> n->mes;
	cin >> n->anio;
	cout<< "Ingresar hora(hora/min): ";
	cin >> n->hora;
	cin >> n->min;
	n->sgte=NULL;
}

void encolarCita(TpCita &cita){
	TpCita n, p=cita;
	n= crearCita();
	if(cita==NULL)
		cita=n;
	else{
		while(p->sgte!=NULL)
			p=p->sgte;
		p->sgte=n;
	}
	
}

void editarCita(){
	
}

int menuPrincipal(){
	int opc;
	cout<< "Bienvenido al gestor medico\n";
	cout<< "\t1. Pacientes\n";
	cout<< "\t2. Medicos\n";
	cout<< "\t3. Salir\n";
	cin>> opc;
	system("cls");
	return opc;
}

void menuPaciente(){
	int opc;
	do{
		cout<< "\n\t1. Registrar Paciente\n";
		cout<< "\t2. Buscar, modificar o borrar historial medico\n";
		cout<< "\t3. Regresar\n";
		cin>> opc;
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
		cin>> opc;
		switch(opc){
			case 3:{
				encolarCita(cita);
				break;
			}
			case 4:{
				editarCita();
				break;
			}
			case 5:{
				
				break;
			}
		}
		system("pause");
		system("cls");
	} while(opc!=7);
}

int main(){
	int opc;
	TpCita cita=NULL;
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
