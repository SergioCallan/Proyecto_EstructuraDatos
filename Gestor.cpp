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

struct Paciente{
	string dni;
	string nombres;
	string apellidos;
	string celular;
	struct Paciente *sgte;
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

struct Personal{
	struct Personal *ant;
	string id;
	string nombre;
	string apellidos;
	int salario;
	string especialidad;
	struct Personal *sgte;
};

typedef struct Personal *TpPersonal;
typedef struct Cita *TpCita;
typedef struct Paciente *TpPaciente;

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

TpPaciente registroPaciente(){
	TpPaciente nuevo = NULL;
	nuevo = new(struct Paciente);
	cout<<"Ingrese el dni:"<<endl;
	cin>>nuevo->dni;
	cout<<"Ingrese los nombres:"<<endl;
	cin>>nuevo->nombres;
	cout<<"Ingrese los apellidos:"<<endl;
	cin>>nuevo->apellidos;
	cout<<"Ingrese el numero de telefono:"<<endl;
	cin>>nuevo->celular;
	nuevo->sgte = NULL;
	cout<<"El paciente ha sido registrado correctamente."<<endl;
	return nuevo;
}

void insertarPaciente(TpPaciente &paciente){
	TpPaciente nuevo = registroPaciente(), p=paciente;
	if(paciente==NULL){
		paciente = nuevo;
	}else{
		while(p->sgte != NULL)
			p=p->sgte;
		p->sgte = nuevo;
	}
}



void menuPaciente(TpPaciente &paciente){
	int opc;
	
	do{
		cout<< "\n\t1. Registrar Paciente\n";
		cout<< "\t2. Buscar, modificar o borrar historial medico\n";
		cout<< "\t3. Regresar\n";
		cin>> opc;
		switch(opc){
			case 1:{
				insertarPaciente(paciente);
				break;
			}
			case 2:{
				
				break;
			}
			case 3:{
				break;
			}
		}
	} while(opc!=3);
}

TpPersonal registroPersonal(){
	TpPersonal nuevo = NULL;
	nuevo = new(struct Personal);
	cout<<"Ingrese el id:"<<endl;
	cin>>nuevo->id;
	cout<<"Ingrese los nombres:"<<endl;
	cin>>nuevo->nombre;
	cout<<"Ingrese los apellidos:"<<endl;
	cin>>nuevo->apellidos;
	cout<<"Ingrese el salario:"<<endl;
	cin>>nuevo->salario;
	cout<<"Ingrese la especialidad:"<<endl;
	cin>>nuevo->especialidad;
	nuevo->ant = NULL;
	nuevo->sgte = NULL;
	return nuevo;
}

void insertarPersonal(TpPersonal &personal){
	int pos;
	TpPersonal nuevo = NULL, p=personal;
	nuevo = registroPersonal();
	if(personal == NULL){
		nuevo->ant = nuevo;
		nuevo->sgte = nuevo;
		personal = nuevo;
	}else{
		cout<<"Ingrese la posicion del horario del medico"<<endl;
		cin>>pos;
		if(pos==1){
			personal->ant->sgte = nuevo;
			nuevo->ant = personal->ant;
			nuevo->sgte = personal;
			personal->ant = nuevo;
			personal=nuevo;
		}else{
			int x=1;
			bool encontrado = false;
			while(p->sgte != personal && x!=pos){
				p = p->sgte;
				x++;
			}
			if(x==pos){
				p->ant->sgte = nuevo;
				nuevo->ant = p->ant;
				p->ant = nuevo;
				nuevo->sgte = p;
			}else{
				cout<<"La longitud de la lista es menor a la posicion buscada."<<endl;
			}
			
		}
	}
}


void menuMedico(TpPersonal &personal){
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
			case 1:{
				insertarPersonal(personal);
				break;
			}
			case 2:{
				
				break;
			}
			case 3:{
				
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
	TpPersonal personal = NULL;
	TpPaciente paciente = NULL;
	TpCita cita=NULL;
	do{
		opc=menuPrincipal();
		switch(opc){
			case 1:{
				menuPaciente(paciente);
				break;
			}
			case 2:{
				menuMedico(personal);
				break;
			}
		}
	} while(opc!=3);
	cout<< "Gracias por usar el sistema de gestion\n";
}
