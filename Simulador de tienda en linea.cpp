#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Producto {
public:
    int id;
    string nombre;
    double precio;
    int stock;

    Producto() {}
    Producto(int i, string n, double p, int s) : id(i), nombre(n), precio(p), stock(s) {}
};

class Carrito {
public:
    map<int, int> items;

    void agregarProducto(int id) {
        items[id]++;
    }

    void quitarProducto(int id) {
        if (items.count(id)) {
            items[id]--;
            if (items[id] <= 0) items.erase(id);
        }
    }

    void vaciar() {
        items.clear();
    }

    void mostrar(const map<int, Producto>& inventario) {
        if (items.empty()) {
            cout << "Carrito vacío.\n";
            return;
        }
        for (auto& item : items) {
            int id = item.first;
            int cantidad = item.second;
            cout << inventario.at(id).nombre << " x" << cantidad << " - S/" << inventario.at(id).precio << " cada uno\n";
        }
    }
};

class Usuario {
public:
    string nombre;
    string dni;
    string celular;
    string tipo;
    Carrito carrito;
    map<int, int> historial;

    Usuario() {}
    Usuario(string nom, string d, string c, string t) : nombre(nom), dni(d), celular(c), tipo(t) {}

    virtual double aplicarDescuento(double total) {
        return total;
    }

    void actualizarDatos(string n, string d, string c) {
        nombre = n;
        dni = d;
        celular = c;
    }

    void mostrarDatos() {
        cout << "\n--- Datos del usuario ---\n";
        cout << "Nombre: " << nombre << "\nDNI: " << dni << "\nCelular: " << celular << "\nTipo: " << tipo << endl;
    }
};

class ClienteRegular : public Usuario {
public:
    ClienteRegular(string nom, string d, string c) : Usuario(nom, d, c, "regular") {}
};

class ClientePremium : public Usuario {
public:
    ClientePremium(string nom, string d, string c) : Usuario(nom, d, c, "premium") {}

    double aplicarDescuento(double total) {
        return total * 0.9;
    }
};

class Sistema {
public:
    map<string, Usuario*> usuarios;
    map<int, Producto> inventario;
    map<int, double> ventasPorProducto;
    map<string, double> ventasPorUsuario;
    int nextId = 1;

    void registrarUsuario(string nombre, string dni, string celular, string tipo) {
        if (usuarios.count(dni) == 0) {
            if (tipo == "premium")
                usuarios[dni] = new ClientePremium(nombre, dni, celular);
            else
                usuarios[dni] = new ClienteRegular(nombre, dni, celular);
        }
    }

    Usuario* iniciarSesion(string dni) {
        if (usuarios.count(dni)) return usuarios[dni];
        return nullptr;
    }

    void agregarProductoInventario(string nombre, double precio, int stock) {
        inventario[nextId] = Producto(nextId, nombre, precio, stock);
        nextId++;
    }

    void actualizarInventario(int id, int nuevoStock, double nuevoPrecio) {
        if (inventario.count(id)) {
            inventario[id].stock = nuevoStock;
            inventario[id].precio = nuevoPrecio;
        }
    }

    void mostrarInventario() {
        for (auto& par : inventario) {
            cout << par.first << ". " << par.second.nombre << " - S/" << par.second.precio << " - Stock: " << par.second.stock << endl;
        }
    }

    void confirmarCompra(Usuario* u) {
        double total = 0;
        for (auto& item : u->carrito.items) {
            int id = item.first;
            int cantidad = item.second;
            if (inventario[id].stock >= cantidad) {
                total += inventario[id].precio * cantidad;
            }
        }
        total = u->aplicarDescuento(total);
        for (auto& item : u->carrito.items) {
            int id = item.first;
            int cantidad = item.second;
            inventario[id].stock -= cantidad;
            u->historial[id] += cantidad;
            ventasPorProducto[id] += inventario[id].precio * cantidad;
        }
        ventasPorUsuario[u->dni] += total;
        u->carrito.vaciar();
        cout << "Total a pagar: S/" << total << endl;
    }
};

bool validarDNI(const string& dni) {
    return dni.length() == 8 && all_of(dni.begin(), dni.end(), ::isdigit);
}

int main() {
    Sistema sistema;

    sistema.registrarUsuario("Admin", "00000000", "000000000", "admin");
    sistema.agregarProductoInventario("Laptop", 3000, 10);
    sistema.agregarProductoInventario("Mouse", 50, 100);
    sistema.agregarProductoInventario("Teclado", 120, 80);
    sistema.agregarProductoInventario("Monitor", 850, 40);
    sistema.agregarProductoInventario("USB 64GB", 90, 150);
    sistema.agregarProductoInventario("Audífonos", 150, 60);
    sistema.agregarProductoInventario("Webcam", 250, 30);

    Usuario* u = nullptr;
    string dni;

    while (true) {
        cout << "\n--- Iniciar Sesión ---\n";
        cout << "Ingrese DNI de 8 dígitos (o 'salir' para terminar): ";
        cin >> dni;

        if (dni == "salir") break;

        if (!validarDNI(dni)) {
            cout << "DNI inválido. Debe tener exactamente 8 dígitos.\n";
            continue;
        }

        u = sistema.iniciarSesion(dni);
        if (!u) {
            string nombre, celular, tipo;
            cout << "Nuevo usuario. Ingrese nombre: "; cin >> nombre;
            cout << "Celular: "; cin >> celular;
            cout << "Tipo (regular/premium): "; cin >> tipo;
            sistema.registrarUsuario(nombre, dni, celular, tipo);
            u = sistema.iniciarSesion(dni);
        } else {
            u->mostrarDatos();
        }

        int opcion;
        do {
            cout << "\n1. Ver productos\n2. Agregar producto al carrito\n3. Quitar producto\n4. Ver carrito\n5. Confirmar compra\n6. Ingresar otro usuario\n7. Salir\nOpcion: ";
            cin >> opcion;
            if (opcion == 1) {
                sistema.mostrarInventario();
            } else if (opcion == 2) {
                int id; cout << "ID producto: "; cin >> id;
                u->carrito.agregarProducto(id);
            } else if (opcion == 3) {
                int id; cout << "ID producto: "; cin >> id;
                u->carrito.quitarProducto(id);
            } else if (opcion == 4) {
                u->carrito.mostrar(sistema.inventario);
            } else if (opcion == 5) {
                sistema.confirmarCompra(u);
            } else if (opcion == 6) {
                break;
            }
        } while (opcion != 7);

        if (opcion == 7) break;
    }

    return 0;
}
