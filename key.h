#ifndef KEY_H
#define KEY_H

#include "events.h"

namespace cogui {

class key
{
public:

    // Standard letter keys
    static cogui::key A;
    static cogui::key B;
    static cogui::key C;
    static cogui::key D;
    static cogui::key E;
    static cogui::key F;
    static cogui::key G;
    static cogui::key H;
    static cogui::key I;
    static cogui::key J;
    static cogui::key K;
    static cogui::key L;
    static cogui::key M;
    static cogui::key N;
    static cogui::key O;
    static cogui::key P;
    static cogui::key Q;
    static cogui::key R;
    static cogui::key S;
    static cogui::key T;
    static cogui::key U;
    static cogui::key V;
    static cogui::key W;
    static cogui::key X;
    static cogui::key Y;
    static cogui::key Z;

    // Numbers
    static cogui::key Number_1;
    static cogui::key Number_2;
    static cogui::key Number_3;
    static cogui::key Number_4;
    static cogui::key Number_5;
    static cogui::key Number_6;
    static cogui::key Number_7;
    static cogui::key Number_8;
    static cogui::key Number_9;
    static cogui::key Number_0;

    // punctuation keys
    static cogui::key Comma;                        // The , key
    static cogui::key FullStop;                     // The . key
    static cogui::key Slash;                        // The / key
    static cogui::key Semicolon;                    // The ; key
    static cogui::key Apostrophe;                   // The ' key
    static cogui::key OpeningSquareBracket;         // The [ key
    static cogui::key ClosingSquareBracket;         // The ] key
    static cogui::key Backslash;                    // The \ key
    static cogui::key Equal;                        // The = key
    static cogui::key Minus;                        // The - key
    static cogui::key Grave;                        // the ` key

    // function keys
    static cogui::key F1;
    static cogui::key F2;
    static cogui::key F3;
    static cogui::key F4;
    static cogui::key F5;
    static cogui::key F6;
    static cogui::key F7;
    static cogui::key F8;
    static cogui::key F9;
    static cogui::key F10;
    static cogui::key F11;
    static cogui::key F12;

    // Escape
    static cogui::key Escape;

    // Arrow keys
    static cogui::key Up;
    static cogui::key Down;
    static cogui::key Left;
    static cogui::key Right;

    // Jumping keys
    static cogui::key Home;
    static cogui::key End;
    static cogui::key PgUp;
    static cogui::key PgDn;

    // typing keys
    static cogui::key Insert;
    static cogui::key Delete;
    static cogui::key Space;
    static cogui::key Enter;

    // modifier keys
    static cogui::key Alt;
    static cogui::key Ctrl;
    static cogui::key Shift;

    // used to kreate hotkeys
    key operator + (const key& other);

    key(const events::keypress& generator);
    key() = default;

    std::wstring get_character() const
    {
        return m_generator.get_chardata();
    }

private:
    events::keypress m_generator;
};

}

#endif // KEY_H
