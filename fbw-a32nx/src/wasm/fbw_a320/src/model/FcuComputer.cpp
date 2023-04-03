#include "FcuComputer.h"
#include "FcuComputer_types.h"
#include "rtwtypes.h"
#include <cmath>

void FcuComputer::FcuComputer_MATLABFunction(const base_arinc_429 *rtu_u, real_T rtu_bit, uint32_T *rty_y)
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

void FcuComputer::FcuComputer_MATLABFunction_f_Reset(rtDW_MATLABFunction_FcuComputer_c_T *localDW)
{
  localDW->previousInput_not_empty = false;
}

void FcuComputer::FcuComputer_MATLABFunction_a(boolean_T rtu_u, boolean_T rtu_isRisingEdge, boolean_T *rty_y,
  rtDW_MATLABFunction_FcuComputer_c_T *localDW)
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

void FcuComputer::FcuComputer_EFISFilterLogic_Reset(rtDW_EFISFilterLogic_FcuComputer_T *localDW)
{
  localDW->pEfisFilter = efis_filter_selection::NONE;
}

void FcuComputer::FcuComputer_EFISFilterLogic(boolean_T rtu_cstr, boolean_T rtu_wpt, boolean_T rtu_vord, boolean_T
  rtu_ndb, boolean_T rtu_arpt, efis_filter_selection *rty_efisFilter, rtDW_EFISFilterLogic_FcuComputer_T *localDW)
{
  if (((localDW->pEfisFilter == efis_filter_selection::CSTR) && rtu_cstr) || ((localDW->pEfisFilter ==
        efis_filter_selection::WPT) && rtu_wpt) || ((localDW->pEfisFilter == efis_filter_selection::VORD) && rtu_vord) ||
      ((localDW->pEfisFilter == efis_filter_selection::NDB) && rtu_ndb) || ((localDW->pEfisFilter ==
        efis_filter_selection::ARPT) && rtu_arpt)) {
    localDW->pEfisFilter = efis_filter_selection::NONE;
  } else if (rtu_cstr) {
    localDW->pEfisFilter = efis_filter_selection::CSTR;
  } else if (rtu_wpt) {
    localDW->pEfisFilter = efis_filter_selection::WPT;
  } else if (rtu_vord) {
    localDW->pEfisFilter = efis_filter_selection::VORD;
  } else if (rtu_ndb) {
    localDW->pEfisFilter = efis_filter_selection::NDB;
  } else if (rtu_arpt) {
    localDW->pEfisFilter = efis_filter_selection::ARPT;
  }

  *rty_efisFilter = localDW->pEfisFilter;
}

void FcuComputer::FcuComputer_MATLABFunction_j_Init(rtDW_MATLABFunction_FcuComputer_b_T *localDW)
{
  localDW->qnh_active = true;
}

void FcuComputer::FcuComputer_MATLABFunction_a_Reset(rtDW_MATLABFunction_FcuComputer_b_T *localDW)
{
  localDW->std_active = false;
  localDW->qnh_active = true;
  localDW->qfe_active = false;
}

void FcuComputer::FcuComputer_MATLABFunction_p(boolean_T rtu_knob_push, boolean_T rtu_knob_pull, boolean_T *rty_std,
  boolean_T *rty_qnh, boolean_T *rty_qfe, rtDW_MATLABFunction_FcuComputer_b_T *localDW)
{
  if (rtu_knob_push && localDW->std_active) {
    localDW->std_active = false;
  } else if (rtu_knob_push && (!localDW->std_active)) {
    localDW->qnh_active = !localDW->qnh_active;
    localDW->qfe_active = !localDW->qfe_active;
  } else {
    localDW->std_active = ((rtu_knob_pull && (!localDW->std_active)) || localDW->std_active);
  }

  *rty_std = localDW->std_active;
  *rty_qnh = localDW->qnh_active;
  *rty_qfe = localDW->qfe_active;
}

void FcuComputer::FcuComputer_MATLABFunction1_Init(rtDW_MATLABFunction1_FcuComputer_T *localDW)
{
  localDW->pValueHpa = 1013.0;
  localDW->pValueInhg = 29.92;
}

void FcuComputer::FcuComputer_MATLABFunction1_Reset(rtDW_MATLABFunction1_FcuComputer_T *localDW)
{
  localDW->pValueHpa = 1013.0;
  localDW->pValueInhg = 29.92;
}

void FcuComputer::FcuComputer_MATLABFunction1(boolean_T rtu_std_active, boolean_T rtu_inhg_active, real_T
  rtu_click_count, real_T *rty_value_hpa, real_T *rty_value_inhg, rtDW_MATLABFunction1_FcuComputer_T *localDW)
{
  boolean_T tmp;
  tmp = !rtu_std_active;
  if (tmp && (!rtu_inhg_active)) {
    localDW->pValueHpa = std::fmax(std::fmin(localDW->pValueHpa + rtu_click_count, 1100.0), 745.0);
    localDW->pValueInhg = std::round(localDW->pValueHpa * 0.02953 * 100.0) / 100.0;
  } else if (tmp && rtu_inhg_active) {
    localDW->pValueInhg = std::fmax(std::fmin(rtu_click_count * 0.01 + localDW->pValueInhg, 32.48), 22.0);
    localDW->pValueHpa = localDW->pValueInhg * 33.863867253640365;
    localDW->pValueHpa = std::round(localDW->pValueHpa);
  }

  *rty_value_hpa = localDW->pValueHpa;
  *rty_value_inhg = localDW->pValueInhg;
}

