#ifndef A380FacComputer_h_
#define A380FacComputer_h_
#include "rtwtypes.h"
#include "A380FacComputer_types.h"

class A380FacComputer final
{
 public:
  struct rtDW_LagFilter_A380FacComputer_T {
    real_T pY;
    real_T pU;
    boolean_T pY_not_empty;
    boolean_T pU_not_empty;
  };

  struct rtDW_RateLimiter_A380FacComputer_T {
    real_T pY;
    boolean_T pY_not_empty;
  };

  struct rtDW_LagFilter_A380FacComputer_g_T {
    real32_T pY;
    real32_T pU;
    boolean_T pY_not_empty;
    boolean_T pU_not_empty;
  };

  struct rtDW_RateLimiter_A380FacComputer_b_T {
    real_T pY;
    boolean_T pY_not_empty;
  };

  struct rtDW_RateLimiter_A380FacComputer_d_T {
    real_T pY;
    boolean_T pY_not_empty;
  };

  struct rtDW_MATLABFunction_A380FacComputer_f_T {
    real_T timeSinceCondition;
    boolean_T output;
  };

  struct D_Work_A380FacComputer_T {
    real_T Delay_DSTATE;
    real_T Delay_DSTATE_d;
    real_T Delay_DSTATE_dc;
    real_T pY;
    real_T pU;
    real_T takeoff_config;
    real_T takeoff_config_c;
    real_T takeoff_config_g;
    real_T sAlphaFloor;
    uint8_T is_active_c15_A380FacComputer;
    uint8_T is_c15_A380FacComputer;
    boolean_T Memory_PreviousInput;
    boolean_T icLoad;
    boolean_T pY_not_empty;
    boolean_T pU_not_empty;
    boolean_T previousInput;
    boolean_T previousInput_not_empty;
    boolean_T Runtime_MODE;
    rtDW_MATLABFunction_A380FacComputer_f_T sf_MATLABFunction_jf;
    rtDW_MATLABFunction_A380FacComputer_f_T sf_MATLABFunction_a;
    rtDW_MATLABFunction_A380FacComputer_f_T sf_MATLABFunction_p;
    rtDW_RateLimiter_A380FacComputer_d_T sf_RateLimiter_fu;
    rtDW_RateLimiter_A380FacComputer_d_T sf_RateLimiter_l;
    rtDW_RateLimiter_A380FacComputer_d_T sf_RateLimiter_p;
    rtDW_RateLimiter_A380FacComputer_b_T sf_RateLimiter_g0;
    rtDW_RateLimiter_A380FacComputer_b_T sf_RateLimiter_g;
    rtDW_RateLimiter_A380FacComputer_b_T sf_RateLimiter_f;
    rtDW_LagFilter_A380FacComputer_T sf_LagFilter_i;
    rtDW_LagFilter_A380FacComputer_T sf_LagFilter_c;
    rtDW_LagFilter_A380FacComputer_g_T sf_LagFilter_d5;
    rtDW_LagFilter_A380FacComputer_T sf_LagFilter_f;
    rtDW_LagFilter_A380FacComputer_g_T sf_LagFilter_k;
    rtDW_LagFilter_A380FacComputer_T sf_LagFilter_d;
    rtDW_RateLimiter_A380FacComputer_T sf_RateLimiter_a;
    rtDW_RateLimiter_A380FacComputer_T sf_RateLimiter_n;
    rtDW_RateLimiter_A380FacComputer_T sf_RateLimiter_j;
    rtDW_RateLimiter_A380FacComputer_T sf_RateLimiter_c;
    rtDW_RateLimiter_A380FacComputer_T sf_RateLimiter;
    rtDW_LagFilter_A380FacComputer_T sf_LagFilter;
  };

  struct ExternalInputs_A380FacComputer_T {
    fac_inputs in;
  };

  struct ExternalOutputs_A380FacComputer_T {
    fac_outputs out;
  };

