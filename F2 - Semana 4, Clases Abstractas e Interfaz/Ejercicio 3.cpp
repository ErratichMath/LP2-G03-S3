#include <iostream>
#include <string>
using namespace std;

class Empleado {
protected:
    string nombre;

public:
    Empleado(string nom) : nombre(nom) {}

    virtual double calcularSalario() = 0; // Método virtual puro (interfaz de cálculo)

    virtual void mostrarSalario() = 0;

    virtual ~Empleado() {}
};

class EmpleadoTiempoCompleto : public Empleado {
private:
    double salarioMensual;

public:
    EmpleadoTiempoCompleto(string nom, double salario)
        : Empleado(nom), salarioMensual(salario) {}

    double calcularSalario() override {
        return salarioMensual;
    }
    
    void mostrarSalario() override{
        cout << "Empleado: " << nombre << " | Salario: S/." << calcularSalario() << endl;
    }
    
};

class EmpleadoMedioTiempo : public Empleado {
private:
    int horasTrabajadas;
    double tarifaPorHora;

public:
    EmpleadoMedioTiempo(string nom, int horas, double tarifa)
        : Empleado(nom), horasTrabajadas(horas), tarifaPorHora(tarifa) {}

    double calcularSalario() override {
        return horasTrabajadas * tarifaPorHora;
    }
    
    void mostrarSalario() override{
        cout << "Empleado: " << nombre << " | Salario: S/." << calcularSalario() << endl;
    }
};

int main() {
    Empleado* emp1 = new EmpleadoTiempoCompleto("Jack", 3500.0);
    Empleado* emp2 = new EmpleadoMedioTiempo("Melisa", 80, 25.0);

    emp1->mostrarSalario();
    emp2->mostrarSalario();

    delete emp1;
    delete emp2;

    return 0;
}
