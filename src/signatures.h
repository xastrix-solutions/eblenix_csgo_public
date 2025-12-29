#pragma once

#include <stdint.h>
#include <windows.h>
#include <string>
#include <vector>

enum _signature_list {
	S_DEVICE,
	S_GLOW_MANAGER,
	S_WEAPON_SYSTEM,
	S_VIEW_MATRIX,
	S_LINE_GOES_THROUGH_SMOKE,
	S_HAS_C4,
	S_INPUT,
	S_CAM_THINK,
	S_IS_LOADOUTALLOWED,
	S_LIST_LEAVES,
	maxSignatures,
};

using sig_t = uint8_t*;

struct sig {
	void init();
	sig_t get_sig(_signature_list index);

private:
	DWORD get_module_size(const HMODULE mod);
	std::vector<int> pattern_to_bytes(const char* signature);
	sig_t scan_sig(const std::string& module_name, const std::string& signature);

private:
	sig_t m_signatures[maxSignatures];
};

inline sig g_sig;