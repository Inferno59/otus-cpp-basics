#include <iostream>

////////////////////////////////////////////////////////////////////////////////

namespace conversion {
    enum class ResultCode {
        Ok,
        Failed,
        NotFound,
        OutOfMemory,
        NotImplemented
    };

    class Result {
    public:
        Result() : m_code{ResultCode::Ok} {}

        explicit Result(ResultCode code) : m_code{code} {}

        ResultCode getResult() const { return m_code; }

        bool isError() const { return m_code != ResultCode::Ok; }

        explicit 
        operator bool() const { return isError(); }

        bool toBool() const { return isError(); }

    private:
        const ResultCode m_code;
    };

    //! The function which does something, but could return an error on failure.
    Result doSomeImportantTask() {
        Result result{ResultCode::Ok};

        /* ... */

        return result;
    }

    void example() {
        const Result result = doSomeImportantTask();

        // Calling the method to see - is it an error?
        if (result.isError()) {
            std::cout << "We have error!" << std::endl;
        } else {
            std::cout << "Everything is good!" << std::endl;
        }

        // Call the Result::operator bool here
        if (result) {
            std::cout << "We have error!" << std::endl;
        } else {
            std::cout << "Everything is good!" << std::endl;
        }

        // Use direct func
        if (result.toBool()) {
            std::cout << "We have error!" << std::endl;
        } else {
            std::cout << "Everything is good!" << std::endl;
        }

        bool res = static_cast<bool>(result);
//      float fVal = result;
    }
} // namespace conversion

////////////////////////////////////////////////////////////////////////////////

int main() {
    conversion::example();
    return 0;
}

/*
Describes a method of creating another type from this type - like "convert".

Good for general cases, such as checking for success, but in specific cases,
it could confuse readers.

Could be explicitly to don't allow implicit conversations.
*/