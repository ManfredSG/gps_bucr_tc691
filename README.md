# Universidad de Costa Rica; TCU-691: Tropicalización de la tecnología.

## Proyecto: 
Desarrollar un prototipo para los buses internos, en donde mediante la implementación de un Arduino, un módulo GPS y pantallas, se pueda observar el recorrido en tiempo real de estos.

## Propuesta:
Para dar inicio al proyecto, se requiere crear una caja la cual se implementará dentro del bus, dicha caja posee el arduino, un módulo de WIFI y un módulo de gps. 
Como primera parte, se espera tener un logging, en donde mediante el arduino se haga una solicitud de ingreso y con ello pueda accesar a un "botón" de inicio y final del viaje, seguidamente se pueda rastrear el recorrido del bus, para finalmente "enviar los datos" de la posición.
(Esta es una propuesta general y base, a la cual se le pueden hacer cambios y mejoras.)

### Logging de usuario:
Para realizar el logging de usuario se propone utilizar un display de 7 segmentos y se usan tres botones: uno para aumentar el valor del dígito, uno para avanzar al siguiente dígito, y uno para confirmar el ingreso.
Tener una función enterPIN() maneja el ingreso del PIN. Los valores ingresados se comparan con el PIN correcto almacenado.
El display de 7 segmentos muestra el valor del dígito actual usando la función displayDigit().
La función de validación del PIN compara el PIN ingresado con el correcto.
Si el PIN es correcto, el rastreo se inicia, de lo contrario, se solicita el ingreso del PIN nuevamente.
(La idea principal es que se haga el rastreo solo cuando esta loggeado el usuario).

### Botón de inicio y fin de viaje:
Si el PIN es correcto entonces se inicia con el rastreo.
Para finalizar el rastreo se presiona el mismo botón de confirmación.

### Rastrear localización:
Para rastrear la localización se propone crear una función de "tracking" y si es true, las coordenadas GPS se envían al servidor cada X cantidad de segundos utilizando una función sendGPSData().

### Enviar datos:
Almacenar las coordenadas GPS en un arreglo o enviarlas directamente a un servidor.
Configurar un servidor que reciba y almacene los datos enviados por el Arduino.

#### Opciones de servidor:
- Usar un servicio de alojamiento web
- Configurar un servidor local
- Servidor en la nube

### Paso 2:

Iniciar el armado y conexiones del Arduino, el módulo de GPS y el display de 7 segmentos, además de los botones para realizar las pruebas.

#### Para realizar la conexión del modulo y el arduino se recomienda ver el siguiente video:
https://www.youtube.com/watch?v=ViZT5w7tPqI

#### Documento de Overleaf del proyecto
https://www.overleaf.com/project/666ca35c0123c4f0aee49700


