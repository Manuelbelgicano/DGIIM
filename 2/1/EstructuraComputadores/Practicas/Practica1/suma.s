.section .data
lista:
	.int 12345678,23456789,34567890,45678901,56789012,67890123,78901234,89012345
	.int 10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000
	.int 20202020,10101010,30303030,40404040,50505050,60606060,70707070,80808080
	.int 11223344,55667788,99001122,33445566,77889900,99887766,55443322,11009988

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
	inc       %esi
	cmp  %esi,%ecx
	jne bucle

	pop %esi
	ret
