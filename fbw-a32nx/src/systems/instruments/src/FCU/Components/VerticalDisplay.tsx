import { DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { FcuSimvars } from '../shared/FcuSimvarPublisher';

export class VerticalDisplay extends DisplayComponent<{bus: EventBus}> {
    private vsValue = 0;

    private vsDashes = false;

    private trkFpaMode = false;

    private dotVisibilitySub = Subject.create('');

    private vsLabelSub = Subject.create('');

    private fpaLabelSub = Subject.create('');

    private altValueSub = Subject.create('');

    private vsValueSub = Subject.create('');

    public onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<FcuSimvars>();

        sub.on('afsDisplayTrkFpaMode').whenChanged().handle((value) => {
            this.trkFpaMode = value;

            this.fpaLabelSub.set(value ? 'Active' : 'Inactive');
            this.vsLabelSub.set(value ? 'Inactive' : 'Active');

            this.handleVsFpaDisplay();
        });

        sub.on('afsDisplayVsFpaDashes').whenChanged().handle((value) => {
            this.vsDashes = value;
            this.handleVsFpaDisplay();
        });

        sub.on('afsDisplayVsFpaValue').whenChanged().handle((value) => {
            this.vsValue = value;
            this.handleVsFpaDisplay();
        });

        sub.on('afsDisplayAltValue').whenChanged().handle((value) => {
            this.altValueSub.set(Math.round(value).toString().padStart(5, '0'));
        });

        sub.on('afsDisplayLvlChManaged').whenChanged().handle((value) => {
            this.dotVisibilitySub.set(value ? 'visible' : 'hidden');
        });
    }

    private handleVsFpaDisplay() {
        const sign = Math.sign(this.vsValue) >= 0 ? '+' : '~';
        const absValue = Math.abs(this.vsValue);

        if (this.trkFpaMode && this.vsDashes) {
            this.vsValueSub.set('~-.-');
        } else if (this.trkFpaMode && !this.vsDashes) {
            this.vsValueSub.set(`${sign}${absValue.toFixed(1)}`);
        } else if (this.vsDashes) {
            this.vsValueSub.set('~----');
        } else {
            this.vsValueSub.set(`${sign}${Math.floor(absValue * 0.01).toString().padStart(2, '0')}oo`);
        }
    }

    public render(): VNode {
        return (
            <g transform="translate(768 0)">
                <g>
                    <text id="ALT" class="Active" x="128" y="30.72">ALT</text>
                    <text id="Value" class="Value" x="48" y="87.04">{this.altValueSub}</text>
                </g>

                <g transform="translate(256 0)">
                    <text
                        id="VS"
                        x="174.08"
                        y="30.72"
                        text-anchor="end"
                        class={this.vsLabelSub}
                    >
                        V/S
                    </text>
                    <text
                        id="FPA"
                        x="230.4"
                        y="30.72"
                        text-anchor="end"
                        class={this.fpaLabelSub}
                    >
                        FPA
                    </text>
                    <text id="Value" class="Value" x="38.4" y="87.04">{this.vsValueSub}</text>
                </g>

                <g>
                    <line x1="184.32" y1="18.432" x2="184.32" y2="30.72" />
                    <line x1="184.32" y1="20.48" x2="220.16" y2="20.48" />
                    <text id="LVLCH" class="Active" x="225.28" y="30.72">LVL/CH</text>
                    <line x1="373.76" y1="18.432" x2="373.76" y2="30.72" />
                    <line x1="373.76" y1="20.48" x2="337.92" y2="20.48" />
                    <circle id="Illuminator" r="14" cx="272." cy="63.488" visibility={this.dotVisibilitySub} />
                </g>
            </g>
        );
    }
}
