#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Producto {
protected:
    string nombre;
    double precio;
    int cantidad;
public:
    Producto(string n, double p, int c) : nombre(n), precio(p), cantidad(c) {}
    virtual double calcularValor() = 0;
    virtual void aplicarDescuento() = 0;
    virtual void mostrarInfo() = 0;
    virtual ~Producto() {}
};

class Electronico : public Producto {
public:
    Electronico(string n, double p, int c) : Producto(n, p, c) {}
    double calcularValor() override {
        return precio * cantidad;
    }
    void aplicarDescuento() override {
        precio = precio * 0.9; 
    }
    void mostrarInfo() override {
        cout << "Electrónico: " << nombre << ", Precio: $" << precio
             << ", Cantidad: " << cantidad << ", Valor total: $" << calcularValor() << endl;
    }
};

class Ropa : public Producto {
public:
    Ropa(string n, double p, int c) : Producto(n, p, c) {}
    double calcularValor() override {
        return precio * cantidad;
    }
    void aplicarDescuento() override {
        precio = precio * 0.8; 
    }
    void mostrarInfo() override {
        cout << "Ropa: " << nombre << ", Precio: $" << precio
             << ", Cantidad: " << cantidad << ", Valor total: $" << calcularValor() << endl;
    }
};

class Alimento : public Producto {
public:
    Alimento(string n, double p, int c) : Producto(n, p, c) {}
    double calcularValor() override {
        return precio * cantidad;
    }
    void aplicarDescuento() override {
        precio = precio * 0.95; 
    }
    void mostrarInfo() override {
        cout << "Alimento: " << nombre << ", Precio: $" << precio
             << ", Cantidad: " << cantidad << ", Valor total: $" << calcularValor() << endl;
    }
};

int main() {
    vector<Producto*> inventario;

    inventario.push_back(new Electronico("Smartphone", 500, 10));
    inventario.push_back(new Ropa("Camiseta", 20, 50));
    inventario.push_back(new Alimento("Manzana", 1, 200));

    cout << "Inventario antes del descuento:" << endl;
    for (Producto* p : inventario) {
        p->mostrarInfo();
    }

    cout << "\nAplicando descuentos..." << endl;
    for (Producto* p : inventario) {
        p->aplicarDescuento();
    }

    cout << "\nInventario después del descuento:" << endl;
    for (Producto* p : inventario) {
        p->mostrarInfo();
    }

    for (Producto* p : inventario) {
        delete p;
    }

    return 0;
}