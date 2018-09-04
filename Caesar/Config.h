#pragma once

#include <string>

class Config {
private:
    std::string path;
public:
    Config(const std::string&);
    // void init();
    void load();
    void save();

    bool hide_from_obs = false;

    struct {
        bool enabled = false;
        bool teammates = false;
        bool delayShot = false;
        float targetSelection = 3.0f;
        float hitbox = 1.0f;
        float multiPoint = 0.0f;
        bool penetration = false;
        bool silent = false;
        bool perfectSilent = false;
        bool autoscope = false;
    } aimbot;

    bool quick_stop = false;
    bool quick_stop_duck = false;

    struct {
        bool enabled = false;
        bool whileShooting = false;
        float type = 3.0f;
        float move = 3.0f;
        float variance = 0.0f;
        float limit = 0.0f;
    } fakelag;

    struct {
        float volume = 0.0f;
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    } brightness;

    bool autopistol = false;
    bool autoreload = false;
    bool fastzoom = false;

    bool nosmoke = false;
    bool remove_scope = false;

    struct {
        bool enabled = false;
        float r = 255.0f;
        float g = 255.0f;
        float b = 255.0f;
    } crosshair;
  

    float thirdperson = 0.0f;

    bool disable_render_teammates = false;

    bool bullets_trace = false;

    float noflash = 0.0f;

    bool esp = false;
    bool esp_behind = false;
    bool esp_teammates = false;

    bool esp_box = false;
    float esp_box_ct_vis_r = 0.0f;
    float esp_box_ct_vis_g = 100.0f;
    float esp_box_ct_vis_b = 255.0f;
    float esp_box_t_vis_r = 255.0f;
    float esp_box_t_vis_g = 100.0f;
    float esp_box_t_vis_b = 0.0f;
    float esp_box_ct_invis_r = 0.0f;
    float esp_box_ct_invis_g = 255.0f;
    float esp_box_ct_invis_b = 255.0f;
    float esp_box_t_invis_r = 255.0f;
    float esp_box_t_invis_g = 255.0f;
    float esp_box_t_invis_b = 0.0f;
    float esp_box_friends_r = 0.0f;
    float esp_box_friends_g = 255.0f;
    float esp_box_friends_b = 0.0f;

    bool esp_box_outline = false;
    bool esp_name = false;

    bool esp_fake = false;
    bool bypass_trace_blockers = true;
    bool bypass_valid_blockers = false;
    float esp_sound_minimum_volume = 0.0f;

    float esp_weapon = 1.0f;
    float esp_weapon_r = 255.0f;
    float esp_weapon_g = 0.0f;
    float esp_weapon_b = 255.0f;

    float esp_world_weapon = 1.0f;
    float esp_world_weapon_r = 255.0f;
    float esp_world_weapon_g = 255.0f;
    float esp_world_weapon_b = 255.0f;

    bool esp_flags = false;
    bool esp_distance = false;
    bool esp_hitboxes = false;
    bool esp_sound = false;
    bool esp_health = false;

    float esp_alpha = 200.0f;

    bool esp_line_of_sight = false;
    float esp_line_of_sight_r = 255.0f;
    float esp_line_of_sight_g = 255.0f;
    float esp_line_of_sight_b = 255.0f;

    bool esp_screen = false;

    bool esp_shots_fired = false;

    bool esp_bomb = false;
    float esp_bomb_r = 255.0f;
    float esp_bomb_g = 0.0f;
    float esp_bomb_b = 0.0f;

    bool hud_clear = false;

    bool penetration_info = false;

    float recoil_overlay_r = 255.0f;
    float recoil_overlay_g = 255.0f;
    float recoil_overlay_b = 0.0f;

    float spread_overlay_r = 255.0f;
    float spread_overlay_g = 0.0f;
    float spread_overlay_b = 0.0f;

    bool grenade_trajectory = false;

    bool chams = false;
    bool chams_behind_wall = false;
    float chams_type = 3.0f;

    float chams_t_vis_r = 255.0f;
    float chams_t_vis_g = 100.0f;
    float chams_t_vis_b = 0.0f;

    float chams_t_invis_r = 255.0f;
    float chams_t_invis_g = 255.0f;
    float chams_t_invis_b = 0.0f;

    float chams_ct_vis_r = 0.0f;
    float chams_ct_vis_g = 100.0f;
    float chams_ct_vis_b = 255.0f;

    float chams_ct_invis_r = 0.0f;
    float chams_ct_invis_g = 255.0f;
    float chams_ct_invis_b = 255.0f;

    bool glow_players = false;

    float glow_players_ct_r = 0.0f;
    float glow_players_ct_g = 0.0f;
    float glow_players_ct_b = 255.0f;

    float glow_players_t_r = 255.0f;
    float glow_players_t_g = 0.0f;
    float glow_players_t_b = 0.0f;

    bool spread_overlay = false;
    bool spread_overlay_old = false;
    bool recoil_overlay = false;

    bool draw_aim_fov = false;
    float draw_aim_fov_r = 255.0f;
    float draw_aim_fov_g = 255.0f;
    float draw_aim_fov_b = 0.0f;

    bool norecoil = false;
    bool norecoil_visual = false;

    bool nospread = false;
    float nospread_method = 1.0f;

    float aa_yaw_while_running = 0.0f;
    float aa_yaw = 0.0f;
    float aa_yaw_static = 0.0f;
    float aa_pitch = 0.0f;
    float aa_edge = 0.0f;

    bool legit_teammates = false;
    bool trigger_only_zoomed = false;
    float block_attack_after_kill = 0.0f;
    int trigger_key = -1;

    float menu_legit_global_section = 1.0f;
    float menu_legit_sub_section = 1.0f;

    int menu_key = 45;

    float menu_color_r = 215.0f;
    float menu_color_g = 111.0f;
    float menu_color_b = 234.0f;

    bool bunnyhop = false;
    bool knifebot = false;

    float name_stealer = 0.0f;

    bool debug = false;

    struct legit_weapons {
        bool aim;
        bool aim_head;
        bool aim_chest;
        bool aim_stomach;
        bool aim_quick_stop;
        bool aim_humanize;
        bool aim_spread_compenstation;
        float aim_accuracy;
        float aim_psilent;
        float aim_fov;
        float aim_speed;
        float aim_speed_in_attack;
        float aim_speed_scale_fov;
        float aim_recoil_compensation_pitch;
        float aim_recoil_compensation_yaw;
        float aim_recoil_compensation_after_shots_fired;
        float aim_reaction_time;

        bool trigger;
        bool trigger_head;
        bool trigger_chest;
        bool trigger_stomach;
        bool trigger_penetration;
        float trigger_accuracy;
    } legit[31];
};