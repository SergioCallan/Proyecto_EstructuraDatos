#include <iostream>
#include<fstream>
#include<sstream>
using namespace std;

struct Paciente{
	string dni;
	string nombres;
	string apellidos;
	string celular;
	struct Paciente *sgte;
};

struct Cita{
	string idMedico;
	string dniPaciente;
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

struct Historial{
	
	string DNI;
	string NombreCompleto;
	string Enfermedad;
	string Alergias;
	string DiagnosticoGeneral;
	struct Historial *sgte;
	
};

struct ConsultasHistorial{
	
	string DNIpaciente;
	int dia;
	int mes;
	int anio;
	string Motivo;
	string Antecedente;
	string Desarrollo;	
	
	struct ConsultasHistorial *sgte;
	
};

struct PruebasHistorial{
	
	string DNIPaciente;
	int dia;
	int mes;
	int anio;
	string NombreDePrueba;
	string Resultado;	
	
	struct PruebasHistorial *sgte;
	
};

typedef struct Personal *TpPersonal;
typedef struct Cita *TpCita;
typedef struct Paciente *TpPaciente;
typedef struct Medicamento *TpMedicamento;

//Historial
typedef struct Historial *TpHistorial;
typedef struct ConsultasHistorial *TpConsulta;
typedef struct PruebasHistorial *TpPruebas;

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

bool buscarID(TpPersonal personal, string idMedico){
	
	if(personal == NULL){
		
		return false;
		
	}
	
	do{
		if(personal->id==idMedico)
			return true;
		personal=personal->sgte;
	}while(personal->sgte!=personal);
	return false;
}

bool buscarDNI(TpPaciente paciente, string dniPaciente){
	while(paciente!=NULL){
		if(paciente->dni==dniPaciente)
			return true;
		paciente=paciente->sgte;
	}
	return false;
}

//************************************************** HISTORIAL ******************************



TpHistorial crearHistorial(string DNI, string nombreCom){
	
	int op;
	
	TpHistorial nuevo = NULL;
	nuevo = new (struct Historial);

	nuevo->DNI=DNI;
	nuevo->NombreCompleto = nombreCom;
	nuevo->Enfermedad = "Sin Especificar";
	nuevo->Alergias = "Sin Especificar";
	nuevo->DiagnosticoGeneral = "Sin Especificar";
	
	nuevo->sgte= NULL;
	return nuevo;
	
}

void encolarHistorial(TpHistorial &historial, TpHistorial nuevo){
	
	TpHistorial p = historial;
	
	if(historial==NULL) historial = nuevo;

	else{
		
		while(p->sgte != NULL) p=p->sgte;
		
		p->sgte = nuevo;
		
	}
	
}


void insertarHistorial(TpHistorial &historial, TpPaciente paciente, bool existe){
	
	TpHistorial nuevo = NULL;
	
	if(existe == false){
		
		
		
		nuevo = crearHistorial(paciente->dni,paciente->nombres + " " + paciente->apellidos);
		
	}

	encolarHistorial (historial, nuevo);
	
}

void insertarTXTHistorial(TpHistorial &historial, ofstream &HistorialTXT){
	
	TpHistorial p = historial;
	
	if(historial!=NULL){
		while(p->sgte != NULL){
			p=p->sgte;	
		}
	}
	
	HistorialTXT<<p->DNI<<endl;
	HistorialTXT<<p->NombreCompleto<<endl;
	HistorialTXT<<p->Enfermedad<<endl;
	HistorialTXT<<p->Alergias<<endl;
	HistorialTXT<<p->DiagnosticoGeneral<<endl;
	
}

void recuperarTXTHistorial(TpHistorial &hist){
	
	ifstream HistorialTXT("Historial.txt",ios::in);
	
	string DNI, nombre, enfermedad, alergias, diagnostico;
	
	getline(HistorialTXT,DNI);
	
	while(!HistorialTXT.eof()){
		
		getline(HistorialTXT,nombre);
		getline(HistorialTXT,enfermedad);
		getline(HistorialTXT,alergias);
		getline(HistorialTXT,diagnostico);
		
		TpHistorial nuevo = NULL;
		nuevo = new(struct Historial);
		
		nuevo->DNI = DNI;
		nuevo->NombreCompleto = nombre;
		nuevo->Enfermedad = enfermedad;
		nuevo->Alergias = alergias;
		nuevo->DiagnosticoGeneral = diagnostico;
		
		nuevo->sgte=NULL;
		
		encolarHistorial(hist, nuevo);
		getline(HistorialTXT,DNI);
			
	}
	
}

void copiarTXTHistorial(TpHistorial &historial, ofstream &HistorialTXT){
	
	TpHistorial p = historial;
	while(p!=NULL){
		
		HistorialTXT<<p->DNI<<endl;
		HistorialTXT<<p->NombreCompleto<<endl;
		HistorialTXT<<p->Enfermedad<<endl;
		HistorialTXT<<p->Alergias<<endl;
		HistorialTXT<<p->DiagnosticoGeneral<<endl;
		p=p->sgte;
	}
	
}

void modificarHistorial(TpHistorial &p){
	
	int op;
	
	cout<<"\n\t\tDesea modificar el historial del paciente?\n";
	cout<<"\t\t (1): Si\n";
	cout<<"\t\t (2): No\n\n";
	
	cout<<"\t\t Opcion: ";
	
	do{
		
		cin>>op;
		
	}while(op<1 || op>2);
			
	if(op == 1){
		
		cout<<"\nModificar \"Enfermedad\"?\n";
		cout<<"(1): Si\n";
		cout<<"(2): No\n\n";
	
		cout<<"Opcion: ";
		
		do{
		
			cin>>op;
			
		}while(op<1 || op>2);
		
		if(op == 1){
			
			cin.ignore();
			cout<<"\n**Enfermedad - "<<p->NombreCompleto<<" (Actualizacion): ";
			getline(cin,p->Enfermedad);
			
		}
		
		cout<<"\nModificar \"Alergias\"?\n";
		cout<<"(1): Si\n";
		cout<<"(2): No\n\n";
	
		cout<<"Opcion: ";
		
		do{
		
			cin>>op;
			
		}while(op<1 || op>2);
		
		if(op == 1){
			
			cin.ignore();
			cout<<"\n**Alergias - "<<p->NombreCompleto<<" (Actualizacion): ";
			getline(cin,p->Alergias);
			
		}
		
		cout<<"\nModificar \"Diagnostico\"?\n";
		cout<<"(1): Si\n";
		cout<<"(2): No\n\n";
	
		cout<<"Opcion: ";
		
		do{
		
			cin>>op;
			
		}while(op<1 || op>2);
		
		if(op == 1){
			
			cin.ignore();
			cout<<"\n**Diagnostico - "<<p->NombreCompleto<<" (Actualizacion): ";
			getline(cin,p->DiagnosticoGeneral);
			
		}
		
		
		
	}
	
}

void mostrarHistorial(TpHistorial historial, TpConsulta consultas, TpPruebas pruebas, string dni){
	
	TpHistorial p = historial;
	bool encontrado1 = false;
	bool encontrado2 = false;
	int i=0;
	
	while(p!=NULL && encontrado1 == false){
		
		if(dni==p->DNI){
			
			cout<< "\n Nombre del paciente: "<< p->NombreCompleto;
			cout<< "\n Enfermedad: "<<p->Enfermedad;
			cout<< "\n Alergias: "<<p->Alergias;
			cout<< "\n Diagnostico: "<<p->DiagnosticoGeneral;
			cout<< "\n\n-----------------------------------------------------------------------------------\n";
			
			encontrado1 = true;
			
			cout<<"\n\t--- Fichas de consulta del paciente "<<p->NombreCompleto<<" ---\n";
			
			while(consultas != NULL){
				
				encontrado2 = false;
					
				if(dni == consultas->DNIpaciente){
						
					encontrado2 = true;
					
					i++;
					
					cout<<"\n>>Consulta "<<i;
					cout<<"\n =**Fecha de la consulta: "<<consultas->dia<<"/"<<consultas->mes<<"/"<<consultas->anio;
					cout<<"\n =**Motivo: "<<consultas->Motivo;
					cout<<"\n =**Antecedentes: "<<consultas->Antecedente;
					cout<<"\n =**Desarrollo: "<<consultas->Desarrollo;
	
				}	
								
				cout<<"\n";				
				consultas = consultas->sgte;
					
			}
				
			if(encontrado2 == false) cout<<"\n ==> No se ha registrado la realizacion de alguna consulta de "<<p->NombreCompleto<<"\n";

			cout<<endl;			
			
			modificarHistorial(p);
			ofstream HistorialTXT("HistorialMod.txt",ios::app);
			copiarTXTHistorial(historial, HistorialTXT);
			HistorialTXT.close();
			remove("Historial.txt");
			rename("HistorialMod.txt","Historial.txt");	
			
		}	
		
		p = p->sgte;
		
	}	
	
	if(encontrado1 == false) cout<< "No se encontro un paciente con ese DNI.\n";
		
}

void presentarHistorial(TpHistorial historial, TpConsulta consultas, TpPruebas pruebas){
	
	int op;
	string dni;
				

	cout<<"Ingrese el DNI del paciente: ";
	cin>>dni;
				
	mostrarHistorial(historial,consultas,pruebas,dni);
		
}

void generarPrescripcion(string diagnostico, string medicamentos, string dni, string nombre, string enfermedad) {
    ofstream archivoPrescripcion("Prescripcion.txt", ios::app);  // Abre el archivo en modo de apendizado

    if (archivoPrescripcion.is_open()) {
        // Agrega una línea de espacio entre prescripciones
        archivoPrescripcion << endl;

        // Escribe los datos del paciente y la prescripción en el archivo
        archivoPrescripcion << "DNI del paciente: " << dni << endl;
        archivoPrescripcion << "Nombre del paciente: " << nombre << endl;
        archivoPrescripcion << "Enfermedad: " << enfermedad << endl;
        archivoPrescripcion << "Diagnóstico: " << diagnostico << endl;
        archivoPrescripcion << "Prescripción médica: " << medicamentos << endl;

        // Cierra el archivo
        archivoPrescripcion.close();
        cout << "Prescripcion generada e impresa correctamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo de prescripción." << endl;
    }
}


//************************************************** PACIENTE ******************************
TpPaciente registroPaciente(TpPaciente &paciente){
	TpPaciente nuevo = NULL;
	nuevo = new(struct Paciente);
	do{
		cout<<"Ingrese el dni:"<<endl;
		cin>>nuevo->dni;
		if(buscarDNI(paciente, nuevo->dni))
			cout<<"Este DNI ya esta registrado. Pruebe con otro ... \n";
	}while(buscarDNI(paciente, nuevo->dni));
	
	cout<<"Ingrese los nombres:"<<endl;
	cin.ignore();
	getline(cin,nuevo->nombres);
	cout<<"Ingrese los apellidos:"<<endl;
	getline(cin,nuevo->apellidos);
	cout<<"Ingrese el numero de telefono:"<<endl;
	cin>>nuevo->celular;
	nuevo->sgte = NULL;
	cout<<"El paciente ha sido registrado correctamente."<<endl;
	return nuevo;
}

void insertarPaciente(TpPaciente &paciente, TpPaciente &nuevo, bool existe){
	if(existe==false){
		nuevo = registroPaciente(paciente);
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
	string seguro;
	cout<<"DNI - NOMBRES - APELLIDOS - CELULAR"<<endl;
	while(p != NULL){
		cout<< " "<<i+1<<") "<<p->dni<<" - "<<p->nombres<<" - "<<p->apellidos<<" - "<<p->celular<< endl;
		p=p->sgte;
		i++;	
	}
}

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
	ifstream PacienteTXT("Pacientes.txt",ios::in);
	string d, n, a, c, e, s;
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

void citasPaciente(TpCita citas, string dni){
	bool encontrado=false;
	while(citas!=NULL){
		if(dni==citas->dniPaciente){
			cout<< "\nID del medico encargado: "<<citas->idMedico;
			cout<< "\nDNI del paciente: "<< citas->dniPaciente;
			cout<< "\nFecha de la cita: "<<citas->dia<<"/"<<citas->mes<<"/"<<citas->anio;
			cout<< "\nHora de la cita: "<<citas->hora<<":"<<citas->min;
			cout<< "\n\n------------------------------------------------------\n";
			encontrado=true;
		}	
		citas=citas->sgte;
	}
	if(!encontrado)
		cout<< "No se encontraron citas para ese paciente.\n";
	system("PAUSE");
}

void menuPaciente(TpPaciente &paciente, TpHistorial &historial, TpConsulta consultas, TpPruebas pruebas, TpCita citas){
	
	int opc;
	
	do{
		system("cls");
		cout<< "\n\t1. Registrar Paciente\n";
		cout<< "\t2. Ver y modificar historial medico\n";
		cout<< "\t3. Mostrar citas de un paciente en especifico\n";
		cout<< "\t4. Regresar\n";
		cin>> opc;
		
		system("CLS");
		
		switch(opc){
			case 1:{
				
				TpPaciente nuevo = NULL;
				ofstream PacienteTXT("Pacientes.txt",ios::app);
				insertarPaciente(paciente, nuevo, false);
				insertarTXTPaciente(paciente, PacienteTXT);
				PacienteTXT.close();
				
				ofstream HistorialTXT("Historial.txt",ios::app);
				insertarHistorial(historial,nuevo,false);
				insertarTXTHistorial(historial,HistorialTXT);
				HistorialTXT.close();	
					
				cout<<"\n\n\n\n";
				verListaPaciente(paciente);
				break;
			}
			case 2:{
				
				presentarHistorial(historial, consultas, pruebas);	
				break;
			}
			case 3:{
				string dni;
				cout<< "Insertar el DNI del paciente: ";
				cin>> dni;
				citasPaciente(citas, dni);
				break;
			}
		}
		
		cout<<"\n";
		
		system("pause");
		
	} while(opc!=4);
}

// **************************** PERSONAL ***************************

TpPersonal registroPersonal(TpPersonal &personal){
	TpPersonal nuevo = NULL;
	nuevo = new(struct Personal);
	do{
		cout<<"Ingrese el id:"<<endl;
		cin>>nuevo->id;
		if(buscarID(personal, nuevo->id))
			cout<<"Este ID ya esta registrado. Pruebe con otro...\n";
	}while(buscarID(personal, nuevo->id));
	cout<<"Ingrese los nombres:"<<endl;
	cin.ignore();
	getline(cin,nuevo->nombre);
	cout<<"Ingrese los apellidos:"<<endl;
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
	}
}

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
		nuevo = registroPersonal(personal);
		if(personal == NULL){
			nuevo->ant = nuevo;
			nuevo->sgte = nuevo;
			personal = nuevo;
		}
		else{
			cout<<"Ingrese la posicion del horario del medico"<<endl;
			cin>>pos;
			if(pos==1){
				if(existeUnPersonal(personal)){
					nuevo->sgte = personal;
					nuevo->ant = personal;
					personal->sgte = nuevo;
					personal->ant = nuevo;
					personal = nuevo;
				}
				else{
					personal->ant->sgte = nuevo;
					nuevo->sgte = personal;
					nuevo->ant = personal->ant;
					personal->ant = nuevo;
					personal=nuevo;	
				}
			}
			else{
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
				}
				else{
					cout<<"La longitud de la lista es menor a la posicion buscada."<<endl;
				}
				
			}
		}
	}
	else{
		if(personal == NULL){
			nuevo->ant = nuevo;
			nuevo->sgte = nuevo;
			personal = nuevo;
		}
		else{
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

void eliminarTXTPersonal(TpPersonal &personal, ifstream &PersonalTXT, ofstream &Salida, int pos){
	string id, nombre, apellidos, salario, especialidad;
	cin.ignore();
	getline(PersonalTXT, id); int x=1;
	while(!PersonalTXT.eof()){
		getline(PersonalTXT, nombre);
		getline(PersonalTXT, apellidos);
		getline(PersonalTXT, salario);
		getline(PersonalTXT, especialidad);
		if(x==pos){
			x++;
			if(personal == NULL)
				break;
		}else{
			Salida<<id<<endl;
			Salida<<nombre<<endl;
			Salida<<apellidos<<endl;
			Salida<<salario<<endl;
			Salida<<especialidad<<endl;
			x++;
		}
		getline(PersonalTXT, id);
	}
}

void eliminarPersonal(TpPersonal &personal){
	TpPersonal p = personal;
	int x=1, pos; bool flag = false;
	if(personal == NULL){
		cout<<"No hay personal registrado...\n";
	}else{
		verListaPersonal(personal);
		cout<<"Inserte la posición del personal a eliminar ---> ";cin>>pos;
		if(pos==1){
			if(personal->sgte == personal){
				personal = NULL;
				delete(p);
			}else{
				personal->ant->sgte = personal->sgte;
				personal->sgte->ant = personal->ant;
				personal = personal->sgte;
				delete(p);
			}
		}else{
			while(p->sgte != personal && x != pos){
				p=p->sgte;
				x++;
				if(x==pos)
				flag=true;
			}	
			if(flag==true){
				p->ant->sgte = p->sgte;
				p->sgte->ant = p->ant;
				delete(p);
			}
			else{
				cout<<"ERROR: Posicion No Existe en la Lista"<<endl;
				system("pause");
			}
		}
		ifstream PersonalTXT("Personal.txt",ios::in);
		ofstream Salida("PersonalMod.txt",ios::app);
		eliminarTXTPersonal(personal, PersonalTXT, Salida, pos);
		PersonalTXT.close();
		Salida.close();
		remove("Personal.txt");
		rename("PersonalMod.txt","Personal.txt");
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
	ifstream PersonalTXT("Personal.txt",ios::in);
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
		istringstream(s)>>nuevo->salario;
		nuevo->especialidad = e;
		nuevo->sgte=NULL;
		insertarPersonal(personal, nuevo, true);
		getline(PersonalTXT,i);
	}
}

//*********************************************  CITAS  ****************************************





int buscarOcupado(TpCita citas, string idMedico, int dia, int mes, int anio, int hora, int min){
	int minutos=0, dif=0, result=0;
	while(citas!=NULL){
		if(citas->idMedico==idMedico){
			if(citas->dia==dia&& citas->mes==mes&& citas->anio==anio){
				hora*=60;
				min+=hora;
				minutos=minutos+citas->hora*60;
				minutos+=citas->min;
				dif= min-minutos;
				if(dif<30 && dif>-30)
					result++;
			}
		}
		citas=citas->sgte;
	}
	return result;
}

TpCita crearCita(TpCita citas, TpPersonal &personal, TpPaciente &paciente){
	string dniPaciente, idMedico;
	int dia, mes, anio, hora, min, aux;
	bool idEncontrado= false, dniEncontrado=false, desocupado= true;
	TpCita nuevo=NULL;
	nuevo= new struct Cita;
	do{
		cout<< "Ingrese el DNI del paciente: ";
		cin >> dniPaciente;
		cout<< "Ingrese el ID del personal a cargo de la cita: ";
		cin >> idMedico;
		idEncontrado= buscarID(personal, idMedico);
		dniEncontrado= buscarDNI(paciente, dniPaciente);
		if(!idEncontrado)
			cout<<"No se ha encontrado el medico registrado.\n";
		if(!dniEncontrado)
			cout<<"No se ha encontrado el paciente registrado.\n";
	}while(!idEncontrado || !dniEncontrado);
	do{
		do{
			cout<< "Ingrese la fecha de la cita (dd/mm/yyyy): ";
			cin >> dia;
			cin >> mes;
			cin >> anio;
			if(dia>31 ||dia<1 ||mes<1 ||mes>12 ||anio<2023)
				cout<<"Fecha invalida, ingrese los datos otra vez.\n";
		} while(dia>31 ||dia<1 ||mes<1 ||mes>12 ||anio<2023);
		do{
			cout<< "Insertar la hora destinada a la cita en formato 24hrs. (hh-mm): ";
			cin >> hora;
			cin >> min;
			if(hora<1|| hora>24 || min<0 ||min>59)
				cout<<"Hora invalida, ingrese los datos otra vez.\n";
		} while(hora<1|| hora>24 || min<0 ||min>59);
		aux= buscarOcupado(citas, idMedico, dia, mes, anio, hora, min);
		if(aux==1){
			cout<< "Fecha ya ocupada por otra cita, por favor, reprograme\n";
			desocupado=false;
		}
		else
			desocupado=true;
		aux=0;
	} while(!desocupado);
	nuevo->idMedico= idMedico;
	nuevo->dniPaciente= dniPaciente;
	nuevo->dia= dia;
	nuevo->mes= mes;
	nuevo->anio= anio;
	nuevo->hora= hora;
	nuevo->min= min;
	nuevo->sgte= NULL;
	return nuevo;
}

void agendarCita(TpPersonal &personal, TpPaciente &paciente, TpCita &citas, TpCita nuevo, bool existe){
	if(existe==false){
		nuevo = crearCita(citas, personal, paciente);
	}
	TpCita p=citas;
	
	if(citas==NULL){
		citas = nuevo;
	}else{
		while(p->sgte != NULL)
			p=p->sgte;
		p->sgte = nuevo;
	}
}

void agendarTXTCita(TpCita &citas, ofstream &CitasTXT){
	TpCita p = citas;
	if(citas!=NULL){
		while(p->sgte != NULL){
			p=p->sgte;	
		}
	}
	CitasTXT<<p->idMedico<<endl;
	CitasTXT<<p->dniPaciente<<endl;
	CitasTXT<<p->dia<<endl;
	CitasTXT<<p->mes<<endl;
	CitasTXT<<p->anio<<endl;
	CitasTXT<<p->hora<<endl;
	CitasTXT<<p->min<<endl;
}

void copiarTXTCita(TpCita &citas, ofstream &CitasTXT){
	TpCita p = citas;
	while(p!=NULL){
		
		CitasTXT<<p->idMedico<<endl;
		CitasTXT<<p->dniPaciente<<endl;
		CitasTXT<<p->dia<<endl;
		CitasTXT<<p->mes<<endl;
		CitasTXT<<p->anio<<endl;
		CitasTXT<<p->hora<<endl;
		CitasTXT<<p->min<<endl;
		p=p->sgte;
	}
}

void recuperarTXTCitas(TpPersonal &personal, TpPaciente &paciente, TpCita &citas){
	ifstream CitasTXT("Citas.txt",ios::in);
	string idMedico, dniPaciente, dia, mes, anio, hora, min;
	getline(CitasTXT,idMedico);
	while(!CitasTXT.eof()){
		getline(CitasTXT,dniPaciente);
		getline(CitasTXT,dia);
		getline(CitasTXT,mes);
		getline(CitasTXT,anio);
		getline(CitasTXT,hora);
		getline(CitasTXT,min);
		TpCita nuevo = NULL;
		nuevo = new(struct Cita);
		nuevo->idMedico = idMedico;
		nuevo->dniPaciente = dniPaciente;
		istringstream(dia)>>nuevo->dia;
		istringstream(mes)>>nuevo->mes;
		istringstream(anio)>>nuevo->anio;
		istringstream(hora)>>nuevo->hora;
		istringstream(min)>>nuevo->min;
		nuevo->sgte=NULL;
		agendarCita(personal, paciente, citas, nuevo, true);
		getline(CitasTXT,idMedico);
	}
}

void mostrarCitas(TpCita citas){
	while(citas!=NULL){
		cout<< "\nID del medico encargado: "<<citas->idMedico;
		cout<< "\nDNI del paciente: "<< citas->dniPaciente;
		cout<< "\nFecha de la cita: "<<citas->dia<<"/"<<citas->mes<<"/"<<citas->anio;
		cout<< "\nHora de la cita: "<<citas->hora<<":"<<citas->min;
		cout<< "\n\n------------------------------------------------------\n";
		citas=citas->sgte;
	}
}

void eliminarCita(TpCita &citas, string idBusqueda, string dniBusqueda, int dia, int mes, int anio, int hora, int min){
	TpCita p= citas, t=NULL;
	
	if(p==NULL){
		
		cout<<"No hay citas guardadas\n";
		return;
		
	}
	
	if(p->idMedico==idBusqueda &&  p->dniPaciente==dniBusqueda && p->dia==dia &&p->mes==mes &&p->anio==anio && p->hora == hora && p->min == min){
		t=p;
		citas=citas->sgte;
		delete(t);
		return;
	}
	while(p!=NULL){
		t=p;
		p=p->sgte;
		if(p->idMedico==idBusqueda &&  p->dniPaciente==dniBusqueda && p->dia==dia &&p->mes==mes && p->anio==anio && p->hora == hora && p->min == min){
			t->sgte=p->sgte;
			delete(p);
			return;
		}
	}
	if (p == NULL) {
        cout << "La cita ingresada no existe." <<endl;
        return;
    }
	
}

void buscarCita(TpCita &citas, string idBusqueda, string dniBusqueda, int dia, int mes, int anio, int hora, int min){
	TpCita p= citas;
	int diaN, mesN, anioN, minN, horaN, aux;
	bool desocupado= true;
	while(p!=NULL){
		if(p->idMedico==idBusqueda &&  p->dniPaciente==dniBusqueda && p->dia==dia &&p->mes==mes &&p->anio==anio && p->hora==hora &&p->min==min){
			do{
				do{
					cout<< "Ingrese la nueva fecha de la cita (dd/mm/yyyy): ";
					cin>> diaN;
					cin>> mesN;
					cin>> anioN;
					if(diaN>31 ||diaN<1 ||mesN<1 ||mesN>12 ||anioN<2023)
						cout<<"Fecha invalida, ingrese los datos otra vez.\n";
				} while(diaN>31 ||diaN<1 ||mesN<1 ||mesN>12 ||anioN<2023);
				
				do{
					cout<< "Insertar la nueva hora de la cita en formato 24hrs. (hh-mm): ";
					cin >> horaN;
					cin >> minN;
					if(horaN<1|| horaN>24 || minN<0 ||minN>59)
						cout<<"Hora invalida, ingrese los datos otra vez.\n";
				} while(horaN<1|| horaN>24 || minN<0 ||minN>59);
				aux= buscarOcupado(citas, idBusqueda, diaN, mesN, anioN, horaN, minN);
				if(aux>=1){
					if(hora!=horaN){
						cout<< "Fecha ya ocupada por otra cita, por favor, reprograme\n";
						desocupado=false;
					}
					else if(aux==2){
						cout<< "Fecha ya ocupada por otra cita, por favor, reprograme\n";
						desocupado=false;
					}
				}
				else
					desocupado=true;
				aux=0;
			} while(!desocupado);
			p->dia= diaN;
			p->mes= mesN;
			p->anio= anioN;
			p->hora= horaN;
			p->min= minN;
			return;
		}
		p=p->sgte;
	}
	cout << "La cita ingresada no existe." <<endl;
    return;
}

//*********************************************  MEDICAMENTO  ****************************************

void verListaMedicamento(TpMedicamento lista){
	int i=0; TpMedicamento p = lista;
	cout<<"ID - PRECIO - UNIDADES \t - CONTRAINDICACIONES"<<endl;
	while(p != NULL){
		cout<< " "<<i+1<<") "<<p->id<<" - "<<p->precio<<" - "<<p->unidades<<" -\t "<<p->contraindicaciones<< endl;
		p=p->sgte;
		i++;	
	}
}

bool buscarIDMedicamento(TpMedicamento medicamento, string id){
	if(medicamento == NULL){
		return false;
	}
	do{
		if(medicamento->id == id)
			return true;
		medicamento = medicamento->sgte;
	}while(medicamento->sgte != NULL);
	return false;
}

TpMedicamento registroMedicamento(TpMedicamento &medicamento){
	TpMedicamento nuevo = NULL;
	nuevo = new(struct Medicamento);
	do{
		cout<<"Ingrese el id:"<<endl;
		cin>>nuevo->id;
		if(buscarIDMedicamento(medicamento, nuevo->id))
			cout<<"El medicamento esta registrado. Intente otra ID...\n\n";
	}while(buscarIDMedicamento(medicamento, nuevo->id));
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
		nuevo = registroMedicamento(medicamento);
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

void modificarTXTMedicamento(TpMedicamento &medicamento, ofstream &Salida){
	TpMedicamento p=medicamento;
	while(p->sgte != NULL){
		Salida<<p->id<<endl;
		Salida<<p->precio<<endl;
		Salida<<p->unidades<<endl;
		Salida<<p->contraindicaciones<<endl;
		p=p->sgte;
	}
	Salida<<p->id<<endl;
	Salida<<p->precio<<endl;
	Salida<<p->unidades<<endl;
	Salida<<p->contraindicaciones<<endl;
}

void modificarMedicamento(TpMedicamento &medicamento){
	TpMedicamento p = medicamento;
	int x=1, pos, opc; bool flag = false;
	verListaMedicamento(medicamento);
	cout<<"Inserte la posición del personal a eliminar ---> ";cin>>pos;
	if(pos==1){
		if(medicamento ==NULL){
			cout<<"\n No hay medicamentos registrados... "<<endl;
			system("pause");
			return;
		}else{
			do{
				system("CLS");
				cout<<"Seleccione que caracteristica desea cambiar:\n";
				cout<<"1. Precio\n";
				cout<<"2. Unidades\n";
				cout<<"3. Contraindicaciones\n";
				cout<<"4. Salir\n";
				cin>>opc;
				switch(opc){
					case 1:{
						cout<<"Ingrese el nuevo precio:\n";
						cin>>medicamento->precio;
						break;
					}
					case 2:{
						cout<<"Ingrese la nueva cantidad de unidades:\n";
						cin>>medicamento->unidades;
						break;
					}
					case 3:{
						cout<<"Ingrese las nuevas contraindicaciones:\n";
						cin.ignore();
						getline(cin,medicamento->contraindicaciones);
						break;
					}
					case 4:{
						break;
					}
				}
			}while(opc != 4);
		}
	}else{
		

	while(p->sgte != NULL && x != pos){
		p=p->sgte;
		x++;
		if(x==pos)
			flag=true;
	}	
	if(flag==true){
		do{
			system("CLS");
			cout<<"Seleccione que caracteristica desea cambiar:\n";
			cout<<"1. Precio\n";
			cout<<"2. Unidades\n";
			cout<<"3. Contraindicaciones\n";
			cout<<"4. Salir\n";
			cin>>opc;
			switch(opc){
				case 1:{
					cout<<"Ingrese el nuevo precio:\n";
					cin>>p->precio;
					break;
				}
				case 2:{
					cout<<"Ingrese la nueva cantidad de unidades:\n";
					cin>>p->unidades;
					break;
				}
				case 3:{
					cout<<"Ingrese las nuevas contraindicaciones:\n";
					cin.ignore();
					getline(cin,p->contraindicaciones);
					break;
				}
				case 4:{
					break;
				}	
			}
		}while(opc != 4);
	}
	else{
		cout<<"ERROR: Posicion No Existe en la Lista"<<endl;
		system("pause");
		return;
	}}
	ofstream Salida("MedicamentoMod.txt",ios::app);
	modificarTXTMedicamento(medicamento, Salida);
	Salida.close();
	remove("Medicamentos.txt");
	rename("MedicamentoMod.txt","Medicamentos.txt");
}

void eliminarTXTMedicamento(TpMedicamento &medicamento, ifstream &MedicamentoTXT, ofstream &Salida, int pos){
	string id, precio, unidades, contraindicaciones;
	cin.ignore();
	getline(MedicamentoTXT, id); int x=1;
	while(!MedicamentoTXT.eof()){
		getline(MedicamentoTXT, precio);
		getline(MedicamentoTXT, unidades);
		getline(MedicamentoTXT, contraindicaciones);
		if(x==pos){
			x++;
			if(medicamento == NULL)
				break;
		}else{
			Salida<<id<<endl;
			Salida<<precio<<endl;
			Salida<<unidades<<endl;
			Salida<<contraindicaciones<<endl;
			x++;
		}
		getline(MedicamentoTXT, id);
	}
}

void eliminarMedicamento(TpMedicamento &medicamento){
	TpMedicamento p=medicamento, t=NULL;
	int x=1, pos;
	bool flag=false;
	if(medicamento == NULL){
		cout<<"\n No hay medicamentos registrados...\n";
	}else{
		verListaMedicamento(medicamento);
		cout<<"Inserte la posición del personal a eliminar ---> ";cin>>pos;
		if(pos==1){
			t = medicamento;
			if(medicamento->sgte == NULL){
				medicamento = NULL;
			}else{
				medicamento=medicamento->sgte;
			}
			delete(t);
		}else{
			while(p->sgte != NULL && x != pos){
				t=p;
				p=p->sgte;
				x++;
				if(x==pos)
					flag=true;
			}	
			if(flag==true){
				t->sgte= p->sgte;
				delete(p);
				system("pause");
			}
			else{
				cout<<"ERROR: Posicion No Existe en la Lista"<<endl;
				system("pause");
				return;
			}
		}
		ifstream MedicamentoTXT("Medicamentos.txt",ios::in);
		ofstream Salida("MedicamentosMod.txt",ios::app);
		eliminarTXTMedicamento(medicamento, MedicamentoTXT, Salida, pos);
		MedicamentoTXT.close();
		Salida.close();
		remove("Medicamentos.txt");
		rename("MedicamentosMod.txt","Medicamentos.txt");
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
	ifstream MedicamentoTXT("Medicamentos.txt",ios::in);
	string i, p, u, c;
	getline(MedicamentoTXT,i);
	while(!MedicamentoTXT.eof()){
		getline(MedicamentoTXT,p);
		getline(MedicamentoTXT,u);
		getline(MedicamentoTXT,c);
		TpMedicamento nuevo = NULL;
		nuevo = new(struct Medicamento);
		nuevo->id = i;
		istringstream(p)>>nuevo->precio;
		istringstream(u)>>nuevo->unidades;
		nuevo->contraindicaciones = c;
		nuevo->sgte=NULL;
		insertarMedicamento(medicamento, nuevo, true);
		getline(MedicamentoTXT,i);
	}
}



//*************************************************ConsultasHistorial******************************************

TpConsulta crearConsulta(TpCita citas, string DNI){
	
	
	
	int op;
	string motivo, antecedentes, desarrollo;
	
	TpConsulta nuevo = NULL;
	nuevo = new (struct ConsultasHistorial);

	nuevo->DNIpaciente = DNI;
	nuevo->dia = citas->dia;
	nuevo->mes = citas->mes;
	nuevo->anio = citas->anio;

	cout<<"\nIngrese el Motivo de la cita: ";
	
	cin.ignore();
	getline(cin,motivo);
	
	cout<<"\n";
	
	cout<<"\nIngrese los Antedecedentes: ";
	getline(cin,antecedentes);
	
	cout<<"\n";
	
	cout<<"\nIngrese el Desarrollo de la cita: ";
	getline(cin,desarrollo);
	
	nuevo->Motivo = motivo;
	nuevo->Antecedente = antecedentes;
	nuevo->Desarrollo = desarrollo;
	
	cout<<"\n";
	
	nuevo->sgte= NULL;
	return nuevo;
	
}

void encolarConsulta(TpConsulta &consultas, TpConsulta nuevo){
	
	TpConsulta p = consultas;
	
	if(consultas == NULL) consultas = nuevo;

	else{
		
		while(p->sgte != NULL) p=p->sgte;
		
		p->sgte = nuevo;
		
	}
	
}

void insertarTXTConsultas(TpConsulta &consultas, ofstream &ConsultaTXT){
	
	TpConsulta p = consultas;
	
	if(consultas!=NULL){
		while(p->sgte != NULL){
			p=p->sgte;	
		}
	}

	ConsultaTXT<<p->DNIpaciente <<endl;
	ConsultaTXT<<p->dia<<endl;
	ConsultaTXT<<p->mes<<endl;
	ConsultaTXT<<p->anio<<endl;
	ConsultaTXT<<p->Motivo<<endl;
	ConsultaTXT<<p->Antecedente<<endl;
	ConsultaTXT<<p->Desarrollo<<endl;

}

void insertarConsulta(TpConsulta &consultas, TpCita &citas){
	
	TpConsulta nuevo = NULL;
	TpCita p = citas;
	
	string dni, id;
	int dia, mes,anio, hora, min;
				
	cout<<"Ingrese el DNI del paciente: ";
    cin>>dni;			
				
	cout<<"Ingrese el ID del medico: "	;
	cin>>id;	
				
	cout<<"Ingrese el dia de la cita (dd/mm/aa): ";
	cin>>dia;
	cin>>mes;
	cin>>anio;
	
	cout<<"Ingrese la hora de la cita (hh:mm): ";
	cin>>hora;
	cin>>min;
	
	while(p != NULL){
			
			
		if(p->dniPaciente == dni && p->idMedico == id && p->dia == dia && p->mes == mes && p->anio == anio && p->hora == hora && p->min == min){
					
			nuevo = crearConsulta(p,dni);
			
			encolarConsulta (consultas, nuevo);
			
			ofstream ConsultaTXT("ConsultasH.txt",ios::app);

			insertarTXTConsultas(consultas, ConsultaTXT);
			ConsultaTXT.close();
			
			
			eliminarCita(citas,id,dni,dia,mes,anio,hora,min);
		
			ofstream CitasTXT("CitasMod.txt",ios::app);
			copiarTXTCita(citas, CitasTXT);
			CitasTXT.close();
			remove("Citas.txt");
			rename("CitasMod.txt","Citas.txt");	
				
			return;
				
		}
			
			
		p = p->sgte;
			
	}

}



void recuperarTXTConsulta(TpConsulta &consultas){
	
	ifstream ConsultaTXT("ConsultasH.txt",ios::in);
	
	string DNI, motivo, antecedente, desarrollo, dia, mes, anio;
	
	getline(ConsultaTXT,DNI);
	
	while(!ConsultaTXT.eof()){
		
		getline(ConsultaTXT,dia);
		getline(ConsultaTXT,mes);
		getline(ConsultaTXT,anio);
		getline(ConsultaTXT,motivo);
		getline(ConsultaTXT,antecedente);
		getline(ConsultaTXT,desarrollo);
		
		TpConsulta nuevo = NULL;
		nuevo = new(struct ConsultasHistorial);
		
		nuevo->DNIpaciente = DNI;
		nuevo->Motivo = motivo;
		nuevo->Antecedente = antecedente;
		nuevo->Desarrollo = desarrollo;
		
		istringstream(dia)>>nuevo->dia;
		istringstream(mes)>>nuevo->mes;
		istringstream(anio)>>nuevo->anio;
		
		nuevo->sgte=NULL;
		
		encolarConsulta(consultas, nuevo);
		getline(ConsultaTXT,DNI);
			
	}
	
}

void menuMedico(TpPersonal &personal, TpPaciente &paciente, TpMedicamento &medicamento, TpCita &citas, TpHistorial historial, TpConsulta &consultas){
	int opc;
	
	do{
		system("CLS");
		cout<< "1. Registrar Personal\n";
		cout<< "2. Eliminar Personal\n";
		cout<< "3. Registrar Medicinas\n";
		cout<< "4. Modificar Medicinas\n";
		cout<< "5. Eliminar Medicinas\n";
		cout<< "6. Crear citas\n";
		cout<< "7. Mostrar citas totales\n";
		cout<< "8. Editar citas\n";
		cout<< "9. Eliminar cita\n";
		cout<< "10. Generar prescripcion\n";
		cout<< "11. Documentar cita\n";		
		cout<< "12. Regresar\n";
		cin>> opc;
		switch(opc){
			case 1:{
				system("CLS");
				TpPersonal nuevo = NULL;
				ofstream PersonalTXT("modificacion.txt",ios::app);
				insertarPersonal(personal, nuevo, false);
				insertarTXTPersonal(personal, PersonalTXT);
				PersonalTXT.close();
				remove("Personal.txt");
				rename("modificacion.txt","Personal.txt");
				cout<<"\n\n\n\n";
				verListaPersonal(personal);
				break;
			}
			case 2:{
				eliminarPersonal(personal);
				cout<<"\n\n\n\n";
				verListaPersonal(personal);
				break;
			}
			case 3:{
				system("CLS");
				ofstream MedicamentoTXT("Medicamentos.txt",ios::app);
				TpMedicamento nuevo = NULL;
				insertarMedicamento(medicamento, nuevo, false);
				insertarTXTMedicamento(medicamento, MedicamentoTXT);
				MedicamentoTXT.close();
				cout<<"\n\n\n\n";
				verListaMedicamento(medicamento);
				break;
			}
			case 4:{
				system("CLS");
				modificarMedicamento(medicamento);
				break;
			}
			case 5:{
				system("CLS");
				eliminarMedicamento(medicamento);
				break;
			}
			case 6:{
				system("CLS");
				ofstream CitasTXT("Citas.txt",ios::app);
				TpCita nuevo = NULL;
				agendarCita(personal, paciente, citas, nuevo, false);
				agendarTXTCita(citas, CitasTXT);
				CitasTXT.close();
				cout<<"\n\n\n\n";
				break;
			}
			case 7:{
				mostrarCitas(citas);
				break;
			}
			case 8:{
				string idBusqueda;
				string dniBusqueda;
				int dia;
				int mes;
				int anio;
				int hora;
				int min;
				mostrarCitas(citas);
				cout<< "Ingrese el id del medico encargado de la consulta: ";
				cin>> idBusqueda;
				cout<< "Ingrese el DNI del paciente: ";
				cin>> dniBusqueda;
				do{
					cout<< "Ingrese el dia de la cita: ";
					cin>> dia;
					cin>> mes;
					cin>> anio;	
					if(dia<1||dia>31||mes<1||mes>12||anio<2023)
						cout<< "Fecha invalida, ingrese una correcta.";
				} while(dia<1||dia>31||mes<1||mes>12||anio<2023);
				do{
					cout<< "Insertar la hora de la cita en formato 24hrs. (hh-mm): ";
					cin >> hora;
					cin >> min;
					if(hora<1|| hora>24 || min<0 ||min>59)
						cout<<"Hora invalida, ingrese los datos otra vez.\n";
				} while(hora<1|| hora>24 || min<0 ||min>59);
				buscarCita(citas, idBusqueda, dniBusqueda, dia, mes, anio, hora, min);
				ofstream CitasTXT("CitasMod.txt",ios::app);
				copiarTXTCita(citas, CitasTXT);
				CitasTXT.close();
				remove("Citas.txt");
				rename("CitasMod.txt","Citas.txt");
				break;
			}
			case 9:{
				string idBusqueda;
				string dniBusqueda;
				int dia;
				int mes;
				int anio;
				int hora;
				int min;
				
				mostrarCitas(citas);
				cout<< "Ingrese el id del medico encargado de la consulta: ";
				cin>> idBusqueda;
				cout<< "Ingrese el DNI del paciente: ";
				cin>> dniBusqueda;
				cout<< "Ingrese el dia de la cita: ";
				cin>> dia;
				cin>> mes;
				cin>> anio;
				cout<<"Ingrese la hora de la cita: ";
				cin>>hora;
				cin>>min;
				
				eliminarCita(citas, idBusqueda, dniBusqueda, dia, mes, anio, hora, min);
				ofstream CitasTXT("CitasMod.txt",ios::app);
				copiarTXTCita(citas, CitasTXT);
				CitasTXT.close();
				remove("Citas.txt");
				rename("CitasMod.txt","Citas.txt");
				break;
			}
			case 10:{
				string dni;
                cout << "Ingrese el DNI del paciente: ";
                cin >> dni;

                TpHistorial p = historial;
                bool encontrado = false;

                while (p != NULL) {
                    if (dni == p->DNI) {
                        cout << "\nPrescripcion del paciente\n";
                        cout << "DNI del paciente: " << p->DNI << endl;
                        cout << "Nombre del paciente: " << p->NombreCompleto << endl;
                        cout << "Enfermedad: " << p->Enfermedad << endl;
                        cout << "Alergias: " << p->Alergias << endl;
                        cout << "Diagnostico general: " << p->DiagnosticoGeneral << endl;

                        // Generar y guardar la prescripción en un archivo
                        string prescripcion;
                        cout << "Ingrese la prescripcion medica: ";
                        cin.ignore();
                        getline(cin, prescripcion);
                        generarPrescripcion(p->DiagnosticoGeneral, prescripcion, p->DNI, p->NombreCompleto, p->Enfermedad);

                        encontrado = true;
                        break;
                    }
                    p = p->sgte;
                }

                if (!encontrado) {
                    cout << "No se encontro un paciente con ese DNI.\n";
                }
				break;
			}
			
			case 11:{
				insertarConsulta(consultas, citas);
				break;
			}
			
			case 12:{
				break;
			}
			
		}
		system("pause");
	} while(opc!=12);
}

// ******************************************* MAIN ***********************

int main(){
	int opc;
	TpPersonal personal = NULL;
	TpPaciente paciente = NULL;
	TpCita citas=NULL;
	TpMedicamento medicamento = NULL;
	TpHistorial historial = NULL;
	TpConsulta consultas = NULL;
	TpPruebas pruebas = NULL;
	
	recuperarTXTPersonal(personal);
	recuperarTXTPaciente(paciente);
	recuperarTXTCitas(personal, paciente, citas);
	recuperarTXTMedicamento(medicamento);
	recuperarTXTHistorial(historial);
	recuperarTXTConsulta(consultas);
	
	do{
		system("CLS");
		opc=menuPrincipal();
		switch(opc){
			case 1:{
				menuPaciente(paciente, historial,consultas, pruebas, citas);
				break;
			}
			case 2:{
				menuMedico(personal, paciente, medicamento, citas, historial, consultas);
				break;
			}
		}
	} while(opc!=3);
	cout<< "Gracias por usar el sistema de gestion\n";
	
}


