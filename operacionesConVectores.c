/*
 * operacionesConVectores.c
 *
 *  Created on: 10 mar 2023
 *      Author: nakal
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "operacionesConVectores.h"


VectorMejorado_t* VectorMejorado() {
	VectorMejorado_t *self;

	self = (VectorMejorado_t*)malloc(sizeof(VectorMejorado_t));
	if (self == NULL) {
		return NULL;
	}

	self->vec = NULL;
	self->len = 0;

	return self;
}

VectorMejorado_t* VectorMejoradoWithLength(unsigned int n) {
	VectorMejorado_t *self;

	self = VectorMejorado();
	if (self == NULL || n == 0) {
		return NULL;
	}

	self->len = n;
	self->vec = calloc(n, sizeof(int));
	if (self->vec == NULL) {
		free(self);
		return NULL;
	}

	return self;
}

VectorMejorado_t* VectorMejoradoCC(VectorMejorado_t *self) {
	VectorMejorado_t *copy;
	unsigned int i;

	copy = VectorMejoradoWithLength(self->len);

	if (copy == NULL) {
		return NULL;
	}

	for (i = 0; i < self->len; i++) {
		copy->vec[i] = self->vec[i];
	}

	return copy;
}

VectorMejorado_t* RedimensionarVector(VectorMejorado_t *self, unsigned int n) {
	unsigned int i;

	//Para poder usar realloc tengo que  redimensionar el vector actual,
	//no lo puedo guardar en otra variable y despues devolverla.

	if (self == NULL) {
		return VectorMejoradoWithLength(n);
	}

	self->vec = realloc(self->vec, n * sizeof(int));
	if (self->vec == NULL) {
		return NULL;
	}

	for (i = self->len; i < n; i++) {
		self->vec[i] = 0;
	}
	self->len = n;

	return self;
}

int imprimirVector(VectorMejorado_t *self) {
	unsigned int i;

	if (self != NULL && self->vec != NULL) {
		if (self->len > 0) {
			printf("[");
			for (i = 0; i < self->len - 1; i++) {
				printf("%d, ", self->vec[i]);
			}

			printf("%d]\n", self->vec[self->len - 1]);
			fflush(0);
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		return -2;
	}
}

void asignarValores(VectorMejorado_t *self, int seed) {
	unsigned int i;

	if (self != NULL && self->vec != NULL) {
		srand(seed);
		for (i = 0; i < self->len; i++) {
			self->vec[i] = rand();
		}
	}
}


void DestruirVector(VectorMejorado_t *self) {

	if (self != NULL) {
		free (self->vec);
	}

	free(self);
}

int asignarVector(const VectorMejorado_t *self1, VectorMejorado_t *self2) {
	unsigned int i;

	if (self1 != NULL && self2 != NULL && self1 != self2 && self1->vec != NULL && self2->vec != NULL) {
		if (self1->len == self2->len) {
			for (i = 0; i < self1->len; i++) {
				self2->vec[i] = self1->vec[i];
			}
		}
		else {
			realloc(self2->vec, self1->len * sizeof(int));
			if (self2->vec == NULL) {
				return -1;
			}
			self2->len = self1->len;
			asignarVector(self1, self2);
		}
	}
	else {
		return -2;
	}
	return 0;
}

int compararVector(VectorMejorado_t *self1, VectorMejorado_t *self2) {
	unsigned int i;

	if (self1 != NULL && self2 != NULL && self1 != self2 && self1->vec != NULL && self2->vec != NULL) {
		if (self1->len == self2->len) {
			for (i = 0; i < self1->len; i++) {
				if (self1->vec[i] != self2->vec[i]) {
					return 0;
				}
			}
			return 1;
		}
		else return 0;
	}
	else {
		return -1;
	}
}

int hayOtro(VectorMejorado_t *self, int n) {
	unsigned int i;

	if (self != NULL && self->vec != NULL) {
		for (i = 0; i < self->len; i++) {
			if (self->vec[i] == n) {
				return 1;
			}
		}
		return 0;
	}
	else {
		return 0;
	}
}

void ordenarVector(VectorMejorado_t *self) {
	unsigned int i, j;
	int aux;

	if (self != NULL && self->vec != NULL) {
		for (i = 0; i < self->len; i++) {
			for (j = i + 1; j < self->len; j++) {
				if (self->vec[j] < self->vec[i]) {
					aux = self->vec[j];
					self->vec[j] = self->vec[i];
					self->vec[i] = aux;
				}
			}
		}
	}
}

int productoEscalar(VectorMejorado_t *self1, VectorMejorado_t *self2, int *resultado) {
	int prod = 0;
	int i;

	if (self1 != NULL && self2 != NULL && self1 != self2 && self1->vec != NULL && self2->vec != NULL) {
		if (self1->len == self2->len){
			for (i = 0; i < self1->len; i++) {
				prod += self1->vec[i] * self2->vec[i];
			}
			*resultado = prod;
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		return -2;
	}
}

int maximo(VectorMejorado_t *self, int *resultado) {
	int  max = self->vec[0];
	unsigned int i;

	if (self != NULL && self->vec != NULL) {
		for (i = 1; i < self->len; i++) {
			if (self->vec[i] > max) {
				max = self->vec[i];
			}
		}
		*resultado = max;
		return 0;
	}
	else {
		return -1;
	}
}

int minimo(VectorMejorado_t *self, int *resultado) {
	int  min = self->vec[0];
	unsigned int i;

	if (self != NULL && self->vec != NULL) {
		for (i = 1; i < self->len; i++) {
			if (self->vec[i] < min) {
				min = self->vec[i];
			}
		}
		*resultado = min;
		return 0;
	}
	else {
		return -1;
	}
}

VectorMejorado_t* invertido(VectorMejorado_t *self) {
	unsigned int i;
	VectorMejorado_t* aux = VectorMejoradoCC(self);

	if (self != NULL && self->vec != NULL) {
		for (i = 0; i < self->len; i++) {
			aux->vec[i] = self->vec[self->len - i - 1];
		}
		return aux;
	}
	else {
		return NULL;
	}
}

int media(VectorMejorado_t *self, float *resultado) {
	int suma = 0;
	unsigned int i;

	if (self != NULL && self->vec != NULL) {
		for (i = 0; i < self->len; i++) {
			suma += self->vec[i];
		}
		*resultado = (float)suma / (float)self->len;
		return 0;
	}
	else {
		return -1;
	}
}

int mediana(VectorMejorado_t *self, float *resultado) {

//Si len es par, devulevo la media entre los valores centrales. Y si es impar, devulvo el valor central.

	if (self != NULL && self->vec != NULL) {
		ordenarVector(self);
		if (self->len % 2 == 0) {
			*resultado = (float)(self->vec[(self->len / 2) - 1] + self->vec[self->len / 2]) / (float)2;
			return 0;
		}
		else {
			*resultado = (float)self->vec[((self->len + 1) / 2) - 1];
			return 0;
		}
	}
	else {
		return -1;
	}
}

VectorMejorado_t* moda(VectorMejorado_t *self) {
	VectorMejorado_t *contador = NULL;
	VectorMejorado_t *resultado = NULL;
	VectorMejorado_t *aux = NULL;
	unsigned int i, j;
	int max, err;

	//Voy guardando en aux los numeros sin repetirlos y en contador el numero de repeticiones

	contador = VectorMejorado();
	resultado = VectorMejorado();
	aux = VectorMejorado();
	if (contador == NULL || resultado == NULL || aux == NULL) {
		return NULL;
	}

	for (j = 0; j < self->len; j++) {
		if (!hayOtro(aux, self->vec[j])) {
			aux = RedimensionarVector(aux, aux->len + 1);
			contador = RedimensionarVector(contador, contador->len + 1);
			if (contador == NULL || aux == NULL) {
				return NULL;
			}
			contador->vec[contador->len - 1]++;
			aux->vec[aux->len - 1] = self->vec[j];

			for (i = j + 1; i < self->len; i++) {
				if (self->vec[j] == self->vec[i]) {
					contador->vec[contador->len - 1]++;
				}
			}
		}
	}
//	printf("contador: ");
//	imprimirVector(contador);
//	printf("aux: ");
//	imprimirVector(aux);

	//Ahora voy guardando en resultado los numeros de aux cuyo correspondiente de contador es igual al maximo de contador y devuelvo resultado.

	err = maximo(contador, &max);
	if (!err) {
		for (i = 0; i < self->len; i++) {
			if (contador->vec[i] == max) {
				resultado = RedimensionarVector(resultado, resultado->len + 1);
				if (resultado == NULL) {
					DestruirVector(contador);
					DestruirVector(aux);
					return NULL;
				}
				else {
					resultado->vec[resultado->len - 1] = aux->vec[i];
				}
			}
		}
		DestruirVector(contador);
		DestruirVector(aux);
		return resultado;
	}
	else {
		DestruirVector(contador);
		DestruirVector(aux);
		return NULL;
	}


}

void probarModa() {
	VectorMejorado_t *mi_vector_mejorado1 = NULL;

	mi_vector_mejorado1 = VectorMejoradoWithLength(4);
	printf("La moda del vector: ");
	imprimirVector(mi_vector_mejorado1);
	printf("es:");
	imprimirVector(moda(mi_vector_mejorado1));

	mi_vector_mejorado1->vec[0] = 1;
	mi_vector_mejorado1->vec[1] = 3;
	mi_vector_mejorado1->vec[2] = 3;
	mi_vector_mejorado1->vec[3] = 2;

	printf("La moda del vector: ");
	imprimirVector(mi_vector_mejorado1);
	printf("es:");
	imprimirVector(moda(mi_vector_mejorado1));

	printf("La moda del vector: ");
	RedimensionarVector(mi_vector_mejorado1, 6);
	imprimirVector(mi_vector_mejorado1);
	printf("es:");
	imprimirVector(moda(mi_vector_mejorado1));

	DestruirVector(mi_vector_mejorado1);

}

VectorMejorado_t* sumarVectores(VectorMejorado_t *self1, VectorMejorado_t *self2) {
	unsigned int i;
	VectorMejorado_t *aux;

	if (self1 != NULL && self1->vec != NULL && self2 != NULL && self2->vec != NULL && self1->len == self2->len) {
		aux = VectorMejoradoWithLength(self1->len);
		for (i = 0; i < aux->len; i++) {
			aux->vec[i] = self1->vec[i] + self2->vec[i];
		}
		return aux;
	}
	else {
		return NULL;
	}
}

VectorMejorado_t* productoVectores(VectorMejorado_t *self1, VectorMejorado_t *other) {
	unsigned int i;
	VectorMejorado_t *aux;

	if (self1 != NULL && self1->vec != NULL && other != NULL && other->vec != NULL && self1->len == other->len) {
		aux = VectorMejoradoWithLength(self1->len);
		for (i = 0; i < aux->len; i++) {
			aux->vec[i] = self1->vec[i] + other->vec[i];
		}
		return aux;
	}
	else {
		return NULL;
	}
}

int setVec(VectorMejorado_t *self, unsigned int n, int valor) {

	if (self != NULL && self->vec != NULL && n >= 0 && n < self->len) {
		self->vec[n] = valor;
		return 0;
	}
	else {
		return -1;
	}
}

int setLen(VectorMejorado_t *self, unsigned int n) {

	if (self != NULL) {
		self->len = n;
		return 0;
	}
	else {
		return -1;
	}
}

int getVec(VectorMejorado_t *self, unsigned int i, int *resultado) {

	if (self != NULL && self->vec != NULL && i >= 0 && i < self->len) {
		*resultado = self->vec[i];
		return 0;
	}
	else {
		return -1;
	}
}

int getLen(VectorMejorado_t *self, int *resultado) {

	if (self != NULL) {
		*resultado = self->len;
		return 0;
	}
	else {
		return -1;
	}
}

int escribirVec(VectorMejorado_t *self, char *path) {
	int fd, wc, err;

	if (self == NULL) {
		return -2;
	}

	fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		printf("Error opening file to write\n");
		return -1;
	}

	wc = 0;
	do {
		//TODO: If you change  the struct, check the read and write functions
		err = write(fd, &self->len, sizeof(self->len));
		if (err == -1) {
			printf("Errors while writing len\n");
			return -1;
		}

		wc += err;
	} while (wc < sizeof(self->len));

	wc = 0;
	do {

		err = write(fd, self->vec, sizeof(int) * self->len);
		if (err == -1) {
			printf("Errors while writing vec\n");
			return -1;
		}

		wc += err;
	} while (wc < sizeof(int) * self->len);

	err = close(fd);
	if (err) {
		printf("Error closing file\n");
		return -1;
	}
	return 0;
}

int leerVec(VectorMejorado_t *self, char *path) {
	int fd, err, rc;
	//TODO comprobar que self no es nulo
	//TODO si es nulo, hacer un constructor
	if (self == NULL) {
		self = VectorMejorado();
	}
	fd = open(path, O_RDONLY);
	if (fd == -1) {
		printf("Error opening file to read\n");
		return -1;
	}

	rc = 0;
	do {
		err = read(fd, &self->len, sizeof(self->len));
		if (err == -1) {
			printf("Errors while reading len\n");
			return -1;
		}

		rc += err;
	} while (rc < sizeof(self->len));

	rc = 0;
	do {
		err = read(fd, self->vec, self->len * sizeof(int));
		if (err == -1) {
			printf("Errors while reading vec\n");
			return -1;
		}

		rc += err;
	} while (rc < self->len * sizeof(int));

	err = close(fd);
	if (err) {
		printf("Error closing file\n");
		return -1;
	}
	return 0;
}

int main () {
	VectorMejorado_t *self1, *self2;
	unsigned int len1 = 4, len2 = 4;
	int seed, prod, max, min;
	float media_v, mediana_v;
    char *path = "test.txt";

	self1 = VectorMejoradoWithLength(len1);
	self2 = VectorMejoradoWithLength(len2);

	printf("Dame la semilla: ");
	fflush (0);
	scanf("%d", &seed);

	asignarValores(self1, seed);
	asignarValores(self2, seed - 50);
	printf("El primer vector es: ");
	imprimirVector(self1);
	printf("El segundo vector es: ");
	imprimirVector(self2);
	printf("El primer vector ordenado es: ");
	ordenarVector(self1);
	imprimirVector(self1);
	productoEscalar(self1, self2, &prod);
	printf("El producto escalar es: %d\n", prod);

	if (compararVector(self1, self2)) {
		printf("Los vectores son iguales.\n");
	}
	else {
		printf("Los vectores son diferentes\n");
	}
	maximo(self1, &max);
	printf("El valor máximo del primer vector es: %d\n", max);
	minimo(self1, &min);
	printf("El valor mínimo del primer vector es: %d\n", min);
	printf("El vector invertido es: ");
	imprimirVector(invertido(self1));
	media(self1, &media_v);
	printf("La media del primer vector es: %f\n", media_v);
	fflush(0);
	mediana(self1, &mediana_v);
	printf("La mediana del primer vector es: %f\n", mediana_v);
	printf("La(s) moda(s) del primer vector es/son: ");
	fflush(0);
	imprimirVector(moda(self1));
	probarModa();
	printf("El vector suma es: ");
	imprimirVector(sumarVectores(self1, self2));
	printf("El vector producto es: ");
	imprimirVector(productoVectores(self1, self2));


	if (!escribirVec(self1, path)) {
		if (!leerVec(self2, path)) {
			printf("Completada la escritura y lectura con éxito\n");
			fflush(0);
			imprimirVector(self2);
		}
	}
	DestruirVector(self1);
	DestruirVector(self2);

	return 0;
}
