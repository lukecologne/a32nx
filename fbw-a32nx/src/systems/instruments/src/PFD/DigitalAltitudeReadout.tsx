// eslint-disable-next-line @typescript-eslint/no-unused-vars
import { DisplayComponent, EventBus, FSComponent, Subject, VNode } from 'msfssdk';
import { Arinc429Values } from './shared/ArincValueProvider';
import { PFDSimvars } from './shared/PFDSimvarPublisher';

interface DigitalAltitudeReadoutProps {
    bus: EventBus;
}

export class DigitalAltitudeReadout extends DisplayComponent<DigitalAltitudeReadoutProps> {
    private mda = 0;

    private altitude = 0;

    private isNegativeSub = Subject.create('hidden')

    private largeDigitClassList = Subject.create('');

    private smallDigitClassList = Subject.create('');

    private tensDigits1Value = Subject.create('');

    private tensDigits2Value = Subject.create('');

    private tensDigits3Value = Subject.create('');

    private tensDigits4Value = Subject.create('');

    private tensPosition = Subject.create('');

    private hundredsUpperValue = Subject.create('');

    private hundredsLowerValue = Subject.create('');

    private hundredsPosition = Subject.create('');

    private thousandsUpperValue = Subject.create('');

    private thousandsLowerValue = Subject.create('');

    private thousandsPosition = Subject.create('');

    private tenThousandsUpperValue = Subject.create('');

    private tenThousandsLowerValue = Subject.create('');

    private tenThousandsPosition = Subject.create('');

    onAfterRender(node: VNode): void {
        super.onAfterRender(node);

        const sub = this.props.bus.getSubscriber<PFDSimvars & Arinc429Values>();

        sub.on('mda').whenChanged().handle((mda) => {
            this.mda = mda;
            this.updateColor();
        });

        sub.on('altitudeAr').handle((altitude) => {
            const isNegative = altitude.value < 0;
            this.isNegativeSub.set(isNegative ? 'visible' : 'hidden');

            this.altitude = altitude.value;
            this.updateColor();

            const largeLetterSpacing = 7.1;
            const smallLetterSpacing = 4.53 / 2;

            const absalt = Math.abs(this.altitude);
            const round10000 = Math.trunc(absalt / 10000);
            const round1000 = Math.trunc(absalt / 1000);
            const round100 = Math.trunc(absalt / 100);

            const tenThousandsOffset = (absalt - round10000 * 10000) / 10000;
            this.tenThousandsPosition.set(`translate(0 ${tenThousandsOffset * largeLetterSpacing})`);

            const tenThousandsDigitHigh = round10000 + 1;
            const tenThousandsDigitLow = round10000;
            this.tenThousandsUpperValue.set(tenThousandsDigitHigh.toString());
            this.tenThousandsLowerValue.set(tenThousandsDigitLow.toString());

            const thousandsDigitOffset = (this.altitude - Math.trunc(this.altitude / 1000) * 1000) / 1000;
            this.thousandsPosition.set(`translate(0 ${thousandsDigitOffset * largeLetterSpacing})`);

            const thousandsDigitHigh = round1000 - round10000 * 10;
            const thousandsDigitLow = thousandsDigitHigh + 1 - Math.trunc((thousandsDigitHigh + 1) / 10) * 10;
            this.thousandsUpperValue.set(thousandsDigitLow.toString());
            this.thousandsLowerValue.set(thousandsDigitHigh.toString());

            const hundredsDigitOffset = (this.altitude - Math.trunc(this.altitude / 100) * 100) / 100;
            this.hundredsPosition.set(`translate(0 ${hundredsDigitOffset * largeLetterSpacing})`);

            const hundredsDigitLow = round100 - 10 * round1000;
            const hundredsDigitHigh = hundredsDigitLow + 1 - Math.trunc((hundredsDigitLow + 1) / 10) * 10;
            this.hundredsUpperValue.set(hundredsDigitHigh.toString());
            this.hundredsLowerValue.set(hundredsDigitLow.toString());

            const tenthDigitsOffset = (this.altitude - Math.trunc(this.altitude / 20) * 20) / 10;
            this.tensPosition.set(`translate(0 ${tenthDigitsOffset * smallLetterSpacing})`);

            const tenthDigitModulus = (Math.trunc(this.altitude / 20) * 2 - Math.trunc(this.altitude / 100) * 10) * 10;
            const tenthDigit2 = tenthDigitModulus;
            const tenthDigit3 = tenthDigitModulus + 20 - Math.trunc((tenthDigitModulus + 20) / 100) * 100;
            const tenthDigit4 = tenthDigitModulus + 40 - Math.trunc((tenthDigitModulus + 40) / 100) * 100;
            const tenthDigit1 = tenthDigitModulus - 20 + 100 - Math.trunc((tenthDigitModulus - 20 + 100) / 100) * 100;

            this.tensDigits1Value.set(tenthDigit1.toFixed(0).padStart(2, '0'));
            this.tensDigits2Value.set(tenthDigit2.toFixed(0).padStart(2, '0'));
            this.tensDigits3Value.set(tenthDigit3.toFixed(0).padStart(2, '0'));
            this.tensDigits4Value.set(tenthDigit4.toFixed(0).padStart(2, '0'));
        });
    }

