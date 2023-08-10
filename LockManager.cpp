#include <iostream>
#include <mutex>
#include <condition_variable>

class LockManager {
public:
    LockManager() : readers(0), writer(false) {}

    void acquireReadLock() {
        std::unique_lock<std::mutex> lock(mutex);
        while (writer) {
            cv.wait(lock);
        }
        readers++;
    }

    void releaseReadLock() {
        std::unique_lock<std::mutex> lock(mutex);
        readers--;
        if (readers == 0) {
            cv.notify_all();
        }
    }

    void acquireWriteLock() {
        std::unique_lock<std::mutex> lock(mutex);
        while (readers > 0 || writer) {
            cv.wait(lock);
        }
        writer = true;
    }

    void releaseWriteLock() {
        std::unique_lock<std::mutex> lock(mutex);
        writer = false;
        cv.notify_all();
    }

private:
    std::mutex mutex;
    std::condition_variable cv;
    int readers;
    bool writer;
};

int main() {
    // Simulating exclusive lock function
    auto exclusiveLock = [](std::function<void()> operation) {
        std::cout << "Acquiring exclusive lock..." << std::endl;
        // Simulate exclusive operation
        operation();
        std::cout << "Releasing exclusive lock..." << std::endl;
    };

    LockManager lockManager;

    // Acquiring read lock
    lockManager.acquireReadLock();
    exclusiveLock([]() {
        // Perform read operation
        std::cout << "Read operation" << std::endl;
    });
    lockManager.releaseReadLock();

    // Acquiring write lock
    lockManager.acquireWriteLock();
    exclusiveLock([]() {
        // Perform write operation
        std::cout << "Write operation" << std::endl;
    });
    lockManager.releaseWriteLock();

    return 0;
}
