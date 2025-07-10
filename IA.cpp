#include <iostream>
#include <string>
using namespace std;

string responder(const string& entrada) {
    if (entrada == "hola" || entrada == "Hola") {
        return "¡Hola! ¿En qué puedo ayudarte?";
    } else if (entrada == "adios" || entrada == "Adios") {
        return "¡Hasta luego!";
    } else {
        return "No entiendo tu mensaje.";
    }
}

int main() {
    string mensaje;
    cout << "Escribe un mensaje: ";
    getline(cin, mensaje);
    cout << responder(mensaje) << endl;
    return 0;
}