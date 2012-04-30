#include <cstdlib>
#include <cstdio>
#include "anillo.h"

#define LOG cerr << '\n' << __FILE__ << " [" << __LINE__ << "] "

template <typename T>
Anillo<T>::Anillo() : primero(NULL), nodoAnterior(NULL), longitud(0) {
}

template <typename T>
Anillo<T>::Anillo(const Anillo<T>& otro) : primero(NULL), nodoAnterior(NULL), longitud(0) {
	if (otro.esVacio())
		return;

	Nodo* nodo = otro.primero;
	Nodo* anterior = NULL;

	// Recorrer todos los nodos, copiarlos, y "engancharlos" a nuestro anillo.
	do {
		assert(nodo != NULL);

		Nodo* nuevo = new Nodo(nodo->elemento());
		nuevo->anterior = anterior;

		if (nodo == otro.primero)
			primero = nuevo;

		if (nodo == otro.nodoAnterior)
			nodoAnterior = nuevo;

		if (anterior != NULL)
			anterior->proximo = nuevo;

        anterior = nuevo;
		nodo = nodo->proximo;
	} while (nodo != otro.primero);

	assert(primero != NULL);
	assert(anterior != NULL);
	anterior->proximo = primero;
	primero->anterior = anterior;

	longitud = otro.longitud;
}

template <typename T>
Anillo<T>::~Anillo() {
	while (!esVacio()) eliminar(siguiente());
}

template <typename T>
bool Anillo<T>::operator==(const Anillo<T>& otro) const {
	if (longitud != otro.longitud)
		return false;

	Nodo* a = primero;
	Nodo* b = otro.primero;

	// Recorrer todos los nodos de los dos anillos, y ver que
	// todos los elementos en el orden respectivo sean iguales
	// y que tengan el mismo nodoAnterior.
	for (int i = 0; i < longitud; i++) {
		assert(a != NULL);
		assert(b != NULL);

		if (!(a->elemento() == b->elemento()))
			return false;

		if ((a == nodoAnterior) != (b == otro.nodoAnterior))
			return false;

		a = a->proximo;
		b = b->proximo;
	}

	return true;
}

template <typename T>
bool Anillo<T>::esVacio() const {
	return longitud == 0;
}

template <typename T>
int Anillo<T>::tamanio() const {
	return longitud;
}

template <typename T>
const T& Anillo<T>::siguiente() {
	assert(!esVacio());
	assert(primero != NULL);

	nodoAnterior = primero;
	primero = primero->proximo;
	return nodoAnterior->elemento();
}

template <typename T>
void Anillo<T>::agregar(const T& nuevoElemento) {
	Nodo* nodo = new Nodo(nuevoElemento);              //creo nuevo nodo con el elemento

	if (primero == NULL) {
		primero = nodo;                  //hago que el anillo apunte al nuevo nodo
		primero->proximo = primero;
		primero->anterior = primero;
	} else {
		nodo->proximo = primero;          //lo pongo antes del que era el proximo
		nodo->anterior = primero->anterior;   //lo pongo despues del que ya paso

		primero->anterior = nodo;
		nodo->anterior->proximo = nodo;

		primero = nodo;
	}

	longitud++;                                      //aumento la longitud del anillo
}

template <typename T>
void Anillo<T>::eliminar(const T& elementoAEliminar) {
	Nodo* nodo;

	// Si el elemento a eliminar es el primero, poner un nuevo primero.
	if (primero->elemento() == elementoAEliminar) {
		nodo = primero;
		primero = nodo->proximo;
	} else {
		nodo = buscar(elementoAEliminar);
		if (nodo == NULL)
			return;
	}

	assert(nodo != NULL);
	assert(nodo->anterior != NULL);
	assert(nodo->proximo != NULL);
	nodo->anterior->proximo = nodo->proximo;
	nodo->proximo->anterior = nodo->anterior;
	delete nodo;

	if (nodo == nodoAnterior)
		nodoAnterior = NULL;

	longitud--;
	if (longitud == 0)
		primero = NULL;
}

template <typename T>
bool Anillo<T>::huboAnterior() const {
	return nodoAnterior != NULL;
}

template <typename T>
const T& Anillo<T>::anterior() const {
	assert(nodoAnterior != NULL);
	return nodoAnterior->elemento();
}

template <typename T>
void Anillo<T>::retroceder() {
	primero = primero->anterior;
}

template <typename T>
struct Anillo<T>::Nodo* Anillo<T>::buscar(const T& elementoABuscar) {
	if (longitud == 0)
		return NULL;

	Nodo* nodo = primero;
	assert (nodo != NULL);

	do {
		if (nodo->elemento() == elementoABuscar)
				return nodo;

		nodo = nodo->proximo;
	} while (nodo != primero);

	return NULL;
}

template <typename T>
ostream& Anillo<T>::mostrarAnillo(ostream& out) const {
	out << '[';

	Nodo* actual = primero;
	if (actual != NULL) {
		do {
			out << actual->elemento();
			if (actual == nodoAnterior)
				out << '*';

			actual = actual->proximo;
			if (actual != primero)
				out<<", ";
		} while (actual != primero);
	}

	out << ']';
}

