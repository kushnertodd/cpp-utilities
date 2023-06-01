// Fig. 22.22: Fig22_22.cpp
  // Standard Library class map test program.
  #include <iostream>
  #include <map> // map class-template definition
  #include <list>
  #include <algorithm>
  #include <functional>
  #include <iterator>
  using namespace std;

  // define short name for map type used in this program
  //typedef list< double, less< int > > DList;
  typedef list< double > DList;
  typedef map< int, double, less< int > > Mid;

  int main()
  {
     Mid pairs;
     DList dlist;
     ostream_iterator< int > output( cout, " " );

     // insert eight value_type objects in pairs                
     int array[] = { 15, 30, 5, 10, 25, 5, 20, 15 };
     dlist.insert(dlist.begin(), array, array+8);
     cout << "dlist contains:";
     copy(dlist.begin(), dlist.end(), output);
     cout << endl;
     sort(dlist);
     cout << "sorted dlist contains:";
     copy( dlist.begin(), dlist.end(), output);
     cout << endl;

     // insert eight value_type objects in pairs                
     pairs.insert( Mid::value_type( 15, 2.7 ) );                
     pairs.insert( Mid::value_type( 30, 111.11 ) );             
     pairs.insert( Mid::value_type( 5, 1010.1 ) );              
     pairs.insert( Mid::value_type( 10, 22.22 ) );              
     pairs.insert( Mid::value_type( 25, 33.333 ) );             
     pairs.insert( Mid::value_type( 5, 77.54 ) ); // dup ignored
     pairs.insert( Mid::value_type( 20, 9.345 ) );              
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

     cout << endl;
     return 0;
  } // end main
