#include <iostream>
#include <vector>
using namespace std;

// Interfaces según ISP
class IMostrarTarea {
    public:
        virtual void mostrarTarea() const = 0;
        virtual ~IMostrarTarea() {}
};

class IGestionarTarea {
    public:
        virtual void cambiarEstado(string nuevoEstado) = 0;
        virtual string getTitulo() const = 0;
        virtual ~IGestionarTarea() {}
};

class IProgreso {
    public:
        virtual void mostrarProgreso(int completadas, int total) const = 0;
        virtual ~IProgreso() {}
};

class Tarea : public IMostrarTarea, public IGestionarTarea {
    private:
        string titulo;
        string descripcion;
        string estado;
    
    public:
        // Constructor
        Tarea(string title, string descrip) : titulo(title), descripcion(descrip), estado("pendiente") {}
    
        // Métodos de IMostrarTarea
        void mostrarTarea() const override {
            cout << "Tarea: " << titulo << ", Descripción: " << descripcion << ", Estado: " << estado << endl;
        }
    
        // Métodos de IGestionarTarea
        void cambiarEstado(string nuevoEstado) override {
            estado = nuevoEstado;
        }
    
        string getTitulo() const override {
            return titulo;
        }
};

class GestorTareas {
    private:
        vector<Tarea> tareas;
    
    public:
        void agregarTarea(const Tarea &nuevaTarea) {
            tareas.push_back(nuevaTarea);
        }
    
        void mostrarTareas() const {
            if (tareas.empty()) {
                cout << "No hay tareas pendientes.\n";
                return;
            }
            for (const Tarea &t : tareas) {
                t.mostrarTarea();
                cout << "*******************\n";
            }
        }
    
        void completarTarea(string titulo) {
            for (Tarea &t : tareas) {
                if (t.getTitulo() == titulo) {
                    t.cambiarEstado("Completada");
                    cout << "Tarea: " << titulo << " marcada como completada.\n";
                    return;
                }
            }
            cout << "Tarea no encontrada.\n";
        }
};

class GestorFechas {
    public:
        void establecerFechaLimite(string fecha) {
            cout << "Fecha límite establecida: " << fecha << endl;
        }
};

class SeguimientoProceso : public IProgreso {
    public:
        void mostrarProgreso(int completadas, int total) const override {
            double porcentaje = (total == 0) ? 0 : (double(completadas) / total) * 100;
            cout << "Progreso: " << porcentaje << "% de tareas completadas.\n";
        }
};

int main() {
    // Crear objetos
    GestorTareas gestor;
    GestorFechas gestorFechas;
    SeguimientoProceso seguimiento;

    // Agregar tareas
    gestor.agregarTarea(Tarea("Estudiar SOLID", "Leer sobre el principio SRP."));
    gestor.agregarTarea(Tarea("Documentación", "Subrayar datos principales de la minuta."));

    // Mostrar tareas
    gestor.mostrarTareas();

    // Completar una tarea
    gestor.completarTarea("Documentación");

    // Mostrar progreso
    seguimiento.mostrarProgreso(1, 2);

    // Establecer fecha límite
    gestorFechas.establecerFechaLimite("2025-04-10");

    return 0;
}
