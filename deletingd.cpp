#include <iostream>
#include <cstdlib>

void operator delete(void* p) {

    printf("Global Del of %p\n", p);
    free(p);
}
class Widget {public: virtual ~Widget() = default;};
class SuperWidget : public Widget {
public:

    void operator delete(void* p) {
        printf("SW Del of %p\n", p);
        ::operator delete(p);

    }
    ~SuperWidget() {printf("SW destructor\n");}
    std::string name = "A long heap based string"; // "short";

};

int main() {

    {

        auto stack_SW = SuperWidget{};

        printf("Addr of stack_SW %p\n", &stack_SW);

    } // SuperWidget goes out of scope, D1 (non-deleting) destructor called.

    Widget* w_ptr = new SuperWidget{};

    printf("Addr of SW %p\n", w_ptr);

    delete w_ptr;

    // delete called on SuperWidget. D0 (deleting) destructor called.

    // NOT followed by call to delete.

}
