import pandas as pd
import matplotlib.pyplot as plt

# Cargar los datos generados por tu nuevo main
df = pd.read_csv('resultados_punto_medio.csv')

plt.figure(figsize=(11, 6))

# Graficamos el comportamiento del error para ambas funciones
plt.plot(df['n'], df['error_gaussiana'], '-', label='Error Función Gaussiana ($f_g$)', color='blue', linewidth=2)
plt.plot(df['n'], df['error_exponencial'], '-', label='Error Segunda Función ($f_e$)', color='darkorange', linewidth=2)

# Línea de referencia para la precisión "mínima antes del cero" (1e-6)
plt.axhline(y=1e-6, color='red', linestyle='--', alpha=0.7, label='Umbral de Precisión Mínima ($10^{-6}$)')

# Configuración de ejes estilo artículo de física
plt.title('Convergencia del Método del Punto Medio vs. Gauss-Legendre (n=7)', fontsize=13, fontweight='bold')
plt.xlabel('Número de Rectángulos ($n$)', fontsize=11)
plt.ylabel('Error Absoluto (Escala Logarítmica)', fontsize=11)

plt.yscale('log') # Clave para ver cómo el error se acerca a cero de forma exponencial
plt.grid(True, which="both", linestyle=':', alpha=0.5)
plt.legend(fontsize=10)

# Guardar automáticamente la figura para el informe del grupo
plt.savefig('convergencia_punto_medio_ambas.png', dpi=300)
plt.show()