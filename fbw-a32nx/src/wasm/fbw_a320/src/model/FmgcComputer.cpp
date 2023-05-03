#include "FmgcComputer.h"
#include "rtwtypes.h"
#include "FmgcComputer_types.h"
#include <cmath>

void FmgcComputer::FmgcComputer_MATLABFunction_Reset(rtDW_MATLABFunction_FmgcComputer_T *localDW)
{
  localDW->output = false;
  localDW->timeSinceCondition = 0.0;
}

void FmgcComputer::FmgcComputer_MATLABFunction(boolean_T rtu_u, real_T rtu_Ts, boolean_T rtu_isRisingEdge, real_T
  rtu_timeDelay, boolean_T *rty_y, rtDW_MATLABFunction_FmgcComputer_T *localDW)
{
  if (rtu_u == rtu_isRisingEdge) {
    localDW->timeSinceCondition += rtu_Ts;
    if (localDW->timeSinceCondition >= rtu_timeDelay) {
      localDW->output = rtu_u;
    }
  } else {
    localDW->timeSinceCondition = 0.0;
    localDW->output = rtu_u;
  }

  *rty_y = localDW->output;
}

void FmgcComputer::FmgcComputer_MATLABFunction_m_Reset(rtDW_MATLABFunction_FmgcComputer_e_T *localDW)
{
  localDW->previousInput_not_empty = false;
}

void FmgcComputer::FmgcComputer_MATLABFunction_i(boolean_T rtu_u, boolean_T rtu_isRisingEdge, boolean_T *rty_y,
  rtDW_MATLABFunction_FmgcComputer_e_T *localDW)
{
  if (!localDW->previousInput_not_empty) {
    localDW->previousInput = rtu_isRisingEdge;
    localDW->previousInput_not_empty = true;
  }

  if (rtu_isRisingEdge) {
    *rty_y = (rtu_u && (!localDW->previousInput));
  } else {
    *rty_y = ((!rtu_u) && localDW->previousInput);
  }

  localDW->previousInput = rtu_u;
}

void FmgcComputer::FmgcComputer_MATLABFunction_f(const base_arinc_429 *rtu_u, boolean_T *rty_y)
{
  *rty_y = (rtu_u->SSM != static_cast<uint32_T>(SignStatusMatrix::FailureWarning));
}

void FmgcComputer::FmgcComputer_MATLABFunction_k(const base_arinc_429 *rtu_u, real_T rtu_bit, uint32_T *rty_y)
{
  real32_T tmp;
  uint32_T a;
  tmp = std::round(rtu_u->Data);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      a = static_cast<uint32_T>(tmp);
    } else {
      a = 0U;
    }
  } else {
    a = MAX_uint32_T;
  }

  if (-(rtu_bit - 1.0) >= 0.0) {
    if (-(rtu_bit - 1.0) <= 31.0) {
      a <<= static_cast<uint8_T>(-(rtu_bit - 1.0));
    } else {
      a = 0U;
    }
  } else if (-(rtu_bit - 1.0) >= -31.0) {
    a >>= static_cast<uint8_T>(rtu_bit - 1.0);
  } else {
    a = 0U;
  }

  *rty_y = a & 1U;
}

void FmgcComputer::FmgcComputer_MATLABFunction_g(const base_arinc_429 *rtu_u, boolean_T *rty_y)
{
  *rty_y = (rtu_u->SSM == static_cast<uint32_T>(SignStatusMatrix::NormalOperation));
}

void FmgcComputer::FmgcComputer_MATLABFunction_gy(const boolean_T rtu_u[19], real32_T *rty_y)
{
  uint32_T out;
  out = 0U;
  for (int32_T i{0}; i < 19; i++) {
    out |= static_cast<uint32_T>(rtu_u[i]) << (i + 10);
  }

  *rty_y = static_cast<real32_T>(out);
}

