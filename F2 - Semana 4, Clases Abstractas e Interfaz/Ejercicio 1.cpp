#include <iostream>
#include <cmath>
using namespace std;

class Figura {
public:
    // Métodos abstractos (virtuales puros)
    virtual void dibujar() = 0;
    virtual double calcularArea() = 0;

    // Destructor virtual
    virtual ~Figura() {}
};

class Circulo : public Figura {
private:
    double radio;

public:
    Circulo(double r) : radio(r) {}

    void dibujar() override {
        cout << "Dibujando un círculo..." << endl;
    }

    double calcularArea() override {
        return M_PI * radio * radio;
    }
};

class Rectangulo : public Figura {
private:
    double base, altura;

public:
    Rectangulo(double b, double h) : base(b), altura(h) {}

    void dibujar() override {
        cout << "Dibujando un rectángulo..." << endl;
    }

    double calcularArea() override {
        return base * altura;
    }
};

class Triangulo : public Figura {
private:
    double base, altura;

public:
    Triangulo(double b, double h) : base(b), altura(h) {}

    void dibujar() override {
        cout << "Dibujando un triángulo..." << endl;
    }

    double calcularArea() override {
        return (base * altura) / 2;
    }
};

int main() {
    Figura* fig1 = new Circulo(5.0);
    Figura* fig2 = new Rectangulo(4.0, 6.0);
    Figura* fig3 = new Triangulo(3.0, 8.0);

    // Uso polimórfico
    fig1->dibujar();
    cout << "Área del círculo: " << fig1->calcularArea() << "\n\n";

    fig2->dibujar();
    cout << "Área del rectángulo: " << fig2->calcularArea() << "\n\n";

    fig3->dibujar();
    cout << "Área del triángulo: " << fig3->calcularArea() << "\n";

    // Liberar memoria
    delete fig1;
    delete fig2;
    delete fig3;

    return 0;
}
