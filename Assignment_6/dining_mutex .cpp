#include <bits/stdc++.h>
#include <mutex>
#include <thread>

using namespace std;
const int N = 8;
    
class fork
{
    public:
		fork()
		{
			;
		}
		mutex mu;
};

void eat(fork &fork_left, fork& fork_right, int number) 
{
        
        fork_left.mu.lock();
        fork_right.mu.lock();
        cout << "Philosopher " << number << " is eating." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "\nPhilosopher " << number << " has finished eating." << endl;
        fork_right.mu.unlock();
        fork_left.mu.unlock();
}
    
int main()
{
    fork forks[N];
    thread philosopher[N];
    cout << "Philosopher " << 1 << " is thinking." << endl;
    philosopher[0] = thread(eat, ref(forks[0]), ref(forks[N-1]), 1);
    for(int i = 1; i < N; ++i) 
    {
        cout << "Philosopher " << (i+1) << " is thinking." << endl;
        philosopher[i] = thread(eat, ref(forks[i]), ref(forks[i-1]), (i+1));
    }
    
    for(auto &ph: philosopher) ph.join();
    return 0;
}
