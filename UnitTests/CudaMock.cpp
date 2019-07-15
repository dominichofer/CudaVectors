#include "pch.h"
#include "CudaMock.h"

cudaError_t cudaMallocHost(void** ptr, std::size_t size)
{
	*ptr = cuda_memory_model.MallocHost(size);
	return cudaSuccess;
}

cudaError_t cudaFreeHost(void* ptr)
{
	cuda_memory_model.FreeHost(ptr);
	return cudaSuccess;
}

cudaError_t cudaMalloc(void** devPtr, std::size_t size)
{
	*devPtr = cuda_memory_model.MallocDevice(size);
	return cudaSuccess;
}

cudaError_t cudaFree(void* devPtr)
{
	cuda_memory_model.FreeDevice(devPtr);
	return cudaSuccess;
}

cudaError_t cudaMemcpy(void* dst, const void* src, std::size_t count, cudaMemcpyKind kind)
{
	return cudaSuccess; // TODO: Implement!
}

cudaError_t cudaMemcpyAsync(void* dst, const void* src, std::size_t count, cudaMemcpyKind kind)
{
	return cudaSuccess; // TODO: Implement!
}

void CudaMock::SetUp()
{
	cuda_memory_model.clear();
}

void CudaMock::TearDown()
{
	ASSERT_TRUE(cuda_memory_model.empty());
}
