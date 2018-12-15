#include <iostream>
#include <chrono>
#include <thread>

#include <Event/BaseComponent.h>
#include <Thread/BaseStoppable.h>

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

        void Process() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        void Handler(Event *ev) {
            switch(ev->GetType()) {
                case Actions::A_STARTED: {
                    UserEvent<std::string> *msg = static_cast<UserEvent<std::string> *>(ev);
                    std::cout << "[A] START: " << msg->GetObject() << std::endl;
                } break;

                case Actions::A_ENDED: {
                    std::cout << "[A] END" << std::endl;
                } break;
            }
        }

        void End() {

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

        void Process() {
            if(AEnded && BEnded) {
                Stop();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        void Handler(Event *ev) {
            if(ev->GetType() == Actions::A_ENDED) {
                std::cout << "[*] A_ENDED" << std::endl;
                AEnded = true;
            }

            else if(ev->GetType() == Actions::B_ENDED) {
                std::cout << "[*] B_ENDED" << std::endl;
                BEnded = true;
            }
        }

        void End() {

        }
};

class Stoppable : public BaseStoppable {
    public:
        void Run() {
            BaseComponent::Publish(UserEvent<std::string>(A_STARTED, "Mensaje de inicio de A"));
            BaseComponent::Publish(Event(B_STARTED));

            while(!Stopping()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            BaseComponent::Publish(Event(A_ENDED));
            BaseComponent::Publish(Event(B_ENDED));   
        }
};

int main(int argc, char **argv) {
    (void)argc, (void)argv;

    DemoController demo;
    demo.Start();

    AReceiver a;
    a.Start();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    Stoppable stoppable;
    stoppable();
    stoppable.Stop();

    stoppable.Wait();
    demo.Wait();

    a.Stop();
    a.Wait();
    return 0;
}
