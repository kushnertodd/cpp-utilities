class Stack {
  public:
      class Underflow{};
      class Overflow{};
      virtual ~Stack();
      virtual void push(char c) = 0;
      virtual char pop() = 0;
};
