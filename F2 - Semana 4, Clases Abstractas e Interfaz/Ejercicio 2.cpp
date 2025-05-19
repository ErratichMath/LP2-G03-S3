#include <iostream>
#include<string>
using namespace std;

class Reproductor{
public:
    //metodos virtuales
    virtual void reproducir() = 0;
    virtual void pausar() = 0;
    virtual void detener() = 0;
    virtual string getAudio() = 0; //adicional
    
    //destructor
    virtual ~Reproductor() {}
};

class ReproductorMP3 : public Reproductor {
private:
    string audio;
public:
    ReproductorMP3(string a) : audio(a) {}
    
    void reproducir() override {
        cout<<"Reproduciendo: "<<audio<<endl;
    }
    
    void pausar() override {
        cout<<"Se pauso: "<<audio<<endl;
    }
    
    void detener() override {
        cout<<"Se detuvo el audio: "<<audio<<endl;
    }
    
    string getAudio() override {
        return audio;
    }
};

int main()
{
    ReproductorMP3* audio1 = new ReproductorMP3("Música_A.mp3");
    ReproductorMP3* audio2 = new ReproductorMP3("Música_B.mp3");
    
    cout <<"Ahora se reproducirá: " << audio1->getAudio() <<endl;
    
    audio1->reproducir();
    audio1-> pausar();
    audio1-> detener();
    
    cout <<"\nAhora se reproducirá: " << audio2->getAudio() <<endl;
    audio2->reproducir();
    audio2-> pausar();
    audio2-> detener();
    
    delete audio1;
    delete audio2;
    return 0;
};
