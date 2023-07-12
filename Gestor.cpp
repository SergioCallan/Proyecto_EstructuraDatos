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
	string TipoDePrueba;
	string Resultado;	
	
	struct PruebasHistorial *sgte;
	
};

typedef struct Personal *TpPersonal;
typedef struct Cita *TpCita;
typedef struct Paciente *TpPaciente;
typedef struct Medicamento *TpMedicamento;

//Historial
typedef struct Historial *TpHistorial;
typedef struct ConsultasHistorial *TpConsultas;
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
	
	/*
	cout<<"El paciente posee alguna enfermedad? (1: Si, 0: No): ";
	
	do{
		
		cin>>op;
		
	}while(op<0 || op>1);
	
	cout<<"\n";
	
	if(op == true){
		
		cin.ignore();
		cout<<"Enfermedad: ";
		getline(cin,enfermedad);
	
	}
	
	else{
		
		enfermedad = "Sin enfermedad";
		
	}
	
	cout<<"El paciente posee alguna alergia? (1: Si, 0: No): ";
	
	do{
		
		cin>>op;
		
	}while(op<0 || op>1);
	
	cout<<"\n";
	
	if(op == true){
		
		cin.ignore();
		cout<<"Alergias: ";
		getline(cin,alergias);
	
	}
	
	else{
		
		enfermedad = "Sin alergias";
		
	}
		
	cout<<"Diagnostico General: ";
	getline(cin,diagnostico);
	*/
	
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

