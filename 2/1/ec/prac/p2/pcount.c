#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define WSIZE 8*sizeof(int)
#define SIZE (1<<16)
int lista[SIZE];
int resultado=0;

/**
 * @brief Cálculo del peso Hamming con bucle for
 */
int pcount_1(unsigned* array, int len) {
    int  i, j, res=0;
    for (i=0; i<len; i++){
	for (j = 0; j < WSIZE; j++) {
		unsigned mask = 0x1 << j;
		res += (array[i] & mask) != 0;
	}
    }
    return res;
}

/**
 * @brief Cálculo del peso Hamming con bucle while
 */
int pcount_2(unsigned* array, int len) {
    int  i, j, res=0;
    for (i=0; i<len; i++){
	unsigned x=array[i];
		do {
			res += x & 0x1;
			x >>= 1;
		} while (x);
	}
  
    return res;
}

/**
 * @brief Cálculo del peso Hamming con un bucle escrito en ensamblador
 */
int pcount_3(unsigned* array, int len) {
    int  i, res=0;
    for (i=0; i<len; i++){
	unsigned x =array[i];
	asm("\n"
	"bucle:		\n\t"
	"shr %[x]	\n\t"
	"adc $0, %[r]	\n\t"
	"cmp $0, %[x]	\n\t"
	"jne bucle	\n\t"
	: [r] "+r" (res)
	: [x] "r" (x));	
	
    }
    return res;
}
/**
 * @brief Cálculo del peso Hamming mediante comparaciones con una máscara 
 * diferente.
 */
int pcount_4(unsigned* array, int len) {
	int i, k;
	int result = 0;
	for (i = 0; i < len; i++) {
		int val = 0;
		unsigned x = array[i];
		for (k = 0; k < 8; k++) {
			val += x & 0x01010101;
			x >>= 1;
		}

	val += (val >> 16);
	val += (val >> 8);
	result += (val & 0xff);
	}
	return result;
}

/**
 * @brief Cálculo del peso Hamming con ensamblador
*/
int pcount_5(unsigned* array, int len) {
	int i;
	int val, result = 0;
	int SSE_mask[] = { 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f };
	int SSE_LUTb[] = { 0x02010100, 0x03020201, 0x03020201, 0x04030302 };
	if (len & 0x3)
		printf("leyendo 128b pero len no multiplo de 4?\n");
	for (i = 0; i < len; i += 4) {
	
		asm("movdqu %[x], %%xmm0 	\n\t"
		"movdqu %[m], %%xmm6 		\n\t"
		"movdqa %%xmm0, %%xmm1 		\n\t"
		"psrlw $4, %%xmm1 		\n\t"
		"pand %%xmm6, %%xmm0 		\n\t"
		"pand %%xmm6, %%xmm1 		\n\t"
		"movdqu %[l], %%xmm2 		\n\t"
		"movdqa %%xmm2, %%xmm3 		\n\t"
		"pshufb %%xmm0, %%xmm2 		\n\t"
		"pshufb %%xmm1, %%xmm3 		\n\t"
		"paddb %%xmm2, %%xmm3 		\n\t"
		"pxor %%xmm0, %%xmm0 		\n\t"
		"psadbw %%xmm0, %%xmm3 		\n\t"
		"paddd %%xmm3, %%xmm0 		\n\t"
		"movd %%xmm0, %[val] 		\n\t"
		: [val]"=r" (val)
		: [x] "m" (array[i]),
		[m] "m" (SSE_mask[0]),
		[l] "m" (SSE_LUTb[0])

		);

		result += val;
	}
	return result;
}
/**
 * @brief Cálculo del peso Hamming usando una instrucción propia de asm llamada
 * POPCNT.
 */
int pcount_6(unsigned * array, int len) {
	int i;
	unsigned x;
	int val, res=0;
	for(i=0; i<len; i++) {
		x=array[i];
		asm("popcnt %[x], %[val]"
		: [val] "=r" (val)
		: [x] "r" (x)
		);
		res+=val;
	}
	return res;
}

void crono(int (*func)(), char* msg) {
    struct timeval tv1,tv2;
    long tv_usecs;

    gettimeofday(&tv1,NULL);
    resultado = func(lista,SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
}

int main() {
	int i;
	for (i=0; i<SIZE; i++)
		lista[i]=i;

	crono(pcount_1,"(1ª versión)");
	crono(pcount_2,"(2ª versión)");
	crono(pcount_3,"(3ª versión)");
	crono(pcount_4,"(4ª versión)");
	crono(pcount_5,"(5ª versión)");
	crono(pcount_6,"(6ª versión)");

	exit(0);
}
