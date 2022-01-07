import React from 'react';
import { render } from '@instruments/common/index';
import { useSimVar } from '@instruments/common/simVars';
import { useCoherentEvent } from '@instruments/common/hooks';
import { EisControlPanel } from './EisControlPanel';
import { AfsControlPanel } from './AfsControlPanel';

import './style.scss';

const Fcu = () => {
    const [dcBusEssPowered] = useSimVar('L:A32NX_ELEC_DC_ESS_BUS_IS_POWERED', 'Bool', 250);
    const [dcBus2Powered] = useSimVar('L:A32NX_ELEC_DC_2_BUS_IS_POWERED', 'Bool', 250);

    const [potValue] = useSimVar('LIGHT POTENTIOMETER:87', 'percent over 100', 250);

    // This forwards H events to the C++ logic, since Custom K events cannot be
    // used in XML.
    // Decomposes the H event name into K event name and K event index, so
    // "H:A32NX_FCU_TEST:2" would become SetSimVarValue('K:A32NX.FCU_TEST', 'number', 2).
    // This allows data to be transmitted with H events.
    useCoherentEvent('OnInteractionEvent', (target: string, args: string[]) => {
        const name = args[0];
        const prefix = 'A32NX_FCU';

        if (name.startsWith(prefix)) {
            let num = 0;
            let kEventName = `K:A32NX.FCU${name.slice(prefix.length)}`;
            const colonIndex = kEventName.search(/:\d*$/);

            if (colonIndex !== -1) {
                num = Number(kEventName.slice(colonIndex + 1));
                kEventName = kEventName.slice(0, colonIndex);
            }

            SimVar.SetSimVarValue(kEventName, 'number', num);
        }
    });

    if (!(dcBusEssPowered || dcBus2Powered) || potValue === 0) return null;

    return (
        <div className="wrapper">
            <AfsControlPanel />
            <EisControlPanel isLeftSide />
            <EisControlPanel isLeftSide={false} />
        </div>
    );
};

render(<Fcu />);
