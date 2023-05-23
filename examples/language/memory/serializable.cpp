#include "serializable.hpp"

void * Serializable::deserialize_char_string(const char *chars_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  int chars_len;
  p = deserialize_int(chars_len, p);
  std::memcpy(chars_val, p,  chars_len);
  p += chars_len;
  *p++ = '\0';
  return p;
}

void * Serializable::deserialize_chars(char *chars_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  int chars_len;
  p = deserialize_int(chars_len, p);
  std::memcpy(chars_val, p,  chars_len);
  p += chars_len;
  return p;
}

void * Serializable::deserialize_double(double &double_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(*double_val, p, sizeof(double));
  p += sizeof(double);
  return p;
}

void * Serializable::deserialize_float(float &float_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(*float_val, p, sizeof(float));
  p += sizeof(float);
  return p;
}

void * Serializable::deserialize_int(int &int_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(*int_val, p, sizeof(int));
  p += sizeof(int);
  return p;
}

void * Serializable::deserialize_long(long &long_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(*long_val, p, sizeof(long));
  p += sizeof(long);
  return p;
}

void * Serializable::deserialize_string(const std::string &string_val, void *buffer) {
  return deserialize_chars(string_val.c_str(), buffer);
}

void * Serializable::serialize_char_string(const char *chars_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  int chars_len = std::strlen(chars_val);
  p = serialize_int(chars_len, p);
  std::memcpy(p, chars_val, chars_len);
  p += chars_len;
  return p;
}

void * Serializable::serialize_chars(const char *chars_val, int chars_len, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  p = serialize_int(chars_len, p);
  std::memcpy(p, chars_val, chars_len);
  p += chars_len;
  return p;
}

void * Serializable::serialize_double(double &double_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(p, *double_val, sizeof(double));
  p += sizeof(double);
  return p;
}

void * Serializable::serialize_float(float &float_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(p, *float_val, sizeof(float));
  p += sizeof(float);
  return p;
}

void * Serializable::serialize_int(int &int_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(p, *int_val, sizeof(int));
  p += sizeof(int);
  return p;
}

void * Serializable::serialize_long(long &long_val, void *buffer) {
  unsigned char *p = (unsigned char *) buffer;
  std::memcpy(p, *long_val, sizeof(long));
  p += sizeof(long);
  return p;
}

void * Serializable::serialize_string(const std::string &string_val, void *buffer) {
  return serialize_chars(string_val.c_str(), buffer);
}