void FcuComputer::FcuComputer_MATLABFunction_g_Reset(rtDW_MATLABFunction_FcuComputer_l_T *localDW)
{
  localDW->pY_not_empty = false;
}

void FcuComputer::FcuComputer_MATLABFunction_m(boolean_T rtu_u, boolean_T *rty_y, boolean_T rtp_init,
  rtDW_MATLABFunction_FcuComputer_l_T *localDW)
{
  if (!localDW->pY_not_empty) {
    localDW->pY = rtp_init;
    localDW->pY_not_empty = true;
  }

  if (rtu_u) {
    localDW->pY = !localDW->pY;
  }

  *rty_y = localDW->pY;
}

void FcuComputer::FcuComputer_MATLABFunction_e(const boolean_T rtu_u[19], real32_T *rty_y)
{
  uint32_T out;
  out = 0U;
  for (int32_T i{0}; i < 19; i++) {
    out |= static_cast<uint32_T>(rtu_u[i]) << (i + 10);
  }

  *rty_y = static_cast<real32_T>(out);
}

void FcuComputer::FcuComputer_MATLABFunction_n(const base_fcu_efis_logic_outputs *rtu_logic, const
  base_fcu_efis_panel_inputs *rtu_data, int8_T *rty_baroValueMode, real32_T *rty_baroValue, int8_T *rty_baroMode)
{
  int8_T baroValueMode;
  if (rtu_logic->baro_std) {
    baroValueMode = 0;
  } else if (!rtu_data->baro_is_inhg) {
    baroValueMode = 1;
  } else {
    baroValueMode = 2;
  }

  switch (baroValueMode) {
   case 1:
    *rty_baroValue = rtu_logic->baro_value_hpa;
    break;

   case 2:
    *rty_baroValue = rtu_logic->baro_value_inhg;
    break;

   default:
    *rty_baroValue = 0.0F;
    break;
  }

  if (rtu_logic->baro_std) {
    *rty_baroMode = 0;
  } else if (rtu_logic->baro_qnh) {
    *rty_baroMode = 1;
  } else {
    *rty_baroMode = 2;
  }

  *rty_baroValueMode = baroValueMode;
}

