import pandas as pd
import matplotlib.pyplot as plt

# Cargar los datos del CSV
df = pd.read_csv('integrales.csv')

plt.figure(figsize=(10, 6))

# Graficamos las tres curvas acumulativas
plt.plot(df['x'], df['cajas'], 'o-', label='Integral Cajas (Riemann)', color='blue', markevery=2, alpha=0.7)
plt.plot(df['x'], df['trapecio'], 's-', label='Integral Trapecio', color='green', markevery=2, alpha=0.7)
plt.plot(df['x'], df['simpson'], label='Integral Simpson (Referencia Exacta)', color='red', linewidth=2.5)

# Títulos y estilo estilo "Paper de Física"
plt.title('Función de Área Acumulada para la Distribución Gaussiana', fontsize=14, fontweight='bold')
plt.xlabel('Límite Superior de Integración (x)', fontsize=12)
plt.ylabel('Área Acumulada $F(x) = \int_{0}^{x} f(t)dt$', fontsize=12)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(fontsize=11)

# Guardar la imagen automáticamente para tus compañeros
plt.savefig('curvas_integrales_gaussiana.png', dpi=300)
plt.show()



df_err = pd.read_csv('error_integrales.csv')

plt.figure(figsize=(10, 6))
plt.loglog(df_err['h'], df_err['err_cajas'], 'o-', label='Cajas (Riemann) $O(h)$', color='blue')
plt.loglog(df_err['h'], df_err['err_trapecio'], 's-', label='Trapecio $O(h^2)$', color='green')
plt.loglog(df_err['h'], df_err['err_simpson'], 'd-', label='Simpson $O(h^4)$', color='red')

plt.gca().invert_xaxis() # Invertimos para leer de h grande a h chica
plt.title('Análisis Asintótico de Convergencia: Paso $h$ vs. Error Absoluto', fontsize=14, fontweight='bold')
plt.xlabel('Tamaño del paso $h$ (Escala Logarítmica)', fontsize=12)
plt.ylabel('Error Absoluto (Escala Logarítmica)', fontsize=12)
plt.grid(True, which="both", linestyle=':', alpha=0.6)
plt.legend(fontsize=11)

plt.savefig('error_integrales_loglog.png', dpi=300)
plt.show()