    private updateColor() {
        const color = (this.mda !== 0 && this.altitude < this.mda) ? 'Amber' : 'Green';

        this.largeDigitClassList.set(`FontLargest MiddleAlign ${color}`);
        this.smallDigitClassList.set(`FontSmallest MiddleAlign ${color}`);
    }

    render(): VNode {
        return (
            <g id="AltReadoutGroup">
                <g transform={this.tenThousandsPosition}>
                    <text x="120.4772" y="76.179276" class={this.largeDigitClassList}>{this.tenThousandsUpperValue}</text>
                    <text x="120.47482" y="83.269829" class={this.largeDigitClassList}>{this.tenThousandsLowerValue}</text>
                </g>
                <g transform={this.thousandsPosition}>
                    <text x="125.0332" y="76.179688" class={this.largeDigitClassList}>{this.thousandsUpperValue}</text>
                    <text x="125.03112" y="83.269867" class={this.largeDigitClassList}>{this.thousandsLowerValue}</text>
                </g>
                <g transform={this.hundredsPosition}>
                    <text x="129.46671" y="76.177689" class={this.largeDigitClassList}>{this.hundredsUpperValue}</text>
                    <text x="129.4669" y="83.269379" class={this.largeDigitClassList}>{this.hundredsLowerValue}</text>
                </g>
                <g transform={this.tensPosition}>
                    <text x="135.52931" y="86.963669" class={this.smallDigitClassList}>{this.tensDigits1Value}</text>
                    <text x="135.52954" y="82.51902" class={this.smallDigitClassList}>{this.tensDigits2Value}</text>
                    <text x="135.53026" y="78.014465" class={this.smallDigitClassList}>{this.tensDigits3Value}</text>
                    <text x="135.53026" y="73.484421" class={this.smallDigitClassList}>{this.tensDigits4Value}</text>
                </g>
                <path id="AltReadoutReducedAccurMarks" class="NormalStroke Amber" style="display: none" d="m132.61 81.669h4.7345m-4.7345-1.6933h4.7345" />
                <path id="AltReadoutOutline" class="NormalStroke Yellow" d="m117.75 76.337h13.096v-2.671h8.8647v14.313h-8.8647v-2.671h-13.096" />

                <g id="AltNegativeText" class="FontLarge EndAlign" visibility={this.isNegativeSub}>
                    <text class="White" x="121.51714" y="77.956947">N</text>
                    <text class="White" x="121.7" y="83.251389">E</text>
                    <text class="White" x="121.63675" y="88.486031">G</text>
                </g>

            </g>
        );
    }
}
