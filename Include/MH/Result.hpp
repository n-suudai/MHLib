
#pragma once


#include "MH/OS/Types.hpp"
#include "MH/External/fmt.hpp"


#define MH_MAKE_RESULT(isSucceeded, ...)    MH::MakeResult(isSucceeded, #isSucceeded, __FILE__, static_cast<MH::u64>(__LINE__), __FUNCTION__, ##__VA_ARGS__)


namespace MH {


class Result
{
public:
    inline Result(bool isSucceeded = false)
        : m_isSucceeded(isSucceeded)
        , m_text(m_isSucceeded ? "Succeeded" : "Failed")
    {}

    inline Result(bool isSucceeded, const std::string& text)
        : m_isSucceeded(isSucceeded)
        , m_text(text)
    {}

    inline ~Result() = default;

    inline bool IsSucceeded() const { return m_isSucceeded; }

    inline bool IsFailed() const { return !m_isSucceeded; }

    inline const std::string& GetText() const { return m_text; }

    inline operator bool() const { return IsSucceeded(); }

private:
    bool        m_isSucceeded;
    std::string m_text;
};


inline Result MakeResult(
    bool        isSucceeded,
    const char* pExpression,
    const char* pFile,
    u64         line,
    const char* pFunction
)
{
    std::string text = "Succeeded";
    if (!isSucceeded)
    {
        text = fmt::format(
            "[{0}]\n"
            "is Failed.\n"
            "{1}({2}) : {3}",
            pExpression,
            pFile, line, pFunction
        );
    }
    return Result(isSucceeded, text);
}


template<class ... Args>
inline Result MakeResult(
    bool        isSucceeded,
    const char* pExpression,
    const char* pFile,
    u64         line,
    const char* pFunction,
    const char* pFormat,
    const Args& ... args
)
{
    std::string text = "Succeeded";
    if (!isSucceeded)
    {
        text = fmt::format(pFormat, args ...);
        text = fmt::format(
            "[{0}]\n"
            "is Failed.\n"
            "{1}({2}) : {3}"
            "{4}",
            pExpression,
            pFile, line, pFunction,
            text
        );
    }
    return Result(isSucceeded, text);
}


} // namespace MH

