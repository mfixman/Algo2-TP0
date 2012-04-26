#include <cstdlib>
#include <cstdio>
#include "anillo.h"

#define LOG cerr << '\n' << '[' << __LINE__ << "] "


bool kill = false;

template <typename T>
Anillo<T>::Anillo()
{
	primero = NULL;
	elNodoAnterior = NULL;
	longitud = 0;
}

template <typename T>
Anillo<T>::Anillo(const Anillo<T>& otro) {
	Nodo* nodo = otro.primero;
	Nodo* anterior = NULL;

	do {
		Nodo* nuevo = new Nodo();

		assert(nodo != NULL);
		assert(nuevo != NULL);

		nuevo->elemento = nodo->elemento;
		nuevo->anterior = anterior;

		if (anterior != NULL)
			anterior->proximo = nuevo;

        anterior = nuevo;
		nodo = nodo->proximo;
	} while (nodo != otro.primero);
	anterior->proximo = nodo;

    primero = nodo;
	elNodoAnterior = otro.elNodoAnterior;
	longitud = otro.longitud;
}

template <typename T>
Anillo<T>::~Anillo()
{
	while (!esVacio()) {
		LOG << longitud;
		eliminar(siguiente());
	}
}

template <typename T>
bool Anillo<T>::operator==(const Anillo<T>& otro) const {
	if (longitud != otro.longitud || elNodoAnterior != otro.elNodoAnterior)
		return false;

	Nodo* a = primero;
	Nodo* b = otro.primero;

	for (int i = 0; i < longitud; i++) {
		assert(a != NULL);
		assert(b != NULL);

		if (a->elemento != b->elemento)
			return false;

		a = a->proximo;
		b = b->proximo;
	}

	return true;
}

template <typename T>
bool Anillo<T>::esVacio() const
{
	return longitud == 0;
}

template <typename T>
int Anillo<T>::tamanio() const
{
	return longitud;
}

template <typename T>
const T& Anillo<T>::siguiente() {
	assert(!esVacio());
	assert(primero != NULL);

	elNodoAnterior = primero;
	primero = primero->proximo;
	return elNodoAnterior->elemento;
}

template <typename T>
void Anillo<T>::agregar(const T& nuevoElemento) {
	Nodo* punteroNuevoNodo = new Nodo(nuevoElemento);              //creo nuevo nodo con el elemento

	if (primero == NULL) {
		primero = punteroNuevoNodo;                  //hago que el anillo apunte al nuevo nodo
		primero->proximo = primero;
		primero->anterior = primero;
	} else {
		punteroNuevoNodo->proximo = primero;          //lo pongo antes del que era el proximo
		punteroNuevoNodo->anterior = primero->anterior;   //lo pongo despues del que ya paso

		primero->anterior = punteroNuevoNodo;
		punteroNuevoNodo->anterior->proximo = punteroNuevoNodo;

		primero = punteroNuevoNodo;
	}

	longitud++;                                      //aumento la longitud del anillo
}

template <typename T>
void Anillo<T>::eliminar(const T& elementoAEliminar) {
	LOG << *this;

	struct Nodo* punteroAlNodo;
	LOG ;

	if (primero->elemento == elementoAEliminar) {
		punteroAlNodo = primero;
		primero = punteroAlNodo->proximo;
	} else {
		punteroAlNodo = this->buscar(elementoAEliminar);
	}

	LOG ;
	if (punteroAlNodo != NULL) {
		if (punteroAlNodo == elNodoAnterior) {
			elNodoAnterior = NULL;
		}

		punteroAlNodo->anterior->proximo = punteroAlNodo->proximo;
		punteroAlNodo->proximo->anterior = punteroAlNodo->anterior;
		longitud--;

		LOG ;
		delete punteroAlNodo;
		LOG ;

		if (longitud == 0)
			primero = elNodoAnterior = NULL;
	}
}

template <typename T>
bool Anillo<T>::huboAnterior() const{
	return elNodoAnterior != NULL;
}

template <typename T>
const T& Anillo<T>::anterior() const{
	assert(elNodoAnterior != NULL);
	return elNodoAnterior->elemento ;
}

template <typename T>
void Anillo<T>::retroceder() {
	primero = primero->anterior;
}

template <typename T>
struct Anillo<T>::Nodo * Anillo<T>::buscar(const T& elementoABuscar) {
	LOG << longitud;
	if (longitud == 0)
		return NULL;

	struct Nodo* punteroANodo = primero;
	assert (punteroANodo != NULL);
	LOG << elementoABuscar;

	do {
		if (punteroANodo->elemento == elementoABuscar)
			return punteroANodo;

		LOG << longitud << ' ' << punteroANodo << ' ' << primero;
		punteroANodo = punteroANodo->proximo;
	} while (punteroANodo != primero);

	return NULL;
}

template <typename T>
ostream& Anillo<T>::mostrarAnillo(ostream& out) const {
	out << '[';

	Nodo* actual = primero;
	if (actual != NULL) {
		do {
			out << actual->elemento;
			if (actual == elNodoAnterior)
				out << '*';

			actual = actual->proximo;
		} while (actual != primero);
	}

	out << ']';
}

