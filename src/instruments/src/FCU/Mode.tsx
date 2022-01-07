import React from 'react';
import { useSimVar } from '@instruments/common/simVars';
import { useArinc429Var } from '@instruments/common/arinc429';
import { SvgGroup } from '../SD/Common/SvgGroup';

export const Mode = () => {
    const [annLtSwitchPos] = useSimVar('L:A32NX_OVHD_INTLT_ANN', 'number', 500);
    const ltsTest = annLtSwitchPos === 0;

    const fcuDiscreteWord1 = useArinc429Var('L:A32NX_FCU_DISCRETE_WORD_1');
    const isTrkFpa = fcuDiscreteWord1.getBitValue(25);

    return (
        <SvgGroup x={512} y={0}>
            <text className={!isTrkFpa || ltsTest ? 'active' : 'inactive'} x="102.4" y="51" textAnchor="end" alignmentBaseline="middle">HDG</text>
            <text className={isTrkFpa || ltsTest ? 'active' : 'inactive'} x="102.4" y="87" textAnchor="end">TRK</text>
            <text className={!isTrkFpa || ltsTest ? 'active' : 'inactive'} x="153.6" y="51" alignmentBaseline="middle">V/S</text>
            <text className={isTrkFpa || ltsTest ? 'active' : 'inactive'} x="153.6" y="87">FPA</text>
        </SvgGroup>
    );
};
