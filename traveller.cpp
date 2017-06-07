/*
Programa de registro de pasajeros
Elias Edgardo Segundo Antonio
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct traveller{
	int key;
	string name;
	string origin;
	string destiny;
	double price;
};
vector<traveller> travellers(10);

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
bool insertData(traveller);
int findPlace();
string join(string);
string split(string);
void write();
void menu();
bool updateTraveller(int);
bool eraseTraveller(int);
int findTraveller(int);

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
				updateTraveller(key);
				break;
			case 4:
				cout<<"Ingresar clave: ";
				cin>>key;
				if(eraseTraveller(key))
				{
					cout<<"Pasajero eliminado!\n";
				}
				else cout<<"Error al borrar pasajero\n";
				break;
			case 5:
				cout<<"Ingrese clave: ";
				cin>>key;
				findT(key);
				break;
			case 6:
				makeUserPage();
				system("travellers.html");
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
			for(int i=0;i<travellers.size();i++)
			{
				if(travellers[i].key==key)
				{
					cout<<"Elemento encontrado en la posicion "<<i<<"\n";
					cout<<travellers[i].name<<"\n";
					cout<<travellers[i].origin<<"\n";
					cout<<travellers[i].destiny<<"\n";
					cout<<travellers[i].price<<"\n\n";
					return 1;
				}

			}
			return -1;
			break;
		case 2:
			sort();
			int right=0,left=0,m;
			while(travellers[right].key!=-1)right++;
			while(left<=right)
			{
				m=int((left+right)/2);
				if(travellers[m].key==key)
				{
					cout<<"Elemento encontrado en la posicion "<<m<<"\n";
					cout<<travellers[m].name<<"\n";
					cout<<travellers[m].origin<<"\n";
					cout<<travellers[m].destiny<<"\n";
					cout<<travellers[m].price<<"\n\n";
					return 1;
				}
				if(travellers[m].key>key) right=m-1;
				else left=m+1;
			}
			return -1;
			break;
	}
}

void sort()
{
	for(int i=0;i<travellers.size();i++)
	{
		for(int j=0;j<travellers.size();j++)
		{
			if(travellers[i].key<travellers[j].key)
			{
				if(travellers[i].key!=-1)
				swap(travellers[i],travellers[j]);
			}
		}
	}
}

bool updateTraveller(int key)
{
	int index=-1;
	for(int i=0;i<travellers.size();i++)
	{
		if(travellers[i].key==key)
			index=i;
	}
	if(index!=-1)
	{
		int option;
		cout<<"Que campo desea cambiar?\n"
		<<"1.-Nombre   2.-Origen   3.-Destino   4.-Precio\n";
		cout<<"Ingrese la opcion: ";
		cin>>option;
		switch(option)
		{
			case 1:
				cin.get();
				cout<<"Ingrese el nuevo nombre: ";
				getline(cin,travellers[index].name);
				break;
			case 2:
				cin.get();
				cout<<"Ingrese el nuevo origen: ";
				getline(cin,travellers[index].origin);
				break;
			case 3:
				cin.get();
				cout<<"Ingrese el nuevo destino: ";
				getline(cin,travellers[index].destiny);
				break;
			case 4:
				cout<<"Ingrese el nuevo precio: ";
				cin>>travellers[index].price;
				break;
		}
		write();
	}
	else return false;
}

void menu()
{
	cout<<"Ingrese el numero de la opcion deseada: \n"
	<<"1.-Registrar Un pasajero\n"
	<<"2.-Mostrar datos del archivo\n"
	<<"3.-Modificar un pasajero por clave\n"
	<<"4.-Eliminar un elemento por clave\n"
	<<"5.-Buscar un elemento por clave\n"
	<<"6.-Mostrar pagina web\n"
	<<"7.- Salir\n"
	<<"Ingrese: ";
}

bool eraseTraveller(int key)
{
	int index=-1;
	for(int i=0;i<travellers.size();i++)
	{
		if(travellers[i].key==key)
			index=i;
	}
	if(index!=-1)
	{
		travellers.erase(travellers.begin()+index);
		write();
		return true;
	}
	else return false;
}

void showData()
{
	read();
	cout<<setw(6)<<"Clave"<<setw(40)<<"Nombre"<<
	setw(30)<<"Origen"<<setw(30)<<"Destino"<<setw(12)<<"Pasaje\n";
	for(traveller t: travellers)
	{
		if(t.key!=-1)
		{
			cout<<setw(6);
			cout<<t.key;
			cout<<setw(40);
			cout<<split(t.name);
			cout<<setw(30);
			cout<<split(t.origin);
			cout<<setw(30);
			cout<<split(t.destiny);
			cout<<setw(12);
			cout<<t.price<<" \n";	
		}
		
	}
}

void read()
{
	setup();
	ifstream in("passengers.txt",ios::in);
	int pos=0;
	while(in>>travellers[pos].key>>travellers[pos].name>>
		travellers[pos].origin>>travellers[pos].destiny>>
		travellers[pos].price
		)
	{
		pos++;
	}
}


void write()
{
	ofstream out("passengers.txt",ios::out);
	if(out)
	{
		for(traveller t: travellers)
		{
			if(t.key!=-1)
			out<<t.key<<" "<<join(t.name)<<" "
			<<join(t.origin)<<" "
			<<join(t.destiny)<<" "
			<<t.price<<" ";
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
	for(int i=0;i<travellers.size();i++)
	{
		if(travellers[i].key==-1)return i;
	}
	cout<<"debug\n";
	return -1;
}

bool insertData(traveller temp)
{
	int placeEmpty=findPlace();
	if(placeEmpty!=-1)
	{
		travellers[placeEmpty]=temp;
		return true;
	}
	else return false;

}

void getData()
{
	cin.get();
	traveller temp;
	cout<<"Introduzca el nombre del pasajero: ";
	getline(cin,temp.name);
	cout<<"Introduzca la clave del pasajero: ";
	cin>>temp.key;
	cin.get();
	cout<<"Ahora introduzca el origen: ";
	getline(cin,temp.origin);
	cout<<"Introduzca el destino: ";
	getline(cin,temp.destiny);
	cout<<"Finalmente introduzca el precio del viaje: ";
	cin>>temp.price;
	cin.get();
	if(insertData(temp))
	{
		write();
		cout<<"\nRegistro exitoso!\n";

	} else cout<<"\nNo hay lugares\n";

}

void setup()
{
	traveller empty;
	empty.key=-1;
	empty.name="";
	empty.origin="";
	empty.destiny="";
	empty.price=0;
	for(int i=0;i<travellers.size();i++)
	{
		travellers[i]=empty;
	}
}

void makeUserPage()
	{
		fstream out("travellers.html",ios::out);
		out<<"<!DOCTYPE html>\n";
		out<<"<html lang='en'>\n";
		out<<"<head>\n";
		out<<"<meta charset='UTF-8'>\n";
		out<<"<meta name='viewport' content='width=device-width,";
		out<<"user-scalable=no, initial-scale=1.0,maximum-scale=1.0, minimum-scale=1.0'>\n";
		out<<"<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'";
		out<<"integrity='sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u'\n"; 
		out<<"crossorigin='anonymous'>\n";

		out<<"<title>Pagina de pasajeros</title>\n";
		out<<"</head>\n";
		out<<"<body>\n";
		out<<"<table class='table table-striped'>\n";
			out<<"<tr>\n";
				out<<"<th>Clave</th>\n";
				out<<"<th>Nombre</th>\n";
				out<<"<th>Origen</th>\n";
				out<<"<th>Destino</th>\n";
				out<<"<th>Precio</th>\n";
			out<<"</tr>\n";
			for(traveller t:travellers)
			{
				if(t.key!=-1){
				out<<"<tr>\n";
				out<<"<td>"<<t.key<<"</td>\n";
				out<<"<td>"<<split(t.name)<<"</td>\n";
				out<<"<td>"<<split(t.origin)<<"</td>\n";
				out<<"<td>"<<split(t.destiny)<<"</td>\n";
				out<<"<td>"<<t.price<<"</td>\n";
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