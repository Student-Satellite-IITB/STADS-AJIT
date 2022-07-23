#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//RGA constants
#define THRESHOLD 3
#define STAR_MIN_PIXEL 3
#define STAR_MAX_PIXEL 150
#define MAX_STARS 100
#define SKIP_PIXELS 2
#define LENGTH 808
#define BREADTH 608
#define PIXEL_WIDTH 0.0000048
#define NUM_MAX_STARS 13

//SM constants
#define FOCAL_LENGTH 0.036
#define EPSILON 2.22e-15
#define DELTA 1e-4
#define ANG_DIST_TOLERANCE 1.2
#define N_GC 8876
#define N_KVEC_PAIRS 224792
#define Y_MAX 0.9999999999926209
#define Y_MIN 0.9900261208247870
#define TOL 0.5
#define P1 35
#define P2 80
