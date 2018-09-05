#include <fstream>
#include <ShlObj.h>

#include "json/json.h"

#include "Config.h"

Config config{ "Caesar.json" };

Config::Config(const std::string& name)
{
    char buff[MAX_PATH]{ }; // Default initialization to zero array as the array is placed on stack
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, buff))) {
        path = buff + std::string{ '\\' } +name;
    }
}

void Config::load()
{
    std::ifstream in{ path };

    if (!in.is_open())
        return;

    Json::Value config;
    in >> config;

    hide_from_obs = config["hide_from_obs"].asBool();
    aimbot.enabled = config["aimbot"]["enabled"].asBool();
    aimbot.teammates = config["aimbot"]["teammates"].asBool();
    aimbot.delayShot = config["aimbot"]["delayShot"].asBool();
    aimbot.targetSelection = config["aimbot"]["targetSelection"].asFloat();
    aimbot.hitbox = config["aimbot"]["hitbox"].asFloat();
    aimbot.multiPoint = config["aimbot"]["multiPoint"].asFloat();
    aimbot.penetration = config["aimbot"]["penetration"].asBool();
    aimbot.silent = config["aimbot"]["silent"].asBool();
    aimbot.perfectSilent = config["aimbot"]["perfectSilent"].asBool();
    aimbot.autoscope = config["aimbot"]["autoscope"].asBool();
    quick_stop = config["quick_stop"].asBool();
    quick_stop_duck = config["quick_stop_duck"].asBool();
    fakelag.enabled = config["fakelag"]["enabled"].asBool();
    fakelag.whileShooting = config["fakelag"]["whileShooting"].asBool();
    fakelag.type = config["fakelag"]["type"].asFloat();
    fakelag.move = config["fakelag"]["move"].asFloat();
    fakelag.variance = config["fakelag"]["variance"].asFloat();
    fakelag.limit = config["fakelag"]["limit"].asFloat();
    brightness.volume = config["brightness"]["volume"].asFloat();
    brightness.r = config["brightness"]["r"].asFloat();
    brightness.g = config["brightness"]["g"].asFloat();
    brightness.b = config["brightness"]["b"].asFloat();
    autopistol = config["autopistol"].asBool();
    autoreload = config["autoreload"].asBool();
    fastzoom = config["fastzoom"].asBool();
    nosmoke = config["nosmoke"].asBool();
    remove_scope = config["remove_scope"].asBool();
    crosshair.enabled = config["crosshair"]["enabled"].asBool();
    crosshair.r = config["crosshair"]["r"].asFloat();
    crosshair.g = config["crosshair"]["g"].asFloat();
    crosshair.b = config["crosshair"]["b"].asFloat();
    thirdperson = config["thirdperson"].asFloat();
    disable_render_teammates = config["disable_render_teammates"].asBool();
    bullets_trace = config["bullets_trace"].asBool();
    noflash = config["noflash"].asFloat();
    esp = config["esp"].asBool();
    esp_behind = config["esp_behind"].asBool();
    esp_teammates = config["esp_teammates"].asBool();
    esp_box = config["esp_box"].asBool();
    esp_box_ct_vis_r = config["esp_box_ct_vis_r"].asFloat();
    esp_box_ct_vis_g = config["esp_box_ct_vis_g"].asFloat();
    esp_box_ct_vis_b = config["esp_box_ct_vis_b"].asFloat();
    esp_box_t_vis_r = config["esp_box_t_vis_r"].asFloat();
    esp_box_t_vis_g = config["esp_box_t_vis_g"].asFloat();
    esp_box_t_vis_b = config["esp_box_t_vis_b"].asFloat();
    esp_box_ct_invis_r = config["esp_box_ct_invis_r"].asFloat();
    esp_box_ct_invis_g = config["esp_box_ct_invis_g"].asFloat();
    esp_box_ct_invis_b = config["esp_box_ct_invis_b"].asFloat();
    esp_box_t_invis_r = config["esp_box_t_invis_r"].asFloat();
    esp_box_t_invis_g = config["esp_box_t_invis_g"].asFloat();
    esp_box_t_invis_b = config["esp_box_t_invis_b"].asFloat();
    esp_box_friends_r = config["esp_box_friends_r"].asFloat();
    esp_box_friends_g = config["esp_box_friends_g"].asFloat();
    esp_box_friends_b = config["esp_box_friends_b"].asFloat();
    esp_box_outline = config["esp_box_outline"].asBool();
    esp_name = config["esp_name"].asBool();
    esp_fake = config["esp_fake"].asBool();
    bypass_trace_blockers = config["bypass_trace_blockers"].asBool();
    bypass_valid_blockers = config["bypass_valid_blockers"].asBool();
    esp_sound_minimum_volume = config["esp_sound_minimum_volume"].asFloat();
    esp_weapon = config["esp_weapon"].asFloat();
    esp_weapon_r = config["esp_weapon_r"].asFloat();
    esp_weapon_g = config["esp_weapon_g"].asFloat();
    esp_weapon_b = config["esp_weapon_b"].asFloat();
    esp_world_weapon = config["esp_world_weapon"].asFloat();
    esp_world_weapon_r = config["esp_world_weapon_r"].asFloat();
    esp_world_weapon_g = config["esp_world_weapon_g"].asFloat();
    esp_world_weapon_b = config["esp_world_weapon_b"].asFloat();
    esp_flags = config["esp_flags"].asBool();
    esp_distance = config["esp_distance"].asBool();
    esp_hitboxes = config["esp_hitboxes"].asBool();
    esp_sound = config["esp_sound"].asBool();
    esp_health = config["esp_health"].asBool();
    esp_alpha = config["esp_alpha"].asFloat();
    esp_line_of_sight = config["esp_line_of_sight"].asBool();
    esp_line_of_sight_r = config["esp_line_of_sight_r"].asFloat();
    esp_line_of_sight_g = config["esp_line_of_sight_g"].asFloat();
    esp_line_of_sight_b = config["esp_line_of_sight_b"].asFloat();
    esp_screen = config["esp_screen"].asBool();
    esp_shots_fired = config["esp_shots_fired"].asBool();
    esp_bomb = config["esp_bomb"].asBool();
    esp_bomb_r = config["esp_bomb_r"].asFloat();
    esp_bomb_g = config["esp_bomb_g"].asFloat();
    esp_bomb_b = config["esp_bomb_b"].asFloat();
    hud_clear = config["hud_clear"].asBool();
    penetration_info = config["penetration_info"].asBool();
    recoil_overlay_r = config["recoil_overlay_r"].asFloat();
    recoil_overlay_g = config["recoil_overlay_g"].asFloat();
    recoil_overlay_b = config["recoil_overlay_b"].asFloat();
    spread_overlay_r = config["spread_overlay_r"].asFloat();
    spread_overlay_g = config["spread_overlay_g"].asFloat();
    spread_overlay_b = config["spread_overlay_b"].asFloat();
    grenade_trajectory = config["grenade_trajectory"].asBool();
    chams = config["chams"].asBool();
    chams_behind_wall = config["chams_behind_wall"].asBool();
    chams_type = config["chams_type"].asFloat();
    chams_t_vis_r = config["chams_t_vis_r"].asFloat();
    chams_t_vis_g = config["chams_t_vis_g"].asFloat();
    chams_t_vis_b = config["chams_t_vis_b"].asFloat();
    chams_t_invis_r = config["chams_t_invis_r"].asFloat();
    chams_t_invis_g = config["chams_t_invis_g"].asFloat();
    chams_t_invis_b = config["chams_t_invis_b"].asFloat();
    chams_ct_vis_r = config["chams_ct_vis_r"].asFloat();
    chams_ct_vis_g = config["chams_ct_vis_g"].asFloat();
    chams_ct_vis_b = config["chams_ct_vis_b"].asFloat();
    chams_ct_invis_r = config["chams_ct_invis_r"].asFloat();
    chams_ct_invis_g = config["chams_ct_invis_g"].asFloat();
    chams_ct_invis_b = config["chams_ct_invis_b"].asFloat();
    glow_players = config["glow_players"].asBool();
    glow_players_ct_r = config["glow_players_ct_r"].asFloat();
    glow_players_ct_g = config["glow_players_ct_g"].asFloat();
    glow_players_ct_b = config["glow_players_ct_b"].asFloat();
    glow_players_t_r = config["glow_players_t_r"].asFloat();
    glow_players_t_g = config["glow_players_t_g"].asFloat();
    glow_players_t_b = config["glow_players_t_b"].asFloat();
    spread_overlay = config["spread_overlay"].asBool();
    spread_overlay_old = config["spread_overlay_old"].asBool();
    recoil_overlay = config["recoil_overlay"].asBool();
    draw_aim_fov = config["draw_aim_fov"].asBool();
    draw_aim_fov_r = config["draw_aim_fov_r"].asFloat();
    draw_aim_fov_g = config["draw_aim_fov_g"].asFloat();
    draw_aim_fov_b = config["draw_aim_fov_b"].asFloat();
    norecoil = config["norecoil"].asBool();
    norecoil_visual = config["norecoil_visual"].asBool();
    nospread = config["nospread"].asBool();
    nospread_method = config["nospread_method"].asFloat();
    aa_yaw_while_running = config["aa_yaw_while_running"].asFloat();
    aa_yaw = config["aa_yaw"].asFloat();
    aa_yaw_static = config["aa_yaw_static"].asFloat();
    aa_pitch = config["aa_pitch"].asFloat();
    aa_edge = config["aa_edge"].asFloat();
    legit_teammates = config["legit_teammates"].asBool();
    trigger_only_zoomed = config["trigger_only_zoomed"].asBool();
    block_attack_after_kill = config["block_attack_after_kill"].asFloat();
    trigger_key = config["trigger_key"].asInt();
    menu_legit_global_section = config["menu_legit_global_section"].asFloat();
    menu_legit_sub_section = config["menu_legit_sub_section"].asFloat();
    menu_key = config["menu_key"].asInt();
    menu_color_r = config["menu_color_r"].asFloat();
    menu_color_g = config["menu_color_g"].asFloat();
    menu_color_b = config["menu_color_b"].asFloat();
    bunnyhop = config["bunnyhop"].asBool();
    knifebot = config["knifebot"].asBool();
    name_stealer = config["name_stealer"].asFloat();
    debug = config["debug"].asBool();

    for (int i = 1; i < 31; i++) {
        if (i == 2 || i == 4 || i == 6 || i == 9 || i == 25)
            continue;

        std::string weaponName = "weapon_" + std::to_string(i);

        legit[i].aim = config[weaponName]["aim"].asBool();
        legit[i].aim_head = config[weaponName]["aim_head"].asBool();
        legit[i].aim_chest = config[weaponName]["aim_chest"].asBool();
        legit[i].aim_stomach = config[weaponName]["aim_stomach"].asBool();
        legit[i].aim_quick_stop = config[weaponName]["aim_quick_stop"].asBool();
        legit[i].aim_humanize = config[weaponName]["aim_humanize"].asBool();
        legit[i].aim_spread_compenstation = config[weaponName]["aim_spread_compenstation"].asBool();
        legit[i].aim_accuracy = config[weaponName]["aim_accuracy"].asFloat();
        legit[i].aim_psilent = config[weaponName]["aim_psilent"].asFloat();
        legit[i].aim_fov = config[weaponName]["aim_fov"].asFloat();
        legit[i].aim_speed = config[weaponName]["aim_speed"].asFloat();
        legit[i].aim_speed_in_attack = config[weaponName]["aim_speed_in_attack"].asFloat();
        legit[i].aim_speed_scale_fov = config[weaponName]["aim_speed_scale_fov"].asFloat();
        legit[i].aim_recoil_compensation_pitch = config[weaponName]["aim_recoil_compensation_pitch"].asFloat();
        legit[i].aim_recoil_compensation_yaw = config[weaponName]["aim_recoil_compensation_yaw"].asFloat();
        legit[i].aim_recoil_compensation_after_shots_fired = config[weaponName]["aim_recoil_compensation_after_shots_fired"].asFloat();
        legit[i].aim_reaction_time = config[weaponName]["aim_reaction_time"].asFloat();
        legit[i].trigger = config[weaponName]["trigger"].asBool();
        legit[i].trigger_head = config[weaponName]["trigger_head"].asBool();
        legit[i].trigger_chest = config[weaponName]["trigger_chest"].asBool();
        legit[i].trigger_stomach = config[weaponName]["trigger_stomach"].asBool();
        legit[i].trigger_penetration = config[weaponName]["trigger_penetration"].asBool();
        legit[i].trigger_accuracy = config[weaponName]["trigger_accuracy"].asFloat();
    }

    in.close();
}