void FmgcComputer::step()
{
  real32_T rtb_y_a1;
  real32_T rtb_y_bb;
  real32_T rtb_y_i;
  real32_T rtb_y_je;
  real32_T rtb_y_kh;
  real32_T rtb_y_osy;
  real32_T rtb_y_ou;
  real32_T rtb_y_pn;
  uint32_T rtb_y_cjd;
  uint32_T rtb_y_h3;
  uint32_T rtb_y_py;
  boolean_T rtb_VectorConcatenate[19];
  boolean_T rtb_Memory;
  boolean_T rtb_OR_d;
  boolean_T rtb_adrOppInvalid;
  boolean_T rtb_y_f4;
  boolean_T rtb_y_fg;
  boolean_T rtb_y_k4;
  if (FmgcComputer_U.in.sim_data.computer_running) {
    real_T rtb_DataTypeConversion;
    real32_T rtb_V_ias;
    real32_T rtb_V_tas;
    real32_T rtb_alpha;
    real32_T rtb_alt;
    real32_T rtb_mach_i;
    real32_T rtb_n_x;
    real32_T rtb_n_y;
    real32_T rtb_n_z;
    real32_T rtb_p_s_c;
    real32_T rtb_phi;
    real32_T rtb_phi_dot;
    real32_T rtb_q;
    real32_T rtb_r;
    real32_T rtb_theta;
    real32_T rtb_theta_dot;
    boolean_T fdOppOff;
    boolean_T fdOwnOff;
    boolean_T rtb_Logic_e_idx_0_tmp;
    boolean_T rtb_Logic_gj_idx_0_tmp;
    boolean_T rtb_Logic_o_idx_0_tmp;
    boolean_T rtb_Logic_o_idx_0_tmp_0;
    boolean_T rtb_Logic_o_idx_0_tmp_tmp;
    boolean_T rtb_NOT4;
    boolean_T rtb_NOT6;
    boolean_T rtb_OR2_tmp;
    boolean_T rtb_adr3Invalid;
    boolean_T rtb_adrOwnInvalid;
    boolean_T rtb_ap_fd_athr_condition;
    boolean_T rtb_ap_fd_condition;
    boolean_T rtb_ap_inop_tmp;
    boolean_T rtb_ap_inop_tmp_tmp;
    boolean_T rtb_appCapacity_idx_2;
    boolean_T rtb_fmgcOppPriority_tmp;
    boolean_T rtb_fmgcOppPriority_tmp_0;
    boolean_T rtb_ir3Invalid;
    boolean_T rtb_irOppInvalid;
    boolean_T rtb_irOwnInvalid;
    boolean_T tmp;
    if (!FmgcComputer_DWork.Runtime_MODE) {
      FmgcComputer_DWork.Delay_DSTATE = FmgcComputer_P.Delay_InitialCondition;
      FmgcComputer_DWork.Delay_DSTATE_p = FmgcComputer_P.Delay_InitialCondition_g;
      FmgcComputer_DWork.Memory_PreviousInput = FmgcComputer_P.SRFlipFlop1_initial_condition;
      FmgcComputer_DWork.Memory_PreviousInput_g = FmgcComputer_P.SRFlipFlop_initial_condition;
      FmgcComputer_DWork.Memory_PreviousInput_p = FmgcComputer_P.SRFlipFlop_initial_condition_b;
      FmgcComputer_DWork.Memory_PreviousInput_k = FmgcComputer_P.SRFlipFlop_initial_condition_h;
      FmgcComputer_DWork.Memory_PreviousInput_c = FmgcComputer_P.SRFlipFlop_initial_condition_i;
      FmgcComputer_DWork.Memory_PreviousInput_l = FmgcComputer_P.SRFlipFlop_initial_condition_d;
      FmgcComputer_DWork.Memory_PreviousInput_d = FmgcComputer_P.SRFlipFlop_initial_condition_iz;
      FmgcComputer_DWork.Memory_PreviousInput_dv = FmgcComputer_P.SRFlipFlop_initial_condition_l;
      FmgcComputer_DWork.Memory_PreviousInput_f = FmgcComputer_P.SRFlipFlop_initial_condition_j;
      FmgcComputer_DWork.Memory_PreviousInput_i = FmgcComputer_P.SRFlipFlop_initial_condition_h5;
      FmgcComputer_DWork.Memory_PreviousInput_e = FmgcComputer_P.SRFlipFlop_initial_condition_e;
      FmgcComputer_DWork.Memory_PreviousInput_f2 = FmgcComputer_P.SRFlipFlop_initial_condition_c;
      FmgcComputer_DWork.Memory_PreviousInput_i1 = FmgcComputer_P.SRFlipFlop_initial_condition_o;
      FmgcComputer_DWork.Memory_PreviousInput_ip = FmgcComputer_P.SRFlipFlop_initial_condition_g;
      FmgcComputer_DWork.Memory_PreviousInput_a = FmgcComputer_P.SRFlipFlop_initial_condition_n;
      FmgcComputer_DWork.Memory_PreviousInput_cv = FmgcComputer_P.SRFlipFlop_initial_condition_of;
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_i);
      FmgcComputer_MATLABFunction_Reset(&FmgcComputer_DWork.sf_MATLABFunction_f);
      FmgcComputer_MATLABFunction_Reset(&FmgcComputer_DWork.sf_MATLABFunction);
      FmgcComputer_MATLABFunction_Reset(&FmgcComputer_DWork.sf_MATLABFunction_hz);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_gk);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_d3);
      FmgcComputer_MATLABFunction_Reset(&FmgcComputer_DWork.sf_MATLABFunction_h);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_fn);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_di2);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_h4);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_m1);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_h0);
      FmgcComputer_MATLABFunction_m_Reset(&FmgcComputer_DWork.sf_MATLABFunction_jl);
      FmgcComputer_DWork.Runtime_MODE = true;
    }

    rtb_adrOwnInvalid = ((FmgcComputer_U.in.bus_inputs.adr_own_bus.airspeed_computed_kn.SSM == static_cast<uint32_T>
                          (SignStatusMatrix::FailureWarning)) ||
                         (FmgcComputer_U.in.bus_inputs.adr_own_bus.aoa_corrected_deg.SSM == static_cast<uint32_T>
                          (SignStatusMatrix::FailureWarning)));
    rtb_adrOppInvalid = ((FmgcComputer_U.in.bus_inputs.adr_opp_bus.airspeed_computed_kn.SSM == static_cast<uint32_T>
                          (SignStatusMatrix::FailureWarning)) ||
                         (FmgcComputer_U.in.bus_inputs.adr_opp_bus.aoa_corrected_deg.SSM == static_cast<uint32_T>
                          (SignStatusMatrix::FailureWarning)));
    rtb_adr3Invalid = ((FmgcComputer_U.in.bus_inputs.adr_3_bus.airspeed_computed_kn.SSM == static_cast<uint32_T>
                        (SignStatusMatrix::FailureWarning)) ||
                       (FmgcComputer_U.in.bus_inputs.adr_3_bus.aoa_corrected_deg.SSM == static_cast<uint32_T>
                        (SignStatusMatrix::FailureWarning)));
    rtb_adrOppInvalid = ((rtb_adrOwnInvalid && rtb_adrOppInvalid) || (rtb_adrOwnInvalid && rtb_adr3Invalid) ||
                         (rtb_adrOppInvalid && rtb_adr3Invalid));
    rtb_irOwnInvalid = ((FmgcComputer_U.in.bus_inputs.ir_own_bus.body_yaw_rate_deg_s.SSM != static_cast<uint32_T>
                         (SignStatusMatrix::NormalOperation)) ||
                        (FmgcComputer_U.in.bus_inputs.ir_own_bus.body_lat_accel_g.SSM != static_cast<uint32_T>
                         (SignStatusMatrix::NormalOperation)));
    rtb_irOppInvalid = ((FmgcComputer_U.in.bus_inputs.ir_opp_bus.body_yaw_rate_deg_s.SSM != static_cast<uint32_T>
                         (SignStatusMatrix::NormalOperation)) ||
                        (FmgcComputer_U.in.bus_inputs.ir_opp_bus.body_lat_accel_g.SSM != static_cast<uint32_T>
                         (SignStatusMatrix::NormalOperation)));
    rtb_ir3Invalid = ((FmgcComputer_U.in.bus_inputs.ir_3_bus.body_yaw_rate_deg_s.SSM != static_cast<uint32_T>
                       (SignStatusMatrix::NormalOperation)) ||
                      (FmgcComputer_U.in.bus_inputs.ir_3_bus.body_lat_accel_g.SSM != static_cast<uint32_T>
                       (SignStatusMatrix::NormalOperation)));
    rtb_irOppInvalid = ((rtb_irOwnInvalid && rtb_irOppInvalid) || (rtb_irOwnInvalid && rtb_ir3Invalid) ||
                        (rtb_irOppInvalid && rtb_ir3Invalid));
    if (!rtb_adrOwnInvalid) {
      rtb_V_ias = FmgcComputer_U.in.bus_inputs.adr_own_bus.airspeed_computed_kn.Data;
      rtb_V_tas = FmgcComputer_U.in.bus_inputs.adr_own_bus.airspeed_true_kn.Data;
      rtb_mach_i = FmgcComputer_U.in.bus_inputs.adr_own_bus.mach.Data;
      rtb_alpha = FmgcComputer_U.in.bus_inputs.adr_own_bus.aoa_corrected_deg.Data;
      rtb_p_s_c = FmgcComputer_U.in.bus_inputs.adr_own_bus.corrected_average_static_pressure.Data;
      rtb_alt = FmgcComputer_U.in.bus_inputs.adr_own_bus.altitude_corrected_ft.Data;
    } else if (!rtb_adr3Invalid) {
      rtb_V_ias = FmgcComputer_U.in.bus_inputs.adr_3_bus.airspeed_computed_kn.Data;
      rtb_V_tas = FmgcComputer_U.in.bus_inputs.adr_3_bus.airspeed_true_kn.Data;
      rtb_mach_i = FmgcComputer_U.in.bus_inputs.adr_3_bus.mach.Data;
      rtb_alpha = FmgcComputer_U.in.bus_inputs.adr_3_bus.aoa_corrected_deg.Data;
      rtb_p_s_c = FmgcComputer_U.in.bus_inputs.adr_3_bus.corrected_average_static_pressure.Data;
      rtb_alt = FmgcComputer_U.in.bus_inputs.adr_own_bus.altitude_corrected_ft.Data;
    } else {
      rtb_V_ias = 0.0F;
      rtb_V_tas = 0.0F;
      rtb_mach_i = 0.0F;
      rtb_alpha = 0.0F;
      rtb_p_s_c = 0.0F;
      rtb_alt = 0.0F;
    }

    if (!rtb_irOwnInvalid) {
      rtb_theta = FmgcComputer_U.in.bus_inputs.ir_own_bus.pitch_angle_deg.Data;
      rtb_phi = FmgcComputer_U.in.bus_inputs.ir_own_bus.roll_angle_deg.Data;
      rtb_q = FmgcComputer_U.in.bus_inputs.ir_own_bus.body_pitch_rate_deg_s.Data;
      rtb_r = FmgcComputer_U.in.bus_inputs.ir_own_bus.body_yaw_rate_deg_s.Data;
      rtb_n_x = FmgcComputer_U.in.bus_inputs.ir_own_bus.body_long_accel_g.Data;
      rtb_n_y = FmgcComputer_U.in.bus_inputs.ir_own_bus.body_lat_accel_g.Data;
      rtb_n_z = FmgcComputer_U.in.bus_inputs.ir_own_bus.body_normal_accel_g.Data;
      rtb_theta_dot = FmgcComputer_U.in.bus_inputs.ir_own_bus.pitch_att_rate_deg_s.Data;
      rtb_phi_dot = FmgcComputer_U.in.bus_inputs.ir_own_bus.roll_att_rate_deg_s.Data;
    } else if (!rtb_ir3Invalid) {
      rtb_theta = FmgcComputer_U.in.bus_inputs.ir_3_bus.pitch_angle_deg.Data;
      rtb_phi = FmgcComputer_U.in.bus_inputs.ir_3_bus.roll_angle_deg.Data;
      rtb_q = FmgcComputer_U.in.bus_inputs.ir_3_bus.body_pitch_rate_deg_s.Data;
      rtb_r = FmgcComputer_U.in.bus_inputs.ir_3_bus.body_yaw_rate_deg_s.Data;
      rtb_n_x = FmgcComputer_U.in.bus_inputs.ir_3_bus.body_long_accel_g.Data;
      rtb_n_y = FmgcComputer_U.in.bus_inputs.ir_3_bus.body_lat_accel_g.Data;
      rtb_n_z = FmgcComputer_U.in.bus_inputs.ir_3_bus.body_normal_accel_g.Data;
      rtb_theta_dot = FmgcComputer_U.in.bus_inputs.ir_3_bus.pitch_att_rate_deg_s.Data;
      rtb_phi_dot = FmgcComputer_U.in.bus_inputs.ir_3_bus.roll_att_rate_deg_s.Data;
    } else {
      rtb_theta = 0.0F;
      rtb_phi = 0.0F;
      rtb_q = 0.0F;
      rtb_r = 0.0F;
      rtb_n_x = 0.0F;
      rtb_n_y = 0.0F;
      rtb_n_z = 0.0F;
      rtb_theta_dot = 0.0F;
      rtb_phi_dot = 0.0F;
    }

    rtb_adrOwnInvalid = (FmgcComputer_U.in.bus_inputs.ra_own_bus.radio_height_ft.SSM == static_cast<uint32_T>
                         (SignStatusMatrix::FailureWarning));
    rtb_adr3Invalid = (FmgcComputer_U.in.bus_inputs.ra_opp_bus.radio_height_ft.SSM == static_cast<uint32_T>
                       (SignStatusMatrix::FailureWarning));
    rtb_irOwnInvalid = (rtb_adrOwnInvalid && rtb_adr3Invalid);
    rtb_ir3Invalid = !rtb_adr3Invalid;
    tmp = !rtb_adrOwnInvalid;
    if (tmp && rtb_ir3Invalid) {
      rtb_DataTypeConversion = FmgcComputer_U.in.bus_inputs.ra_own_bus.radio_height_ft.Data;
    } else if (rtb_adrOwnInvalid && rtb_ir3Invalid) {
      rtb_DataTypeConversion = FmgcComputer_U.in.bus_inputs.ra_opp_bus.radio_height_ft.Data;
    } else if (tmp && rtb_adr3Invalid) {
      rtb_DataTypeConversion = FmgcComputer_U.in.bus_inputs.ra_own_bus.radio_height_ft.Data;
    } else {
      rtb_DataTypeConversion = 250.0;
    }

    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5,
      FmgcComputer_P.BitfromLabel_bit, &rtb_y_py);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5,
      FmgcComputer_P.BitfromLabel1_bit, &rtb_y_h3);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5,
      FmgcComputer_P.BitfromLabel2_bit, &rtb_y_cjd);
    rtb_NOT4 = (rtb_y_cjd == 0U);
    FmgcComputer_MATLABFunction_f(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5, &rtb_y_f4);
    rtb_NOT6 = ((rtb_y_py != 0U) && (rtb_y_h3 != 0U) && rtb_NOT4 && rtb_y_f4);
    rtb_y_f4 = ((!rtb_y_f4) || (!rtb_NOT4));
    rtb_ap_fd_condition = (FmgcComputer_DWork.Delay_DSTATE.lateral_modes.land_active ||
      FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.pitch_goaround_active);
    rtb_ap_fd_athr_condition = ((!rtb_adrOppInvalid) && (!rtb_irOppInvalid) && ((!rtb_y_f4) || rtb_ap_fd_condition) &&
      (FmgcComputer_U.in.fms_inputs.fm_valid || rtb_ap_fd_condition ||
       (FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.gs_active &&
        FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.trk_submode_active && (rtb_DataTypeConversion < 700.0))));
    rtb_ap_fd_condition = (((!FmgcComputer_P.fmgc_logic_output_MATLABStruct.fac_weights_failure) || rtb_ap_fd_condition)
      && ((!FmgcComputer_P.fmgc_logic_output_MATLABStruct.fac_speeds_failure) ||
          FmgcComputer_DWork.Delay_DSTATE.lateral_modes.land_active));
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fcu_bus.fcu_discrete_word_2,
      FmgcComputer_P.BitfromLabel_bit_n, &rtb_y_py);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fcu_bus.fcu_discrete_word_2,
      FmgcComputer_P.BitfromLabel1_bit_i, &rtb_y_h3);
    if (FmgcComputer_U.in.discrete_inputs.is_unit_1) {
      fdOwnOff = (rtb_y_py != 0U);
      fdOppOff = (rtb_y_h3 != 0U);
    } else {
      fdOwnOff = (rtb_y_h3 != 0U);
      fdOppOff = (rtb_y_py != 0U);
    }

    fdOwnOff = (rtb_ap_fd_athr_condition && rtb_ap_fd_condition && ((!fdOwnOff) || ((!fdOppOff) &&
      (!FmgcComputer_U.in.discrete_inputs.fd_opp_engaged))));
    FmgcComputer_MATLABFunction_i(FmgcComputer_U.in.discrete_inputs.fcu_ap_button, FmgcComputer_P.PulseNode_isRisingEdge,
      &rtb_y_fg, &FmgcComputer_DWork.sf_MATLABFunction_i);
    FmgcComputer_MATLABFunction(!rtb_NOT6, FmgcComputer_U.in.time.dt, FmgcComputer_P.ConfirmNode1_isRisingEdge,
      FmgcComputer_P.ConfirmNode1_timeDelay, &rtb_OR_d, &FmgcComputer_DWork.sf_MATLABFunction_f);
    fdOppOff = ((FmgcComputer_U.in.discrete_inputs.eng_opp_stop && FmgcComputer_U.in.discrete_inputs.eng_own_stop &&
                 rtb_NOT6) || rtb_OR_d);
    rtb_NOT4 = ((!FmgcComputer_U.in.discrete_inputs.ap_instinctive_disc) &&
                (!FmgcComputer_U.in.discrete_inputs.elac_own_ap_disc) &&
                (!FmgcComputer_U.in.discrete_inputs.elac_opp_ap_disc));
    rtb_ap_inop_tmp_tmp = !rtb_ap_fd_athr_condition;
    rtb_ap_inop_tmp = (rtb_ap_inop_tmp_tmp || (!rtb_ap_fd_condition) || (!rtb_NOT4));
    FmgcComputer_DWork.Memory_PreviousInput = FmgcComputer_P.Logic_table[(((static_cast<uint32_T>(rtb_y_fg &&
      (!FmgcComputer_DWork.Delay_DSTATE_p) && fdOppOff && rtb_ap_fd_condition && rtb_ap_fd_athr_condition && rtb_NOT4) <<
      1) + (rtb_ap_inop_tmp || (rtb_y_fg && FmgcComputer_DWork.Delay_DSTATE_p) ||
            FmgcComputer_U.in.discrete_inputs.ap_instinctive_disc)) << 1) + FmgcComputer_DWork.Memory_PreviousInput];
    rtb_NOT4 = (rtb_y_fg && FmgcComputer_DWork.Memory_PreviousInput);
    FmgcComputer_MATLABFunction(FmgcComputer_DWork.Memory_PreviousInput, FmgcComputer_U.in.time.dt,
      FmgcComputer_P.ConfirmNode_isRisingEdge, FmgcComputer_P.ConfirmNode_timeDelay, &rtb_y_fg,
      &FmgcComputer_DWork.sf_MATLABFunction);
    FmgcComputer_DWork.Delay_DSTATE_p = FmgcComputer_P.Logic_table_h[(((static_cast<uint32_T>(rtb_NOT4) << 1) +
      ((!rtb_y_fg) || FmgcComputer_U.in.discrete_inputs.ap_instinctive_disc)) << 1) +
      FmgcComputer_DWork.Memory_PreviousInput_g];
    FmgcComputer_DWork.Memory_PreviousInput_p = FmgcComputer_P.Logic_table_n[(static_cast<uint32_T>
      (rtb_ap_fd_athr_condition && FmgcComputer_U.in.discrete_inputs.fcu_athr_button) << 2) +
      FmgcComputer_DWork.Memory_PreviousInput_p];
    rtb_NOT4 = (FmgcComputer_U.in.discrete_inputs.ap_opp_engaged || FmgcComputer_U.in.discrete_inputs.fd_opp_engaged);
    rtb_fmgcOppPriority_tmp = !FmgcComputer_DWork.Delay_DSTATE_p;
    rtb_fmgcOppPriority_tmp_0 = !fdOwnOff;
    rtb_appCapacity_idx_2 = (rtb_NOT4 || FmgcComputer_U.in.discrete_inputs.athr_opp_engaged);
    rtb_y_k4 = !FmgcComputer_DWork.Memory_PreviousInput_p;
    rtb_NOT4 = (((!FmgcComputer_U.in.discrete_inputs.is_unit_1) || (rtb_fmgcOppPriority_tmp &&
      (FmgcComputer_U.in.discrete_inputs.ap_opp_engaged || rtb_fmgcOppPriority_tmp_0) && (rtb_NOT4 || rtb_y_k4) &&
      rtb_appCapacity_idx_2)) && (FmgcComputer_U.in.discrete_inputs.is_unit_1 || ((rtb_fmgcOppPriority_tmp ||
      FmgcComputer_U.in.discrete_inputs.ap_opp_engaged) && (rtb_NOT4 || rtb_fmgcOppPriority_tmp_0) &&
      (rtb_appCapacity_idx_2 || rtb_y_k4) && (FmgcComputer_DWork.Delay_DSTATE_p || fdOwnOff ||
      FmgcComputer_DWork.Memory_PreviousInput_p || (!FmgcComputer_U.in.discrete_inputs.fmgc_opp_healthy)))));
    rtb_appCapacity_idx_2 = (rtb_fmgcOppPriority_tmp || (!FmgcComputer_U.in.discrete_inputs.ap_opp_engaged));
    rtb_fmgcOppPriority_tmp = (rtb_NOT4 && rtb_appCapacity_idx_2);
    rtb_fmgcOppPriority_tmp_0 = (FmgcComputer_DWork.Delay_DSTATE_p || FmgcComputer_U.in.discrete_inputs.ap_opp_engaged ||
      fdOwnOff || FmgcComputer_U.in.discrete_inputs.fd_opp_engaged);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_1,
      FmgcComputer_P.BitfromLabel_bit_c, &rtb_y_py);
    FmgcComputer_MATLABFunction(rtb_NOT6, FmgcComputer_U.in.time.dt, FmgcComputer_P.ConfirmNode_isRisingEdge_h,
      FmgcComputer_P.ConfirmNode_timeDelay_i, &rtb_y_fg, &FmgcComputer_DWork.sf_MATLABFunction_hz);
    FmgcComputer_MATLABFunction_i(false, FmgcComputer_P.PulseNode_isRisingEdge_p, &rtb_OR_d,
      &FmgcComputer_DWork.sf_MATLABFunction_gk);
    rtb_Memory = !FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.pitch_takeoff_active;
    rtb_y_k4 = !FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.pitch_goaround_active;
    rtb_Logic_gj_idx_0_tmp = !rtb_fmgcOppPriority_tmp;
    FmgcComputer_DWork.Memory_PreviousInput_k = FmgcComputer_P.Logic_table_b[(((static_cast<uint32_T>
      (((FmgcComputer_U.in.fms_inputs.v_2_kts > FmgcComputer_P.CompareToConstant1_const) && (rtb_y_py != 0U) &&
        rtb_fmgcOppPriority_tmp) || (rtb_Logic_gj_idx_0_tmp && rtb_Memory && rtb_y_k4 && rtb_y_fg &&
      (FmgcComputer_U.in.fms_inputs.v_2_kts > FmgcComputer_P.CompareToConstant2_const) &&
      (FmgcComputer_P.CompareToConstant_const_b <= 0) && rtb_OR_d)) << 1) + false) << 1) +
      FmgcComputer_DWork.Memory_PreviousInput_k];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_2,
      FmgcComputer_P.BitfromLabel_bit_a, &rtb_y_py);
    FmgcComputer_DWork.Memory_PreviousInput_c = FmgcComputer_P.Logic_table_hz[(((static_cast<uint32_T>((rtb_y_py != 0U) &&
      rtb_fmgcOppPriority_tmp) << 1) + false) << 1) + FmgcComputer_DWork.Memory_PreviousInput_c];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_3,
      FmgcComputer_P.BitfromLabel_bit_k, &rtb_y_py);
    rtb_Logic_e_idx_0_tmp = !FmgcComputer_DWork.Delay_DSTATE.lateral_modes.land_active;
    FmgcComputer_DWork.Memory_PreviousInput_l = FmgcComputer_P.Logic_table_k[(((static_cast<uint32_T>
      (rtb_Logic_e_idx_0_tmp && ((rtb_y_py != 0U) && rtb_fmgcOppPriority_tmp)) << 1) + false) << 1) +
      FmgcComputer_DWork.Memory_PreviousInput_l];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_4,
      FmgcComputer_P.BitfromLabel_bit_f, &rtb_y_py);
    FmgcComputer_DWork.Memory_PreviousInput_d = FmgcComputer_P.Logic_table_p[(((static_cast<uint32_T>((rtb_y_py != 0U) &&
      rtb_fmgcOppPriority_tmp) << 1) + false) << 1) + FmgcComputer_DWork.Memory_PreviousInput_d];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_3,
      FmgcComputer_P.BitfromLabel_bit_l, &rtb_y_py);
    rtb_y_fg = !FmgcComputer_DWork.Delay_DSTATE.armed_modes.land_armed;
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fcu_bus.fcu_discrete_word_1,
      FmgcComputer_P.BitfromLabel2_bit_e, &rtb_y_h3);
    FmgcComputer_MATLABFunction_i(rtb_y_h3 != 0U, FmgcComputer_P.PulseNode_isRisingEdge_h, &rtb_y_fg,
      &FmgcComputer_DWork.sf_MATLABFunction_d3);
    rtb_OR_d = !FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.final_des_active;
    rtb_y_k4 = (rtb_Memory && (!FmgcComputer_DWork.Delay_DSTATE.lateral_modes.rwy_active) && rtb_y_k4 &&
                (!FmgcComputer_DWork.Delay_DSTATE.lateral_modes.roll_goaround_active) && rtb_OR_d && rtb_y_fg);
    FmgcComputer_DWork.Memory_PreviousInput_dv = FmgcComputer_P.Logic_table_c[(((static_cast<uint32_T>
      (rtb_Logic_e_idx_0_tmp && ((rtb_y_py != 0U) && rtb_fmgcOppPriority_tmp)) << 1) + false) << 1) +
      FmgcComputer_DWork.Memory_PreviousInput_dv];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_1,
      FmgcComputer_P.BitfromLabel_bit_a4, &rtb_y_py);
    FmgcComputer_DWork.Memory_PreviousInput_f = FmgcComputer_P.Logic_table_pl[(((static_cast<uint32_T>((rtb_y_py != 0U) &&
      rtb_fmgcOppPriority_tmp) << 1) + false) << 1) + FmgcComputer_DWork.Memory_PreviousInput_f];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_1,
      FmgcComputer_P.BitfromLabel_bit_cs, &rtb_y_py);
    FmgcComputer_MATLABFunction(rtb_NOT6, FmgcComputer_U.in.time.dt, FmgcComputer_P.ConfirmNode_isRisingEdge_m,
      FmgcComputer_P.ConfirmNode_timeDelay_j, &rtb_y_k4, &FmgcComputer_DWork.sf_MATLABFunction_h);
    FmgcComputer_MATLABFunction_i(false, FmgcComputer_P.PulseNode_isRisingEdge_c, &rtb_y_fg,
      &FmgcComputer_DWork.sf_MATLABFunction_fn);
    FmgcComputer_DWork.Memory_PreviousInput_i = FmgcComputer_P.Logic_table_o[(((static_cast<uint32_T>(((rtb_y_py != 0U) &&
      rtb_fmgcOppPriority_tmp) || ((!rtb_fmgcOppPriority_tmp) && rtb_Memory &&
      (!FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.pitch_goaround_active) && (!rtb_y_k4) &&
      (FmgcComputer_P.CompareToConstant_const_j <= 0) && rtb_y_fg)) << 1) + false) << 1) +
      FmgcComputer_DWork.Memory_PreviousInput_i];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_2,
      FmgcComputer_P.BitfromLabel_bit_e, &rtb_y_py);
    FmgcComputer_DWork.Memory_PreviousInput_e = FmgcComputer_P.Logic_table_c2[(((static_cast<uint32_T>((rtb_y_py != 0U) &&
      rtb_fmgcOppPriority_tmp) << 1) + false) << 1) + FmgcComputer_DWork.Memory_PreviousInput_e];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_2,
      FmgcComputer_P.BitfromLabel_bit_p, &rtb_y_py);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_2,
      FmgcComputer_P.BitfromLabel1_bit_o, &rtb_y_h3);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fcu_bus.fcu_discrete_word_2,
      FmgcComputer_P.BitfromLabel2_bit_i, &rtb_y_cjd);
    FmgcComputer_MATLABFunction_i(rtb_y_cjd != 0U, FmgcComputer_P.PulseNode_isRisingEdge_i, &rtb_Memory,
      &FmgcComputer_DWork.sf_MATLABFunction_di2);
    rtb_OR2_tmp = !FmgcComputer_U.in.fms_inputs.lateral_flight_plan_valid;
    rtb_y_fg = (FmgcComputer_DWork.Delay_DSTATE.lateral_modes.nav_active && rtb_OR2_tmp && rtb_OR_d);
    FmgcComputer_MATLABFunction_i(rtb_fmgcOppPriority_tmp_0, FmgcComputer_P.PulseNode1_isRisingEdge, &rtb_OR_d,
      &FmgcComputer_DWork.sf_MATLABFunction_h4);
    rtb_OR_d = (fdOppOff && rtb_OR_d);
    rtb_Logic_o_idx_0_tmp = !rtb_fmgcOppPriority_tmp_0;
    rtb_Logic_o_idx_0_tmp_tmp = (FmgcComputer_DWork.Delay_DSTATE.lateral_modes.rwy_active ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.roll_goaround_active);
    rtb_Logic_o_idx_0_tmp_0 = (rtb_Logic_o_idx_0_tmp_tmp || FmgcComputer_DWork.Delay_DSTATE.lateral_modes.loc_cpt_active
      || FmgcComputer_DWork.Delay_DSTATE.lateral_modes.loc_trk_active);
    FmgcComputer_DWork.Memory_PreviousInput_f2 = FmgcComputer_P.Logic_table_i[(((static_cast<uint32_T>((((rtb_y_py != 0U)
      || (rtb_y_h3 != 0U)) && rtb_fmgcOppPriority_tmp) || (rtb_Logic_gj_idx_0_tmp && ((fdOppOff && rtb_Memory) ||
      rtb_y_fg || rtb_OR_d))) << 1) + (rtb_Logic_o_idx_0_tmp_0 ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.nav_active || rtb_Logic_o_idx_0_tmp)) << 1) +
      FmgcComputer_DWork.Memory_PreviousInput_f2];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fcu_bus.fcu_discrete_word_1,
      FmgcComputer_P.BitfromLabel3_bit, &rtb_y_py);
    rtb_y_k4 = ((rtb_y_py != 0U) && FmgcComputer_DWork.Memory_PreviousInput_f2);
    rtb_Logic_e_idx_0_tmp = (FmgcComputer_DWork.Memory_PreviousInput_f2 && (rtb_y_py == 0U));
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_3,
      FmgcComputer_P.BitfromLabel_bit_fu, &rtb_y_py);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fcu_bus.fcu_discrete_word_2,
      FmgcComputer_P.BitfromLabel2_bit_m, &rtb_y_h3);
    FmgcComputer_MATLABFunction_i(rtb_y_h3 != 0U, FmgcComputer_P.PulseNode_isRisingEdge_j, &rtb_y_fg,
      &FmgcComputer_DWork.sf_MATLABFunction_m1);
    rtb_Memory = ((!FmgcComputer_DWork.Delay_DSTATE.lateral_modes.loc_cpt_active) &&
                  (!FmgcComputer_DWork.Delay_DSTATE.lateral_modes.loc_trk_active) && rtb_y_fg);
    FmgcComputer_MATLABFunction_g(&FmgcComputer_U.in.bus_inputs.fcu_bus.selected_hdg_deg, &rtb_OR_d);
    FmgcComputer_MATLABFunction_g(&FmgcComputer_U.in.bus_inputs.fcu_bus.selected_trk_deg, &rtb_y_fg);
    rtb_Memory = (rtb_Memory || (rtb_NOT6 && ((!rtb_OR_d) && (!rtb_y_fg)) &&
      ((!FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.any_lateral_mode_engaged) ||
       FmgcComputer_DWork.Memory_PreviousInput_c)));
    rtb_y_fg = (rtb_Logic_gj_idx_0_tmp && FmgcComputer_U.in.fms_inputs.lateral_flight_plan_valid && rtb_Memory);
    rtb_OR_d = (((rtb_y_py != 0U) && rtb_fmgcOppPriority_tmp) || rtb_y_fg);
    FmgcComputer_MATLABFunction_g(&FmgcComputer_U.in.bus_inputs.fcu_bus.selected_hdg_deg, &rtb_Memory);
    FmgcComputer_MATLABFunction_g(&FmgcComputer_U.in.bus_inputs.fcu_bus.selected_trk_deg, &rtb_y_fg);
    FmgcComputer_MATLABFunction_i(rtb_Memory || rtb_y_fg, FmgcComputer_P.PulseNode2_isRisingEdge, &rtb_Memory,
      &FmgcComputer_DWork.sf_MATLABFunction_h0);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fcu_bus.fcu_discrete_word_2,
      FmgcComputer_P.BitfromLabel1_bit_p, &rtb_y_py);
    FmgcComputer_MATLABFunction_i(rtb_y_py != 0U, FmgcComputer_P.PulseNode1_isRisingEdge_k, &rtb_y_fg,
      &FmgcComputer_DWork.sf_MATLABFunction_jl);
    FmgcComputer_DWork.Memory_PreviousInput_i1 = FmgcComputer_P.Logic_table_g[(((rtb_Memory || rtb_y_fg ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.nav_active || rtb_Logic_o_idx_0_tmp) + (static_cast<uint32_T>
      (rtb_OR_d) << 1)) << 1) + FmgcComputer_DWork.Memory_PreviousInput_i1];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_2,
      FmgcComputer_P.BitfromLabel_bit_nk, &rtb_y_py);
    FmgcComputer_DWork.Memory_PreviousInput_ip = FmgcComputer_P.Logic_table_a[(((static_cast<uint32_T>(((rtb_y_py != 0U)
      && rtb_fmgcOppPriority_tmp) || (rtb_Logic_gj_idx_0_tmp && FmgcComputer_U.in.fms_inputs.nav_capture_condition &&
      (FmgcComputer_DWork.Memory_PreviousInput_i1 || FmgcComputer_U.in.fms_inputs.direct_to_nav_engage) &&
      ((rtb_DataTypeConversion >= FmgcComputer_P.CompareToConstant_const) || rtb_irOwnInvalid))) << 1) + (rtb_OR2_tmp ||
      rtb_Logic_o_idx_0_tmp || (rtb_Logic_o_idx_0_tmp_0 || FmgcComputer_DWork.Delay_DSTATE.lateral_modes.hdg_active ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.trk_active))) << 1) + FmgcComputer_DWork.Memory_PreviousInput_ip];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_3,
      FmgcComputer_P.BitfromLabel_bit_o, &rtb_y_py);
    FmgcComputer_DWork.Memory_PreviousInput_a = FmgcComputer_P.Logic_table_ku[(((static_cast<uint32_T>(((rtb_y_py != 0U)
      && rtb_fmgcOppPriority_tmp) || (rtb_Logic_gj_idx_0_tmp && (FmgcComputer_DWork.Delay_DSTATE.armed_modes.land_armed ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.land_active))) << 1) + false) << 1) +
      FmgcComputer_DWork.Memory_PreviousInput_a];
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_2,
      FmgcComputer_P.BitfromLabel_bit_j, &rtb_y_py);
    FmgcComputer_DWork.Memory_PreviousInput_cv = FmgcComputer_P.Logic_table_g4[(((rtb_Logic_o_idx_0_tmp_tmp ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.nav_active ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.loc_trk_active ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.hdg_active ||
      FmgcComputer_DWork.Delay_DSTATE.lateral_modes.trk_active || rtb_Logic_o_idx_0_tmp) + (static_cast<uint32_T>
      ((rtb_y_py != 0U) && rtb_fmgcOppPriority_tmp) << 1)) << 1) + FmgcComputer_DWork.Memory_PreviousInput_cv];
    rtb_y_fg = (FmgcComputer_DWork.Memory_PreviousInput_cv || FmgcComputer_DWork.Memory_PreviousInput_d ||
                FmgcComputer_DWork.Memory_PreviousInput_f || FmgcComputer_DWork.Memory_PreviousInput_e);
    rtb_Logic_gj_idx_0_tmp = (rtb_NOT6 || ((rtb_DataTypeConversion < FmgcComputer_P.CompareToConstant_const_c) &&
      (!rtb_irOwnInvalid)) || rtb_y_fg);
    FmgcComputer_MATLABFunction_g(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_3, &rtb_y_fg);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_3,
      FmgcComputer_P.BitfromLabel_bit_i, &rtb_y_py);
    FmgcComputer_MATLABFunction_g(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_4, &rtb_y_fg);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_4,
      FmgcComputer_P.BitfromLabel1_bit_i5, &rtb_y_py);
    FmgcComputer_MATLABFunction_g(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_4, &rtb_y_fg);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_4,
      FmgcComputer_P.BitfromLabel2_bit_o, &rtb_y_py);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_4,
      FmgcComputer_P.BitfromLabel3_bit_l, &rtb_y_h3);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fmgc_opp_bus.discrete_word_4,
      FmgcComputer_P.BitfromLabel4_bit, &rtb_y_cjd);
    if (rtb_NOT4) {
      rtb_OR2_tmp = ((rtb_y_py != 0U) && rtb_y_fg);
    } else {
      rtb_OR2_tmp = false;
    }

    rtb_Memory = (rtb_appCapacity_idx_2 && rtb_OR2_tmp);
    if (rtb_NOT4) {
      rtb_OR2_tmp = ((rtb_y_h3 != 0U) && rtb_y_fg);
    } else {
      rtb_OR2_tmp = false;
    }

    rtb_OR_d = (rtb_appCapacity_idx_2 && rtb_OR2_tmp);
    if (rtb_NOT4) {
      rtb_OR2_tmp = ((rtb_y_cjd != 0U) && rtb_y_fg);
    } else {
      rtb_OR2_tmp = false;
    }

    rtb_appCapacity_idx_2 = (rtb_appCapacity_idx_2 && rtb_OR2_tmp);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[8] = false;
    rtb_VectorConcatenate[9] = false;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant10_Value;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_bb);
    rtb_VectorConcatenate[0] = FmgcComputer_U.in.discrete_inputs.ap_instinctive_disc;
    rtb_VectorConcatenate[1] = FmgcComputer_DWork.Delay_DSTATE_p;
    rtb_VectorConcatenate[2] = fdOwnOff;
    rtb_VectorConcatenate[3] = FmgcComputer_DWork.Memory_PreviousInput_d;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant3_Value;
    rtb_VectorConcatenate[5] = false;
    rtb_VectorConcatenate[6] = false;
    rtb_VectorConcatenate[7] = false;
    rtb_VectorConcatenate[8] = rtb_ap_inop_tmp;
    rtb_VectorConcatenate[9] = true;
    rtb_VectorConcatenate[10] = true;
    rtb_VectorConcatenate[11] = true;
    rtb_VectorConcatenate[12] = rtb_Memory;
    rtb_VectorConcatenate[13] = rtb_OR_d;
    rtb_VectorConcatenate[14] = rtb_appCapacity_idx_2;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant3_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant3_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant3_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant3_Value;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_osy);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[2] = FmgcComputer_DWork.Memory_PreviousInput_p;
    rtb_VectorConcatenate[3] = false;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[6] = FmgcComputer_U.in.discrete_inputs.athr_instinctive_disc;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[13] = rtb_ap_inop_tmp_tmp;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant4_Value_g;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_je);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant5_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant5_Value;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_a1);
    rtb_VectorConcatenate[0] = rtb_Logic_gj_idx_0_tmp;
    rtb_VectorConcatenate[1] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.alt_acq_armed;
    rtb_VectorConcatenate[2] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.alt_acq_arm_possible;
    rtb_VectorConcatenate[3] = FmgcComputer_DWork.Memory_PreviousInput_i1;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[5] = FmgcComputer_DWork.Memory_PreviousInput_a;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[9] = FmgcComputer_DWork.Memory_PreviousInput_l;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.glide_armed;
    rtb_VectorConcatenate[12] = FmgcComputer_DWork.Memory_PreviousInput_dv;
    rtb_VectorConcatenate[13] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.clb_armed;
    rtb_VectorConcatenate[14] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.des_armed;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant6_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant6_Value;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_ou);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[4] = FmgcComputer_DWork.Memory_PreviousInput_k;
    rtb_VectorConcatenate[5] = FmgcComputer_DWork.Memory_PreviousInput_i;
    rtb_VectorConcatenate[6] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.vs_active;
    rtb_VectorConcatenate[7] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.fpa_active;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[12] = FmgcComputer_DWork.Memory_PreviousInput_f;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant7_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant7_Value;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_pn);
    rtb_VectorConcatenate[0] = false;
    rtb_VectorConcatenate[1] = FmgcComputer_DWork.Memory_PreviousInput_ip;
    rtb_VectorConcatenate[2] = FmgcComputer_DWork.Memory_PreviousInput_cv;
    rtb_VectorConcatenate[3] = false;
    rtb_VectorConcatenate[4] = FmgcComputer_DWork.Memory_PreviousInput_e;
    rtb_VectorConcatenate[5] = rtb_y_k4;
    rtb_VectorConcatenate[6] = rtb_Logic_e_idx_0_tmp;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[9] = FmgcComputer_DWork.Memory_PreviousInput_c;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[12] = false;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[14] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.align_submode_active;
    rtb_VectorConcatenate[15] = FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.rollout_submode_active;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant8_Value;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_i);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant9_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant9_Value;
    FmgcComputer_MATLABFunction_gy(rtb_VectorConcatenate, &rtb_y_kh);
    FmgcComputer_Y.out.data = FmgcComputer_U.in;
    FmgcComputer_Y.out.logic.on_ground = rtb_NOT6;
    FmgcComputer_Y.out.logic.gnd_eng_stop_flt_5s = fdOppOff;
    FmgcComputer_Y.out.logic.ap_fd_athr_common_condition = rtb_ap_fd_athr_condition;
    FmgcComputer_Y.out.logic.ap_fd_common_condition = rtb_ap_fd_condition;
    FmgcComputer_Y.out.logic.fd_own_engaged = fdOwnOff;
    FmgcComputer_Y.out.logic.ap_own_engaged = FmgcComputer_DWork.Delay_DSTATE_p;
    FmgcComputer_Y.out.logic.athr_own_engaged = FmgcComputer_DWork.Memory_PreviousInput_p;
    FmgcComputer_Y.out.logic.athr_active = false;
    FmgcComputer_Y.out.logic.ap_inop = rtb_ap_inop_tmp;
    FmgcComputer_Y.out.logic.athr_inop = rtb_ap_inop_tmp_tmp;
    FmgcComputer_Y.out.logic.fmgc_opp_priority = rtb_NOT4;
    FmgcComputer_Y.out.logic.double_adr_failure = rtb_adrOppInvalid;
    FmgcComputer_Y.out.logic.double_ir_failure = rtb_irOppInvalid;
    FmgcComputer_Y.out.logic.adr_computation_data.V_ias_kn = rtb_V_ias;
    FmgcComputer_Y.out.logic.adr_computation_data.V_tas_kn = rtb_V_tas;
    FmgcComputer_Y.out.logic.adr_computation_data.mach = rtb_mach_i;
    FmgcComputer_Y.out.logic.adr_computation_data.alpha_deg = rtb_alpha;
    FmgcComputer_Y.out.logic.adr_computation_data.p_s_c_hpa = rtb_p_s_c;
    FmgcComputer_Y.out.logic.adr_computation_data.altitude_corrected_ft = rtb_alt;
    FmgcComputer_Y.out.logic.ir_computation_data.theta_deg = rtb_theta;
    FmgcComputer_Y.out.logic.ir_computation_data.phi_deg = rtb_phi;
    FmgcComputer_Y.out.logic.ir_computation_data.q_deg_s = rtb_q;
    FmgcComputer_Y.out.logic.ir_computation_data.r_deg_s = rtb_r;
    FmgcComputer_Y.out.logic.ir_computation_data.n_x_g = rtb_n_x;
    FmgcComputer_Y.out.logic.ir_computation_data.n_y_g = rtb_n_y;
    FmgcComputer_Y.out.logic.ir_computation_data.n_z_g = rtb_n_z;
    FmgcComputer_Y.out.logic.ir_computation_data.theta_dot_deg_s = rtb_theta_dot;
    FmgcComputer_Y.out.logic.ir_computation_data.phi_dot_deg_s = rtb_phi_dot;
    if (tmp && rtb_ir3Invalid) {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = FmgcComputer_U.in.bus_inputs.ra_own_bus.radio_height_ft.Data;
    } else if (rtb_adrOwnInvalid && rtb_ir3Invalid) {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = FmgcComputer_U.in.bus_inputs.ra_opp_bus.radio_height_ft.Data;
    } else if (tmp && rtb_adr3Invalid) {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = FmgcComputer_U.in.bus_inputs.ra_own_bus.radio_height_ft.Data;
    } else {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = 250.0;
    }

    FmgcComputer_Y.out.logic.dual_ra_failure = rtb_irOwnInvalid;
    FmgcComputer_Y.out.logic.fac_lg_data_failure = rtb_y_f4;
    FmgcComputer_Y.out.logic.fac_flap_slat_data_failure = false;
    FmgcComputer_Y.out.logic.flap_position = 0.0;
    FmgcComputer_Y.out.logic.slat_position = 0.0;
    FmgcComputer_Y.out.logic.flap_slat_lever_position = 0;
    FmgcComputer_Y.out.logic.fac_speeds_failure = FmgcComputer_P.fmgc_logic_output_MATLABStruct.fac_speeds_failure;
    FmgcComputer_Y.out.logic.fac_weights_failure = FmgcComputer_P.fmgc_logic_output_MATLABStruct.fac_weights_failure;
    FmgcComputer_Y.out.logic.fcu_failure = false;
    FmgcComputer_Y.out.logic.ils_failure = FmgcComputer_P.fmgc_logic_output_MATLABStruct.ils_failure;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.rwy_active = false;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.nav_active = FmgcComputer_DWork.Memory_PreviousInput_ip;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.loc_cpt_active = FmgcComputer_DWork.Memory_PreviousInput_cv;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.loc_trk_active = false;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.roll_goaround_active = FmgcComputer_DWork.Memory_PreviousInput_e;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.hdg_active = rtb_y_k4;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.trk_active = rtb_Logic_e_idx_0_tmp;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.rwy_loc_submode_active = FmgcComputer_DWork.Memory_PreviousInput_c;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.rwy_trk_submode_active = false;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.land_active = FmgcComputer_DWork.Memory_PreviousInput_d;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.align_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.align_submode_active;
    FmgcComputer_Y.out.ap_fd_logic.lateral_modes.rollout_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.rollout_submode_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.clb_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.clb_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.des_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.des_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.pitch_takeoff_active = FmgcComputer_DWork.Memory_PreviousInput_k;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.pitch_goaround_active = FmgcComputer_DWork.Memory_PreviousInput_i;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.vs_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.vs_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.fpa_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.fpa_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.alt_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.alt_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.trk_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.trk_submode_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.capt_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.capt_submode_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.gs_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.gs_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.final_des_active = FmgcComputer_DWork.Memory_PreviousInput_f;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.expedite_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.expedite_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.flare_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.flare_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.cruise_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.cruise_active;
    FmgcComputer_Y.out.ap_fd_logic.longitudinal_modes.tcas_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.tcas_active;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.alt_acq_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.alt_acq_armed;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.alt_acq_arm_possible =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.alt_acq_arm_possible;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.nav_armed = FmgcComputer_DWork.Memory_PreviousInput_i1;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.nav_arm_possible =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.nav_arm_possible;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.loc_armed = FmgcComputer_DWork.Memory_PreviousInput_a;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.land_armed = FmgcComputer_DWork.Memory_PreviousInput_l;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.glide_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.glide_armed;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.final_des_armed = FmgcComputer_DWork.Memory_PreviousInput_dv;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.clb_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.clb_armed;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.des_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.des_armed;
    FmgcComputer_Y.out.ap_fd_logic.armed_modes.tcas_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.tcas_armed;
    FmgcComputer_Y.out.ap_fd_logic.auto_spd_control_active = false;
    FmgcComputer_Y.out.ap_fd_logic.manual_spd_control_active = false;
    FmgcComputer_Y.out.ap_fd_logic.fmgc_opp_mode_sync = rtb_fmgcOppPriority_tmp;
    FmgcComputer_Y.out.ap_fd_logic.any_ap_fd_engaged = rtb_fmgcOppPriority_tmp_0;
    FmgcComputer_Y.out.ap_fd_logic.any_lateral_mode_engaged = false;
    FmgcComputer_Y.out.ap_fd_logic.any_longitudinal_mode_engaged = false;
    FmgcComputer_Y.out.ap_fd_logic.hdg_trk_preset_available = rtb_Logic_gj_idx_0_tmp;
    FmgcComputer_Y.out.ap_fd_logic.ap_fd_mode_reversion =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.ap_fd_mode_reversion;
    FmgcComputer_Y.out.ap_fd_logic.pitch_fd_bars_flashing =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.pitch_fd_bars_flashing;
    FmgcComputer_Y.out.ap_fd_logic.roll_fd_bars_flashing =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.roll_fd_bars_flashing;
    FmgcComputer_Y.out.ap_fd_logic.loc_bc_selection =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.loc_bc_selection;
    FmgcComputer_Y.out.ap_fd_logic.vs_target_not_held =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.vs_target_not_held;
    FmgcComputer_Y.out.ap_fd_logic.tcas_ra_inhibited =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.tcas_ra_inhibited;
    FmgcComputer_Y.out.ap_fd_logic.trk_fpa_deselected =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.trk_fpa_deselected;
    FmgcComputer_Y.out.ap_fd_logic.longi_large_box_tcas =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longi_large_box_tcas;
    FmgcComputer_Y.out.ap_fd_logic.land_2_capability = false;
    FmgcComputer_Y.out.ap_fd_logic.land_3_fail_passive_capability = false;
    FmgcComputer_Y.out.ap_fd_logic.land_3_fail_op_capability = false;
    FmgcComputer_Y.out.ap_fd_logic.land_2_inop = true;
    FmgcComputer_Y.out.ap_fd_logic.land_3_fail_passive_inop = true;
    FmgcComputer_Y.out.ap_fd_logic.land_3_fail_op_inop = true;
    FmgcComputer_Y.out.ap_fd_logic.land_2_capacity = rtb_Memory;
    FmgcComputer_Y.out.ap_fd_logic.land_3_fail_passive_capacity = rtb_OR_d;
    FmgcComputer_Y.out.ap_fd_logic.land_3_fail_op_capacity = rtb_appCapacity_idx_2;
    FmgcComputer_Y.out.discrete_outputs.athr_own_engaged = FmgcComputer_DWork.Memory_PreviousInput_p;
    FmgcComputer_Y.out.discrete_outputs.fd_own_engaged = fdOwnOff;
    FmgcComputer_Y.out.discrete_outputs.ap_own_engaged = FmgcComputer_DWork.Delay_DSTATE_p;
    FmgcComputer_Y.out.discrete_outputs.fcu_own_fail = FmgcComputer_P.Constant_Value;
    FmgcComputer_Y.out.discrete_outputs.fmgc_healthy = FmgcComputer_P.Constant1_Value_i;
    FmgcComputer_Y.out.discrete_outputs.ils_test_inhibit = FmgcComputer_P.Constant_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.pfd_sel_spd_kts.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.pfd_sel_spd_kts.Data = FmgcComputer_P.Constant17_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.runway_hdg_memorized_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.runway_hdg_memorized_deg.Data = FmgcComputer_P.Constant18_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.preset_mach_from_mcdu.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.preset_mach_from_mcdu.Data = FmgcComputer_P.Constant19_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.preset_speed_from_mcdu_kts.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.preset_speed_from_mcdu_kts.Data = FmgcComputer_P.Constant20_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.roll_fd_command.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.roll_fd_command.Data = FmgcComputer_P.Constant16_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.pitch_fd_command.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.pitch_fd_command.Data = FmgcComputer_P.Constant1_Value;
    if (FmgcComputer_DWork.Memory_PreviousInput_c ||
        FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.align_submode_active ||
        FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.rollout_submode_active) {
      FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.yaw_fd_command.SSM = static_cast<uint32_T>
        (FmgcComputer_P.EnumeratedConstant1_Value);
    } else {
      FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.yaw_fd_command.SSM = static_cast<uint32_T>
        (FmgcComputer_P.EnumeratedConstant_Value);
    }

    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.yaw_fd_command.Data = FmgcComputer_P.Constant2_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_5.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_5.Data = rtb_y_bb;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_4.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_4.Data = rtb_y_osy;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.fm_alt_constraint_ft.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.fm_alt_constraint_ft.Data = FmgcComputer_P.Constant21_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.altitude_ft.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.altitude_ft.Data = FmgcComputer_P.Constant22_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.mach.SSM = static_cast<uint32_T>(FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.mach.Data = FmgcComputer_P.Constant23_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.cas_kts.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.cas_kts.Data = FmgcComputer_P.Constant24_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.flx_to_temp_deg_c.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.flx_to_temp_deg_c.Data = FmgcComputer_P.Constant25_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_discrete_word.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_discrete_word.Data = rtb_y_je;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_fma_discrete_word.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_fma_discrete_word.Data = rtb_y_a1;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_3.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_3.Data = rtb_y_ou;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_1.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_1.Data = rtb_y_pn;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_2.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_2.Data = rtb_y_i;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_6.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_6.Data = rtb_y_kh;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.synchro_spd_mach_value.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.synchro_spd_mach_value.Data = FmgcComputer_P.Constant26_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.low_target_speed_margin_kts.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.low_target_speed_margin_kts.Data = FmgcComputer_P.Constant27_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.high_target_speed_margin_kts.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.high_target_speed_margin_kts.Data = FmgcComputer_P.Constant28_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_p_ail_voted_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_p_ail_voted_cmd_deg.Data = FmgcComputer_P.Constant11_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_p_splr_voted_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_p_splr_voted_cmd_deg.Data = FmgcComputer_P.Constant12_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_r_voted_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_r_voted_cmd_deg.Data = FmgcComputer_P.Constant13_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_nosewheel_voted_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_nosewheel_voted_cmd_deg.Data = FmgcComputer_P.Constant14_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_q_voted_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.delta_q_voted_cmd_deg.Data = FmgcComputer_P.Constant15_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.track_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.track_deg.Data = FmgcComputer_P.Constant29_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.heading_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.heading_deg.Data = FmgcComputer_P.Constant30_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.fpa_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.fpa_deg.Data = FmgcComputer_P.Constant31_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.n1_command_percent.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.n1_command_percent.Data = FmgcComputer_P.Constant32_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.vertical_speed_ft_min.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.vertical_speed_ft_min.Data = FmgcComputer_P.Constant33_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_weight_lbs.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_d);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_weight_lbs.Data = FmgcComputer_P.Constant1_Value_k;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_weight_lbs.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_d);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_weight_lbs.Data = FmgcComputer_P.Constant1_Value_k;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_cg_percent.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_d);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_cg_percent.Data = FmgcComputer_P.Constant1_Value_k;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_cg_percent.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_d);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_cg_percent.Data = FmgcComputer_P.Constant1_Value_k;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fg_radio_height_ft.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_d);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fg_radio_height_ft.Data = FmgcComputer_P.Constant1_Value_k;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_4.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_4.Data = rtb_y_osy;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.ats_discrete_word.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.ats_discrete_word.Data = rtb_y_je;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_3.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_3.Data = rtb_y_ou;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_1.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_1.Data = rtb_y_pn;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_2.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_2.Data = rtb_y_i;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.approach_spd_target_kn.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_d);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.approach_spd_target_kn.Data = FmgcComputer_P.Constant11_Value_m;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_p_ail_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_p_ail_cmd_deg.Data = FmgcComputer_P.Constant11_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_p_splr_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_p_splr_cmd_deg.Data = FmgcComputer_P.Constant12_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_r_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_r_cmd_deg.Data = FmgcComputer_P.Constant13_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_nose_wheel_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_nose_wheel_cmd_deg.Data = FmgcComputer_P.Constant14_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_q_cmd_deg.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.delta_q_cmd_deg.Data = FmgcComputer_P.Constant15_Value;
    FmgcComputer_MATLABFunction_f(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5, &rtb_adrOppInvalid);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5,
      FmgcComputer_P.BitfromLabel_bit_l2, &rtb_y_py);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5,
      FmgcComputer_P.BitfromLabel1_bit_pu, &rtb_y_py);
    FmgcComputer_MATLABFunction_k(&FmgcComputer_U.in.bus_inputs.fac_own_bus.discrete_word_5,
      FmgcComputer_P.BitfromLabel2_bit_l, &rtb_y_py);
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.rwy_active = false;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.nav_active = FmgcComputer_DWork.Memory_PreviousInput_ip;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.loc_cpt_active = FmgcComputer_DWork.Memory_PreviousInput_cv;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.loc_trk_active = false;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.roll_goaround_active = FmgcComputer_DWork.Memory_PreviousInput_e;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.hdg_active = rtb_y_k4;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.trk_active = rtb_Logic_e_idx_0_tmp;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.rwy_loc_submode_active = FmgcComputer_DWork.Memory_PreviousInput_c;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.rwy_trk_submode_active = false;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.land_active = FmgcComputer_DWork.Memory_PreviousInput_d;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.align_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.align_submode_active;
    FmgcComputer_DWork.Delay_DSTATE.lateral_modes.rollout_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.lateral_modes.rollout_submode_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.clb_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.clb_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.des_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.des_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.pitch_takeoff_active = FmgcComputer_DWork.Memory_PreviousInput_k;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.pitch_goaround_active = FmgcComputer_DWork.Memory_PreviousInput_i;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.vs_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.vs_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.fpa_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.fpa_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.alt_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.alt_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.trk_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.trk_submode_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.capt_submode_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.capt_submode_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.gs_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.gs_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.final_des_active = FmgcComputer_DWork.Memory_PreviousInput_f;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.expedite_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.expedite_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.flare_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.flare_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.cruise_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.cruise_active;
    FmgcComputer_DWork.Delay_DSTATE.longitudinal_modes.tcas_active =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longitudinal_modes.tcas_active;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.alt_acq_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.alt_acq_armed;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.alt_acq_arm_possible =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.alt_acq_arm_possible;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.nav_armed = FmgcComputer_DWork.Memory_PreviousInput_i1;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.nav_arm_possible =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.nav_arm_possible;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.loc_armed = FmgcComputer_DWork.Memory_PreviousInput_a;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.land_armed = FmgcComputer_DWork.Memory_PreviousInput_l;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.glide_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.glide_armed;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.final_des_armed = FmgcComputer_DWork.Memory_PreviousInput_dv;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.clb_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.clb_armed;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.des_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.des_armed;
    FmgcComputer_DWork.Delay_DSTATE.armed_modes.tcas_armed =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.armed_modes.tcas_armed;
    FmgcComputer_DWork.Delay_DSTATE.auto_spd_control_active = false;
    FmgcComputer_DWork.Delay_DSTATE.manual_spd_control_active = false;
    FmgcComputer_DWork.Delay_DSTATE.fmgc_opp_mode_sync = rtb_fmgcOppPriority_tmp;
    FmgcComputer_DWork.Delay_DSTATE.any_ap_fd_engaged = rtb_fmgcOppPriority_tmp_0;
    FmgcComputer_DWork.Delay_DSTATE.any_lateral_mode_engaged = false;
    FmgcComputer_DWork.Delay_DSTATE.any_longitudinal_mode_engaged = false;
    FmgcComputer_DWork.Delay_DSTATE.hdg_trk_preset_available = rtb_Logic_gj_idx_0_tmp;
    FmgcComputer_DWork.Delay_DSTATE.ap_fd_mode_reversion =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.ap_fd_mode_reversion;
    FmgcComputer_DWork.Delay_DSTATE.pitch_fd_bars_flashing =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.pitch_fd_bars_flashing;
    FmgcComputer_DWork.Delay_DSTATE.roll_fd_bars_flashing =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.roll_fd_bars_flashing;
    FmgcComputer_DWork.Delay_DSTATE.loc_bc_selection =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.loc_bc_selection;
    FmgcComputer_DWork.Delay_DSTATE.vs_target_not_held =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.vs_target_not_held;
    FmgcComputer_DWork.Delay_DSTATE.tcas_ra_inhibited =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.tcas_ra_inhibited;
    FmgcComputer_DWork.Delay_DSTATE.trk_fpa_deselected =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.trk_fpa_deselected;
    FmgcComputer_DWork.Delay_DSTATE.longi_large_box_tcas =
      FmgcComputer_P.fmgc_ap_fd_logic_output_MATLABStruct.longi_large_box_tcas;
    FmgcComputer_DWork.Delay_DSTATE.land_2_capability = false;
    FmgcComputer_DWork.Delay_DSTATE.land_3_fail_passive_capability = false;
    FmgcComputer_DWork.Delay_DSTATE.land_3_fail_op_capability = false;
    FmgcComputer_DWork.Delay_DSTATE.land_2_inop = true;
    FmgcComputer_DWork.Delay_DSTATE.land_3_fail_passive_inop = true;
    FmgcComputer_DWork.Delay_DSTATE.land_3_fail_op_inop = true;
    FmgcComputer_DWork.Delay_DSTATE.land_2_capacity = rtb_Memory;
    FmgcComputer_DWork.Delay_DSTATE.land_3_fail_passive_capacity = rtb_OR_d;
    FmgcComputer_DWork.Delay_DSTATE.land_3_fail_op_capacity = rtb_appCapacity_idx_2;
    FmgcComputer_DWork.Memory_PreviousInput_g = FmgcComputer_DWork.Delay_DSTATE_p;
  } else {
    FmgcComputer_DWork.Runtime_MODE = false;
  }
}

