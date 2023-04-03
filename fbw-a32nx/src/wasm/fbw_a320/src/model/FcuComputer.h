#ifndef RTW_HEADER_FcuComputer_h_
#define RTW_HEADER_FcuComputer_h_
#include "rtwtypes.h"
#include "FcuComputer_types.h"

class FcuComputer final
{
 public:
  struct rtDW_MATLABFunction_FcuComputer_c_T {
    boolean_T previousInput;
    boolean_T previousInput_not_empty;
  };

  struct rtDW_EFISFilterLogic_FcuComputer_T {
    efis_filter_selection pEfisFilter;
  };

  struct rtDW_MATLABFunction_FcuComputer_b_T {
    boolean_T std_active;
    boolean_T qnh_active;
    boolean_T qfe_active;
  };

  struct rtDW_MATLABFunction1_FcuComputer_T {
    real_T pValueHpa;
    real_T pValueInhg;
  };

  struct rtDW_MATLABFunction_FcuComputer_l_T {
    boolean_T pY;
    boolean_T pY_not_empty;
  };

  struct D_Work_FcuComputer_T {
    boolean_T p_trk_fpa_active;
    boolean_T Runtime_MODE;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_je;
    rtDW_MATLABFunction_FcuComputer_l_T sf_MATLABFunction_hk;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_ja0;
    rtDW_MATLABFunction_FcuComputer_l_T sf_MATLABFunction_ja;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_gx;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_ng;
    rtDW_MATLABFunction1_FcuComputer_T sf_MATLABFunction1_e;
    rtDW_MATLABFunction_FcuComputer_b_T sf_MATLABFunction_jp;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_cb;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_d;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_hl;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_e;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_f;
    rtDW_EFISFilterLogic_FcuComputer_T sf_EFISFilterLogic_h;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_j;
    rtDW_MATLABFunction_FcuComputer_l_T sf_MATLABFunction_k;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_ik;
    rtDW_MATLABFunction_FcuComputer_l_T sf_MATLABFunction_m;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_b3;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_hc;
    rtDW_MATLABFunction1_FcuComputer_T sf_MATLABFunction1;
    rtDW_MATLABFunction_FcuComputer_b_T sf_MATLABFunction_p;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_bp;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_g;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_id;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_n;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_h;
    rtDW_EFISFilterLogic_FcuComputer_T sf_EFISFilterLogic;
    rtDW_MATLABFunction_FcuComputer_c_T sf_MATLABFunction_a4;
  };

  struct ExternalInputs_FcuComputer_T {
    fcu_inputs in;
  };

  struct ExternalOutputs_FcuComputer_T {
    fcu_outputs out;
  };

