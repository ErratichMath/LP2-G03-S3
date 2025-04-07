#include <iostream>
#include <vector>
#include <string>
using namespace std;

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

    void agregarVenta(Venta* v) {
        compras.push_back(v);
    }

    void agregarPago(Pago* p) {
        pagos.push_back(p);
    }

    void mostrarHistorial() {
        cout << "Historial de compras y pagos de: " << nombre << endl;
        for (auto v : compras) {
            v->mostrarDetalleVenta();
        }
        for (auto p : pagos) {
            p->mostrarPago();
        }
    }
};

int main() {
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

    // Liberar memoria
    delete venta1;
    delete prod1;
    delete prod2;
    delete prov1;
    delete cliente1;

    return 0;
}