void FmgcComputer::initialize()
{
  FmgcComputer_DWork.Delay_DSTATE = FmgcComputer_P.Delay_InitialCondition;
  FmgcComputer_DWork.Delay_DSTATE_p = FmgcComputer_P.Delay_InitialCondition_g;
  FmgcComputer_DWork.Memory_PreviousInput = FmgcComputer_P.SRFlipFlop1_initial_condition;
  FmgcComputer_DWork.Memory_PreviousInput_g = FmgcComputer_P.SRFlipFlop_initial_condition;
  FmgcComputer_DWork.Memory_PreviousInput_p = FmgcComputer_P.SRFlipFlop_initial_condition_b;
  FmgcComputer_DWork.Memory_PreviousInput_k = FmgcComputer_P.SRFlipFlop_initial_condition_h;
  FmgcComputer_DWork.Memory_PreviousInput_c = FmgcComputer_P.SRFlipFlop_initial_condition_i;
  FmgcComputer_DWork.Memory_PreviousInput_l = FmgcComputer_P.SRFlipFlop_initial_condition_d;
  FmgcComputer_DWork.Memory_PreviousInput_d = FmgcComputer_P.SRFlipFlop_initial_condition_iz;
  FmgcComputer_DWork.Memory_PreviousInput_dv = FmgcComputer_P.SRFlipFlop_initial_condition_l;
  FmgcComputer_DWork.Memory_PreviousInput_f = FmgcComputer_P.SRFlipFlop_initial_condition_j;
  FmgcComputer_DWork.Memory_PreviousInput_i = FmgcComputer_P.SRFlipFlop_initial_condition_h5;
  FmgcComputer_DWork.Memory_PreviousInput_e = FmgcComputer_P.SRFlipFlop_initial_condition_e;
  FmgcComputer_DWork.Memory_PreviousInput_f2 = FmgcComputer_P.SRFlipFlop_initial_condition_c;
  FmgcComputer_DWork.Memory_PreviousInput_i1 = FmgcComputer_P.SRFlipFlop_initial_condition_o;
  FmgcComputer_DWork.Memory_PreviousInput_ip = FmgcComputer_P.SRFlipFlop_initial_condition_g;
  FmgcComputer_DWork.Memory_PreviousInput_a = FmgcComputer_P.SRFlipFlop_initial_condition_n;
  FmgcComputer_DWork.Memory_PreviousInput_cv = FmgcComputer_P.SRFlipFlop_initial_condition_of;
  FmgcComputer_Y.out = FmgcComputer_P.out_Y0;
}

void FmgcComputer::terminate()
{
}

FmgcComputer::FmgcComputer():
  FmgcComputer_U(),
  FmgcComputer_Y(),
  FmgcComputer_DWork()
{
}

FmgcComputer::~FmgcComputer()
{
}
