#include <fstream>

#include "json/json.h"

#include "Config.h"

Config::Config(const std::string& name)
{

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
    

}
