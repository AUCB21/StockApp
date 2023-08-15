#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>


using namespace std;

enum pcTipos
	{ PC_Desktop, Notebook, PC_AiO, PC_Cosud };

enum estadoMantenimiento 
	{ activo, inactivo };

struct PC {
	string nombre;
	pcTipos tipoPc;
	estadoMantenimiento estado;
	string ubicacionGeografica;
	string usuarioAsociado;
};

struct Monitor {
	string marca;
	string usuarioAsociado;
	string ubicacionGeografica;
	const short unsigned int tamano;
};

struct Usuario {
	string nombre;
	string rubro;
	string ubicacionGeografica;
	PC* pcAsociada;
	Monitor* monitorAsociado;
};

struct listaUsuarios {
	vector<Usuario> usuarios;
};