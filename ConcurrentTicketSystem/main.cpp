#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>
#include <SFML/Graphics.hpp>
#include <string>

static const int N = 15;
std::atomic_int turn[N] = { 0, 0, 0, 0, 0,0, 0, 0, 0, 0,0, 0, 0, 0, 0 };
std::atomic_int num = 1;
std::atomic_int next = 1;
int threadCount = 0;
sf::Vector2f playerPosition(42, 42);


void ticket() {
	static std::mutex mutex;

	int i = threadCount++;
	mutex.lock();
	std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
	mutex.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(1));

	while (1) {
		turn[i] = num.fetch_add(1);
		mutex.lock();
		std::cout << "Thread ID: " << std::this_thread::get_id() << " takes ticket, turn order: " << turn[i] << std::endl;
		mutex.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		while (turn[i] != next) {
			continue;
		}
		mutex.lock();
		std::cout << "Thread ID: " << std::this_thread::get_id() << "'s Critical Section, turn order: " << turn[i] << std::endl;
		mutex.unlock();
		std::string data = "Player position: " + std::to_string(playerPosition.x) + ", " + std::to_string(playerPosition.y);
		next += 1;
		mutex.lock();
		std::cout << data << " for Thread ID:" << std::this_thread::get_id() << ", next: " << next << std::endl;
		mutex.unlock();
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