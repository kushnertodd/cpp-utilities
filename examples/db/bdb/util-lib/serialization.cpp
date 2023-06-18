#include <cstring>
#include "serialization.hpp"

size_t Serialization::buffer_len_char_string(const char *chars_val) {
  int chars_len = (int) std::strlen(chars_val) + 1;
  return
    //sizeof(chars_len) +
      chars_len;
}

size_t Serialization::buffer_len_string(const std::string &string_val) {
  return buffer_len_char_string(string_val.c_str());
}

/*
void *Serializable::deserialize_char_string(char *chars_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  int chars_len;
  p = (unsigned char *) deserialize_int(chars_len, p);
  std::memcpy(chars_val, p, chars_len);
  p += chars_len;
  *p++ = '\0';
  return p;
}
*/

void *Serialization::deserialize_double(double &double_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  std::memcpy(&double_val, p, sizeof(double));
  p += sizeof(double);
  return p;
}

void *Serialization::deserialize_float(float &float_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  std::memcpy(&float_val, p, sizeof(float));
  p += sizeof(float);
  return p;
}

void *Serialization::deserialize_int(int &int_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  std::memcpy(&int_val, p, sizeof(int));
  p += sizeof(int);
  return p;
}

void *Serialization::deserialize_long(long &long_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  std::memcpy(&long_val, p, sizeof(long));
  p += sizeof(long);
  return p;
}

void *Serialization::deserialize_string(std::string &string_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  //p = (unsigned char *) deserialize_int(chars_len, p);
  size_t chars_len = std::strlen((char *) p) + 1;
  string_val = std::string((const char *) p);
  p += chars_len;
  return p;
}

void *Serialization::serialize_char_string(const char *chars_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  int chars_len = (int) std::strlen(chars_val) + 1;
  //p = (unsigned char *) serialize_int(chars_len, p);
  strcpy((char *) p, chars_val);
  p += chars_len;
  return p;
}

void *Serialization::serialize_double(const double &double_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  std::memcpy(p, &double_val, sizeof(double));
  p += sizeof(double);
  return p;
}

void *Serialization::serialize_float(const float &float_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  std::memcpy(p, &float_val, sizeof(float));
  p += sizeof(float);
  return p;
}

void *Serialization::serialize_int(const int &int_val, void *buffer)  {
  auto *p = (unsigned char *) buffer;
  std::memcpy(p, &int_val, sizeof(int));
  p += sizeof(int);
  return p;
}

void *Serialization::serialize_long(const long &long_val, void *buffer) {
  auto *p = (unsigned char *) buffer;
  std::memcpy(p, &long_val, sizeof(long));
  p += sizeof(long);
  return p;
}

void *Serialization::serialize_string(const std::string &string_val, void *buffer) {
  return serialize_char_string(string_val.c_str(), buffer);
}

