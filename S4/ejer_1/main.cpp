#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Libro; 
class Usuario;

class Autor {
private:
    string nombre;
    string nacionalidad;
    vector<Libro*> libros;
public:
    Autor(string n, string nac) : nombre(n), nacionalidad(nac) {}

    void agregarLibro(Libro* libro) {
        libros.push_back(libro);
    }

    string getNombre() { return nombre; }
    string getNacionalidad() { return nacionalidad; }
};

class Libro {
private:
    string isbn;
    string titulo;
    int anioPublicacion;
    int cantidadEjemplares;
    Autor* autor;
public:
    Libro(string i, string t, int a, int c, Autor* aut) : isbn(i), titulo(t), anioPublicacion(a), cantidadEjemplares(c), autor(aut) {
        autor->agregarLibro(this);
    }

    string getTitulo() { return titulo; }
    string getISBN() { return isbn; }
    Autor* getAutor() { return autor; }
};

class Prestamo {
private:
    Libro* libro;
    string fechaPrestamo;
    string fechaDevolucion;
public:
    Prestamo(Libro* l, string fp, string fd) : libro(l), fechaPrestamo(fp), fechaDevolucion(fd) {}

    void mostrarDetalle() {
        cout << "Libro: " << libro->getTitulo() << ", Fecha préstamo: " << fechaPrestamo << ", Fecha devolución: " << fechaDevolucion << endl;
    }
};

class Usuario {
private:
    string nombre;
    string direccion;
    string telefono;
    vector<Prestamo*> prestamos;
public:
    Usuario(string n, string d, string t) : nombre(n), direccion(d), telefono(t) {}

    void agregarPrestamo(Prestamo* prestamo) {
        prestamos.push_back(prestamo);
    }

    void mostrarPrestamos() {
        cout << "Prestamos de: " << nombre << endl;
        for (auto p : prestamos) {
            p->mostrarDetalle();
        }
    }
};

int main() {
    Autor* autor1 = new Autor("Gabriel García Márquez", "Colombiano");
    Libro* libro1 = new Libro("978-3-16-148410-0", "Cien años de soledad", 1967, 3, autor1);

    Usuario* usuario1 = new Usuario("Laura Perez", "Calle Falsa 123", "987654321");
    Prestamo* prestamo1 = new Prestamo(libro1, "2025-03-01", "2025-03-15");

    usuario1->agregarPrestamo(prestamo1);
    usuario1->mostrarPrestamos();

    // Liberar memoria
    delete prestamo1;
    delete libro1;
    delete autor1;
    delete usuario1;

    return 0;
}