  struct Parameters_FcuComputer_T {
    real_T BitfromLabel_bit;
    real_T BitfromLabel1_bit;
    SignStatusMatrix EnumeratedConstant1_Value;
    efis_filter_selection EnumeratedConstant7_Value;
    efis_filter_selection EnumeratedConstant6_Value;
    efis_filter_selection EnumeratedConstant8_Value;
    efis_filter_selection EnumeratedConstant9_Value;
    efis_filter_selection EnumeratedConstant10_Value;
    efis_filter_selection EnumeratedConstant7_Value_b;
    efis_filter_selection EnumeratedConstant6_Value_m;
    efis_filter_selection EnumeratedConstant8_Value_g;
    efis_filter_selection EnumeratedConstant9_Value_c;
    efis_filter_selection EnumeratedConstant10_Value_m;
    efis_filter_selection EnumeratedConstant7_Value_k;
    efis_filter_selection EnumeratedConstant6_Value_l;
    efis_filter_selection EnumeratedConstant8_Value_a;
    efis_filter_selection EnumeratedConstant9_Value_g;
    efis_filter_selection EnumeratedConstant10_Value_b;
    efis_filter_selection EnumeratedConstant7_Value_a;
    efis_filter_selection EnumeratedConstant6_Value_l4;
    efis_filter_selection EnumeratedConstant8_Value_p;
    efis_filter_selection EnumeratedConstant9_Value_o;
    efis_filter_selection EnumeratedConstant10_Value_e;
    efis_mode_selection EnumeratedConstant2_Value;
    efis_mode_selection EnumeratedConstant1_Value_b;
    efis_mode_selection EnumeratedConstant3_Value;
    efis_mode_selection EnumeratedConstant4_Value;
    efis_mode_selection EnumeratedConstant5_Value;
    efis_mode_selection EnumeratedConstant2_Value_a;
    efis_mode_selection EnumeratedConstant1_Value_m;
    efis_mode_selection EnumeratedConstant3_Value_l;
    efis_mode_selection EnumeratedConstant4_Value_b;
    efis_mode_selection EnumeratedConstant5_Value_e;
    efis_navaid_selection EnumeratedConstant12_Value;
    efis_navaid_selection EnumeratedConstant11_Value;
    efis_navaid_selection EnumeratedConstant12_Value_a;
    efis_navaid_selection EnumeratedConstant11_Value_o;
    efis_range_selection EnumeratedConstant2_Value_g;
    efis_range_selection EnumeratedConstant1_Value_h;
    efis_range_selection EnumeratedConstant3_Value_i;
    efis_range_selection EnumeratedConstant4_Value_n;
    efis_range_selection EnumeratedConstant5_Value_a;
    efis_range_selection EnumeratedConstant2_Value_l;
    efis_range_selection EnumeratedConstant1_Value_n;
    efis_range_selection EnumeratedConstant3_Value_e;
    efis_range_selection EnumeratedConstant4_Value_i;
    efis_range_selection EnumeratedConstant5_Value_k;
    boolean_T TFlipFlop_init;
    boolean_T TFlipFlop1_init;
    boolean_T TFlipFlop_init_f;
    boolean_T TFlipFlop1_init_a;
    boolean_T PulseNode_isRisingEdge;
    boolean_T PulseNode1_isRisingEdge;
    boolean_T PulseNode2_isRisingEdge;
    boolean_T PulseNode3_isRisingEdge;
    boolean_T PulseNode4_isRisingEdge;
    boolean_T PulseNode_isRisingEdge_n;
    boolean_T PulseNode_isRisingEdge_nj;
    boolean_T PulseNode_isRisingEdge_a;
    boolean_T PulseNode1_isRisingEdge_h;
    boolean_T PulseNode_isRisingEdge_m;
    boolean_T PulseNode1_isRisingEdge_k;
    boolean_T PulseNode2_isRisingEdge_a;
    boolean_T PulseNode3_isRisingEdge_g;
    boolean_T PulseNode4_isRisingEdge_a;
    boolean_T PulseNode_isRisingEdge_i;
    boolean_T PulseNode_isRisingEdge_h;
    boolean_T PulseNode_isRisingEdge_o;
    boolean_T PulseNode1_isRisingEdge_f;
    boolean_T PulseNode_isRisingEdge_oa;
    fcu_outputs out_Y0;
    base_fcu_bus Constant2_Value;
    base_fcu_logic_outputs Constant1_Value;
    base_fcu_discrete_outputs Constant3_Value;
    real_T Constant8_Value;
    real_T Constant10_Value;
    real_T Constant12_Value;
    real_T Constant14_Value;
    real32_T Constant16_Value;
    real32_T Constant1_Value_g;
    real32_T Constant2_Value_l;
    real32_T Constant3_Value_b;
    real32_T Constant4_Value;
    real32_T Constant5_Value;
    real32_T Constant6_Value;
    real32_T Constant7_Value;
    real32_T Constant8_Value_i;
    real32_T Constant9_Value;
    real32_T Constant21_Value;
    boolean_T Constant15_Value;
    boolean_T Constant1_Value_c;
    boolean_T Constant4_Value_m;
    boolean_T Constant2_Value_e;
    boolean_T Constant5_Value_a;
    boolean_T Constant6_Value_b;
    boolean_T Constant3_Value_o;
    boolean_T Constant1_Value_i;
    boolean_T Constant10_Value_f;
    boolean_T Constant10_Value_a;
    boolean_T Constant10_Value_p;
    boolean_T Constant10_Value_e;
    boolean_T Constant19_Value;
    boolean_T Constant20_Value;
  };

