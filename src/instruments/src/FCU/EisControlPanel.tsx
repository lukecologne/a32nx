import React from 'react';
import { useSimVar } from '@instruments/common/simVars';
import { useArinc429Var } from '@instruments/common/arinc429';

interface EisControlPanelProps {
    isLeftSide: boolean
}

export const EisControlPanel = ({ isLeftSide }: EisControlPanelProps) => {
    const fcuEis1Word = useArinc429Var(`L:A32NX_FCU_${isLeftSide ? 'L' : 'R'}_EIS_WORD_1`);
    const fcuEis2Word = useArinc429Var(`L:A32NX_FCU_${isLeftSide ? 'L' : 'R'}_EIS_WORD_2`);
    const fcuBaroSettingHpa = useArinc429Var(`L:A32NX_FCU_${isLeftSide ? 'L' : 'R'}_BARO_CORR_HPA`);
    const fcuBaroSettingInhg = useArinc429Var(`L:A32NX_FCU_${isLeftSide ? 'L' : 'R'}_BARO_CORR_INHG`);

    const baroIsStd = fcuEis2Word.getBitValue(28);
    const baroIsQnh = fcuEis2Word.getBitValue(29);

    const [annLtSwitchPos] = useSimVar('L:A32NX_OVHD_INTLT_ANN', 'number', 500);
    const ltsTest = annLtSwitchPos === 0;

    let formattedValueString: string;
    if (ltsTest) {
        formattedValueString = '88.88';
    } else if (baroIsStd) {
        formattedValueString = 'Std';
    } else if (fcuEis1Word.getBitValue(11)) {
        formattedValueString = (Math.round(fcuBaroSettingInhg.value * 100) / 100).toFixed(2);
    } else {
        formattedValueString = fcuBaroSettingHpa.value.toString().padStart(4, '0');
    }

    return (
        <svg className="baro-svg" viewBox="0 0 179 102" style={{ top: '102px', left: isLeftSide ? '0px' : '179px' }}>
            <text className={(!baroIsQnh && !baroIsStd) || ltsTest ? 'active' : 'inactive'} x="25" y="33">QFE</text>
            <text className={(baroIsQnh && !baroIsStd) || ltsTest ? 'active' : 'inactive'} x="150" y="33" textAnchor="end">QNH</text>
            <text className="value" x="14" y="88" textAnchor="start">{formattedValueString}</text>
        </svg>
    );
};
