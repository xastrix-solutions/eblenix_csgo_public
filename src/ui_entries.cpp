#include "ui.h"

void ui::add(const std::wstring& name, std::function<void()> fn, bool space)
{
	menu_entry[m_entry_size].m_name = name;
	menu_entry[m_entry_size].m_space = space;

	if (m_entry_position == m_entry_size)
		fn();

	++m_entry_size;
}

void ui::add_bool(const std::wstring& name, const std::string& var, bool space)
{
	subm_entry[s_entry_size].m_name = name;
	subm_entry[s_entry_size].m_var = var;

	subm_entry[s_entry_size].m_state = UI_BOOL_STATE;

	subm_entry[s_entry_size].m_space = space;

	++s_entry_size;
}

void ui::add_int(const std::wstring& name, const std::string& var, int min, int max, int step, bool space)
{
	subm_entry[s_entry_size].m_name = name;
	subm_entry[s_entry_size].m_var = var;

	subm_entry[s_entry_size].m_int_min = min;
	subm_entry[s_entry_size].m_int_max = max;

	subm_entry[s_entry_size].m_int_step = step;

	subm_entry[s_entry_size].m_state = UI_INT_STATE;

	subm_entry[s_entry_size].m_space = space;

	++s_entry_size;
}

void ui::add_float(const std::wstring& name, const std::string& var, float min, float max, float step, bool space)
{
	subm_entry[s_entry_size].m_name = name;
	subm_entry[s_entry_size].m_var = var;

	subm_entry[s_entry_size].m_float_min = min;
	subm_entry[s_entry_size].m_float_max = max;

	subm_entry[s_entry_size].m_float_step = step;

	subm_entry[s_entry_size].m_state = UI_FLOAT_STATE;

	subm_entry[s_entry_size].m_space = space;

	++s_entry_size;
}

void ui::add_item(const std::wstring& name, const std::string& var, std::vector<std::wstring> items, bool space)
{
	subm_entry[s_entry_size].m_name = name;
	subm_entry[s_entry_size].m_var = var;

	subm_entry[s_entry_size].m_int_min = 0;
	subm_entry[s_entry_size].m_int_max = items.size() - 1;

	subm_entry[s_entry_size].m_int_step = 1;

	subm_entry[s_entry_size].m_state = UI_ITEM_STATE;
	subm_entry[s_entry_size].m_items = items;

	subm_entry[s_entry_size].m_space = space;

	++s_entry_size;
}

void ui::add_key(const std::wstring& name, const std::string& var, bool space)
{
	subm_entry[s_entry_size].m_name = name;
	subm_entry[s_entry_size].m_var = var;

	subm_entry[s_entry_size].m_state = UI_KEY_STATE;

	subm_entry[s_entry_size].m_space = space;

	++s_entry_size;
}

void ui::add_function(const std::wstring& name, std::function<void()> fn, bool space)
{
	subm_entry[s_entry_size].m_name = name;

	subm_entry[s_entry_size].m_state = UI_FUNCTION_STATE;
	subm_entry[s_entry_size].m_fn = fn;

	subm_entry[s_entry_size].m_space = space;

	++s_entry_size;
}

void ui::add_tab(const std::wstring& name, std::function<void()> fn, bool space)
{
	subm_entry[s_entry_size].m_name = name;

	subm_entry[s_entry_size].m_state = UI_TAB_STATE;

	subm_entry[s_entry_size].m_space = space;

	if (s_entry_position == s_entry_size)
		fn();

	++s_entry_size;
}

void ui::add_sub_bool(const std::wstring& name, const std::string& var, bool space)
{
	ssubm_entry[ss_entry_size].m_name = name;
	ssubm_entry[ss_entry_size].m_var = var;

	ssubm_entry[ss_entry_size].m_state = UI_BOOL_STATE;

	ssubm_entry[ss_entry_size].m_space = space;

	++ss_entry_size;
}

