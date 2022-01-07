import React from 'react';
import { useSimVar } from '@instruments/common/simVars';
import { useArinc429Var } from '@instruments/common/arinc429';
import { SvgGroup } from '../SD/Common/SvgGroup';

export const SpeedControl = () => {
    const [annLtSwitchPos] = useSimVar('L:A32NX_OVHD_INTLT_ANN', 'number', 500);
    const ltsTest = annLtSwitchPos === 0;

    const fcuDiscreteWord1 = useArinc429Var('L:A32NX_FCU_DISCRETE_WORD_1');
    const isMach = fcuDiscreteWord1.getBitValue(25);
    const fmgc1HasPriority = fcuDiscreteWord1.getBitValue(20);

    const fmgcDiscreteWord5 = useArinc429Var(`L:A32NX_FMGC_${fmgc1HasPriority ? '1' : '2'}_DISCRETE_WORD_5`);
    const autoSpeedControl = fmgcDiscreteWord5.getBitValueOr(19, false);

    const fcuSpdValue = useArinc429Var('L:A32NX_FCU_SELECTED_SPEED');
    const fcuMachValue = useArinc429Var('L:A32NX_FCU_SELECTED_MACH');

    let displayString = '';
    if (ltsTest) {
        displayString = '8.88';
    } else if (fcuSpdValue.isNoComputedData() && fcuMachValue.isNoComputedData()) {
        displayString = isMach ? '-.--' : '---';
    } else if (fcuSpdValue.isNormalOperation() || fcuMachValue.isNormalOperation()) {
        displayString = isMach ? fcuMachValue.value.toFixed(2) : Math.round(fcuSpdValue.value).toString();
    }

    return (
        <SvgGroup x={0} y={0}>
            <text className={!isMach || ltsTest ? 'active' : 'inactive'} x="38" y="31">SPD</text>
            <text className={isMach || ltsTest ? 'active' : 'inactive'} x="102" y="31">MACH</text>
            <text className="value" x="46" y="87">{displayString}</text>
            <circle className={autoSpeedControl || ltsTest ? 'active' : 'inactive'} r="13" cx="187" cy="63" />
        </SvgGroup>
    );
};