  FcuComputer(FcuComputer const&) = delete;
  FcuComputer& operator= (FcuComputer const&) & = delete;
  FcuComputer(FcuComputer &&) = delete;
  FcuComputer& operator= (FcuComputer &&) = delete;
  void setExternalInputs(const ExternalInputs_FcuComputer_T *pExternalInputs_FcuComputer_T)
  {
    FcuComputer_U = *pExternalInputs_FcuComputer_T;
  }

  const ExternalOutputs_FcuComputer_T &getExternalOutputs() const
  {
    return FcuComputer_Y;
  }

  void initialize();
  void step();
  static void terminate();
  FcuComputer();
  ~FcuComputer();
 private:
  ExternalInputs_FcuComputer_T FcuComputer_U;
  ExternalOutputs_FcuComputer_T FcuComputer_Y;
  D_Work_FcuComputer_T FcuComputer_DWork;
  static Parameters_FcuComputer_T FcuComputer_P;
  static void FcuComputer_MATLABFunction(const base_arinc_429 *rtu_u, real_T rtu_bit, uint32_T *rty_y);
  static void FcuComputer_MATLABFunction_f_Reset(rtDW_MATLABFunction_FcuComputer_c_T *localDW);
  static void FcuComputer_MATLABFunction_a(boolean_T rtu_u, boolean_T rtu_isRisingEdge, boolean_T *rty_y,
    rtDW_MATLABFunction_FcuComputer_c_T *localDW);
  static void FcuComputer_EFISFilterLogic_Reset(rtDW_EFISFilterLogic_FcuComputer_T *localDW);
  static void FcuComputer_EFISFilterLogic(boolean_T rtu_cstr, boolean_T rtu_wpt, boolean_T rtu_vord, boolean_T rtu_ndb,
    boolean_T rtu_arpt, efis_filter_selection *rty_efisFilter, rtDW_EFISFilterLogic_FcuComputer_T *localDW);
  static void FcuComputer_MATLABFunction_j_Init(rtDW_MATLABFunction_FcuComputer_b_T *localDW);
  static void FcuComputer_MATLABFunction_a_Reset(rtDW_MATLABFunction_FcuComputer_b_T *localDW);
  static void FcuComputer_MATLABFunction_p(boolean_T rtu_knob_push, boolean_T rtu_knob_pull, boolean_T *rty_std,
    boolean_T *rty_qnh, boolean_T *rty_qfe, rtDW_MATLABFunction_FcuComputer_b_T *localDW);
  static void FcuComputer_MATLABFunction1_Init(rtDW_MATLABFunction1_FcuComputer_T *localDW);
  static void FcuComputer_MATLABFunction1_Reset(rtDW_MATLABFunction1_FcuComputer_T *localDW);
  static void FcuComputer_MATLABFunction1(boolean_T rtu_std_active, boolean_T rtu_inhg_active, real_T rtu_click_count,
    real_T *rty_value_hpa, real_T *rty_value_inhg, rtDW_MATLABFunction1_FcuComputer_T *localDW);
  static void FcuComputer_MATLABFunction_g_Reset(rtDW_MATLABFunction_FcuComputer_l_T *localDW);
  static void FcuComputer_MATLABFunction_m(boolean_T rtu_u, boolean_T *rty_y, boolean_T rtp_init,
    rtDW_MATLABFunction_FcuComputer_l_T *localDW);
  static void FcuComputer_MATLABFunction_e(const boolean_T rtu_u[19], real32_T *rty_y);
  static void FcuComputer_MATLABFunction_n(const base_fcu_efis_logic_outputs *rtu_logic, const
    base_fcu_efis_panel_inputs *rtu_data, int8_T *rty_baroValueMode, real32_T *rty_baroValue, int8_T *rty_baroMode);
};

#endif

