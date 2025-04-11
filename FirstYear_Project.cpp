#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para sort
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

using namespace std;

void clear() {
    system(CLEAR_COMMAND);
}

struct Articulo {
    string nombre;
    string descripcion;
    double precio;
};

class Departamento {
public:
    string nombre;
    vector<Articulo> articulos;

    Departamento(const string& nombre, const vector<Articulo>& articulos)
        : nombre(nombre), articulos(articulos) {}
};

struct Carrito {
    string nombre;
    string descripcion;
    double precio;
};

class UserInfo {
public:
    int numeroCuenta;
    string nombreApellido;
    int edad;
    string sexo;
    string direccion;
    int codigoPostal;
    int puntosDisponibles;
    vector<Carrito> carrito;

    void obtenerInformacionUsuario() {
        clear();
        cout << "Ingrese su número de cuenta: ";
        while (!(cin >> numeroCuenta)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Intente de nuevo: ";
        }

        cin.ignore();
        cout << "Ingrese su nombre y apellido: ";
        getline(cin, nombreApellido);

        do {
            cout << "Ingrese su edad (entre 18 y 99 años): ";
            cin >> edad;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                edad = 0;
                cout << "Entrada inválida. ";
                continue;
            }
            if (edad < 18) {
                cout << "Debe ser mayor de edad para ingresar." << endl;
            } else if (edad > 99) {
                cout << "Edad fuera del rango permitido. Intente de nuevo." << endl;
            }
        } while (edad < 18 || edad > 99);

        cin.ignore();
        cout << "Ingrese su sexo (hombre/mujer): ";
        getline(cin, sexo);
        for (char& c : sexo) c = tolower(c);
        while (sexo != "hombre" && sexo != "mujer") {
            cout << "Sexo no válido. Ingrese hombre o mujer: ";
            getline(cin, sexo);
            for (char& c : sexo) c = tolower(c);
        }

        cout << "Ingrese su dirección: ";
        getline(cin, direccion);

        cout << "Ingrese su código postal: ";
        while (!(cin >> codigoPostal)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Código inválido. Intente de nuevo: ";
        }

        cout << "Ingrese sus puntos disponibles: ";
        while (!(cin >> puntosDisponibles)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Número inválido. Intente de nuevo: ";
        }
    }
};

void ordenarPorNombre(vector<Departamento>& tienda) {
    sort(tienda.begin(), tienda.end(), [](const Departamento& a, const Departamento& b) {
        return a.nombre < b.nombre;
    });
}

bool buscarYAgregarArticulo(UserInfo& usuario, const vector<Departamento>& tienda, const string& nombreArticulo) {
    for (const auto& depto : tienda) {
        for (const auto& articulo : depto.articulos) {
            if (articulo.nombre == nombreArticulo) {
                usuario.carrito.push_back({articulo.nombre, articulo.descripcion, articulo.precio});
                cout << "Artículo agregado al carrito." << endl;
                return true;
            }
        }
    }
    return false;
}

