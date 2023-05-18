enum class Traffic_light { red, yellow, green };
enum class Warning { green, yellow, orange, red }; // fire alert lev els
Warning a1 = 7; // error : no int->War ning conversion
int a2 = green; // error : green not in scope
int a3 = Warning::green; // error : no War ning->int conversion
Warning a4 = Warning::green; // OK
void f(Traffic_light x)
{
  if (x == 9) { /* ... */ } // error : 9 is not a Traffic_light
  if (x == red) { /* ... */ } // error : no red in scope
  if (x == Warning::red) { /* ... */ } // error : x is not a War ning
  if (x == Traffic_light::red) { /* ... */ } // OK
}
