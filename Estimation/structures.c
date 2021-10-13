#include<stdio.h>
#include<math.h>

typedef struct Vec Vec;
typedef struct Matrix_3 Matrix_3;

void Vec_construct(Vec *temp, double x,double y,double z); // Construct a vector 
void cross(Vec* temp,Vec* vec1,Vec* vec2); // Takes cross product : vec1 * vec2 and stores it in temp
double dot(Vec* vec1,Vec* vec2); // Takes the dot product
void scale_vec(Vec *temp,double k); // Scales a vector by a scalar (modifies the input)
void add_vec(Vec *temp,Vec* vec1,Vec* vec2); //Adds 2 vectors and stores in temp
void matrix_construct(Matrix_3 *temp,unsigned char x); // Based on x, Matrix is constructed - can be a zero matrix or an identity matrix
void add_matrix(Matrix_3 *temp,Matrix_3 *m1,Matrix_3 *m2);
void scale_matrix(Matrix_3 *temp,Matrix_3 *M,double k); // scales a matrix by a scalar (modifies the input matrix)
double det(Matrix_3 *temp); // takes the determinant of the matrix
double trace(Matrix_3 *temp);
void T(Matrix_3 *temp,Matrix_3 *m1); // Takes the transpose of m and stores in temp
void adjoint(Matrix_3 *temp,Matrix_3* m); // adjoint of m is stored in temp
void outer_product(Matrix_3* temp,Vec* v1,Vec* v2); // v1 v2^T = temp (Outer product in this order)
void matmul(Vec* temp,Matrix_3* M,Vec *v); // temp = Mv (Matrix and vector multiplication in this order)

struct Vec{
	double x,y,z;
};
void Vec_construct(Vec *temp, double x,double y,double z)
{
	temp->x = x;
	temp->y = y;
	temp->z = z;
}
void cross(Vec* temp,Vec* vec1,Vec* vec2){
	temp->x = vec1->y*vec2->z - vec1->z*vec2->y;
	temp->y = vec1->z*vec2->x - vec1->x*vec2->z;
	temp->z = vec1->x*vec2->y - vec1->y*vec2->x;
}
double dot(Vec* vec1,Vec* vec2){
	return (vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z);
}
void scale_vec(Vec *temp,double k){  // This modifies the input matrix
	temp->x *= k;temp->y *= k;temp->z *= k;
}
void add_vec(Vec *temp,Vec* vec1,Vec* vec2){
	temp->x = vec1->x + vec2->x;
	temp->y = vec1->y + vec2->y;
	temp->z = vec1->z + vec2->z;
}
struct Matrix_3{
	double elements[3][3];
	// Vec operator* (Vec v);
};

void matrix_construct(Matrix_3 *temp,unsigned char x)
{
	if (x == 0){ // Null Matrix
		for (unsigned char i = 0; i < 3; i++) {
			for (unsigned char j = 0; j < 3; j++) {
				(temp->elements)[i][j] = 0;
			}
		}
	}
	if (x == 1){  // Identity Matrix
		for (unsigned char i = 0; i < 3; i++) {
			for (unsigned char j = 0; j < 3; j++) {
				if (i == j) (temp->elements)[i][j] = 1;
				else (temp->elements)[i][j] = 0;
			}
		}
	}
}
void add_matrix(Matrix_3 *temp,Matrix_3 *m1,Matrix_3 *m2){
	for (unsigned char i = 0; i < 3; i++) {
		for (unsigned char j = 0; j < 3; j++) {
			(temp->elements)[i][j] = (m1->elements)[i][j] + (m2->elements)[i][j];
		}
	}
}

void scale_matrix(Matrix_3 *temp,Matrix_3 *M,double k){
	for (unsigned char i = 0; i < 3; i++) {
		for (unsigned char j = 0; j < 3; j++) {
			temp->elements[i][j] = (M->elements[i][j])*k;
		}
	}
}
double det(Matrix_3 *temp){
	double x;
	x = temp->elements[0][0] * (temp->elements[1][1]*temp->elements[2][2] - temp->elements[1][2]*temp->elements[2][1])
	- temp->elements[0][1] * (temp->elements[1][0]*temp->elements[2][2] - temp->elements[1][2]*temp->elements[2][0])
	+ temp->elements[0][2] * (temp->elements[1][0]*temp->elements[2][1] - temp->elements[1][1]*temp->elements[2][0]);
	return x;
}
double trace(Matrix_3 *temp){
	return (temp->elements[0][0] + temp->elements[1][1] + temp->elements[2][2]);
}
void T(Matrix_3 *temp,Matrix_3 *m1){                                                                  // Transpose Operation
	for (unsigned char i = 0; i < 3; i++) {
		for (unsigned char j = 0; j < 3; j++) {
			temp->elements[i][j] = m1->elements[j][i];
		}
	}        // #REVISIT pass value by reference
}
void adjoint(Matrix_3 *temp,Matrix_3* m){
	temp->elements[0][0] = m->elements[1][1]*m->elements[2][2] - m->elements[1][2]*m->elements[2][1];
	temp->elements[1][0] = m->elements[1][2]*m->elements[2][0] - m->elements[1][0]*m->elements[2][2];
	temp->elements[2][0] = m->elements[1][0]*m->elements[2][1] - m->elements[2][0]*m->elements[1][1];
	temp->elements[0][1] = m->elements[2][1]*m->elements[0][2] - m->elements[0][1]*m->elements[2][2];
	temp->elements[1][1] = m->elements[0][0]*m->elements[2][2] - m->elements[2][0]*m->elements[0][2];
	temp->elements[2][1] = m->elements[2][0]*m->elements[0][1] - m->elements[0][0]*m->elements[2][1];
	temp->elements[0][2] = m->elements[0][1]*m->elements[1][2] - m->elements[1][1]*m->elements[0][2];
	temp->elements[1][2] = m->elements[1][0]*m->elements[0][2] - m->elements[0][0]*m->elements[1][2];
	temp->elements[2][2] = m->elements[0][0]*m->elements[1][1] - m->elements[1][0]*m->elements[0][1];
}
void outer_product(Matrix_3* temp,Vec* v1,Vec* v2){
	temp->elements[0][0] = v1->x*v2->x;
	temp->elements[0][1] = v1->x*v2->y;
	temp->elements[0][2] = v1->x*v2->z;
	temp->elements[1][0] = v1->y*v2->x;
	temp->elements[1][1] = v1->y*v2->y;
	temp->elements[1][2] = v1->y*v2->z;
	temp->elements[2][0] = v1->z*v2->x;
	temp->elements[2][1] = v1->z*v2->y;
	temp->elements[2][2] = v1->z*v2->z;
}
void matmul(Vec* temp,Matrix_3* M,Vec *v){
	temp->x = M->elements[0][0]*v->x + M->elements[0][1]*v->y + M->elements[0][2]*v->z;
	temp->y = M->elements[1][0]*v->x + M->elements[1][1]*v->y + M->elements[1][2]*v->z;
	temp->z = M->elements[2][0]*v->x + M->elements[2][1]*v->y + M->elements[2][2]*v->z;
}
