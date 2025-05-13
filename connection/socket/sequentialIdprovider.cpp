#include "sequentialIdprovider.h"

SequentialIdProvider SequentialIdProvider::singleton;

SequentialIdProvider &SequentialIdProvider::get()
{
    return singleton;
}

std::atomic<long long> SequentialIdProvider::next()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return cur++;
}
