import { ComponentProps, DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { FcuSimvars } from '../shared/FcuSimvarPublisher';

interface EisDisplayProps extends ComponentProps {
    isCaptSide: boolean;
    x: number;
    y: number;
    bus: EventBus;
}

export class EisDisplay extends DisplayComponent<EisDisplayProps> {
    public onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<FcuSimvars>();
    }

    public render(): VNode {
        return (
            <g transform={`translate(${this.props.x} ${this.props.y})`} class="efis-background">
                <text id="QFE" class="Inactive" x="25.088" y="32.768">QFE</text>
                <text id="QNH" class="Active" x="150.528" y="32.768" text-anchor="end">QNH</text>
                <text id="Value" class="Value" x="14.336" y="88.064">1013</text>
            </g>
        );
    }
}
