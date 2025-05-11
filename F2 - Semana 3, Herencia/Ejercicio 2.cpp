#include <iostream>
#include <string>
using namespace std;

class Persona {
protected:
    string correo;  // Atributo protected (accesible en clases derivadas)

public:
    string nombre;
    int edad;
    double salario;
    
    Persona(string n, int e, double s, string c)
        : nombre(n), edad(e), salario(s), correo(c) {}

    void mostrarDatos() {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << " años" << endl;
        cout << "Salario: S/." << salario << endl;
    }
};

class Empleado : public Persona {
public:
    Empleado(string n, int e, double s, string c)
        : Persona(n, e, s, c) {}

    void mostrarCorreo() {
        cout << "Correo del Empleado: " << correo << endl;
    }
};

class Cliente : public Persona {
public:
    Cliente(string n, int e, double s, string c)
        : Persona(n, e, s, c) {}

    void mostrarCorreo() {
        cout << "Correo del Cliente: " << correo << endl;
    }
};

int main() {
    Empleado emp("Luis", 30, 3500.0, "luis@empresa.com");
    Cliente cli("Jazmin", 25, 0.0, "jazmin@gmail.com");

    cout << "=== Datos del Empleado ===" << endl;
    emp.mostrarDatos();
    emp.mostrarCorreo();

    cout << "\n=== Datos del Cliente ===" << endl;
    cli.mostrarDatos();
    cli.mostrarCorreo();

    return 0;
}

