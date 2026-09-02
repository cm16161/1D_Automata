#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

constexpr size_t ARR_SIZE = 74;

using namespace std;

class Engine {
	public:

	Engine() : m_back(ARR_SIZE, false), m_front(ARR_SIZE, false) {}
	//~Engine() = default;
	void set(ssize_t idx){
		if(idx < 0){
			idx = ARR_SIZE - (idx % ARR_SIZE);
		}
		if(idx > ARR_SIZE){
			idx = idx % ARR_SIZE;
		}

		m_back[idx] = true;
	}
	void uset(ssize_t idx){
		if(idx < 0){
			idx = ARR_SIZE - (idx % ARR_SIZE);
		}
		if(idx > ARR_SIZE){
			idx = idx % ARR_SIZE;
		}

		m_back[idx] = false;
	}

	void process(){
		for(int i = 0; i < ARR_SIZE; i++){
			m_front[i] = isAlive(m_back[i]);
		}
	}

	void print(){
		for(auto i : m_front){
			cout << i;
		}
		cout << endl;
		swap(m_front, m_back);
	}

	private:

	bool isAlive(ssize_t idx){
		int l = (idx - 1) < 0 ? ARR_SIZE-1 : idx-1;
		int r = (idx + 1) % ARR_SIZE;
		return true;
	}

	vector<bool> m_back;
	vector<bool> m_front;

};

int main(){
	std::cout << "\033[2J\033[1;1H";

	Engine e;
	e.set(ARR_SIZE/2);
	while(true){
		e.process();
		e.print();
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	return 0;
}