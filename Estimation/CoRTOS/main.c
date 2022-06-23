#include "cortos.h"

//combined structures.c into quest.c -------- 
typedef struct Vec Vec;
typedef struct Matrix_3 Matrix_3;
double absoluteValue(double x);
double square_root(double x);
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

double absoluteValue(double x){
    if(x<0){
    x =-x;}
    return x;

}

double square_root(double x){
    double guess =1;
    while (absoluteValue((guess*guess)/x -1.0) >= 0.0001){
        guess = ((x/guess) + guess)/2;
        
    }
  return guess;
} //square_root fuction ---------
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
	unsigned char i = 0;
	unsigned char j = 0;
		for (i=0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				(temp->elements)[i][j] = 0;
			}
		}
	}
	if (x == 1){  // Identity Matrix
	unsigned char i = 0;
	unsigned char j = 0;
		for ( i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				if (i == j) (temp->elements)[i][j] = 1;
				else (temp->elements)[i][j] = 0;
			}
		}
	}
}
void add_matrix(Matrix_3 *temp,Matrix_3 *m1,Matrix_3 *m2){
	unsigned char i = 0;
	unsigned char j = 0;
	for ( i = 0; i < 3; i++) {
		for ( j = 0; j < 3; j++) {
			(temp->elements)[i][j] = (m1->elements)[i][j] + (m2->elements)[i][j];
		}
	}
}

