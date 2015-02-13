#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <CL/cl.h>

using namespace std;

#define MAX_SOURCE_SIZE (0x100000)


void platforminfo(cl_platform_id platform_id){
	
	size_t platform_name_length = 0;
	clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 0, 0, &platform_name_length);

	char* platform_name = new char[platform_name_length];
	clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, platform_name_length, platform_name, 0);

	cout << "Naziv platforme: " << platform_name << endl;
	
	struct{
		cl_device_type type;
		const char* name;
		cl_uint count;} devices[] = {
			{ CL_DEVICE_TYPE_CPU, "CL_DEVICE_TYPE_CPU", 0 },
			{ CL_DEVICE_TYPE_GPU, "CL_DEVICE_TYPE_GPU", 0 },
			{ CL_DEVICE_TYPE_ACCELERATOR, "CL_DEVICE_TYPE_ACCELERATOR", 0 }};

		const int NUM_OF_DEVICE_TYPES = sizeof(devices) / sizeof(devices[0]);
		cout << "Broj procesnih jedinica prema tipu:\n";
		
		for (int i = 0; i < NUM_OF_DEVICE_TYPES; ++i){
			clGetDeviceIDs(platform_id, devices[i].type, 0, 0, &devices[i].count);
			cout << "  "<< i+1<< ". " << devices[i].name << ": " << devices[i].count << endl;
		}

		for (int type_index = 0; type_index < NUM_OF_DEVICE_TYPES; ++type_index)
		{
			cl_uint cur_num_of_devices = devices[type_index].count;
			if (cur_num_of_devices == 0)
				continue;

			cl_device_id* devices_of_type = new cl_device_id[cur_num_of_devices];
			clGetDeviceIDs(platform_id, devices[type_index].type, cur_num_of_devices, devices_of_type, 0);

			for (cl_uint device_index = 0; device_index < cur_num_of_devices; ++device_index){
				cout << "\n" << devices[type_index].name << "[" << device_index << "]\n";
				cl_device_id device = devices_of_type[device_index];

				size_t property_length = 0;
				clGetDeviceInfo(device, CL_DEVICE_NAME, 0, 0, &property_length);
				char* property_value = new char[property_length];
				clGetDeviceInfo(device, CL_DEVICE_NAME, property_length, property_value, 0);
				cout << "    " << "CL_DEVICE_NAME: " << property_value << endl;
				delete[] property_value;

				property_length = 0;
				clGetDeviceInfo(device, CL_DRIVER_VERSION, 0, 0, &property_length);
				property_value = new char[property_length];
				clGetDeviceInfo(device, CL_DRIVER_VERSION, property_length, property_value, 0);
				cout << "    " << "CL_DRIVER_VERSION: " << property_value << endl;
				delete[] property_value;

				cl_uint value;
				property_length = 0;
				clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(value), &value, &property_length);                                                   \
					cout << "    " << "CL_DEVICE_MAX_COMPUTE_UNITS" << ": " << value << endl;

				value = 0;
				property_length = 0;
				clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(value), &value, &property_length);                                                   \
					cout << "    " << "CL_DEVICE_MAX_CLOCK_FREQUENCY" << ": " << value << endl;

				value = 0;
				property_length = 0;
				clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(value), &value, &property_length);                                                   \
					cout << "    " << "CL_DEVICE_ADDRESS_BITS" << ": " << value << endl;

				cl_ulong lvalue = 0;
				property_length = 0;
				clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(lvalue), &lvalue, &property_length);                                                   \
					cout << "    " << "CL_DEVICE_MAX_MEM_ALLOC_SIZE" << ": " << lvalue << endl;

				lvalue = 0;
				property_length = 0;
				clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(lvalue), &lvalue, &property_length);                                                   \
					cout << "    " << "CL_DEVICE_GLOBAL_MEM_SIZE" << ": " << lvalue << endl;

				lvalue = 0;
				property_length = 0;
				clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(lvalue), &lvalue, &property_length);                                                   \
					cout << "    " << "CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE" << ": " << lvalue << endl;
			}
		}		                    
};


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
	
	cl_kernel kernel[3] = { NULL, NULL, NULL };

	int i, j;
	float* A;
	float* B;
	float* C;

	A = (float*)malloc(3 * 3 * sizeof(float));
	B = (float*)malloc(3 * 3 * sizeof(float));
	C = (float*)malloc(3 * 3 * sizeof(float));

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

	cout << "MNOZENJE 3x3 MATRICA:\n\n";
	
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			cout << "A [" << i + 1 << "][" << j + 1 << "] = ";
			cin >> A[i * 3 + j];
		}
	}

	cout << endl;

	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			cout << "B [" << i + 1 << "][" << j + 1 << "] = ";
			cin >> B[i * 3 + j];
		}
	}

	cout << endl;
	
	feedback = clGetPlatformIDs(1, &platform_id, &returnPlatformNumber);			
	feedback = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &returnDeviceNumber);	

	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &feedback);

	
	command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &feedback);

	
	bufferA = clCreateBuffer(context, CL_MEM_READ_WRITE, 3 * 3 * sizeof(float), NULL, &feedback);
	bufferB = clCreateBuffer(context, CL_MEM_READ_WRITE, 3 * 3 * sizeof(float), NULL, &feedback);
	bufferC = clCreateBuffer(context, CL_MEM_READ_WRITE, 3 * 3 * sizeof(float), NULL, &feedback);

	
	feedback = clEnqueueWriteBuffer(command_queue, bufferA, CL_TRUE, 0, 3 * 3 * sizeof(float), A, 0, NULL, NULL);
	feedback = clEnqueueWriteBuffer(command_queue, bufferB, CL_TRUE, 0, 3 * 3 * sizeof(float), B, 0, NULL, NULL);

	
	program = clCreateProgramWithSource(context, 1, (const char **)&sadrzajDatoteke, (const size_t *)&velicinaDatoteke, &feedback);
	feedback = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	
	kernel[0] = clCreateKernel(program, "prvi", &feedback);
	kernel[1] = clCreateKernel(program, "drugi", &feedback);
	kernel[2] = clCreateKernel(program, "treci", &feedback);

	
	for (i = 0; i<3; i++) {
		feedback = clSetKernelArg(kernel[i], 0, sizeof(cl_mem), (void *)&bufferA);
		feedback = clSetKernelArg(kernel[i], 1, sizeof(cl_mem), (void *)&bufferB);
		feedback = clSetKernelArg(kernel[i], 2, sizeof(cl_mem), (void *)&bufferC);
	}

	
	for (i = 0; i<3; i++) {
		feedback = clEnqueueTask(command_queue, kernel[i], 0, NULL, NULL);
	}

	
	feedback = clEnqueueReadBuffer(command_queue, bufferC, CL_TRUE, 0, 3 * 3 * sizeof(float), C, 0, NULL, NULL);

	cout << endl << "A * B = "<< endl << endl;

	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			printf("%7.2f ", C[i * 3 + j]);
		}
		printf("\n");
	}

	cout << "\n\n*******PLATFORM***DETAILS*******" << endl;
	platforminfo(platform_id);


	feedback = clFlush(command_queue);
	feedback = clFinish(command_queue);
	feedback = clReleaseKernel(kernel[0]);
	feedback = clReleaseKernel(kernel[1]);
	feedback = clReleaseKernel(kernel[2]);
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

	cout << endl;
	system("pause");
	return 0;
}
