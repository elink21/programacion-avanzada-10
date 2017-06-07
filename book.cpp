/*
Programa de registro de libros
Elias Edgardo Segundo Antonio
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct book{
	string title;
	int key;
	string auth;
	int stock;
};
vector<book> books(10);

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
bool insertData(book);
int findPlace();
string join(string);
string split(string);
void write();
void menu();
bool updateBook(int);
bool eraseBook(int);
int findBook(int);

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
				updateBook(key);
				break;
			case 4:
				cout<<"Ingresar clave: ";
				cin>>key;
				if(eraseBook(key))
				{
					cout<<"Libro eliminado!\n";
				}
				else cout<<"Error al borrar libro\n";
				break;
			case 5:
				cout<<"Ingrese clave: ";
				cin>>key;
				findT(key);
				break;
			case 6:
				makeUserPage();
				system("books.html");
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
			for(int i=0;i<books.size();i++)
			{
				if(books[i].key==key)
				{
					cout<<"Elemento encontrado en la posicion "<<i<<"\n";
					cout<<books[i].title<<"\n";
					cout<<books[i].auth<<"\n";
					cout<<books[i].stock<<"\n";
					return 1;
				}

			}
			return -1;
			break;
		case 2:
			sort();
			int right=0,left=0,m;
			while(books[right].key!=-1)right++;
			while(left<=right)
			{
				m=int((left+right)/2);
				if(books[m].key==key)
				{
					cout<<"Elemento encontrado en la posicion "<<m<<"\n";
					cout<<books[m].title<<"\n";
					cout<<books[m].auth<<"\n";
					cout<<books[m].stock<<"\n";
					return 1;
				}
				if(books[m].key>key) right=m-1;
				else left=m+1;
			}
			return -1;
			break;
	}
}

void sort()
{
	for(int i=0;i<books.size();i++)
	{
		for(int j=0;j<books.size();j++)
		{
			if(books[i].key<books[j].key)
			{
				if(books[i].key!=-1)
				swap(books[i],books[j]);
			}
		}
	}
}

bool updateBook(int key)
{
	int index=-1;
	for(int i=0;i<books.size();i++)
	{
		if(books[i].key==key)
			index=i;
	}
	if(index!=-1)
	{
		int option;
		cout<<"Que campo desea cambiar?\n"
		<<"1.-Nombre 2.-Autor 3.-Inventario\n";
		cout<<"Ingrese la opcion: ";
		cin>>option;
		switch(option)
		{
			case 1:
				cin.get();
				cout<<"Ingrese el nuevo nombre: ";
				getline(cin,books[index].title);
				break;
			case 2:
				cin.get();
				cout<<"Ingrese el nuevo: ";
				getline(cin,books[index].auth);
				break;
			case 3:
				cin.get();
				cout<<"Ingrese la nueva cantidad: ";
				cin>>books[index].stock;
				break;
		}
		write();
	}
	else return false;
}

void menu()
{
	cout<<"Ingrese el numero de la opcion deseada: \n"
	<<"1.-Registrar un libro\n"
	<<"2.-Mostrar datos del archivo\n"
	<<"3.-Modificar un libro por clave\n"
	<<"4.-Eliminar un elemento por clave\n"
	<<"5.-Buscar un elemento por clave\n"
	<<"6.-Mostrar pagina web\n"
	<<"7.- Salir\n"
	<<"Ingrese: ";
}

bool eraseBook(int key)
{
	int index=-1;
	for(int i=0;i<books.size();i++)
	{
		if(books[i].key==key)
			index=i;
	}
	if(index!=-1)
	{
		books.erase(books.begin()+index);
		write();
		return true;
	}
	else return false;
}

void showData()
{
	read();
	cout<<setw(6)<<"Clave"<<setw(40)<<"Titulo"<<
	setw(30)<<"Autor"<<setw(30)<<"Inventario"<<"\n";
	for(book b: books)
	{
		if(b.key!=-1)
		{
			cout<<setw(6);
			cout<<b.key;
			cout<<setw(40);
			cout<<split(b.title);
			cout<<setw(30);
			cout<<split(b.auth);
			cout<<setw(30);
			cout<<b.stock<<"\n";	
		}
		
	}
}

void read()
{
	setup();
	ifstream in("books.txt",ios::in);
	int pos=0;
	while(in>>books[pos].key>>books[pos].title>>
		books[pos].auth>>books[pos].stock
		)
	{
		pos++;
	}
}


void write()
{
	ofstream out("books.txt",ios::out);
	if(out)
	{
		for(book b: books)
		{
			if(b.key!=-1)
			out<<b.key<<" "<<join(b.title)<<" "
			<<join(b.auth)<<" "<<b.stock<<" ";
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
	for(int i=0;i<books.size();i++)
	{
		if(books[i].key==-1)return i;
	}
	return -1;
}

bool insertData(book temp)
{
	int placeEmpty=findPlace();
	if(placeEmpty!=-1)
	{
		books[placeEmpty]=temp;
		return true;
	}
	else return false;

}

void getData()
{
	cin.get();
	book temp;
	cout<<"Introduzca la clave del libro: ";
	cin>>temp.key;
	cin.get();
	cout<<"Introduzca el nombre del libro: ";
	getline(cin,temp.title);
	cout<<"Introduzca el autor del libro: ";
	getline(cin,temp.auth);
	cout<<"Introduzca el stock del libro: ";
	cin>>temp.stock;
	if(insertData(temp))
	{
		write();
		cout<<"\nRegistro exitoso!\n";
	} else cout<<"\nNo hay lugares\n";

}

void setup()
{
	book empty;
	empty.key=-1;
	empty.title="";
	empty.auth="";
	empty.stock=0;
	for(int i=0;i<books.size();i++)
	{
		books[i]=empty;
	}
}

void makeUserPage()
	{
		fstream out("books.html",ios::out);
		out<<"<!DOCTYPE html>\n";
		out<<"<html lang='en'>\n";
		out<<"<head>\n";
		out<<"<meta charset='UTF-8'>\n";
		out<<"<meta title='viewport' content='width=device-width,";
		out<<"user-scalable=no, initial-scale=1.0,maximum-scale=1.0, minimum-scale=1.0'>\n";
		out<<"<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'";
		out<<"integrity='sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u'\n"; 
		out<<"crossorigin='anonymous'>\n";

		out<<"<title>Pagina de libros</title>\n";
		out<<"</head>\n";
		out<<"<body>\n";
		out<<"<table class='table table-striped'>\n";
			out<<"<tr>\n";
				out<<"<th>Clave</th>\n";
				out<<"<th>Nombre</th>\n";
				out<<"<th>Autor</th>\n";
				out<<"<th>Stock</th>\n";
			out<<"</tr>\n";
			for(book b:books)
			{
				if(b.key!=-1){
				out<<"<tr>\n";
				out<<"<td>"<<b.key<<"</td>\n";
				out<<"<td>"<<split(b.title)<<"</td>\n";
				out<<"<td>"<<split(b.auth)<<"</td>\n";
				out<<"<td>"<<b.stock<<"</td>\n";
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