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
Almacenar las coordenadas GPS en un arreglo o envíalas directamente a un servidor.
Configura un servidor que reciba y almacene los datos enviados por el Arduino.

#### Opciones de servidor:
- Usar un servicio de alojamiento web
- Configurar un servidor local
- Servidor en la nube

#### Para realizar la conexión del modulo y el arduino se recomienda ver el siguiente video:
https://www.youtube.com/watch?v=ViZT5w7tPqI
