#ifndef RTW_HEADER_FmgcComputer_h_
#define RTW_HEADER_FmgcComputer_h_
#include "rtwtypes.h"
#include "FmgcComputer_types.h"

class FmgcComputer final
{
 public:
  struct rtDW_MATLABFunction_FmgcComputer_T {
    real_T timeSinceCondition;
    boolean_T output;
  };

  struct rtDW_MATLABFunction_FmgcComputer_e_T {
    boolean_T previousInput;
    boolean_T previousInput_not_empty;
  };

  struct D_Work_FmgcComputer_T {
    base_fmgc_ap_fd_logic_outputs Delay_DSTATE;
    boolean_T Delay_DSTATE_p;
    boolean_T Memory_PreviousInput;
    boolean_T Memory_PreviousInput_g;
    boolean_T Memory_PreviousInput_p;
    boolean_T Memory_PreviousInput_k;
    boolean_T Memory_PreviousInput_c;
    boolean_T Memory_PreviousInput_l;
    boolean_T Memory_PreviousInput_d;
    boolean_T Memory_PreviousInput_dv;
    boolean_T Memory_PreviousInput_f;
    boolean_T Memory_PreviousInput_i;
    boolean_T Memory_PreviousInput_e;
    boolean_T Memory_PreviousInput_f2;
    boolean_T Memory_PreviousInput_i1;
    boolean_T Memory_PreviousInput_ip;
    boolean_T Memory_PreviousInput_a;
    boolean_T Memory_PreviousInput_cv;
    boolean_T Runtime_MODE;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_h0;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_jl;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_m1;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_h4;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_di2;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_gk;
    rtDW_MATLABFunction_FmgcComputer_T sf_MATLABFunction_hz;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_fn;
    rtDW_MATLABFunction_FmgcComputer_T sf_MATLABFunction_h;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_d3;
    rtDW_MATLABFunction_FmgcComputer_e_T sf_MATLABFunction_i;
    rtDW_MATLABFunction_FmgcComputer_T sf_MATLABFunction_f;
    rtDW_MATLABFunction_FmgcComputer_T sf_MATLABFunction;
  };

  struct ExternalInputs_FmgcComputer_T {
    fmgc_inputs in;
  };

  struct ExternalOutputs_FmgcComputer_T {
    fmgc_outputs out;
  };

  struct Parameters_FmgcComputer_T {
    struct_WMm7UfsRAo27Sw9yOtp9SH fmgc_logic_output_MATLABStruct;
    base_fmgc_ap_fd_logic_outputs fmgc_ap_fd_logic_output_MATLABStruct;
    base_fmgc_discrete_outputs fmgc_discrete_output_MATLABStruct;
    real_T BitfromLabel_bit;
    real_T BitfromLabel1_bit;
    real_T BitfromLabel2_bit;
    real_T BitfromLabel_bit_n;
    real_T BitfromLabel1_bit_i;
    real_T BitfromLabel_bit_c;
    real_T BitfromLabel_bit_a;
    real_T BitfromLabel_bit_k;
    real_T BitfromLabel_bit_f;
    real_T BitfromLabel_bit_l;
    real_T BitfromLabel2_bit_e;
    real_T BitfromLabel_bit_a4;
    real_T BitfromLabel_bit_cs;
    real_T BitfromLabel_bit_e;
    real_T BitfromLabel_bit_p;
    real_T BitfromLabel1_bit_o;
    real_T BitfromLabel2_bit_i;
    real_T BitfromLabel3_bit;
    real_T BitfromLabel_bit_fu;
    real_T BitfromLabel2_bit_m;
    real_T BitfromLabel1_bit_p;
    real_T BitfromLabel_bit_nk;
    real_T BitfromLabel_bit_o;
    real_T BitfromLabel_bit_j;
    real_T BitfromLabel_bit_i;
    real_T BitfromLabel1_bit_i5;
    real_T BitfromLabel2_bit_o;
    real_T BitfromLabel3_bit_l;
    real_T BitfromLabel4_bit;
    real_T BitfromLabel_bit_l2;
    real_T BitfromLabel1_bit_pu;
    real_T BitfromLabel2_bit_l;
    real_T CompareToConstant1_const;
    real_T CompareToConstant2_const;
    real_T CompareToConstant_const;
    real_T CompareToConstant_const_c;
    real_T ConfirmNode1_timeDelay;
    real_T ConfirmNode_timeDelay;
    real_T ConfirmNode_timeDelay_i;
    real_T ConfirmNode_timeDelay_j;
    SignStatusMatrix EnumeratedConstant1_Value;
    SignStatusMatrix EnumeratedConstant_Value;
    SignStatusMatrix EnumeratedConstant1_Value_d;
    boolean_T SRFlipFlop1_initial_condition;
    boolean_T SRFlipFlop_initial_condition;
    boolean_T SRFlipFlop_initial_condition_b;
    boolean_T SRFlipFlop_initial_condition_h;
    boolean_T SRFlipFlop_initial_condition_i;
    boolean_T SRFlipFlop_initial_condition_d;
    boolean_T SRFlipFlop_initial_condition_iz;
    boolean_T SRFlipFlop_initial_condition_l;
    boolean_T SRFlipFlop_initial_condition_j;
    boolean_T SRFlipFlop_initial_condition_h5;
    boolean_T SRFlipFlop_initial_condition_e;
    boolean_T SRFlipFlop_initial_condition_c;
    boolean_T SRFlipFlop_initial_condition_o;
    boolean_T SRFlipFlop_initial_condition_g;
    boolean_T SRFlipFlop_initial_condition_n;
    boolean_T SRFlipFlop_initial_condition_of;
    boolean_T PulseNode_isRisingEdge;
    boolean_T ConfirmNode1_isRisingEdge;
    boolean_T ConfirmNode_isRisingEdge;
    boolean_T ConfirmNode_isRisingEdge_h;
    boolean_T PulseNode_isRisingEdge_p;
    boolean_T PulseNode_isRisingEdge_h;
    boolean_T ConfirmNode_isRisingEdge_m;
    boolean_T PulseNode_isRisingEdge_c;
    boolean_T PulseNode_isRisingEdge_i;
    boolean_T PulseNode1_isRisingEdge;
    boolean_T PulseNode_isRisingEdge_j;
    boolean_T PulseNode2_isRisingEdge;
    boolean_T PulseNode1_isRisingEdge_k;
    int8_T CompareToConstant_const_b;
    int8_T CompareToConstant_const_j;
    fmgc_outputs out_Y0;
    base_fmgc_bus_outputs Constant4_Value;
    base_fmgc_ap_fd_logic_outputs Delay_InitialCondition;
    real32_T Constant17_Value;
    real32_T Constant18_Value;
    real32_T Constant19_Value;
    real32_T Constant20_Value;
    real32_T Constant16_Value;
    real32_T Constant1_Value;
    real32_T Constant2_Value;
    real32_T Constant21_Value;
    real32_T Constant22_Value;
    real32_T Constant23_Value;
    real32_T Constant24_Value;
    real32_T Constant25_Value;
    real32_T Constant26_Value;
    real32_T Constant27_Value;
    real32_T Constant28_Value;
    real32_T Constant11_Value;
    real32_T Constant12_Value;
    real32_T Constant13_Value;
    real32_T Constant14_Value;
    real32_T Constant15_Value;
    real32_T Constant29_Value;
    real32_T Constant30_Value;
    real32_T Constant31_Value;
    real32_T Constant32_Value;
    real32_T Constant33_Value;
    real32_T Constant1_Value_k;
    real32_T Constant11_Value_m;
    boolean_T Delay_InitialCondition_g;
    boolean_T Logic_table[16];
    boolean_T Logic_table_h[16];
    boolean_T Logic_table_n[16];
    boolean_T Logic_table_b[16];
    boolean_T Logic_table_hz[16];
    boolean_T Logic_table_k[16];
    boolean_T Logic_table_p[16];
    boolean_T Logic_table_c[16];
    boolean_T Logic_table_pl[16];
    boolean_T Logic_table_o[16];
    boolean_T Logic_table_c2[16];
    boolean_T Logic_table_i[16];
    boolean_T Logic_table_g[16];
    boolean_T Logic_table_a[16];
    boolean_T Logic_table_ku[16];
    boolean_T Logic_table_g4[16];
    boolean_T Constant_Value;
    boolean_T Constant1_Value_i;
    boolean_T Constant10_Value;
    boolean_T Constant3_Value;
    boolean_T Constant4_Value_g;
    boolean_T Constant5_Value;
    boolean_T Constant6_Value;
    boolean_T Constant7_Value;
    boolean_T Constant8_Value;
    boolean_T Constant9_Value;
  };

