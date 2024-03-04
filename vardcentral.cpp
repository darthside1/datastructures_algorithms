#include <iostream>
#include <queue>
#include <chrono>

class Customer {
    private:

    int m_queueNumber;
    std::string m_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_queueTime;

    public:

    Customer(int queueNumber, std::string name) {
        m_queueNumber = queueNumber;
        m_name = name;
        m_queueTime = std::chrono::high_resolution_clock::now();
    }

    ~Customer() {
        std::cout << m_name << " (queue number: " << m_queueNumber << ") left queue after " << 
        std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_queueTime).count() <<
        " seconds." << std::endl;
    }
};

void printMenu() {

    std::cout << "----------------------------------" << std::endl;
    std::cout << "VÅRDCENTRALEN QUEUE SYSTEM PREMIUM" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "1. Add customer to queue" << std::endl;
    std::cout << "2. Remove cutomer from queue" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void clearConsoleKindOf() {
    for (int i = 0; i < 30; i++) { std::cout << std::endl; }
}

int main() {

    std::queue<Customer> queue;
    int queueNumber = 0;
    std::string exampleName = "Sheldon";
    bool isRunning = true;
    int choice = 0;

    // Main loop
    while (isRunning)
    {
        clearConsoleKindOf();
        printMenu();
        std::cin >> choice;

        switch (choice)
        {
            case 1: // Enqueue
            {
                clearConsoleKindOf();
                Customer  newCustomer(queueNumber, exampleName);
                queue.push(newCustomer);
                queueNumber++;
                std::cout << "**Customer added successfully**" << std::endl;
                std::cout << "Press enter to continue.." << std::endl;
                std::cin.get();
                std::cin.get();
            }
            break;

            case 2: // Dequeue
            {
                clearConsoleKindOf();

                if (!queue.empty()) {
                    queue.pop();
                    std::cout << "Press enter to continue.." << std::endl;
                    std::cin.get();
                    std::cin.get();
                } else {
                    std::cout << "**The queue is empty**" << std::endl;
                    std::cout << "Press enter to continue.." << std::endl;
                    std::cin.get();
                    std::cin.get();
                }
            }
            break;

            case 3:
            {
                clearConsoleKindOf();
                std::cout << "Exiting.." << std::endl;
                isRunning = false;
            }
            break;
            
            default:
            {
                clearConsoleKindOf();
                std::cout << "Invalid input.. Try again" << std::endl;
            }
            break;
        }
    }
    
    
}