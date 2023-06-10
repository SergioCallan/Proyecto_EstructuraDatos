#include <iostream>
#include<fstream>
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

struct Medicamento{
	string id;
	int precio;
	int unidades;
	string contraindicaciones;
	struct Medicamento *sgte;
};

typedef struct Personal *TpPersonal;
typedef struct Cita *TpCita;
typedef struct Paciente *TpPaciente;
typedef struct Medicamento *TpMedicamento;

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


//************************************************** PACIENTE ******************************
TpPaciente registroPaciente(){
	TpPaciente nuevo = NULL;
	nuevo = new(struct Paciente);
	cout<<"Ingrese el dni:"<<endl;
	cin>>nuevo->dni;
	cout<<"Ingrese los nombres:"<<endl;
	cin.ignore();
	getline(cin,nuevo->nombres);
	cout<<"Ingrese los apellidos:"<<endl;
	cin.ignore();
	getline(cin,nuevo->apellidos);
	cout<<"Ingrese el numero de telefono:"<<endl;
	cin>>nuevo->celular;
	nuevo->sgte = NULL;
	cout<<"El paciente ha sido registrado correctamente."<<endl;
	return nuevo;
}

void insertarPaciente(TpPaciente &paciente, TpPaciente nuevo, bool existe){
	if(existe==false){
		nuevo = registroPaciente();
	}
	TpPaciente p=paciente;
	if(paciente==NULL){
		paciente = nuevo;
	}else{
		while(p->sgte != NULL)
			p=p->sgte;
		p->sgte = nuevo;
	}
}

void verListaPaciente(TpPaciente lista){
	int i=0; TpPaciente p = lista;
	cout<<"DNI - NOMBRES - APELLIDOS - CELULAR"<<endl;
	while(p != NULL){
		cout<< " "<<i+1<<") "<<p->dni<<" - "<<p->nombres<<" - "<<p->apellidos<<" - "<<p->celular<< endl;
		p=p->sgte;
		i++;	
}}

void insertarTXTPaciente(TpPaciente &paciente, ofstream &PacienteTXT){
	TpPaciente p = paciente;
	if(paciente!=NULL){
		while(p->sgte != NULL){
			p=p->sgte;	
		}
	}
	
	PacienteTXT<<p->dni<<endl;
	PacienteTXT<<p->nombres<<endl;
	PacienteTXT<<p->apellidos<<endl;
	PacienteTXT<<p->celular<<endl;
}

