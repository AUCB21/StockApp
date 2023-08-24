#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum pcTipos
{
    PC_Desktop, Notebook, PC_AiO, PC_Cosud, Unspecified
};

enum estadoMantenimiento
{
    activo, inactivo
};

struct PC {
    string codigo;
    pcTipos tipoPc = Unspecified;
    estadoMantenimiento mantenimiento = inactivo;
    string motivoMantenimiento;
    string ubicacionGeografica;
    string usuarioAsociado;
};

struct Monitor {
    string codigo;
    string marca;
    string usuarioAsociado;
    string ubicacionGeografica;
    short unsigned int tamano = 0;
};

struct Usuario {
    string nombre;
    string rubro;
    string ubicacionGeografica;
    PC* pcAsociada = nullptr;
    Monitor* monitorAsociado = nullptr;
};

Monitor* crearMonitor() {
    Monitor* mon = new Monitor();
    cout << "Ingrese el codigo del monitor (..-MON-...): ";
    cin >> mon->codigo;

    cout << "Ingrese la marca del monitor: ";
    cin >> mon->marca;

    cout << "Ingrese el tamano del monitor: ";
    cin >> mon->tamano;
    
    return mon;
}

PC* crearPc() {
    PC* pc = new PC();
    cout << "Indique del codigo de la pc: ";
    cin >> pc->codigo;
    
    while (pc->tipoPc == Unspecified) {
        cout << "Ingrese el tipo de PC (PC_Desktop | Notebook | PC_AiO | PC_Cosud): ";
        string inputLine;
        cin >> inputLine;

        if (inputLine == "PC_Desktop")
            pc->tipoPc = PC_Desktop;
        else if (inputLine == "Notebook")
            pc->tipoPc = Notebook;
        else if (inputLine == "PC_AiO")
            pc->tipoPc = PC_AiO;
        else if (inputLine == "PC_Cosud")
            pc->tipoPc = PC_Cosud;
        else
            cout << "Tipo de PC no reconocido. Reintente con las opciones anteriores." << endl;
    }

    char ans[3];
    cout << "Se encuentra la PC en mantenimiento? (si | no): ";
    cin >> ans;

    while (ans == "si" || ans == "no") {
        if (ans == "si") {
            pc->mantenimiento = activo;
            cout << "Indique el motivo del mantenimiento: ";
            cin.ignore();
            getline(cin, pc->motivoMantenimiento);
            cout << "El motivo indicado es: " << pc->motivoMantenimiento;
        }
        else pc->mantenimiento = inactivo;
    }
    return pc;
}

Usuario* crearUsuario() {
    Usuario* usuario = new Usuario();

    cin.ignore();

    cout << "Ingrese el nombre del usuario: ";
    cin.ignore();
    getline(cin, usuario->nombre);
    

    cout << "Ingrese el rubro del usuario: ";
    cin.ignore();
    cin >> usuario->rubro;
    
    cin.ignore();

    cout << "Ingrese la ubicacion del usuario: ";
    getline(cin, usuario->ubicacionGeografica);
    return usuario;
}

void guardarUsuarios(vector<Usuario*> &usuarios, Usuario*& usuario) {
    usuario->monitorAsociado->ubicacionGeografica = usuario->ubicacionGeografica;
    usuario->pcAsociada->ubicacionGeografica = usuario->ubicacionGeografica;

    usuario->pcAsociada->usuarioAsociado = usuario->nombre;
    usuario->monitorAsociado->usuarioAsociado = usuario->nombre;

    usuarios.push_back(usuario);
}

void mostrarUsuarios(const vector<Usuario*> usuarios) {
    for (Usuario* usuario : usuarios) {
        cout << "El usuario es: " << usuario->nombre << ". " << endl;
        cout << "===========================================" << endl;
        cout << "El usuario pertenece a: " << usuario->rubro << endl;
        cout << "El usuario se encuentra en: " << usuario->ubicacionGeografica << endl;
        cout << "El usuario tiene en uso actual: \n"
            << usuario->pcAsociada->codigo << " - ";
        switch (usuario->pcAsociada->tipoPc) {
        case PC_Desktop:
            cout << "PC Desktop";
            break;
        case Notebook:
            cout << "Notebook";
            break;
        case PC_AiO:
            cout << "PC AiO";
            break;
        case PC_Cosud:
            cout << "PC Cosud";
            break;
        default:
            cout << "Tipo de PC no especificado";
            break;
        };

        cout << " - Mantenimiento? " << (usuario->pcAsociada->mantenimiento == activo ? "Activo" : "Inactivo")
            << "\n"
            << usuario->monitorAsociado->codigo << " - " << usuario->monitorAsociado->marca
            << " " << usuario->monitorAsociado->tamano << endl;
        cout << "===========================================" << endl;
    }
}

int main() {
    vector<Usuario*> usuarios;

    int opcion = 0;

    cout << "Cuantos usuarios desea crear?: ";
    cin >> opcion;

    for (int i = 0; i < opcion; i++) {
        cout << "=============Usuario " << i + 1 << "=============" << endl;
        Usuario* usr = crearUsuario();

        usr->monitorAsociado = crearMonitor();
        usr->pcAsociada = crearPc();

        guardarUsuarios(usuarios, usr);
    }

    mostrarUsuarios(usuarios);

    // Liberar memoria de usuarios
    for (Usuario* u : usuarios) delete u;
    usuarios.clear();

    return 0;
}