#include "ui.h"

#include "globals.h"

void ui::handle_toggle_keys(unsigned int k)
{
	if (k == g_vars.get_as<int>(V_KEYS_ON_TOGGLE_UI).value())
		m_opened = !m_opened;

	if (k == g_vars.get_as<int>(V_KEYS_ON_TOGGLE_AIMBOT).value())
		g_vars.set(V_AIMBOT_ENABLED, !g_vars.get_as<bool>(V_AIMBOT_ENABLED).value());

	if (k == g_vars.get_as<int>(V_KEYS_ON_TOGGLE_TRIGGERBOT).value())
		g_vars.set(V_TRIGGERBOT_ENABLED, !g_vars.get_as<bool>(V_TRIGGERBOT_ENABLED).value());

	if (k == g_vars.get_as<int>(V_KEYS_ON_TOGGLE_THIRDPERSON).value())
		g_vars.set(V_MISC_VISUAL_THIRDPERSON, !g_vars.get_as<bool>(V_MISC_VISUAL_THIRDPERSON).value());

	if (k == g_vars.get_as<int>(V_KEYS_ON_TOGGLE_PANIC).value())
		GLOBAL(panic) = !GLOBAL(panic);
}

void ui::handle_input(unsigned int k)
{
	if (!s_opened[UI_SUB_POS])
	{
		if (k == VK_RIGHT)
		{
			s_entry_position = 0;
			s_opened[UI_SUB_POS] = true;
		}
		else if (k == VK_UP)
		{
			if (m_entry_position > 0)
				--m_entry_position;
		}
		else if (k == VK_DOWN)
		{
			if (m_entry_position < (m_entry_size - 1))
				++m_entry_position;
		}
	}
	else
	{
		if (!s_opened[UI_SUB_SUB_POS])
		{
			if (k == VK_UP)
			{
				if (!subm_entry[s_entry_position].m_key_hold)
				{
					if (s_entry_position > 0)
						--s_entry_position;
					else
						s_opened[UI_SUB_POS] = false;
				}
			}
			else if (k == VK_DOWN)
			{
				if (!subm_entry[s_entry_position].m_key_hold)
				{
					if (s_entry_position < (s_entry_size - 1))
						++s_entry_position;
				}
			}
			else if (k == VK_LEFT)
			{
				if (subm_entry[s_entry_position].m_state == UI_BOOL_STATE)
				{
					g_vars.set(subm_entry[s_entry_position].m_var, false);
				}
				else if (subm_entry[s_entry_position].m_state == UI_INT_STATE)
				{
					auto value = g_vars.get_as<int>(subm_entry[s_entry_position].m_var).value();

					g_vars.set(subm_entry[s_entry_position].m_var, value -= subm_entry[s_entry_position].m_int_step);

					if (value < subm_entry[s_entry_position].m_int_min)
						g_vars.set(subm_entry[s_entry_position].m_var, subm_entry[s_entry_position].m_int_min);
				}
				else if (subm_entry[s_entry_position].m_state == UI_FLOAT_STATE)
				{
					auto value = g_vars.get_as<float>(subm_entry[s_entry_position].m_var).value();

					g_vars.set(subm_entry[s_entry_position].m_var, value -= subm_entry[s_entry_position].m_float_step);

					if (value < subm_entry[s_entry_position].m_float_min)
						g_vars.set(subm_entry[s_entry_position].m_var, subm_entry[s_entry_position].m_float_min);
				}
				else if (subm_entry[s_entry_position].m_state == UI_ITEM_STATE)
				{
					auto value = g_vars.get_as<int>(subm_entry[s_entry_position].m_var).value();

					g_vars.set(subm_entry[s_entry_position].m_var, value -= subm_entry[s_entry_position].m_int_step);

					if (value < subm_entry[s_entry_position].m_int_min)
						g_vars.set(subm_entry[s_entry_position].m_var, subm_entry[s_entry_position].m_int_min);
				}
			}
			else if (k == VK_RIGHT)
			{
				if (subm_entry[s_entry_position].m_state == UI_BOOL_STATE)
				{
					g_vars.set(subm_entry[s_entry_position].m_var, true);
				}
				else if (subm_entry[s_entry_position].m_state == UI_INT_STATE)
				{
					auto value = g_vars.get_as<int>(subm_entry[s_entry_position].m_var).value();

					g_vars.set(subm_entry[s_entry_position].m_var, value += subm_entry[s_entry_position].m_int_step);

					if (value > subm_entry[s_entry_position].m_int_max)
						g_vars.set(subm_entry[s_entry_position].m_var, subm_entry[s_entry_position].m_int_max);
				}
				else if (subm_entry[s_entry_position].m_state == UI_FLOAT_STATE)
				{
					auto value = g_vars.get_as<float>(subm_entry[s_entry_position].m_var).value();

					g_vars.set(subm_entry[s_entry_position].m_var, value += subm_entry[s_entry_position].m_float_step);

					if (value > subm_entry[s_entry_position].m_float_max)
						g_vars.set(subm_entry[s_entry_position].m_var, subm_entry[s_entry_position].m_float_max);
				}
				else if (subm_entry[s_entry_position].m_state == UI_ITEM_STATE)
				{
					auto value = g_vars.get_as<int>(subm_entry[s_entry_position].m_var).value();

					g_vars.set(subm_entry[s_entry_position].m_var, value += subm_entry[s_entry_position].m_int_step);

					if (value > subm_entry[s_entry_position].m_int_max)
						g_vars.set(subm_entry[s_entry_position].m_var, subm_entry[s_entry_position].m_int_max);
				}
				else if (subm_entry[s_entry_position].m_state == UI_TAB_STATE)
				{
					ss_entry_position = 0;
					s_opened[UI_SUB_SUB_POS] = true;
				}
			}
			else if (k == VK_BACK)
			{
				if (subm_entry[s_entry_position].m_state == UI_KEY_STATE &&
					subm_entry[s_entry_position].m_key_hold)
				{
					g_vars.set(subm_entry[s_entry_position].m_var, 0);
					subm_entry[s_entry_position].m_key_hold = false;
				}
				else
					s_opened[UI_SUB_POS] = false;
			}
			else if (k == VK_RETURN)
			{
				if (subm_entry[s_entry_position].m_state == UI_KEY_STATE)
				{
					subm_entry[s_entry_position].m_key_hold = true;
				}
				else if (subm_entry[s_entry_position].m_state == UI_FUNCTION_STATE)
				{
					subm_entry[s_entry_position].m_fn();
				}
			}
			else
			{
				if (subm_entry[s_entry_position].m_state == UI_KEY_STATE &&
					subm_entry[s_entry_position].m_key_hold)
				{
					g_vars.set(subm_entry[s_entry_position].m_var, static_cast<int>(k));
					subm_entry[s_entry_position].m_key_hold = false;
				}
			}
		}
		else
		{
			if (!s_opened[UI_SUB_SUB_SUB_POS])
			{
				if (k == VK_UP)
				{
					if (!ssubm_entry[ss_entry_position].m_key_hold)
					{
						if (ss_entry_position > 0)
							--ss_entry_position;
						else
							s_opened[UI_SUB_SUB_POS] = false;
					}
				}
				else if (k == VK_DOWN)
				{
					if (!ssubm_entry[ss_entry_position].m_key_hold)
					{
						if (ss_entry_position < (ss_entry_size - 1))
							++ss_entry_position;
					}
				}
				else if (k == VK_LEFT)
				{
					if (ssubm_entry[ss_entry_position].m_state == UI_BOOL_STATE)
					{
						g_vars.set(ssubm_entry[ss_entry_position].m_var, false);
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_INT_STATE)
					{
						auto value = g_vars.get_as<int>(ssubm_entry[ss_entry_position].m_var).value();

						g_vars.set(ssubm_entry[ss_entry_position].m_var, value -= ssubm_entry[ss_entry_position].m_int_step);

						if (value < ssubm_entry[ss_entry_position].m_int_min)
							g_vars.set(ssubm_entry[ss_entry_position].m_var, ssubm_entry[ss_entry_position].m_int_min);
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_FLOAT_STATE)
					{
						auto value = g_vars.get_as<float>(ssubm_entry[ss_entry_position].m_var).value();

						g_vars.set(ssubm_entry[ss_entry_position].m_var, value -= ssubm_entry[ss_entry_position].m_float_step);

						if (value < ssubm_entry[ss_entry_position].m_float_min)
							g_vars.set(ssubm_entry[ss_entry_position].m_var, ssubm_entry[ss_entry_position].m_float_min);
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_ITEM_STATE)
					{
						auto value = g_vars.get_as<int>(ssubm_entry[ss_entry_position].m_var).value();

						g_vars.set(ssubm_entry[ss_entry_position].m_var, value -= ssubm_entry[ss_entry_position].m_int_step);

						if (value < ssubm_entry[ss_entry_position].m_int_min)
							g_vars.set(ssubm_entry[ss_entry_position].m_var, ssubm_entry[ss_entry_position].m_int_min);
					}
				}
				else if (k == VK_RIGHT)
				{
					if (ssubm_entry[ss_entry_position].m_state == UI_BOOL_STATE)
					{
						g_vars.set(ssubm_entry[ss_entry_position].m_var, true);
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_INT_STATE)
					{
						auto value = g_vars.get_as<int>(ssubm_entry[ss_entry_position].m_var).value();

						g_vars.set(ssubm_entry[ss_entry_position].m_var, value += ssubm_entry[ss_entry_position].m_int_step);

						if (value > ssubm_entry[ss_entry_position].m_int_max)
							g_vars.set(ssubm_entry[ss_entry_position].m_var, ssubm_entry[ss_entry_position].m_int_max);
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_FLOAT_STATE)
					{
						auto value = g_vars.get_as<float>(ssubm_entry[ss_entry_position].m_var).value();

						g_vars.set(ssubm_entry[ss_entry_position].m_var, value += ssubm_entry[ss_entry_position].m_float_step);

						if (value > ssubm_entry[ss_entry_position].m_float_max)
							g_vars.set(ssubm_entry[ss_entry_position].m_var, ssubm_entry[ss_entry_position].m_float_max);
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_ITEM_STATE)
					{
						auto value = g_vars.get_as<int>(ssubm_entry[ss_entry_position].m_var).value();

						g_vars.set(ssubm_entry[ss_entry_position].m_var, value += ssubm_entry[ss_entry_position].m_int_step);

						if (value > ssubm_entry[ss_entry_position].m_int_max)
							g_vars.set(ssubm_entry[ss_entry_position].m_var, ssubm_entry[ss_entry_position].m_int_max);
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_TAB_STATE)
					{
						sss_entry_position = 0;
						s_opened[UI_SUB_SUB_SUB_POS] = true;
					}
				}
				else if (k == VK_BACK)
				{
					if (ssubm_entry[ss_entry_position].m_state == UI_KEY_STATE &&
						ssubm_entry[ss_entry_position].m_key_hold)
					{
						g_vars.set(ssubm_entry[ss_entry_position].m_var, 0);
						ssubm_entry[ss_entry_position].m_key_hold = false;
					}
					else
						s_opened[UI_SUB_SUB_POS] = false;
				}
				else if (k == VK_RETURN)
				{
					if (ssubm_entry[ss_entry_position].m_state == UI_KEY_STATE)
					{
						ssubm_entry[ss_entry_position].m_key_hold = true;
					}
					else if (ssubm_entry[ss_entry_position].m_state == UI_FUNCTION_STATE)
					{
						ssubm_entry[ss_entry_position].m_fn();
					}
				}
				else
				{
					if (ssubm_entry[ss_entry_position].m_state == UI_KEY_STATE &&
						ssubm_entry[ss_entry_position].m_key_hold)
					{
						g_vars.set(ssubm_entry[ss_entry_position].m_var, static_cast<int>(k));
						ssubm_entry[ss_entry_position].m_key_hold = false;
					}
				}
			}
			else
			{
				if (k == VK_UP)
				{
					if (!sssubm_entry[sss_entry_position].m_key_hold)
					{
						if (sss_entry_position > 0)
							--sss_entry_position;
						else
							s_opened[UI_SUB_SUB_SUB_POS] = false;
					}
				}
				else if (k == VK_DOWN)
				{
					if (!sssubm_entry[sss_entry_position].m_key_hold)
					{
						if (sss_entry_position < (sss_entry_size - 1))
							++sss_entry_position;
					}
				}
				else if (k == VK_LEFT)
				{
					if (sssubm_entry[sss_entry_position].m_state == UI_BOOL_STATE)
					{
						g_vars.set(sssubm_entry[sss_entry_position].m_var, false);
					}
					else if (sssubm_entry[sss_entry_position].m_state == UI_INT_STATE)
					{
						auto value = g_vars.get_as<int>(sssubm_entry[sss_entry_position].m_var).value();

						g_vars.set(sssubm_entry[sss_entry_position].m_var, value -= sssubm_entry[sss_entry_position].m_int_step);

						if (value < sssubm_entry[sss_entry_position].m_int_min)
							g_vars.set(sssubm_entry[sss_entry_position].m_var, sssubm_entry[sss_entry_position].m_int_min);
					}
					else if (sssubm_entry[sss_entry_position].m_state == UI_FLOAT_STATE)
					{
						auto value = g_vars.get_as<float>(sssubm_entry[sss_entry_position].m_var).value();

						g_vars.set(sssubm_entry[sss_entry_position].m_var, value -= sssubm_entry[sss_entry_position].m_float_step);

						if (value < sssubm_entry[sss_entry_position].m_float_min)
							g_vars.set(sssubm_entry[sss_entry_position].m_var, sssubm_entry[sss_entry_position].m_float_min);
					}
					else if (sssubm_entry[sss_entry_position].m_state == UI_ITEM_STATE)
					{
						auto value = g_vars.get_as<int>(sssubm_entry[sss_entry_position].m_var).value();

						g_vars.set(sssubm_entry[sss_entry_position].m_var, value -= sssubm_entry[sss_entry_position].m_int_step);

						if (value < sssubm_entry[sss_entry_position].m_int_min)
							g_vars.set(sssubm_entry[sss_entry_position].m_var, sssubm_entry[sss_entry_position].m_int_min);
					}
				}
				else if (k == VK_RIGHT)
				{
					if (sssubm_entry[sss_entry_position].m_state == UI_BOOL_STATE)
					{
						g_vars.set(sssubm_entry[sss_entry_position].m_var, true);
					}
					else if (sssubm_entry[sss_entry_position].m_state == UI_INT_STATE)
					{
						auto value = g_vars.get_as<int>(sssubm_entry[sss_entry_position].m_var).value();

						g_vars.set(sssubm_entry[sss_entry_position].m_var, value += sssubm_entry[sss_entry_position].m_int_step);

						if (value > sssubm_entry[sss_entry_position].m_int_max)
							g_vars.set(sssubm_entry[sss_entry_position].m_var, sssubm_entry[sss_entry_position].m_int_max);
					}
					else if (sssubm_entry[sss_entry_position].m_state == UI_FLOAT_STATE)
					{
						auto value = g_vars.get_as<float>(sssubm_entry[sss_entry_position].m_var).value();

						g_vars.set(sssubm_entry[sss_entry_position].m_var, value += sssubm_entry[sss_entry_position].m_float_step);

						if (value > sssubm_entry[sss_entry_position].m_float_max)
							g_vars.set(sssubm_entry[sss_entry_position].m_var, sssubm_entry[sss_entry_position].m_float_max);
					}
					else if (sssubm_entry[sss_entry_position].m_state == UI_ITEM_STATE)
					{
						auto value = g_vars.get_as<int>(sssubm_entry[sss_entry_position].m_var).value();

						g_vars.set(sssubm_entry[sss_entry_position].m_var, value += sssubm_entry[sss_entry_position].m_int_step);

						if (value > sssubm_entry[sss_entry_position].m_int_max)
							g_vars.set(sssubm_entry[sss_entry_position].m_var, sssubm_entry[sss_entry_position].m_int_max);
					}
				}
				else if (k == VK_BACK)
				{
					if (sssubm_entry[sss_entry_position].m_state == UI_KEY_STATE &&
						sssubm_entry[sss_entry_position].m_key_hold)
					{
						g_vars.set(sssubm_entry[sss_entry_position].m_var, 0);
						sssubm_entry[sss_entry_position].m_key_hold = false;
					}
					else
						s_opened[UI_SUB_SUB_SUB_POS] = false;
				}
				else if (k == VK_RETURN)
				{
					if (sssubm_entry[sss_entry_position].m_state == UI_KEY_STATE)
					{
						sssubm_entry[sss_entry_position].m_key_hold = true;
					}
					else if (sssubm_entry[sss_entry_position].m_state == UI_FUNCTION_STATE)
					{
						sssubm_entry[sss_entry_position].m_fn();
					}
				}
				else
				{
					if (sssubm_entry[sss_entry_position].m_state == UI_KEY_STATE &&
						sssubm_entry[sss_entry_position].m_key_hold)
					{
						g_vars.set(sssubm_entry[sss_entry_position].m_var, static_cast<int>(k));
						sssubm_entry[sss_entry_position].m_key_hold = false;
					}
				}
			}
		}
	}
}