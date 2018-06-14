// Copyright (c) 2018 Johnny Borov <JohnnyBorov@gmail.com>. Released under MIT License.

#ifndef RM_RESOURCE_HANDLE_H
#define RM_RESOURCE_HANDLE_H

#include <cstddef>
#include <string>
#include <exception>

// This exception type is thrown if ResourceHandle constructor gets invalid resource name.
// Compile with -DRM_NO_EXCEPTIONS to disable throwing on invalid resource name.
class ResourceNotFound : public std::exception {
public:
  ResourceNotFound(std::string resource_name) : m_message{"ResourceManager: Resource not found: " + resource_name} {}
  virtual const char* what() const noexcept { return m_message.c_str(); }

private:
  const std::string m_message;
};


// This class holds a pointer to the beginning of binary data for the requested resource
// and the length/size (in bytes) of this data. (length and size are the same thing).
// -------------------------------------------------------------------------------------------
// If constructor is called with an invalid resource name ResourceNotFound exception is thrown
// Compile with -DRM_NO_EXCEPTIONS to disable throwing on invalid resource name.
// -------------------------------------------------------------------------------------------
// If exceptions are disabled and constructor is called with an invalid resource name
// then the pointer to the data equials nullptr and length/size equals 0.
// In this case you can use isValid() to determine whether construction was successful or not.
// ===========================================================================================
// Avaliable functions:
// -- const bool isValid() const noexcept:
//  # returns true if construction was successful, false otherwise.
//  #
// -- const unsigned char* const data() const noexcept:
//  # returns the pointer to the beginning of binary data or nullptr if construction failed.
//  # The data is null-terminated in the end.
//  #
// -- const char* const c_str() const noexcept:
//  # returns the pointer to the beginning of binary data or nullptr if construction failed.
//  # The data is null-terminated in the end.
//  #
// -- std::string string() const:
//  # returns std::string based on the binary data with same length as the data.
//  # If there are zeroes in the middle of the data string will contain them anyway.
//  #
// -- const size_t size() const noexcept:
//  # returns size of the data in bytes or 0 if construction failed.
//  # Null-terminator is not taken into account.
//  #
// -- const size_t length() const noexcept:
//  # same as size().
//  #
// ===========================================================================================
class ResourceHandle {
public:
  ResourceHandle(std::string resource_name);

  const bool isValid() const noexcept { if (m_data_start) return true; else return false; }

  const size_t size() const noexcept { return m_data_len; }
  const size_t length() const noexcept { return m_data_len; }

  const unsigned char* const data() const noexcept { return m_data_start; }

  const char* const c_str() const noexcept { return reinterpret_cast<const char*>(m_data_start);; }
  std::string string() const { return std::string(reinterpret_cast<const char*>(m_data_start), m_data_len); }

private:
  const unsigned char* m_data_start;
  size_t m_data_len;
};

#endif // RM_RESOURCE_HANDLE_H