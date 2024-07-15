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

#### Paso 2:

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

### Paso 5
-Investigar funcionanmiento y conexión de ESP-01, para poder hacer uso de WiFi.

-Trabaja con 3.3v, tener cuidado de no conectarle 5v porque se quema.