  struct Parameters_A380FacComputer_T {
    base_fac_analog_outputs fac_analog_output_MATLABStruct;
    base_fac_laws_outputs fac_laws_output_MATLABStruct;
    base_fac_discrete_outputs fac_discrete_output_MATLABStruct;
    real_T LagFilter1_C1;
    real_T LagFilter1_C1_d;
    real_T LagFilter2_C1;
    real_T LagFilter3_C1;
    real_T LagFilter_C1;
    real_T LagFilter_C1_k;
    real_T LagFilter_C1_f;
    real_T WashoutFilter_C1;
    real_T DiscreteDerivativeVariableTs_Gain;
    real_T DiscreteDerivativeVariableTs_Gain_l;
    real_T DiscreteTimeIntegratorVariableTs_Gain;
    real_T DiscreteDerivativeVariableTs_InitialCondition;
    real_T RateLimiterGenericVariableTs1_InitialCondition;
    real_T RateLimiterGenericVariableTs_InitialCondition;
    real_T DiscreteDerivativeVariableTs_InitialCondition_l;
    real_T RateLimiterGenericVariableTs_InitialCondition_o;
    real_T DiscreteTimeIntegratorVariableTs_LowerLimit;
    real_T DiscreteTimeIntegratorVariableTs_UpperLimit;
    real_T BitfromLabel_bit;
    real_T BitfromLabel5_bit;
    real_T BitfromLabel6_bit;
    real_T BitfromLabel7_bit;
    real_T BitfromLabel8_bit;
    real_T BitfromLabel1_bit;
    real_T BitfromLabel4_bit;
    real_T BitfromLabel3_bit;
    real_T BitfromLabel2_bit;
    real_T BitfromLabel1_bit_d;
    real_T BitfromLabel8_bit_i;
    real_T BitfromLabel9_bit;
    real_T BitfromLabel10_bit;
    real_T BitfromLabel11_bit;
    real_T BitfromLabel12_bit;
    real_T BitfromLabel_bit_m;
    real_T BitfromLabel2_bit_n;
    real_T BitfromLabel3_bit_i;
    real_T BitfromLabel4_bit_p;
    real_T BitfromLabel5_bit_g;
    real_T BitfromLabel6_bit_n;
    real_T BitfromLabel7_bit_p;
    real_T BitfromLabel6_bit_m;
    real_T BitfromLabel7_bit_i;
    real_T BitfromLabel_bit_j;
    real_T BitfromLabel1_bit_e;
    real_T BitfromLabel_bit_c;
    real_T BitfromLabel1_bit_n;
    real_T BitfromLabel3_bit_k;
    real_T BitfromLabel4_bit_k;
    real_T CompareToConstant4_const;
    real_T CompareToConstant2_const;
    real_T CompareToConstant3_const;
    real_T CompareToConstant1_const;
    real_T CompareToConstant_const;
    real_T CompareToConstant_const_i;
    real_T CompareToConstant1_const_i;
    real_T RateLimiterGenericVariableTs1_lo;
    real_T RateLimiterGenericVariableTs1_lo_n;
    real_T RateLimiterGenericVariableTs4_lo;
    real_T RateLimiterGenericVariableTs3_lo;
    real_T RateLimiterGenericVariableTs2_lo;
    real_T RateLimiterGenericVariableTs1_lo_f;
    real_T RateLimiterGenericVariableTs_lo;
    real_T RateLimiterGenericVariableTs_lo_e;
    real_T RateLimiterGenericVariableTs_lo_d;
    real_T RateLimiterGenericVariableTs_lo_f;
    real_T RateLimiterGenericVariableTs_lo_p;
    real_T ConfirmNode_timeDelay;
    real_T ConfirmNode_timeDelay_m;
    real_T ConfirmNode_timeDelay_l;
    real_T RateLimiterGenericVariableTs1_up;
    real_T RateLimiterGenericVariableTs1_up_g;
    real_T RateLimiterGenericVariableTs4_up;
    real_T RateLimiterGenericVariableTs3_up;
    real_T RateLimiterGenericVariableTs2_up;
    real_T RateLimiterGenericVariableTs1_up_d;
    real_T RateLimiterGenericVariableTs_up;
    real_T RateLimiterGenericVariableTs_up_g;
    real_T RateLimiterGenericVariableTs_up_l;
    real_T RateLimiterGenericVariableTs_up_a;
    real_T RateLimiterGenericVariableTs_up_c;
    SignStatusMatrix EnumeratedConstant1_Value;
    SignStatusMatrix EnumeratedConstant_Value;
    SignStatusMatrix EnumeratedConstant2_Value;
    real32_T CompareToConstant_const_f;
    real32_T CompareToConstant1_const_l;
    real32_T CompareToConstant2_const_i;
    boolean_T SRFlipFlop_initial_condition;
    boolean_T ConfirmNode_isRisingEdge;
    boolean_T ConfirmNode_isRisingEdge_a;
    boolean_T ConfirmNode_isRisingEdge_o;
    boolean_T PulseNode_isRisingEdge;
    fac_outputs out_Y0;
    base_fac_bus Constant4_Value;
    base_fac_flight_envelope_outputs Constant5_Value;
    base_fac_logic_outputs Constant1_Value;
    real_T Constant_Value;
    real_T Gain4_Gain;
    real_T Vmcl5_Value;
    real_T Vmcl10_Value;
    real_T uDLookupTable_tableData[2];
    real_T uDLookupTable_bp01Data[2];
    real_T Vfe_35_Value;
    real_T Constant2_Value;
    real_T Constant3_Value;
    real_T Constant1_Value_m;
    real_T Gain2_Gain;
    real_T Constant2_Value_m;
    real_T Saturation_UpperSat;
    real_T Saturation_LowerSat;
    real_T Constant_Value_g;
    real_T Gain_Gain;
    real_T Saturation1_UpperSat;
    real_T Saturation1_LowerSat;
    real_T Saturation_UpperSat_a;
    real_T Saturation_LowerSat_l;
    real_T Gain5_Gain;
    real_T Saturation1_UpperSat_o;
    real_T Saturation1_LowerSat_n;
    real_T Gain_Gain_k;
    real_T alphamax_tableData[24];
    real_T alphamax_bp01Data[4];
    real_T alphamax_bp02Data[6];
    real_T alphaprotection_tableData[24];
    real_T alphaprotection_bp01Data[4];
    real_T alphaprotection_bp02Data[6];
    real_T Gain3_Gain;
    real_T alpha0_tableData[6];
    real_T alpha0_bp01Data[6];
    real_T alphamax_tableData_b[24];
    real_T alphamax_bp01Data_m[4];
    real_T alphamax_bp02Data_a[6];
    real_T alphaprotection_tableData_p[24];
    real_T alphaprotection_bp01Data_b[4];
    real_T alphaprotection_bp02Data_m[6];
    real_T alphastallwarnmax_tableData[24];
    real_T alphastallwarnmax_bp01Data[4];
    real_T alphastallwarnmax_bp02Data[6];
    real_T Gain2_Gain_d;
    real_T uDLookupTable1_tableData[96];
    real_T uDLookupTable1_bp01Data[8];
    real_T uDLookupTable1_bp02Data[12];
    real_T Gain3_Gain_h;
    real_T nDLookupTable_tableData[96];
    real_T nDLookupTable_bp01Data[8];
    real_T nDLookupTable_bp02Data[2];
    real_T nDLookupTable_bp03Data[6];
    real_T spoilermaxdeflection_tableData[6];
    real_T spoilermaxdeflection_bp01Data[6];
    real_T VLSincreasemaxdeflection_tableData[6];
    real_T VLSincreasemaxdeflection_bp01Data[6];
    real_T Vmcl_Value;
    real_T Gain3_Gain_b;
    real_T uDLookupTable_tableData_m[40];
    real_T uDLookupTable_bp01Data_n[8];
    real_T uDLookupTable_bp02Data[5];
    real_T _Value;
    real_T Gain2_Gain_j;
    real_T uDLookupTable1_tableData_j[96];
    real_T uDLookupTable1_bp01Data_p[8];
    real_T uDLookupTable1_bp02Data_n[12];
    real_T Gain3_Gain_d;
    real_T nDLookupTable_tableData_e[96];
    real_T nDLookupTable_bp01Data_p[8];
    real_T nDLookupTable_bp02Data_b[2];
    real_T nDLookupTable_bp03Data_h[6];
    real_T Gain2_Gain_o;
    real_T uDLookupTable1_tableData_o[96];
    real_T uDLookupTable1_bp01Data_a[8];
    real_T uDLookupTable1_bp02Data_l[12];
    real_T Gain3_Gain_n;
    real_T nDLookupTable_tableData_p[96];
    real_T nDLookupTable_bp01Data_a[8];
    real_T nDLookupTable_bp02Data_f[2];
    real_T nDLookupTable_bp03Data_m[6];
    real_T Switch_Threshold;
    real_T Gain2_Gain_c;
    real_T uDLookupTable1_tableData_i[96];
    real_T uDLookupTable1_bp01Data_l[8];
    real_T uDLookupTable1_bp02Data_p[12];
    real_T Constant2_Value_c;
    real_T Gain3_Gain_a;
    real_T nDLookupTable_tableData_k[96];
    real_T nDLookupTable_bp01Data_o[8];
    real_T nDLookupTable_bp02Data_m[2];
    real_T nDLookupTable_bp03Data_md[6];
    real_T Gain2_Gain_e;
    real_T Vmcl20_Value;
    real_T Vfe_25_Value;
    real_T uDLookupTable1_tableData_ow[6];
    real_T uDLookupTable1_bp01Data_pi[6];
    real_T uDLookupTable_tableData_k[6];
    real_T uDLookupTable_bp01Data_i[6];
    real_T Constant1_Value_p;
    real_T Saturation_UpperSat_j;
    real_T Saturation_LowerSat_c;
    real_T Gain_Gain_j;
    real_T Saturation_UpperSat_e;
    real_T Saturation_LowerSat_o;
    real_T uDLookupTable_tableData_j[7];
    real_T uDLookupTable_bp01Data_ik[7];
    real_T Saturation_UpperSat_g;
    real_T Saturation_LowerSat_f;
    real_T Constant_Value_b;
    real_T Constant_Value_d;
    real_T Switch7_Threshold;
    real_T Constant1_Value_l;
    real_T Switch6_Threshold;
    real32_T Switch6_Threshold_n;
    real32_T Constant2_Value_k;
    real32_T Constant3_Value_d;
    real32_T Constant6_Value;
    real32_T Constant4_Value_j;
    real32_T Constant1_Value_c;
    real32_T Gain4_Gain_o;
    real32_T uDLookupTable_tableData_d[15];
    real32_T uDLookupTable_bp01Data_o[5];
    real32_T uDLookupTable_bp02Data_p[3];
    real32_T Constant28_Value;
    real32_T Constant22_Value;
    real32_T Constant21_Value;
    real32_T Constant4_Value_b;
    real32_T Constant26_Value;
    uint32_T alphamax_maxIndex[2];
    uint32_T alphaprotection_maxIndex[2];
    uint32_T alphamax_maxIndex_g[2];
    uint32_T alphaprotection_maxIndex_m[2];
    uint32_T alphastallwarnmax_maxIndex[2];
    uint32_T uDLookupTable1_maxIndex[2];
    uint32_T nDLookupTable_maxIndex[3];
    uint32_T nDLookupTable_dimSizes[3];
    uint32_T uDLookupTable_maxIndex[2];
    uint32_T uDLookupTable1_maxIndex_k[2];
    uint32_T nDLookupTable_maxIndex_e[3];
    uint32_T nDLookupTable_dimSizes_l[3];
    uint32_T uDLookupTable1_maxIndex_b[2];
    uint32_T nDLookupTable_maxIndex_m[3];
    uint32_T nDLookupTable_dimSizes_p[3];
    uint32_T uDLookupTable1_maxIndex_g[2];
    uint32_T nDLookupTable_maxIndex_g[3];
    uint32_T nDLookupTable_dimSizes_i[3];
    uint32_T uDLookupTable_maxIndex_j[2];
    boolean_T Constant_Value_c;
    boolean_T Constant_Value_h;
    boolean_T Constant_Value_b5;
    boolean_T reset_Value;
    boolean_T Constant1_Value_mf;
    boolean_T reset_Value_k;
    boolean_T reset_Value_o;
    boolean_T reset_Value_a;
    boolean_T reset_Value_i;
    boolean_T reset_Value_k5;
    boolean_T reset_Value_m;
    boolean_T reset_Value_i3;
    boolean_T Logic_table[16];
    boolean_T Constant2_Value_o;
    boolean_T Constant1_Value_d;
    boolean_T Constant10_Value;
    boolean_T Constant18_Value;
    boolean_T Constant9_Value;
    boolean_T Constant19_Value;
  };

