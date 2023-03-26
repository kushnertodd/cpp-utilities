#include <iostream>
#include <exception>

class MyException : public std::exception {
private:
  const char* msg;
  const char* more;
  const int num;

public:
  MyException(
    const char* m_msg,
    const char* m_more,
    const int m_num) :
    msg (m_msg),
    more (m_more),
    num (m_num)
  {
  }

  virtual const char* what() const noexcept {
    return msg;
  }
  const char* get_more() const {
    return more;
  }
  int get_num() const {
    return num;
  }
};

int main()
{
  try
  {
    MyException ex("msg", "more", 1);
    throw ex;
  }
  catch (MyException& ex)
  {
    std::cout<< "what: '" << ex.what() << "'" << std::endl;
    std::cout<< "more: '" << ex.get_more() << "'" << std::endl;
    std::cout<< "num: " << ex.get_num() << std::endl;

    //return EXIT_FAILURE;
  }
  try
  {
    throw "message";
  } 
  catch (const char* ex) 
  {
    std::cout<<"caught: const char* '" << ex << "'" << std::endl;
  }
  try
  {
    throw std::string("message");
  } 
  catch (std::string ex) 
  {
    std::cout<<"caught: std::string '" << ex << "'" << std::endl;
  }
  try
  {
    throw 1;
  } 
  catch (int ex) 
  {
    std::cout<<"caught: int " << ex << std::endl;
  }

}
