#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Animal{
public:
    virtual void comer() = 0;
    virtual void dormir() = 0;
    virtual void moverse() = 0;
    void mostrarInfo(){
        comer();
        dormir();
        moverse();
        cout<<"----------------------\n";
    }  
    virtual ~Animal() {};
};
class Mamifero: public Animal{
private:
    int patas;
    string piel;
    string especie;
public:
    Mamifero(int p, string pj, string e): patas(p), piel(pj), especie(e){};
    void comer() override{
        cout<<"El mamifero "<<especie<<" está comiendo.\n";
    }
    void dormir() override{
        cout<<"El mamifero "<<especie<<" está durmiendo.\n";
    }
    void moverse() override{
        cout<<"El mamifero "<<especie<<" camina con "<<patas<<" patas.\n";
    }
};

class Ave: public Animal{
private:
    int patas;
    int alas;
    string piel;
    string especie;
public: 
    Ave(int p, int a, string pj, string e): patas(p), alas(a), piel(pj), especie(e){};
    void comer() override{
        cout<<"El ave "<<especie<<" está comiendo.\n";
    }
    void dormir() override{
        cout<<"El ave "<<especie<<" está durmiendo en su nido.\n";
    }
    void moverse() override{
        cout<<"El ave "<<especie<<" vuela con "<<alas<<" alas.\n";
    }
};   

class Reptil: public Animal{
private:
    int patas;
    string piel;
    string especie;
public: 
    Reptil(int p, string pj, string e): patas(p), piel(pj), especie(e){};
    void comer() override{
        cout<<"El reptil "<<especie<<" está comiendo.\n";
    }
    void dormir() override{
        cout<<"El reptil "<<especie<<" está durmiendo.\n";
    }
    void moverse() override{
        if (patas == 0){
            cout<<"El reptil "<<especie<<" se arrastra.\n";
        }else{
            cout<<"El reptil "<<especie<<" camina en "<<patas<<" patas.\n";    
        }
    }
};

int main()
{
    vector<Animal*>zoologico;
    
    zoologico.push_back(new Mamifero(4,"pelaje","Ornitorrinco"));
    zoologico.push_back(new Ave(2,2,"plumas", "paloma"));
    zoologico.push_back(new Reptil(0, "escamas", "Serpiente"));
    
    for(Animal* animal: zoologico){
        animal->mostrarInfo();
    }
    
    for(Animal* animal:zoologico){
        delete animal;
    }
    return 0;
};
