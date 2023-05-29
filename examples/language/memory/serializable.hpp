#pragma once

class Serializable {
public:
  virtual size_t buffer_size() = 0;
  virtual void *deserialize(void *buffer) = 0;
  virtual void *serialize(void *buffer) = 0;

  static void *deserialize_chars(char *chars_val, void *buffer);
  static void *deserialize_char_string(char *chars_val, void *buffer);
  static void *deserialize_double(double &double_val, void *buffer);
  static void *deserialize_float(float &float_val, void *buffer);
  static void *deserialize_int(int &int_val, void *buffer);
  static void *deserialize_long(long &long_val, void *buffer);
  static void *deserialize_string(std::string &string_val, void *buffer);

  static void *serialize_char_string(const char *chars_val, void *buffer);
  static void *serialize_chars(const char *chars_val, int chars_len, void *buffer);
  static void *serialize_double(double &double_val, void *buffer);
  static void *serialize_float(float &float_val, void *buffer);
  static void *serialize_int(int &int_val, void *buffer);
  static void *serialize_long(long &long_val, void *buffer);
  static void *serialize_string(const std::string &string_val, void *buffer);
};
