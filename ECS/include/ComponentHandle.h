#pragma once

template<typename T>
class ComponentHandle {
  std::optional<std::reference_wrapper<T>> _inner;

 public:
  ComponentHandle(std::nullptr_t) : _inner() {
  }

  constexpr ComponentHandle(T &ref) : _inner(std::forward<T&>(ref)) {
  }

  constexpr ComponentHandle(T &&ref) : _inner(std::forward<T&>(ref)) {
  }

  ComponentHandle(const ComponentHandle<T> &) = delete;
  ComponentHandle<T>& operator=(const ComponentHandle<T>&) = delete;

  T& operator*() {
      return _inner->get();
  }

  T* operator->() {
      return &_inner->get();
  }

  operator bool() {
      return _inner.has_value();
  }

  constexpr bool operator==(std::nullptr_t) {
      return _inner == std::nullopt;
  }
};