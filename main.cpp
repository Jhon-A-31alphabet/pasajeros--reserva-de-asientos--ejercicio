#include <iostream>
#include <string>
#include <vector> // los vectores tambien son arrays pero no provocan fuga de memoria en c y c++.
#include <iomanip>  // permite formatear la salida de la consola....
#include <limits>

using namespace std;

struct Pasajero {
    string nombre;
    int numeroAsiento;
    Pasajero() : nombre(""), numeroAsiento(-1) {}
    Pasajero(const string& n, int a) : nombre(n), numeroAsiento(a) {}
};

class Vuelo {
private:
    int capacidadTotal;
    int capacidad1, capacidad2, capacidad3;
    double precio1, precio2, precio3;
    vector<Pasajero> clase1;
    vector<Pasajero> clase2;
    vector<Pasajero> clase3;
public:
    Vuelo(int capacidad, double p1, double p2, double p3)
        : capacidadTotal(capacidad), precio1(p1), precio2(p2), precio3(p3)
    {
        // Calcular cupos por porcentajes: 15%, 25%, 60% y asi sucesivamente......
        capacidad1 = (int) (capacidadTotal * 0.15 + 0.5); // redondeo
        capacidad2 = (int) (capacidadTotal * 0.25 + 0.5);
        capacidad3 = capacidadTotal - capacidad1 - capacidad2;
        clase1.reserve(capacidad1);
        clase2.reserve(capacidad2);
        clase3.reserve(capacidad3);
    }

    bool hayAsientosDisponibles() const {
        return (int)clase1.size() < capacidad1 ||
               (int)clase2.size() < capacidad2 ||
               (int)clase3.size() < capacidad3;
    }

    bool venderBoleto(int clase, const string& nombre) {
        if (clase == 1) {
            if ((int)clase1.size() >= capacidad1) return false;
            int nro = asignarNumeroAsiento(1);
            clase1.emplace_back(nombre, nro);
            return true;
        } else if (clase == 2) {
            if ((int)clase2.size() >= capacidad2) return false;
            int nro = asignarNumeroAsiento(2);
            clase2.emplace_back(nombre, nro);
            return true;
        } else if (clase == 3) {
            if ((int)clase3.size() >= capacidad3) return false;
            int nro = asignarNumeroAsiento(3);
            clase3.emplace_back(nombre, nro);
            return true;
        }
        return false;
    }

    int asignarNumeroAsiento(int clase) const {

        if (clase == 1) return (int)clase1.size() + 1;
        if (clase == 2) return capacidad1 + (int)clase2.size() + 1;
        return capacidad1 + capacidad2 + (int)clase3.size() + 1;
    }

    void mostrarResumenVentas() const {
        cout << "\nResumen de ventas:\n";
        cout << "Clase 1 (Primera) - Vendidos: " << clase1.size()
             << " / " << capacidad1 << "\n";
        cout << "Clase 2 (Segunda)  - Vendidos: " << clase2.size()
             << " / " << capacidad2 << "\n";
        cout << "Clase 3 (Tercera) - Vendidos: " << clase3.size()
             << " / " << capacidad3 << "\n";
    }

    void mostrarListaPasajerosPorClase() const {
        cout << fixed << setprecision(0);
        cout << "\nPasajeros - Clase 1:\n";
        for (const auto& p : clase1)
            cout << "  Asiento " << p.numeroAsiento << " - " << p.nombre << "\n";
        cout << "\nPasajeros - Clase 2:\n";
        for (const auto& p : clase2)
            cout << "  Asiento " << p.numeroAsiento << " - " << p.nombre << "\n";
        cout << "\nPasajeros - Clase 3:\n";
        for (const auto& p : clase3)
            cout << "  Asiento " << p.numeroAsiento << " - " << p.nombre << "\n";
    }

    void mostrarIngresosEstimados() const {
        double ingreso1 = clase1.size() * precio1;
        double ingreso2 = clase2.size() * precio2;
        double ingreso3 = clase3.size() * precio3;
        double total = ingreso1 + ingreso2 + ingreso3;

        cout << fixed << setprecision(2);
        cout << "\nIngresos estimados por clase:\n";
        cout << "Clase 1: $" << ingreso1 << " (" << clase1.size() << " boletos x $" << precio1 << ")\n";
        cout << "Clase 2: $" << ingreso2 << " (" << clase2.size() << " boletos x $" << precio2 << ")\n";
        cout << "Clase 3: $" << ingreso3 << " (" << clase3.size() << " boletos x $" << precio3 << ")\n";
        cout << "Total estimado: $" << total << "\n";
    }

    int getCapacidad1() const { return capacidad1; }
    int getCapacidad2() const { return capacidad2; }
    int getCapacidad3() const { return capacidad3; }
};

int pedirEntero(const string& prompt, int minVal, int maxVal) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= minVal && v <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cout << "Entrada inválida. Intenta de nuevo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string pedirLinea(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int main() {
    cout << "Gestión de Pasajeros por Clase - Consola\n";

    int capacidad;
    cout << "Ingrese la capacidad total del avión: ";
    while (!(cin >> capacidad) || capacidad <= 0) {
        cout << "Capacidad inválida. Introduce un número entero positivo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    double precio1 = 500.0; // primera
    double precio2 = 300.0; // segunda
    double precio3 = 100.0; // tercera

    Vuelo vuelo(capacidad, precio1, precio2, precio3);

    cout << "\nDistribución de asientos aplicada:\n";
    cout << "  Primera: " << vuelo.getCapacidad1() << " asientos\n";
    cout << "  Segunda: " << vuelo.getCapacidad2() << " asientos\n";
    cout << "  Tercera: " << vuelo.getCapacidad3() << " asientos\n";

    while (vuelo.hayAsientosDisponibles()) {
        cout << "\nMenú:\n";
        cout << "  1) Vender boleto\n";
        cout << "  2) Mostrar resumen de ventas\n";
        cout << "  3) Mostrar lista de pasajeros por clase\n";
        cout << "  4) Mostrar ingresos estimados\n";
        cout << "  5) Salir\n";

        int opcion = pedirEntero("Elija una opción (1-5): ", 1, 5);
        if (opcion == 1) {
            cout << "\nVender boleto\n";
            cout << "Elija clase:\n";
            cout << " \033[32m 1) Primera \033[0m \n";   // coloreado con verde por primera clase $$$$$
            cout << "  2) Segunda\n";
            cout << "  3) Tercera\n";
            int clase = pedirEntero("Clase (1-3): ", 1, 3);
            string nombre = pedirLinea("Nombre completo del pasajero: ");
            if (nombre.empty()) {
                cout << "Nombre vacío. Venta cancelada.\n";
                continue;
            }
            bool ok = vuelo.venderBoleto(clase, nombre);
            if (ok) {
                cout << "\033[41;37m Boleto vendido correctamente en clase \033[0m" << clase << ".\n";  //este  fue coloreado con el fondo rojo indicando que se vendio
            } else {
                cout << "No hay asientos disponibles en esa clase.\n";
            }
        } else if (opcion == 2) {
            vuelo.mostrarResumenVentas();
        } else if (opcion == 3) {
            vuelo.mostrarListaPasajerosPorClase();
        } else if (opcion == 4) {
            vuelo.mostrarIngresosEstimados();
        } else if (opcion == 5) {
            cout << "Saliendo...\n";
            break;
        }
    }

    if (!vuelo.hayAsientosDisponibles()) {
        cout << "\nEl avión está completo. No se pueden vender más boletos.\n";
        vuelo.mostrarResumenVentas();
        vuelo.mostrarIngresosEstimados();
    }

    return 0;
}

