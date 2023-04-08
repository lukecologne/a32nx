import { ComponentProps, DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { FcuSimvars } from '../shared/FcuSimvarPublisher';
import { HdgDisplay } from './HdgDisplay';
import { SpdDisplay } from './SpdDisplay';
import { VerticalDisplay } from './VerticalDisplay';

interface AfsDisplayProps extends ComponentProps {
    bus: EventBus;
}

export class AfsDisplay extends DisplayComponent<AfsDisplayProps> {
    private lightsTest = false;

    private trkFpaMode = false;

    private trkFpaLabelSub = Subject.create('');

    private hdgVsLabelSub = Subject.create('');

    public onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<FcuSimvars>();

        sub.on('lightsTest').whenChanged().handle((value) => {
            this.lightsTest = value === 0;

            this.handleLabels();
        });

        sub.on('afsDisplayTrkFpaMode').whenChanged().handle((value) => {
            this.trkFpaMode = value;
            this.handleLabels();
        });
    }

    private handleLabels() {
        this.trkFpaLabelSub.set(this.trkFpaMode || this.lightsTest ? 'Active' : 'Inactive');
        this.hdgVsLabelSub.set(!this.trkFpaMode || this.lightsTest ? 'Active' : 'Inactive');
    }

    public render(): VNode {
        return (
            <g>
                <SpdDisplay bus={this.props.bus} />

                <HdgDisplay bus={this.props.bus} />

                <g transform="translate(512 0)">
                    <text id="HDG" class={this.hdgVsLabelSub} x="102.4" y="51.2" text-anchor="end" alignment-baseline="middle">HDG</text>
                    <text id="TRK" class={this.trkFpaLabelSub} x="102.4" y="87.04" text-anchor="end">TRK</text>
                    <rect id="separator" x="120.32" y="0" width="15.36" height="102.4" fill="rgb(158, 158, 157)" fill-opacity="0.05" />
                    <text id="VS" class={this.hdgVsLabelSub} x="153.6" y="51.2" alignment-baseline="middle">V/S</text>
                    <text id="FPA" class={this.trkFpaLabelSub} x="153.6" y="87.04">FPA</text>
                </g>

                <VerticalDisplay bus={this.props.bus} />
            </g>
        );
    }
}
