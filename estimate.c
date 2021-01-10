
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(double** a, int n, int m){

        for(int i = 0; i < n; i++ ) {
                for(int j = 0; j < m; j++) {
                        printf("%lf ", a[i][j]);
                }
                printf("\n");
        }
        printf("\n\n");
}

void transpose(int n, int m, double **x, double **xTranspose) {
	int index = 0; 

	for(int i = 0; i < m; i++) {
		//go through the first index of every column 
		for(int j = 0; j < n; j++ ) {
		//	printf(" %lf\n", x[j][i]);
			xTranspose[i][j] = x[j][i];
		} 	
		index++;
	}
	
	return; 
}
//m and u have to be the same due to matrix multiplication properties. 
void multiply(int n, int m, double **a, int u, int v, double **b, double **res) {
	if(m != u) {

		puts("Sizes do not match");
		return;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < v; j++) {
			for(int k = 0; k < m; k++ ) {
				res[i][j] = res[i][j] +  (a[i][k] * b[k][j]);
			} 
		}
	}
	return; 
}

void inverse(double **x, double** identity, int r) {
	//according to algorith
	//divide that way its guaranteed to be zero 
	for(int i = 0; i < r; i++) {
		//divide all of row i by pivot i
		double temp = x[i][i];
		for(int row = 0; row < r; row++) {
			//printf("div: %lf\n",  x[i][i]);
			x[i][row] = x[i][row] / temp;//x[i][i];	
			identity[i][row] = identity[i][row] / temp;//x[i][i];
		}
		for(int j = i+1; j < r; j++) {
			//subtract from second row, the first row * a multiple of that second row
			double temp = x[j][i];
			for(int row = 0; row < r; row++) {
				//printf("x: %lf\n", x[i][row] * x[j][i]);
				x[j][row] = x[j][row] -  (x[i][row] * temp);//x[j][i]);
				identity[j][row] -= identity[i][row] * temp;//x[j][i];
			}
		}

	}
	
	for(int i = r- 1; i >= 0; i--) {
		for(int j = i-1; j >= 0; j--) {
		 	double temp = x[j][i];
			for(int row = 0; row < r; row++) {
                                x[j][row] -= x[i][row] * temp;//x[j][i];
                                identity[j][row] = identity[j][row] - (identity[i][row] * temp);//x[j][i];
			}
		}
	}
	return; 
}

void multiplyVector(double **x, int r, int c, double *y, double *result ) {
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			result[i] += x[i][j] * y[j]; 
		}	
	}

	return; 
}


