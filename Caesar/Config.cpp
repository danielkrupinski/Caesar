#include <fstream>
#include <ShlObj.h>
//#include <windef.h>

#include "json/json.h"

#include "Config.h"

Config::Config(const std::string& name)
{
    char buff[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, buff))) {
        path = buff + '\\' + name;
    }
}

void Config::init()
{
    hide_from_obs = false;

    aim = false;
    aim_teammates = false;
    aim_delay_shot = false;
    aim_target_selection = 3;
    aim_hitbox = 1;
    aim_multi_point = 0;
    aim_penetration = false;
    aim_silent = false;
    aim_perfect_silent = false;
    aim_autoscope = false;

    fakelag = false;
    fakelag_while_shooting = false;
    fakelag_type = 3;
    fakelag_move = 3;
    fakelag_variance = 0;
    fakelag_limit = 0;

    brightness = 0;
    brightness_r = 0;
    brightness_g = 0;
    brightness_b = 0;

    quick_stop = false;
    quick_stop_duck = false;

    autopistol = false;
    autoreload = false;
    fastzoom = false;

    nosmoke = false;
    remove_scope = false;
    crosshair = false;

    crosshair_r = 255;
    crosshair_g = 255;
    crosshair_b = 255;

    noflash = 0;
    thirdperson = 0;
    disable_render_teammates = false;
    bullets_trace = false;

    esp = false;
    esp_behind = false;
    esp_teammates = false;

    esp_box = false;
    esp_box_ct_vis_r = 0;
    esp_box_ct_vis_g = 100;
    esp_box_ct_vis_b = 255;
    esp_box_t_vis_r = 255;
    esp_box_t_vis_g = 100;
    esp_box_t_vis_b = 0;
    esp_box_ct_invis_r = 0;
    esp_box_ct_invis_g = 255;
    esp_box_ct_invis_b = 255;
    esp_box_t_invis_r = 255;
    esp_box_t_invis_g = 255;
    esp_box_t_invis_b = 0;
    esp_box_friends_r = 0;
    esp_box_friends_g = 255;
    esp_box_friends_b = 0;

    esp_box_outline = false;
    esp_name = false;

    esp_fake = false;
    bypass_trace_blockers = true;
    bypass_valid_blockers = false;
    esp_sound_minimum_volume = 0;

    esp_weapon = 1;
    esp_weapon_r = 255;
    esp_weapon_g = 0;
    esp_weapon_b = 255;

    esp_world_weapon = 1;
    esp_world_weapon_r = 255;
    esp_world_weapon_g = 255;
    esp_world_weapon_b = 255;

    esp_shots_fired = false;

    esp_flags = false;
    esp_distance = false;
    esp_hitboxes = false;
    esp_sound = false;
    esp_health = false;

    esp_alpha = 200;

    esp_line_of_sight = false;

    esp_line_of_sight_r = 255;
    esp_line_of_sight_g = 255;
    esp_line_of_sight_b = 255;

    esp_screen = false;

    esp_bomb = false;
    esp_bomb_r = 255;
    esp_bomb_g = 0;
    esp_bomb_b = 0;

    grenade_trajectory = false;

    glow_players = false;

    glow_players_ct_r = 0;
    glow_players_ct_g = 0;
    glow_players_ct_b = 255;

    glow_players_t_r = 255;
    glow_players_t_g = 0;
    glow_players_t_b = 0;

    hud_clear = false;

    penetration_info = false;

    recoil_overlay_r = 255;
    recoil_overlay_g = 255;
    recoil_overlay_b = 0;

    spread_overlay_r = 255;
    spread_overlay_g = 0;
    spread_overlay_b = 0;

    chams = false;
    chams_behind_wall = false;
    chams_type = 3;

    chams_t_vis_r = 255;
    chams_t_vis_g = 100;
    chams_t_vis_b = 0;

    chams_t_invis_r = 255;
    chams_t_invis_g = 255;
    chams_t_invis_b = 0;

    chams_ct_vis_r = 0;
    chams_ct_vis_g = 100;
    chams_ct_vis_b = 255;

    chams_ct_invis_r = 0;
    chams_ct_invis_g = 255;
    chams_ct_invis_b = 255;

    spread_overlay = false;
    spread_overlay_old = false;
    recoil_overlay = false;

    draw_aim_fov = false;
    draw_aim_fov_r = 255;
    draw_aim_fov_g = 255;
    draw_aim_fov_b = 0;

    norecoil = false;
    norecoil_visual = false;

    nospread = false;
    nospread_method = 1;

    aa_yaw_while_running = 0;
    aa_yaw = 0;
    aa_yaw_static = 0;
    aa_pitch = 0;
    aa_edge = 0;

    legit_teammates = false;
    trigger_only_zoomed = false;
    block_attack_after_kill = 0;
    trigger_key = -1;

    menu_legit_global_section = 1;
    menu_legit_sub_section = 1;
    menu_key = 45;
    menu_color_r = 215;
    menu_color_g = 111;
    menu_color_b = 234;

    bunnyhop = false;
    knifebot = false;

    name_stealer = false;

    debug = false;
}

void Config::load()
{
    std::ifstream in{ path };

    if (!in.is_open())
        return;

    Json::Value config;
    in >> config;



}

