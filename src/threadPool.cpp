#include "threadPool.h"

#include <QThread>

using std::thread;

ThreadPool::ThreadPool(QVector<QString>& queue, const QString &mp3Path,
                       bool (*fn)(const QString &, const QString &)) :
    m_queue(&queue),
    m_mp3Path(mp3Path),
    m_work_fn(fn)
{
    // int idealThreadCount = QThread::idealThreadCount();
    size_t threadCount = optimalThreadCount(static_cast<size_t> (queue.size()));

    m_tid.resize(threadCount);
    for (auto &thread: m_tid)
    {
        auto res = pthread_create(&thread, nullptr, ThreadFunction, this);
        switch (res)
        {
            case 0:
                break;
            case EAGAIN:
                throw std::runtime_error("Insufficient resources to create thread."); 
            case EINVAL:
                throw std::runtime_error("Invalid settings in attr.");
            case EPERM:
                throw std::runtime_error("Insufficitent permissions.");
            default:
                throw std::runtime_error("Unknown error creating thread.");
        }
    }
}

ThreadPool::~ThreadPool()
{
    for (auto thread: m_tid)
    {
        pthread_join(thread, nullptr);
    }
}

void* ThreadPool::ThreadFunction(void *arg)
{
    auto *ctx = (ThreadPool*)arg;

    while (1)
    {
        pthread_mutex_lock(&ctx->queue_mutex);
        if (ctx->m_queue->empty())
        {
            pthread_mutex_unlock(&ctx->queue_mutex);
            break;
        }

        QString cur(ctx->m_queue->back());
        ctx->m_queue->pop_back();
        pthread_mutex_unlock(&ctx->queue_mutex);
        if (ctx->m_work_fn(cur, ctx->m_mp3Path)) // Increase counter on success
            ctx->ItemsCompleted++;
    }
    return nullptr;
}

size_t ThreadPool::optimalThreadCount(size_t taskCount)
{
    //  Number of concurrent threads supported. If the value is not well defined or not computable, returns ​0​
    const size_t coreCount = thread::hardware_concurrency();
    size_t threadCount = std::min(taskCount, coreCount);

    // zero Check
    return (threadCount == 0) ? 1 : threadCount;
}











