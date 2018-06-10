Explicar: ¿qué significa “estar alineado”?

Decir que algo esta por ejemplo alineado a 8 bytes quiere decir que esta en una direccion de memoria que es un mùltiplo de 8.
Algunas CPUs solo cargaran datos de ubicaciones alineadas, otros cargaran datos de cualquier ubicacion pero si es una ubicacion
alineada sera mucho màs rapido. 

El bus a la memoria no es de un solo byte, tipicamente es de 4/8bytes o mas, esto quiere decir que cuando el CPU hace
un fetch le llegan 4/8 o mas bytes de informacion a partir de la direccion solicitada
Como consecuencia de esto, los ultimos bits menos significativos de una direccion de memoria no son
tenidos en cuenta a veces, la memoria solo puede ser leida o escrita en direcciones multiples del 
tamaño del bus. Si hacemos un request de un byte que comienza en la direccion "9" con un bus de 8 bytes, el CPU va
a solicitar a la memoria un bloque de bytes que comienza en la direccion 8 y luego cargar el segundo en un registro y descartar
el resto.

Un acceso desalineado implica dos fetchs, si se solicitaran 8 bytes a partir de la direccion 9 de memoria, se tienen que ler
8 a partir de la direccion 8, y otros 8 a partir de la direccion 16, y luego hacer un mask. Es por eso que es importante estar
alineado
