import React from 'react';
import { useArinc429Var } from '@instruments/common/arinc429';
import { useSimVar } from '@instruments/common/simVars';
import { SvgGroup } from '../SD/Common/SvgGroup';

export const VerticalControl = () => {
    const [annLtSwitchPos] = useSimVar('L:A32NX_OVHD_INTLT_ANN', 'number', 500);
    const ltsTest = annLtSwitchPos === 0;

    const fcuDiscreteWord1 = useArinc429Var('L:A32NX_FCU_DISCRETE_WORD_1');
    const isTrkFpa = fcuDiscreteWord1.getBitValue(25);
    const fmgc1HasPriority = fcuDiscreteWord1.getBitValue(20);

    const fmgcDiscreteWord1 = useArinc429Var(`L:A32NX_FMGC_${fmgc1HasPriority ? '1' : '2'}_DISCRETE_WORD_1`);
    const fmgcDiscreteWord3 = useArinc429Var(`L:A32NX_FMGC_${fmgc1HasPriority ? '1' : '2'}_DISCRETE_WORD_3`);
    const fmgcDiscreteWord4 = useArinc429Var(`L:A32NX_FMGC_${fmgc1HasPriority ? '1' : '2'}_DISCRETE_WORD_4`);
    const managedVertModeActive = fmgcDiscreteWord1.getBitValue(22) || fmgcDiscreteWord1.getBitValue(15) || fmgcDiscreteWord1.getBitValue(16);
    const managedVertModeArmed = fmgcDiscreteWord3.getBitValue(24) || fmgcDiscreteWord3.getBitValue(25);

    const fcuAltValue = useArinc429Var('L:A32NX_FCU_SELECTED_ALT');

    const fcuVsValue = useArinc429Var('L:A32NX_FCU_SELECTED_VS');
    const fcuFpaValue = useArinc429Var('L:A32NX_FCU_SELECTED_FPA');

    let altDisplayString = '';
    if (ltsTest) {
        altDisplayString = '88888';
    } else if (fcuAltValue.isNoComputedData()) {
        altDisplayString = '-----';
    } else if (fcuAltValue.isNormalOperation()) {
        altDisplayString = fcuAltValue.value.toString().padStart(5, '0');
    }

    let vsFpaDisplayString = '';
    if (ltsTest) {
        vsFpaDisplayString = '+8888';
    } else if (fcuVsValue.isNoComputedData() && fcuFpaValue.isNoComputedData()) {
        vsFpaDisplayString = '-----';
    } else if (fcuVsValue.isNormalOperation() || fcuFpaValue.isNormalOperation()) {
        const vsFpaValue = isTrkFpa ? fcuFpaValue.value : fcuVsValue.value;
        vsFpaDisplayString = isTrkFpa ? Math.abs(vsFpaValue).toFixed(1) : Math.abs(vsFpaValue).toString().padStart(4, '0');
        vsFpaDisplayString = (vsFpaValue >= 0 ? '+' : '-') + vsFpaDisplayString;
    }

    return (
        <SvgGroup x={768} y={0}>
            <SvgGroup x={0} y={0}>
                <text className="active" x="128" y="30.6">ALT</text>
                <text className="value" x="48" y="86.7">{altDisplayString}</text>
                <circle className={managedVertModeActive || managedVertModeArmed || ltsTest ? 'active' : 'inactive'} r="13" cx="272" cy="63.2" />
            </SvgGroup>

            <SvgGroup x={0} y={0}>
                <path className="active" d="M184.3 30.6 v-12.2 h35.9 M337.9 18.4 h35.8 v12.2" />
                <text className="active" x="225.3" y="30.6">LVL/CH</text>
            </SvgGroup>

            <SvgGroup x={256} y={0}>
                <text className={!isTrkFpa || ltsTest ? 'active' : 'inactive'} x="174" y="30.6" textAnchor="end">V/S</text>
                <text className={isTrkFpa || ltsTest ? 'active' : 'inactive'} x="230.4" y="30.6" textAnchor="end">FPA</text>
                <text className="value" x="38.4" y="86.7">{vsFpaDisplayString}</text>
            </SvgGroup>
        </SvgGroup>
    );
};
