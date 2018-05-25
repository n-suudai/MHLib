
#pragma once


#include "MH/OS/Types.hpp"
#include "MH/Result.hpp"
#include <locale>
#include <vector>
#include <fstream>
#include <iterator>


namespace MH {
namespace Utility {


// ロケールを規定値に設定します
inline void InitializeLocale()
{
    setlocale(LC_CTYPE, "");
}


// ワイド文字列からマルチバイト文字列を返す
inline std::string Narrow(const std::wstring &src)
{
    size_t bufSize = src.length() * MB_CUR_MAX + 1;
    char *mbs = new char[bufSize];
    size_t size;
    wcstombs_s(&size, mbs, bufSize, src.c_str(), bufSize);
    std::string dest = mbs;
    delete[] mbs;
    return dest;
}


// マルチバイト文字列からワイド文字列を返す
inline std::wstring Widen(const std::string &src)
{
    size_t bufSize = src.length() + 1;
    wchar_t *wcs = new wchar_t[bufSize];
    size_t size;
    mbstowcs_s(&size, wcs, bufSize, src.c_str(), bufSize);
    std::wstring dest = wcs;
    delete[] wcs;
    return dest;
}


// ファイルの読み込み（バイナリ）
inline Result ReadFile(const std::string& fileName, std::vector<u8>& out)
{
    out.clear();

    std::ifstream file(fileName, std::ios::binary);


    Result result = Result(!file.fail(), "Open " + fileName + " is failed");

    if (result.IsFailed())
    {
        return result;
    }

    file.unsetf(std::ios::skipws);

    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    out.reserve(static_cast<size_t>(fileSize));

    out.insert(
        out.begin(),
        std::istream_iterator<u8>(file),
        std::istream_iterator<u8>()
    );

    return Result(true);
}


} // namespace Utility
} // namespace MH

