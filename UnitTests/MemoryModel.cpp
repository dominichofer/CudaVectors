#include "pch.h"
#include "MemoryModel.h"

void MemoryModel::Memcpy(const std::vector<ByteArray>& source_vec, const void* source,
	std::vector<ByteArray>& destination_vec, void* destination,
	std::size_t count)
{
	auto src = std::find_if(source_vec.begin(), source_vec.end(),
		[source](const auto& arr) { return reinterpret_cast<const void*>(arr.data()) == source; });
	auto dst = std::find_if(destination_vec.begin(), destination_vec.end(),
		[destination](const auto& arr) { return reinterpret_cast<const void*>(arr.data()) == destination; });
	std::copy_n(src->begin(), count, dst->begin());
}

void MemoryModel::clear()
{
	host.clear();
	device.clear();
}

bool MemoryModel::empty() const
{
	return host.empty() && device.empty();
}

void* MemoryModel::MallocHost(std::size_t size)
{
	host.emplace_back(ByteArray(size));
	return reinterpret_cast<void*>(host.back().data());
}

void MemoryModel::FreeHost(void* p)
{
	const auto it = std::remove_if(host.begin(), host.end(),
		[p](const auto& arr) { return reinterpret_cast<const void*>(arr.data()) == p; });
	host.erase(it, host.end());
}

void* MemoryModel::MallocDevice(std::size_t size)
{
	device.emplace_back(ByteArray(size));
	return reinterpret_cast<void*>(device.back().data());
}

void MemoryModel::FreeDevice(void* p)
{
	const auto it = std::remove_if(device.begin(), device.end(),
		[p](auto&& arr) { return reinterpret_cast<void*>(arr.data()) == p; });
	device.erase(it, device.end());
}

void MemoryModel::MemcpyHostToHost(const void* source, void* destination, std::size_t count)
{
	Memcpy(host, source, host, destination, count);
}

void MemoryModel::MemcpyHostToDevice(const void* source, void* destination, std::size_t count)
{
	Memcpy(host, source, device, destination, count);
}

void MemoryModel::MemcpyDeviceToHost(const void* source, void* destination, std::size_t count)
{
	Memcpy(device, source, host, destination, count);
}

void MemoryModel::MemcpyDeviceToDevice(const void* source, void* destination, std::size_t count)
{
	Memcpy(device, source, device, destination, count);
}