  FmgcComputer(FmgcComputer const&) = delete;
  FmgcComputer& operator= (FmgcComputer const&) & = delete;
  FmgcComputer(FmgcComputer &&) = delete;
  FmgcComputer& operator= (FmgcComputer &&) = delete;
  void setExternalInputs(const ExternalInputs_FmgcComputer_T *pExternalInputs_FmgcComputer_T)
  {
    FmgcComputer_U = *pExternalInputs_FmgcComputer_T;
  }

  const ExternalOutputs_FmgcComputer_T &getExternalOutputs() const
  {
    return FmgcComputer_Y;
  }

  void initialize();
  void step();
  static void terminate();
  FmgcComputer();
  ~FmgcComputer();
 private:
  ExternalInputs_FmgcComputer_T FmgcComputer_U;
  ExternalOutputs_FmgcComputer_T FmgcComputer_Y;
  D_Work_FmgcComputer_T FmgcComputer_DWork;
  static Parameters_FmgcComputer_T FmgcComputer_P;
  static void FmgcComputer_MATLABFunction_Reset(rtDW_MATLABFunction_FmgcComputer_T *localDW);
  static void FmgcComputer_MATLABFunction(boolean_T rtu_u, real_T rtu_Ts, boolean_T rtu_isRisingEdge, real_T
    rtu_timeDelay, boolean_T *rty_y, rtDW_MATLABFunction_FmgcComputer_T *localDW);
  static void FmgcComputer_MATLABFunction_m_Reset(rtDW_MATLABFunction_FmgcComputer_e_T *localDW);
  static void FmgcComputer_MATLABFunction_i(boolean_T rtu_u, boolean_T rtu_isRisingEdge, boolean_T *rty_y,
    rtDW_MATLABFunction_FmgcComputer_e_T *localDW);
  static void FmgcComputer_MATLABFunction_f(const base_arinc_429 *rtu_u, boolean_T *rty_y);
  static void FmgcComputer_MATLABFunction_k(const base_arinc_429 *rtu_u, real_T rtu_bit, uint32_T *rty_y);
  static void FmgcComputer_MATLABFunction_g(const base_arinc_429 *rtu_u, boolean_T *rty_y);
  static void FmgcComputer_MATLABFunction_gy(const boolean_T rtu_u[19], real32_T *rty_y);
};

#endif

