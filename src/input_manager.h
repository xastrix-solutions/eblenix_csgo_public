#pragma once

#include <windows.h>
#include <functional>
#include <string>

enum m_state {
	state_none = 1,
	state_down,
	state_up,
	state_pressed,
};

struct mouse_t {
	friend struct input_manager;

	int get_mouse_pos_x() {
		return m_mouse_pos_x;
	}

	int get_mouse_pos_y() {
		return m_mouse_pos_y;
	}

	int get_mouse_wheel_accumlate() {
		return m_wheel_accumulate;
	}

	bool move_object(UINT m, int w, int h, int& x, int& y) {
		static int m_drag_offset_x{};
		static int m_drag_offset_y{};

		static bool m_dragging{};

		switch (m) {
		case WM_LBUTTONDOWN: {
			if (m_mouse_pos_x >= x && m_mouse_pos_x <= x + w &&
				m_mouse_pos_y >= y && m_mouse_pos_y <= y + h) {
				m_dragging = true;
				m_drag_offset_x = m_mouse_pos_x - x;
				m_drag_offset_y = m_mouse_pos_y - y;
			}
			break;
		}
		case WM_MOUSEMOVE: {
			if (m_dragging) {
				x = m_mouse_pos_x - m_drag_offset_x;
				y = m_mouse_pos_y - m_drag_offset_y;
			}
			break;
		}
		case WM_LBUTTONUP: {
			m_dragging = false;
			break;
		}
		}

		return m_dragging;
	}

private:
	int m_mouse_pos_x{};
	int m_mouse_pos_y{};
	int m_wheel_accumulate{};
};

struct input_manager : public mouse_t {
	void init(const std::pair<LPCSTR, LPCSTR>& wnd);
	void add_hk(unsigned int vk, std::function<void()> fn);

	WNDPROC get_wnd_proc();

	void process_message(UINT m, WPARAM w, LPARAM l);
	void process_mouse_message(UINT m, WPARAM w, LPARAM l);
	void process_keybd_message(UINT m, WPARAM w);

	std::wstring virtual_key_to_wstring(unsigned int vk);
	m_state get_key_state(unsigned int vk);

	void undo();
private:
	HWND                  m_hwnd{};
	WNDPROC               m_old_wnd_proc{};
	m_state               m_key_map[256]{};
	std::function<void()> m_hotkeys[256]{};
};

inline input_manager g_input;