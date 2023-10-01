#pragma once

#include <cassert>
#include <vector>

namespace fe {

template<size_t A = alignof(size_t), size_t P = 1024 * 1024>
class Arena {
public:
    template<class T>
    class Allocator {
    public:
        using value_type                             = T;
        using size_type                              = std::size_t;
        using difference_type                        = std::ptrdiff_t ;
        using propagate_on_container_move_assignment = std::true_type;

        Allocator() = delete;
        constexpr Allocator(Arena<A, P>& arena) noexcept
            : arena_(arena) {}
        constexpr Allocator(const Arena<A, P>::Allocator<T>& allocator) noexcept
            : arena_(allocator.arena_) {}

        T* allocate(size_type n, const void* /*hint*/ = 0) {
            static_assert(alignof(T) <= A, "alignment of Arena too small");
            return (T*)arena_.alloc(n * sizeof(T));
        }

        void deallocate(T*, size_type) {}
        constexpr size_type max_size() const { return size_type(-1) / sizeof(T); }

        template<class U> bool operator==(const Allocator<U>& other) const noexcept { return &this->arena_ == &other.arena_; }
        template<class U> bool operator!=(const Allocator<U>& other) const noexcept { return &this->arena_ != &other.arena_; }

    private:
        Arena<A, P>& arena_;
    };

public:
    Arena() = default;
    ~Arena() {
        for (auto p : pages_) delete[] p;
    }

    static constexpr size_t align(size_t n) { return (n + (A - 1)) & ~(A - 1); }

    [[nodiscard]] void* alloc(size_t n) {
        n = align(n);

        if (index_ + n > P) {
            pages_.emplace_back(new char[std::max(P, n)]);
            index_ = 0;
        }

        auto result = pages_.back() + index_;
        index_ += n;
        assert(index_ % A == 0);
        return result;
    }

    /// Tries to remove @p n bytes again.
    /// If this crosses a page boundary, nothing happens.
    void dealloc(size_t n) {
        n = align(n);
        if (ptrdiff_t(index_ - n) > 0) index_ -= n; // don't care otherwise
        assert(index_ % A == 0);
    }

    friend void swap(Arena& a1, Arena& a2) {
        using std::swap;
        swap(a1.pages_, a2.pages_);
        swap(a1.index_, a2.index_);
    }

private:
    std::vector<char*> pages_;
    size_t index_ = P;
};

} // namespace arena
