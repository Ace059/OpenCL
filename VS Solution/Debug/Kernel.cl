// TODO: Add OpenCL kernel code here.
__kernel void prvi(__global float* A, __global float* B, __global float* C)
{
	float sum=0;
	int st=0;
	
	for (int i=0; i<3; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[0]  = sum;
	
	sum=0;
	st=1;

	for (int i=0; i<3; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[1]  = sum;

	sum=0;
	st=2;

	for (int i=0; i<3; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[2]  = sum;

	
}

__kernel void drugi(__global float* A, __global float* B, __global float* C)
{
    float sum=0;
	int st=0;
	
	for (int i=3; i<6; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[3]  = sum;
	
	sum=0;
	st=1;

	for (int i=3; i<6; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[4]  = sum;

	sum=0;
	st=2;

	for (int i=3; i<6; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[5]  = sum;

}

__kernel void treci(__global float* A, __global float* B, __global float* C)
{
    float sum=0;
	int st=0;
	
	for (int i=6; i<9; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[6]  = sum;
	
	sum=0;
	st=1;

	for (int i=6; i<9; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[7]  = sum;

	sum=0;
	st=2;

	for (int i=6; i<9; i++){ 
		sum+= A[i]*B[st];
		st+=3;
	}
	C[8]  = sum;

}