void scale_matrix(Matrix_3 *temp,Matrix_3 *M,double k){
	unsigned char i = 0;
	unsigned char j = 0;
	for ( i = 0; i < 3; i++) {
		for ( j = 0; j < 3; j++) {
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
void T(Matrix_3 *temp,Matrix_3 *m1){ 
	 unsigned char i = 0;
	 unsigned char j = 0;                                                           // Transpose Operation
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
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



double data[3][10] = {{0.4242640687 ,0.2672612419 , -0.32929278 ,-0.4364357805 , -0.1632993162 , 0.4242640687 ,0.2672612419 ,-0.32929278 , -0.4364357805 ,-0.1632993162}, 
{0.5656854249 ,-0.5345224838 ,0.5488212999 ,-0.2182178902 ,-0.4082482905 ,0.9 ,0.1889822365 ,0.9313806308 ,0.4629100499 ,0.3464101615},
{0.7071067812 ,0.8017837257 ,0.7683498199 ,0.8728715609 ,0.898146239 ,0.1 ,0.9449111825 ,0.1552301052 ,0.7715167498 ,0.9237604307}}; //input array ----------




void quest(double data[3][10]) // Based upon the input data, this function prints the components of the estimated quaternion
{
	unsigned char N = 5;
	Vec b[N];Vec r[N];

	double epsilon = 0.15; // epsilon is the threshold error which when exceeded would require rotation

	double a[N]; // weight vector
	a[0] = 1.0/N;a[1] = 1.0/N;a[2] = 1.0/N;a[3] = 1.0/N;a[4] = 1.0/N;
	double guess = 1; // initial guess
	Matrix_3 B,S;
	matrix_construct(&B,0); // Constructs a 3*3 Matrix with all zeroes 
	matrix_construct(&S,0);
	Vec z;
	Vec_construct(&z,0,0,0); // Constructs a 3*1 vector with all zeroes
	unsigned char counter = 0; // counter used in the do while loop below
	double K;
	double norm_2_z;
	double det_S;
	double trace_B;
	double zTSz;
	double zTSSz;
	Matrix_3 adj_S;
	Matrix_3 check;
	// We have the csv file stored in **data
	int i =0;
	for( i = 0;i < 10;i++){ // i is the column number
		if(i < 5){
			Vec_construct(&r[i],data[0][i],data[1][i],data[2][i]); // Construct r vectors according to the data read
		}
		else{
			Vec_construct(&b[i-5],data[0][i],data[1][i],data[2][i]); // Construct b vectors according to the data read
		}
	}
	
	
	// Perform Quest
	double f(double x){ // This is the function whose roots are found using Newton Rapshon 
		double first = (x*x - trace_B*trace_B + K)*(x*x - trace_B*trace_B - norm_2_z);
		double second = (x - trace_B)*(zTSz + det_S);
		return (first - second - zTSSz);
	}
	double f_bar(double x){//This is the derivative of the function whose roots are found using Newton Rapshon 
		double temp = 2*x*(2*x*x - 2*trace_B*trace_B + K - norm_2_z);
		return (temp - zTSz - det_S);
	}

	do {
		if(counter == 1){ // Perform rotation abt x --- {x,-y,-z}
			//unsigned char i = 0; 
			for (i = 0; i < N; i++){
				r[i].y = -1*r[i].y;
				r[i].z = -1*r[i].z;
			}
			}
		if(counter == 2){ // Perform rotation abt y --- {-x,y,-z}
		//unsigned char i = 0; 
		for ( i = 0; i < N; i++){
			r[i].x = -1*r[i].x;
			r[i].z = -1*r[i].z;
		}
		}
		if(counter == 3){ // Perform rotation abt z --- {-x,-y,z}
		//unsigned char i = 0; 
		for ( i = 0; i < N; i++){
			r[i].y = -1*r[i].y;
			r[i].x = -1*r[i].x;
		}
		}
        //unsigned char i = 0;
		for (i = 0; i < N; i++){
			Matrix_3 temp;
			outer_product(&temp,&(b[i]),&(r[i]));
			scale_matrix(&temp,&temp,a[i]);
			add_matrix(&B,&B,&temp);
		}
		for (i = 0; i < N; i++)
		{
			Vec temp;
			cross(&temp,&(b[i]),&(r[i]));
			scale_vec(&temp,a[i]);
			add_vec(&z,&z,&temp);
		}

		trace_B = trace(&B);
		T(&S,&B); // Takes the Transponse of a matrix
		add_matrix(&S,&S,&B); // construct S
		adjoint(&adj_S,&S); // Takes the adjoint of a matrix
		K = trace(&adj_S);
		norm_2_z = z.x*z.x + z.y*z.y + z.z*z.z;
		det_S = det(&S); // Takes the determinant of a matrix
		Vec temp1,temp2; // temporary variables
		matmul(&temp1,&S,&z);
		zTSz = dot(&z,&temp1);
		matmul(&temp2,&S,&temp1);
		zTSSz = dot(&z,&temp2);

		double rho = guess; // sum of weights
		for ( i = 0; i < 5; i++) {
			double x1 = f(rho);
			double x2 = f_bar(rho);
			rho =rho - x1/x2;
		}
		rho += trace_B;
		Matrix_3 I;
		matrix_construct(&I,1);
		scale_matrix(&I,&I,rho);
		scale_matrix(&check,&S,-1);
		add_matrix(&check,&check,&I);

		counter++;
		} while((det(&check)) < epsilon);

Vec q_3;
double q_4 = det(&check);
Matrix_3 adj_check;
adjoint(&adj_check,&check);
matmul(&q_3,&adj_check,&z); //  (I3*rho - (B + B.T())).adjoint() * z

if(counter == 2){
	Vec e;
	Vec_construct(&e,1,0,0);
	double new_4 = -dot(&e,&q_3);
	cross(&q_3,&e,&q_3);
	scale_vec(&e,q_4);
	add_vec(&q_3,&q_3,&e);
	q_4 = new_4;
}
else if(counter == 3){
	Vec e;
	Vec_construct(&e,0,1,0);
	double new_4 = -dot(&e,&q_3);
	cross(&q_3,&e,&q_3);
	scale_vec(&e,q_4);
	add_vec(&q_3,&q_3,&e);
	q_4 = new_4;
}
else if(counter == 4){
	Vec e;
	Vec_construct(&e,0,0,1);
	double new_4 = -dot(&e,&q_3);
	cross(&q_3,&e,&q_3);
	scale_vec(&e,q_4);
	add_vec(&q_3,&q_3,&e);
	q_4 = new_4;
}
double alpha; 
double a1 =  (q_3.x)*(q_3.x);
double a2 = (q_3.y)*(q_3.y);
double a3 = (q_3.z)*(q_3.z);
double a4 = (q_4)*(q_4);
alpha = square_root(a1+a2+a3+a4);

double x1 =(q_3.x);
double x2 = (q_3.y);
double x3 = (q_3.z);
double x4 = (q_4);
//alpha = sqrt(q_3.x*q_3.x + q_3.y*q_3.y+ q_3.z*q_3.z+ q_4*q_4);
CORTOS_INFO("q_3.x = %lf",x1/alpha);
CORTOS_INFO("q_3.y = %lf", x2/alpha);
CORTOS_INFO("q_3.z = %lf",x3/alpha);
CORTOS_INFO("q_4 = %lf",x4/alpha);
//CORTOS_INFO("alpha = %lf ",alpha);
return ;
}

// --------------------------------------------------------- READING THE CSV FILE -------------------------------------------
/*void read_csv(int row, int col, char *filename, double **data){
	FILE *file;
	file = fopen(filename, "r");

	int i = 0;
       
    char line[4098];
	while (fgets(line, 4098, file) && (i < row))
    {
    	char* tmp = strdup(line); // This duplicates the string

	    int j = 0;
	    const char* tok;
	    for (tok = strtok(line, ","); tok && *tok; j++, tok = strtok(NULL, ","))
	    {
	        data[i][j] = atof(tok); // This stores the data in data 
	    }
        free(tmp);
        i++;
    }
}*/ //read_csv no longer needed ---------
// ------------------------------------------------------------------------------
void main()
{
	/* code */
	/*if (argc < 3){
		printf("Please specify the CSV file as an input.\n");
		exit(0);
	}*/

	int row = 3  ;//  = atoi(argv[1]); dimensions hardcoded -----
	int col = 10  ;//  = atoi(argv[2]);
	//char fname[256];	strcpy(fname, argv[3]);

	/*double **data;
	data = (double **)malloc(row * sizeof(double *));
	int i =0;
        for ( i = 0; i < row; ++i){
		data[i] = (double *)malloc(col * sizeof(double));
	} memory allocation not needed --------

	//read_csv(row, col, fname, data);
        int i =0;
        int j =0;
	for( i=0; i< 3; i++){
		for(j=0; j< 10; j++){
			data[i][j] = inp[i][j];
		}
	}*/
	quest(data);
	cortos_exit(0);
}
