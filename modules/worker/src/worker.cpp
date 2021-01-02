#include <worker.hpp>

namespace l1_memory_cache{
        Worker::Worker(const Callback& callback, const std::chrono::milliseconds& period): 
            callback_(callback),
            period_(period),
            is_running_(false){}

        void Worker::Run(){
            is_running_.store(true);
            future_ = std::async(
            std::launch::async,
            [this](){
                while(is_running_){
                    callback_();
                    std::this_thread::sleep_for(period_);
                }
            });
        }

        void Worker::Stop(){
            if(future_.valid()){
                is_running_.store(false);
                future_.wait();
            }
        }

        Worker::~Worker(){
            Stop();
        }
}