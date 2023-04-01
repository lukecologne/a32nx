import { EventBus, SimVarDefinition, SimVarValueType, SimVarPublisher } from 'msfssdk';

export interface FcuSimvars {
    eisDisplayLeftBaroValueMode: number;
    eisDisplayLeftBaroValue: number;
    eisDisplayLeftBaroMode: number;
    eisDisplayRightBaroValueMode: number;
    eisDisplayRightBaroValue: number;
    eisDisplayRightBaroMode: number;

    afsDisplayTrkFpaMode: boolean;
    afsDisplayMachMode: boolean;
    afsDisplaySpdMachValue: number;
    afsDisplaySpdMachManaged: boolean;
    afsDisplayHdgTrkValue: number;
    afsDisplayHdgTrkManaged: boolean;
    afsDisplayAltValue: number;
    afsDisplayLvlChManaged: boolean;
    afsDisplayVsFpaValue: number;
}

export enum FcuVars {
    eisDisplayLeftBaroValueMode = 'L:A32NX_FCU_EFIS_L_DISPLAY_BARO_VALUE_MODE',
    eisDisplayLeftBaroValue = 'L:A32NX_FCU_EFIS_L_DISPLAY_BARO_VALUE',
    eisDisplayLeftBaroMode = 'L:A32NX_FCU_EFIS_L_DISPLAY_BARO_MODE',
    eisDisplayRightBaroValueMode = 'L:A32NX_FCU_EFIS_R_DISPLAY_BARO_VALUE_MODE',
    eisDisplayRightBaroValue = 'L:A32NX_FCU_EFIS_R_DISPLAY_BARO_VALUE',
    eisDisplayRightBaroMode = 'L:A32NX_FCU_EFIS_R_DISPLAY_BARO_MODE',

    afsDisplayTrkFpaMode = 'L:A32NX_FCU_AFS_DISPLAY_TRK_FPA_MODE',
    afsDisplayMachMode = 'L:A32NX_FCU_AFS_DISPLAY_MACH_MODE',
    afsDisplaySpdMachValue = 'L:A32NX_FCU_AFS_DISPLAY_SPD_MACH_VALUE',
    afsDisplaySpdMachManaged = 'L:A32NX_FCU_AFS_DISPLAY_SPD_MACH_MANAGED',
    afsDisplayHdgTrkValue = 'L:A32NX_FCU_AFS_DISPLAY_HDG_TRK_VALUE',
    afsDisplayHdgTrkManaged = 'L:A32NX_FCU_AFS_DISPLAY_HDG_TRK_MANAGED',
    afsDisplayAltValue = 'L:A32NX_FCU_AFS_DISPLAY_ALT_VALUE',
    afsDisplayLvlChManaged = 'L:A32NX_FCU_AFS_DISPLAY_LVL_CH_MANAGED',
    afsDisplayVsFpaValue = 'L:A32NX_FCU_AFS_DISPLAY_VS_FPA_VALUE',
}

export class FCUSimvarPublisher extends SimVarPublisher<FcuSimvars> {
    private static simvars = new Map<keyof FcuSimvars, SimVarDefinition>([
        ['eisDisplayLeftBaroValueMode', { name: FcuVars.eisDisplayLeftBaroValueMode, type: SimVarValueType.Number }],
        ['eisDisplayLeftBaroValue', { name: FcuVars.eisDisplayLeftBaroValue, type: SimVarValueType.Number }],
        ['eisDisplayLeftBaroMode', { name: FcuVars.eisDisplayLeftBaroMode, type: SimVarValueType.Number }],
        ['eisDisplayRightBaroValueMode', { name: FcuVars.eisDisplayRightBaroValueMode, type: SimVarValueType.Number }],
        ['eisDisplayRightBaroValue', { name: FcuVars.eisDisplayRightBaroValue, type: SimVarValueType.Number }],
        ['eisDisplayRightBaroMode', { name: FcuVars.eisDisplayRightBaroMode, type: SimVarValueType.Number }],

        ['afsDisplayTrkFpaMode', { name: FcuVars.afsDisplayTrkFpaMode, type: SimVarValueType.Bool }],
        ['afsDisplayMachMode', { name: FcuVars.afsDisplayMachMode, type: SimVarValueType.Bool }],
        ['afsDisplaySpdMachValue', { name: FcuVars.afsDisplaySpdMachValue, type: SimVarValueType.Number }],
        ['afsDisplaySpdMachManaged', { name: FcuVars.afsDisplaySpdMachManaged, type: SimVarValueType.Bool }],
        ['afsDisplayHdgTrkValue', { name: FcuVars.afsDisplayHdgTrkValue, type: SimVarValueType.Number }],
        ['afsDisplayHdgTrkManaged', { name: FcuVars.afsDisplayHdgTrkManaged, type: SimVarValueType.Bool }],
        ['afsDisplayAltValue', { name: FcuVars.afsDisplayAltValue, type: SimVarValueType.Number }],
        ['afsDisplayLvlChManaged', { name: FcuVars.afsDisplayLvlChManaged, type: SimVarValueType.Bool }],
        ['afsDisplayVsFpaValue', { name: FcuVars.afsDisplayVsFpaValue, type: SimVarValueType.Number }],
    ])

    public constructor(bus: EventBus) {
        super(FCUSimvarPublisher.simvars, bus);
    }
}
