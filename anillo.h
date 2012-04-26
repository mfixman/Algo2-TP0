#ifndef ANILLO_H_
#define ANILLO_H_

#include <iostream>
#include <cassert>
using namespace std;

//se puede asumir que el tipo T tiene constructor por copia
//y operator==
//no se puede asumir que el tipo T tenga operator=
template<typename T>
class Anillo {
public:
	/*
	* constructor por defecto, crea un anillo
	*/
	Anillo();

	/*
	 * constructor por copia, una vez copiado, ambos anillos deben ser
	 * independientes, es decir, cuando se borre uno no debe morir el otro.
	 */
	Anillo(const Anillo<T>&);

	/*
	 * Destructor. Acordarse de liberar toda la memoria!
	 */
	~Anillo();

	/*
	 * Devuelve true si los anillos son iguales
	 */
	bool operator==(const Anillo<T>&) const;

	/*
	 * Dice si el anillo es vac’o.
	 */
	bool esVacio() const;

	/*
	 * Dice el tamanio del anillo
	 */
	int tamanio() const;

	/*
	 * Devuelve el pr—ximo elemento segœn el orden del anillo.
	 * El anillo debe rotar. Con lo cual sucesivas llamadas a esta funci—n
	 * retornan distintos valores.
	 *
	 * El valor retornado pasa a ser el anterior.
	 *
	 * PRE: no es vac’o el anillo.
	 */
	const T& siguiente();

	/*
	 * Agrega el elemento al anillo. Recordar que el œltimo agregado es el
	 * pr—ximo en el orden
	 */
	void agregar(const T&);

	/*
	 * Elimina el elemento indicado del anillo.
	 */
	void eliminar(const T&);

	/*
	 * Indica si hubo anterior elemento elegido
	 * y si Žste pertenece todav’a al anillo.
	 */
	bool huboAnterior() const;

	/*
	 * Indica cu‡l es el elemento elegido la œltima vez.
	 */
	const T& anterior() const;

	/*
	 * Vuelve hacia atr‡s un elemento.
	 * El anterior, en caso de existir, no debe alterarse.
	 */
	void retroceder();

	/*
	 * debe mostrar el anillo en el stream (y retornar el mismo).
	 * Anillo vacio: []
	 * Anillo con 2 elemento (e1 es el pr—ximo a aparecer en siguiente): [e1, e2]
	 * Anillo con 2 elemento (e2 es el pr—ximo a aparecer en siguiente y e1 es el anterior): [e2, e1*]
	 *
	 */
	ostream& mostrarAnillo(ostream&) const;

private:
	struct Nodo {
		T elemento; //de tipo T
		Nodo* proximo;
		Nodo* anterior;

		~Nodo() {
		}

		Nodo(const T& elemento_) : elemento(elemento_) {
		}

		Nodo() {
		}
	};

	Nodo* primero;
	Nodo* elNodoAnterior;

	int longitud;
	Nodo* buscar(const T&);

	//No se puede modificar esta funcion.
	Anillo<T>& operator=(const Anillo<T>& otro) {
			assert(false);
			return *this;
	}

	//Aca va la implementacion del nodo.
};

template<class T>
ostream& operator<<(ostream& out, const Anillo<T>& a) {
		return a.mostrarAnillo(out);
}

#endif //ANILLO_H_
