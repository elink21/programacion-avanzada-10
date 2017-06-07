/*
Programa de registro de estudiantes
Elias Edgardo Segundo Antonio
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct student{
	string name;
	int key;
	double notes[2];
	double note;
};
vector<student> students(10);

//Prototype section
void makeUserPage();
void debug();
int findT(int);
void sort();
void setup();
void read();
void showData();
void getData();
void sort();
bool insertData(student);
int findPlace();
string join(string);
string split(string);
void write();
void menu();
bool updateStudent(int);
bool eraseStudent(int);
int findStudent(int);

int main()
{
	setup();
	int option,key;
	read();
	sort();
	while(option!=7)
	{
		cout<<"\n\n\n";
		menu();
		cin>>option;
		switch(option)
		{
			case 1:
				getData();
				break;
			case 2:
				sort();
				write();
				showData();
				break;
			case 3:
				cout<<"Ingresar clave: ";
				cin>>key;
				updateStudent(key);
				break;
			case 4:
				cout<<"Ingresar clave: ";
				cin>>key;
				if(eraseStudent(key))
				{
					cout<<"Pasajero eliminado!\n";
				}
				else cout<<"Error al borrar estudiante\n";
				break;
			case 5:
				cout<<"Ingrese clave: ";
				cin>>key;
				findT(key);
				break;
			case 6:
				makeUserPage();
				system("students.html");
				break;
			default:
				if(option!=7)
					cout<<"\nIngrese una opcion valida\n";
		}
	}
}

int findT(int key)
{
	int option;
	cout<<"Que tipo de busqueda desea realizar?\n";
	cout<<"1.-Lineal   2.-Binaria\n";
	cout<<"Ingrese: ";
	cin>>option;
	switch(option)
	{
		case 1:
			for(int i=0;i<students.size();i++)
			{
				if(students[i].key==key)
				{
					cout<<"Elemento encontrado en la posicion "<<i<<"\n";
					cout<<students[i].name<<"\n";
					cout<<students[i].notes[0]<<"\n";
					cout<<students[i].notes[1]<<"\n";
					cout<<students[i].note<<"\n";
					return 1;
				}

			}
			return -1;
			break;
		case 2:
			sort();
			int right=0,left=0,m;
			while(students[right].key!=-1)right++;
			while(left<=right)
			{
				m=int((left+right)/2);
				if(students[m].key==key)
				{
					cout<<"Elemento encontrado en la posicion "<<m<<"\n";
					cout<<students[m].name<<"\n";
					cout<<students[m].notes[0]<<"\n";
					cout<<students[m].notes[1]<<"\n";
					cout<<students[m].note<<"\n";
					return 1;
				}
				if(students[m].key>key) right=m-1;
				else left=m+1;
			}
			return -1;
			break;
	}
}

void sort()
{
	for(int i=0;i<students.size();i++)
	{
		for(int j=0;j<students.size();j++)
		{
			if(students[i].key<students[j].key)
			{
				if(students[i].key!=-1)
				swap(students[i],students[j]);
			}
		}
	}
}

bool updateStudent(int key)
{
	int index=-1;
	for(int i=0;i<students.size();i++)
	{
		if(students[i].key==key)
			index=i;
	}
	if(index!=-1)
	{
		int option;
		cout<<"Que campo desea cambiar?\n"
		<<"1.-Nombre 2.-Nota primer parcial 3.-Nota segundo parcial\n";
		cout<<"Ingrese la opcion: ";
		cin>>option;
		switch(option)
		{
			case 1:
				cin.get();
				cout<<"Ingrese el nuevo nombre: ";
				getline(cin,students[index].name);
				break;
			case 2:
				cout<<"Ingrese la nueva nota: ";
				cin>>students[index].notes[0];
				break;
			case 3:
				cin.get();
				cout<<"Ingrese la nueva nota: ";
				cin>>students[index].notes[1];
				break;
		}
		students[index].note=(students[index].notes[0]+students[index].notes[1])/2;
		write();
	}
	else return false;
}

void menu()
{
	cout<<"Ingrese el numero de la opcion deseada: \n"
	<<"1.-Registrar un estudiante\n"
	<<"2.-Mostrar datos del archivo\n"
	<<"3.-Modificar un estudiante por clave\n"
	<<"4.-Eliminar un elemento por clave\n"
	<<"5.-Buscar un elemento por clave\n"
	<<"6.-Mostrar pagina web\n"
	<<"7.- Salir\n"
	<<"Ingrese: ";
}

bool eraseStudent(int key)
{
	int index=-1;
	for(int i=0;i<students.size();i++)
	{
		if(students[i].key==key)
			index=i;
	}
	if(index!=-1)
	{
		students.erase(students.begin()+index);
		write();
		return true;
	}
	else return false;
}

void showData()
{
	read();
	cout<<setw(6)<<"Clave"<<setw(40)<<"Nombre"<<
	setw(30)<<"Nota 1"<<setw(30)<<"Nota 2"<<setw(12)<<"Calificacion final\n";
	for(student s: students)
	{
		if(s.key!=-1)
		{
			cout<<setw(6);
			cout<<s.key;
			cout<<setw(40);
			cout<<split(s.name);
			cout<<setw(30);
			cout<<s.notes[0];
			cout<<setw(30);
			cout<<s.notes[1];
			cout<<setw(12);
			cout<<s.note<<" \n";	
		}
		
	}
}

void read()
{
	setup();
	ifstream in("students.txt",ios::in);
	int pos=0;
	while(in>>students[pos].key>>students[pos].name>>
		students[pos].notes[0]>>students[pos].notes[1]>>
		students[pos].note
		)
	{
		pos++;
	}
}


void write()
{
	ofstream out("students.txt",ios::out);
	if(out)
	{
		for(student s: students)
		{
			if(s.key!=-1)
			out<<s.key<<" "<<join(s.name)<<" "
			<<s.notes[0]<<" "<<s.notes[1]<<" "<<s.note<<" ";
		}
		out.close();
	}
	else cout<<"Error al abrir el archivo";
}

string split(string s)
{
	for(int i=0;i<s.size();i++)
		if(s[i]=='#')s[i]=' ';
	return s;
}

string join(string s)
{
	for(int i=0;i<s.size();i++)
		if(s[i]==' ')s[i]='#';
	return s;
}

int findPlace()
{
	for(int i=0;i<students.size();i++)
	{
		if(students[i].key==-1)return i;
	}
	return -1;
}

bool insertData(student temp)
{
	int placeEmpty=findPlace();
	if(placeEmpty!=-1)
	{
		students[placeEmpty]=temp;
		return true;
	}
	else return false;

}

void getData()
{
	cin.get();
	student temp;
	cout<<"Introduzca la clave del estudiante: ";
	cin>>temp.key;
	cin.get();
	cout<<"Introduzca el nombre del estudiante: ";
	getline(cin,temp.name);
	cout<<"Introduzca la calificacion del primer parcial: ";
	cin>>temp.notes[0];
	cout<<"Introduzca la calificacion del segundo parcial: ";
	cin>>temp.notes[1];
	temp.note=(temp.notes[0]+temp.notes[1])/2;
	if(insertData(temp))
	{
		write();
		cout<<"\nRegistro exitoso!\n";
	} else cout<<"\nNo hay lugares\n";

}

void setup()
{
	student empty;
	empty.key=-1;
	empty.name="";
	empty.notes[0]=0;
	empty.notes[1]=0;
	empty.note=0;
	for(int i=0;i<students.size();i++)
	{
		students[i]=empty;
	}
}

void makeUserPage()
	{
		fstream out("students.html",ios::out);
		out<<"<!DOCTYPE html>\n";
		out<<"<html lang='en'>\n";
		out<<"<head>\n";
		out<<"<meta charset='UTF-8'>\n";
		out<<"<meta name='viewport' content='width=device-width,";
		out<<"user-scalable=no, initial-scale=1.0,maximum-scale=1.0, minimum-scale=1.0'>\n";
		out<<"<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'";
		out<<"integrity='sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u'\n"; 
		out<<"crossorigin='anonymous'>\n";

		out<<"<title>Pagina de estudiantes</title>\n";
		out<<"</head>\n";
		out<<"<body>\n";
		out<<"<table class='table table-striped'>\n";
			out<<"<tr>\n";
				out<<"<th>Clave</th>\n";
				out<<"<th>Nombre</th>\n";
				out<<"<th>Primer parcial</th>\n";
				out<<"<th>Segundo Parcial</th>\n";
				out<<"<th>Promedio</th>\n";
			out<<"</tr>\n";
			for(student s:students)
			{
				if(s.key!=-1){
				out<<"<tr>\n";
				out<<"<td>"<<s.key<<"</td>\n";
				out<<"<td>"<<split(s.name)<<"</td>\n";
				out<<"<td>"<<s.notes[0]<<"</td>\n";
				out<<"<td>"<<s.notes[1]<<"</td>\n";
				out<<"<td>"<<s.note<<"</td>\n";
				out<<"</tr>\n";}		
			}
		out<<"</table>\n";
		out<<"</div>\n";
		out<<"<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'\n";
		out<<"integrity='sha384-Tc5IQib027qvyjSMfHjOMaLkf\n";
		out<<"uWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa '\n"; 
		out<<"crossorigin='anonymous'>\n";
		out<<"</script>\n";
		out<<"</body>\n";
		out<<"</html>\n";
	}