void ui::add_sub_int(const std::wstring& name, const std::string& var, int min, int max, int step, bool space)
{
	ssubm_entry[ss_entry_size].m_name = name;
	ssubm_entry[ss_entry_size].m_var = var;

	ssubm_entry[ss_entry_size].m_int_min = min;
	ssubm_entry[ss_entry_size].m_int_max = max;

	ssubm_entry[ss_entry_size].m_int_step = step;

	ssubm_entry[ss_entry_size].m_state = UI_INT_STATE;

	ssubm_entry[ss_entry_size].m_space = space;

	++ss_entry_size;
}

void ui::add_sub_float(const std::wstring& name, const std::string& var, float min, float max, float step, bool space)
{
	ssubm_entry[ss_entry_size].m_name = name;
	ssubm_entry[ss_entry_size].m_var = var;

	ssubm_entry[ss_entry_size].m_float_min = min;
	ssubm_entry[ss_entry_size].m_float_max = max;

	ssubm_entry[ss_entry_size].m_float_step = step;

	ssubm_entry[ss_entry_size].m_state = UI_FLOAT_STATE;

	ssubm_entry[ss_entry_size].m_space = space;

	++ss_entry_size;
}

void ui::add_sub_item(const std::wstring& name, const std::string& var, std::vector<std::wstring> items, bool space)
{
	ssubm_entry[ss_entry_size].m_name = name;
	ssubm_entry[ss_entry_size].m_var = var;

	ssubm_entry[ss_entry_size].m_int_min = 0;
	ssubm_entry[ss_entry_size].m_int_max = items.size() - 1;

	ssubm_entry[ss_entry_size].m_int_step = 1;

	ssubm_entry[ss_entry_size].m_state = UI_ITEM_STATE;
	ssubm_entry[ss_entry_size].m_items = items;

	ssubm_entry[ss_entry_size].m_space = space;

	++ss_entry_size;
}

void ui::add_sub_key(const std::wstring& name, const std::string& var, bool space)
{
	ssubm_entry[ss_entry_size].m_name = name;
	ssubm_entry[ss_entry_size].m_var = var;

	ssubm_entry[ss_entry_size].m_state = UI_KEY_STATE;

	ssubm_entry[ss_entry_size].m_space = space;

	++ss_entry_size;
}

void ui::add_sub_function(const std::wstring& name, std::function<void()> fn, bool space)
{
	ssubm_entry[ss_entry_size].m_name = name;

	ssubm_entry[ss_entry_size].m_state = UI_FUNCTION_STATE;
	ssubm_entry[ss_entry_size].m_fn = fn;

	ssubm_entry[ss_entry_size].m_space = space;

	++ss_entry_size;
}

void ui::add_sub_tab(const std::wstring& name, std::function<void()> fn, bool space)
{
	ssubm_entry[ss_entry_size].m_name = name;

	ssubm_entry[ss_entry_size].m_state = UI_TAB_STATE;

	ssubm_entry[ss_entry_size].m_space = space;

	if (ss_entry_position == ss_entry_size)
		fn();

	++ss_entry_size;
}

void ui::add_sub_sub_bool(const std::wstring& name, const std::string& var, bool space)
{
	sssubm_entry[sss_entry_size].m_name = name;
	sssubm_entry[sss_entry_size].m_var = var;

	sssubm_entry[sss_entry_size].m_state = UI_BOOL_STATE;

	sssubm_entry[sss_entry_size].m_space = space;

	++sss_entry_size;
}

void ui::add_sub_sub_int(const std::wstring& name, const std::string& var, int min, int max, int step, bool space)
{
	sssubm_entry[sss_entry_size].m_name = name;
	sssubm_entry[sss_entry_size].m_var = var;

	sssubm_entry[sss_entry_size].m_int_min = min;
	sssubm_entry[sss_entry_size].m_int_max = max;

	sssubm_entry[sss_entry_size].m_int_step = step;

	sssubm_entry[sss_entry_size].m_state = UI_INT_STATE;

	sssubm_entry[sss_entry_size].m_space = space;

	++sss_entry_size;
}

