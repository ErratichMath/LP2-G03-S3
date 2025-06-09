#include <iostream>
#include <vector>
#include <limits>
#include <cctype>
using namespace std;

bool nombreValido(string nombre)
{
    for (int i = 0; i < nombre.length(); i++)
    {
        if (!isalpha(nombre[i]))
            return false;
    }
    return true;
}

int leerOpcion()
{
    int valor;
    while (true)
    {
        cout << "Seleccione una opción: ";
        cin >> valor;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Elija correctamente.\n";
        }
        else
        {
            return valor;
        }
    }
}

double leerNumeroPositivo(string mensaje)
{
    double valor;
    do
    {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese un valor válido (mayor a 0).\n";
        }
    } while (valor <= 0);
    return valor;
}

string leerNombre(string tipo)
{
    string nombre;
    do
    {
        cout << "Nombre del " << tipo << ": ";
        cin >> nombre;
        if (!nombreValido(nombre))
        {
            cout << "Ingrese un nombre válido (solo letras).\n";
        }
    } while (!nombreValido(nombre));
    return nombre;
}

class Empleado
{
public:
    virtual void ingresarDatos() = 0;
    virtual double calcularSalario() = 0;
    virtual void mostrarInfo() = 0;
    virtual bool esAsalariado() = 0;
    virtual void editarDatos() = 0;
    virtual ~Empleado() {}
};

class Asalariado : public Empleado
{
private:
    string nombre;
    double salarioMensual;

public:
    void ingresarDatos()
    {
        nombre = leerNombre("asalariado");
        salarioMensual = leerNumeroPositivo("Salario mensual: ");
    }

    void editarDatos()
    {
        cout << "\n-- Editando asalariado --\n";
        nombre = leerNombre("asalariado");
        salarioMensual = leerNumeroPositivo("Nuevo salario mensual: ");
    }

    double calcularSalario()
    {
        return salarioMensual;
    }

    void mostrarInfo()
    {
        cout << "Asalariado: " << nombre << ", Salario: " << calcularSalario() << endl;
    }

    bool esAsalariado()
    {
        return true;
    }
};

class PorHora : public Empleado
{
private:
    string nombre;
    double horasTrabajadas;
    double tarifaPorHora;

public:
    void ingresarDatos()
    {
        nombre = leerNombre("empleado por hora");
        horasTrabajadas = leerNumeroPositivo("Horas trabajadas: ");
        tarifaPorHora = leerNumeroPositivo("Tarifa por hora: ");
    }

    void editarDatos() {} 

    double calcularSalario()
    {
        return horasTrabajadas * tarifaPorHora;
    }

    void mostrarInfo()
    {
        cout << "Empleado por hora: " << nombre << ", Salario: " << calcularSalario() << endl;
    }

    bool esAsalariado()
    {
        return false;
    }
};

class Comisionista : public Empleado
{
private:
    string nombre;
    double ventas;
    double porcentaje;

public:
    void ingresarDatos()
    {
        nombre = leerNombre("comisionista");
        ventas = leerNumeroPositivo("Total de ventas: ");
        do
        {
            porcentaje = leerNumeroPositivo("Porcentaje de comisión (ej. 0.1 = 10%): ");
            if (porcentaje > 1)
                cout << "Ingrese un porcentaje válido (máximo 1 = 100%).\n";
        } while (porcentaje > 1);
    }

    void editarDatos() {} 

    double calcularSalario()
    {
        return ventas * porcentaje;
    }

    void mostrarInfo()
    {
        cout << "Comisionista: " << nombre << ", Salario: " << calcularSalario() << endl;
    }

    bool esAsalariado()
    {
        return false;
    }
};

void editarAsalariado(vector<Empleado*>& empleados)
{
    vector<Empleado*> asalariados;
    vector<int> indices;

    for (int i = 0; i < empleados.size(); i++)
    {
        if (empleados[i]->esAsalariado())
        {
            asalariados.push_back(empleados[i]);
            indices.push_back(i);
        }
    }

    if (asalariados.empty())
    {
        cout << "No hay asalariados registrados.\n";
        return;
    }

    cout << "\n--- Lista de asalariados ---\n";
    for (int i = 0; i < asalariados.size(); i++)
    {
        cout << i + 1 << ". ";
        asalariados[i]->mostrarInfo();
    }

    int eleccion;
    cout << "Seleccione el número del asalariado a editar: ";
    cin >> eleccion;

    if (cin.fail() || eleccion < 1 || eleccion > asalariados.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Elija correctamente.\n";
        return;
    }

    int indiceReal = indices[eleccion - 1];
    empleados[indiceReal]->editarDatos();
    cout << "Asalariado actualizado correctamente.\n";
}

int main()
{
    vector<Empleado*> empleados;
    int opcion;

    do
    {
        cout << "\n--- Sistema de Nómina ---\n";
        cout << "1. Agregar asalariado\n";
        cout << "2. Agregar empleado por hora\n";
        cout << "3. Agregar comisionista\n";
        cout << "4. Mostrar nómina\n";
        cout << "5. Editar asalariado\n";
        cout << "6. Salir\n";

        opcion = leerOpcion();
        Empleado* emp = nullptr;

        switch (opcion)
        {
            case 1:
                emp = new Asalariado();
                break;
            case 2:
                emp = new PorHora();
                break;
            case 3:
                emp = new Comisionista();
                break;
            case 4:
                for (int i = 0; i < empleados.size(); i++)
                {
                    empleados[i]->mostrarInfo();
                }
                break;
            case 5:
                editarAsalariado(empleados);
                break;
            case 6:
                break;
            default:
                cout << "Elija correctamente.\n";
        }

        if (opcion >= 1 && opcion <= 3)
        {
            emp->ingresarDatos();
            empleados.push_back(emp);
        }

    } while (opcion != 6);

    for (int i = 0; i < empleados.size(); i++)
    {
        delete empleados[i];
    }

    return 0;
}
