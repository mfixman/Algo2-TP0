#include "anillo.h"

template <typename T>
Anillo<T>::Anillo()
{
	primero = NULL;
	elNodoAnterior = NULL;
	longitud = 0;
}

template <typename T>
Anillo<T>::~Anillo()
{
	while (this->esVacio()==false) {
		this->eliminar(this->siguiente());
	}
	delete primero;
	primero = NULL;
}

template <typename T>
bool Anillo<T>::esVacio() const
{
	return (longitud == 0);
}

template <typename T>
int Anillo<T>::tamanio() const
{
	return longitud;
}

template <typename T>
const T& Anillo<T>::siguiente() {
	elNodoAnterior = primero;
	primero = primero->proximo;
	return primero->anterior->elemento;
}

template <typename T>
void Anillo<T>::agregar(const T& nuevoElemento) {
	Nodo* punteroNuevoNodo = new Nodo;              //creo nuevo nodo

	punteroNuevoNodo->elemento = nuevoElemento;     //pongo el elemento a agregar en el nodo
	punteroNuevoNodo->proximo = primero;          //lo pongo antes del que era el proximo
	punteroNuevoNodo->anterior = primero->anterior;   //lo pongo despues del que ya paso

	primero->anterior = punteroNuevoNodo;
	punteroNuevoNodo->anterior->proximo = punteroNuevoNodo;
	longitud++;                                      //aumento la longitud del anillo
	primero = punteroNuevoNodo;                   //hago que el anillo apunte al nuevo nodo
}

template <typename T>
void Anillo<T>::eliminar(const T& elementoAEliminar) {
	struct Nodo* punteroAlNodo;

	if (primero->elemento == elementoAEliminar) {
		punteroAlNodo = primero;
		primero = punteroAlNodo->proximo;
	} else {
		punteroAlNodo = this->buscar(elementoAEliminar);
	}

	if (punteroAlNodo != NULL) {
		if (punteroAlNodo == elNodoAnterior) {
			elNodoAnterior = NULL;
		}

		punteroAlNodo->anterior->proximo = punteroAlNodo->proximo;
		punteroAlNodo->proximo->anterior = punteroAlNodo->anterior;
		longitud--;

		delete punteroAlNodo;
	}
}

template <typename T>
bool Anillo<T>::huboAnterior() const{
	return elNodoAnterior != NULL;
}

template <typename T>
const T& Anillo<T>::anterior() const{
	return elNodoAnterior->elemento ;
}

template <typename T>
void Anillo<T>::retroceder() {
	primero = primero->anterior;
}

template <typename T>
struct Anillo<T>::Nodo * Anillo<T>::buscar(const T& elementoABuscar) {
	struct Nodo * punteroANodo = primero->proximo;
	while (punteroANodo->elemento != elementoABuscar && punteroANodo != primero) {
		punteroANodo = punteroANodo->proximo;
	}
	if (punteroANodo == primero)
	{
		return NULL;
	} else {
		return punteroANodo;
	}
}
