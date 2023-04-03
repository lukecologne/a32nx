import { DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { FcuSimvars } from '../shared/FcuSimvarPublisher';

export class HdgDisplay extends DisplayComponent<{bus: EventBus}> {
    private value = 0;

    private dashes = false;

    private dotVisibilitySub = Subject.create('');

    private hdgLabelSub = Subject.create('');

    private trkLabelSub = Subject.create('');

    private valueSub = Subject.create('');

    public onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<FcuSimvars>();

        sub.on('afsDisplayTrkFpaMode').whenChanged().handle((value) => {
            this.trkLabelSub.set(value ? 'Active' : 'Inactive');
            this.hdgLabelSub.set(value ? 'Inactive' : 'Active');
        });

        sub.on('afsDisplayHdgTrkDashes').whenChanged().handle((value) => {
            this.dashes = value;
            this.handleHdgDisplay();
        });

        sub.on('afsDisplayHdgTrkValue').whenChanged().handle((value) => {
            this.value = value;
            this.handleHdgDisplay();
        });

        sub.on('afsDisplayHdgTrkManaged').whenChanged().handle((value) => {
            this.dotVisibilitySub.set(value ? 'visible' : 'hidden');
        });
    }

    private handleHdgDisplay() {
        if (this.dashes) {
            this.valueSub.set('---');
        } else {
            this.valueSub.set(Math.round(this.value).toString().padStart(3, '0'));
        }
    }

    public render(): VNode {
        return (
            <g transform="translate(256 0)">
                <text id="HDG" class={this.hdgLabelSub} x="38.4" y="30.72">HDG</text>
                <text id="TRK" class={this.trkLabelSub} x="104.96" y="30.72">TRK</text>
                <text id="LAT" class="Active" x="163.84" y="30.72">LAT</text>
                <text id="Value" class="Value" x="43.52" y="87.04">{this.valueSub}</text>
                <circle id="Illuminator" r="14" cx="186.88" cy="63.488" visibility={this.dotVisibilitySub} />
            </g>
        );
    }
}
