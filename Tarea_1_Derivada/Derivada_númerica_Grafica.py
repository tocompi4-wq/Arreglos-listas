import pandas as pd
import matplotlib.pyplot as plt

# Lee el archivo CSV generado por C++
# Uso skipinitialspace=True para que borre automáticamente los espacios después de las comas
df = pd.read_csv('Derivadas.csv', skipinitialspace=True)

# Configurar el tamaño de la ventana de la gráfica
plt.figure(figsize=(10, 6))

# Graficar usando los nombres EXACTOS que pusiste en tu C++
# Nota que usamos 'f(x)' entre comillas simples porque así se llama tu columna
# plt.plot(df['x'], df['f(x)'], label='f(x) original', linewidth=2, color='black')
plt.plot(df['x'], df['derivada_a'], label='Derivada Delantera (a)', linestyle='--')
plt.plot(df['x'], df['derivada_c'], label='Derivada Central (c)', linestyle='-.')
plt.plot(df['x'], df['derivada_b'], label='Derivada Trasera (b)', linestyle=':')
plt.plot(df['x'], df['derivada'], label='Derivada Analítica', linestyle='-.')

# Detalles de la gráfica
plt.title('Función Gaussiana y sus Derivadas Numéricas', fontsize=14)
plt.xlabel('Eje X', fontsize=12)
plt.ylabel('Eje Y', fontsize=12)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(fontsize=11)

plt.show()