.section .data
lista:
	.int 1,-2,3,-4,1,-2,3,-4
	.int 1,-2,3,-4,1,-2,3,-4
	.int 1,-2,3,-4,1,-2,3,-4
	.int 1,-2,3,-4,1,-2,3,-4

longlista:
	.int (.-lista)/4

resultado:
	.quad -1

.section .text
main: .global main

	#Parametros iniciales
	mov    $lista, %ebx
	mov longlista, %ecx

	#Desarrollo del programa
	call suma
	mov %eax, resultado
	mov %edx, resultado+4

	#Salida del programa
	mov $1, %eax
	mov $0, %ebx
	int $0x80

suma:
	#Guardamos la informacion de los registros
	push %esi
	push %edi
	push %ebp
	mov $0, %edx 			#Variable con el signo para el acarreo
	mov $0, %esi			#Indice del array lista
	mov $0, %eax			#Variable auxiliar con los elementos de lista
	mov $0, %edi			#Acumulador de acarreo
	mov $0, %ebp			#Acumulador

bucle:
	mov (%ebx,%esi,4), %eax		#Asignamos el elemento i-esimo de lista a nuestro registro
	cdq				#Extendemos el signo a %edx
	add %eax,%ebp			#Realizamos la suma
	adc %edx, %edi			#Sumamos el acarreo
	inc %esi			#Aumentamos el indice
	cmp %esi,%ecx			#Comparamos el indice actual con el tamaño del array lista
	jne bucle

	#Almacenamos los valores en los registros que vamos a usar en main
	mov %ebp, %eax
	mov %edi, %edx

	#Sacamos los antiguos valores de los registros de la pila
	pop %ebp
	pop %edi
	pop %esi

	ret
