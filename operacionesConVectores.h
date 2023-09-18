/*
 * operacionesConVectores.h
 *
 *  Created on: 25 abr 2023
 *      Author: nakal
 */

#ifndef OPERACIONESCONVECTORES_H_
#define OPERACIONESCONVECTORES_H_

typedef struct {
	int *vec;
	int len;
} VectorMejorado_t;

VectorMejorado_t* VectorMejorado();
VectorMejorado_t* VectorMejoradoWithLength(unsigned int n);
VectorMejorado_t* VectorMejoradoCC(VectorMejorado_t *self);
VectorMejorado_t* RedimensionarVector(VectorMejorado_t *self, unsigned int n);
int imprimirVector(VectorMejorado_t *self);
void asignarValores(VectorMejorado_t *self, int seed);
void DestruirVector(VectorMejorado_t *self);
int asignarVector(const VectorMejorado_t *self1, VectorMejorado_t *self2);
int compararVector(VectorMejorado_t *self1, VectorMejorado_t *self2);
int hayOtro(VectorMejorado_t *self, int n);
void ordenarVector(VectorMejorado_t *self);
int productoEscalar(VectorMejorado_t *self1, VectorMejorado_t *self2, int *resultado);
int maximo(VectorMejorado_t *self, int *resultado);
int minimo(VectorMejorado_t *self, int *resultado);
VectorMejorado_t* invertido(VectorMejorado_t *self);
int media(VectorMejorado_t *self, float *resultado);
int mediana(VectorMejorado_t *self, float *resultado);
VectorMejorado_t* moda(VectorMejorado_t *self);
void probarModa();
VectorMejorado_t* sumarVectores(VectorMejorado_t *self1, VectorMejorado_t *self2);
VectorMejorado_t* productoVectores(VectorMejorado_t *self1, VectorMejorado_t *other);
int setVec(VectorMejorado_t *self, unsigned int n, int valor);
int setLen(VectorMejorado_t *self, unsigned int n);
int getVec(VectorMejorado_t *self, unsigned int i, int *resultado);
int getLen(VectorMejorado_t *self, int *resultado);
int escribirVec(VectorMejorado_t *self, char *path);
int leerVec(VectorMejorado_t *self, char *path);


#endif /* OPERACIONESCONVECTORES_H_ */
