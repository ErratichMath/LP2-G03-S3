#include <iostream>
#include <vector>
using namespace std;

class Tarea{
    private:
        string titulo;
        string descripcion;
        string estado;
    public:
        //constructor
        Tarea(string title, string descrip): titulo(title), descripcion(descrip), estado("pendiente") {}
        
        //metodos
        void mostrarTarea(){
            cout<<"Tarea :"<<titulo<<", descripción: "<<descripcion<<", estado: "<<estado<<endl;
        }
        
        void cambiarEstado(string nuevoEstado){
            estado = nuevoEstado;
        }
        
        string getTitulo(){return titulo; }
    
};

class GestorTareas{
    private:
        vector<Tarea>tareas; 
        //crear la "lista" donde vamos almacenar la tarea. Es más funcional porque no sabemos cuantas tareas vamos a necesitar y esto es modificable.
        
    public:
        //porque no se crea constructores para vectores?
        
        void agregarTarea(Tarea nuevaTarea){
            tareas.push_back(nuevaTarea);
        }
        void mostrarTareas(){
            if(tareas.empty()){ //.empty(): verifica si el vector esta vacio y retorna true o false.
                cout<<"No hay tareas pendientes.\n";
                return;
            }
            for (Tarea &title: tareas){ 
                //forma más facil de recorrer cada elemento. "cada elemento title de tipo Tarea dentro del vector tareas, ejecuta el bloque de código. "
                title.mostrarTarea();
                cout<<"*******************\n";
            }
        }
        void completarTarea(string titulo){
            for(Tarea &title: tareas){
                if(title.getTitulo() == titulo){
                    title.cambiarEstado("Completada.");
                    cout<<"Tarea: "<<titulo<<" marcada como completada.\n";
                    return;
                }
            }
            
            cout<<"Tarea no encontrada.\n";
        }
};

class GestorFechas{
    public:
        void establecerFechaLimite(string fecha){
            cout<<"Fecha límite establecida: "<<fecha <<endl;
            //Investigar como codificaria si deseara que una vez pasada la fecha se marque como "incompleta."
        }
};

class SeguimientoProceso{
    public: 
        void mostrarProgreso(int completadas, int total){
            double porcentaje = (total == 0) ? 0:(double(completadas)/total)*100;
            cout<<"Progreso: "<<porcentaje<<"% de tareas completadas.\n";
        }
};


int main()
{
    //crear objetos
    GestorTareas gestor;
    GestorFechas gestorFechas;
    SeguimientoProceso seguimiento;
    
    //agregar tareas
    gestor.agregarTarea(Tarea("Estudiar SOLID", "Leer sobre el principio SRP."));
    gestor.agregarTarea(Tarea("Documentación","Subrayar datos principales de la minuta."));
    
    //Mostrar tareas
    gestor.mostrarTareas();
    
    //Completar una tareas
    gestor.completarTarea("Documentación");
    
    //Mostrar progreso 1 de 2 completadas
    seguimiento.mostrarProgreso(1,2);
    
    //Establecer fecha límite
    gestorFechas.establecerFechaLimite("2025-04-10");

    return 0;
}