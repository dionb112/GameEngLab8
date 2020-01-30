#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

std::mutex mutex;
std::atomic_int _turn[];

void ticket() {
	mutex.lock();
	std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
	mutex.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(1));

	while (1) {

	}

}

int main() {
	std::thread x = std::thread(ticket);
	std::thread y = std::thread(ticket);
	std::thread z = std::thread(ticket);
	std::thread a = std::thread(ticket);
	x.join();
	y.join();
	z.join();
	a.join();

	return 0;
}