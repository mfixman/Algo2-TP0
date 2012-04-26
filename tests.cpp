#include "anillo.cpp"

// auxiliares para tests
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;
void mt_assert(bool expr, int line) {
	if (!expr) {
		ostringstream os;
		os << "error en linea " << line;
		throw os.str();
	}
}
#define RUN_TEST(test) {\
	{bool ok = true;\
	cout << #test << "..." << flush;\
	try { test(); }\
	catch (string& msg) { ok = false; cout << msg; } \
	catch (...) { ok = false; cout << "error"; }\
	if (ok) { cout << "ok"; }\
	cout << endl << flush;\
	}\
}
#define ASSERT_EQ(lhs, rhs) { mt_assert((lhs) == (rhs), __LINE__); }
#define ASSERT(expr) { mt_assert((expr), __LINE__); }
#define ASSERT_STR_EQ(lhs, rhs) { mt_assert(string((lhs)).compare((rhs)) == 0, __LINE__); }
// fin auxiliares para tests

template<typename T>
string to_s(const Anillo<T>* a) {
	ostringstream os;
	os << *a;
	return os.str();
}

void AnilloNuevoEsVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
	delete a;
}

void AnilloUnitarioDaSiguiente() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	ASSERT(!a->esVacio());
	ASSERT_EQ(a->tamanio(), 1);
	ASSERT_EQ(a->siguiente(), 42);
	delete a;
}

void MostrarAnilloVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT_STR_EQ(to_s(a), "[]");
	delete a;
}

void AnilloPuedeRotarVariasVeces() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->agregar(3);
	ASSERT_EQ(a->siguiente(), 3);
	ASSERT_EQ(a->siguiente(), 2);
	ASSERT_EQ(a->siguiente(), 1);
	ASSERT_EQ(a->siguiente(), 3);
	ASSERT_EQ(a->siguiente(), 2);
	ASSERT_EQ(a->siguiente(), 1);
	delete a;
}

void AnilloDeAnilloPuedenCrearseYUsarse(){
	Anillo<Anillo<int> >* a = new Anillo<Anillo<int> >;

	Anillo<int>* b = new Anillo<int>;
	b->agregar(11);
	b->agregar(22);

	a->agregar(*b);
	kill = true;
	a->agregar(*b);

	Anillo<int>* c = new Anillo<int> (*b);
	c->siguiente();
	c->agregar(33);
	a->agregar(*c);

	ASSERT_EQ(a->siguiente(), *c);
	ASSERT_EQ(a->siguiente(), *b);
	ASSERT_EQ(a->siguiente(), *b);

	a->eliminar(*c);

	ASSERT_EQ(a->siguiente(), *b);

	delete c;
	delete b;
	delete a;
}

int main(void) {
	//RUN_TEST(AnilloNuevoEsVacio);
	//RUN_TEST(AnilloUnitarioDaSiguiente);
	//RUN_TEST(MostrarAnilloVacio);
	//RUN_TEST(AnilloPuedeRotarVariasVeces);
	RUN_TEST(AnilloDeAnilloPuedenCrearseYUsarse);
	return 0;
}

