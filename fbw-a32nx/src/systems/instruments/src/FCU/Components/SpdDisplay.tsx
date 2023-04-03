import { DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { FcuSimvars } from '../shared/FcuSimvarPublisher';

export class SpdDisplay extends DisplayComponent<{bus: EventBus}> {
    private value = 0;

    private dashes = false;

    private machActive = false;

    private dotVisibilitySub = Subject.create('');

    private spdLabelSub = Subject.create('');

    private machLabelSub = Subject.create('');

    private valueSub = Subject.create('');

    public onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<FcuSimvars>();

        sub.on('afsDisplayMachMode').whenChanged().handle((value) => {
            this.machActive = value;
            this.machLabelSub.set(value ? 'Active' : 'Inactive');
            this.spdLabelSub.set(value ? 'Inactive' : 'Active');

            this.handleSpeedDisplay();
        });

        sub.on('afsDisplaySpdMachDashes').whenChanged().handle((value) => {
            this.dashes = value;
            this.handleSpeedDisplay();
        });

        sub.on('afsDisplaySpdMachValue').whenChanged().handle((value) => {
            this.value = value;
            this.handleSpeedDisplay();
        });

        sub.on('afsDisplaySpdMachManaged').whenChanged().handle((value) => {
            this.dotVisibilitySub.set(value ? 'visible' : 'hidden');
        });
    }

    private handleSpeedDisplay() {
        if (this.machActive && this.dashes) {
            this.valueSub.set('-.--');
        } else if (this.machActive && !this.dashes) {
            this.valueSub.set(this.value.toFixed(2));
        } else if (this.dashes) {
            this.valueSub.set('---');
        } else {
            this.valueSub.set(Math.round(this.value).toString().padStart(3, '0'));
        }
    }

    public render(): VNode {
        return (
            <g>
                <text id="SPD" class={this.spdLabelSub} x="38.4" y="30.72">SPD</text>
                <text id="MACH" class={this.machLabelSub} x="102.4" y="30.72">MACH</text>
                <text id="Value" class="Value" x="46.08" y="87.04">{this.valueSub}</text>
                <circle id="Illuminator" r="14" cx="186.88" cy="63.488" visibility={this.dotVisibilitySub} />
            </g>
        );
    }
}