  A380FacComputer(A380FacComputer const&) = delete;
  A380FacComputer& operator= (A380FacComputer const&) & = delete;
  A380FacComputer(A380FacComputer &&) = delete;
  A380FacComputer& operator= (A380FacComputer &&) = delete;
  void setExternalInputs(const ExternalInputs_A380FacComputer_T *pExternalInputs_A380FacComputer_T)
  {
    A380FacComputer_U = *pExternalInputs_A380FacComputer_T;
  }

  const ExternalOutputs_A380FacComputer_T &getExternalOutputs() const
  {
    return A380FacComputer_Y;
  }

  void initialize();
  void step();
  static void terminate();
  A380FacComputer();
  ~A380FacComputer();
 private:
  ExternalInputs_A380FacComputer_T A380FacComputer_U;
  ExternalOutputs_A380FacComputer_T A380FacComputer_Y;
  D_Work_A380FacComputer_T A380FacComputer_DWork;
  static Parameters_A380FacComputer_T A380FacComputer_P;
  static void A380FacComputer_MATLABFunction(const base_arinc_429 *rtu_u, boolean_T *rty_y);
  static void A380FacComputer_MATLABFunction_g(const base_arinc_429 *rtu_u, real_T rtu_bit, uint32_T *rty_y);
  static void A380FacComputer_LagFilter_Reset(rtDW_LagFilter_A380FacComputer_T *localDW);
  static void A380FacComputer_LagFilter(real_T rtu_U, real_T rtu_C1, real_T rtu_dt, real_T *rty_Y,
    rtDW_LagFilter_A380FacComputer_T *localDW);
  static void A380FacComputer_RateLimiter_Reset(rtDW_RateLimiter_A380FacComputer_T *localDW);
  static void A380FacComputer_RateLimiter(real_T rtu_u, real_T rtu_up, real_T rtu_lo, real_T rtu_Ts, boolean_T rtu_reset,
    real_T *rty_Y, rtDW_RateLimiter_A380FacComputer_T *localDW);
  static void A380FacComputer_CalculateV_alpha_max(real_T rtu_v_ias, real_T rtu_alpha, real_T rtu_alpha_0, real_T
    rtu_alpha_target, real_T *rty_V_alpha_target);
  static void A380FacComputer_LagFilter_c_Reset(rtDW_LagFilter_A380FacComputer_g_T *localDW);
  static void A380FacComputer_LagFilter_k(real32_T rtu_U, real_T rtu_C1, real_T rtu_dt, real32_T *rty_Y,
    rtDW_LagFilter_A380FacComputer_g_T *localDW);
  static void A380FacComputer_VS1GfromVLS(real_T rtu_vls_conf_0, real_T rtu_vls_conf_other, real_T rtu_flap_handle_index,
    real_T *rty_vs1g);
  static void A380FacComputer_RateLimiter_o_Reset(rtDW_RateLimiter_A380FacComputer_b_T *localDW);
  static void A380FacComputer_RateLimiter_f(real_T rtu_u, real_T rtu_up, real_T rtu_lo, real_T rtu_Ts, real_T rtu_init,
    boolean_T rtu_reset, real_T *rty_Y, rtDW_RateLimiter_A380FacComputer_b_T *localDW);
  static void A380FacComputer_RateLimiter_h_Reset(rtDW_RateLimiter_A380FacComputer_d_T *localDW);
  static void A380FacComputer_RateLimiter_p(real_T rtu_u, real_T rtu_up, real_T rtu_lo, real_T rtu_Ts, real_T rtu_init,
    boolean_T rtu_reset, real_T *rty_Y, rtDW_RateLimiter_A380FacComputer_d_T *localDW);
  static void A380FacComputer_MATLABFunction_pm_Reset(rtDW_MATLABFunction_A380FacComputer_f_T *localDW);
  static void A380FacComputer_MATLABFunction_p(boolean_T rtu_u, real_T rtu_Ts, boolean_T rtu_isRisingEdge, real_T
    rtu_timeDelay, boolean_T *rty_y, rtDW_MATLABFunction_A380FacComputer_f_T *localDW);
  static void A380FacComputer_MATLABFunction_g3(const boolean_T rtu_u[19], real32_T *rty_y);
};

#endif

