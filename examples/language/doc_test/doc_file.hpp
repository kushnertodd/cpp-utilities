//
// Created by kushn on 8/9/2022.
//

#ifndef DOC__DOC_FILE_HPP_
#define DOC__DOC_FILE_HPP_

/**
 * doxygen test class
 * this is a test
 * @image html test.jpg
 *
 * First Header  | Second Header
 * ------------- | -------------
 * Content Cell  | Content Cell
 * Content Cell  | Content Cell
 *
 *   case       | 2.1 | 2.2  | 2.3   | 2.4  | 2.5  | 2.6  | 2.7
 *   -----------|-----|------|-------|------|------|------|-----
 *   upper point|above|above |inside |inside|inside|below |below
 *   lower point|above|inside|above  |inside|below |inside|below
 */
class doc_file {

  /**
   * this is the foo function
   * @param a
   * @param b
   */
  void foo(int a, bool b) {

  }

  /** int test; */
  int test;
};

#endif //DOC__DOC_FILE_HPP_
