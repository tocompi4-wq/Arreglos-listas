#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Declaración de funciones
double f(double x);
double integral_exacta(double a, double b); 
double metodo_cajas(double a, double b, int n);
double metodo_trapecio(double a, double b, int n);
double metodo_simpson(double a, double b, int n);

// ==================================== Funcion main ====================================
int main() {
    double a = 0.0;
    double b = M_PI;
    
    // Calculamos analíticamente el valor real exacto de la Gaussiana de 0 a PI usando ERF
    double valor_exacto_total = integral_exacta(a, b); 

    // Datos para la gráfica de las curvas (Rango variable de x)
    int n_fijo = 100;
    std::ofstream archivo_curvas("curvas_integrales.csv");
    archivo_curvas << "x,exacta,cajas,trapecio,simpson\n";

    // Evaluamos la integral acumulada desde 'a' hasta un 'x_lim' variable
    for(double x_lim = 0.1; x_lim <= M_PI; x_lim += 0.1) {
        archivo_curvas << x_lim << ","
                       << integral_exacta(a, x_lim) << "," // Pasamos a y x_lim
                       << metodo_cajas(a, x_lim, n_fijo) << ","
                       << metodo_trapecio(a, x_lim, n_fijo) << ","
                       << metodo_simpson(a, x_lim, n_fijo) << "\n";
    }
    archivo_curvas.close();


    // Datos para la gráfica de h vs Error (11 valores de h)
    std::ofstream archivo_error("error_integrales.csv");
    archivo_error << "h,error_cajas,error_trapecio,error_simpson\n";

    // Generamos variaciones de n para obtener diferentes tamaños de h
    std::vector<int> n_values = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};

    for(int n : n_values) {
        double h = (b - a) / n;
        
        double err_cajas   = std::abs(valor_exacto_total - metodo_cajas(a, b, n));
        double err_trap    = std::abs(valor_exacto_total - metodo_trapecio(a, b, n));
        double err_simpson = std::abs(valor_exacto_total - metodo_simpson(a, b, n));

        archivo_error << h << "," << err_cajas << "," << err_trap << "," << err_simpson << "\n";
    }
    archivo_error.close();

    std::cout << "¡BRUTAL! CSVs 'curvas_integrales.csv' y 'error_integrales.csv' generados con éxito." << std::endl;
    return 0;
}

// ==================================== Funciones ====================================

double f(double x){ // Función Gaussiana
    return pow(2.71828, ( - ( 0.5 ) * ( pow( (x - 2) / 8, 2 ) ) ) );
}
double integral_exacta(double a, double b) { // Integral exacta acumulada usando std::erf de <cmath>
    double centro = 2.0;
    double ancho = 8.0;

    // Factor analítico de la sustitución
    double factor = ancho * std::sqrt(M_PI / 2.0);

    // Argumentos de la función de error para los límites superior e inferior
    double limite_superior = std::erf((b - centro) / (ancho * std::sqrt(2.0)));
    double limite_inferior = std::erf((a - centro) / (ancho * std::sqrt(2.0)));

    return factor * (limite_superior - limite_inferior);
}
double metodo_cajas(double a, double b, int n) { // Método de Cajas (Riemann por la izquierda)
    double h = (b - a) / n;
    double suma = 0.0;
    for(int i = 0; i < n; i++) {
        suma += f(a + i * h);
    }
    return suma * h;
}
double metodo_trapecio(double a, double b, int n) {// Método del Trapecio
    double h = (b - a) / n;
    double suma = (f(a) + f(b));
    for(int i = 1; i < n; i++) {
        suma += 2 * f(a + i * h);
    }
    return suma * h * 0.5;
}
double metodo_simpson(double a, double b, int n) { // Método de Simpson 1/3
    double h = (b - a) / n;
    double suma = f(a) + f(b);
    
    for(int i = 1; i < n; i++) {
        if(i % 2 == 0) {
            suma += 2.0 * f(a + i * h); 
        } else {
            suma += 4.0 * f(a + i * h); 
        }
    }
    return (h / 3.0) * suma;
}