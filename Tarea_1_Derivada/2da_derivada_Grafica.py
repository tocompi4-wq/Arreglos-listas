import pandas as pd
import matplotlib.pyplot as plt

# GRÁFICA 1: ONDAS DE LA FUNCIÓN Y SUS DERIVADAS (h fijo) =============================================================================
df_func = pd.read_csv('2da_derivada.csv', skipinitialspace=True)

plt.figure(figsize=(10, 5))
plt.plot(df_func['x'], df_func['f(x)'], label='f(x) = sin(x)', color='black', linewidth=2)
plt.plot(df_func['x'], df_func['segunda_derivada_numerica'], 'o', markevery=5, label='2da Derivada Numérica (h=0.0001)', color='blue')
plt.plot(df_func['x'], df_func['segunda_derivada_analitica'], label='2da Derivada Exacta (-sin(x))', color='red', linestyle='--')

plt.title('Función Seno vs. Segundas Derivadas', fontsize=14)
plt.xlabel('Eje X (Radianes)', fontsize=12)
plt.ylabel('Eje Y', fontsize=12)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend()

# GRÁFICA 2: ANÁLISIS DEL ERROR ABSOLUTO (h variable) =============================================================================
df_err = pd.read_csv('2da_derivada_h_variable.csv', skipinitialspace=True)

plt.figure(figsize=(10, 5))
# Graficamos 'h' contra 'error' usando la escala logarítmica obligatoria
plt.loglog(df_err['h'], df_err['error'], 'o-', color='purple', label='Error Absoluto de f\'\'(x)')

# Invertimos el eje X para leer la reducción de h de izquierda a derecha
plt.gca().invert_xaxis() 

plt.title('Análisis de Error: Paso h vs. Error Absoluto en la 2da Derivada', fontsize=14)
plt.xlabel('Tamaño del paso h (Escala Logarítmica)', fontsize=12)
plt.ylabel('Error Absoluto (Escala Logarítmica)', fontsize=12)
plt.grid(True, which="both", linestyle=':', alpha=0.6)
plt.legend()

# Muestra las dos ventanas al tiempo
plt.show()