int main() {
    clear();
    UserInfo usuario;
    bool infoIngresada = false;

    vector<Departamento> tienda = {
        {"Electrodomésticos", {
            {"Refrigerador", "Refrigerador con tecnología de ahorro de energía", 15000.0},
            {"Lavadora", "Lavadora de carga frontal con múltiples funciones", 12000.0},
            {"Licuadora", "Licuadora de alta potencia con múltiples velocidades", 1500.0}
        }},
        {"Hogar", {
            {"Sofá", "Sofá cómodo y elegante para la sala de estar", 8000.0},
            {"Mesa de Centro", "Mesa de centro de madera maciza", 2000.0},
            {"Lámpara", "Lámpara de pie moderna para iluminación ambiental", 1500.0}
        }},
        {"Ropa", {
            {"Camisa", "Camisa de algodón con diseño clásico", 1000.0},
            {"Pantalón", "Pantalón vaquero de corte moderno", 1200.0},
            {"Vestido", "Vestido elegante para ocasiones especiales", 2500.0}
        }},
        {"Calzado", {
            {"Zapatos Deportivos", "Zapatos deportivos para correr", 1500.0},
            {"Botas de Invierno", "Botas resistentes al agua para el invierno", 2000.0},
            {"Zapatillas", "Zapatillas cómodas y elegantes", 1200.0}
        }}
    };

    ordenarPorNombre(tienda);

    int opcion;
    do {
        cout << "\nMENU\n";
        cout << (infoIngresada ? "1. Ver información del usuario\n" : "1. Ingresar información del usuario\n");
        cout << "2. Departamentos y Artículos\n3. Puntos\n4. Carrito\n5. Salir del sistema\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                clear();
                if (!infoIngresada) {
                    usuario.obtenerInformacionUsuario();
                    infoIngresada = true;
                    cout << "Información del usuario ingresada exitosamente." << endl;
                } else {
                    cout << "\nInformación del Usuario:\n";
                    cout << "Número de Cuenta: " << usuario.numeroCuenta << endl;
                    cout << "Nombre y Apellido: " << usuario.nombreApellido << endl;
                    cout << "Edad: " << usuario.edad << " años\nSexo: " << usuario.sexo << endl;
                    cout << "Dirección: " << usuario.direccion << "\nCódigo Postal: " << usuario.codigoPostal << endl;
                    cout << "Puntos Disponibles: " << usuario.puntosDisponibles << endl;
                }
                break;

            case 2:
                clear();
                if (!infoIngresada) {
                    cout << "Por favor ingresa tus datos para navegar." << endl;
                } else {
                    for (const auto& depto : tienda) {
                        cout << "\n" << depto.nombre << ":\n";
                        for (const auto& articulo : depto.articulos) {
                            cout << " - " << articulo.nombre << ": " << articulo.descripcion << " - Precio: $" << articulo.precio << endl;
                        }

                        cout << "¿Deseas agregar algún artículo de este departamento al carrito? (s/n): ";
                        char respuesta;
                        cin >> respuesta;
                        cin.ignore();
                        if (tolower(respuesta) == 's') {
                            cout << "Ingresa el nombre del artículo que deseas agregar: ";
                            string nombreArticulo;
                            getline(cin, nombreArticulo);

                            if (!buscarYAgregarArticulo(usuario, tienda, nombreArticulo)) {
                                cout << "No se encontró el artículo en ninguna sección." << endl;
                            }
                        }
                    }
                }
                break;

            case 3:
                clear();
                if (!infoIngresada) {
                    cout << "Por favor ingresa tus datos para navegar." << endl;
                } else {
                    cout << "\nPuntos y Descuentos:\n";
                    cout << "Puntos disponibles: " << usuario.puntosDisponibles << endl;
                    double equivalente = usuario.puntosDisponibles / 10.0;
                    cout << "100 puntos equivalen a 10 pesos.\n";
                    cout << "Tus puntos equivalen a: $" << equivalente << endl;
                }
                break;

            case 4:
                clear();
                if (!infoIngresada) {
                    cout << "Por favor ingresa tus datos para navegar." << endl;
                } else {
                    cout << "\nCarrito de Compras:\n";
                    double subtotal = 0.0;
                    for (const auto& item : usuario.carrito) {
                        cout << "Nombre: " << item.nombre << " - Descripción: " << item.descripcion << " - Precio: $" << item.precio << endl;
                        subtotal += item.precio;
                    }
                    cout << "\nSubtotal: $" << subtotal << endl;
                    cout << "Puntos disponibles: " << usuario.puntosDisponibles << endl;

                    cout << "¿Deseas utilizar tus puntos disponibles? (s/n): ";
                    char usarPuntos;
                    cin >> usarPuntos;
                    cin.ignore();

                    if (tolower(usarPuntos) == 's') {
                        cout << "Ingrese la cantidad de puntos que desea utilizar: ";
                        int puntosUsar;
                        cin >> puntosUsar;
                        cin.ignore();

                        double descuento = puntosUsar * 0.10;
                        if (descuento <= subtotal) {
                            subtotal -= descuento;
                            usuario.puntosDisponibles -= puntosUsar;
                        } else {
                            cout << "El descuento excede el subtotal. ¿Deseas usar todos los puntos disponibles? (s/n): ";
                            char usarTodos;
                            cin >> usarTodos;
                            cin.ignore();

                            if (tolower(usarTodos) == 's') {
                                puntosUsar = static_cast<int>(subtotal / 0.10);
                                subtotal -= puntosUsar * 0.10;
                                usuario.puntosDisponibles -= puntosUsar;
                            } else {
                                cout << "No se aplicaron puntos." << endl;
                            }
                        }
                    }

                    subtotal = max(0.0, subtotal);
                    cout << "\nTotal a pagar: $" << subtotal << endl;
                    cout << "Puntos restantes: " << usuario.puntosDisponibles << endl;
                    cout << "\nTu pedido será enviado a " << usuario.codigoPostal << " " << usuario.direccion << endl;
                    cout << "Para rastrear tu pedido usa tu número de cuenta: " << usuario.numeroCuenta << endl;
                }
                break;

            case 5:
                clear();
                cout << "Saliendo del sistema..." << endl;
                return 0;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);

    return 0;
}
