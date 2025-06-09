#include <iostream>
using namespace std;
class Figura{
public:
    virtual void calcularArea() = 0;
    virtual void perimetro() = 0;
    void mostrarInfo(){
        calcularArea();
        perimetro();
    };
    virtual ~Figura(){};
};
class Circulo : public Figura{
private:
    double radio;
    double diametro;
public:
    Circulo(double r, double d) : radio(r), diametro(d){};
    void calcularArea() override{
        cout<<"El area del circulo es: "<< 3.1416*(radio*radio)<<endl;
    }
    void perimetro() override{
        if (diametro > 0){
            cout<<"El perimetro del circulo es: "<<3.1416*diametro<<endl;    
        }else{
            cout<<"El perimetro del circulo es: "<<2*3.1416*radio<<endl;
        }
    }
};
class Rectangulo : public Figura{
private:
    double base;
    double altura;
public:
    Rectangulo(double b, double a) : base(b), altura(a){};
    void calcularArea() override{
        cout<<"El area del rectangulo es: "<<base*altura<<endl;
    }
    void perimetro() override{
        cout<<"El perimetro del rectangulo es: "<<2*(base+altura)<<endl;
    }
};
class Triangulo : public Figura{
private:
    double base;
    double altura;
    double lado_1;
    double lado_2;
public:
    Triangulo(double b, double a, double l1, double l2) : base(b), altura(a), lado_1(l1), lado_2(l2){}
    void calcularArea() override{
        cout<<"El area del triángulo es: "<<(base*altura)/2<<endl;
    }
    void perimetro() override{
        cout<<"El perimetro del triángulo es: "<<base+lado_1+lado_2<<endl;
    }
};

int main()
{
    Figura* fig1 = new Circulo(3,0);
    Figura* fig2 = new Circulo(3,6);
    Figura* fig3 = new Rectangulo(4,2);
    Figura* fig4 = new Triangulo(6,2,3,5);
    
    fig1 -> mostrarInfo();
    fig2 -> mostrarInfo();
    fig3 -> mostrarInfo();
    fig4 -> mostrarInfo();
    
    delete fig1;
    delete fig2;
    delete fig3;
    delete fig4;
    return 0;
};
