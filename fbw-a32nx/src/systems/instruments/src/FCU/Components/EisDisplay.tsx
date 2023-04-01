import { ComponentProps, DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { FcuSimvars } from '../shared/FcuSimvarPublisher';

interface EisDisplayProps extends ComponentProps {
    isCaptSide: boolean;
    x: number;
    y: number;
    bus: EventBus;
}

export class EisDisplay extends DisplayComponent<EisDisplayProps> {
    private baroValueMode = 0;

    private baroValue = 0;

    private baroMode = 0;

    private baroValueSub = Subject.create('');

    private qnhRef = FSComponent.createRef<SVGGElement>();

    private qfeRef = FSComponent.createRef<SVGGElement>();

    public onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<FcuSimvars>();

        sub.on(`eisDisplay${this.props.isCaptSide ? 'Left' : 'Right'}BaroValueMode`).whenChanged().handle((newVal) => {
            this.baroValueMode = newVal;
            this.handleDisplay();
        });

        sub.on(`eisDisplay${this.props.isCaptSide ? 'Left' : 'Right'}BaroValue`).whenChanged().handle((newVal) => {
            this.baroValue = newVal;
            this.handleDisplay();
        });

        sub.on(`eisDisplay${this.props.isCaptSide ? 'Left' : 'Right'}BaroMode`).whenChanged().handle((newVal) => {
            this.baroMode = newVal;
            this.handleDisplay();
        });
    }

    private handleDisplay() {
        if (this.baroValueMode === 0) {
            this.baroValueSub.set('Std');
        } else if (this.baroValueMode === 1) {
            this.baroValueSub.set(Math.round(this.baroValue).toString());
        } else {
            this.baroValueSub.set(this.baroValue.toFixed(2));
        }

        if (this.baroMode === 0) {
            this.qfeRef.instance.classList.remove('Active');
            this.qfeRef.instance.classList.add('Inactive');
            this.qnhRef.instance.classList.remove('Active');
            this.qnhRef.instance.classList.add('Inactive');
        } else if (this.baroMode === 1) {
            this.qfeRef.instance.classList.remove('Active');
            this.qfeRef.instance.classList.add('Inactive');
            this.qnhRef.instance.classList.remove('Inactive');
            this.qnhRef.instance.classList.add('Active');
        } else {
            this.qfeRef.instance.classList.remove('Inactive');
            this.qfeRef.instance.classList.add('Active');
            this.qnhRef.instance.classList.remove('Active');
            this.qnhRef.instance.classList.add('Inactive');
        }
    }

    public render(): VNode {
        return (
            <g transform={`translate(${this.props.x} ${this.props.y})`} class="efis-background">
                <text id="QFE" class="Inactive" x="25.088" y="32.768" ref={this.qfeRef}>QFE</text>
                <text id="QNH" class="Active" x="150.528" y="32.768" text-anchor="end" ref={this.qnhRef}>QNH</text>
                <text id="Value" class="Value" x="14.336" y="88.064">{this.baroValueSub}</text>
            </g>
        );
    }
}
