#ifndef RM_RESOURCE_HANDLE_H
#define RM_RESOURCE_HANDLE_H

#include <cstddef>
#include <string>
#include <exception>

class ResourceNotFound : public std::exception {
public:
  ResourceNotFound(std::string resource_name) : m_message{"ResourceManager: Resource not found: " + resource_name} {}
  virtual const char* what() const noexcept { return m_message.c_str(); }

private:
  std::string m_message;
};

class ResourceHandle {
public:
  ResourceHandle(std::string resource_name);

  const bool isValid() const { if (m_data_start) return true; else return false; }

  const unsigned char* const data() const { return reinterpret_cast<const unsigned char*>(m_data_start); }
  const size_t size() const { return m_data_len; }

  const char* const c_str() const { return m_data_start; }
  std::string string() const { return std::string(m_data_start, m_data_len); }

private:
  const char* m_data_start;
  size_t m_data_len;
};

#endif // RM_RESOURCE_HANDLE_H