#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <CL/cl.h>

using namespace std;

#define MAX_SOURCE_SIZE (0x100000)

int main()
{
	cl_platform_id platform_id = NULL; 
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_program program = NULL;

	cl_int feedback;
	cl_uint returnDeviceNumber;
	cl_uint returnPlatformNumber;

	cl_mem bufferA = NULL;
	cl_mem bufferB = NULL;
	cl_mem bufferC = NULL;
	
	cl_kernel kernel[4] = { NULL, NULL, NULL, NULL };

	int i, j;
	float* A;
	float* B;
	float* C;

	A = (float*)malloc(4 * 4 * sizeof(float));
	B = (float*)malloc(4 * 4 * sizeof(float));
	C = (float*)malloc(4 * 4 * sizeof(float));


	FILE *streamDatoteke;
	size_t velicinaDatoteke;
	char *sadrzajDatoteke;

	streamDatoteke = fopen("./Kernel.cl", "rb");
	if (!streamDatoteke) {
		cout << "Greska prilikom otvaranja datoteke kernel-a." << endl;
		system("pause");
		exit(1);}
	
	sadrzajDatoteke = (char *)malloc(MAX_SOURCE_SIZE);
	velicinaDatoteke = fread(sadrzajDatoteke, 1, MAX_SOURCE_SIZE, streamDatoteke);
	fclose(streamDatoteke);

	
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			cout << "A [" << i + 1 << "][" << j + 1 << "] = ";
			cin >> A[i * 4 + j];
			cout << endl;
		}
	}

	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			cout << "B [" << i + 1 << "][" << j + 1 << "] = ";
			cin >> B[i * 4 + j];
			cout << endl;
		}
	}
	
	feedback = clGetPlatformIDs(1, &platform_id, &returnPlatformNumber);			
	feedback = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &returnDeviceNumber);	

	
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &feedback);

	
	command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &feedback);

	
	bufferA = clCreateBuffer(context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &feedback);
	bufferB = clCreateBuffer(context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &feedback);
	bufferC = clCreateBuffer(context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &feedback);

	
	feedback = clEnqueueWriteBuffer(command_queue, bufferA, CL_TRUE, 0, 4 * 4 * sizeof(float), A, 0, NULL, NULL);
	feedback = clEnqueueWriteBuffer(command_queue, bufferB, CL_TRUE, 0, 4 * 4 * sizeof(float), B, 0, NULL, NULL);

	
	program = clCreateProgramWithSource(context, 1, (const char **)&sadrzajDatoteke, (const size_t *)&velicinaDatoteke, &feedback);
	feedback = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	
	kernel[0] = clCreateKernel(program, "prvi", &feedback);
	kernel[1] = clCreateKernel(program, "drugi", &feedback);
	kernel[2] = clCreateKernel(program, "treci", &feedback);
	kernel[3] = clCreateKernel(program, "cetvrti", &feedback);

	
	for (i = 0; i<4; i++) {
		feedback = clSetKernelArg(kernel[i], 0, sizeof(cl_mem), (void *)&bufferA);
		feedback = clSetKernelArg(kernel[i], 1, sizeof(cl_mem), (void *)&bufferB);
		feedback = clSetKernelArg(kernel[i], 2, sizeof(cl_mem), (void *)&bufferC);
	}

	
	for (i = 0; i<4; i++) {
		feedback = clEnqueueTask(command_queue, kernel[i], 0, NULL, NULL);
	}

	
	feedback = clEnqueueReadBuffer(command_queue, bufferC, CL_TRUE, 0, 4 * 4 * sizeof(float), C, 0, NULL, NULL);

	
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			printf("%7.2f ", C[i * 4 + j]);
		}
		printf("\n");
	}

	
	feedback = clFlush(command_queue);
	feedback = clFinish(command_queue);
	feedback = clReleaseKernel(kernel[0]);
	feedback = clReleaseKernel(kernel[1]);
	feedback = clReleaseKernel(kernel[2]);
	feedback = clReleaseKernel(kernel[3]);
	feedback = clReleaseProgram(program);
	feedback = clReleaseMemObject(bufferA);
	feedback = clReleaseMemObject(bufferB);
	feedback = clReleaseMemObject(bufferC);
	feedback = clReleaseCommandQueue(command_queue);
	feedback = clReleaseContext(context);

	free(sadrzajDatoteke);

	free(A);
	free(B);
	free(C);

	system("pause");
	return 0;
}
