#include <cstring>
#include <iostream>
#include <utility>

class DynamicString {
public:
    DynamicString() 
    : m_data{nullptr}
    , m_size{0} {}

    explicit DynamicString(const char *str) 
    : DynamicString{} {
        if (str == nullptr)
            return;
        // First need to check the length of the [str]
        size_t length = std::strlen(str);
        if (!length)
            return;
        // Now we need to allocate memory for the [length] symbols
        m_data = new char[length + 1]; // one more symbol for the zero-termination
        // And now we can copy all symbols from the [str] to the our memory;
        for (size_t i = 0; i < length; ++i) {
            m_data[i] = str[i];
        }
        // Add one more symbol for the zero-termination
        m_data[length] = '\0';
        // Set a correct [m_size] value
        m_size = length;
    }

    DynamicString(const DynamicString &other)
    : DynamicString{other.data()} {}

    void swap(DynamicString& other) {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
    }

    DynamicString& operator= (const DynamicString& other) {
        DynamicString tmp(other); // copy ctor
        swap(tmp);
        return *this;
    }

    ~DynamicString() {
        delete[] m_data;
    }

    size_t size() const { return m_size; }
    char *data() const { return m_data; }

private:
    char *m_data;
    size_t m_size;
};

void example() {
    {
        std::cout << "Basic usage: " << std::endl;
        DynamicString str{"Hello!"};
        std::cout << str.size() << std::endl;
        std::cout << str.data() << std::endl;
    }

    {
        std::cout << "New/delete usage: " << std::endl;
        const DynamicString *str = new DynamicString{"Hello!"};
        std::cout << str->size() << std::endl;
        std::cout << str->data() << std::endl;
        
        // If created with new - has to be deleted manually by delete:
        delete str;
        str = nullptr;

        // Delete checks if str is nullptr, so no additional checks required!
        delete str;
        std::cout << "I'm still alive!" << std::endl;
        
        DynamicString str1{"test1"};
        DynamicString str2{"test2"};
        str1 = str2;
    }
}

int main() {
    example();
    return 0;
}
