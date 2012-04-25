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

}

void AnilloDeAnilloPuedenCrearseYUsarse(){

}

int main(void) {
	RUN_TEST(AnilloNuevoEsVacio);
	RUN_TEST(AnilloUnitarioDaSiguiente);
	RUN_TEST(MostrarAnilloVacio);
	RUN_TEST(AnilloPuedeRotarVariasVeces);
	RUN_TEST(AnilloDeAnilloPuedenCrearseYUsarse);
	return 0;
}

