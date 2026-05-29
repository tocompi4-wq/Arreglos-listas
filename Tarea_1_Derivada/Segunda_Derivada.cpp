#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

// Pre Preparación de funciones
double f(double x);
double segunda_derivada(double x, double h);
double doble_derivada_analitica(double x);


// =================================== Funcion main ============================================
int main(){
    // Codigo para las Derivadas con h fijo
    std::vector<double> x_values;
    double h = 0.0001; // Paso pequeño para la aproximación

    // Creo el dominio de la función
    for(double i= 0; i <= 10; i+=0.02){
        x_values.push_back(i);
    }

    std::ofstream archivo("2da_derivada.csv");
    archivo << "x,f(x),segunda_derivada_numerica,segunda_derivada_analitica\n";

    // Calculo la segunda derivada numérica y analítica para cada valor de x
    for(double x_num : x_values){
        double seg_dev = segunda_derivada(x_num, h);
        double seg_dev_an = doble_derivada_analitica(x_num);

        archivo << x_num << "," << f(x_num) << "," << seg_dev << "," << seg_dev_an << "\n";
        // std::cout << "x: " << x_num << " | f(x): " << f(x_num) << " | Segunda Derivada Numérica: " << seg_dev << " | Segunda Derivada Analítica: " << seg_dev_an << std::endl;
    }

    archivo.close();

    // Codigo para las Derivadas con h variable =S==============================================
    std::vector<double> h_values;
    double x = 5.0; // Punto específico para evaluar la segunda derivada

    // Creo diferentes valores de h
    for( double i = 0; i <= 10; i += 0.5){
        h_values.push_back(pow(10, -i)); // h = 10^(-i)
    }

    archivo.open("2da_derivada_h_variable.csv");
    archivo << "h,error\n";

    // calculamos la segunda derivada numérica para cada valor de h y la comparamos con la analítica
    for(double h_val : h_values){
        double seg_dev = segunda_derivada(x, h_val);
        double seg_dev_an = doble_derivada_analitica(x);

        double error = std::abs(seg_dev - seg_dev_an);

        archivo << h_val << "," << error << "\n";
        // std::cout << "h: " << h_val << " | Segunda Derivada Numérica: " << seg_dev << " | Segunda Derivada Analítica: " << seg_dev_an << " | Error: " << error << std::endl;
    }
    archivo.close();
    std::cout << "Datos generados y guardados en archivos CSV." << std::endl;


    return 0;
}

// Funciones
double f(double x){
    return sin(x);
}
double segunda_derivada(double x, double h){
    return ( f(x + h) - 2*f(x) + f(x - h) )/ pow(h,2);
}
double doble_derivada_analitica(double x){
    return -sin(x);
}