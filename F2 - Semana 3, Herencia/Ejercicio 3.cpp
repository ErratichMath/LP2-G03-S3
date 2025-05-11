#include <iostream>
#include <string>
using namespace std;

class Movil {
protected:
    string marca;
    string modelo;
    string sistemaOperativo;

public:
    Movil(string m, string mo, string so)
        : marca(m), modelo(mo), sistemaOperativo(so) {
        cout << "Constructor de Movil: " << marca << " " << modelo << endl;
    }
    ~Movil() {
        cout << "Destructor de Movil: " << marca << " " << modelo << endl;
    }

    void mostrarInfo() {
        cout << "Marca: " << marca << ", Modelo: " << modelo
             << ", Sistema Operativo: " << sistemaOperativo << endl;
    }
};

class Telefono : public Movil {
public:
    Telefono(string m, string mo, string so)
        : Movil(m, mo, so) {
        cout << "Constructor de Telefono" << endl;
    }

    ~Telefono() {
        cout << "Destructor de Telefono" << endl;
    }
};

class Tablet : public Movil {
public:
    Tablet(string m, string mo, string so)
        : Movil(m, mo, so) {
        cout << "Constructor de Tablet" << endl;
    }

    ~Tablet() {
        cout << "Destructor de Tablet" << endl;
    }
};

int main() {
    cout << "=== Creando un Telefono ===" << endl;
    Telefono t("Samsung", "Galaxy S21", "Android");

    cout << "\n=== Creando una Tablet ===" << endl;
    Tablet tab("Apple", "iPad Air", "iOS");

    cout << "\n=== Información ===" << endl;
    t.mostrarInfo();
    tab.mostrarInfo();

    cout << "\n=== Fin del Programa ===" << endl;

    return 0;
}
