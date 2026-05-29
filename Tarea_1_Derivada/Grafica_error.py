import pandas as pd
import matplotlib.pyplot as plt

# 1. Leer el archivo CSV generado por tu C++ (Error.csv con nombres exactos)
df = pd.read_csv('Error.csv', skipinitialspace=True)

# 2. Configurar el tamaño de la ventana de la gráfica
plt.figure(figsize=(10, 6))

# 3. Graficar usando escala LOG-LOG y tus nombres EXACTOS de columnas
# Añadimos marcadores ('o-', 's-', 'd-') para ver cada punto calculado
plt.loglog(df['h'], df['error_derivada_a'], 'o-', label='Error Derivada Delantera (a)', linestyle='--')
plt.loglog(df['h'], df['error_derivada_b'], 's-', label='Error Derivada Trasera (b)', linestyle=':')
plt.loglog(df['h'], df['error_derivada_c'], 'd-', label='Error Derivada Central (c)', linestyle='-.')

# TRUCO VISUAL CLAVE: Invertimos el eje X para leer la gráfica de mayor a menor h
plt.gca().invert_xaxis()

# 4. Detalles visuales de la gráfica
plt.title('Análisis Numérico: Tamaño del paso (h) vs. Error Absoluto', fontsize=14)
plt.xlabel('Tamaño del paso h (Escala Logarítmica)', fontsize=12)
plt.ylabel('Error Absoluto (Escala Logarítmica)', fontsize=12)

# Rejilla adaptada para gráficos logarítmicos
plt.grid(True, which="both", linestyle=':', alpha=0.6)
plt.legend(fontsize=11)

# 5. Desplegar la gráfica
plt.show()