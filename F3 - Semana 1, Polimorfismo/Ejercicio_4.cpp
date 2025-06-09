#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Personaje
{
public:
    virtual void atacar() = 0;
    virtual void defender() = 0;
    virtual void habilidadEspecial() = 0;
    virtual string getNombre() = 0;
};

class Guerrero : public Personaje
{
public:
    void atacar()
    {
        cout << "El Guerrero lanza un fuerte golpe con su espada." << endl;
    }
    void defender()
    {
        cout << "El Guerrero bloquea con su escudo." << endl;
    }
    void habilidadEspecial()
    {
        cout << "El Guerrero usa Furia de Batalla, aumentando su fuerza." << endl;
    }
    string getNombre()
    {
        return "Guerrero";
    }
};

class Mago : public Personaje
{
public:
    void atacar()
    {
        cout << "El Mago lanza una bola de fuego." << endl;
    }
    void defender()
    {
        cout << "El Mago crea un escudo mágico." << endl;
    }
    void habilidadEspecial()
    {
        cout << "El Mago usa Tormenta Arcana, dañando a todos los enemigos." << endl;
    }
    string getNombre()
    {
        return "Mago";
    }
};

class Arquero : public Personaje
{
public:
    void atacar()
    {
        cout << "El Arquero dispara una flecha precisa." << endl;
    }
    void defender()
    {
        cout << "El Arquero esquiva rápidamente el ataque." << endl;
    }
    void habilidadEspecial()
    {
        cout << "El Arquero usa Lluvia de Flechas sobre sus enemigos." << endl;
    }
    string getNombre()
    {
        return "Arquero";
    }
};

int main()
{
    vector<Personaje *> personajes;
    personajes.push_back(new Guerrero());
    personajes.push_back(new Mago());
    personajes.push_back(new Arquero());

    int opcionPersonaje;
    int accion;

    while (true)
    {
        cout << "\n Selecciona un personaje " << endl;
        for (int i = 0; i < personajes.size(); i++)
        {
            cout << i + 1 << ". " << personajes[i]->getNombre() << endl;
        }
        cout << personajes.size() + 1 << ". Salir" << endl;
        cout << "Opcion: ";
        cin >> opcionPersonaje;

        if (opcionPersonaje < 1 || opcionPersonaje > personajes.size())
            break;

        Personaje *p = personajes[opcionPersonaje - 1];

        cout << "\n Acciones para " << p->getNombre() << " " << endl;
        cout << "1. Atacar" << endl;
        cout << "2. Defender" << endl;
        cout << "3. Habilidad Especial" << endl;
        cout << "Opcion: ";
        cin >> accion;

        switch (accion)
        {
        case 1:
            p->atacar();
            break;
        case 2:
            p->defender();
            break;
        case 3:
            p->habilidadEspecial();
            break;
        default:
            cout << "Accion invalida." << endl;
        }
    }

    for (int i = 0; i < personajes.size(); i++)
    {
        delete personajes[i];
    }

    cout << "Juego finalizado." << endl;
    return 0;
}
