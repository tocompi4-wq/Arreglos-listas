#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <functional>

// Definición de M_PI si no está definido
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Pre defino mis funciones para evitar errores de compilación, por un lado tenemos las funciones a integrar
double f_g(double x);
double f_e(double x);

// Por el otro las funciones para calcular las integrales numéricas
double integral_exacta(double a, double b);
double integral_gauss_legendre(std::function<double(double)> func,int n, double a, double b);
double integral_puntomedio(std::function<double(double)> func, double a, double b, int n);

// ==================================== Funcion main ====================================
int main(){
    // Límites de integración para tus experimentos
    double a = 0.0;
    double b = M_PI;

    // Calculo de los valores usando Gauss-Legendre (7 puntos)
    double I_G = integral_gauss_legendre(f_g, 7, a, b); // Gaussiana
    std::cout << "Referencia exacta f_g (Gauss-Legendre n=7): " << I_G << std::endl;

    double I_E = integral_gauss_legendre(f_e, 7, a, b); // Tu otra funcion no-polinómica
    std::cout << "Referencia exacta f_e (Gauss-Legendre n=7): " << I_E << std::endl;

    // preparo el archivo CSV con una estructura optimizada para DataFrames de Python
    std::ofstream archivo("resultados_punto_medio.csv");
    archivo << "n,error_gaussiana,error_exponencial\n";

    // Ciclo for para evaluar la evolución del error con el Punto Medio de 1 a 100 rectángulos
    for(int i = 1; i <= 200; i++){
        // aproximaciones por Punto Medio para el n actual (i)
        double I_PMG = integral_puntomedio(f_g, a, b, i);
        double I_PME = integral_puntomedio(f_e, a, b, i);

        // error absoluto con respecto a la referencia exacta de Gauss-Legendre
        double error_PMG = std::abs(I_PMG - I_G);
        double error_PME = std::abs(I_PME - I_E);

        // Guardamos de forma horizontal en el CSV: n, error1, error2
        archivo << i << "," << error_PMG << "," << error_PME << "\n";
    }
    
    archivo.close();
    std::cout << "\n'resultados_punto_medio.csv' generado con éxito." << std::endl;

    return 0;
}


// ==================================== Funciones ====================================
double f_g(double x){ // Funcion a integrar
    return std::exp( -0.5 * std::pow((x - 2.0) / 8.0, 2.0) );
}
double f_e(double x){ // segunda funcion a integrar
    return std::exp(x*x);
}
double integral_gauss_legendre(std::function<double(double)> func, int n, double a, double b) { // Metodo gauss legendre
    std::vector<double> x(n), w(n);

    // Nodos estándar reales para n = 3 en [-1, 1]
    x[0] = -0.9491079123427585;
    x[1] = -0.7415311855993945;
    x[2] = -0.4058451513773972;
    x[3] = 0.0;
    x[4] = 0.4058451513773972;
    x[5] = 0.7415311855993945;
    x[6] = 0.9491079123427585;

    // Pesos correspondientes (¡usando decimales .0!)
    w[0] = 0.1294849661688697;
    w[1] = 0.2797053914892767;
    w[2] = 0.3818300505051189;
    w[3] = 0.4179591836734694;
    w[4] = 0.3818300505051189;
    w[5] = 0.2797053914892767;
    w[6] = 0.1294849661688697;

    double suma = 0.0;
    double xi_mapeado = 0.0;
    for (int i = 0; i < n; i++){
        xi_mapeado = ((b - a) / 2) * x[i] + (a + b) / 2;
        suma += w[i] * func(xi_mapeado);
    }

    return ((b - a) / 2) * suma;
}
double integral_puntomedio(std::function<double(double)> func, double a, double b, int n){ // Metodo integral por punto medio
    double h = (b - a) / n;
    double suma = 0.0;

    for(int i = 0; i< n; i++){
        double x_medio = a + (i + 0.5) * h;
        suma += func(x_medio);
    }

    return h * suma;
}
