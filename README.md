# Universidad de Costa Rica; TCU-691: Tropicalización de la tecnología.

## Proyecto: 
Desarrollar un sistema de monitoreo en tiempo real para los buses internos del campus universitario, este sistema permitirá a los usuarios observar el recorrido de los buses en tiempo real, proporcionando información precisa y actualizada sobre la ubicación y el estado de los vehículos en circulación.

La implementación de este sistema se basa en una solución integrada que combina varios componentes clave de hardware y software, que incluyen una pantalla táctil, una Raspberry Pi, un Arduino, un módulo GPS y un modulo WiFi, específicamente la pantalla táctil es el punto de interacción principal para los conductores del bus, donde a través  de una interfaz intuitiva se facilita la interacción con el sistema, permitiendo a los usuarios ingresar sus credenciales e iniciar el rastreo de la unidad.

## Propuesta:
Para dar inicio al proyecto, se requiere crear una caja la cual se implementará dentro del bus, dicha caja posee:

- _Pantalla Táctil FNK0078:_ Proporcionará una interfaz interactiva para los usuarios, permitiéndoles ingresar sus credenciales y visualizar el estado del bus, será el medio principal a través del cual los usuarios interactuarán con el sistema.
- _Raspberry Pi 4:_ Gestionará la interfaz de login, manejando las entradas de usuario a través de la pantalla táctil y se encargará de enviar las credenciales al Arduino.
- _Módulo GPS:_ Este módulo se encargará de capturar las coordenadas de ubicación en tiempo real del bus, los datos proporcionados por el GPS incluirán la latitud, longitud y altitud del bus, así como la fecha y la hora de la captura de estos datos.
- _Módulo WiFi ESP-01:_ Permitirá la transmisión en tiempo real de los datos capturados por el Arduino al servidor remoto. 
- _Arduino:_ Actuará como el controlador principal para la captura de datos de login del Raspberry Pi, los datos de ubicación del módulo GPS y transmitirlos al servidor remoto a través del módulo WiFi ESP-01.

## Equipo
### Raspberry Pi 4
El modelo cuenta con un procesador Broadcom BCM2711 y un CPU Quad-Core Cortex-A72 a 1.5 GHz, este modelo está disponible con varias opciones de memoria RAM, incluyendo versiones de 2 GB, 4 GB y 8 GB. Incluye dos puertos USB 3.0 y dos puertos USB 2.0, lo que facilita la conexión de dispositivos periféricos y almacenamiento adicional, dispone de un puerto Ethernet Gigabit, para conectividad inalámbrica, el dispositivo incorpora WiFi 802.11ac y Bluetooth 5.0.

Está equipada con dos puertos micro HDMI que soportan resoluciones de hasta 4K, permitiendo la conexión de hasta dos monitores simultáneamente, además, dispone de un puerto GPIO de 40 pines que permite la conexión de varios accesorios y módulos adicionales. La alimentación, requiere un suministro de energía de 5V a 3A, el módulo de almacenamiento principal está basado en una tarjeta microSD, que se utiliza para el sistema operativo y los archivos de usuario. 

