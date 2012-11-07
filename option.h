#ifndef OPTION_H
#define OPTION_H
#include <vector>
#include <exception>
using namespace std;

class noneGetException: public exception
{
  virtual const char* what() const throw() {
    return "Can't get a value from an empty option"; 
  }
};

template <typename T>
class Option{
  public:
    Option(T value): value(value) ,hasValue(true) {}
    Option(): hasValue(false) {}
    bool isDefined() const { return hasValue; }
    bool isEmpty() const { return hasValue; }
    bool exists( bool (*p)(T)) const;
    bool operator==(const Option<T> &other) const;
    T operator*() const{ return this->get(); }
    Option<T> filter(bool (*f)(T)) const;
    Option<T> filterNot(bool (*f)(T)) const;
    T get() const;

    template<typename B>
    Option<B> flatMap(Option<B> (*f)(T)) const {
      if (!hasValue){
        return Option<B>();
      } else {
        return f(value);
      }
    }

    void foreach( void (*f)(T)) const;
    void forall( bool (*f)(T)) const;

    template<typename B>
    Option<B> map(B (*f)(T)) const {
      if (!hasValue) {
        return Option<B>();
      } else {
        return Some(f(value));
      }
    }

    T getOrElse (T _else) const;
    vector<T> toVector() const;

  private:

    T value;
    bool hasValue;
};

template <typename T>
class None : public Option<T>{
  public:
    None(): Option<T>(){}
};

template <typename T>
class Some: public Option<T>{
  public:
    Some(T value): Option<T>(value){};
};

template <typename T>
bool Option<T>::exists(bool (*p)(T)) const {
  return hasValue && p(value);
}

template <typename T>
bool Option<T>::operator==(const Option<T> &other) const {
  if (!(this->hasValue) && !(other.hasValue)) {
    return true;
  } else {
    return this->value == other.value; 
  }
}

template <typename T>
Option<T> Option<T>::filter(bool (*f)(T)) const {
  if (!hasValue || !f(value)) {
    return None<T>();
  } else {
    return Some<T>(value);
  }
}

template <typename T>
Option<T> Option<T>::filterNot(bool (*f)(T)) const {
  if (!hasValue || f(value)) {
    return None<T>();
  } else {
    return Some<T>(value);
  }
}

template <typename T>
T Option<T>::get() const {
  if (!hasValue){
    throw noneGetException();
  } else {
    return value;
  }
}

template <typename T>
void Option<T>::foreach(void (*f)(T)) const {
  if (hasValue) {
    f(value);
  }
}

template <typename T>
void Option<T>::forall(bool (*f)(T)) const {
  if (hasValue) {
    return f(value);
  } else {
    return true;
  }
}

template <typename T>
T Option<T>::getOrElse (T _else) const {
  if ( hasValue ) {
    return value;
  } else {
    return _else;
  }
}

template <typename T>
vector<T> Option<T>::toVector() const {
  if (hasValue) {
    return vector<T>{value};
  } else{
    return vector<T>();
  }
}

#endif
