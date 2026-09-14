#pragma once
#include "types.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

/**
 * Network worker thread.
 *
 * The UI thread enqueues NetTask objects; the worker processes them
 * sequentially and writes results into SharedState under its mutex.
 */
class NetworkWorker {
public:
    explicit NetworkWorker(SharedState& state);
    ~NetworkWorker();

    // Non-copyable
    NetworkWorker(const NetworkWorker&)            = delete;
    NetworkWorker& operator=(const NetworkWorker&) = delete;

    /**
     * Enqueue a task for the worker to execute.
     * Thread-safe – may be called from the UI thread.
     */
    void enqueue(NetTask task);

    /** Gracefully stop the worker thread. */
    void stop();

private:
    void run();            // runs in the worker thread
    void handle(const NetTask& task);

    SharedState&                  state_;
    std::queue<NetTask>           queue_;
    std::mutex                    q_mtx_;
    std::condition_variable       q_cv_;
    std::atomic<bool>             running_{true};
    std::thread                   thread_;
};
