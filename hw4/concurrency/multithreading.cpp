#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

using namespace std;

class Foo {
protected:
    int value = 0;

public:
    virtual int Get() const = 0;

    virtual void Set(int new_value) = 0;
};

class FooMutex : public Foo {
private:
    mutable mutex mtx;

public:
    int Get() const override {
        unique_lock<mutex> lock(mtx);
        return value;
    }

    void Set(int newValue) override {
        unique_lock<mutex> lock(mtx);
        value = newValue;
    }
};

class FooSharedMutex : public Foo {
private:
    mutable shared_mutex mtx;

public:
    int Get() const override {
        shared_lock<shared_mutex> lock(mtx);
        return value;
    }

    void Set(int newValue) override {
        unique_lock<shared_mutex> lock(mtx);
        value = newValue;
    }
};

void job(Foo &foo, int iter_count, bool isGet) {
    for (int iter = 0; iter < iter_count; ++iter) {
        if (isGet) {
            foo.Get();
        } else {
            foo.Set(42 * iter + iter_count);
        }
    }
}

enum TestMode {
    Get,
    Set,
    Both
};

int64_t test(Foo &foo, int threads_count, int iter_count, TestMode mode) {
    auto start_time = std::chrono::high_resolution_clock::now();

    vector<thread> threads;
    for (int idx = 0; idx < threads_count; ++idx) {
        bool condition = true;
        switch (mode) {
            case Get:
                condition = true;
                break;
            case Set:
                condition = false;
                break;
            case Both:
                condition = idx % 2 == 0;
                break;
        }

        threads.emplace_back(job, std::ref(foo), iter_count, condition);
    }
    for (auto &thread: threads) {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
}

int main() {
    int threads_count = 4;
    std::cout << "Threads count: " << threads_count << "\n";

    int iter_count = 7'000'000;
    std::cout << "Iter count: " << iter_count << "\n";

    {
        std::cout << "Get Job\n";

        FooMutex foo_mtx;
        std::cout << "Foo Mutex: " << test(foo_mtx, threads_count, iter_count, Get) << "ms\n";
        // ~ 3200 ms

        FooSharedMutex foo_smtx;
        std::cout << "Foo Shared Mutex: " << test(foo_smtx, threads_count, iter_count, Get) << "ms\n";
        // ~ 2500 ms
    }

    {
        std::cout << "Set Job\n";

        FooMutex foo_mtx;
        std::cout << "Foo Mutex: " << test(foo_mtx, threads_count, iter_count, Set) << "ms\n";
        // ~ 3000 ms

        FooSharedMutex foo_smtx;
        std::cout << "Foo Shared Mutex: " << test(foo_smtx, threads_count, iter_count, Set) << "ms\n";
        // ~ 5500 ms
    }

    {
        std::cout << "Both Job\n";

        FooMutex foo_mtx;
        std::cout << "Foo Mutex: " << test(foo_mtx, threads_count, iter_count, Both) << "ms\n";
        // ~ 3000 ms

        FooSharedMutex foo_smtx;
        std::cout << "Foo Shared Mutex: " << test(foo_smtx, threads_count, iter_count, Both) << "ms\n";
        // ~ 10000 ms
    }

    // вывод - shared_mutex полезен только в ситуациях, когда данные часто
    // читаются и редко обновляются, в остальных случаях он проигрывает mutex

    return 0;
}
