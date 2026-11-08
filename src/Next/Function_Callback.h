#include <iostream>
#include <functional>


void SomeFunction() {
  std::cout << "Hello World";
}

// callback
void Process(int Number, void (*EvenCallback)() = nullptr) {
  std::cout << "\nProcessing " << Number;
  if (EvenCallback && Number % 2 == 0) {
    EvenCallback();
  }
}

void LogEven() {
  std::cout << " - that number is even";
}

void FunctionA(){};
bool FunctionB(int x) { return true; }
bool FunctionC(int x, float y) { return true; }


void Greet() {
  std::cout << "Hello World\n";
}

// Returning Functions
std::function<void()> GetFunction() {
  return Greet;
}

int function_demo() {
  auto FunctionPtr{&SomeFunction};
  (*FunctionPtr)(); // output: Hello World

  Process(4, LogEven);


  // A function that returns nothing
  // and accepts no arguments
  void (*PtrA)(){FunctionA};

  // A function that returns a bool
  // and accepts an int argument
  bool (*PtrB)(int){FunctionB};

  // A function that returns a bool and
  // accepts int and float arguments
  bool (*PtrC)(int, float){FunctionC};


  // A function that returns nothing
  // and accepts no arguments
  std::function<void()> stdPtrA{FunctionA};

  // A function that returns a bool
  // and accepts an int argument
  std::function<bool(int)> stdPtrB{FunctionB};

  // A function that returns a bool and
  // accepts int and float arguments
  std::function<bool(int, float)> stdPtrC{FunctionC};

  // When we're providing an initial value, the
  // compiler can usually infer the return and
  // argument types using Class Template Argument
  // Deduction (CTAD)
  std::function PtrD{FunctionC};


  auto Func{GetFunction()};
  Func();

  // Alternatively:
  GetFunction()();

  return 0;
}