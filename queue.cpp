#include <iostream>

template <typename T, int N>
class Queue {

    private:
    T m_array[N];
    int m_index = 0;

    public:

    bool isFull() { return m_index >= N; }

    void enqueue(T data) {

        if (isFull()) 
        {
            std::cout << "**The queue is full**" << std::endl;
        } 
        else 
        {
            m_array[m_index] = data;
            m_index++;
        }
    }

};

int main() {

    Queue<int, 10> numberQueue;
    
    // Intentional overflow of queue
    for (int i = 0; i < 11; i++)
    {
        numberQueue.enqueue(i * 2);
    }
    

    
}