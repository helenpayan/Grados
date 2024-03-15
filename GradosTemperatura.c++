#include <iostream>
#include <string>
#include <list>

class TemperaturaDia {
public:
    std::string fecha;
    std::string tempManana;
    std::string tempTarde;
    std::string tempNoche;

    TemperaturaDia(const std::string& f, 
    const std::string& m, const std::string& t,
    const std::string& n) : fecha(f), tempManana(m), tempTarde(t), tempNoche(n) {}

    void mostrarRegistro() const {
        std::cout << "Fecha: " << fecha
                  << " - Manana: " << tempManana
                  << ", Tarde: " << tempTarde
                  << ", Noche: " << tempNoche << '\n';
    }

    float calcularPromedioDiario() const {
        return (convertirTemperatura(tempManana) + convertirTemperatura(tempTarde) + convertirTemperatura(tempNoche)) / 3;
    }

    static float convertirTemperatura(const std::string& temp) {
        size_t pos = temp.find('°');
        if (pos != std::string::npos) {
            return std::stof(temp.substr(0, pos));
        } else {
            return std::stof(temp); // Si no hay símbolo de grados, se convierte directamente.
        }
    }
};

float calcularPromedioTotal(const std::list<TemperaturaDia>& registros) {
    float sumaTotal = 0;
    if (registros.empty()) {
        return 0;
    }
    for (const auto& registro : registros) {
        sumaTotal += registro.calcularPromedioDiario();
    }
    return sumaTotal / registros.size();
}

int main() {
    std::list<TemperaturaDia> registros;
    int opcion = 0;

    do {
        std::cout << "\nBienvenido, Por favor elija una opcion\n"
                  << "1. Registro de temperatura\n"
                  << "2. Mostrar registros\n"
                  << "3. Calcular promedio de temperatura del d1a\n"
                  << "4. Calcular promedio de temperatura de todos los registros\n"
                  << "5. Salir\n"
                  << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: {
                std::string fecha, manana, tarde, noche;
                std::cout << "Ingrese la fecha (D/M/Aa): ";
                std::getline(std::cin, fecha);
                std::cout << "Por favor escriba la temperatura de la mañana (Ejemplo.10°): ";
                std::getline(std::cin, manana);
                std::cout << "Por favor escriba la temperatura de la tarde (Ejemplo. 10°): ";
                std::getline(std::cin, tarde);
                std::cout << "Por favor escriba la temperatura de la noche (Ejemplo. 10°): ";
                std::getline(std::cin, noche);
                registros.push_back(TemperaturaDia(fecha, manana, tarde, noche));
                break;
            }
            case 2:
                for (const auto& registro : registros) {
                    registro.mostrarRegistro();
                }
                break;
            case 3: {
                std::string fechaBusqueda;
                std::cout << "Escriba la fecha del registro para calcular el promedio: ";
                std::getline(std::cin, fechaBusqueda);
                bool encontrado = false;
                for (const auto& registro : registros) {
                    if (registro.fecha == fechaBusqueda) {
                        std::cout << "El promedio de temperatura para " << fechaBusqueda << " es: "
                                  << registro.calcularPromedioDiario() << "°C\n";
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "No se encontro un registro para la fecha proporcionada.\n";
                }
                break;
            }
            case 4:
                std::cout << "El promedio total de temperatura para todos los registros es: "
                          << calcularPromedioTotal(registros) << "°C\n";
                break;
            case 5:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion no válida.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}

