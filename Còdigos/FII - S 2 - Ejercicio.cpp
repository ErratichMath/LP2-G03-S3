#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Alumno {
private:
    string nombre;
    int edad;
    float promedio;

public:
    Alumno(string n, int e, float p) : nombre(n), edad(e), promedio(p) {}

    string Cadena() const {
        return "Nombre: " + nombre + ", Edad: " + to_string(edad) + ", Promedio: " + to_string(promedio);
    }

    float obtenerPromedio() const {
        return promedio;
    }

    bool esMenorPromedio(const Alumno& otro) const {
        return this->promedio < otro.promedio;
    }
};

class Grupo {
private:
    vector<Alumno> alumnos;
    int cantidad;

public:
    Grupo(int c) : cantidad(c) {
        alumnos.reserve(cantidad);
    }

    string Cadena() const {
        string resultado = "Grupo:\n";
        for (const auto& alumno : alumnos) {
            resultado += alumno.Cadena() + "\n";
        }
        return resultado;
    }

    void agregarAlumno(const string& nombre, int edad, float promedio) {
        if (alumnos.size() < cantidad) {
            alumnos.emplace_back(nombre, edad, promedio);
        } 
    }

    void ordenarAlumnosPorPromedio() {
        int n = alumnos.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i -1; ++j) {
                if (!alumnos[j].esMenorPromedio(alumnos[j + 1])) {
                    Alumno temp = alumnos[j];
                    alumnos[j] = alumnos[j + 1];
                    alumnos[j + 1] = temp;
                }
            }
        }
    }

    float calcularPromedioGeneral() const {
        if (alumnos.empty()) return 0.0f;

        float suma = 0.0f;
        for (const auto& alumno : alumnos) {
            suma += alumno.obtenerPromedio();
        }
        return suma / alumnos.size();
    }

    Alumno obtenerMejorPromedio() const {
        if (alumnos.empty()) throw runtime_error("No hay alumnos en el grupo");

        const Alumno* mejor = &alumnos[0];
        for (const auto& alumno : alumnos) {
            if (alumno.obtenerPromedio() > mejor->obtenerPromedio()) {
                mejor = &alumno;
            }
        }
        return *mejor;
    }
};

int main() {
    Grupo grupo(5);

    grupo.agregarAlumno("Juan", 20, 8.5f);
    grupo.agregarAlumno("Ana", 21, 9.2f);
    grupo.agregarAlumno("Luis", 22, 7.8f);
    grupo.agregarAlumno("Maria", 20, 9.5f);
    grupo.agregarAlumno("Carlos", 23, 8.9f);

    cout << grupo.Cadena() << endl;

    cout << "Promedio general: " << grupo.calcularPromedioGeneral() << endl;

    Alumno mejor = grupo.obtenerMejorPromedio();
    cout << "Alumno con mejor promedio: " << mejor.Cadena() << endl;

    return 0;
}