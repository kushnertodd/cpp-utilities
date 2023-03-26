#include <locale>
#include <iostream>
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

int main()
{
    // this creates a new locale based on the current application default
    // (which is either the one given on startup, but can be overriden with
    // std::locale::global) - then extends it with an extra facet that 
    // controls numeric output.
    std::locale comma_locale(std::locale(), new comma_numpunct());

    // tell cout to use our new locale.
    std::cout.imbue(comma_locale);

    std::cout << std::setprecision(2) << std::fixed << 1000000.1234 << std::endl;
}
