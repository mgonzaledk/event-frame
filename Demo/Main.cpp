#include <iostream>
#include <chrono>
#include <thread>

#include <Event/BaseComponent.h>

enum Actions : Event::Type {
    A_STARTED = 0,
    B_STARTED,
    A_ENDED,
    B_ENDED
};

class AReceiver : public BaseComponent {
    public:
        AReceiver() :
            BaseComponent() {}
        
        void Init() {
            Subscribe(A_STARTED);
            Subscribe(A_ENDED);
        }

        void Run() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        void Process(Event *ev) {
            switch(ev->GetType()) {
                case Actions::A_STARTED: std::cout << "[AReceiver] A_STARTED" << std::endl; break;
                case Actions::A_ENDED: std::cout << "[AReceiver] A_ENDED" << std::endl; break;
            }
        }
};

class DemoController : public BaseComponent {
    private:
        bool AEnded, BEnded;

    public:
        DemoController() :
            BaseComponent(), AEnded(false), BEnded(false) {}

        void Init() {
            Subscribe(A_ENDED);
            Subscribe(B_ENDED);
        }

        void Run() {
            if(AEnded && BEnded) {
                Stop();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        void Process(Event *ev) {
            if(ev->GetType() == Actions::A_ENDED) {
                std::cout << "[*] A_ENDED" << std::endl;
                AEnded = true;
            }

            else if(ev->GetType() == Actions::B_ENDED) {
                std::cout << "[*] B_ENDED" << std::endl;
                BEnded = true;
            }
        }
};

int main(int argc, char **argv) {
    (void)argc, (void)argv;

    DemoController demo;
    demo.Start();

    AReceiver a;
    a.Start();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    BaseComponent::Publish(Event(A_STARTED));
    BaseComponent::Publish(Event(B_STARTED));
    BaseComponent::Publish(Event(A_ENDED));
    BaseComponent::Publish(Event(B_ENDED));

    demo.Wait();

    a.Stop();
    a.Wait();
    return 0;
}
