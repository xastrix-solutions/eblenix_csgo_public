#pragma once

#include <string>
#include <vector>
#include <functional>

#include "render_manager.h"
#include "sprite_manager.h"

enum _ui_states {
	UI_NONE_STATE,
	UI_BOOL_STATE,
	UI_INT_STATE,
	UI_FLOAT_STATE,
	UI_FUNCTION_STATE,
	UI_ITEM_STATE,
	UI_KEY_STATE,
	UI_TAB_STATE,
};

enum _ui_subs {
	UI_SUB_POS,
	UI_SUB_SUB_POS,
	UI_SUB_SUB_SUB_POS,
	maxUISubs,
};

enum _ui_colors {
	UI_MAIN_COL,
	UI_PRIMARY_COL,
	UI_SHADOW_COL,
	UI_TEXT_COL,
	maxUIColors,
};

enum _ui_sprites {
	UI_SPRITE_LOGO,
	maxUISprites,
};

struct m_entry
{
	std::wstring m_name{};
	bool m_space{};
};

struct s_entry
{
	std::wstring m_name{};
	std::string m_var{};

	float m_float_step{},
		  m_float_min{},
		  m_float_max{};

	int m_int_step{},
		m_int_min{},
		m_int_max{};

	bool m_space{},
		 m_key_hold{};

	_ui_states m_state{};

	std::function<void()> m_fn{};
	std::vector<std::wstring> m_items{};
};

struct ui {
	void init(IDirect3DDevice9* device);
	void run();

	void on_reset_sprites();
	void on_reset_end_sprites();

	void handle_toggle_keys(unsigned int k);
	void handle_input(unsigned int k);

	bool get_menu_state() { return m_opened; }
	void set_menu_state(bool v) { m_opened = v; }

private:
	void calc_animation_progress(float anim_time, float delta_time, float& old_alpha);
	void draw(int x, int y);
	void setup();

	void add(const std::wstring& name, std::function<void()> fn, bool space = false);
	void add_bool(const std::wstring& name, const std::string& var, bool space = false);
	void add_int(const std::wstring& name, const std::string& var, int min, int max, int step, bool space = false);
	void add_float(const std::wstring& name, const std::string& var, float min, float max, float step, bool space = false);
	void add_item(const std::wstring& name, const std::string& var, std::vector<std::wstring> items, bool space = false);
	void add_key(const std::wstring& name, const std::string& var, bool space = false);
	void add_function(const std::wstring& name, std::function<void()> fn, bool space = false);
	void add_tab(const std::wstring& name, std::function<void()> fn, bool space = false);
	void add_sub_bool(const std::wstring& name, const std::string& var, bool space = false);
	void add_sub_int(const std::wstring& name, const std::string& var, int min, int max, int step, bool space = false);
	void add_sub_float(const std::wstring& name, const std::string& var, float min, float max, float step, bool space = false);
	void add_sub_item(const std::wstring& name, const std::string& var, std::vector<std::wstring> items, bool space = false);
	void add_sub_key(const std::wstring& name, const std::string& var, bool space = false);
	void add_sub_function(const std::wstring& name, std::function<void()> fn, bool space = false);
	void add_sub_tab(const std::wstring& name, std::function<void()> fn, bool space = false);
	void add_sub_sub_bool(const std::wstring& name, const std::string& var, bool space = false);
	void add_sub_sub_int(const std::wstring& name, const std::string& var, int min, int max, int step, bool space = false);
	void add_sub_sub_float(const std::wstring& name, const std::string& var, float min, float max, float step, bool space = false);
	void add_sub_sub_item(const std::wstring& name, const std::string& var, std::vector<std::wstring> items, bool space = false);
	void add_sub_sub_key(const std::wstring& name, const std::string& var, bool space = false);
	void add_sub_sub_function(const std::wstring& name, std::function<void()> fn, bool space = false);
	void clear();

private:
	bool m_opened{},
	     s_opened[maxUISubs]{};

	int m_entry_position{},
	    m_entry_size{},
		s_entry_position{},
		s_entry_size{},
		ss_entry_position{},
		ss_entry_size{},
		sss_entry_position{},
		sss_entry_size{};

	float current_animation_progress{},
		  target_animation_progress{};

	m_entry menu_entry[10]{};
	s_entry subm_entry[16]{},
		    ssubm_entry[16]{},
		    sssubm_entry[16]{};

	color_t m_colors[maxUIColors]{};
	sprite_t m_sprites[maxUISprites]{};

	std::vector<std::wstring> cfg_list{ L"1", L"2", L"3", L"4", L"5" };
};

inline ui g_ui;