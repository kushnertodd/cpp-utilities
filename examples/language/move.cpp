#include <iostream>

class A {
public:
  int i;
  A(int i) : i(i) {
    std::cout << "  -> constructor A("<<i<<") " << std::endl;
  }
  A(const A& other) : i(other.i) {
    std::cout << "  -> const copy constructor A(const A& other."<<other.i<<") " << std::endl;
  }
  A(A& other) : i(other.i) {
    std::cout << "  -> copy constructor A(A& other."<<other.i<<") " << std::endl;
  }
  A(A&& other) : i(std::move(other.i)) {
    std::cout << "  -> move constructor A(A&& other."<<other.i<<") " << std::endl;
  }
  A& operator=(const A& other) {
    std::cout << "  -> const assignment operator A& operator=(const A& other."<<other.i<<") " << std::endl;
    i = other.i;
    return *this;
  }
  A& operator=(A& other) {
    std::cout << "  -> assignment operator A& operator=(A& other."<<other.i<<") " << std::endl;
    i = other.i;
    return *this;
  }
  A& operator=(A&& other) {
    std::swap(i, other.i);
    std::cout << "  -> move assignment operator A& operator=(A&& other."<<other.i<<") " << std::endl;
    return *this;
  }
};

A rval_to_rval(A a) {
  std::cout << "  -> rval_to_rval(A a."<<a.i<<") " << std::endl;
  return a;
}
A ref_to_rval(A& a) {
  std::cout << "  -> ref_to_rval(A& a."<<a.i<<") " << std::endl;
  return a;
}
A rval_ref_to_rval(A&& a) {
  std::cout << "  -> rval_ref_to_rval(A&& a."<<a.i<<") " << std::endl;
  return a;
}
A&& rval_to_rval_ref(A a) {
  std::cout << "  -> rval_to_rval_ref(A&& a."<<a.i<<") " << std::endl;
  //return std::move(a); warning
  return std::move(rval_to_rval_ref(a));
}
A&& ref_to_rval_ref(A& a) {
  std::cout << "  -> ref_to_rval(A&& a."<<a.i<<") " << std::endl;
  //return a;
  return std::move(a);
}
A&& rval_ref_to_rval_ref(A&& a) {
  std::cout << "  -> rval_ref_to_rval(A&& a."<<a.i<<") " << std::endl;
  //return a;
  return std::move(a);
}
int main() {
  std::cout << "  A a1(1);" << std::endl;
  A a1(1);
  // illegal
  // A& a2(2);
  std::cout << "  A&& a3(3);" << std::endl;
  A&& a3(3);
  std::cout << "  A a4(a3);" << std::endl;
  A a4(a3);
  std::cout << "  A& a5(a4);" << std::endl;
  A& a5(a4);
  std::swap(a5, a5);
  // illegal
  // A&& a6(a5);

  std::cout << "  A a6(A(6));" << std::endl;
  A a6(A(6));
  // illegal
  // A& a7(A(7));
  std::cout << "  A&& a8(A(8));" << std::endl;
  A&& a8(A(8));
  std::swap(a8, a8);

  std::cout << "  A a6z(rval_to_rval(a8));" << std::endl;
  A a6z(rval_to_rval(a8));
  // illegal
  // A& a7z(rval_to_rval(a6z));
  std::cout << "  A&& a8z(rval_to_rval(a6z));" << std::endl;
  A&& a8z(rval_to_rval(a6z));
  std::swap(a8z, a8z);

  std::cout << "  const A a9(9);" << std::endl;
  const A a9(9);
  // illegal
  std::cout << "  const A& a10(10);" << std::endl;
  const A& a10(10);
  A a10x = a10;
  std::swap(a10x, a10x);
  std::cout << "  const A&& a11(11);" << std::endl;
  const A&& a11(11);
  std::cout << "  const A a12(a11);" << std::endl;
  const A a12(a11);
  std::cout << "  const A& a13(a12);" << std::endl;
  const A& a13(a12);
  A a13x = a13;
  std::swap(a13x, a13x);
  // illegal
  // A&& a14(a13);

  // illegal
  std::cout << "  const A a15(A(15));" << std::endl;
  const A a15(A(15));
  // illegal
  // A& a16(A(16));
  std::cout << "  const A&& a17(A(17));" << std::endl;
  const A&& a17(A(17));
  A a17x = a17;
  std::swap(a17x, a17x);
  std::cout << "  const A a18(A(18));" << std::endl;
  const A a18(A(18));
  std::cout << "  const A&& a19(A(19));" << std::endl;
  const A&& a19(A(19));

  std::cout << "  const A a20(rval_to_rval(a19));" << std::endl;
  const A a20(rval_to_rval(a19));
  std::cout << "  const A& a21(rval_to_rval(a20));" << std::endl;
  const A& a21(rval_to_rval(a20));
  std::cout << "  const A&& a22(rval_to_rval(a21));" << std::endl;
  const A&& a22(rval_to_rval(a21));
  A a22x = a22;
  std::swap(a22x, a22x);


  std::cout << "  A a23 = rval_to_rval(A(23));" << std::endl;
  A a23 = rval_to_rval(A(23));
  std::swap(a23, a23);
  // illegal
  // A& a24 = rval_to_rval(A(24));
  std::cout << "  A&& a25 = rval_to_rval(A(25));" << std::endl;
  A&& a25 = rval_to_rval(A(25));
  std::cout << "  A a26 = ref_to_rval(a25);" << std::endl;
  A a26 = ref_to_rval(a25);
  // illegal
  // A& a27 = ref_to_rval(a26);
  std::cout << "  A&& a28 = ref_to_rval(a26);" << std::endl;
  A&& a28 = ref_to_rval(a26);
  std::swap(a28, a28);
  std::cout << "  A a29 = rval_ref_to_rval(A(29));" << std::endl;
  A a29 = rval_ref_to_rval(A(29));
  std::swap(a29, a29);
  // illegal
  // A& a30 = rval_ref_to_rval(A(30));
  std::cout << "  A&& a31 = rval_ref_to_rval(A(31));" << std::endl;
  A&& a31 = rval_ref_to_rval(A(31));
  std::swap(a31, a31);

  std::cout << "  A a32 = rval_to_rval_ref(A(32));" << std::endl;
  std::cout << "  infinite loop: " << std::endl;
  std::cout << "      -> constructor A(32) " << std::endl;
  std::cout << "      -> rval_to_rval_ref(A&& a.32) " << std::endl;
  std::cout << "      -> copy constructor A(A& other.32) " << std::endl;
  std::cout << "      ..." << std::endl;
  // A a32 = rval_to_rval_ref(A(32));
  // std::swap(a32, a32);
  // illegal
  // A& a33 = rval_to_rval_ref(A(33));
  std::cout << "  A&& a34 = rval_to_rval_ref(A(34));" << std::endl;
  std::cout << "  infinite loop: " << std::endl;
  std::cout << "      -> constructor A(34) " << std::endl;
  std::cout << "      -> rval_to_rval_ref(A&& a.34) " << std::endl;
  std::cout << "      -> copy constructor A(A& other.34) " << std::endl;
  // A&& a34 = rval_to_rval_ref(A(34));
  // std::swap(a34, a34);
  std::cout << "  A a35 = ref_to_rval_ref(a34);" << std::endl;
  A a35 = ref_to_rval_ref(a31);
  // illegal
  // A& a36 = ref_to_rval_ref(a35);
  std::cout << "  A&& a37 = ref_to_rval_ref(a35);" << std::endl;
  A&& a37 = ref_to_rval_ref(a35);
  std::swap(a37, a37);
  std::cout << "  A a38 = rval_ref_to_rval_ref(A(38));" << std::endl;
  A a38 = rval_ref_to_rval_ref(A(38));
  std::swap(a38, a38);
  // illegal
  // A& a39 = rval_ref_to_rval_ref(A(39));
  std::cout << "  A&& a40 = rval_ref_to_rval_ref(A(40));" << std::endl;
  A&& a40 = rval_ref_to_rval_ref(A(40));
  std::swap(a40, a40);
}