[Documentación completa](https://www.raspberrypi.com/documentation/)


### Freenove Touchscreen Monitor for Raspberry Pi
Tiene una resolución de 1024 x 600 píxeles, que proporciona una imagen clara y detallada, el monitor se conecta a la Raspberry Pi a través del puerto de pantalla de interfaz de serie (DSI), lo que permite una integración sencilla y directa sin necesidad de controladores adicionales.

En cuanto a la alimentación, el monitor se alimenta a través del mismo cable de conexión que el puerto DSI, eliminando la necesidad de una fuente de alimentación externa adicional para la pantalla. La configuración del monitor en el sistema operativo de la Raspberry Pi se realiza mediante ajustes en el archivo de configuración.


### Arduino UNO
Es una placa de desarrollo basada en el microcontrolador ATmega328P, opera a una frecuencia de 16 MHz, está equipada con 14 pines de entrada/salida digital, de los cuales 6 pueden usarse como salidas PWM (Pulse Width Modulation), además, dispone de 6 pines de entrada analógica.

Para la comunicación y la conexión de periféricos, la placa incluye un puerto USB tipo B para la programación y la comunicación con el ordenador, el cual se utiliza para cargar el código desde el entorno de desarrollo Arduino IDE al microcontrolador y para la comunicación serie durante la ejecución del programa, también cuenta con un conector de alimentación externo que puede recibir voltajes de entre 7V y 12V, lo que permite alimentar la placa de manera independiente de la conexión USB, incluye un regulador de voltaje interno que proporciona una salida de $5V$ para alimentar los componentes conectados a la placa, así como una salida de $3.3V$ para dispositivos que requieren un voltaje menor.

[Documentación completa](https://www.arduino.cc/reference/es/)


### Módulo GPS NEO-6M-1-001
Es un receptor GPS de alta precisión basado en el chip u-blox NEO-6M, está diseñado para proporcionar datos precisos de posicionamiento global, opera a una frecuencia de 1575.42 MHz, cuenta con 50 canales y ofrece una sensibilidad de hasta -161 dBm, el tiempo de arranque en frío es de aproximadamente 35 segundos y en caliente se realiza en alrededor de 1 segundo.

Opera con un voltaje de entre 3.3V y 5V con un consumo de corriente de aproximadamente 50 mA, la comunicación con el módulo se realiza a través de UART (TX/RX). 

Utiliza el protocolo de comunicación NMEA, enviando datos en mensajes estándar como GGA (Información de Posición Global), RMC (Recomendación de Mínima Información de Navegación), GSV (Información de Satélites Visibles) y GSA (Información de Navegación de Satélites). Para una comunicación efectiva, el puerto UART del microcontrolador debe estar configurado a 9600 baudios, con 8 bits de datos, sin paridad y 1 bit de parada.

[Documentación completa](https://content.u-blox.com/sites/default/files/products/documents/NEO-6_DataSheet_%28GPS.G6-HW-09005%29.pdf)


### Módulo WiFi ESP-01
Es una placa de expansión basada en el chip ESP8266, diseñado para proporcionar conectividad WiFi estable, opera en una banda de frecuencia de 2.4 GHz, está equipado con un procesador de 32 bits que puede funcionar a velocidades de hasta 80 MHz y cuenta con una memoria flash de 512 KB para el almacenamiento de firmware. La comunicación con el módulo se realiza a través de una interfaz UART (TX/RX).

Requiere una fuente de alimentación estable de 3.3V, conectar el módulo directamente a una fuente de 5V puede dañarlo, por lo que se recomienda utilizar un regulador de voltaje o un convertidor de nivel para asegurar el voltaje adecuado. 

Para entender el funcionamiento se muestra la descripción de cada pin del módulo Wifi ESP-01:

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

La configuración del módulo ESP-01 se realiza a través de [comandos AT](https://docs.espressif.com/projects/esp-at/en/release-v2.2.0.0_esp8266/AT_Command_Set/TCP-IP_AT_Commands.html#at-cipstatus-obtain-the-tcp-udp-ssl-connection-status-and-information) enviados mediante la comunicación serial UART, los comandos AT permiten configurar el módulo para conectarse a redes WiFi, establecer conexiones TCP/IP y manejar la comunicación de datos, dicho módulo cuenta con dos modos que se configuran a través de los puertos GPIO0 y GPIO2:

- _Modo UART:_ Utilizado para cargar un programa en la memoria Flash del modulo Wifi. Para este propósito es necesario tener el pin GPIO2 desconectado (pull-up interno) y el GPIO0 conectado a tierra al momento de encender/resetear el ESP-01.
- _Modo Flash Boot:_ Utilizado para ejecutar el programa cargado en la memoria Flash; por defecto el ESP-01 tiene guardado el firmware para ser controlado por medio del puerto serie con comandos AT. En este modo, los pines GPIO2 y GPIO0 deben estar desconectados dado que ambos tiene un pull-up interno.

[Documentación completa](https://www.microchip.ua/wireless/esp01.pdf)

### Logging de usuario:
Es crucial asegurar que solo los usuarios autorizados puedan interactuar con el sistema, la implementación del logging de usuario en este proyecto utiliza una pantalla táctil que proporciona una interfaz de usuario interactiva donde los operadores pueden ingresar sus credenciales, está conectada a una Raspberry Pi 4 que actúa como el controlador principal para la pantalla táctil y ejecuta el software necesario para recibir y procesar las credenciales, así como para enviar estas al Arduino, el cual recibe las credenciales de login y se comunica con el módulo WiFi ESP-01 para autenticar al usuario a través de una API. Esta configuración permite a los usuarios ingresar sus credenciales de manera interactiva y segura antes de acceder iniciar el sistema de monitoreo en tiempo real. 

#### Configuración del Hardware:
La pantalla táctil FNK0078 se conecta a la Raspberry Pi utilizando los pines GPIO y una conexión I2C para la interfaz táctil, seguidamente la Raspberry Pi se conecta al Arduino a través del puerto serial para enviar las credenciales de login ingresadas por el operador.

El Raspberry Pi requiere de una tarjeta SD con el sistema operativo precargado, para esto se utiliza la herramienta [Raspberry Pi imager](https://www.raspberrypi.com/software/) desde la cual se gestiona la selección de sistema según el modelo de la tarjeta y las necesidades de uso, posteriormente se requiere insertar la SD en el Raspberry Pi y completar la instalación. Se puede trabajar conectando periféricos (teclado y ratón) directamente a la placa o utilizando protocolo de administración remota Secure Shell (SSH), el cual se debe activar en la configuración del Raspberry Pi y se utiliza desde la terminal de la computadora ya sea [Windows](https://jarrodstech.net/how-to-raspberry-pi-ssh-on-windows-10/) o [Linux](https://www.raspberrypi.com/documentation/computers/remote-access.html#ssh).

#### Configuración del Software:
El Raspberry Pi ejecuta un programa en Python utilizando la biblioteca Tkinter para crear una interfaz gráfica, la cual permite ingresar el nombre de usuario y contraseña en la pantalla táctil, cuando se ingresan las credenciales la Raspberry Pi captura estos datos y los envía al Arduino a través de una conexión serial, el Arduino construye una solicitud HTTP en formato JSON con las credenciales recibidas y las envía a la API de login utilizando el módulo WiFi ESP-01, el Arduino procesa la respuesta de la API, si el login es exitoso, el sistema permite al operador continuar y comenzar el monitoreo en tiempo real del bus, si el login falla, el sistema solicita nuevamente las credenciales al operador. 

### Rastrear localización:
Para implementar el rastreo de localización, en este proyecto se utiliza un modulo GPS que proporciona las coordenadas una vez iniciada la interfaz de usuario al autenticar las credenciales, está conectado a un Arduino que actúa como el controlador principal para procesar las coordenadas recibidas y se comunica con el módulo WiFi ESP-01 para enviar los datos a través de una API. La frecuencia de envío se ajusta en función de los requerimientos del proyecto, con lo cual se permite a los usuarios del bus ver la localización de manera continua y precisa.

#### Configuración del Hardware:
La alimentación del GPS se conecta al Arduino, en GND y VCC en 5V, en cuanto a los pines seriales, RX se conecta al pin 3 del Arduino y TX se conecta al pin 4 del Arduino (según la codificación creada), las conexiones de este modulo se puede observar con mayor detalle en esta [guía](https://www.youtube.com/watch?v=ViZT5w7tPqI).

El modulo WiFi requiere una tensión entre 3.3V y 3.6V con una corriente superior a los 200mA, por lo cual se requiere una alimentación externa para asegurar el funcionamiento, en cuanto a los pines seriales, `TX` se conecta al pin 8 y `RX` requiere una tensión reducida, por lo que se hace un divisor de tensión y luego se conecta al pin 9 (según la codificación creada), esto se puede observar con mayor detalle en esta [guía](https://programarfacil.com/podcast/como-configurar-esp01-wifi-esp8266/#Firmware_para_el_ESP-01).

#### Pruebas funcionales del modulo GPS
![prueba gps](https://github.com/user-attachments/assets/e3b477a9-a8c8-43c0-bf31-6d104acc802f)

Se adjunta una imagen en donde se observa el modulo de GPS en funcionamiento a continuacion se detallan los datos específicos del formato, estos datos son separados por las comas:
- Hora en UTC
- Latitud.
- Longitud.
- Número de satélites.
- Dilución horizontal de posición.
- Altitud en metros sobre el nivel del mar.

#### Recomendaciones
- La antena de el módulo GPS tiene que estar directamente apuntando al cielo, ya que trabaja por medio satelital y en interiores no encuentra la posición.
- Para hacer uso y comprobación de ubicación en Google Maps con respecto a los datos de $GPGGA de latitud y longitud, nuestro GY-NEO6MV2 arroja un formato DMM y debemos convertirlo a formato DD que utiliza Maps.

#### Pruebas funcionales del modulo ESP-01

Debido a que se busca utilizar el ESP-01 como interfaz WiFi del arduino con el fin de enviar datos a un servidor, se hará uso de los comandos AT para la configuración y comunicación del modulo:

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

![Prueba de envío mediante Serial Monitor: configuración](https://github.com/user-attachments/assets/e96d5079-79be-4039-9d9d-5c853f4dbe68)

![Prueba de envío mediante Serial Monitor: envío de datos](https://github.com/user-attachments/assets/db9a7898-3f8f-4760-bc70-c3b4689fba83)

**Notas:** 

**1.** Se debe añadir la tarjeta del módulo ESP-01 a Arduino, para ello se recomienda seguir los pasos vistos en el siguiente [enlace](https://programarfacil.com/podcast/como-configurar-esp01-wifi-esp8266/).

**2.** Se debe deshabilitar el microcontrolador del Arduino, por lo que se conecta el pin RST a GND.

**3.** Para el funcionamiento correcto se debe cambiar el ajuste de línea a "Both NL & CR" y el Baud rate a 115200.

Debido a que los comandos AT requieren un tiempo de respuesta significativo, para simplificar el desarrollo, reducir la complejidad en la ejecución y mejorar la funcionalidad se opta por utilizar la librería WiFiEspAT de Arduino, la cual trabaja internamente los comandos AT ya mencionados y proporciona una interfaz más amigable y directa para la programación del ESP-01.

La librería se instala desde el administrador de bibliotecas en el IDE de Arduino y se incluye normalmente en el sketch, en la función `setup()`, se inicializa la librería con `Serial.begin(115200)` para establecer la comunicación serial y `WiFi.init(&Serial)` para inicializar la librería WiFiEspAT.

Al simplificar los comandos AT directos, ahora se tiene:
- `WiFi.mode(WIFI_MODE_STA)`: Station mode
- `WiFi.mode(WIFI_MODE_AP)`: SoftAP mode
- `WiFi.mode(WIFI_MODE_APSTA)`: SoftAP+Station mode
- `WiFi.begin("SSID", "PASSWORD")`: para conectar a una red WiFi, reemplazando "SSID" y "PASSWORD" con los valores correspondientes. 
- `serial.println(WiFi.localIP())`: para obtener la IP del módulo.
- `WiFi.configMulti(a)`: Habilita la conexión múltiple del modulo, `a` admite valores 1 y 2.
- `WiFi.disconnect()`: para desconectar de la red WiFi.

#### Configuración del Software:
El Arduino ejecuta un programa utilizando las bibliotecas TinyGPS+, SoftwareSerial, ArduinoJson y WiFiEspAT, para crear la interfaz de rastreo, cuando se autentica correctamente, se inicia una conexión serial por software, donde se extraen datos del GPS, el Arduino construye una solicitud HTTP en formato JSON con las coordenadas recibidas y las envía a la API de posición utilizando el módulo WiFi ESP-01, iniciando el monitoreo en tiempo real del bus, el cual se actualiza cada 10 segundos. 

En la configuración inicial, se inicializa la comunicación serial con el módulo GPS y el módulo ESP8266 y se verifica que la conexión sea exitosa antes de proceder, el programa lee continuamente los datos del GPS, cuando los datos están disponibles, se llama a la función encargada de procesar estos datos (`gpsData`), si el GPS no responde en un tiempo razonable, se muestra un mensaje de error y se detiene la ejecución.

La función `connectToWiFi` se define para conectar el módulo ESP8266 a la red WiFi, esta función intenta conectar a la red utilizando las credenciales proporcionadas y verifica el estado de la conexión, la función `gpsData` se encarga de extraer los datos del GPS y serializarlos en un objeto JSON, los datos incluyen la latitud, longitud, altitud, fecha y hora, la función verifica la validez de los datos extraídos antes de agregarlos al objeto JSON.

La función `sendToAPI` se define para enviar los datos serializados en JSON a la API de localización, esta función construye y envía una solicitud HTTP POST, donde la URL se divide en host, puerto y ruta para construir correctamente la solicitud HTTP.