int main(int argc, char **argv)
{
	FILE* file = fopen(argv[1], "r");
	//check if file is NULL
	if(file == NULL) {
		puts("ERROR");
		return EXIT_FAILURE;
	}	


//first file 	
	//scan the name
	char *name = malloc(60*sizeof(char) );
	fscanf(file, "%s", name);
	
	//scan the attribute count
	char *in = malloc(12*sizeof(char)); 
	fscanf(file, "%s", in);
	int k = atoi(in);

	//scan the number of houses 
	fscanf(file, "%s", in);
	int m = atoi(in);
	free(in); 
	
	//create the 2d Array
	int r = m ;
	int c = k + 1; 
	double *y = malloc(r*sizeof(double));
	double **arr = malloc(r*sizeof(double*));
	for(int i = 0; i < r; i++) {
		arr[i] = malloc(c*sizeof(arr[i])); 
	}
	//populate the 2d array
	char *nums = malloc(11*sizeof(int));
	for(int i = 0; i < r; i++) {
		//populate both arrays at once 
		for(int j = 1; j < c;j++) {
			if(j == 0) {
				arr[i][j] = 1; 
			}
			if(fscanf(file, "%s", nums) != EOF) {
				sscanf(nums, "%lf", &arr[i][j]);
			}
		}
		if(fscanf(file, "%s", nums) != EOF) {
                        sscanf(nums, "%lf", &y[i]);
                        }
	}

	for(int i = 0 ; i < r; i++) {
		arr[i][0] = 1; 
	}



	free(nums); 
	//print the matrix	
//	for(int i = 0; i < r; i++) {
//                for(int j = 0; j < c;j++) {
//               		printf("%lf ", arr[i][j]);
//		}
//		printf("\n");
//        }
	//close the first file
	fclose(file);

	FILE* file2 = fopen(argv[2], "r");
        //check if file is NULL
        if(file2 == NULL) {
		puts("ERROR");
        	return EXIT_FAILURE;
        }
	
	//scan name
	char *name2 = malloc(60 *sizeof(char) );  
	fscanf(file2, "%s", name2); 

	//scan attributes
	char *in2 = malloc(12*sizeof(char));
        fscanf(file2, "%s", in2);
        int k2 = atoi(in2);
	
	//scan the houses
	fscanf(file2, "%s", in2);
        int m2 = atoi(in2);
        free(in2);

	//create the second 2d array
	int r2 = m2;
	int c2 = k2 + 1; 
        double **arr2 = malloc(r2*sizeof(double*));

        for(int i = 0; i < r2; i++) {
                arr2[i] = malloc(c2*sizeof(arr2[i]));
        }	
	
	//populate the 2d array
	char *nums2 = malloc(12*sizeof(int));
        for(int i = 0; i < r2; i++) {
                for(int j = 0; j < c2;j++) {
			if(j == 0) {
				arr2[i][j] = 1; 
				continue;
			}
                        if(fscanf(file2, "%s", nums2) != EOF) {
                                sscanf(nums2, "%lf", &arr2[i][j]);
                        }
                }

        }
	free(nums2); 
	//print secondary matrix
///	for(int i = 0; i < r2; i++) {
///              for(int j = 0; j < c2;j++) {
///                        printf("%lf ", arr2[i][j]);
///                }
///                printf("\n");
///
///     }

//Transpose X, IE train file
	//declare memory for transpose
	double **xTranspose; 
		xTranspose = malloc(c*sizeof(double*));
		for(int i = 0; i < c; i++) {
			xTranspose[i] = malloc(r*sizeof(xTranspose[i]));
		}
		//call transpose
		transpose(r,c, arr, xTranspose);
	//print Transpose
///	puts("Transpose");
///	for(int i = 0; i < c; i++) {
///          	for(int j = 0; j < r; j++) {
///               		printf("%lf ", xTranspose[i][j]);
///                }
///               	printf("\n");
///    	}

//multiplication
	//multiply X^t and X
	//declare memory, size (m*n) * (n*m) = m*m
	double **multiple = malloc(c*sizeof(double*));
		for(int i = 0; i < c; i++) {
			multiple[i] = malloc(c*sizeof(multiple[i]));
		}
		for(int i = 0; i < c; i++) {
			for(int j = 0; j < c; j++) {
				multiple[i][j] = 0; 
			}
		}
		

		multiply(c,r,xTranspose,r,c,arr,multiple);
		//print multiple
//inverse
	//take the inverse of multiple, a square matrix. 
	//create the identity matrix. 
	double **identity;
		identity = malloc(c*sizeof(double*)); 	
		for(int i = 0; i < c; i++) {
			identity[i] = malloc(c*sizeof(identity[i]));
		}
		//set diagonals equal to one
		int counter = 0; 
		for(int i = 0; i < c; i++) {
			for(int j = 0; j < c; j++) {
				if(j == counter) {
					identity[i][j] = 1;
				}
				else{
					identity[i][j] = 0; 
				}
			}
			counter++;
		}
		//call inverse
		inverse(multiple, identity, c);

///	printf("IDENITY: \n");
	//print identity
///	print(identity,c,c);
	//print the inverse, which is in identity
///	puts("multiple");
///	print(multiple,c,c);
	//free all of multiple	
	for(int i = 0; i < c; i++) {
		free(multiple[i]);
	}
	free(multiple);	

//multiply inverse with transpose`
	//declare memory for product
	double **multiple2 = malloc(c*sizeof(double*));
	for(int i = 0; i < c; i++) {
		multiple2[i] = malloc(r*sizeof(multiple[i]));
	}
	
	for(int i = 0; i < c; i++) {
		for(int j = 0; j < r; j++) {
			multiple2[i][j] = 0;
		}
	}

	//inverse = identity, transpose = xTranspose
/// 	printf("C: %d R: %d\n", c, r);	
	multiply(c, c, identity, c, r , xTranspose, multiple2);
///	puts("Inverse * TransposeX");
///	print(multiple2, c, r);
	//free the unused arrays
	for(int i = 0; i < c; i++) {
		free(xTranspose[i]);
	}
	free(xTranspose);
	 for(int i = 0; i < c; i++) {
                free(identity[i]);
        }
	free(identity);

	double *result = malloc(c*sizeof(double));

	for(int i = 0; i < c; i++) {
		result[i] = 0;
	}
	
	multiplyVector(multiple2, c,r, y, result);
///	printf("Y for reference:\n");
///	for(int i = 0; i < r; i++) {
///		printf("%lf ", y[i]);
///	}
///	printf("\n");
	
///	printf("w\n");
///      	for(int i = 0; i < c; i++) {
///              printf("%lf\n", result[i]);
///      	}
///        printf("\n");
	
///	puts("X': ");
///	print(arr2, r2,c2); 
//Find Y'
	//multiply vector W with x'(arr2). 
	//allocate memory
	double *price = malloc(r2*sizeof(double));
	multiplyVector(arr2, r2, c2, result, price); 
	
        for(int i = 0; i < r2; i++) {
      		printf("%.0f\n", price[i] );
	}
	
	//free variables
	 for(int i = 0; i < r; i++) {
                free(arr[i]);
        }
	free(arr);
	 for(int i = 0; i < r2; i++) {
                free(arr2[i]);
        }
	free(arr2);
	 for(int i = 0; i < c; i++) {
                free(multiple2[i]);
        }
	free(multiple2);
	free(result);
	free(price);
	free(name);
	free(name2);
	free(y);
	return 0;
}
