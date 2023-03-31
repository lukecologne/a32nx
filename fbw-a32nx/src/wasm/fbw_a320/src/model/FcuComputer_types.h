#ifndef RTW_HEADER_FcuComputer_types_h_
#define RTW_HEADER_FcuComputer_types_h_
#include "rtwtypes.h"

#ifndef DEFINED_TYPEDEF_FOR_efis_range_selection_
#define DEFINED_TYPEDEF_FOR_efis_range_selection_

enum class efis_range_selection
  : int32_T {
  RANGE_10 = 0,
  RANGE_20,
  RANGE_40,
  RANGE_80,
  RANGE_160,
  RANGE_320
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_efis_mode_selection_
#define DEFINED_TYPEDEF_FOR_efis_mode_selection_

enum class efis_mode_selection
  : int32_T {
  ROSE_ILS = 0,
  ROSE_VOR,
  ROSE_NAV,
  ARC,
  PLAN
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_efis_filter_selection_
#define DEFINED_TYPEDEF_FOR_efis_filter_selection_

enum class efis_filter_selection
  : int32_T {
  NONE = 0,
  CSTR,
  WPT,
  VORD,
  NDB,
  ARPT
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_efis_navaid_selection_
#define DEFINED_TYPEDEF_FOR_efis_navaid_selection_

enum class efis_navaid_selection
  : int32_T {
  NONE = 0,
  VOR,
  ADF
};

#endif

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

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_knob_inputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_knob_inputs_

struct base_fcu_knob_inputs
{
  boolean_T pushed;
  boolean_T pulled;
  int8_T turns;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_efis_panel_inputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_efis_panel_inputs_

struct base_fcu_efis_panel_inputs
{
  efis_range_selection efis_range;
  efis_mode_selection efis_mode;
  efis_navaid_selection efis_navaid_1;
  efis_navaid_selection efis_navaid_2;
  boolean_T baro_is_inhg;
  base_fcu_knob_inputs baro_knob;
  boolean_T fd_button_pushed;
  boolean_T ls_button_pushed;
  boolean_T cstr_button_pushed;
  boolean_T wpt_button_pushed;
  boolean_T vord_button_pushed;
  boolean_T ndb_button_pushed;
  boolean_T arpt_button_pushed;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_afs_panel_inputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_afs_panel_inputs_

struct base_fcu_afs_panel_inputs
{
  boolean_T loc_button_pressed;
  boolean_T exped_button_pressed;
  boolean_T appr_button_pressed;
  boolean_T spd_mach_button_pressed;
  boolean_T trk_fpa_button_pressed;
  real_T metric_alt_button_pressed;
  base_fcu_knob_inputs spd_knob;
  base_fcu_knob_inputs hdg_trk_knob;
  base_fcu_knob_inputs alt_knob;
  boolean_T alt_increment_1000;
  base_fcu_knob_inputs vs_fpa_knob;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_discrete_inputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_discrete_inputs_

struct base_fcu_discrete_inputs
{
  boolean_T ap_1_engaged;
  boolean_T fd_1_engaged;
  boolean_T athr_1_engaged;
  boolean_T ap_2_engaged;
  boolean_T fd_2_engaged;
  boolean_T athr_2_engaged;
  boolean_T lights_test;
  base_fcu_efis_panel_inputs capt_efis_inputs;
  base_fcu_efis_panel_inputs fo_efis_inputs;
  base_fcu_afs_panel_inputs afs_inputs;
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

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_bus_inputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_bus_inputs_

struct base_fcu_bus_inputs
{
  base_fmgc_a_bus fmgc_1_bus;
  base_fmgc_a_bus fmgc_2_bus;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_fcu_inputs_
#define DEFINED_TYPEDEF_FOR_fcu_inputs_

struct fcu_inputs
{
  base_time time;
  base_sim_data sim_data;
  base_fcu_discrete_inputs discrete_inputs;
  base_fcu_bus_inputs bus_inputs;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_efis_logic_outputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_efis_logic_outputs_

struct base_fcu_efis_logic_outputs
{
  boolean_T fd_on;
  boolean_T ls_on;
  efis_filter_selection efis_filter;
  boolean_T baro_std;
  boolean_T baro_qnh;
  boolean_T baro_qfe;
  real32_T baro_value_hpa;
  real32_T baro_value_inhg;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_logic_outputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_logic_outputs_

struct base_fcu_logic_outputs
{
  boolean_T fmgc_1_has_priority;
  base_fcu_efis_logic_outputs capt_efis;
  base_fcu_efis_logic_outputs fo_efis;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_efis_panel_outputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_efis_panel_outputs_

struct base_fcu_efis_panel_outputs
{
  boolean_T fd_light_on;
  boolean_T ls_light_on;
  boolean_T cstr_light_on;
  boolean_T wpt_light_on;
  boolean_T vord_light_on;
  boolean_T ndb_light_on;
  boolean_T arpt_light_on;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_afs_panel_outputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_afs_panel_outputs_

struct base_fcu_afs_panel_outputs
{
  boolean_T loc_light_on;
  boolean_T exped_light_on;
  boolean_T appr_light_on;
  boolean_T ap_1_light_on;
  boolean_T ap_2_light_on;
  boolean_T athr_light_on;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_discrete_outputs_
#define DEFINED_TYPEDEF_FOR_base_fcu_discrete_outputs_

struct base_fcu_discrete_outputs
{
  base_fcu_efis_panel_outputs capt_efis_outputs;
  base_fcu_efis_panel_outputs fo_efis_outputs;
  base_fcu_afs_panel_outputs afs_outputs;
  boolean_T fcu_healthy;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_base_fcu_bus_
#define DEFINED_TYPEDEF_FOR_base_fcu_bus_

struct base_fcu_bus
{
  base_arinc_429 selected_hdg_deg;
  base_arinc_429 selected_alt_ft;
  base_arinc_429 selected_spd_kts;
  base_arinc_429 selected_vz_ft_min;
  base_arinc_429 selected_mach;
  base_arinc_429 selected_trk_deg;
  base_arinc_429 selected_fpa_deg;
  base_arinc_429 ats_fma_discrete_word;
  base_arinc_429 fcu_flex_to_temp_deg_c;
  base_arinc_429 ats_discrete_word;
  base_arinc_429 eis_discrete_word_1_left;
  base_arinc_429 eis_discrete_word_1_right;
  base_arinc_429 eis_discrete_word_2_left;
  base_arinc_429 eis_discrete_word_2_right;
  base_arinc_429 baro_setting_left_hpa;
  base_arinc_429 baro_setting_right_hpa;
  base_arinc_429 baro_setting_left_inhg;
  base_arinc_429 baro_setting_right_inhg;
  base_arinc_429 fcu_discrete_word_2;
  base_arinc_429 fcu_discrete_word_1;
  base_arinc_429 n1_cmd_percent;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_fcu_outputs_
#define DEFINED_TYPEDEF_FOR_fcu_outputs_

struct fcu_outputs
{
  fcu_inputs data;
  base_fcu_logic_outputs logic;
  base_fcu_discrete_outputs discrete_outputs;
  base_fcu_bus bus_outputs;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_bqjSWtmatK4obwyFIPQOyC_
#define DEFINED_TYPEDEF_FOR_struct_bqjSWtmatK4obwyFIPQOyC_

struct struct_bqjSWtmatK4obwyFIPQOyC
{
  boolean_T fd_on;
  boolean_T ls_on;
  efis_filter_selection efis_filter;
  boolean_T baro_std;
  boolean_T baro_qnh;
  boolean_T baro_qfe;
  real_T baro_value_hpa;
  real_T baro_value_inhg;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_XLWtyCEKE4tFdVYBl9lDvC_
#define DEFINED_TYPEDEF_FOR_struct_XLWtyCEKE4tFdVYBl9lDvC_

struct struct_XLWtyCEKE4tFdVYBl9lDvC
{
  boolean_T fmgc_1_has_priority;
  struct_bqjSWtmatK4obwyFIPQOyC capt_efis;
  struct_bqjSWtmatK4obwyFIPQOyC fo_efis;
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

#ifndef DEFINED_TYPEDEF_FOR_struct_jKPQGsPwrNwDJirnuGEHpB_
#define DEFINED_TYPEDEF_FOR_struct_jKPQGsPwrNwDJirnuGEHpB_

struct struct_jKPQGsPwrNwDJirnuGEHpB
{
  struct_2OohiAWrazWy5wDS5iisgF selected_hdg_deg;
  struct_2OohiAWrazWy5wDS5iisgF selected_alt_ft;
  struct_2OohiAWrazWy5wDS5iisgF selected_spd_kts;
  struct_2OohiAWrazWy5wDS5iisgF selected_vz_ft_min;
  struct_2OohiAWrazWy5wDS5iisgF selected_mach;
  struct_2OohiAWrazWy5wDS5iisgF selected_trk_deg;
  struct_2OohiAWrazWy5wDS5iisgF selected_fpa_deg;
  struct_2OohiAWrazWy5wDS5iisgF ats_fma_discrete_word;
  struct_2OohiAWrazWy5wDS5iisgF fcu_flex_to_temp_deg_c;
  struct_2OohiAWrazWy5wDS5iisgF ats_discrete_word;
  struct_2OohiAWrazWy5wDS5iisgF eis_discrete_word_1_left;
  struct_2OohiAWrazWy5wDS5iisgF eis_discrete_word_1_right;
  struct_2OohiAWrazWy5wDS5iisgF eis_discrete_word_2_left;
  struct_2OohiAWrazWy5wDS5iisgF eis_discrete_word_2_right;
  struct_2OohiAWrazWy5wDS5iisgF baro_setting_left_hpa;
  struct_2OohiAWrazWy5wDS5iisgF baro_setting_right_hpa;
  struct_2OohiAWrazWy5wDS5iisgF baro_setting_left_inhg;
  struct_2OohiAWrazWy5wDS5iisgF baro_setting_right_inhg;
  struct_2OohiAWrazWy5wDS5iisgF fcu_discrete_word_2;
  struct_2OohiAWrazWy5wDS5iisgF fcu_discrete_word_1;
  struct_2OohiAWrazWy5wDS5iisgF n1_cmd_percent;
};

#endif
#endif

