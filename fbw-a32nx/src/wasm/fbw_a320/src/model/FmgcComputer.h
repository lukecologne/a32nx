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

  struct D_Work_FmgcComputer_T {
    base_fmgc_ap_fd_logic_outputs Delay_DSTATE;
    boolean_T Delay_DSTATE_p;
    boolean_T Memory_PreviousInput;
    boolean_T Memory_PreviousInput_g;
    boolean_T Memory_PreviousInput_p;
    boolean_T previousInput;
    boolean_T previousInput_not_empty;
    boolean_T Runtime_MODE;
    rtDW_MATLABFunction_FmgcComputer_T sf_MATLABFunction_m;
    rtDW_MATLABFunction_FmgcComputer_T sf_MATLABFunction;
  };

  struct ExternalInputs_FmgcComputer_T {
    fmgc_inputs in;
  };

  struct ExternalOutputs_FmgcComputer_T {
    fmgc_outputs out;
  };

  struct Parameters_FmgcComputer_T {
    base_fmgc_logic_outputs fmgc_logic_output_MATLABStruct;
    base_fmgc_ap_fd_logic_outputs fmgc_ap_fd_logic_output_MATLABStruct;
    base_fmgc_discrete_outputs fmgc_discrete_output_MATLABStruct;
    real_T ConfirmNode_timeDelay;
    real_T ConfirmNode_timeDelay_b;
    SignStatusMatrix EnumeratedConstant1_Value;
    boolean_T SRFlipFlop1_initial_condition;
    boolean_T SRFlipFlop_initial_condition;
    boolean_T SRFlipFlop_initial_condition_b;
    boolean_T ConfirmNode_isRisingEdge;
    boolean_T PulseNode_isRisingEdge;
    boolean_T ConfirmNode_isRisingEdge_k;
    fmgc_outputs out_Y0;
    base_fmgc_bus_outputs Constant4_Value;
    base_fmgc_ap_fd_logic_outputs Delay_InitialCondition;
    real32_T Constant16_Value;
    real32_T Constant1_Value;
    real32_T Constant2_Value;
    real32_T Constant11_Value;
    real32_T Constant12_Value;
    real32_T Constant13_Value;
    real32_T Constant14_Value;
    real32_T Constant15_Value;
    boolean_T Delay_InitialCondition_g;
    boolean_T Logic_table[16];
    boolean_T Logic_table_h[16];
    boolean_T Logic_table_n[16];
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
  static void FmgcComputer_RAMonitoring(const fmgc_outputs *rtu_in, real32_T *rty_raComputationValue, boolean_T
    *rty_dualRaFailure);
  static void FmgcComputer_MATLABFunction_g(const boolean_T rtu_u[19], real32_T *rty_y);
};

#endif

