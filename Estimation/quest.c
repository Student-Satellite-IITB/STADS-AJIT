#include<math.h>
#include "structures.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void quest(double **data) // Based upon the input data, this function prints the components of the estimated quaternion
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
	for(int i = 0;i < 10;i++){ // i is the column number
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
			for (unsigned char i = 0; i < N; i++){
				r[i].y = -1*r[i].y;
				r[i].z = -1*r[i].z;
			}
			}
		if(counter == 2){ // Perform rotation abt y --- {-x,y,-z}
		for (unsigned char i = 0; i < N; i++){
			r[i].x = -1*r[i].x;
			r[i].z = -1*r[i].z;
		}
		}
		if(counter == 3){ // Perform rotation abt z --- {-x,-y,z}
		for (unsigned char i = 0; i < N; i++){
			r[i].y = -1*r[i].y;
			r[i].x = -1*r[i].x;
		}
		}

		for (unsigned char i = 0; i < N; i++){
			Matrix_3 temp;
			outer_product(&temp,&(b[i]),&(r[i]));
			scale_matrix(&temp,&temp,a[i]);
			add_matrix(&B,&B,&temp);
		}
		for (unsigned char i = 0; i < N; i++)
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
		for (unsigned char i = 0; i < 5; i++) {
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
alpha = sqrt((q_3.x)*(q_3.x) + (q_3.y)*(q_3.y) + (q_3.z)*(q_3.z) + (q_4)*(q_4));

printf("q_3.x = %lf \n", q_3.x/alpha);
printf("q_3.y = %lf \n", q_3.y/alpha);
printf("q_3.z = %lf \n", q_3.z/alpha);
printf("q_4 = %lf \n", q_4/alpha);

}

// --------------------------------------------------------- READING THE CSV FILE -------------------------------------------
void read_csv(int row, int col, char *filename, double **data){
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
}
// ------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
	/* code */
	if (argc < 3){
		printf("Please specify the CSV file as an input.\n");
		exit(0);
	}

	int row     = atoi(argv[1]);
	int col     = atoi(argv[2]);
	char fname[256];	strcpy(fname, argv[3]);

	double **data;
	data = (double **)malloc(row * sizeof(double *));
	for (int i = 0; i < row; ++i){
		data[i] = (double *)malloc(col * sizeof(double));
	}

	read_csv(row, col, fname, data);
	quest(data);
	return 0;
}