void recuperarTXTPaciente(TpPaciente &paciente){
	ifstream PacienteTXT("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\Pacientes.txt",ios::in);
	string d, n, a, c;
	getline(PacienteTXT,d);
	while(!PacienteTXT.eof()){
		getline(PacienteTXT,n);
		getline(PacienteTXT,a);
		getline(PacienteTXT,c);
		TpPaciente nuevo = NULL;
		nuevo = new(struct Paciente);
		nuevo->dni = d;
		nuevo->nombres = n;
		nuevo->apellidos = a;
		nuevo->celular = c;
		nuevo->sgte=NULL;
		insertarPaciente(paciente, nuevo, true);
		getline(PacienteTXT,d);
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
				system("CLS");
				TpPaciente nuevo = NULL;
				ofstream PacienteTXT("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\Pacientes.txt",ios::app);
				insertarPaciente(paciente, nuevo, false);
				insertarTXTPaciente(paciente, PacienteTXT);
				PacienteTXT.close();
				cout<<"\n\n\n\n";
				verListaPaciente(paciente);
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



// **************************** PERSONAL ***************************

TpPersonal registroPersonal(){
	TpPersonal nuevo = NULL;
	nuevo = new(struct Personal);
	cout<<"Ingrese el id:"<<endl;
	cin.ignore();
	getline(cin,nuevo->especialidad);
	cout<<"Ingrese los nombres:"<<endl;
	cin.ignore();
	getline(cin,nuevo->nombre);
	cout<<"Ingrese los apellidos:"<<endl;
	cin.ignore();
	getline(cin,nuevo->apellidos);
	cout<<"Ingrese el salario:"<<endl;
	cin>>nuevo->salario;
	cout<<"Ingrese la especialidad:"<<endl;
	cin.ignore();
	getline(cin,nuevo->especialidad);
	nuevo->ant = NULL;
	nuevo->sgte = NULL;
	return nuevo;
}



void verListaPersonal(TpPersonal lista){
	int i=0;
    TpPersonal p=lista;
    if(lista==NULL){
    	cout<<"lista vacia"<<endl<<endl;
	}else{
		cout<<"ID - NOMBRES - APELLIDOS - SALARIO - ESPECIALIDAD"<<endl;
    do{
        cout<< " "<<i+1<<") "<<p->id<<" - "<<p->nombre<<" - "<<p->apellidos<<" - "<<p->salario<<" - "<<p->especialidad<< endl;
        p=p->sgte;
        i++;
    } while ( p!= lista);
}}

bool existeUnPersonal(TpPersonal personal){
	int i = 1; TpPersonal p = personal; bool existe=false;
	while( p->sgte != personal){
		p=p->sgte;
		i++;
	}
    
    if(i==1){
    	existe = true;
	}
	return existe;
}

void insertarPersonal(TpPersonal &personal, TpPersonal nuevo, bool existe){
	int pos;
	TpPersonal p=personal;
	if(existe==false){
		nuevo = registroPersonal();
		if(personal == NULL){
			nuevo->ant = nuevo;
			nuevo->sgte = nuevo;
			personal = nuevo;
		}else{
			cout<<"Ingrese la posicion del horario del medico"<<endl;
			cin>>pos;
			if(pos==1){
				if(existeUnPersonal(personal)){
					nuevo->sgte = personal;
					nuevo->ant = personal;
					personal->sgte = nuevo;
					personal->ant = nuevo;
					personal = nuevo;
				}else{
					personal->ant->sgte = nuevo;
					nuevo->sgte = personal;
					nuevo->ant = personal->ant;
					personal->ant = nuevo;
					personal=nuevo;	
				}
			}else{
				int x=1; bool encontrado=false;
				while(p->sgte != personal && x!=pos){
					p = p->sgte;
					x++;
					if(x==pos){
						encontrado = true;
					}
				}
				if(encontrado==true){
					nuevo->sgte = p;
					nuevo->ant = p->ant;
					p->ant->sgte = nuevo;
					p->ant = nuevo;
				}else{
					cout<<"La longitud de la lista es menor a la posicion buscada."<<endl;
				}
				
			}
	}}else{
		if(personal == NULL){
			nuevo->ant = nuevo;
			nuevo->sgte = nuevo;
			personal = nuevo;
		}else{
			while(p->sgte != personal){
				p = p->sgte;
			}
				personal->ant->sgte = nuevo;
				nuevo->ant = personal->ant;
				nuevo->sgte = personal;
				personal->ant = nuevo;
		}
	}
}

void insertarTXTPersonal(TpPersonal &personal, ofstream &PersonalTXT){ 
	TpPersonal p = personal;
	if(personal!=NULL){
		while(p->sgte != personal){
			PersonalTXT<<p->id<<endl;
			PersonalTXT<<p->nombre<<endl;
			PersonalTXT<<p->apellidos<<endl;
			PersonalTXT<<p->salario<<endl;
			PersonalTXT<<p->especialidad<<endl;
			p=p->sgte;	
		}
	}
	PersonalTXT<<p->id<<endl;
	PersonalTXT<<p->nombre<<endl;
	PersonalTXT<<p->apellidos<<endl;
	PersonalTXT<<p->salario<<endl;
	PersonalTXT<<p->especialidad<<endl;
}

void recuperarTXTPersonal(TpPersonal &personal){
	ifstream PersonalTXT("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\Personal.txt",ios::in);
	string i, n, a, s, e;
	getline(PersonalTXT,i);
	while(!PersonalTXT.eof()){
		getline(PersonalTXT,n);
		getline(PersonalTXT,a);
		getline(PersonalTXT,s);
		getline(PersonalTXT,e);
		TpPersonal nuevo = NULL;
		nuevo = new(struct Personal);
		nuevo->ant = NULL;
		nuevo->id = i;
		nuevo->nombre = n;
		nuevo->apellidos = a;
		nuevo->salario = stoi(s);
		nuevo->especialidad = e;
		nuevo->sgte=NULL;
		insertarPersonal(personal, nuevo, true);
		getline(PersonalTXT,i);
	}
}

//*********************************************  MEDICAMENTO  ****************************************

TpMedicamento registroMedicamento(){
	TpMedicamento nuevo = NULL;
	nuevo = new(struct Medicamento);
	cout<<"Ingrese el id:"<<endl;
	cin>>nuevo->id;
	cout<<"Ingrese el precio:"<<endl;
	cin>>nuevo->precio;
	cout<<"Ingrese las unidades disponibles:"<<endl;
	cin>>nuevo->unidades;
	cout<<"Ingrese las contraindicaciones:"<<endl;
	cin.ignore();
	getline(cin,nuevo->contraindicaciones);
	nuevo->sgte = NULL;
	cout<<"El medicamento ha sido registrado correctamente."<<endl;
	return nuevo;
}

void insertarMedicamento(TpMedicamento &medicamento, TpMedicamento nuevo, bool existe){
	if(existe==false){
		nuevo = registroMedicamento();
	}
	TpMedicamento p=medicamento;
	
	if(medicamento==NULL){
		medicamento = nuevo;
	}else{
		while(p->sgte != NULL)
			p=p->sgte;
		p->sgte = nuevo;
	}	
}

void insertarTXTMedicamento(TpMedicamento &medicamento, ofstream &MedicamentoTXT){
	TpMedicamento p = medicamento;
	if(medicamento!=NULL){
		while(p->sgte != NULL){
			p=p->sgte;	
		}
	}
	
	MedicamentoTXT<<p->id<<endl;
	MedicamentoTXT<<p->precio<<endl;
	MedicamentoTXT<<p->unidades<<endl;
	MedicamentoTXT<<p->contraindicaciones<<endl;
}

void recuperarTXTMedicamento(TpMedicamento &medicamento){
	ifstream MedicamentoTXT("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\Medicamentos.txt",ios::in);
	string i, p, u, c;
	getline(MedicamentoTXT,i);
	while(!MedicamentoTXT.eof()){
		getline(MedicamentoTXT,p);
		getline(MedicamentoTXT,u);
		getline(MedicamentoTXT,c);
		TpMedicamento nuevo = NULL;
		nuevo = new(struct Medicamento);
		nuevo->id = i;
		nuevo->precio = stoi(p);
		nuevo->unidades = stoi(u);
		nuevo->contraindicaciones = c;
		nuevo->sgte=NULL;
		insertarMedicamento(medicamento, nuevo, true);
		getline(MedicamentoTXT,i);
	}
}





void verListaMedicamento(TpMedicamento lista){
	int i=0; TpMedicamento p = lista;
	cout<<"ID - PRECIO - UNIDADES \t - CONTRAINDICACIONES"<<endl;
	while(p != NULL){
		cout<< " "<<i+1<<") "<<p->id<<" - "<<p->precio<<" - "<<p->unidades<<" -\t "<<p->contraindicaciones<< endl;
		p=p->sgte;
		i++;	
}}


void menuMedico(TpPersonal &personal, TpMedicamento &medicamento){
	int opc;
	
	do{
		system("CLS");
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
				system("CLS");
				TpPersonal nuevo = NULL;
				ofstream PersonalTXT("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\modificacion.txt",ios::app);
				insertarPersonal(personal, nuevo, false);
				insertarTXTPersonal(personal, PersonalTXT);
				PersonalTXT.close();
				remove("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\Personal.txt");
				rename("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\modificacion.txt","D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\Personal.txt");
				cout<<"\n\n\n\n";
				verListaPersonal(personal);
				break;
			}
			case 2:{
				system("CLS");
				ofstream MedicamentoTXT("D:\\CLASES UNMSM\\5 CICLO\\Estructura de datos\\PROYECTO\\Medicamentos.txt",ios::app);
				TpMedicamento nuevo = NULL;
				insertarMedicamento(medicamento, nuevo, false);
				insertarTXTMedicamento(medicamento, MedicamentoTXT);
				MedicamentoTXT.close();
				cout<<"\n\n\n\n";
				verListaMedicamento(medicamento);
				break;
			}
			case 3:{
				cout<<"\n\n\n\n";
				verListaPersonal(personal);
				break;
			}
			case 4:{
				editarCita();
				break;
			}
			case 5:{
				
				break;
			}
			case 6:{
				
				break;
			}
		}
		system("pause");
	} while(opc!=7);
}

// ******************************************* MAIN ***********************

int main(){
	int opc;
	TpPersonal personal = NULL;
	TpPaciente paciente = NULL;
	TpCita cita=NULL;
	TpMedicamento medicamento = NULL;
	recuperarTXTPersonal(personal);
	recuperarTXTPaciente(paciente);
	// recuperarTXTCita(cita);
	recuperarTXTMedicamento(medicamento);
	do{
		system("CLS");
		opc=menuPrincipal();
		switch(opc){
			case 1:{
				menuPaciente(paciente);
				break;
			}
			case 2:{
				menuMedico(personal, medicamento);
				break;
			}
		}
	} while(opc!=3);
	cout<< "Gracias por usar el sistema de gestion\n";
}
