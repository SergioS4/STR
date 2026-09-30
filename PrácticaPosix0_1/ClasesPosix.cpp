#include "ClasesPosix.h"
#include "Identificador.h"
#include <stdio.h>

Identificador_t Identificador;

/*
**********************************************************
********************** Clase hilo_t **********************
**********************************************************
*/

// Implementación del constructor sin parámetros. Este método reservará memoria para los atributos de la clase e inicializará los atributos de creación del hilo
hilo_t::hilo_t()
{

	// Guardar el resultado de Identificador.ObtenerId() en el atributo de clase que almacena el identificador del hilo
	identificador = Identificador.ObtenerId();
	// Inicialización de los atributos de creación del hilo
	pthread_attr_init(&atributos);
	// Inicialización de la función del hilo a NULL
	funcion = NULL;
	// Inicialización de los datos de la función del hilo a NULL
	dato = NULL;
}
// fin del constructor

// Implementación del destructor sin parámetros. Este método destruirá los atributos de creación del hilo y liberará la memoria de los atributos de la clase
hilo_t::~hilo_t()
{

	// Destrucción de los atributos de creación del hilo
	pthread_attr_destroy(&atributos);
}
// Fin del destructor

// Implementación del método Lanzar. Este método se encargará de lanzar un hilo usando la función y los datos almacenados en la clase
int hilo_t::Lanzar()
{

	// Si la función asociada existe (no es NULL)
	if(funcion != NULL)
	{
		/*Crear un hilo usando como parámetros la dirección de memoria al manejador del hilo, la dirección de memoria a los atributos de creación del hilo, la función del hilo y los datos del hilo.
		Se devolverá el resultado de la llamada a pthread_create*/
		return pthread_create(&manejador, &atributos, funcion, dato);
	}
	else
	{
		// Si la función asociada no existe
		// Devolver -1
		return -1;
	}
}
// Fin de Lanzar

// Implementación del método AsignarFuncion. Asignará el parámetro recibido al atributo que almacena la función del hilo
void hilo_t::AsignarFuncion(void *(*func)(void *))
{
	// Asignar el parámetro del método al atributo de la clase que almacena la función asociada
	funcion = func;
}
// Fin de AsignarFuncion

// Implementación del método AsignarDato. Asignará el parámetro recibido al atributo que almacena los datos que se usarán con la función del hilo
void hilo_t::AsignarDato(void *d)
{
	// Asignar el parámetro del método al atributo de la clase que almacena el parámetro que se usará con la función asociada
	dato = d;
}
// fin de AsignarDato

// Implementación del método AsignarFuncionYDato. Este método llamará a los métodos AsignarFuncion y AsignarDato con cada uno de sus parámetros
void hilo_t::AsignarFuncionYDato(void *(*func)(void *), void *d)
{
	// Llamar a AsignarFuncion
	AsignarFuncion(func);
	// Llamar a AsignarDato
	AsignarDato(d);
}
// Fin de AsignarFuncionYDato

// Implementación del método Join sin parámetros. Este método esperará por el hilo indicado por el manejador de la clase y retornará el valor devuelto por dicho hilo.
void *hilo_t::Join()
{
	// Definir una variable de tipo puntero a void (debe ser puntero a void para permitir que se pueda devolver cualquier tipo de dato). No hay que reservar memoria.
	void *var;
	// Esperar por el hilo asociado a la clase
	pthread_join(manejador, &var);
	// Devolver la variable definida en la primera línea del método.
	return var;
}
// Fin de Join

// Implementación de método ObtenerManejador sin parámetros. Este método devolverá el valor del manejador del hilo asociado a la clase.
void *hilo_t::ObtenerManejador()
{
	// Devolver el manejador del hilo
	return &manejador;
}
// Fin de ObtenerManejador

// Implementación de método ObtenerIdentificaror sin parámetros. Este método devolverá el valor del identificador del hilo asociado a la clase.
int hilo_t::ObtenerIdentificador()
{
	// Devolver el identificador del hilo
	return identificador;
}
// Fin de ObtenerIdentificaror
