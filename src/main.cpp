#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <functional>
#include <string>

constexpr size_t ARR_SIZE = 89;

using namespace std;

const string WHITE = "\033[37m";
const string GREEN = "\033[32m";

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

	Engine& process(){
		for(int i = 0; i < ARR_SIZE; i++){
			m_front[i] =
				//C_Rule1(i);
				WR_Rule90(i);

		}
		return *this;
	}

	void print(){
		for(auto i : m_front){
			if(i){
				cout << GREEN << i;
			}
			else{
				cout << WHITE << i;
			}
		}
		cout << endl;
		swap(m_front, m_back);
	}

	private:

	// wrap
	bool C_Rule1(ssize_t idx){
		ssize_t l = (idx - 1) < 0 ? ARR_SIZE-1 : idx-1;
		idx = idx % ARR_SIZE;
		ssize_t r = (idx + 1) % ARR_SIZE;
		return m_back[l] && m_back[idx] || m_back[idx] || m_back[r];
	}

	bool WR_Rule30(ssize_t idx){
		ssize_t l = (idx - 1) < 0 ? ARR_SIZE-1 : idx-1;
		idx = idx % ARR_SIZE;
		ssize_t r = (idx + 1) % ARR_SIZE;
		return m_back[l] ^ (m_back[idx] || m_back[r]);
	}
	bool WR_Rule90(ssize_t idx){
		ssize_t l = (idx - 1) < 0 ? ARR_SIZE-1 : idx-1;
		idx = idx % ARR_SIZE;
		ssize_t r = (idx + 1) % ARR_SIZE;
		return m_back[l] ^ m_back[r];
	}


	// TODO: reflection (rather than wrap)
	//bool isAlive(ssize_t idx){
	//	int l = (idx - 1) < 0 ? ARR_SIZE-1 : idx-1;
	//	int r = (idx + 1) % ARR_SIZE;
	//	return true;
	//}

	vector<bool> m_back;
	vector<bool> m_front;


};

int main(){
	std::cout << "\033[2J\033[1;1H";

	Engine e;
	ssize_t middle = ARR_SIZE/2;
	//e.set(middle-1);
	e.set(middle);
	//e.set(middle+1);
	while(true){
		e.process().print();
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	return 0;
}