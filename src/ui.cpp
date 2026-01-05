#include "ui.h"

#include "globals.h"
#include "config_manager.h"
#include "interfaces.h"

#include "sprites.hpp"

void ui::init(IDirect3DDevice9* device)
{
	m_sprites[UI_SPRITE_LOGO].init(device, m_ui_logotype, sizeof(m_ui_logotype), 178, 33);
}

void ui::run()
{
	float old_progress{};
	calc_animation_progress(8.5f, g_csgo.m_globals->frame_time, old_progress);

	m_colors[UI_MAIN_COL] = color_t(V_UI_COL,
		static_cast<int>(target_animation_progress * 255.0f));

	m_colors[UI_PRIMARY_COL] = color_t(V_UI_COL,
		static_cast<int>(target_animation_progress * 130.0f));

	m_colors[UI_SHADOW_COL] = color_t(20, 20, 20,
		static_cast<int>(target_animation_progress * g_vars.get_as<int>(V_UI_COL_A).value()));

	m_colors[UI_TEXT_COL] = color_t(253, 253, 253,
		static_cast<int>(target_animation_progress * 255.0f));

	if (target_animation_progress > 0.0f)
	{
		clear();
		setup();

		for (int i = 0; i < maxUISprites; i++)
			m_sprites[i].begin();

		draw(g_vars.get_as<int>(V_UI_POS_X).value(), g_vars.get_as<int>(V_UI_POS_Y).value());

		for (int i = 0; i < maxUISprites; i++)
			m_sprites[i].end();
	}

	current_animation_progress = old_progress;
}

void ui::calc_animation_progress(float anim_time, float delta_time, float& old_alpha)
{
	if (m_opened)
	{
		target_animation_progress += anim_time * delta_time;

		if (target_animation_progress > 1.0f)
			target_animation_progress = 1.0f;
	}
	else
	{
		target_animation_progress -= anim_time * delta_time;

		if (target_animation_progress < 0.0f)
			target_animation_progress = 0.0f;
	}

	old_alpha = current_animation_progress;
	current_animation_progress = target_animation_progress;
}

