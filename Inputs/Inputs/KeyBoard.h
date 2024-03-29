#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <array>
#include <Windows.h>

#pragma comment(lib, "User32.lib") // GetAsyncKeyState Function

#pragma warning( push )
#pragma warning(disable : 26812)   // disable warning of using enum

class Keyboard
{
public:
	enum Key
	{
		BACKSPACE = 0x08,
		TAB = 0x09,

		CLEAR = 0x0C,
		ENTER = 0x0D,

		SHIFT = 0x10,
		CTRL = 0x11,
		ALT = 0x12,
		PAUSE = 0x13,
		MAJ_LOCK = 0x14,

		ESCAPE = 0x1B,

		SPACE = 0x20,
		PAGE_UP = 0x21,
		PAGE_DOWN = 0x22,
		END = 0x23,
		HOME = 0x24,
		LEFT = 0x25,
		UP = 0x26,
		RIGHT = 0x27,
		DOWN = 0x28,
		SELECT = 0x29,
		PRINT = 0x2A,
		EXECUTE = 0x2B,
		SNAPSHOT = 0x2C,
		INSERT = 0x2D,
		DEL = 0x2E,

		_0 = 0x30,
		_1, _2, _3, _4, _5, _6, _7, _8, _9,

		A = 0x41,
		B, C, D, E, F, G, H, I, J, K, L, M, N,
		O, P, Q, R, S, T, U, V, W, X, Y, Z,

		PAD0 = 0x60,
		PAD1, PAD2, PAD3, PAD4, PAD5,
		PAD6, PAD7, PAD8, PAD9,

		MULTIPLY = 0x6A,
		ADD, SEPARATOR, SUBTRACT, DECIMAL, DIVIDE,

		F1 = 0x70,
		F2, F3, F4, F5, F6, F7, F8, F9, F10, F11,
		F12, F13, F14, F15, F16, F17, F18,
		F19, F20, F21, F22, F23, F24,

		NUMLOCK = 0x90,

		LSHIFT = 0xA0,
		RSHIFT = 0xA1,
		LCONTROL = 0xA2,
		RCONTROL = 0xA3,
		LMENU = 0xA4,
		RMENU = 0xA5
	};
private:
	static const int keyCount{ Keyboard::Key::RMENU + 1 };

	inline static std::array<std::pair<short, short>, keyCount> m_keys;	// previous, current
	inline static bool m_init{ false };

public:
	Keyboard() {
		if (!m_init) {
			this->eventUpdate();
			m_init = true;
		}
	}

	~Keyboard() = default;

	const void eventUpdate() {
		for (int i = BACKSPACE; i < this->keyCount; i++) {
			this->m_keys.at(i).first = m_keys.at(i).second;
			this->m_keys.at(i).second = GetAsyncKeyState(i);
		}
	}

	const bool on_pressed(Keyboard::Key k) const {
		return !(this->m_keys.at(k).first & 0x8000) && this->m_keys.at(k).second & 0x8000;
	}

	const bool is_pressed(Keyboard::Key k) const {
		return this->m_keys.at(k).second & 0x8000;
	}

	const bool on_release(Keyboard::Key k) const {
		return this->m_keys.at(k).first & 0x8000 && !(this->m_keys.at(k).second & 0x8000);
	}

	const bool is_released(Keyboard::Key k) const {
		return !(this->m_keys.at(k).second & 0x8000);
	}

	const bool text_pressed(Keyboard::Key k) const {
		return this->m_keys.at(k).second & 0x0001;
	}
};

#pragma warning( pop )
#endif // !KEYBOARD_H