void ui::add_sub_sub_float(const std::wstring& name, const std::string& var, float min, float max, float step, bool space)
{
	sssubm_entry[sss_entry_size].m_name = name;
	sssubm_entry[sss_entry_size].m_var = var;

	sssubm_entry[sss_entry_size].m_float_min = min;
	sssubm_entry[sss_entry_size].m_float_max = max;

	sssubm_entry[sss_entry_size].m_float_step = step;

	sssubm_entry[sss_entry_size].m_state = UI_FLOAT_STATE;

	sssubm_entry[sss_entry_size].m_space = space;

	++sss_entry_size;
}

void ui::add_sub_sub_item(const std::wstring& name, const std::string& var, std::vector<std::wstring> items, bool space)
{
	sssubm_entry[sss_entry_size].m_name = name;
	sssubm_entry[sss_entry_size].m_var = var;

	sssubm_entry[sss_entry_size].m_int_min = 0;
	sssubm_entry[sss_entry_size].m_int_max = items.size() - 1;

	sssubm_entry[sss_entry_size].m_int_step = 1;

	sssubm_entry[sss_entry_size].m_state = UI_ITEM_STATE;
	sssubm_entry[sss_entry_size].m_items = items;

	sssubm_entry[sss_entry_size].m_space = space;

	++sss_entry_size;
}

void ui::add_sub_sub_key(const std::wstring& name, const std::string& var, bool space)
{
	sssubm_entry[sss_entry_size].m_name = name;
	sssubm_entry[sss_entry_size].m_var = var;

	sssubm_entry[sss_entry_size].m_state = UI_KEY_STATE;

	sssubm_entry[sss_entry_size].m_space = space;

	++sss_entry_size;
}

void ui::add_sub_sub_function(const std::wstring& name, std::function<void()> fn, bool space)
{
	sssubm_entry[sss_entry_size].m_name = name;

	sssubm_entry[sss_entry_size].m_state = UI_FUNCTION_STATE;
	sssubm_entry[sss_entry_size].m_fn = fn;

	sssubm_entry[sss_entry_size].m_space = space;

	++sss_entry_size;
}

void ui::clear()
{
	for (int i = 0; i < m_entry_size; i++) {
		menu_entry[i].m_name.clear();
		menu_entry[i].m_space = false;
	}

	for (int i = 0; i < s_entry_size; i++) {
		subm_entry[i].m_name.clear();
		subm_entry[i].m_var.clear();

		subm_entry[i].m_int_min = 0;
		subm_entry[i].m_int_max = 0;
		subm_entry[i].m_int_step = 0;

		subm_entry[i].m_float_min = 0.0f;
		subm_entry[i].m_float_max = 0.0f;
		subm_entry[i].m_float_step = 0.0f;

		subm_entry[i].m_state = UI_NONE_STATE;

		subm_entry[i].m_items.clear();
		subm_entry[i].m_fn = []() {};
	}

	for (int i = 0; i < ss_entry_size; i++) {
		ssubm_entry[i].m_name.clear();
		ssubm_entry[i].m_var.clear();

		ssubm_entry[i].m_int_min = 0;
		ssubm_entry[i].m_int_max = 0;
		ssubm_entry[i].m_int_step = 0;

		ssubm_entry[i].m_float_min = 0.0f;
		ssubm_entry[i].m_float_max = 0.0f;
		ssubm_entry[i].m_float_step = 0.0f;

		ssubm_entry[i].m_state = UI_NONE_STATE;

		ssubm_entry[i].m_items.clear();
		ssubm_entry[i].m_fn = []() {};
	}

	for (int i = 0; i < sss_entry_size; i++) {
		sssubm_entry[i].m_name.clear();
		sssubm_entry[i].m_var.clear();

		sssubm_entry[i].m_int_min = 0;
		sssubm_entry[i].m_int_max = 0;
		sssubm_entry[i].m_int_step = 0;

		sssubm_entry[i].m_float_min = 0.0f;
		sssubm_entry[i].m_float_max = 0.0f;
		sssubm_entry[i].m_float_step = 0.0f;

		sssubm_entry[i].m_state = UI_NONE_STATE;

		sssubm_entry[i].m_items.clear();
		sssubm_entry[i].m_fn = []() {};
	}

	m_entry_size = 0;
	s_entry_size = 0;
	ss_entry_size = 0;
	sss_entry_size = 0;
}