void ui::setup()
{
	add(L"Aim", [&]() {
		add_bool(L"Enable", V_AIMBOT_ENABLED, true);

		add_bool(L"Silent", V_AIMBOT_SILENT);
		add_bool(L"Auto Pistol", V_AIMBOT_AUTOPISTOL, true);

		add_bool(L"Visible", V_AIMBOT_VISIBLE_CHECK);
		add_bool(L"Team", V_AIMBOT_TEAMMATE_CHECK);
		add_bool(L"Smoke", V_AIMBOT_SMOKE_CHECK);
		add_bool(L"Flash", V_AIMBOT_FLASH_CHECK);
		add_bool(L"Scope", V_AIMBOT_SCOPE_CHECK);
		add_bool(L"Jump", V_AIMBOT_JUMP_CHECK, true);

		add_tab(L"Weapons", [&]() {
			std::vector<std::wstring> m_hitboxes{ L"Head", L"Neck", L"Chest", L"Stomach", L"Pelvis" };
			std::vector<std::wstring> m_types{ L"Hitbox", L"Nearest" };

			add_sub_tab(L"Pistols", [&]() {
				add_sub_sub_item(L"Type", V_AIMBOT_TYPE_PISTOL, m_types, true);

				if (g_vars.get_as<int>(V_AIMBOT_TYPE_PISTOL).value() == 0)
					add_sub_sub_item(L"Hitbox", V_AIMBOT_BONE_PISTOL, m_hitboxes, true);

				add_sub_sub_float(L"Fov", V_AIMBOT_FOV_PISTOL, 0.0f, 180.0f, 0.5f);
				add_sub_sub_float(L"Smooth", V_AIMBOT_SMOOTH_PISTOL, 1.0f, 10.0f, 0.1f);
			});

			add_sub_tab(L"Rifles", [&]() {
				add_sub_sub_item(L"Type", V_AIMBOT_TYPE_RIFLE, m_types, true);

				if (g_vars.get_as<int>(V_AIMBOT_TYPE_RIFLE).value() == 0)
					add_sub_sub_item(L"Hitbox", V_AIMBOT_BONE_RIFLE, m_hitboxes, true);

				add_sub_sub_float(L"Fov", V_AIMBOT_FOV_RIFLE, 0.0f, 180.0f, 0.5f);
				add_sub_sub_float(L"Smooth", V_AIMBOT_SMOOTH_RIFLE, 1.0f, 10.0f, 0.1f);
			});

			add_sub_tab(L"Snipers", [&]() {
				add_sub_sub_item(L"Type", V_AIMBOT_TYPE_SNIPER, m_types, true);

				if (g_vars.get_as<int>(V_AIMBOT_TYPE_SNIPER).value() == 0)
					add_sub_sub_item(L"Hitbox", V_AIMBOT_BONE_SNIPER, m_hitboxes, true);

				add_sub_sub_float(L"Fov", V_AIMBOT_FOV_SNIPER, 0.0f, 180.0f, 0.5f);
				add_sub_sub_float(L"Smooth", V_AIMBOT_SMOOTH_SNIPER, 1.0f, 10.0f, 0.1f);
			});

			add_sub_tab(L"Heavies", [&]() {
				add_sub_sub_item(L"Type", V_AIMBOT_TYPE_HEAVY, m_types, true);

				if (g_vars.get_as<int>(V_AIMBOT_TYPE_HEAVY).value() == 0)
					add_sub_sub_item(L"Hitbox", V_AIMBOT_BONE_HEAVY, m_hitboxes, true);

				add_sub_sub_float(L"Fov", V_AIMBOT_FOV_HEAVY, 0.0f, 180.0f, 0.5f);
				add_sub_sub_float(L"Smooth", V_AIMBOT_SMOOTH_HEAVY, 1.0f, 10.0f, 0.1f);
			});

			add_sub_tab(L"Smgs", [&]() {
				add_sub_sub_item(L"Type", V_AIMBOT_TYPE_SMG, m_types, true);

				if (g_vars.get_as<int>(V_AIMBOT_TYPE_SMG).value() == 0)
					add_sub_sub_item(L"Hitbox", V_AIMBOT_BONE_SMG, m_hitboxes, true);

				add_sub_sub_float(L"Fov", V_AIMBOT_FOV_SMG, 0.0f, 180.0f, 0.5f);
				add_sub_sub_float(L"Smooth", V_AIMBOT_SMOOTH_SMG, 1.0f, 10.0f, 0.1f);
			});
		});

		add_tab(L"Knifes", [&]() {
			add_sub_bool(L"Enable", V_KNIFEBOT_ENABLED, true);

			add_sub_bool(L"Team", V_KNIFEBOT_TEAMMATE_CHECK);
			add_sub_bool(L"Smoke", V_KNIFEBOT_SMOKE_CHECK);
			add_sub_bool(L"Flash", V_KNIFEBOT_FLASH_CHECK, true);

			add_sub_float(L"Distance", V_KNIFEBOT_DISTANCE, 40.0f, 80.0f, 0.5f);
		});
	});

	add(L"Trigger", [&]() {
		add_bool(L"Enable", V_TRIGGERBOT_ENABLED, true);

		add_bool(L"Team", V_TRIGGERBOT_TEAMMATE_CHECK);
		add_bool(L"Smoke", V_TRIGGERBOT_SMOKE_CHECK);
		add_bool(L"Flash", V_TRIGGERBOT_FLASH_CHECK);
		add_bool(L"Scope", V_TRIGGERBOT_SCOPE_CHECK);
		add_bool(L"Jump", V_TRIGGERBOT_JUMP_CHECK, true);

		add_bool(L"Head", V_TRIGGERBOT_HITBOX_HEAD);
		add_bool(L"Body", V_TRIGGERBOT_HITBOX_BODY);
		add_bool(L"Arms", V_TRIGGERBOT_HITBOX_ARMS);
		add_bool(L"Legs", V_TRIGGERBOT_HITBOX_LEGS);
	});

	add(L"Esp", [&]() {
		add_bool(L"Enable", V_ESP_ENABLED, true);

		add_bool(L"Team", V_ESP_TEAM);
		add_bool(L"Visible", V_ESP_VISIBLE_ONLY);
		add_bool(L"Walking", V_ESP_WALKING_ONLY, true);

		add_item(L"Render Type", V_ESP_RENDER_TYPE, { L"Static", L"Dynamic" }, true);

		add_tab(L"Name", [&]() {
			add_sub_bool(L"Enable", V_ESP_NAME_ENABLED, true);

			add_sub_item(L"Name Type", V_ESP_NAME_TYPE, { L"Default", L"Lower", L"Upper" }, true);

			add_sub_int(L"Name R", V_ESP_NAME_COL_R, 0, 255, 1);
			add_sub_int(L"Name G", V_ESP_NAME_COL_G, 0, 255, 1);
			add_sub_int(L"Name B", V_ESP_NAME_COL_B, 0, 255, 1);
		});

		add_tab(L"Box", [&]() {
			add_sub_bool(L"Enable", V_ESP_BOX_ENABLED, true);

			add_sub_item(L"Box Type", V_ESP_BOX_TYPE,
				{ L"Default", L"Default (Background)", L"Corner", L"Corner (Background)" }, true);

			add_sub_int(L"Box R", V_ESP_BOX_COL_R, 0, 255, 1);
			add_sub_int(L"Box G", V_ESP_BOX_COL_G, 0, 255, 1);
			add_sub_int(L"Box B", V_ESP_BOX_COL_B, 0, 255, 1);
		});

		add_tab(L"Health", [&]() {
			add_sub_bool(L"Enable", V_ESP_HEALTH_ENABLED, true);

			add_sub_item(L"Health Type", V_ESP_HEALTH_TYPE, { L"Default", L"Health Based" }, true);

			if (g_vars.get_as<int>(V_ESP_HEALTH_TYPE).value() == 0)
			{
				add_sub_int(L"Health R", V_ESP_HEALTH_COL_R, 0, 255, 1);
				add_sub_int(L"Health G", V_ESP_HEALTH_COL_G, 0, 255, 1);
				add_sub_int(L"Health B", V_ESP_HEALTH_COL_B, 0, 255, 1, true);
			}

			add_sub_bool(L"Health Battery", V_ESP_HEALTH_BATTERY);
		});

		add_tab(L"Weapon", [&]() {
			add_sub_bool(L"Enable", V_ESP_WEAPON_ENABLED, true);

			add_sub_item(L"Weapon Type", V_ESP_WEAPON_TYPE, { L"Text", L"Icon" }, true);

			add_sub_int(L"Weapon R", V_ESP_WEAPON_COL_R, 0, 255, 1);
			add_sub_int(L"Weapon G", V_ESP_WEAPON_COL_G, 0, 255, 1);
			add_sub_int(L"Weapon B", V_ESP_WEAPON_COL_B, 0, 255, 1);
		});

		add_tab(L"Skeleton", [&]() {
			add_sub_bool(L"Enable", V_ESP_SKELETON_ENABLED, true);

			add_sub_item(L"Skeleton Type", V_ESP_SKELETON_TYPE, { L"Default", L"Health Based" }, true);

			add_sub_int(L"Skeleton R", V_ESP_SKELETON_COL_R, 0, 255, 1);
			add_sub_int(L"Skeleton G", V_ESP_SKELETON_COL_G, 0, 255, 1);
			add_sub_int(L"Skeleton B", V_ESP_SKELETON_COL_B, 0, 255, 1);
		});

		add_tab(L"Armor", [&]() {
			add_sub_bool(L"Enable", V_ESP_ARMOR_ENABLED, true);

			add_sub_int(L"Armor R", V_ESP_ARMOR_COL_R, 0, 255, 1);
			add_sub_int(L"Armor G", V_ESP_ARMOR_COL_G, 0, 255, 1);
			add_sub_int(L"Armor B", V_ESP_ARMOR_COL_B, 0, 255, 1);
		});

		add_tab(L"Barrel", [&]() {
			add_sub_bool(L"Enable", V_ESP_BARREL_ENABLED, true);

			add_sub_int(L"Barrel R", V_ESP_BARREL_COL_R, 0, 255, 1);
			add_sub_int(L"Barrel G", V_ESP_BARREL_COL_G, 0, 255, 1);
			add_sub_int(L"Barrel B", V_ESP_BARREL_COL_B, 0, 255, 1);
		});

		add_tab(L"Crosshair", [&]() {
			add_sub_bool(L"Enable", V_ESP_CROSSHAIR_ENABLED, true);

			add_sub_int(L"Crosshair R", V_ESP_CROSSHAIR_COL_R, 0, 255, 1);
			add_sub_int(L"Crosshair G", V_ESP_CROSSHAIR_COL_G, 0, 255, 1);
			add_sub_int(L"Crosshair B", V_ESP_CROSSHAIR_COL_B, 0, 255, 1);
		});

		add_tab(L"Snap Lines", [&]() {
			add_sub_bool(L"Enable", V_ESP_SNAP_LINES_ENABLED, true);

			add_sub_int(L"Snap Lines R", V_ESP_SNAP_LINES_COL_R, 0, 255, 1);
			add_sub_int(L"Snap Lines G", V_ESP_SNAP_LINES_COL_G, 0, 255, 1);
			add_sub_int(L"Snap Lines B", V_ESP_SNAP_LINES_COL_B, 0, 255, 1);
		}, true);

		add_tab(L"Flags", [&]() {
			add_sub_bool(L"Enable", V_ESP_FLAGS_ENABLED, true);

			add_sub_bool(L"HK", V_ESP_FLAGS_HK);
			add_sub_bool(L"Health", V_ESP_FLAGS_HEALTH);
			add_sub_bool(L"Money", V_ESP_FLAGS_MONEY);
			add_sub_bool(L"Ammo", V_ESP_FLAGS_AMMO);
			add_sub_bool(L"Scoped", V_ESP_FLAGS_SCOPED);
			add_sub_bool(L"Flashed", V_ESP_FLAGS_FLASHED);
			add_sub_bool(L"Defusing", V_ESP_FLAGS_DEFUSING);
			add_sub_bool(L"Distance", V_ESP_FLAGS_DISTANCE, true);

			add_sub_int(L"Flags R", V_ESP_FLAGS_COL_R, 0, 255, 1);
			add_sub_int(L"Flags G", V_ESP_FLAGS_COL_G, 0, 255, 1);
			add_sub_int(L"Flags B", V_ESP_FLAGS_COL_B, 0, 255, 1, true);

			add_sub_tab(L"Inventory Items", [&]() {
				add_sub_sub_bool(L"Enable", V_ESP_FLAGS_ITEMS_ENABLED, true);

				add_sub_sub_int(L"Inventory Items R", V_ESP_FLAGS_ITEMS_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Inventory Items G", V_ESP_FLAGS_ITEMS_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Inventory Items B", V_ESP_FLAGS_ITEMS_COL_B, 0, 255, 1);
			});
		});
	});

	add(L"Visuals", [&]() {
		add_bool(L"Enable", V_VISUALS_ENABLED, true);

		add_tab(L"Interface", [&]() {
			add_sub_bool(L"Draw Status", V_VISUALS_INTERFACE_STATUS);
			add_sub_bool(L"Draw Spectators", V_VISUALS_INTERFACE_SPECTATORS);
		});

		add_tab(L"World", [&]() {
			add_sub_tab(L"Items", [&]() {
				add_sub_sub_bool(L"Enable", V_VISUALS_WORLD_ITEMS_ENABLED, true);

				add_sub_sub_bool(L"Items Distance", V_VISUALS_WORLD_ITEMS_DISTANCE, true);

				add_sub_sub_int(L"Items R", V_VISUALS_WORLD_ITEMS_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Items G", V_VISUALS_WORLD_ITEMS_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Items B", V_VISUALS_WORLD_ITEMS_COL_B, 0, 255, 1);
			});

			add_sub_tab(L"Grenades (In use)", [&]() {
				add_sub_sub_bool(L"Enable", V_VISUALS_WORLD_PROJECTLINES_ENABLED, true);

				add_sub_sub_item(L"Grenades Type", V_VISUALS_WORLD_PROJECTLINES_TYPE, { L"Text", L"Icon" }, true);

				add_sub_sub_bool(L"Grenades Distance", V_VISUALS_WORLD_PROJECTLINES_DISTANCE, true);

				add_sub_sub_int(L"Grenades R", V_VISUALS_WORLD_PROJECTLINES_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Grenades G", V_VISUALS_WORLD_PROJECTLINES_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Grenades B", V_VISUALS_WORLD_PROJECTLINES_COL_B, 0, 255, 1);
			});

			add_sub_tab(L"Weapons", [&]() {
				add_sub_sub_bool(L"Enable", V_VISUALS_WORLD_WEAPONS_ENABLED, true);

				add_sub_sub_item(L"Weapons Type", V_VISUALS_WORLD_WEAPONS_TYPE, { L"Text", L"Icon" }, true);

				add_sub_sub_bool(L"Weapons Distance", V_VISUALS_WORLD_WEAPONS_DISTANCE);
				add_sub_sub_bool(L"Weapons Ammo Bar", V_VISUALS_WORLD_WEAPONS_AMMO_BAR, true);

				add_sub_sub_int(L"Weapons R", V_VISUALS_WORLD_WEAPONS_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Weapons G", V_VISUALS_WORLD_WEAPONS_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Weapons B", V_VISUALS_WORLD_WEAPONS_COL_B, 0, 255, 1, true);

				add_sub_sub_int(L"Weapons Ammo Bar R", V_VISUALS_WORLD_WEAPONS_AMMO_BAR_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Weapons Ammo Bar G", V_VISUALS_WORLD_WEAPONS_AMMO_BAR_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Weapons Ammo Bar B", V_VISUALS_WORLD_WEAPONS_AMMO_BAR_COL_B, 0, 255, 1);
			});

			add_sub_tab(L"Bomb (Planted)", [&]() {
				add_sub_sub_bool(L"Enable", V_VISUALS_WORLD_C4_ENABLED, true);

				add_sub_sub_item(L"Bomb Type", V_VISUALS_WORLD_C4_TYPE, { L"Text", L"Icon" }, true);

				add_sub_sub_bool(L"Bomb Time Bar", V_VISUALS_WORLD_C4_TIME_BAR);
				add_sub_sub_bool(L"Bomb Defuse Bar", V_VISUALS_WORLD_C4_DEFUSE_BAR);
				add_sub_sub_bool(L"Bomb Damage Indicator", V_VISUALS_WORLD_C4_DAMAGE_INDICATOR, true);

				add_sub_sub_int(L"Bomb R", V_VISUALS_WORLD_C4_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Bomb G", V_VISUALS_WORLD_C4_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Bomb B", V_VISUALS_WORLD_C4_COL_B, 0, 255, 1, true);

				add_sub_sub_int(L"Bomb Time Bar R", V_VISUALS_WORLD_C4_COL_TIME_BAR_R, 0, 255, 1);
				add_sub_sub_int(L"Bomb Time Bar G", V_VISUALS_WORLD_C4_COL_TIME_BAR_G, 0, 255, 1);
				add_sub_sub_int(L"Bomb Time Bar B", V_VISUALS_WORLD_C4_COL_TIME_BAR_B, 0, 255, 1, true);

				add_sub_sub_int(L"Bomb Defuse Bar R", V_VISUALS_WORLD_C4_COL_DEFUSE_BAR_R, 0, 255, 1);
				add_sub_sub_int(L"Bomb Defuse Bar G", V_VISUALS_WORLD_C4_COL_DEFUSE_BAR_G, 0, 255, 1);
				add_sub_sub_int(L"Bomb Defuse Bar B", V_VISUALS_WORLD_C4_COL_DEFUSE_BAR_B, 0, 255, 1);
			});

			add_sub_tab(L"Nightmode", [&]() {
				add_sub_sub_bool(L"Enable", V_VISUALS_WORLD_NIGHTMODE_ENABLED, true);

				add_sub_sub_float(L"World Brightness", V_VISUALS_WORLD_NIGHTMODE_WORLD_BRIGHTNESS, 0.1f, 1.0f, 0.01f);
				add_sub_sub_float(L"Sky Brightness", V_VISUALS_WORLD_NIGHTMODE_SKY_BRIGHTNESS, 0.1f, 1.0f, 0.01f);
				add_sub_sub_float(L"Models Brightness", V_VISUALS_WORLD_NIGHTMODE_MODEL_BRIGHTNESS, 0.1f, 1.0f, 0.01f);
				add_sub_sub_float(L"Decals Brightness", V_VISUALS_WORLD_NIGHTMODE_DECAL_BRIGHTNESS, 0.1f, 1.0f, 0.01f);
				add_sub_sub_float(L"Others Brightness", V_VISUALS_WORLD_NIGHTMODE_OTHER_BRIGHTNESS, 0.1f, 1.0f, 0.01f, true);

				add_sub_sub_function(L"Apply Changes", []() {
					GLOBAL(visuals_nightmode_state) = false;
				});
			});
		});

		add_tab(L"Removals", [&]() {
			add_sub_bool(L"Smoke", V_VISUALS_REMOVALS_SMOKE);
			add_sub_bool(L"Flash", V_VISUALS_REMOVALS_FLASH);
			add_sub_bool(L"Hands", V_VISUALS_REMOVALS_HANDS);
			add_sub_bool(L"Sleeves", V_VISUALS_REMOVALS_SLEEVES);
			add_sub_bool(L"Scope", V_VISUALS_REMOVALS_SCOPE);
		});
	});

	add(L"Essentials", [&]() {
		add_tab(L"Visual", [&]() {
			add_sub_bool(L"Radar", V_MISC_VISUAL_ENGINE_RADAR);
			add_sub_bool(L"Inventory Unlock", V_MISC_VISUAL_INVENTORY_UNLOCK);
			add_sub_bool(L"Reveal Ranks", V_MISC_VISUAL_REVEAL_RANKS, true);

			add_sub_float(L"Viewmodel Fov", V_MISC_VISUAL_VIEWMODEL_FOV, 54.0f, 130.0f, 1.0f, true);

			add_sub_bool(L"Aspect Ratio", V_MISC_VISUAL_ASPECT_RATIO);
			add_sub_float(L"Aspect Ratio Value", V_MISC_VISUAL_ASPECT_RATIO_VALUE, 10.0f, 30.0f, 0.5f, true);

			add_sub_bool(L"Thirdperson", V_MISC_VISUAL_THIRDPERSON);
			add_sub_float(L"Thirdperson Fov", V_MISC_VISUAL_THIRDPERSON_FOV, 20.0f, 90.0f, 1.0f);
		});

		add_tab(L"Movement", [&]() {
			add_sub_bool(L"Bunnyhop", V_MISC_MOVEMENT_BUNNYHOP);
			add_sub_bool(L"Infinite Duck", V_MISC_MOVEMENT_INFINITE_DUCK);
			add_sub_bool(L"Autostrafe", V_MISC_MOVEMENT_AUTO_STRAFE);
		});

		add_tab(L"Event Logs", [&]() {
			add_sub_bool(L"Player Hurt", V_MISC_EVENT_LOGS_PLAYER_HURT);
			add_sub_bool(L"Player Purchase", V_MISC_EVENT_LOGS_PLAYER_PURCHASE);
		});

		add_tab(L"Menu", [&]() {
			add_sub_bool(L"Mouse Wheel Navigation", V_UI_MOUSE_WHEEL_NAVIGATION, true);

			add_sub_int(L"Position X", V_UI_POS_X, 0, 500, 1);
			add_sub_int(L"Position Y", V_UI_POS_Y, 0, 700, 1, true);

			add_sub_int(L"Menu R", V_UI_COL_R, 0, 255, 1);
			add_sub_int(L"Menu G", V_UI_COL_G, 0, 255, 1);
			add_sub_int(L"Menu B", V_UI_COL_B, 0, 255, 1, true);

			add_sub_int(L"Menu A", V_UI_COL_A, 70, 170, 1);
		}, true);

		add_function(L"Unload", []() {
			g::Unload();
		});
	});

	add(L"Glow", [&]() {
		add_bool(L"Enable", V_GLOW_ENABLED, true);

		add_bool(L"Team", V_GLOW_TEAM);
		add_bool(L"Visible", V_GLOW_VISIBLE_ONLY);
		add_bool(L"Walking", V_GLOW_WALKING_ONLY, true);

		add_bool(L"C4", V_GLOW_C4, true);

		add_tab(L"Color", [&]() {
			add_sub_tab(L"Enemy", [&]() {
				add_sub_sub_int(L"Enemy R", V_GLOW_ENEMY_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Enemy G", V_GLOW_ENEMY_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Enemy B", V_GLOW_ENEMY_COL_B, 0, 255, 1, true);

				add_sub_sub_int(L"Enemy A", V_GLOW_ENEMY_COL_A, 130, 255, 1);
			});

			add_sub_tab(L"Team", [&]() {
				add_sub_sub_int(L"Team R", V_GLOW_TEAM_COL_R, 0, 255, 1);
				add_sub_sub_int(L"Team G", V_GLOW_TEAM_COL_G, 0, 255, 1);
				add_sub_sub_int(L"Team B", V_GLOW_TEAM_COL_B, 0, 255, 1, true);

				add_sub_sub_int(L"Team A", V_GLOW_TEAM_COL_A, 130, 255, 1);
			});

			add_sub_tab(L"C4", [&]() {
				add_sub_sub_int(L"C4 R", V_GLOW_C4_COL_R, 0, 255, 1);
				add_sub_sub_int(L"C4 G", V_GLOW_C4_COL_G, 0, 255, 1);
				add_sub_sub_int(L"C4 B", V_GLOW_C4_COL_B, 0, 255, 1, true);

				add_sub_sub_int(L"C4 A", V_GLOW_C4_COL_A, 130, 255, 1);
			}, true);

			add_sub_bool(L"Health Based", V_GLOW_HEALTH_BASED);
		});
	});

	add(L"Chams", [&]() {
		add_bool(L"Enable", V_CHAMS_ENABLED, true);

		add_bool(L"Team", V_CHAMS_TEAM);
		add_bool(L"Visible", V_CHAMS_VISIBLE_ONLY);
		add_bool(L"Walking", V_CHAMS_WALKING_ONLY, true);

		add_item(L"Type", V_CHAMS_TYPE, { L"1", L"2", L"3" }, true);

		add_int(L"Chams R", V_CHAMS_COL_R, 0, 255, 1);
		add_int(L"Chams G", V_CHAMS_COL_G, 0, 255, 1);
		add_int(L"Chams B", V_CHAMS_COL_B, 0, 255, 1, true);

		add_bool(L"Health Based", V_CHAMS_HEALTH_BASED);
	});

	add(L"Keys", [&]() {
		add_tab(L"On Toggle", [&]() {
			add_sub_tab(L"Aim", [&]() {
				add_sub_sub_key(L"Aimbot", V_KEYS_ON_TOGGLE_AIMBOT);
				add_sub_sub_key(L"Trigger", V_KEYS_ON_TOGGLE_TRIGGERBOT);
			});

			add_sub_tab(L"Misc", [&]() {
				add_sub_sub_key(L"Thirdperson", V_KEYS_ON_TOGGLE_THIRDPERSON);
			});

			add_sub_tab(L"Other", [&]() {
				add_sub_sub_key(L"Menu", V_KEYS_ON_TOGGLE_UI);
				add_sub_sub_key(L"Panic", V_KEYS_ON_TOGGLE_PANIC);
			});
		});

		add_tab(L"On Hold", [&]() {
			add_sub_tab(L"Misc", [&]() {
				add_sub_sub_key(L"Blockbot", V_KEYS_ON_HOLD_BLOCKBOT);
			});
		});
	}, true);

	add(L"Load Settings", [&]() {
		for (const auto& cfg : cfg_list) {
			add_function(cfg, [cfg]() {
				config_manager::load_config(cfg);
			});
		}
	});

	add(L"Save Settings", [&]() {
		for (const auto& cfg : cfg_list) {
			add_function(cfg, [cfg]() {
				config_manager::save_config(cfg);
			});
		}
	});
}

void ui::on_reset_sprites()
{
	for (int i = 0; i < maxUISprites; i++)
		m_sprites[i].on_reset();
}

void ui::on_reset_end_sprites()
{
	for (int i = 0; i < maxUISprites; i++)
		m_sprites[i].on_reset_end();
}