#include <locale>
#include <iostream>
#include <sstream>
#include <iomanip>

class comma_numpunct : public std::numpunct<char>
{
  protected:
    virtual char do_thousands_sep() const
    {
        return ',';
    }

    virtual std::string do_grouping() const
    {
        return "\03";
    }
};

class format_comma {
  public:
    format_comma() { }
    static std::string format(long num, int width = 0) {
      std::locale comma_locale(std::locale(), new comma_numpunct());
      std::ostringstream os;
      os.imbue(comma_locale);
      if (width == 0)
        os << num;
      else
        os << std::setw(width) << num;
      return os.str();
    }
};

int main()
{
    // this creates a new locale based on the current application default
    // (which is either the one given on startup, but can be overriden with
    // std::locale::global) - then extends it with an extra facet that 
    // controls numeric output.
    //std::locale comma_locale(std::locale(), new comma_numpunct());

    // tell cout to use our new locale.
    std::ostringstream os;
    long num = 1000000000;

    std::cout << format_comma::format(num) << std::endl;
    std::cout << format_comma::format(num, 15) << std::endl;
    std::cout << num << std::endl;
}
