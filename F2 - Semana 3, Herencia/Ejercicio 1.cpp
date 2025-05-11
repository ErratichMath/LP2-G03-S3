#include <iostream>
using namespace std;
class Vehiculo {
protected:
    string marca;
    string modelo;
    int anio;
    float precio;
public:
    Vehiculo(string m, string mo, int a, float p) {
        marca = m;
        modelo = mo;
        anio = a;
        precio = p;
    }
    void mostrarDatos() {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Año: " << anio << endl;
        cout << "Precio: $" << precio << endl;
    }
};
class Automovil : public Vehiculo {
    int puertas;
    string combustible;
public:
    Automovil(string m, string mo, int a, float p, int pu, string comb)
        : Vehiculo(m, mo, a, p) {
        puertas = pu;
        combustible = comb;
    }

    void mostrar() {
        mostrarDatos();
        cout << "Puertas: " << puertas << endl;
        cout << "Combustible: " << combustible << endl;
    }
};
class Motocicleta : public Vehiculo {
    int cilindrada;
public:
    Motocicleta(string m, string mo, int a, float p, int cil)
        : Vehiculo(m, mo, a, p) {
        cilindrada = cil;
    }

    void mostrar() {
        mostrarDatos();
        cout << "Cilindrada: " << cilindrada << " cc" << endl;
    }
};
int main() {
    Automovil auto1("Toyota", "Corolla", 2020, 18000, 4, "Gasolina");
    Motocicleta moto1("Yamaha", "FZ", 2022, 4500, 150);
    cout << "Datos del automóvil:" << endl;
    auto1.mostrar();
    cout << endl << "Datos de la motocicleta:" << endl;
    moto1.mostrar();
    return 0;
}
