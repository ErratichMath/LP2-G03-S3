#include <iostream>
#include <vector>
using namespace std;

// INTERFAZ PARA TAREAS
class ITarea {
    public:
        virtual void mostrarTarea() const = 0;
        virtual void cambiarEstado(string nuevoEstado) = 0;
        virtual string getTitulo() const = 0;
        virtual ~ITarea() {} // Destructor virtual
};

// CLASE BASE: TAREA ESTÁNDAR
class Tarea : public ITarea {
    protected:
        string titulo;
        string descripcion;
        string estado;
    public:
        Tarea(string title, string descrip) : titulo(title), descripcion(descrip), estado("pendiente") {}
    
        void mostrarTarea() const override {
            cout << "Tarea: " << titulo << ", Descripción: " << descripcion << ", Estado: " << estado << endl;
        }
    
        void cambiarEstado(string nuevoEstado) override {
            estado = nuevoEstado;
        }
    
        string getTitulo() const override {
            return titulo;
        }
};

// CLASE DERIVADA: TAREA CON PRIORIDAD
class TareaPrioritaria : public Tarea {
    private:
        int prioridad;
    public:
        TareaPrioritaria(string title, string descrip, int prioridadNivel)
            : Tarea(title, descrip), prioridad(prioridadNivel) {}
    
        void mostrarTarea() const override {
            cout << "[PRIORIDAD " << prioridad << "] Tarea: " << titulo 
                 << ", Descripción: " << descripcion << ", Estado: " << estado << endl;
        }
};

// CLASE DERIVADA: TAREA CON FECHA LÍMITE
class TareaConFechaLimite : public Tarea {
    private:
        string fechaLimite;
    public:
        TareaConFechaLimite(string title, string descrip, string fecha)
            : Tarea(title, descrip), fechaLimite(fecha) {}
    
        void mostrarTarea() const override {
            cout << "Tarea: " << titulo << ", Descripción: " << descripcion 
                 << ", Estado: " << estado << ", Fecha Límite: " << fechaLimite << endl;
        }
};

// GESTOR DE TAREAS QUE MANEJA CUALQUIER TIPO DE TAREA
class GestorTareas {
    private:
        vector<ITarea*> tareas;
    public:
        void agregarTarea(ITarea* nuevaTarea) {
            tareas.push_back(nuevaTarea);
        }
    
        void mostrarTareas() const {
            if (tareas.empty()) {
                cout << "No hay tareas pendientes.\n";
                return;
            }
            for (const ITarea* tarea : tareas) {
                tarea->mostrarTarea();
                cout << "*******************\n";
            }
        }
    
        void completarTarea(string titulo) {
            for (ITarea* tarea : tareas) {
                if (tarea->getTitulo() == titulo) {
                    tarea->cambiarEstado("Completada");
                    cout << "Tarea: " << titulo << " marcada como completada.\n";
                    return;
                }
            }
            cout << "Tarea no encontrada.\n";
        }
    
        ~GestorTareas() {
            for (ITarea* tarea : tareas) {
                delete tarea;
            }
        }
};

// CLASE SEGUIMIENTO DE PROGRESO
class SeguimientoProceso {
    public:
        void mostrarProgreso(int completadas, int total) {
            double porcentaje = (total == 0) ? 0 : (double(completadas) / total) * 100;
            cout << "Progreso: " << porcentaje << "% de tareas completadas.\n";
        }
};

int main() {
    GestorTareas gestor;
    SeguimientoProceso seguimiento;

    gestor.agregarTarea(new Tarea("Estudiar SOLID", "Leer sobre el principio SRP."));
    gestor.agregarTarea(new TareaPrioritaria("Entrega de proyecto", "Terminar código", 1));
    gestor.agregarTarea(new TareaConFechaLimite("Revisión de código", "Corregir errores", "2025-04-15"));

    gestor.mostrarTareas();

    gestor.completarTarea("Entrega de proyecto");

    seguimiento.mostrarProgreso(1, 3);

    return 0;
}