void FcuComputer::step()
{
  const base_arinc_429 *rtb_Switch_0;
  base_fcu_efis_logic_outputs rtb_BusAssignment_a_logic_capt_efis;
  base_fcu_efis_logic_outputs rtb_BusAssignment_a_logic_fo_efis;
  real_T rtb_value_hpa;
  real_T rtb_value_inhg;
  real32_T rtb_y;
  real32_T rtb_y_b;
  real32_T rtb_y_ea;
  real32_T rtb_y_g;
  real32_T rtb_y_i;
  real32_T rtb_y_l;
  uint32_T rtb_DataTypeConversion1;
  int8_T rtb_baroMode;
  int8_T rtb_baroValueMode;
  boolean_T rtb_VectorConcatenate[19];
  boolean_T rtb_Equal6;
  boolean_T rtb_Equal7;
  boolean_T rtb_Equal8;
  boolean_T rtb_Equal9;
  boolean_T rtb_OR;
  boolean_T rtb_qnh;
  boolean_T rtb_y_pv;
  efis_filter_selection rtb_efisFilter;
  if (FcuComputer_U.in.sim_data.computer_running) {
    real32_T rtb_BusAssignment_o_baro_value_hpa;
    real32_T rtb_BusAssignment_o_baro_value_inhg;
    real32_T rtb_BusConversion_InsertedFor_BusAssignment_at_inport_1_BusCreator1_fo_efis_outputs_baro_value;
    real32_T rtb_capt_efis_outputs_baro_value;
    int8_T rtb_capt_efis_outputs_baro_mode;
    int8_T rtb_capt_efis_outputs_baro_value_mode;
    boolean_T rtb_BusAssignment_o_baro_qnh;
    boolean_T rtb_BusAssignment_o_baro_std;
    boolean_T rtb_BusAssignment_o_fd_on;
    boolean_T rtb_BusAssignment_o_ls_on;
    efis_filter_selection rtb_BusAssignment_o_efis_filter;
    if (!FcuComputer_DWork.Runtime_MODE) {
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_h);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_n);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_id);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_g);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_bp);
      FcuComputer_EFISFilterLogic_Reset(&FcuComputer_DWork.sf_EFISFilterLogic);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_ik);
      FcuComputer_MATLABFunction_g_Reset(&FcuComputer_DWork.sf_MATLABFunction_m);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_j);
      FcuComputer_MATLABFunction_g_Reset(&FcuComputer_DWork.sf_MATLABFunction_k);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_hc);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_b3);
      FcuComputer_MATLABFunction_a_Reset(&FcuComputer_DWork.sf_MATLABFunction_p);
      FcuComputer_MATLABFunction1_Reset(&FcuComputer_DWork.sf_MATLABFunction1);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_f);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_e);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_hl);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_d);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_cb);
      FcuComputer_EFISFilterLogic_Reset(&FcuComputer_DWork.sf_EFISFilterLogic_h);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_ja0);
      FcuComputer_MATLABFunction_g_Reset(&FcuComputer_DWork.sf_MATLABFunction_ja);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_je);
      FcuComputer_MATLABFunction_g_Reset(&FcuComputer_DWork.sf_MATLABFunction_hk);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_ng);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_gx);
      FcuComputer_MATLABFunction_a_Reset(&FcuComputer_DWork.sf_MATLABFunction_jp);
      FcuComputer_MATLABFunction1_Reset(&FcuComputer_DWork.sf_MATLABFunction1_e);
      FcuComputer_MATLABFunction_f_Reset(&FcuComputer_DWork.sf_MATLABFunction_a4);
      FcuComputer_DWork.p_trk_fpa_active = false;
      FcuComputer_DWork.Runtime_MODE = true;
    }

    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.cstr_button_pushed,
      FcuComputer_P.PulseNode_isRisingEdge, &rtb_Equal7, &FcuComputer_DWork.sf_MATLABFunction_h);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.wpt_button_pushed,
      FcuComputer_P.PulseNode1_isRisingEdge, &rtb_Equal6, &FcuComputer_DWork.sf_MATLABFunction_n);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.vord_button_pushed,
      FcuComputer_P.PulseNode2_isRisingEdge, &rtb_OR, &FcuComputer_DWork.sf_MATLABFunction_id);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.ndb_button_pushed,
      FcuComputer_P.PulseNode3_isRisingEdge, &rtb_qnh, &FcuComputer_DWork.sf_MATLABFunction_g);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.arpt_button_pushed,
      FcuComputer_P.PulseNode4_isRisingEdge, &rtb_y_pv, &FcuComputer_DWork.sf_MATLABFunction_bp);
    FcuComputer_EFISFilterLogic(rtb_Equal7, rtb_Equal6, rtb_OR, rtb_qnh, rtb_y_pv, &rtb_efisFilter,
      &FcuComputer_DWork.sf_EFISFilterLogic);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.fd_button_pushed,
      FcuComputer_P.PulseNode_isRisingEdge_n, &rtb_y_pv, &FcuComputer_DWork.sf_MATLABFunction_ik);
    FcuComputer_MATLABFunction_m(rtb_y_pv, &rtb_OR, FcuComputer_P.TFlipFlop_init, &FcuComputer_DWork.sf_MATLABFunction_m);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.ls_button_pushed,
      FcuComputer_P.PulseNode_isRisingEdge_nj, &rtb_y_pv, &FcuComputer_DWork.sf_MATLABFunction_j);
    FcuComputer_MATLABFunction_m(rtb_y_pv, &rtb_qnh, FcuComputer_P.TFlipFlop1_init,
      &FcuComputer_DWork.sf_MATLABFunction_k);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.baro_knob.pushed,
      FcuComputer_P.PulseNode_isRisingEdge_a, &rtb_Equal6, &FcuComputer_DWork.sf_MATLABFunction_hc);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.baro_knob.pulled,
      FcuComputer_P.PulseNode1_isRisingEdge_h, &rtb_y_pv, &FcuComputer_DWork.sf_MATLABFunction_b3);
    FcuComputer_MATLABFunction_p(rtb_Equal6, rtb_y_pv, &rtb_Equal7, &rtb_Equal8, &rtb_Equal9,
      &FcuComputer_DWork.sf_MATLABFunction_p);
    FcuComputer_MATLABFunction1(rtb_Equal7, FcuComputer_U.in.discrete_inputs.capt_efis_inputs.baro_is_inhg, static_cast<
      real_T>(FcuComputer_U.in.discrete_inputs.capt_efis_inputs.baro_knob.turns), &rtb_value_inhg, &rtb_value_hpa,
      &FcuComputer_DWork.sf_MATLABFunction1);
    rtb_BusAssignment_o_efis_filter = rtb_efisFilter;
    rtb_BusAssignment_o_fd_on = rtb_OR;
    rtb_BusAssignment_o_ls_on = rtb_qnh;
    rtb_BusAssignment_o_baro_std = rtb_Equal7;
    rtb_BusAssignment_o_baro_qnh = rtb_Equal8;
    rtb_BusAssignment_a_logic_capt_efis.baro_qfe = rtb_Equal9;
    rtb_BusAssignment_o_baro_value_hpa = static_cast<real32_T>(rtb_value_inhg);
    rtb_BusAssignment_o_baro_value_inhg = static_cast<real32_T>(rtb_value_hpa);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.cstr_button_pushed,
      FcuComputer_P.PulseNode_isRisingEdge_m, &rtb_Equal7, &FcuComputer_DWork.sf_MATLABFunction_f);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.wpt_button_pushed,
      FcuComputer_P.PulseNode1_isRisingEdge_k, &rtb_Equal6, &FcuComputer_DWork.sf_MATLABFunction_e);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.vord_button_pushed,
      FcuComputer_P.PulseNode2_isRisingEdge_a, &rtb_OR, &FcuComputer_DWork.sf_MATLABFunction_hl);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.ndb_button_pushed,
      FcuComputer_P.PulseNode3_isRisingEdge_g, &rtb_qnh, &FcuComputer_DWork.sf_MATLABFunction_d);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.arpt_button_pushed,
      FcuComputer_P.PulseNode4_isRisingEdge_a, &rtb_y_pv, &FcuComputer_DWork.sf_MATLABFunction_cb);
    FcuComputer_EFISFilterLogic(rtb_Equal7, rtb_Equal6, rtb_OR, rtb_qnh, rtb_y_pv, &rtb_efisFilter,
      &FcuComputer_DWork.sf_EFISFilterLogic_h);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.fd_button_pushed,
      FcuComputer_P.PulseNode_isRisingEdge_i, &rtb_OR, &FcuComputer_DWork.sf_MATLABFunction_ja0);
    FcuComputer_MATLABFunction_m(rtb_OR, &rtb_Equal7, FcuComputer_P.TFlipFlop_init_f,
      &FcuComputer_DWork.sf_MATLABFunction_ja);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.ls_button_pushed,
      FcuComputer_P.PulseNode_isRisingEdge_h, &rtb_OR, &FcuComputer_DWork.sf_MATLABFunction_je);
    FcuComputer_MATLABFunction_m(rtb_OR, &rtb_Equal6, FcuComputer_P.TFlipFlop1_init_a,
      &FcuComputer_DWork.sf_MATLABFunction_hk);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.baro_knob.pushed,
      FcuComputer_P.PulseNode_isRisingEdge_o, &rtb_Equal8, &FcuComputer_DWork.sf_MATLABFunction_ng);
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.baro_knob.pulled,
      FcuComputer_P.PulseNode1_isRisingEdge_f, &rtb_OR, &FcuComputer_DWork.sf_MATLABFunction_gx);
    FcuComputer_MATLABFunction_p(rtb_Equal8, rtb_OR, &rtb_Equal9, &rtb_qnh, &rtb_y_pv,
      &FcuComputer_DWork.sf_MATLABFunction_jp);
    FcuComputer_MATLABFunction1(rtb_Equal9, FcuComputer_U.in.discrete_inputs.fo_efis_inputs.baro_is_inhg,
      static_cast<real_T>(FcuComputer_U.in.discrete_inputs.fo_efis_inputs.baro_knob.turns), &rtb_value_hpa,
      &rtb_value_inhg, &FcuComputer_DWork.sf_MATLABFunction1_e);
    rtb_y_g = static_cast<real32_T>(rtb_value_hpa);
    rtb_y_ea = static_cast<real32_T>(rtb_value_inhg);
    rtb_OR = !FcuComputer_U.in.discrete_inputs.ap_1_engaged;
    rtb_OR = (FcuComputer_U.in.discrete_inputs.ap_2_engaged || (rtb_OR && FcuComputer_U.in.discrete_inputs.fd_2_engaged)
              || (rtb_OR && (!FcuComputer_U.in.discrete_inputs.fd_1_engaged) &&
                  FcuComputer_U.in.discrete_inputs.athr_2_engaged));
    rtb_BusAssignment_a_logic_fo_efis.baro_qfe = rtb_y_pv;
    FcuComputer_MATLABFunction_a(FcuComputer_U.in.discrete_inputs.afs_inputs.trk_fpa_button_pressed,
      FcuComputer_P.PulseNode_isRisingEdge_oa, &rtb_y_pv, &FcuComputer_DWork.sf_MATLABFunction_a4);
    if (rtb_y_pv) {
      FcuComputer_DWork.p_trk_fpa_active = !FcuComputer_DWork.p_trk_fpa_active;
    }

    if (rtb_OR) {
      rtb_Switch_0 = &FcuComputer_U.in.bus_inputs.fmgc_1_bus.discrete_word_5;
    } else {
      rtb_Switch_0 = &FcuComputer_U.in.bus_inputs.fmgc_2_bus.discrete_word_5;
    }

    FcuComputer_MATLABFunction(rtb_Switch_0, FcuComputer_P.BitfromLabel_bit, &rtb_DataTypeConversion1);
    rtb_y_pv = (rtb_Switch_0->SSM == static_cast<uint32_T>(SignStatusMatrix::NormalOperation));
    FcuComputer_Y.out.logic.afs.auto_speed_control = ((rtb_DataTypeConversion1 != 0U) && rtb_y_pv);
    FcuComputer_MATLABFunction(rtb_Switch_0, FcuComputer_P.BitfromLabel1_bit, &rtb_DataTypeConversion1);
    FcuComputer_Y.out.logic.afs.selected_speed_control = (rtb_y_pv && (rtb_DataTypeConversion1 != 0U));
    rtb_BusAssignment_a_logic_capt_efis.fd_on = rtb_BusAssignment_o_fd_on;
    rtb_BusAssignment_a_logic_capt_efis.ls_on = rtb_BusAssignment_o_ls_on;
    rtb_BusAssignment_a_logic_capt_efis.efis_filter = rtb_BusAssignment_o_efis_filter;
    rtb_BusAssignment_a_logic_capt_efis.baro_std = rtb_BusAssignment_o_baro_std;
    rtb_BusAssignment_a_logic_capt_efis.baro_qnh = rtb_BusAssignment_o_baro_qnh;
    rtb_BusAssignment_a_logic_capt_efis.baro_value_hpa = rtb_BusAssignment_o_baro_value_hpa;
    rtb_BusAssignment_a_logic_capt_efis.baro_value_inhg = rtb_BusAssignment_o_baro_value_inhg;
    rtb_BusAssignment_a_logic_fo_efis.fd_on = rtb_Equal7;
    rtb_BusAssignment_a_logic_fo_efis.ls_on = rtb_Equal6;
    rtb_BusAssignment_a_logic_fo_efis.efis_filter = rtb_efisFilter;
    rtb_BusAssignment_a_logic_fo_efis.baro_std = rtb_Equal9;
    rtb_BusAssignment_a_logic_fo_efis.baro_qnh = rtb_qnh;
    rtb_BusAssignment_a_logic_fo_efis.baro_value_hpa = static_cast<real32_T>(rtb_value_hpa);
    rtb_BusAssignment_a_logic_fo_efis.baro_value_inhg = static_cast<real32_T>(rtb_value_inhg);
    FcuComputer_MATLABFunction_n(&rtb_BusAssignment_a_logic_capt_efis,
      &FcuComputer_U.in.discrete_inputs.capt_efis_inputs, &rtb_baroMode, &rtb_y_g, &rtb_baroValueMode);
    rtb_capt_efis_outputs_baro_value_mode = rtb_baroMode;
    rtb_capt_efis_outputs_baro_value = rtb_y_g;
    rtb_capt_efis_outputs_baro_mode = rtb_baroValueMode;
    FcuComputer_MATLABFunction_n(&rtb_BusAssignment_a_logic_fo_efis, &FcuComputer_U.in.discrete_inputs.fo_efis_inputs,
      &rtb_baroValueMode, &rtb_y_g, &rtb_baroMode);
    rtb_BusConversion_InsertedFor_BusAssignment_at_inport_1_BusCreator1_fo_efis_outputs_baro_value = rtb_y_g;
    rtb_VectorConcatenate[0] = FcuComputer_U.in.discrete_inputs.capt_efis_inputs.baro_is_inhg;
    rtb_VectorConcatenate[1] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[2] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[3] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[4] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[5] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[6] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[7] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[8] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[9] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[10] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[11] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[12] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[13] = FcuComputer_P.Constant10_Value_f;
    rtb_VectorConcatenate[14] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant2_Value_g);
    rtb_VectorConcatenate[15] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant1_Value_h);
    rtb_VectorConcatenate[16] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant3_Value_i);
    rtb_VectorConcatenate[17] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant4_Value_n);
    rtb_VectorConcatenate[18] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant5_Value_a);
    FcuComputer_MATLABFunction_e(rtb_VectorConcatenate, &rtb_y_i);
    rtb_VectorConcatenate[0] = FcuComputer_U.in.discrete_inputs.fo_efis_inputs.baro_is_inhg;
    rtb_VectorConcatenate[1] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[2] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[3] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[4] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[5] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[6] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[7] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[8] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[9] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[10] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[11] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[12] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[13] = FcuComputer_P.Constant10_Value_a;
    rtb_VectorConcatenate[14] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant2_Value_l);
    rtb_VectorConcatenate[15] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant1_Value_n);
    rtb_VectorConcatenate[16] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant3_Value_e);
    rtb_VectorConcatenate[17] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant4_Value_i);
    rtb_VectorConcatenate[18] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_range ==
      FcuComputer_P.EnumeratedConstant5_Value_k);
    FcuComputer_MATLABFunction_e(rtb_VectorConcatenate, &rtb_y);
    rtb_VectorConcatenate[0] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant2_Value);
    rtb_VectorConcatenate[1] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant1_Value_b);
    rtb_VectorConcatenate[2] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant3_Value);
    rtb_VectorConcatenate[3] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant4_Value);
    rtb_VectorConcatenate[4] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant5_Value);
    rtb_VectorConcatenate[5] = FcuComputer_P.Constant10_Value_p;
    rtb_VectorConcatenate[6] = (rtb_BusAssignment_o_efis_filter == FcuComputer_P.EnumeratedConstant7_Value_k);
    rtb_VectorConcatenate[7] = (rtb_BusAssignment_o_efis_filter == FcuComputer_P.EnumeratedConstant6_Value_l);
    rtb_VectorConcatenate[8] = (rtb_BusAssignment_o_efis_filter == FcuComputer_P.EnumeratedConstant8_Value_a);
    rtb_VectorConcatenate[9] = (rtb_BusAssignment_o_efis_filter == FcuComputer_P.EnumeratedConstant9_Value_g);
    rtb_VectorConcatenate[10] = (rtb_BusAssignment_o_efis_filter == FcuComputer_P.EnumeratedConstant10_Value_b);
    rtb_VectorConcatenate[11] = rtb_BusAssignment_o_ls_on;
    rtb_VectorConcatenate[12] = !rtb_BusAssignment_o_fd_on;
    rtb_VectorConcatenate[13] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_navaid_1 ==
      FcuComputer_P.EnumeratedConstant12_Value);
    rtb_VectorConcatenate[14] = (FcuComputer_P.EnumeratedConstant12_Value ==
      FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_navaid_2);
    rtb_VectorConcatenate[15] = (FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_navaid_1 ==
      FcuComputer_P.EnumeratedConstant11_Value);
    rtb_VectorConcatenate[16] = (FcuComputer_P.EnumeratedConstant11_Value ==
      FcuComputer_U.in.discrete_inputs.capt_efis_inputs.efis_navaid_2);
    rtb_VectorConcatenate[17] = rtb_BusAssignment_o_baro_std;
    rtb_VectorConcatenate[18] = rtb_BusAssignment_o_baro_qnh;
    FcuComputer_MATLABFunction_e(rtb_VectorConcatenate, &rtb_y_ea);
    rtb_VectorConcatenate[0] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant2_Value_a);
    rtb_VectorConcatenate[1] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant1_Value_m);
    rtb_VectorConcatenate[2] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant3_Value_l);
    rtb_VectorConcatenate[3] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant4_Value_b);
    rtb_VectorConcatenate[4] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_mode ==
      FcuComputer_P.EnumeratedConstant5_Value_e);
    rtb_VectorConcatenate[5] = FcuComputer_P.Constant10_Value_e;
    rtb_VectorConcatenate[6] = (rtb_efisFilter == FcuComputer_P.EnumeratedConstant7_Value_a);
    rtb_VectorConcatenate[7] = (rtb_efisFilter == FcuComputer_P.EnumeratedConstant6_Value_l4);
    rtb_VectorConcatenate[8] = (rtb_efisFilter == FcuComputer_P.EnumeratedConstant8_Value_p);
    rtb_VectorConcatenate[9] = (rtb_efisFilter == FcuComputer_P.EnumeratedConstant9_Value_o);
    rtb_VectorConcatenate[10] = (rtb_efisFilter == FcuComputer_P.EnumeratedConstant10_Value_e);
    rtb_VectorConcatenate[11] = rtb_Equal6;
    rtb_VectorConcatenate[12] = !rtb_Equal7;
    rtb_VectorConcatenate[13] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_navaid_1 ==
      FcuComputer_P.EnumeratedConstant12_Value_a);
    rtb_VectorConcatenate[14] = (FcuComputer_P.EnumeratedConstant12_Value_a ==
      FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_navaid_2);
    rtb_VectorConcatenate[15] = (FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_navaid_1 ==
      FcuComputer_P.EnumeratedConstant11_Value_o);
    rtb_VectorConcatenate[16] = (FcuComputer_P.EnumeratedConstant11_Value_o ==
      FcuComputer_U.in.discrete_inputs.fo_efis_inputs.efis_navaid_2);
    rtb_VectorConcatenate[17] = rtb_Equal9;
    rtb_VectorConcatenate[18] = rtb_qnh;
    FcuComputer_MATLABFunction_e(rtb_VectorConcatenate, &rtb_y_g);
    rtb_VectorConcatenate[0] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[1] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[2] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[3] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[4] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[5] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[6] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[7] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[8] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[9] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[10] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[11] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[12] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[13] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[14] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[15] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[16] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[17] = FcuComputer_P.Constant19_Value;
    rtb_VectorConcatenate[18] = FcuComputer_P.Constant19_Value;
    FcuComputer_MATLABFunction_e(rtb_VectorConcatenate, &rtb_y_b);
    rtb_VectorConcatenate[0] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[1] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[2] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[3] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[4] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[5] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[6] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[7] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[8] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[9] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[10] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[11] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[12] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[13] = !FcuComputer_DWork.p_trk_fpa_active;
    rtb_VectorConcatenate[14] = FcuComputer_DWork.p_trk_fpa_active;
    rtb_VectorConcatenate[15] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[16] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[17] = FcuComputer_P.Constant20_Value;
    rtb_VectorConcatenate[18] = FcuComputer_P.Constant20_Value;
    FcuComputer_MATLABFunction_e(rtb_VectorConcatenate, &rtb_y_l);
    FcuComputer_Y.out.data = FcuComputer_U.in;
    FcuComputer_Y.out.logic.afs.fmgc_1_has_priority = rtb_OR;
    FcuComputer_Y.out.logic.afs.trk_fpa_active = FcuComputer_DWork.p_trk_fpa_active;
    FcuComputer_Y.out.logic.afs.spd_mach_display_value = 0.0;
    FcuComputer_Y.out.logic.afs.spd_mach_dashes = false;
    FcuComputer_Y.out.logic.afs.hdg_trk_managed = false;
    FcuComputer_Y.out.logic.afs.hdg_trk_selected = false;
    FcuComputer_Y.out.logic.afs.hdg_trk_display_value = 0.0;
    FcuComputer_Y.out.logic.afs.hdg_trk_dashes = false;
    FcuComputer_Y.out.logic.afs.alt_display_value = 0.0;
    FcuComputer_Y.out.logic.afs.lvl_ch_managed = false;
    FcuComputer_Y.out.logic.afs.lvl_ch_selected = false;
    FcuComputer_Y.out.logic.afs.vs_fpa_display_value = FcuComputer_P.Constant1_Value.afs.vs_fpa_display_value;
    FcuComputer_Y.out.logic.afs.vs_fpa_dashes = FcuComputer_P.Constant1_Value.afs.vs_fpa_dashes;
    FcuComputer_Y.out.logic.afs.exped_active = FcuComputer_P.Constant1_Value.afs.exped_active;
    FcuComputer_Y.out.logic.afs.loc_only_active = FcuComputer_P.Constant1_Value.afs.loc_only_active;
    FcuComputer_Y.out.logic.afs.appr_active = FcuComputer_P.Constant1_Value.afs.appr_active;
    FcuComputer_Y.out.logic.capt_efis = rtb_BusAssignment_a_logic_capt_efis;
    FcuComputer_Y.out.logic.fo_efis = rtb_BusAssignment_a_logic_fo_efis;
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.fd_light_on = rtb_BusAssignment_o_fd_on;
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.ls_light_on = rtb_BusAssignment_o_ls_on;
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.cstr_light_on = (rtb_BusAssignment_o_efis_filter ==
      FcuComputer_P.EnumeratedConstant7_Value);
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.wpt_light_on = (rtb_BusAssignment_o_efis_filter ==
      FcuComputer_P.EnumeratedConstant6_Value);
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.vord_light_on = (rtb_BusAssignment_o_efis_filter ==
      FcuComputer_P.EnumeratedConstant8_Value);
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.ndb_light_on = (rtb_BusAssignment_o_efis_filter ==
      FcuComputer_P.EnumeratedConstant9_Value);
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.arpt_light_on = (rtb_BusAssignment_o_efis_filter ==
      FcuComputer_P.EnumeratedConstant10_Value);
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.baro_value_mode = rtb_capt_efis_outputs_baro_value_mode;
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.baro_value = rtb_capt_efis_outputs_baro_value;
    FcuComputer_Y.out.discrete_outputs.capt_efis_outputs.baro_mode = rtb_capt_efis_outputs_baro_mode;
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.fd_light_on = rtb_Equal7;
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.ls_light_on = rtb_Equal6;
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.cstr_light_on = (rtb_efisFilter ==
      FcuComputer_P.EnumeratedConstant7_Value_b);
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.wpt_light_on = (rtb_efisFilter ==
      FcuComputer_P.EnumeratedConstant6_Value_m);
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.vord_light_on = (rtb_efisFilter ==
      FcuComputer_P.EnumeratedConstant8_Value_g);
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.ndb_light_on = (rtb_efisFilter ==
      FcuComputer_P.EnumeratedConstant9_Value_c);
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.arpt_light_on = (rtb_efisFilter ==
      FcuComputer_P.EnumeratedConstant10_Value_m);
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.baro_value_mode = rtb_baroValueMode;
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.baro_value =
      rtb_BusConversion_InsertedFor_BusAssignment_at_inport_1_BusCreator1_fo_efis_outputs_baro_value;
    FcuComputer_Y.out.discrete_outputs.fo_efis_outputs.baro_mode = rtb_baroMode;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.loc_light_on = FcuComputer_P.Constant1_Value.afs.loc_only_active;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.exped_light_on = FcuComputer_P.Constant1_Value.afs.exped_active;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.appr_light_on = FcuComputer_P.Constant1_Value.afs.appr_active;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.ap_1_light_on = FcuComputer_U.in.discrete_inputs.ap_1_engaged;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.ap_2_light_on = FcuComputer_U.in.discrete_inputs.ap_2_engaged;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.athr_light_on = (FcuComputer_U.in.discrete_inputs.athr_1_engaged ||
      FcuComputer_U.in.discrete_inputs.athr_2_engaged);
    FcuComputer_Y.out.discrete_outputs.afs_outputs.trk_fpa_mode = FcuComputer_DWork.p_trk_fpa_active;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.mach_mode = FcuComputer_P.Constant15_Value;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.spd_mach_value = FcuComputer_P.Constant8_Value;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.spd_mach_dashes = FcuComputer_P.Constant1_Value_c;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.spd_mach_managed = FcuComputer_P.Constant4_Value_m;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.hdg_trk_value = FcuComputer_P.Constant10_Value;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.hdg_trk_dashes = FcuComputer_P.Constant2_Value_e;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.hdg_trk_managed = FcuComputer_P.Constant5_Value_a;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.alt_value = FcuComputer_P.Constant12_Value;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.lvl_ch_managed = FcuComputer_P.Constant6_Value_b;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.vs_fpa_value = FcuComputer_P.Constant14_Value;
    FcuComputer_Y.out.discrete_outputs.afs_outputs.vs_fpa_dashes = FcuComputer_P.Constant3_Value_o;
    FcuComputer_Y.out.discrete_outputs.fcu_healthy = FcuComputer_P.Constant1_Value_i;
    FcuComputer_Y.out.bus_outputs.selected_hdg_deg.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.selected_hdg_deg.Data = FcuComputer_P.Constant16_Value;
    FcuComputer_Y.out.bus_outputs.selected_alt_ft.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.selected_alt_ft.Data = FcuComputer_P.Constant1_Value_g;
    FcuComputer_Y.out.bus_outputs.selected_spd_kts.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.selected_spd_kts.Data = FcuComputer_P.Constant2_Value_l;
    FcuComputer_Y.out.bus_outputs.selected_vz_ft_min.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.selected_vz_ft_min.Data = FcuComputer_P.Constant3_Value_b;
    FcuComputer_Y.out.bus_outputs.selected_mach.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.selected_mach.Data = FcuComputer_P.Constant4_Value;
    FcuComputer_Y.out.bus_outputs.selected_trk_deg.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.selected_trk_deg.Data = FcuComputer_P.Constant5_Value;
    FcuComputer_Y.out.bus_outputs.selected_fpa_deg.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.selected_fpa_deg.Data = FcuComputer_P.Constant6_Value;
    FcuComputer_Y.out.bus_outputs.ats_fma_discrete_word.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.ats_fma_discrete_word.Data = FcuComputer_P.Constant7_Value;
    FcuComputer_Y.out.bus_outputs.fcu_flex_to_temp_deg_c.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.fcu_flex_to_temp_deg_c.Data = FcuComputer_P.Constant8_Value_i;
    FcuComputer_Y.out.bus_outputs.ats_discrete_word.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.ats_discrete_word.Data = FcuComputer_P.Constant9_Value;
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_1_left.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_1_left.Data = rtb_y_i;
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_1_right.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_1_right.Data = rtb_y;
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_2_left.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_2_left.Data = rtb_y_ea;
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_2_right.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.eis_discrete_word_2_right.Data = rtb_y_g;
    FcuComputer_Y.out.bus_outputs.baro_setting_left_hpa.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.baro_setting_left_hpa.Data = rtb_BusAssignment_o_baro_value_hpa;
    FcuComputer_Y.out.bus_outputs.baro_setting_right_hpa.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.baro_setting_right_hpa.Data = static_cast<real32_T>(rtb_value_hpa);
    FcuComputer_Y.out.bus_outputs.baro_setting_left_inhg.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.baro_setting_left_inhg.Data = rtb_BusAssignment_o_baro_value_inhg;
    FcuComputer_Y.out.bus_outputs.baro_setting_right_inhg.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.baro_setting_right_inhg.Data = static_cast<real32_T>(rtb_value_inhg);
    FcuComputer_Y.out.bus_outputs.fcu_discrete_word_2.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.fcu_discrete_word_2.Data = rtb_y_b;
    FcuComputer_Y.out.bus_outputs.fcu_discrete_word_1.SSM = static_cast<uint32_T>
      (FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.fcu_discrete_word_1.Data = rtb_y_l;
    FcuComputer_Y.out.bus_outputs.n1_cmd_percent.SSM = static_cast<uint32_T>(FcuComputer_P.EnumeratedConstant1_Value);
    FcuComputer_Y.out.bus_outputs.n1_cmd_percent.Data = FcuComputer_P.Constant21_Value;
  } else {
    FcuComputer_DWork.Runtime_MODE = false;
  }
}

void FcuComputer::initialize()
{
  FcuComputer_MATLABFunction_j_Init(&FcuComputer_DWork.sf_MATLABFunction_p);
  FcuComputer_MATLABFunction1_Init(&FcuComputer_DWork.sf_MATLABFunction1);
  FcuComputer_MATLABFunction_j_Init(&FcuComputer_DWork.sf_MATLABFunction_jp);
  FcuComputer_MATLABFunction1_Init(&FcuComputer_DWork.sf_MATLABFunction1_e);
  FcuComputer_Y.out = FcuComputer_P.out_Y0;
}

void FcuComputer::terminate()
{
}

FcuComputer::FcuComputer():
  FcuComputer_U(),
  FcuComputer_Y(),
  FcuComputer_DWork()
{
}

FcuComputer::~FcuComputer()
{
}
