.section .data
lista:
	.int 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000
	.int 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000
	.int 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000
	.int 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000

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
	push %esi
	mov $0, %edx 			#Acumulador de acarreos
	mov $0, %esi			#Índice
	mov $0, %eax			#Suma de elementos

bucle:
	add (%ebx,%esi,4), %eax		#Suma de elementos
	adc $0, %edx			#Suma de acarreos
	inc %esi			#aumento del índice
	cmp %esi,%ecx			#comparación del índice actual con el último
	jne bucle

	pop %esi
	ret
