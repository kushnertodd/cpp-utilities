// Fig. 22.22: Fig22_22.cpp
  // Standard Library class map test program.
  #include <iostream>
  #include <map> // map class-template definition
  #include <list>
  #include <algorithm>
  #include <functional>
  #include <iterator>
  using namespace std;

  typedef map< int, double, less< int > > Mid;

  int main()
  {
     Mid pairs;

     // insert eight value_type objects in pairs                
     pairs.insert( Mid::value_type( 15, 2.7 ) );                
     pairs.insert( Mid::value_type( 30, 111.11 ) );             
     pairs.insert( Mid::value_type( 5, 77.54 ) ); // dup ignored
     pairs.insert( Mid::value_type( 15, 99.3 ) ); // dup ignored

     cout << "pairs contains:\nKey\tValue\n";

     // use const_iterator to walk through elements of pairs
     for ( Mid::const_iterator iter = pairs.begin();        
        iter != pairs.end(); ++iter )                       
        cout << iter->first << '\t' << iter->second << '\n';

     pairs[ 25 ] = 9999.99; // use subscripting to change value for key 25
     pairs[ 40 ] = 8765.43; // use subscripting to insert value for key 40

     cout << "\nAfter subscript operations, pairs contains:\nKey\tValue\n";

     // use const_iterator to walk through elements of pairs
     for ( Mid::const_iterator iter2 = pairs.begin();
        iter2 != pairs.end(); ++iter2 )
        cout << iter2->first << '\t' << iter2->second << '\n';

     Mid::iterator it1 = pairs.find(25);
     if (it1 == pairs.end())
       cout << "find(25) = nothing " << endl;
     else
       cout << "find(25) = " << it1->second;
     Mid::iterator it2 = pairs.find(26);
     cout << endl;
     //if (it2 == pairs.end())
     //  cout << "find(26) = nothing " << endl;
     //else
       cout << "find(26) = " << it2->second;
     cout << endl;
     return 0;
  } // end main