void mostrar(TpHistorial historial, string dni){
	
	bool encontrado = false;
	
	while(historial!=NULL){
		
		if(dni==historial->DNI){
			
			cout<< "\nDNI del paciente: "<<dni;
			cout<< "\nNombre del paciente: "<< historial->NombreCompleto;
			cout<< "\nEnfermedad: "<<historial->Enfermedad;
			cout<< "\nAlergias: "<<historial->Alergias;
			cout<< "\nDiagnostico: "<<historial->DiagnosticoGeneral;
			cout<< "\n\n------------------------------------------------------\n";
			encontrado = true;
		}	
		historial=historial->sgte;
	}
	
	if(!encontrado) cout<< "No se encontro un paciente con ese DNI.\n";
		
	system("PAUSE");
	
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

void menuHistorial(TpHistorial &historial){
	
	int op;
	string dni;
				
	do{
		
		system("cls");
		
		cout<<"\t== Historiales Medicos ==\n\n";
	
		cout<<"(1): Ver historial medico de un paciente\n";
		cout<<"(2): Modificar historial medico de un paciente\n";
		cout<<"(3): Regresar\n\n";
		
		cout<<"Opcion: ";	
		
		do{
						
			cin>>op;
						
		}while(op<1 || op>3);
		
		switch(op){
			
			case 1:{
				
				cout<<"Ingrese el DNI del paciente: ";
				cin>>dni;
				
				mostrar(historial,dni);
				
				break;
			}
			
			case 2:{
				
				
				
				break;
			}
			
		}
		
	}while(op != 3);
	
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
	getline(cin,nuevo->apellidos);
	cout<<"Ingrese el numero de telefono:"<<endl;
	cin>>nuevo->celular;
	nuevo->sgte = NULL;
	cout<<"El paciente ha sido registrado correctamente."<<endl;
	return nuevo;
}

void insertarPaciente(TpPaciente &paciente, TpPaciente &nuevo, bool existe){
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

void menuPaciente(TpPaciente &paciente, TpHistorial &historial, TpCita citas){
	int opc;
	
	do{
		system("cls");
		cout<< "\n\t1. Registrar Paciente\n";
		cout<< "\t2. Ver y modificar historial medico\n";
		cout<< "\t3. Mostrar citas de un paciente en especifico\n";
		cout<< "\t4. Regresar\n";
		cin>> opc;
		switch(opc){
			case 1:{
				system("CLS");
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
				menuHistorial(historial);
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

TpPersonal registroPersonal(){
	TpPersonal nuevo = NULL;
	nuevo = new(struct Personal);
	cout<<"Ingrese el id:"<<endl;
	cin>>nuevo->id;
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
		nuevo = registroPersonal();
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

bool buscarID(TpPersonal personal, string idMedico){
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

void eliminarCita(TpCita &citas, string idBusqueda, string dniBusqueda, int dia, int mes, int anio){
	TpCita p= citas, t=NULL;
	if(p->idMedico==idBusqueda &&  p->dniPaciente==dniBusqueda && p->dia==dia &&p->mes==mes &&p->anio==anio){
		t=p;
		citas=citas->sgte;
		delete(t);
		return;
	}
	while(p!=NULL){
		t=p;
		p=p->sgte;
		if(p->idMedico==idBusqueda &&  p->dniPaciente==dniBusqueda && p->dia==dia &&p->mes==mes &&p->anio==anio){
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
					else if(aux==2&&hora==horaN){
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

void verListaMedicamento(TpMedicamento lista){
	int i=0; TpMedicamento p = lista;
	cout<<"ID - PRECIO - UNIDADES \t - CONTRAINDICACIONES"<<endl;
	while(p != NULL){
		cout<< " "<<i+1<<") "<<p->id<<" - "<<p->precio<<" - "<<p->unidades<<" -\t "<<p->contraindicaciones<< endl;
		p=p->sgte;
		i++;	
	}
}

void menuMedico(TpPersonal &personal, TpPaciente &paciente, TpMedicamento &medicamento, TpCita &citas, TpHistorial &historial){
	int opc;
	
	do{
		system("CLS");
		cout<< "1. Registrar Personal\n";
		cout<< "2. Registrar Medicinas\n";
		cout<< "3. Crear citas\n";
		cout<< "4. Mostrar citas totales\n";
		cout<< "5. Editar citas\n";
		cout<< "6. Eliminar cita\n";
		cout<< "7. Generar prescripcion\n";
		cout<< "8. Regresar\n";
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
			case 3:{
				system("CLS");
				ofstream CitasTXT("Citas.txt",ios::app);
				TpCita nuevo = NULL;
				agendarCita(personal, paciente, citas, nuevo, false);
				agendarTXTCita(citas, CitasTXT);
				CitasTXT.close();
				cout<<"\n\n\n\n";
				break;
			}
			case 4:{
				mostrarCitas(citas);
				break;
			}
			case 5:{
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
				ofstream CitasTXT("\CitasMod.txt",ios::app);
				copiarTXTCita(citas, CitasTXT);
				CitasTXT.close();
				remove("\Citas.txt");
				rename("\CitasMod.txt","\Citas.txt");
				break;
			}
			case 6:{
				string idBusqueda;
				string dniBusqueda;
				int dia;
				int mes;
				int anio;
				mostrarCitas(citas);
				cout<< "Ingrese el id del medico encargado de la consulta: ";
				cin>> idBusqueda;
				cout<< "Ingrese el DNI del paciente: ";
				cin>> dniBusqueda;
				cout<< "Ingrese el dia de la cita: ";
				cin>> dia;
				cin>> mes;
				cin>> anio;
				eliminarCita(citas, idBusqueda, dniBusqueda, dia, mes, anio);
				ofstream CitasTXT("CitasMod.txt",ios::app);
				copiarTXTCita(citas, CitasTXT);
				CitasTXT.close();
				remove("Citas.txt");
				rename("CitasMod.txt","Citas.txt");
				break;
			}
			case 7:{
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
		}
		system("pause");
	} while(opc!=8);
}

// ******************************************* MAIN ***********************

int main(){
	int opc;
	TpPersonal personal = NULL;
	TpPaciente paciente = NULL;
	TpCita citas=NULL;
	TpMedicamento medicamento = NULL;
	TpHistorial historial = NULL;
	
	recuperarTXTPersonal(personal);
	recuperarTXTPaciente(paciente);
	recuperarTXTCitas(personal, paciente, citas);
	recuperarTXTMedicamento(medicamento);
	recuperarTXTHistorial(historial);
	
	do{
		system("CLS");
		opc=menuPrincipal();
		switch(opc){
			case 1:{
				menuPaciente(paciente, historial, citas);
				break;
			}
			case 2:{
				menuMedico(personal, paciente, medicamento, citas, historial);
				break;
			}
		}
	} while(opc!=3);
	cout<< "Gracias por usar el sistema de gestion\n";
}
