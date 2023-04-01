import { ComponentProps, DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { FcuSimvars } from '../shared/FcuSimvarPublisher';

interface AfsDisplayProps extends ComponentProps {
    bus: EventBus;
}

export class AfsDisplay extends DisplayComponent<AfsDisplayProps> {
    public onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<FcuSimvars>();
    }

    public render(): VNode {
        return (
            <g class="afs-background">
                <g>
                    <text id="SPD" class="Active" x="38.4" y="30.72">SPD</text>
                    <text id="MACH" class="Inactive" x="102.4" y="30.72">MACH</text>
                    <text id="Value" class="Value" x="46.08" y="87.04">100</text>
                    <circle id="Illuminator" r="14" cx="186.88" cy="63.488" />
                </g>

                <g transform="translate(256 0)">
                    <text id="HDG" class="Active" x="38.4" y="30.72">HDG</text>
                    <text id="TRK" class="Inactive" x="104.96" y="30.72">TRK</text>
                    <text id="LAT" class="Active" x="163.84" y="30.72">LAT</text>
                    <text id="Value" class="Value" x="43.52" y="87.04">054</text>
                    <circle id="Illuminator" r="14" cx="186.88" cy="63.488" />
                </g>

                <g transform="translate(512 0)">
                    <text id="HDG" class="Active" x="102.4" y="51.2" text-anchor="end" alignment-baseline="middle">HDG</text>
                    <text id="TRK" class="Inactive" x="102.4" y="87.04" text-anchor="end">TRK</text>
                    <rect id="separator" x="120.32" y="0" width="15.36" height="102.4" fill="rgb(158, 158, 157)" fill-opacity="0.05" />
                    <text id="VS" class="Active" x="153.6" y="51.2" alignment-baseline="middle">V/S</text>
                    <text id="FPA" class="Inactive" x="153.6" y="87.04">FPA</text>
                </g>

                <g transform="translate(768 0)">
                    <g>
                        <text id="ALT" class="Active" x="128" y="30.72">ALT</text>
                        <text id="Value" class="Value" x="48" y="87.04">00100</text>
                        <circle id="Illuminator" r="14" cx="272." cy="63.488" />
                    </g>

                    <g transform="translate(256 0)">
                        <text id="VS" class="Active" x="174.08" y="30.72" text-anchor="end">V/S</text>
                        <text id="FPA" class="Inactive" x="230.4" y="30.72" text-anchor="end">FPA</text>
                        <text id="Value" class="Value" x="38.4" y="87.04">+00oo</text>
                    </g>

                    <g>
                        <line x1="184.32" y1="18.432" x2="184.32" y2="30.72" />
                        <line x1="184.32" y1="20.48" x2="220.16" y2="20.48" />
                        <text id="LVLCH" class="Active" x="225.28" y="30.72">LVL/CH</text>
                        <line x1="373.76" y1="18.432" x2="373.76" y2="30.72" />
                        <line x1="373.76" y1="20.48" x2="337.92" y2="20.48" />
                    </g>
                </g>
            </g>
        );
    }
}
