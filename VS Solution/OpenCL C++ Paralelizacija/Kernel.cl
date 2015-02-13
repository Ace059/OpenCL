// TODO: Add OpenCL kernel code here.
__kernel void prvi(__global float* A, __global float* B, __global float* C)
{
	float sum=0;
	int st=0;
	
	for (int i=0; i<4; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[0]  = sum;
	
	sum=0;
	st=1;

	for (int i=0; i<4; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[1]  = sum;

	sum=0;
	st=2;

	for (int i=0; i<4; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[2]  = sum;

	sum=0;
	st=3;

	for (int i=0; i<4; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[3]  = sum;
}

__kernel void drugi(__global float* A, __global float* B, __global float* C)
{
    float sum=0;
	int st=0;
	
	for (int i=4; i<8; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[4]  = sum;
	
	sum=0;
	st=1;

	for (int i=4; i<8; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[5]  = sum;

	sum=0;
	st=2;

	for (int i=4; i<8; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[6]  = sum;

	sum=0;
	st=3;

	for (int i=4; i<8; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[7]  = sum;
}

__kernel void treci(__global float* A, __global float* B, __global float* C)
{
    float sum=0;
	int st=0;
	
	for (int i=8; i<12; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[8]  = sum;
	
	sum=0;
	st=1;

	for (int i=8; i<12; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[9]  = sum;

	sum=0;
	st=2;

	for (int i=8; i<12; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[10]  = sum;

	sum=0;
	st=3;

	for (int i=8; i<12; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[11]  = sum;
}

__kernel void cetvrti(__global float* A, __global float* B, __global float* C)
{   
	float sum=0;
	int st=0;
	
	for (int i=12; i<16; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[12]  = sum;
	
	sum=0;
	st=1;

	for (int i=12; i<16; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[13]  = sum;

	sum=0;
	st=2;

	for (int i=12; i<16; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[14]  = sum;

	sum=0;
	st=3;

	for (int i=12; i<16; i++){ 
		sum+= A[i]*B[st];
		st+=4;
	}
	C[15]  = sum;
}
