.section .data
lista:
	.long 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,100000000
	.long 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,100000000
	.long 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,100000000
	.long 1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,100000000
longlista:
	.int (.-lista)/4

resultado:
	.quad -1

.section .text
_start:	.global _start
	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, resultado
	mov %edx, resultado+4

	mov $1, %eax
	mov $0, %ebx
	int $0x80

suma:
	push %esi
	mov $0, %edx
	mov $0, %esi
	mov $0, %eax

bucle:
	add (%ebx,%esi,4), %eax
	adc $0, %edx
	inc %esi
	cmp %esi,%ecx
	jne bucle

	pop %esi
	ret
