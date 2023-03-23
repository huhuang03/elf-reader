//
// Created by hwf on 2023/3/7.
//
#include <stdio.h>

class Foo {
 private:
  static Foo* inst_;
  int i = 0;
  Foo() {
    i = 2;
  }

 public:
  static Foo* getInstance() {
    if (inst_ == nullptr) {
      inst_ = new Foo();
    }
    return inst_;
  }
};

int a = 1;
int b = 0;
int c;

Foo* Foo::inst_;

int main() {
  printf("foo: %p", Foo::getInstance());
  return 0;
}
