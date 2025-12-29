#include "signatures.h"

#include "helpers.h"
#include "globals.h"

void sig::init()
{
	m_signatures[S_DEVICE]                  = scan_sig(GLOBAL(module_list[shaderapidx9DLL]), "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1;
	m_signatures[S_GLOW_MANAGER]            = scan_sig(GLOBAL(module_list[clientDLL]), "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00") + 3;
	m_signatures[S_WEAPON_SYSTEM]           = scan_sig(GLOBAL(module_list[clientDLL]), "8B 35 ? ? ? ? FF 10 0F B7 C0") + 2;
	m_signatures[S_VIEW_MATRIX]             = scan_sig(GLOBAL(module_list[clientDLL]), "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9") + 3;
	m_signatures[S_LINE_GOES_THROUGH_SMOKE] = scan_sig(GLOBAL(module_list[clientDLL]), "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
	m_signatures[S_HAS_C4]                  = scan_sig(GLOBAL(module_list[clientDLL]), "56 8B F1 85 F6 74 31");
	m_signatures[S_INPUT]                   = scan_sig(GLOBAL(module_list[clientDLL]), "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1;
	m_signatures[S_CAM_THINK]               = scan_sig(GLOBAL(module_list[clientDLL]), "85 C0 75 30 38 86");
	m_signatures[S_IS_LOADOUTALLOWED]       = scan_sig(GLOBAL(module_list[clientDLL]), "84 C0 75 04 B0 01 5F");
	m_signatures[S_LIST_LEAVES]             = scan_sig(GLOBAL(module_list[clientDLL]), "56 52 FF 50 18") + 5;
}

sig_t sig::get_sig(_signature_list index)
{
	return m_signatures[index];
}

DWORD sig::get_module_size(const HMODULE mod)
{
	const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(mod);

	if (!dos_header || dos_header->e_magic != IMAGE_DOS_SIGNATURE)
		return 0L;

	const auto nt_header = reinterpret_cast<PIMAGE_NT_HEADERS>(mod + dos_header->e_lfanew);

	if (!nt_header || nt_header->Signature != IMAGE_NT_SIGNATURE)
		return 0L;

	return nt_header->OptionalHeader.SizeOfImage;
}

std::vector<int> sig::pattern_to_bytes(const char* signature)
{
	std::vector<int> bytes{};

	auto start = const_cast<char*>(signature);
	for (auto c = start; c < start + strlen(signature); c++)
	{
		if (*c == '?') {
			c++;

			if (*c == '?')
				c++;

			bytes.push_back(-1);
		}
		else {
			bytes.push_back(std::strtoul(c, &c, 16));
		}
	}

	return bytes;
}

sig_t sig::scan_sig(const std::string& module_name, const std::string& signature)
{
	const auto mod = GetModuleHandleA(module_name.c_str());

	if (!mod)
		return {};

	const auto base = reinterpret_cast<uint8_t*>(mod);
	const auto bytes = pattern_to_bytes(signature.c_str());

	const auto module_size = get_module_size(mod);

	const auto pattern_data = bytes.data();
	const auto pattern_size = bytes.size();

	for (int i = 0; i < module_size - pattern_size; i++) {
		auto found = true;

		for (auto j = 0; j < pattern_size; ++j) {
			if (base[i + j] != pattern_data[j] && pattern_data[j] != -1) {
				found = false;
				break;
			}
		}

		if (found)
			return &base[i];
	}

#ifdef _DEBUG
	printf("Wrong signature: %s\n", signature.c_str());
#endif

	return {};
}