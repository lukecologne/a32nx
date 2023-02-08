#include "FmgcComputer.h"
#include "rtwtypes.h"
#include "FmgcComputer_types.h"

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

void FmgcComputer::FmgcComputer_MATLABFunction_g(const boolean_T rtu_u[19], real32_T *rty_y)
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
  real32_T rtb_V_ias;
  real32_T rtb_V_tas;
  real32_T rtb_alpha;
  real32_T rtb_alt;
  real32_T rtb_mach;
  real32_T rtb_p_s_c;
  real32_T rtb_phi;
  real32_T rtb_theta;
  boolean_T rtb_VectorConcatenate[19];
  boolean_T rtb_ir3Invalid;
  if (FmgcComputer_U.in.sim_data.computer_running) {
    real32_T rtb_n_x;
    real32_T rtb_n_y;
    real32_T rtb_n_z;
    real32_T rtb_phi_dot;
    real32_T rtb_q;
    real32_T rtb_r;
    real32_T rtb_theta_dot;
    boolean_T rtb_adr3Invalid;
    boolean_T rtb_adrOppInvalid;
    boolean_T rtb_adrOwnInvalid;
    boolean_T rtb_irOppInvalid;
    boolean_T rtb_irOwnInvalid;
    boolean_T rtb_y_h;
    if (!FmgcComputer_DWork.Runtime_MODE) {
      FmgcComputer_DWork.Delay_DSTATE = FmgcComputer_P.Delay_InitialCondition;
      FmgcComputer_DWork.Memory_PreviousInput = FmgcComputer_P.SRFlipFlop1_initial_condition;
      FmgcComputer_DWork.Memory_PreviousInput_g = FmgcComputer_P.SRFlipFlop_initial_condition;
      FmgcComputer_MATLABFunction_Reset(&FmgcComputer_DWork.sf_MATLABFunction_m);
      FmgcComputer_DWork.previousInput_not_empty = false;
      FmgcComputer_MATLABFunction_Reset(&FmgcComputer_DWork.sf_MATLABFunction);
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
      rtb_mach = FmgcComputer_U.in.bus_inputs.adr_own_bus.mach.Data;
      rtb_alpha = FmgcComputer_U.in.bus_inputs.adr_own_bus.aoa_corrected_deg.Data;
      rtb_p_s_c = FmgcComputer_U.in.bus_inputs.adr_own_bus.corrected_average_static_pressure.Data;
      rtb_alt = FmgcComputer_U.in.bus_inputs.adr_own_bus.altitude_corrected_ft.Data;
    } else if (!rtb_adr3Invalid) {
      rtb_V_ias = FmgcComputer_U.in.bus_inputs.adr_3_bus.airspeed_computed_kn.Data;
      rtb_V_tas = FmgcComputer_U.in.bus_inputs.adr_3_bus.airspeed_true_kn.Data;
      rtb_mach = FmgcComputer_U.in.bus_inputs.adr_3_bus.mach.Data;
      rtb_alpha = FmgcComputer_U.in.bus_inputs.adr_3_bus.aoa_corrected_deg.Data;
      rtb_p_s_c = FmgcComputer_U.in.bus_inputs.adr_3_bus.corrected_average_static_pressure.Data;
      rtb_alt = FmgcComputer_U.in.bus_inputs.adr_own_bus.altitude_corrected_ft.Data;
    } else {
      rtb_V_ias = 0.0F;
      rtb_V_tas = 0.0F;
      rtb_mach = 0.0F;
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
    rtb_irOwnInvalid = (rtb_adrOppInvalid || rtb_irOppInvalid);
    FmgcComputer_MATLABFunction(rtb_irOwnInvalid, FmgcComputer_U.in.time.dt, FmgcComputer_P.ConfirmNode_isRisingEdge,
      FmgcComputer_P.ConfirmNode_timeDelay, &rtb_ir3Invalid, &FmgcComputer_DWork.sf_MATLABFunction_m);
    FmgcComputer_Y.out.logic.fd_own_engaged = rtb_ir3Invalid;
    if (!FmgcComputer_DWork.previousInput_not_empty) {
      FmgcComputer_DWork.previousInput = FmgcComputer_P.PulseNode_isRisingEdge;
      FmgcComputer_DWork.previousInput_not_empty = true;
    }

    if (FmgcComputer_P.PulseNode_isRisingEdge) {
      rtb_y_h = (FmgcComputer_U.in.discrete_inputs.fcu_ap_button && (!FmgcComputer_DWork.previousInput));
    } else {
      rtb_y_h = ((!FmgcComputer_U.in.discrete_inputs.fcu_ap_button) && FmgcComputer_DWork.previousInput);
    }

    FmgcComputer_DWork.previousInput = FmgcComputer_U.in.discrete_inputs.fcu_ap_button;
    FmgcComputer_DWork.Memory_PreviousInput = FmgcComputer_P.Logic_table[(((static_cast<uint32_T>(rtb_y_h &&
      (!FmgcComputer_DWork.Delay_DSTATE) && rtb_irOwnInvalid) << 1) + ((!rtb_irOwnInvalid) || (rtb_y_h &&
      FmgcComputer_DWork.Delay_DSTATE))) << 1) + FmgcComputer_DWork.Memory_PreviousInput];
    FmgcComputer_MATLABFunction(FmgcComputer_DWork.Memory_PreviousInput, FmgcComputer_U.in.time.dt,
      FmgcComputer_P.ConfirmNode_isRisingEdge_k, FmgcComputer_P.ConfirmNode_timeDelay_b, &rtb_ir3Invalid,
      &FmgcComputer_DWork.sf_MATLABFunction);
    FmgcComputer_DWork.Delay_DSTATE = FmgcComputer_P.Logic_table_h[(((static_cast<uint32_T>(rtb_y_h &&
      FmgcComputer_DWork.Memory_PreviousInput) << 1) + ((!rtb_ir3Invalid) ||
      FmgcComputer_U.in.discrete_inputs.ap_instinctive_disc)) << 1) + FmgcComputer_DWork.Memory_PreviousInput_g];
    FmgcComputer_Y.out.data = FmgcComputer_U.in;
    FmgcComputer_Y.out.logic.on_ground = FmgcComputer_P.fmgc_logic_output_MATLABStruct.on_ground;
    FmgcComputer_Y.out.logic.ap_fd_athr_common_condition = rtb_irOwnInvalid;
    FmgcComputer_Y.out.logic.ap_fd_common_condition = true;
    FmgcComputer_Y.out.logic.double_adr_failure = rtb_adrOppInvalid;
    FmgcComputer_Y.out.logic.double_ir_failure = rtb_irOppInvalid;
    FmgcComputer_Y.out.logic.adr_computation_data.V_ias_kn = rtb_V_ias;
    FmgcComputer_Y.out.logic.adr_computation_data.V_tas_kn = rtb_V_tas;
    FmgcComputer_Y.out.logic.adr_computation_data.mach = rtb_mach;
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
    rtb_adrOppInvalid = !rtb_adr3Invalid;
    rtb_irOppInvalid = !rtb_adrOwnInvalid;
    if (rtb_irOppInvalid && rtb_adrOppInvalid) {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = FmgcComputer_U.in.bus_inputs.ra_own_bus.radio_height_ft.Data;
    } else if (rtb_adrOwnInvalid && rtb_adrOppInvalid) {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = FmgcComputer_U.in.bus_inputs.ra_opp_bus.radio_height_ft.Data;
    } else if (rtb_irOppInvalid && rtb_adr3Invalid) {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = FmgcComputer_U.in.bus_inputs.ra_own_bus.radio_height_ft.Data;
    } else {
      FmgcComputer_Y.out.logic.ra_computation_data_ft = 250.0;
    }

    FmgcComputer_Y.out.logic.dual_ra_failure = (rtb_adrOwnInvalid && rtb_adr3Invalid);
    FmgcComputer_Y.out.logic.ap_own_engaged = FmgcComputer_DWork.Delay_DSTATE;
    FmgcComputer_Y.out.logic.athr_own_engaged = false;
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant10_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant10_Value;
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_V_ias);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant3_Value_m;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant3_Value_m;
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_V_tas);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant4_Value_g;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant4_Value_g;
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_mach);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant5_Value_a;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant5_Value_a;
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_alpha);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant6_Value_l;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant6_Value_l;
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_p_s_c);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant7_Value_b;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant7_Value_b;
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_alt);
    rtb_VectorConcatenate[0] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[1] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[2] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[3] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[4] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[5] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[6] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[7] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[8] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[9] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[10] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[11] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[12] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[13] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[14] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[15] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[16] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[17] = FmgcComputer_P.Constant8_Value;
    rtb_VectorConcatenate[18] = FmgcComputer_P.Constant8_Value;
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_theta);
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
    FmgcComputer_MATLABFunction_g(rtb_VectorConcatenate, &rtb_phi);
    FmgcComputer_Y.out.discrete_outputs.athr_own_engaged = FmgcComputer_Y.out.logic.athr_own_engaged;
    FmgcComputer_Y.out.discrete_outputs.fd_own_engaged = FmgcComputer_Y.out.logic.fd_own_engaged;
    FmgcComputer_Y.out.discrete_outputs.ap_own_engaged = FmgcComputer_Y.out.logic.ap_own_engaged;
    FmgcComputer_Y.out.discrete_outputs.fcu_own_fail = FmgcComputer_P.Constant_Value_m;
    FmgcComputer_Y.out.discrete_outputs.fmgc_healthy = FmgcComputer_P.Constant1_Value_i;
    FmgcComputer_Y.out.discrete_outputs.ils_test_inhibit = FmgcComputer_P.Constant_Value_m;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.roll_fd_command.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.roll_fd_command.Data = FmgcComputer_P.Constant16_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.pitch_fd_command.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.pitch_fd_command.Data = FmgcComputer_P.Constant1_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.yaw_fd_command.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.yaw_fd_command.Data = FmgcComputer_P.Constant2_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_5.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_5.Data = rtb_V_ias;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_4.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_4.Data = rtb_V_tas;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_discrete_word.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_discrete_word.Data = rtb_mach;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_fma_discrete_word.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.ats_fma_discrete_word.Data = rtb_alpha;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_3.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_3.Data = rtb_p_s_c;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_1.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_1.Data = rtb_alt;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_2.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_2.Data = rtb_theta;
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_6.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_a_bus.discrete_word_6.Data = rtb_phi;
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
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_weight_lbs.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_weight_lbs.Data = FmgcComputer_P.Constant_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_weight_lbs.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_weight_lbs.Data = FmgcComputer_P.Constant1_Value_e;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_cg_percent.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fac_cg_percent.Data = FmgcComputer_P.Constant2_Value_l;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_cg_percent.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fm_cg_percent.Data = FmgcComputer_P.Constant3_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fg_radio_height_ft.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.fg_radio_height_ft.Data = FmgcComputer_P.Constant4_Value_n;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_4.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_4.Data = rtb_V_tas;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.ats_discrete_word.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.ats_discrete_word.Data = rtb_mach;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_3.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_3.Data = rtb_p_s_c;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_1.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_1.Data = rtb_alt;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_2.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.discrete_word_2.Data = rtb_theta;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.approach_spd_target_kn.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.approach_spd_target_kn.Data = FmgcComputer_P.Constant5_Value;
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
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.n1_left_percent.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.n1_left_percent.Data = FmgcComputer_P.Constant6_Value;
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.n1_right_percent.SSM = static_cast<uint32_T>
      (FmgcComputer_P.EnumeratedConstant1_Value_a);
    FmgcComputer_Y.out.bus_outputs.fmgc_b_bus.n1_right_percent.Data = FmgcComputer_P.Constant7_Value;
    FmgcComputer_DWork.Memory_PreviousInput_g = FmgcComputer_DWork.Delay_DSTATE;
  } else {
    FmgcComputer_DWork.Runtime_MODE = false;
  }
}

void FmgcComputer::initialize()
{
  FmgcComputer_DWork.Delay_DSTATE = FmgcComputer_P.Delay_InitialCondition;
  FmgcComputer_DWork.Memory_PreviousInput = FmgcComputer_P.SRFlipFlop1_initial_condition;
  FmgcComputer_DWork.Memory_PreviousInput_g = FmgcComputer_P.SRFlipFlop_initial_condition;
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
