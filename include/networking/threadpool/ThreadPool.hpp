#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector> // for std::vector 
#include <thread> // for std::thread
#include <functional> // for std::function 
#include <future> // for std::future
#include <queue> // for std::queue
#include <condition_variable> // for std::condition_variable
#include <iostream>
#include <memory>
#include <mutex> 
#include <type_traits> 
namespace HDE { 
    class ThreadPool {
    public:
        ThreadPool(size_t numThreads);
        ~ThreadPool();

        template<class F>
        auto enqueue(F&& f) -> std::future<typename std::invoke_result<F>::type> {
            using return_type = typename std::invoke_result<F>::type;

            auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));
            std::future<return_type> res = task->get_future();

            {
                std::unique_lock lock(queueMutex);
                tasks.emplace([task] { (*task)(); });
            }

            condition.notify_one();
            return res;
        }



    private:
        std::vector<std::thread> workers; // Worker threads 
        std::queue<std::function<void()>> tasks; // task queue

        std::mutex queueMutex; // mutex for task queue
        std::condition_variable condition; // condition variable for task synchronization 
        bool stop; // flag to indicate if the pool is stopping
    };
}
#endif // THREAD_POOL_HPP   