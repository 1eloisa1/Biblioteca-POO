#pragma once
#include <vector>
#include <cstddef>
#include <concepts>
#include <utility>

// Q1 (B): CRTP - Mixin para contagem estática de instâncias vivas sem vtable
template <typename Derived>
class Counted {
private:
    static inline int count_ = 0;

public:
    Counted() { ++count_; }
    Counted(const Counted&) { ++count_; }
    Counted(Counted&&) noexcept { ++count_; }
    ~Counted() { --count_; }

    static int alive() { return count_; }
};

// Q1 (C): Concept C++20 - Restringe o template para tipos com calcular() const -> double
template <typename T>
concept Calculavel = requires(const T& t) {
    { t.calcular() } -> std::convertible_to<double>;
};

// Q1 (A) & (D): Template reutilizável restrito pelo Concept Calculavel
template <Calculavel T>
class Registry {
private:
    std::vector<T> items_;

public:
    void add(T item) {
        items_.push_back(std::move(item));
    }

    const T& at(std::size_t index) const {
        return items_.at(index);
    }

    std::size_t size() const {
        return items_.size();
    }

    const std::vector<T>& get_items() const {
        return items_;
    }
};