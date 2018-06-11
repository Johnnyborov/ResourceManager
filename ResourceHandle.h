#ifndef RESOURCE_HANDLE_H
#define RESOURCE_HANDLE_H
#include <cstddef>
#include <string>

class ResourceHandle {
public:
  ResourceHandle(std::string resource_name);
  ResourceHandle(const char* data_start, const size_t data_len) : m_data_start{ data_start }, m_data_len{ data_len } {}

private:
  const char* m_data_start;
  size_t m_data_len;
};


#endif // RESOURCE_HANDLE_H