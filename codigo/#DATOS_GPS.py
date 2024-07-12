import serial
import os
from datetime import datetime
import time


# Configura el puerto serie (ajusta el nombre del puerto según sea necesario)
ser = serial.Serial('COM9', 9600)  # Reemplaza 'COM9' con el puerto correcto


# Obtiene la ruta del directorio donde se encuentra este script
script_dir = os.path.dirname(os.path.abspath(__file__))


# Crea el nombre del archivo en la misma carpeta que el script
file_path = os.path.join(script_dir, 'gps_data.txt')


try:
    # Abre un archivo TXT para escribir los datos
    with open(file_path, 'a') as file:
        while True:
            try:
                start_time = time.time()


                # Variables para almacenar las sentencias GPS
                gpgga_data = ""
                gpgll_data = ""


                while True:
                    # Lee una línea de datos del puerto serie
                    line = ser.readline().decode('utf-8').strip()


                    # Verifica si la línea comienza con $GPRMC o $GPGLL
                    if line.startswith('$GPGGA'):
                        gpgga_data = line
                    elif line.startswith('$GPGLL'):
                        gpgll_data = line


                    # Si ambas sentencias han sido recibidas, guarda los datos
                    if gpgga_data and gpgll_data:
                        # Agrega un campo de tiempo a las líneas de datos
                        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                        data_with_timestamp = f"[{timestamp}] {gpgga_data}\n[{timestamp}] {gpgll_data}\n"


                        # Escribe las líneas de datos en el archivo
                        file.write(data_with_timestamp)
                        file.flush()  # Asegura que los datos se guarden inmediatamente


                        print(f"Datos recibidos y guardados: {data_with_timestamp}")


                        # Reinicia las variables de datos
                        gpgga_data = ""
                        gpgll_data = ""


                        # Espera hasta que haya pasado un minuto
                        elapsed_time = time.time() - start_time
                        if elapsed_time < 60:
                            time.sleep(60 - elapsed_time)
                        break


            except KeyboardInterrupt:
                print("Programa terminado por el usuario")
                break
            except Exception as e:
                print(f"Error: {e}")
except Exception as e:
    print(f"Error al abrir el archivo: {e}")
finally:
    ser.close()
    print(f"Los datos se han guardado en: {file_path}")