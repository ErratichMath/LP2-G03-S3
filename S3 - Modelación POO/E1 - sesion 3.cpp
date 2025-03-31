#include <iostream>
#include <vector>
using namespace std;
class ITarea {
public:
    virtual void mostrarTarea() = 0;
    virtual void cambiarEstado(string) = 0;
    virtual string getTitulo() = 0;
    virtual ~ITarea() {}
};

class IGestorTareas {
public:
    virtual void agregarTarea(ITarea*) = 0;
    virtual void mostrarTareas() = 0;
    virtual void completarTarea(string) = 0;
    virtual ~IGestorTareas() {}
};

class IGestorFechas {
public:
    virtual void establecerFechaLimite(string) = 0;
    virtual ~IGestorFechas() {}
};

class ISeguimientoProgreso {
public:
    virtual void mostrarProgreso(int, int) = 0;
    virtual ~ISeguimientoProgreso() {}
};

class Tarea : public ITarea {
private:
    string titulo, descripcion, estado;
public:
    Tarea(string t, string d) : titulo(t), descripcion(d), estado("Pendiente") {}
    void mostrarTarea() override {
        cout << "Tarea: " << titulo << "\nDescripción: " << descripcion << "\nEstado: " << estado << endl;
    }
    void cambiarEstado(string nuevoEstado) override {
        estado = nuevoEstado;
    }
    string getTitulo() override { return titulo; }
};

class GestorTareas : public IGestorTareas {
private:
    vector<ITarea*> tareas;
public:
    void agregarTarea(ITarea* nuevaTarea) override {
        tareas.push_back(nuevaTarea);
    }
    void mostrarTareas() override {
        for (ITarea* t : tareas) {
            t->mostrarTarea();
            cout << "----------------\n";
        }
    }
    void completarTarea(string titulo) override {
        for (ITarea* t : tareas) {
            if (t->getTitulo() == titulo) {
                t->cambiarEstado("Completada");
                cout << "Tarea '" << titulo << "' marcada como completada.\n";
                return;
            }
        }
        cout << "Tarea no encontrada.\n";
    }
};

class GestorFechas : public IGestorFechas {
public:
    void establecerFechaLimite(string fecha) override {
        cout << "Fecha límite establecida: " << fecha << endl;
    }
};

class SeguimientoProgreso : public ISeguimientoProgreso {
public:
    void mostrarProgreso(int completadas, int total) override {
        double porcentaje = (total == 0) ? 0 : (double(completadas) / total) * 100;
        cout << "Progreso: " << porcentaje << "% de tareas completadas.\n";
    }
};

int main() {
    GestorTareas gestor;
    GestorFechas gestorFechas;
    SeguimientoProgreso seguimiento;

    ITarea* tarea1 = new Tarea("Estudiar SOLID", "Leer sobre el principio SRP");
    ITarea* tarea2 = new Tarea("Hacer ejercicio", "Salir a correr 30 minutos");
    
    gestor.agregarTarea(tarea1);
    gestor.agregarTarea(tarea2);
    gestor.mostrarTareas();
    
    gestor.completarTarea("Estudiar SOLID");
    seguimiento.mostrarProgreso(1, 2);
    gestorFechas.establecerFechaLimite("2025-04-10");
    
    delete tarea1;
    delete tarea2;
    return 0;
}
