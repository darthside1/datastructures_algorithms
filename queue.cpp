#include <iostream>

template <typename T, int N>
class Queue {

    private:
    int m_front;
    int m_end;
    T m_array[N];

    public:
    Queue() {
        m_front = -1;
        m_end = -1;
    }

    bool isEmpty() const { return m_front == -1 && m_end == -1; }

    bool isFull() const { return m_end == N - 1;}

    void enqueue(const T& value) {

        if (isFull()) 
        { 
            std::cout << "* The queue is full *" << std::endl; 
            return; 
        }
        else if (isEmpty())
        {
            m_end = 0;
            m_front = 0;
            m_array[m_end] = value;
        }
        else
        {
            m_end++;
            m_array[m_end] = value;
            // Testa om detta funkar när koden är klar
            // m_array[++m_end] = value;
        }
    }

    const T& dequeue() {

        static T x = T();
        if (isEmpty())
        {
            std::cout << "* Queue is empty *" << std::endl;
            return x;
        }
        else if (m_end == m_front) // Only one element in array
        {
            x = m_array[m_end];
            m_front = -1;
            m_end = -1;
            return x;
        }
        else
        {
            std::cout << "Front value: " << m_front << std::endl;
            x = m_array[m_front];
            m_array[m_front] = T();
            m_front++;
            return x;
        }
    }

    int getSize() const { return N; }

    void display() const {

        std::cout << "The queue contains -> ";
        for (int i = 0; i < (sizeof(m_array / sizeof(T))); i++)
        {
            std::cout << "  [" << m_array[i] << "]  " << std::endl;
        }   
    }

};

int main() {

    Queue<std::string, 10> queue;
    std::cout << "Test" << std::endl;

}