#include "Agenda.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#define NOMBRE_ARCHIVO "contactos.txt"

Agenda::Agenda() : _primer(NULL), _ultimo(NULL)
{
}

int cantidadContactos = 0;

void Agenda::Agregar(Contacto *contacto)
{
    if (_primer == NULL) // Si la lista está vacía
    {
        _primer = contacto;
        _ultimo = contacto;
    }
    else // Si la lista no está vacía
    {
        _ultimo->SetSiguiente(contacto);
        _ultimo = contacto;
    }
}

bool Agenda::Eliminar(int indice)
{
    int contador = -1;
    Contacto *i = _primer;

    while (i != NULL)
    {
        Contacto *siguiente = i->GetSiguiente();
        contador++;

        if (contador == indice)
        {

            Contacto *auxiliar = i;

            if (_primer == i)
            {
                _primer = siguiente;
            }
            else
            {
                _ultimo->SetSiguiente(siguiente);
            }

            delete auxiliar;

            return true;
        }

        _ultimo = i;
        i = siguiente;
    }

    if (contador <= indice || contador >= indice)
    {
        return false;
    }
}

bool Agenda::Modificar(int indice, std::string nombre, std::string telefono)
{
    // Implementar este método
    /*
        Este método tiene como objetivo modificar un contacto de la agenda.

        Este método recibe parámetros el índice del contacto a eliminar (iniciando en cero) , el nuevo nombre y nuevo teléfono de dicho contacto.
    */

    int contador = -1;
    Contacto *Actualizacion = _primer;

    while (Actualizacion != NULL)
    {
        Contacto *siguiente = Actualizacion->GetSiguiente();
        contador++;

        if (contador == indice)
        {

            Actualizacion->SetNombre(nombre);
            Actualizacion->SetTelefono(telefono);
            return true;
        }

        Actualizacion = siguiente;
    }

    if (contador <= indice || contador >= indice)
    {
        return false;
    }

    return false;
}

void Agenda::Cargar()
{

    // Terminar la implementación de este método
    /*
        Este método es el que carga desde un archivo de texto todos los contactos almacenados en el disco duro.
    */
    std::ifstream lector(NOMBRE_ARCHIVO);
    std::string linea;

    if (lector.is_open())
    {
        int i = 0;

        cout << endl
             << "****** Antigua *******" << endl;

        while (!lector.eof())
        {
            getline(lector, linea);

            if (linea != "")
            {
                int position = linea.find(",");
                std::string nombre = linea.substr(0, position);
                std::string telefono = linea.substr(position + 1);

                Contacto *contacto = new Contacto(nombre, telefono);
                Agregar(contacto);

                std::cout << i << "- " << nombre << " " << telefono << std::endl;
                i++;
            }
        }
    }

    cout << endl
         << "**********************\n\n"
         << endl;

    lector.close();
}

void Agenda::Guardar()
{
    // Terminar la implementación de este método
    /*
    Este método es el que guarda en un archivo de texto (en el disco duro) todos los contactos.
    */
    std::ofstream escritor(NOMBRE_ARCHIVO);
    Contacto *contacto = _primer;

    while (contacto != NULL)
    {
        escritor << contacto->GetNombre() << "," << contacto->GetTelefono() << std::endl;
        contacto = contacto->GetSiguiente();
    }
}
