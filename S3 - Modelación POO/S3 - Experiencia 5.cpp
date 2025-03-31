#include <iostream>
#include <vector>
using namespace std;

// Definimos una interfaz para tareas
class ITarea {
    public:
        virtual void mostrarTarea() const = 0;
        virtual void cambiarEstado(const string& nuevoEstado) = 0;
        virtual string getTitulo() const = 0;
        virtual ~ITarea() {}
};

class Tarea : public ITarea {
    private:
        string titulo;
        string descripcion;
        string estado;
    public:
        Tarea(string title, string descrip) : titulo(title), descripcion(descrip), estado("pendiente") {}
        
        void mostrarTarea() const override {
            cout << "Tarea: " << titulo << ", descripción: " << descripcion << ", estado: " << estado << endl;
        }
        
        void cambiarEstado(const string& nuevoEstado) override {
            estado = nuevoEstado;
        }
        
        string getTitulo() const override { return titulo; }
};

// Definimos una interfaz para el gestor de tareas
class IGestorTareas {
    public:
        virtual void agregarTarea(ITarea* nuevaTarea) = 0;
        virtual void mostrarTareas() const = 0;
        virtual void completarTarea(const string& titulo) = 0;
        virtual ~IGestorTareas() {}
};

class GestorTareas : public IGestorTareas {
    private:
        vector<ITarea*> tareas;
    public:
        void agregarTarea(ITarea* nuevaTarea) override {
            tareas.push_back(nuevaTarea);
        }
        
        void mostrarTareas() const override {
            if (tareas.empty()) {
                cout << "No hay tareas pendientes.\n";
                return;
            }
            for (const ITarea* tarea : tareas) {
                tarea->mostrarTarea();
                cout << "*******************\n";
            }
        }
        
        void completarTarea(const string& titulo) override {
            for (ITarea* tarea : tareas) {
                if (tarea->getTitulo() == titulo) {
                    tarea->cambiarEstado("Completada");
                    cout << "Tarea: " << titulo << " marcada como completada.\n";
                    return;
                }
            }
            cout << "Tarea no encontrada.\n";
        }
};

// Definimos una interfaz para la gestión de fechas
class IGestorFechas {
    public:
        virtual void establecerFechaLimite(const string& fecha) = 0;
        virtual ~IGestorFechas() {}
};

class GestorFechas : public IGestorFechas {
    public:
        void establecerFechaLimite(const string& fecha) override {
            cout << "Fecha límite establecida: " << fecha << endl;
        }
};

// Definimos una interfaz para el seguimiento del proceso
class ISeguimientoProceso {
    public:
        virtual void mostrarProgreso(int completadas, int total) const = 0;
        virtual ~ISeguimientoProceso() {}
};

class SeguimientoProceso : public ISeguimientoProceso {
    public:
        void mostrarProgreso(int completadas, int total) const override {
            double porcentaje = (total == 0) ? 0 : (double(completadas) / total) * 100;
            cout << "Progreso: " << porcentaje << "% de tareas completadas.\n";
        }
};

int main() {
    GestorTareas gestor;
    GestorFechas gestorFechas;
    SeguimientoProceso seguimiento;
    
    // Agregar tareas
    Tarea tarea1("Estudiar SOLID", "Leer sobre el principio SRP.");
    Tarea tarea2("Documentación", "Subrayar datos principales de la minuta.");
    
    gestor.agregarTarea(&tarea1);
    gestor.agregarTarea(&tarea2);
    
    // Mostrar tareas
    gestor.mostrarTareas();
    
    // Completar una tarea
    gestor.completarTarea("Documentación");
    
    // Mostrar progreso 1 de 2 completadas
    seguimiento.mostrarProgreso(1, 2);
    
    // Establecer fecha límite
    gestorFechas.establecerFechaLimite("2025-04-10");

    return 0;
}