void Config::save()
{
    std::ofstream out{ path };

    if (!out.is_open())
        return;

    Json::Value config;

    config["hide_from_obs"] = hide_from_obs;
    config["aimbot"]["enabled"] = aimbot.enabled;
    config["aimbot"]["teammates"] = aimbot.teammates;
    config["aimbot"]["delayShot"] = aimbot.delayShot;
    config["aimbot"]["targetSelection"] = aimbot.targetSelection;
    config["aimbot"]["hitbox"] = aimbot.hitbox;
    config["aimbot"]["multiPoint"] = aimbot.multiPoint;
    config["aimbot"]["penetration"] = aimbot.penetration;
    config["aimbot"]["silent"] = aimbot.silent;
    config["aimbot"]["perfectSilent"] = aimbot.perfectSilent;
    config["aimbot"]["autoscope"] = aimbot.autoscope;
    config["quick_stop"] = quick_stop;
    config["quick_stop_duck"] = quick_stop_duck;
    config["fakelag"]["enabled"] = fakelag.enabled;
    config["fakelag"]["whileShooting"] = fakelag.whileShooting;
    config["fakelag"]["type"] = fakelag.type;
    config["fakelag"]["move"] = fakelag.move;
    config["fakelag"]["variance"] = fakelag.variance;
    config["fakelag"]["limit"] = fakelag.limit;
    config["brightness"]["volume"] = brightness.volume;
    config["brightness"]["r"] = brightness.r;
    config["brightness"]["g"] = brightness.g;
    config["brightness"]["b"] = brightness.b;
    config["autopistol"] = autopistol;
    config["autoreload"] = autoreload;
    config["fastzoom"] = fastzoom;
    config["nosmoke"] = nosmoke;
    config["remove_scope"] = remove_scope;
    config["crosshair"]["enabled"] = crosshair.enabled;
    config["crosshair"]["r"] = crosshair.r;
    config["crosshair"]["g"] = crosshair.g;
    config["crosshair"]["b"] = crosshair.b;
    config["thirdperson"] = thirdperson;
    config["disable_render_teammates"] = disable_render_teammates;
    config["bullets_trace"] = bullets_trace;
    config["noflash"] = noflash;
    config["esp"] = esp;
    config["esp_behind"] = esp_behind;
    config["esp_teammates"] = esp_teammates;
    config["esp_box"] = esp_box;
    config["esp_box_ct_vis_r"] = esp_box_ct_vis_r;
    config["esp_box_ct_vis_g"] = esp_box_ct_vis_g;
    config["esp_box_ct_vis_b"] = esp_box_ct_vis_b;
    config["esp_box_t_vis_r"] = esp_box_t_vis_r;
    config["esp_box_t_vis_g"] = esp_box_t_vis_g;
    config["esp_box_t_vis_b"] = esp_box_t_vis_b;
    config["esp_box_ct_invis_r"] = esp_box_ct_invis_r;
    config["esp_box_ct_invis_g"] = esp_box_ct_invis_g;
    config["esp_box_ct_invis_b"] = esp_box_ct_invis_b;
    config["esp_box_t_invis_r"] = esp_box_t_invis_r;
    config["esp_box_t_invis_g"] = esp_box_t_invis_g;
    config["esp_box_t_invis_b"] = esp_box_t_invis_b;
    config["esp_box_friends_r"] = esp_box_friends_r;
    config["esp_box_friends_g"] = esp_box_friends_g;
    config["esp_box_friends_b"] = esp_box_friends_b;
    config["esp_box_outline"] = esp_box_outline;
    config["esp_name"] = esp_name;
    config["esp_fake"] = esp_fake;
    config["bypass_trace_blockers"] = bypass_trace_blockers;
    config["bypass_valid_blockers"] = bypass_valid_blockers;
    config["esp_sound_minimum_volume"] = esp_sound_minimum_volume;
    config["esp_weapon"] = esp_weapon;
    config["esp_weapon_r"] = esp_weapon_r;
    config["esp_weapon_g"] = esp_weapon_g;
    config["esp_weapon_b"] = esp_weapon_b;
    config["esp_world_weapon"] = esp_world_weapon;
    config["esp_world_weapon_r"] = esp_world_weapon_r;
    config["esp_world_weapon_g"] = esp_world_weapon_g;
    config["esp_world_weapon_b"] = esp_world_weapon_b;
    config["esp_flags"] = esp_flags;
    config["esp_distance"] = esp_distance;
    config["esp_hitboxes"] = esp_hitboxes;
    config["esp_sound"] = esp_sound;
    config["esp_health"] = esp_health;
    config["esp_alpha"] = esp_alpha;
    config["esp_line_of_sight"] = esp_line_of_sight;
    config["esp_line_of_sight_r"] = esp_line_of_sight_r;
    config["esp_line_of_sight_g"] = esp_line_of_sight_g;
    config["esp_line_of_sight_b"] = esp_line_of_sight_b;
    config["esp_screen"] = esp_screen;
    config["esp_shots_fired"] = esp_shots_fired;
    config["esp_bomb"] = esp_bomb;
    config["esp_bomb_r"] = esp_bomb_r;
    config["esp_bomb_g"] = esp_bomb_g;
    config["esp_bomb_b"] = esp_bomb_b;
    config["hud_clear"] = hud_clear;
    config["penetration_info"] = penetration_info;
    config["recoil_overlay_r"] = recoil_overlay_r;
    config["recoil_overlay_g"] = recoil_overlay_g;
    config["recoil_overlay_b"] = recoil_overlay_b;
    config["spread_overlay_r"] = spread_overlay_r;
    config["spread_overlay_g"] = spread_overlay_g;
    config["spread_overlay_b"] = spread_overlay_b;
    config["grenade_trajectory"] = grenade_trajectory;
    config["chams"] = chams;
    config["chams_behind_wall"] = chams_behind_wall;
    config["chams_type"] = chams_type;
    config["chams_t_vis_r"] = chams_t_vis_r;
    config["chams_t_vis_g"] = chams_t_vis_g;
    config["chams_t_vis_b"] = chams_t_vis_b;
    config["chams_t_invis_r"] = chams_t_invis_r;
    config["chams_t_invis_g"] = chams_t_invis_g;
    config["chams_t_invis_b"] = chams_t_invis_b;
    config["chams_ct_vis_r"] = chams_ct_vis_r;
    config["chams_ct_vis_g"] = chams_ct_vis_g;
    config["chams_ct_vis_b"] = chams_ct_vis_b;
    config["chams_ct_invis_r"] = chams_ct_invis_r;
    config["chams_ct_invis_g"] = chams_ct_invis_g;
    config["chams_ct_invis_b"] = chams_ct_invis_b;
    config["glow_players"] = glow_players;
    config["glow_players_ct_r"] = glow_players_ct_r;
    config["glow_players_ct_g"] = glow_players_ct_g;
    config["glow_players_ct_b"] = glow_players_ct_b;
    config["glow_players_t_r"] = glow_players_t_r;
    config["glow_players_t_g"] = glow_players_t_g;
    config["glow_players_t_b"] = glow_players_t_b;
    config["spread_overlay"] = spread_overlay;
    config["spread_overlay_old"] = spread_overlay_old;
    config["recoil_overlay"] = recoil_overlay;
    config["draw_aim_fov"] = draw_aim_fov;
    config["draw_aim_fov_r"] = draw_aim_fov_r;
    config["draw_aim_fov_g"] = draw_aim_fov_g;
    config["draw_aim_fov_b"] = draw_aim_fov_b;
    config["norecoil"] = norecoil;
    config["norecoil_visual"] = norecoil_visual;
    config["nospread"] = nospread;
    config["nospread_method"] = nospread_method;
    config["aa_yaw_while_running"] = aa_yaw_while_running;
    config["aa_yaw"] = aa_yaw;
    config["aa_yaw_static"] = aa_yaw_static;
    config["aa_pitch"] = aa_pitch;
    config["aa_edge"] = aa_edge;
    config["legit_teammates"] = legit_teammates;
    config["trigger_only_zoomed"] = trigger_only_zoomed;
    config["block_attack_after_kill"] = block_attack_after_kill;
    config["trigger_key"] = trigger_key;
    config["menu_legit_global_section"] = menu_legit_global_section;
    config["menu_legit_sub_section"] = menu_legit_sub_section;
    config["menu_key"] = menu_key;
    config["menu_color_r"] = menu_color_r;
    config["menu_color_g"] = menu_color_g;
    config["menu_color_b"] = menu_color_b;
    config["bunnyhop"] = bunnyhop;
    config["knifebot"] = knifebot;
    config["name_stealer"] = name_stealer;
    config["debug"] = debug;

    for (int i = 1; i < 31; i++) {
        if (i == 2 || i == 4 || i == 6 || i == 9 || i == 25)
            continue;

        std::string weaponName = "weapon_" + std::to_string(i);

        config[weaponName]["aim"] = legit[i].aim;
        config[weaponName]["aim_head"] = legit[i].aim_head;
        config[weaponName]["aim_chest"] = legit[i].aim_chest;
        config[weaponName]["aim_stomach"] = legit[i].aim_stomach;
        config[weaponName]["aim_quick_stop"] = legit[i].aim_quick_stop;
        config[weaponName]["aim_humanize"] = legit[i].aim_humanize;
        config[weaponName]["aim_spread_compenstation"] = legit[i].aim_spread_compenstation;
        config[weaponName]["aim_accuracy"] = legit[i].aim_accuracy;
        config[weaponName]["aim_psilent"] = legit[i].aim_psilent;
        config[weaponName]["aim_fov"] = legit[i].aim_fov;
        config[weaponName]["aim_speed"] = legit[i].aim_speed;
        config[weaponName]["aim_speed_in_attack"] = legit[i].aim_speed_in_attack;
        config[weaponName]["aim_speed_scale_fov"] = legit[i].aim_speed_scale_fov;
        config[weaponName]["aim_recoil_compensation_pitch"] = legit[i].aim_recoil_compensation_pitch;
        config[weaponName]["aim_recoil_compensation_yaw"] = legit[i].aim_recoil_compensation_yaw;
        config[weaponName]["aim_recoil_compensation_after_shots_fired"] = legit[i].aim_recoil_compensation_after_shots_fired;
        config[weaponName]["aim_reaction_time"] = legit[i].aim_reaction_time;
        config[weaponName]["trigger"] = legit[i].trigger;
        config[weaponName]["trigger_head"] = legit[i].trigger_head;
        config[weaponName]["trigger_chest"] = legit[i].trigger_chest;
        config[weaponName]["trigger_stomach"] = legit[i].trigger_stomach;
        config[weaponName]["trigger_penetration"] = legit[i].trigger_penetration;
        config[weaponName]["trigger_accuracy"] = legit[i].trigger_accuracy;
    }

    out << config;
    out.close();
}