void Config::save()
{
    std::ofstream out{ path };

    if (!out.is_open())
        return;

    Json::Value config;

    config["hide_from_obs"] = hide_from_obs;
    config["aim"] = aim;
    config["aim_teammates"] = aim_teammates;
    config["aim_delay_shot"] = aim_delay_shot;
    config["aim_target_selection"] = aim_target_selection;
    config["aim_hitbox"] = aim_hitbox;
    config["aim_multi_point"] = aim_multi_point;
    config["aim_penetration"] = aim_penetration;
    config["aim_silent"] = aim_silent;
    config["aim_perfect_silent"] = aim_perfect_silent;
    config["aim_autoscope"] = aim_autoscope;
    config["quick_stop"] = quick_stop;
    config["quick_stop_duck"] = quick_stop_duck;
    config["fakelag"] = fakelag;
    config["fakelag_while_shooting"] = fakelag_while_shooting;
    config["fakelag_type"] = fakelag_type;
    config["fakelag_move"] = fakelag_move;
    config["fakelag_variance"] = fakelag_variance;
    config["fakelag_limit"] = fakelag_limit;
    config["brightness"] = brightness;
    config["brightness_r"] = brightness_r;
    config["brightness_g"] = brightness_g;
    config["brightness_b"] = brightness_b;

    /*
    config["fakelag_type"] = fakelag_type;
    config["fakelag_type"] = fakelag_type;
    config["fakelag_type"] = fakelag_type;
    config["fakelag_type"] = fakelag_type;
    config["fakelag_type"] = fakelag_type;
    config["fakelag_type"] = fakelag_type;

    */
    bool autopistol;
    bool autoreload;
    bool fastzoom;

    bool nosmoke;
    bool remove_scope;
    bool crosshair;

    float crosshair_r;
    float crosshair_g;
    float crosshair_b;

    float thirdperson;

    bool disable_render_teammates;

    bool bullets_trace;

    float noflash;

    bool esp;
    bool esp_behind;
    bool esp_teammates;

    bool esp_box;
    float esp_box_ct_vis_r;
    float esp_box_ct_vis_g;
    float esp_box_ct_vis_b;
    float esp_box_t_vis_r;
    float esp_box_t_vis_g;
    float esp_box_t_vis_b;
    float esp_box_ct_invis_r;
    float esp_box_ct_invis_g;
    float esp_box_ct_invis_b;
    float esp_box_t_invis_r;
    float esp_box_t_invis_g;
    float esp_box_t_invis_b;
    float esp_box_friends_r;
    float esp_box_friends_g;
    float esp_box_friends_b;

    bool esp_box_outline;
    bool esp_name;

    bool esp_fake;
    bool bypass_trace_blockers;
    bool bypass_valid_blockers;
    float esp_sound_minimum_volume;

    float esp_weapon;
    float esp_weapon_r;
    float esp_weapon_g;
    float esp_weapon_b;

    float esp_world_weapon;
    float esp_world_weapon_r;
    float esp_world_weapon_g;
    float esp_world_weapon_b;

    bool esp_flags;
    bool esp_distance;
    bool esp_hitboxes;
    bool esp_sound;
    bool esp_health;

    float esp_alpha;

    bool esp_line_of_sight;
    float esp_line_of_sight_r;
    float esp_line_of_sight_g;
    float esp_line_of_sight_b;

    bool esp_screen;

    bool esp_shots_fired;

    bool esp_bomb;
    float esp_bomb_r;
    float esp_bomb_g;
    float esp_bomb_b;

    bool hud_clear;

    bool penetration_info;

    float recoil_overlay_r;
    float recoil_overlay_g;
    float recoil_overlay_b;

    float spread_overlay_r;
    float spread_overlay_g;
    float spread_overlay_b;

    bool grenade_trajectory;

    bool chams;
    bool chams_behind_wall;
    float chams_type;

    float chams_t_vis_r;
    float chams_t_vis_g;
    float chams_t_vis_b;

    float chams_t_invis_r;
    float chams_t_invis_g;
    float chams_t_invis_b;

    float chams_ct_vis_r;
    float chams_ct_vis_g;
    float chams_ct_vis_b;

    float chams_ct_invis_r;
    float chams_ct_invis_g;
    float chams_ct_invis_b;

    bool glow_players;

    float glow_players_ct_r;
    float glow_players_ct_g;
    float glow_players_ct_b;

    float glow_players_t_r;
    float glow_players_t_g;
    float glow_players_t_b;

    bool spread_overlay;
    bool spread_overlay_old;
    bool recoil_overlay;

    bool draw_aim_fov;
    float draw_aim_fov_r;
    float draw_aim_fov_g;
    float draw_aim_fov_b;

    bool norecoil;
    bool norecoil_visual;

    bool nospread;
    float nospread_method;

    float aa_yaw_while_running;
    float aa_yaw;
    float aa_yaw_static;
    float aa_pitch;
    float aa_edge;

    bool legit_teammates;
    bool trigger_only_zoomed;
    float block_attack_after_kill;
    int trigger_key;

    float menu_legit_global_section;
    float menu_legit_sub_section;

    int menu_key;

    float menu_color_r;
    float menu_color_g;
    float menu_color_b;

    bool bunnyhop;
    bool knifebot;

    float name_stealer;

    bool debug;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;
    config["aim"] = aim;

}

