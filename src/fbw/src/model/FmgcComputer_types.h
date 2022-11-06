#ifndef RTW_HEADER_FmgcComputer_types_h_
#define RTW_HEADER_FmgcComputer_types_h_
#include "rtwtypes.h"

#ifndef DEFINED_TYPEDEF_FOR_SignStatusMatrix_
#define DEFINED_TYPEDEF_FOR_SignStatusMatrix_

enum class SignStatusMatrix
  : int32_T {
  FailureWarning = 0,
  NoComputedData,
  FunctionalTest,
  NormalOperation
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_time_
#define DEFINED_TYPEDEF_FOR_base_time_

struct base_time
{
  real_T dt;
  real_T simulation_time;
  real_T monotonic_time;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_sim_data_
#define DEFINED_TYPEDEF_FOR_base_sim_data_

struct base_sim_data
{
  boolean_T slew_on;
  boolean_T pause_on;
  boolean_T tracking_mode_on_override;
  boolean_T tailstrike_protection_on;
  boolean_T computer_running;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_discrete_inputs_
#define DEFINED_TYPEDEF_FOR_base_fmgc_discrete_inputs_

struct base_fmgc_discrete_inputs
{
  boolean_T is_unit_1;
  boolean_T athr_opp_engaged;
  boolean_T fcu_athr_button;
  boolean_T athr_instinctive_disc;
  boolean_T fd_opp_engd;
  boolean_T ap_opp_engaged;
  boolean_T fcu_ap_button;
  boolean_T ap_instinctive_disc;
  boolean_T powersupply_split;
  boolean_T fcu_opp_healthy;
  boolean_T fcu_own_healthy;
  boolean_T fac_opp_healthy;
  boolean_T fac_own_healthy;
  boolean_T fmgc_opp_healthy;
  boolean_T mcdu_opp_fail;
  boolean_T mcdu_own_fail;
  boolean_T nav_control_opp;
  boolean_T nav_control_own;
  boolean_T fwc_opp_valid;
  boolean_T fwc_own_valid;
  boolean_T pfd_opp_valid;
  boolean_T pfd_own_valid;
  boolean_T adc_3_switch;
  boolean_T att_3_switch;
  boolean_T left_wheel_spd_abv_70_kts;
  boolean_T right_wheel_spd_abv_70_kts;
  boolean_T bscu_opp_valid;
  boolean_T bscu_own_valid;
  boolean_T nose_gear_pressed_opp;
  boolean_T nose_gear_pressed_own;
  boolean_T elac_opp_ap_disc;
  boolean_T elac_own_ap_disc;
  boolean_T eng_opp_stop;
  boolean_T eng_own_stop;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fms_inputs_
#define DEFINED_TYPEDEF_FOR_base_fms_inputs_

struct base_fms_inputs
{
  boolean_T fm_valid;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_arinc_429_
#define DEFINED_TYPEDEF_FOR_base_arinc_429_

struct base_arinc_429
{
  uint32_T SSM;
  real32_T Data;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fac_bus_
#define DEFINED_TYPEDEF_FOR_base_fac_bus_

struct base_fac_bus
{
  base_arinc_429 discrete_word_1;
  base_arinc_429 gamma_a_deg;
  base_arinc_429 gamma_t_deg;
  base_arinc_429 total_weight_lbs;
  base_arinc_429 center_of_gravity_pos_percent;
  base_arinc_429 sideslip_target_deg;
  base_arinc_429 fac_slat_angle_deg;
  base_arinc_429 fac_flap_angle;
  base_arinc_429 discrete_word_2;
  base_arinc_429 rudder_travel_limit_command_deg;
  base_arinc_429 delta_r_yaw_damper_deg;
  base_arinc_429 estimated_sideslip_deg;
  base_arinc_429 v_alpha_lim_kn;
  base_arinc_429 v_ls_kn;
  base_arinc_429 v_stall_kn;
  base_arinc_429 v_alpha_prot_kn;
  base_arinc_429 v_stall_warn_kn;
  base_arinc_429 speed_trend_kn;
  base_arinc_429 v_3_kn;
  base_arinc_429 v_4_kn;
  base_arinc_429 v_man_kn;
  base_arinc_429 v_max_kn;
  base_arinc_429 v_fe_next_kn;
  base_arinc_429 discrete_word_3;
  base_arinc_429 discrete_word_4;
  base_arinc_429 discrete_word_5;
  base_arinc_429 delta_r_rudder_trim_deg;
  base_arinc_429 rudder_trim_pos_deg;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_adr_bus_
#define DEFINED_TYPEDEF_FOR_base_adr_bus_

struct base_adr_bus
{
  base_arinc_429 altitude_standard_ft;
  base_arinc_429 altitude_corrected_ft;
  base_arinc_429 mach;
  base_arinc_429 airspeed_computed_kn;
  base_arinc_429 airspeed_true_kn;
  base_arinc_429 vertical_speed_ft_min;
  base_arinc_429 aoa_corrected_deg;
  base_arinc_429 corrected_average_static_pressure;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_ir_bus_
#define DEFINED_TYPEDEF_FOR_base_ir_bus_

struct base_ir_bus
{
  base_arinc_429 discrete_word_1;
  base_arinc_429 latitude_deg;
  base_arinc_429 longitude_deg;
  base_arinc_429 ground_speed_kn;
  base_arinc_429 track_angle_true_deg;
  base_arinc_429 heading_true_deg;
  base_arinc_429 wind_speed_kn;
  base_arinc_429 wind_direction_true_deg;
  base_arinc_429 track_angle_magnetic_deg;
  base_arinc_429 heading_magnetic_deg;
  base_arinc_429 drift_angle_deg;
  base_arinc_429 flight_path_angle_deg;
  base_arinc_429 flight_path_accel_g;
  base_arinc_429 pitch_angle_deg;
  base_arinc_429 roll_angle_deg;
  base_arinc_429 body_pitch_rate_deg_s;
  base_arinc_429 body_roll_rate_deg_s;
  base_arinc_429 body_yaw_rate_deg_s;
  base_arinc_429 body_long_accel_g;
  base_arinc_429 body_lat_accel_g;
  base_arinc_429 body_normal_accel_g;
  base_arinc_429 track_angle_rate_deg_s;
  base_arinc_429 pitch_att_rate_deg_s;
  base_arinc_429 roll_att_rate_deg_s;
  base_arinc_429 inertial_alt_ft;
  base_arinc_429 along_track_horiz_acc_g;
  base_arinc_429 cross_track_horiz_acc_g;
  base_arinc_429 vertical_accel_g;
  base_arinc_429 inertial_vertical_speed_ft_s;
  base_arinc_429 north_south_velocity_kn;
  base_arinc_429 east_west_velocity_kn;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcdc_bus_
#define DEFINED_TYPEDEF_FOR_base_fcdc_bus_

struct base_fcdc_bus
{
  base_arinc_429 efcs_status_word_1;
  base_arinc_429 efcs_status_word_2;
  base_arinc_429 efcs_status_word_3;
  base_arinc_429 efcs_status_word_4;
  base_arinc_429 efcs_status_word_5;
  base_arinc_429 capt_roll_command_deg;
  base_arinc_429 fo_roll_command_deg;
  base_arinc_429 rudder_pedal_position_deg;
  base_arinc_429 capt_pitch_command_deg;
  base_arinc_429 fo_pitch_command_deg;
  base_arinc_429 aileron_left_pos_deg;
  base_arinc_429 elevator_left_pos_deg;
  base_arinc_429 aileron_right_pos_deg;
  base_arinc_429 elevator_right_pos_deg;
  base_arinc_429 horiz_stab_trim_pos_deg;
  base_arinc_429 spoiler_1_left_pos_deg;
  base_arinc_429 spoiler_2_left_pos_deg;
  base_arinc_429 spoiler_3_left_pos_deg;
  base_arinc_429 spoiler_4_left_pos_deg;
  base_arinc_429 spoiler_5_left_pos_deg;
  base_arinc_429 spoiler_1_right_pos_deg;
  base_arinc_429 spoiler_2_right_pos_deg;
  base_arinc_429 spoiler_3_right_pos_deg;
  base_arinc_429 spoiler_4_right_pos_deg;
  base_arinc_429 spoiler_5_right_pos_deg;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_ra_bus_
#define DEFINED_TYPEDEF_FOR_base_ra_bus_

struct base_ra_bus
{
  base_arinc_429 radio_height_ft;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_a_bus_
#define DEFINED_TYPEDEF_FOR_base_fmgc_a_bus_

struct base_fmgc_a_bus
{
  base_arinc_429 roll_fd_command;
  base_arinc_429 pitch_fd_command;
  base_arinc_429 yaw_fd_command;
  base_arinc_429 discrete_word_5;
  base_arinc_429 discrete_word_4;
  base_arinc_429 ats_discrete_word;
  base_arinc_429 ats_fma_discrete_word;
  base_arinc_429 discrete_word_3;
  base_arinc_429 discrete_word_1;
  base_arinc_429 discrete_word_2;
  base_arinc_429 discrete_word_6;
  base_arinc_429 delta_p_ail_voted_cmd_deg;
  base_arinc_429 delta_p_splr_voted_cmd_deg;
  base_arinc_429 delta_r_voted_cmd_deg;
  base_arinc_429 delta_nosewheel_voted_cmd_deg;
  base_arinc_429 delta_q_voted_cmd_deg;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_bus_
#define DEFINED_TYPEDEF_FOR_base_fcu_bus_

struct base_fcu_bus
{
  real_T selected_hdg_deg;
  real_T selected_alt_ft;
  real_T selected_spd_kts;
  real_T selected_vz_ft_min;
  real_T selected_mach;
  real_T selected_trk_deg;
  real_T selected_fpa_deg;
  real_T ats_fma_discrete_word;
  real_T fcu_flex_to_temp_deg_c;
  real_T ats_discrete_word;
  real_T eis_discrete_word_1_left;
  real_T eis_discrete_word_1_right;
  real_T eis_discrete_word_2_left;
  real_T eis_discrete_word_2_right;
  real_T fcu_discrete_word_2;
  real_T fcu_discrete_word_1;
  real_T n1_cmd_percent;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_bus_inputs_
#define DEFINED_TYPEDEF_FOR_base_fmgc_bus_inputs_

struct base_fmgc_bus_inputs
{
  base_fac_bus fac_opp_bus;
  base_fac_bus fac_own_bus;
  base_adr_bus adr_3_bus;
  base_ir_bus ir_3_bus;
  base_adr_bus adr_opp_bus;
  base_ir_bus ir_opp_bus;
  base_adr_bus adr_own_bus;
  base_ir_bus ir_own_bus;
  base_fcdc_bus fcdc_opp_bus;
  base_fcdc_bus fcdc_own_bus;
  base_ra_bus ra_opp_bus;
  base_ra_bus ra_own_bus;
  base_fmgc_a_bus fmgc_opp_bus;
  base_fcu_bus fcu_opp;
  base_fcu_bus fcu_own;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_fmgc_inputs_
#define DEFINED_TYPEDEF_FOR_fmgc_inputs_

struct fmgc_inputs
{
  base_time time;
  base_sim_data sim_data;
  base_fmgc_discrete_inputs discrete_inputs;
  base_fms_inputs fms_inputs;
  base_fmgc_bus_inputs bus_inputs;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_adr_computation_data_
#define DEFINED_TYPEDEF_FOR_base_fmgc_adr_computation_data_

struct base_fmgc_adr_computation_data
{
  real_T V_ias_kn;
  real_T V_tas_kn;
  real_T mach;
  real_T alpha_deg;
  real_T p_s_c_hpa;
  real_T altitude_corrected_ft;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_ir_computation_data_
#define DEFINED_TYPEDEF_FOR_base_fmgc_ir_computation_data_

struct base_fmgc_ir_computation_data
{
  real_T theta_deg;
  real_T phi_deg;
  real_T q_deg_s;
  real_T r_deg_s;
  real_T n_x_g;
  real_T n_y_g;
  real_T n_z_g;
  real_T theta_dot_deg_s;
  real_T phi_dot_deg_s;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_logic_outputs_
#define DEFINED_TYPEDEF_FOR_base_fmgc_logic_outputs_

struct base_fmgc_logic_outputs
{
  boolean_T on_ground;
  boolean_T ap_fd_athr_common_condition;
  boolean_T ap_fd_common_condition;
  boolean_T fd_own_engaged;
  boolean_T ap_own_engaged;
  boolean_T athr_own_engaged;
  boolean_T double_adr_failure;
  boolean_T double_ir_failure;
  base_fmgc_adr_computation_data adr_computation_data;
  base_fmgc_ir_computation_data ir_computation_data;
  real_T ra_computation_data_ft;
  boolean_T dual_ra_failure;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_discrete_outputs_
#define DEFINED_TYPEDEF_FOR_base_fmgc_discrete_outputs_

struct base_fmgc_discrete_outputs
{
  boolean_T athr_own_engaged;
  boolean_T fd_own_engaged;
  boolean_T ap_own_engaged;
  boolean_T fcu_own_fail;
  boolean_T fmgc_healthy;
  boolean_T ils_test_inhibit;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_b_bus_
#define DEFINED_TYPEDEF_FOR_base_fmgc_b_bus_

struct base_fmgc_b_bus
{
  base_arinc_429 fac_weight_lbs;
  base_arinc_429 fm_weight_lbs;
  base_arinc_429 fac_cg_percent;
  base_arinc_429 fm_cg_percent;
  base_arinc_429 fg_radio_height_ft;
  base_arinc_429 discrete_word_4;
  base_arinc_429 ats_discrete_word;
  base_arinc_429 discrete_word_3;
  base_arinc_429 discrete_word_1;
  base_arinc_429 discrete_word_2;
  base_arinc_429 approach_spd_target_kn;
  base_arinc_429 delta_p_ail_cmd_deg;
  base_arinc_429 delta_p_splr_cmd_deg;
  base_arinc_429 delta_r_cmd_deg;
  base_arinc_429 delta_nose_wheel_cmd_deg;
  base_arinc_429 delta_q_cmd_deg;
  base_arinc_429 n1_left_percent;
  base_arinc_429 n1_right_percent;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fmgc_bus_outputs_
#define DEFINED_TYPEDEF_FOR_base_fmgc_bus_outputs_

struct base_fmgc_bus_outputs
{
  base_fmgc_a_bus fmgc_a_bus;
  base_fmgc_b_bus fmgc_b_bus;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_fmgc_outputs_
#define DEFINED_TYPEDEF_FOR_fmgc_outputs_

struct fmgc_outputs
{
  fmgc_inputs data;
  base_fmgc_logic_outputs logic;
  base_fmgc_discrete_outputs discrete_outputs;
  base_fmgc_bus_outputs bus_outputs;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_2OohiAWrazWy5wDS5iisgF_
#define DEFINED_TYPEDEF_FOR_struct_2OohiAWrazWy5wDS5iisgF_

struct struct_2OohiAWrazWy5wDS5iisgF
{
  real_T SSM;
  real_T Data;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_PU75bC6JQHPO0CCSfJRZYE_
#define DEFINED_TYPEDEF_FOR_struct_PU75bC6JQHPO0CCSfJRZYE_

struct struct_PU75bC6JQHPO0CCSfJRZYE
{
  struct_2OohiAWrazWy5wDS5iisgF roll_fd_command;
  struct_2OohiAWrazWy5wDS5iisgF pitch_fd_command;
  struct_2OohiAWrazWy5wDS5iisgF yaw_fd_command;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_5;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_4;
  struct_2OohiAWrazWy5wDS5iisgF ats_discrete_word;
  struct_2OohiAWrazWy5wDS5iisgF ats_fma_discrete_word;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_3;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_1;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_2;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_6;
  struct_2OohiAWrazWy5wDS5iisgF delta_p_ail_voted_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_p_splr_voted_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_r_voted_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_nosewheel_voted_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_q_voted_cmd_deg;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_4xpe111mhgRDizxiF0fNDB_
#define DEFINED_TYPEDEF_FOR_struct_4xpe111mhgRDizxiF0fNDB_

struct struct_4xpe111mhgRDizxiF0fNDB
{
  struct_2OohiAWrazWy5wDS5iisgF fac_weight_lbs;
  struct_2OohiAWrazWy5wDS5iisgF fm_weight_lbs;
  struct_2OohiAWrazWy5wDS5iisgF fac_cg_percent;
  struct_2OohiAWrazWy5wDS5iisgF fm_cg_percent;
  struct_2OohiAWrazWy5wDS5iisgF fg_radio_height_ft;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_4;
  struct_2OohiAWrazWy5wDS5iisgF ats_discrete_word;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_3;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_1;
  struct_2OohiAWrazWy5wDS5iisgF discrete_word_2;
  struct_2OohiAWrazWy5wDS5iisgF approach_spd_target_kn;
  struct_2OohiAWrazWy5wDS5iisgF delta_p_ail_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_p_splr_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_r_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_nose_wheel_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF delta_q_cmd_deg;
  struct_2OohiAWrazWy5wDS5iisgF n1_left_percent;
  struct_2OohiAWrazWy5wDS5iisgF n1_right_percent;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_d0aybyYrGUAWb8eZSltKpB_
#define DEFINED_TYPEDEF_FOR_struct_d0aybyYrGUAWb8eZSltKpB_

struct struct_d0aybyYrGUAWb8eZSltKpB
{
  struct_PU75bC6JQHPO0CCSfJRZYE fmgc_a_bus;
  struct_4xpe111mhgRDizxiF0fNDB fmgc_b_bus;
};

#endif
#endif

