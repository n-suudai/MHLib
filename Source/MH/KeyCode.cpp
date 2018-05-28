#include "MH/KeyCode.hpp"
#include "MH/OS/Types.hpp"


namespace MH {


static const std::string strKeyCodes[] = {
    "Unknown",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "Escape",
    "Return",
    "Space",
    "BackSpace",
    "Delete",
    "LControl",
    "LShift",
    "RControl",
    "RShift",
    "Up",
    "Down",
    "Left",
    "Right",
};


static const std::string strMouseButtons[] = {
    "Left",
    "Right",
    "Middle",
};


std::string KeyCodeToString(KEY_CODE key)
{
    return strKeyCodes[static_cast<u32>(key)];
}


std::string MouseButtonToString(MOUSE_BUTTON mouse)
{
    return strMouseButtons[static_cast<u32>(mouse)];
}


} // namespace MH

