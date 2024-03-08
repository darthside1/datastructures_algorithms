#include <iostream>

#define RESET_COLOR "\033[0m"
#define GREEN_TEXT "\033[32m"

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

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
            std::cout << GREEN_TEXT << "The queue is full" << RESET_COLOR << std::endl; 
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

            m_array[++m_end] = value;
        }
        std::cout << GREEN_TEXT << "'" << value << "' was added to the queue" << RESET_COLOR << std::endl;
    }

    const T& dequeue() {

        static T x = T();
        if (isEmpty())
        {
            std::cout << GREEN_TEXT << "The queue is empty" << RESET_COLOR << std::endl;
            return x;
        }
        else if (m_end == m_front)
        {
            std::cout << GREEN_TEXT << "'" << m_array[m_front] << "' was removed from the front of the queue. The queue is now empty" << RESET_COLOR << std::endl;
            x = m_array[m_end];
            m_front = -1;
            m_end = -1;
            return x;
        }
        else
        {
            std::cout << GREEN_TEXT << "'" << m_array[m_front] << "' was removed from the front of the queue" << RESET_COLOR << std::endl;
            x = m_array[m_front];
            m_array[m_front] = T();
            m_front++;
            return x;
        }
    }

    int getSize() const {

        if (isEmpty()) { return 0; }
        
        int count = 0;
        for (int i = m_front; i <= m_end; ++i) { ++count; }
        return count;
    }

    void display() const {

        if (isEmpty())
        {
            std::cout << GREEN_TEXT << "The queue is empty" << RESET_COLOR << std::endl;
        }
        else {
            std::cout << "The queue contains:" << std::endl;
            std::cout << std::endl;
            for (int i = 0; i < N; i++) {
                if (m_array[i] == T()) { continue; }
                else { std::cout << "■ " << m_array[i] << std::endl; }
            }
            std::cout << std::endl;
            std::cout << "Press enter to return to menu.." << std::endl;
            std::cin.get();
            std::cin.get();
            system(CLEAR);
        }
    }

};

void displayMenu() {
        std::cout << std::endl;
        std::cout << "********************" << std::endl;
        std::cout << "Queue Data Structure" << std::endl;
        std::cout << "********************" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Add a name to the queue" << std::endl;
        std::cout << "2. Remove a name from the queue" << std::endl;
        std::cout << "3. Check if the queue is empty" << std::endl;
        std::cout << "4. Check if the queue is full" << std::endl;
        std::cout << "5. Display number of names in the queue" << std::endl;
        std::cout << "6. Display the queue" << std::endl;
        std::cout << "7. Exit" << std::endl;
}


int main() {

    Queue<std::string, 5> queue;
    std::string name;
    int menu;
    bool running = true;


    system(CLEAR);
    do
    {
        displayMenu();
        std::cin >> menu;

        switch (menu)
        {
        case 1:
            system(CLEAR);
            std::cout << "Enter name to add to queue:  " << std::endl;
            std::cin >> name;
            system(CLEAR);
            queue.enqueue(name);
            break;
        case 2:
            system(CLEAR);
            queue.dequeue();
            break;
        case 3:
            system(CLEAR);
            queue.isEmpty() ? 
            std::cout << GREEN_TEXT << "The queue is empty" << RESET_COLOR << std::endl : 
            std::cout << GREEN_TEXT << "The queue is not empty" << RESET_COLOR << std::endl;
            break;
        case 4:
            system(CLEAR);
            queue.isFull() ? 
            std::cout << GREEN_TEXT << "The queue is full" << RESET_COLOR << std::endl : 
            std::cout << GREEN_TEXT << "The queue is not full" << RESET_COLOR << std::endl;
            break;
        case 5:
            system(CLEAR);
            queue.getSize() == 1 ? 
            std::cout << GREEN_TEXT << "The queue currently has " << queue.getSize() << " name in it" << RESET_COLOR << std::endl :
            std::cout << GREEN_TEXT << "The queue currently has " << queue.getSize() << " names in it" << RESET_COLOR << std::endl;
            break;
        case 6:
            system(CLEAR);
            queue.display();
            break;
        case 7:
            system(CLEAR);
            std::cout << "Exiting program.. " << std::endl;
            std::cout << std::endl;
            running = false;
            break;
        default:
            std::cout << "Invalid input, try again.." << std::endl;
            break;
        }

    } while (running);
    
    return 0;
}