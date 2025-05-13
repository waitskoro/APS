#pragma once

#include<atomic>
#include<mutex>

class SequentialIdProvider
{
    static SequentialIdProvider singleton;
    SequentialIdProvider() : cur{ 0 } {
    }

    std::atomic<long long> cur;
    std::mutex m_mutex;
public:
    SequentialIdProvider(const SequentialIdProvider&)
        = delete;
    SequentialIdProvider&
    operator=(const SequentialIdProvider&) = delete;

    static SequentialIdProvider& get();
    std::atomic<long long> next();
};
