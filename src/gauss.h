#ifndef RATOM_GAUSS_H
#define RATOM_GAUSS_H


//
// Calculates 1D integral over the interval by Gauss quadrature
//
// Reprezentuje algorytm calkowania numerycznego funkcji jednej zmiennej za pomoca kwadratur Gaussa.
//
// Calkowanie wykonywane jest na przedziale [a, b].
//	Kwadratury Gaussa sa przeznaczone do calkowania na przedziale [-1, 1]. Dlatego
//	nalezy wykonac zmiane zmiennych, aby calkowac na dowolnym przedziale [a, b].
//	te podstawienie jest wykonywane wewnatrz skladowej Calc().
//
//	Stopien kwadratury Gaussa okresla liczbe punktow na przedziale [-1, 1], dla ktorych
//	obliczana jest wartosc funkcji. Mowiac nieprecyzyjnie, liczba wezlow determinuje
//	dokladnosc obliczanej calki.
//
//	*** Komentarz numeryczny ***
//	Kwadratury Gaussa zdefiniowane sa na przedziale [-1, 1], wiec nalezy zrobic
//	podstawienie zmieniajace granice calkowania z [a, b] na [-1, 1]. Mozna to zrobic
//	za pomoca przeksztalcenia liniowego:
//
//     x(t) = P * t + Q    ==> dx = P * dt
//
//	Przeksztalcenie to musi spelniac warunki:
//		x(-1) = a   oraz   x(1) = b
//	co jest rownowazne ukladowi rownan na P i Q
//		a = -P + Q
//		b =  P + Q
//	Z powyzszego otrzymujemy Q = (a + b) / 2,  P = (b - a) / 2
//	Ostatecznie otrzymujemy:
//	\f[
//		I = \int_a^b f(x) dx = P * \int_{-1}^1 f(P * t + Q) dt
//	\f]
//	Ten wzor jest wykorzystany do obliczania calki
//
//	*** Uwaga ***
//	Wagi kwadratur sa zapisane w tablicy $w$.
//	Wspolrzedne kwadratur zapisane sa w tablicy $t$.
//
//   Zbigniew Romanowski [ROMZ@wp.pl]
//



#include <cstddef>
#include <vector>
#include "fun1D.h"

class Gauss
{
public:
    Gauss();
    ~Gauss() = default;

    static double Calc( const Fun1D& f, double a, double b );

    static double X( size_t i )  { return m_x[ i ]; }
    static double W( size_t i )  { return m_w[ i ]; }
    static double Size( )  { return m_x.size(); }


private:
    // Quadrature degree
    static const size_t m_deg;

    // Quadrature weights
    static std::vector< double > m_w;

    // Quadrature nodes
    static std::vector< double > m_x;
};

#endif

