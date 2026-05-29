#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

// Pre - Preparar las funciones ==============================
double f(double x);
double derivada_a(double x, double h);
double derivada_b(double x, double h);
double derivada_c(double x, double h);
double derivada(double x);

//  ============================== Funcion main ============================================================

int main() {
    // Preparar variables
    int j;
    std::vector<double> x_range;
    std::cout<<"rango de la función: ";
    std::cin >> j;
    
    
    // Ciclo para crear el rango de la función
    for(double i = 0; i <= j; i += 0.1){
        x_range.push_back(i);
    }
    
    double h = 0.01;
    
    // Ciclo for para calcular las derivadas
    for(double x : x_range){
        std::cout << "Función: " << f(x) << std::endl;
        std::cout << "derivada a: " << derivada_a(x, h) << "  ||  ";
        std::cout << "derivada c: " <<derivada_c(x, h) << "  ||  ";
        std::cout << "derivada b: " << derivada_b(x, h) << "  ||  ";
        std::cout << "derivada: " << derivada(x) << "  ||  " << std::endl;
    }
    
    std::ofstream archivo("Derivadas.csv");

    archivo << "x, f(x), derivada_a, derivada_c, derivada_b, derivada\n";
    
    for(double x : x_range){
        double val_f = f(x);
        double der_a = derivada_a(x, h);
        double der_c = derivada_c(x, h);
        double der_b = derivada_b(x, h);
        double der = derivada(x);

        std::cout << "procesando x = " << x << std::endl;

        archivo << x << ", " << val_f << ", " << der_a << ", " << der_c << ", " << der_b << ", " << der << "\n";
        

    }
    archivo.close();
    std::cout << "Datos guardados en Derivadas.csv" << std::endl;

    return 0;
}

// Funciones usadas =====================================================

double f(double x){ // Funcion a derivar
    return pow(2.71828, ( - ( 0.5 ) * ( pow( (x - 2) / 8, 2 ) ) ) );
}
double derivada_a(double x, double h){ // Derivada adelante
    return ( f(x + h) - f(x) ) / h;
}
double derivada_b(double x, double h){ // Derivada atras (backward)
    return ( - f(x - h) + f(x) ) / h;
}
double derivada_c(double x, double h){ // Deriada central
    return ( f(x + h) - f(x - h) ) / ( 2 * h );
}
double derivada(double x){ // Función de la Derivada analítica/exacta
    return - ( 1.0 / 8.0 ) * ( x / 8.0 - 0.25 ) * f(x);
}