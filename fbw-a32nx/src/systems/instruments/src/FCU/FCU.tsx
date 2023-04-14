import { ComponentProps, DisplayComponent, EventBus, FSComponent, VNode } from '@microsoft/msfs-sdk';
import { EisDisplay } from 'instruments/src/FCU/Components/EisDisplay';
import { AfsDisplay } from 'instruments/src/FCU/Components/AfsDisplay';

import './style.scss';

interface FCUProps extends ComponentProps {
    bus: EventBus;
}

export class FCUComponent extends DisplayComponent<FCUProps> {
    onAfterRender(node: VNode): void {
        super.onAfterRender(node);
    }

    render(): VNode {
        return (
            <svg class="fcu-svg" version="1.1" viewBox="0 0 1280 256" xmlns="http://www.w3.org/2000/svg">
                <AfsDisplay bus={this.props.bus} />
                <EisDisplay isCaptSide x={0} y={102.4} bus={this.props.bus} />
                <EisDisplay isCaptSide={false} x={203.2} y={102.4} bus={this.props.bus} />
            </svg>
        );
    }
}