#### Pruebas funcionales del modulo GPS
![prueba gps](https://github.com/user-attachments/assets/e3b477a9-a8c8-43c0-bf31-6d104acc802f)

Se adjunta una imagen en donde se observa el modulo de GPS en funcionamiento a continuacion se detallan los datos específicos del formato, estos datos son separados por las comas:
- Hora en UTC
- Latitud.
- Longitud.
- Número de satélites.
- Dilución horizontal de posición.
- Altitud en metros sobre el nivel del mar.

  Cabe resaltar que la antena de el módulo GPS tiene que estar directamente apuntando al cielo, ya que trabaja por medio satelital y en interiores no encuentra la posición.

### Paso 3
- Se debe de conseguir la botonera o un teclado matricial 4x4.
- Se debe de realizar la simulación del dispositivo conectado con el display, además de ver el consumo de los componentes, para proceder con el armado.
- Se debe de buscar que método usar para la alimentación.

### Paso 4
- Convertir y darle significado a los datos que arroja el GPS en el Arduino.
- Extraer los datos a un .JSON o carpeta en la computadora.

Se realizó un código para enviar los datos del Arduino a Python, dado que el Arduino como tal no puede generar un archivo sin una memoria, el cual se encuentra en la carpeta de código con el nombre de “Arduino_a_Python"

También se hizo un código en Python que extrae solo 2 datos, el $GPGGA y $GPGLL como primer intento de hacer la extracción de la totalidad de los datos, en intervalo de cada 1 minuto, este código también se encuentra en la carpeta de código con el nombre de “#DATOS_GPS"
- La extracción de datos de Arduino a Python quedó descartada de momento, se va a realizar un envío de datos hacia una url.

### Paso 5
- Investigar funcionamiento y conexión de ESP-01, para poder hacer uso de WiFi.
- Se busca enviar los datos a una dirección url.
- El ESP-01 trabaja con 3.3v y admite máximo 3.6v, tener cuidado de no conectarle 5v porque se quema.
- Se recomienda intensidad mayor a 200mA.
- Se adquirió un uJPM Módulo suplidor de potencia 3.3V - 5v, con el cual se logra suplir los 3.3v y 200mA requeridos por el ESP-01 y se logra hacer la conexión a WiFi.

### Descripción de conexión Arduino a ESP-01
| Nº | Nombre del Pin | Función |
|----|----------------|---------|
| 1  | GND            | GND     |
| 2  | GPIO2          | GPIO, Pull-up Interno |
| 3  | GPIO0          | GPIO, Pull-up Interno |
| 4  | RXD            | UART0, pin de datos recibidos RXD |
| 5  | VCC            | Fuente de alimentación de 3.3V (VDD) |
| 6  | RST            | Pin de reset externo, activo bajo |
| 7  | CH_PD          | Pin de habilitación del chip. Activo alto |
| 8  | TXD            | UART0, pin de datos enviados TXD |

*Tabla 1: Descripción de los Pines para el ESP-01*


### Paso 6
- Investigar uso de comandos AT para hacer la exportación de datos del ESP-01 a url, ya lograda la conexión a WiFi.

#### Comandos AT para la configuración y comunicación del módulo

A continuación se describen los comandos AT utilizados por el momento para la configuración y comunicación del módulo:

- `AT+CWMODE=a`: Indica el modo de funcionamiento del módulo, sustituir `a` por:
    - 1: Station mode.
    - 2: SoftAP mode.
    - 3: SoftAP+Station mode.
- `AT+CWLAP`: Muestra en el serial monitor las redes WiFi disponibles.
- `AT+CWJAP="SSID","PASSWORD"`: Establece la conexión con una red WiFi, sustituir SSID por el nombre de la red y PASSWORD por la contraseña.
- `AT+CIFSR`: Muestra las direcciones IP relacionadas a la conexión actual del módulo, se identifica la IP estática que corresponde al módulo (`:STAIP`).
- `AT+CIPMUX=a`: Habilita la conexión múltiple del módulo, `a` admite valores 1 y 2.
- `AT+CIPSERVER=a,b`: Indica el manejo del servidor, sustituir `a` y `b` por:
    - `a=1`: para habilitar el servidor.
    - `a=0`: para deshabilitar el servidor.
    - `b`: por el puerto que se utiliza.
- `AT+CIPSEND=0,b`: Indica la longitud de los datos que se enviarán al servidor, sustituir `b` por una cantidad mayor o igual al número de caracteres que se utilizan.
- `AT+CIPCLOSE=0`: Envía el mensaje a la dirección planteada.

#### Pruebas funcionales del modulo ESP-01

![Prueba de envío mediante Serial Monitor: configuración](https://github.com/user-attachments/assets/e96d5079-79be-4039-9d9d-5c853f4dbe68)

![Prueba de envío mediante Serial Monitor: envío de datos](https://github.com/user-attachments/assets/db9a7898-3f8f-4760-bc70-c3b4689fba83)

**Nota 1:** Se debe añadir la tarjeta del módulo ESP-01 a Arduino, para ello se recomienda seguir los pasos vistos en el siguiente [enlace](https://programarfacil.com/podcast/como-configurar-esp01-wifi-esp8266/).

**Nota 2:** Se debe deshabilitar el microcontrolador del Arduino, por lo que se conecta el pin RST a GND.

**Nota 3:** Para el funcionamiento correcto se debe cambiar el ajuste de línea a "Both NL & CR" y el Baud rate a 115200.

### Recomendaciones
- Para hacer uso y comprobación de ubicación en Google Maps con respecto a los datos de $GPGGA de latitud y longitud, nuestro GY-NEO6MV2 arroja un formato DMM y debemos convertirlo a formato DD que utiliza Maps.
