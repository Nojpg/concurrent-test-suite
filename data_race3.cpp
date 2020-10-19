std::string data;
std::atomic<bool> ready{ false };

void thread1() {
    data = "very important bytes";
    ready.store(true, std::memory_order_relaxed);
}

void thread2() {
    while(!ready.load(std::memory_order_relaxed));
    std::cout << "data is ready" << data << "\n"; //potential mem corrupt
}
