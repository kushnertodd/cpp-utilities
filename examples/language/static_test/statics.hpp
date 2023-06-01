// https://en.cppreference.com/w/cpp/language/static

class Statics {
public:
  static int not_inited;
  static int* not_inited_ptr;
  static void init();
};

class Globals {
public:
  int not_inited;
  int* not_inited_ptr;
  void init();
};

