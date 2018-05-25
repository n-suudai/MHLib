
#pragma once


#include <string>


namespace MH {


class Result
{
public:
    inline Result(bool result = false)
        : m_result(result)
        , m_text(result ? "Succeeded" : "Failed")
    {}

    inline Result(bool result, std::string const& text)
        : m_result(result)
        , m_text(result ? "Succeeded" : text)
    {}

    inline ~Result() = default;

    inline bool IsSucceeded() const { return m_result; }

    inline bool IsFailed() const { return !m_result; }

    inline std::string const& GetText() const { return m_text; }

private:
    bool        m_result;
    std::string m_text;
};


} // namespace MH

