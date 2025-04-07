#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// --------------------- TIENDA DE ROPA ---------------------
class Producto;
class Cliente;

class Proveedor {
private:
    string nombre;
    string direccion;
public:
    Proveedor(string n, string d) : nombre(n), direccion(d) {}
    string getNombre() { return nombre; }
    string getDireccion() { return direccion; }
};

class Producto {
private:
    string codigo;
    string descripcion;
    double precio;
    Proveedor* proveedor;
public:
    Producto(string c, string d, double p, Proveedor* prov) : codigo(c), descripcion(d), precio(p), proveedor(prov) {}
    string getDescripcion() { return descripcion; }
    double getPrecio() { return precio; }
};

class Pago {
private:
    double monto;
    string fecha;
public:
    Pago(double m, string f) : monto(m), fecha(f) {}
    void mostrarPago() {
        cout << "Pago: S/" << monto << ", Fecha: " << fecha << endl;
    }
};

class Venta {
private:
    string numeroFactura;
    string fecha;
    Cliente* cliente;
    vector<Producto*> productosVendidos;
public:
    Venta(string nf, string f, Cliente* c) : numeroFactura(nf), fecha(f), cliente(c) {}
    void agregarProducto(Producto* p) {
        productosVendidos.push_back(p);
    }
    void mostrarDetalleVenta() {
        cout << "Factura: " << numeroFactura << ", Fecha: " << fecha << endl;
        cout << "Productos vendidos: " << endl;
        for (auto p : productosVendidos) {
            cout << "- " << p->getDescripcion() << " (S/" << p->getPrecio() << ")" << endl;
        }
    }
};

class Cliente {
private:
    string nombre;
    string direccion;
    string telefono;
    vector<Venta*> compras;
    vector<Pago*> pagos;
public:
    Cliente(string n, string d, string t) : nombre(n), direccion(d), telefono(t) {}
    void agregarVenta(Venta* v) { compras.push_back(v); }
    void agregarPago(Pago* p) { pagos.push_back(p); }
    void mostrarHistorial() {
        cout << "Historial de compras y pagos de: " << nombre << endl;
        for (auto v : compras) { v->mostrarDetalleVenta(); }
        for (auto p : pagos) { p->mostrarPago(); }
    }
};

// --------------------- UNIVERSIDAD ---------------------
class Asignatura;

class Profesor {
private:
    string nombre;
    string direccion;
    string telefono;
    vector<Asignatura*> asignaturas;
public:
    Profesor(string n, string d, string t) : nombre(n), direccion(d), telefono(t) {}
    void agregarAsignatura(Asignatura* a) { asignaturas.push_back(a); }
    string getNombre() { return nombre; }
};

class Estudiante {
private:
    string nombre;
    string direccion;
    string matricula;
    map<Asignatura*, pair<double, int>> historial; // Asignatura -> (nota, faltas)
public:
    Estudiante(string n, string d, string m) : nombre(n), direccion(d), matricula(m) {}
    void matricular(Asignatura* a) { historial[a] = {0.0, 0}; }
    void registrarNota(Asignatura* a, double nota) { historial[a].first = nota; }
    void registrarFalta(Asignatura* a) { historial[a].second++; }
    void mostrarHistorial();
    string getNombre() { return nombre; }
};

class Asignatura {
private:
    string codigo;
    string nombre;
    string descripcion;
    Profesor* profesor;
public:
    Asignatura(string c, string n, string d, Profesor* p) : codigo(c), nombre(n), descripcion(d), profesor(p) {
        profesor->agregarAsignatura(this);
    }
    string getNombre() { return nombre; }
    string getCodigo() { return codigo; }
};

void Estudiante::mostrarHistorial() {
    cout << "Historial de " << nombre << ":" << endl;
    for (auto& entry : historial) {
        Asignatura* a = entry.first;
        double nota = entry.second.first;
        int faltas = entry.second.second;
        cout << "- " << a->getNombre() << " (" << a->getCodigo() << "): Nota: " << nota << ", Faltas: " << faltas << endl;
    }
}

// --------------------- MAIN ---------------------
int main() {
    // Tienda de ropa
    Proveedor* prov1 = new Proveedor("Moda S.A.", "Av. Principal 456");
    Producto* prod1 = new Producto("001", "Camisa blanca", 49.90, prov1);
    Producto* prod2 = new Producto("002", "Pantalón jeans", 89.90, prov1);
    Cliente* cliente1 = new Cliente("Carlos Ramos", "Calle Luna 321", "987654321");
    Venta* venta1 = new Venta("F001", "2025-03-30", cliente1);
    venta1->agregarProducto(prod1);
    venta1->agregarProducto(prod2);
    cliente1->agregarVenta(venta1);
    cliente1->agregarPago(new Pago(139.80, "2025-03-30"));
    cliente1->mostrarHistorial();

    // Universidad
    Profesor* prof1 = new Profesor("Dra. Sánchez", "Calle Sol 123", "999123456");
    Asignatura* asig1 = new Asignatura("MAT101", "Matemática", "Álgebra básica", prof1);
    Asignatura* asig2 = new Asignatura("HIS102", "Historia", "Historia del Perú", prof1);
    Estudiante* est1 = new Estudiante("Ana Pérez", "Av. Verde 123", "20251234");
    est1->matricular(asig1);
    est1->matricular(asig2);
    est1->registrarNota(asig1, 17.5);
    est1->registrarFalta(asig1);
    est1->registrarFalta(asig1);
    est1->registrarNota(asig2, 15.0);
    est1->mostrarHistorial();

    // Liberar memoria
    delete prov1;
    delete prod1;
    delete prod2;
    delete venta1;
    delete cliente1;
    delete prof1;
    delete asig1;
    delete asig2;
    delete est1;

    return 0;
}
