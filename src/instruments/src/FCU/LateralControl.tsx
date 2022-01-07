import React from 'react';
import { useSimVar } from '@instruments/common/simVars';
import { useArinc429Var } from '@instruments/common/arinc429';
import { SvgGroup } from '../SD/Common/SvgGroup';

export const LateralControl = () => {
    const [annLtSwitchPos] = useSimVar('L:A32NX_OVHD_INTLT_ANN', 'number', 500);
    const ltsTest = annLtSwitchPos === 0;

    const fcuDiscreteWord1 = useArinc429Var('L:A32NX_FCU_DISCRETE_WORD_1');
    const isTrkFpa = fcuDiscreteWord1.getBitValue(25);
    const fmgc1HasPriority = fcuDiscreteWord1.getBitValue(20);

    const fmgcDiscreteWord2 = useArinc429Var(`L:A32NX_FMGC_${fmgc1HasPriority ? '1' : '2'}_DISCRETE_WORD_2`);
    const fmgcDiscreteWord3 = useArinc429Var(`L:A32NX_FMGC_${fmgc1HasPriority ? '1' : '2'}_DISCRETE_WORD_3`);
    const fmgcDiscreteWord4 = useArinc429Var(`L:A32NX_FMGC_${fmgc1HasPriority ? '1' : '2'}_DISCRETE_WORD_4`);
    const selectedLatModeEngaged = fmgcDiscreteWord2.getBitValue(16) || fmgcDiscreteWord2.getBitValue(17) || fmgcDiscreteWord4.getBitValue(14);
    const managedLatModeArmed = fmgcDiscreteWord3.getBitValue(14) || fmgcDiscreteWord3.getBitValue(16);

    const fcuHdgValue = useArinc429Var('L:A32NX_FCU_SELECTED_HEADING');
    const fcuTrkValue = useArinc429Var('L:A32NX_FCU_SELECTED_TRACK');

    let displayString = '';
    if (ltsTest) {
        displayString = '888';
    } else if (fcuHdgValue.isNoComputedData() && fcuTrkValue.isNoComputedData()) {
        displayString = '---';
    } else if (fcuHdgValue.isNormalOperation() || fcuTrkValue.isNormalOperation()) {
        const val = isTrkFpa ? fcuTrkValue.value : fcuHdgValue.value;
        displayString = val.toString().padStart(3, '0');
    }

    return (
        <SvgGroup x={256} y={0}>
            <text className={!isTrkFpa || ltsTest ? 'active' : 'inactive'} x="38" y="31">HDG</text>
            <text className={isTrkFpa || ltsTest ? 'active' : 'inactive'} x="105" y="31">TRK</text>
            <text className="active" x="164" y="31">LAT</text>
            <text className="value" x="44" y="87">{displayString}</text>
            <circle className={!selectedLatModeEngaged || managedLatModeArmed || ltsTest ? 'active' : 'inactive'} r="13" cx="187" cy="63" />
        </SvgGroup>
    );
};
