#pragma once

#include <QString>
#include <QVector>

#include <thread>
#include <iostream>

class ThreadPool
{
public:
    ThreadPool(QVector<QString>& m_queue, const QString &mp3Path,
               bool (*fn)(const QString &, const QString &));
    ThreadPool() = delete;
    ~ThreadPool();

private:
    static void* ThreadFunction(void *arg);
    size_t optimalThreadCount(size_t taskCount);

private:
    QVector<pthread_t> m_tid;
    QVector<QString> *m_queue;
    QString m_mp3Path;
    bool (*m_work_fn)(const QString &, const QString &);

    size_t ItemsCompleted = 0;
    pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
};

