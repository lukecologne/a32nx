import {
  ComponentProps,
  ConsumerSubject,
  DisplayComponent,
  EventBus,
  FSComponent,
  MappedSubject,
  VNode,
} from '@microsoft/msfs-sdk';
import { NavAidMode } from '@flybywiresim/fbw-sdk';
import { FcuSimvars } from '../Publishers/FcuSimvarPublisher';

interface EisDisplayProps extends ComponentProps {
  isCaptSide: boolean;
  bus: EventBus;
}

export class EisDisplay extends DisplayComponent<EisDisplayProps> {
  public render(): VNode {
    return (
      <g>
        <BaroRefDisplay
          isCaptSide={this.props.isCaptSide}
          x={this.props.isCaptSide ? 3072 : 4096}
          y={921.6}
          bus={this.props.bus}
        />
        <NdDataDisplay
          bus={this.props.bus}
          x={150}
          y={this.props.isCaptSide ? 875 : 1450}
          index={this.props.isCaptSide ? 0 : 1}
        />
      </g>
    );
  }
}

interface BaroRefDisplayProps extends ComponentProps {
  isCaptSide: boolean;
  x: number;
  y: number;
  bus: EventBus;
}

class BaroRefDisplay extends DisplayComponent<BaroRefDisplayProps> {
  private sub = this.props.bus.getSubscriber<FcuSimvars>();

  private baroValueMode = ConsumerSubject.create(null, 0);

  private baroValue = ConsumerSubject.create(null, 0);

  private baroMode = ConsumerSubject.create(null, 0);

  private lightsTest = ConsumerSubject.create(this.sub.on('lightsTest'), false);

  private baroValueSub = MappedSubject.create(
    ([lightsTest, baroValueMode, baroValue]) => {
      if (lightsTest) {
        return '88.88';
      } else if (baroValueMode === 0) {
        return 'Std';
      } else if (baroValueMode === 1) {
        return Math.round(baroValue).toString().padStart(4, '0');
      } else {
        return baroValue.toFixed(2);
      }
    },
    this.lightsTest,
    this.baroValueMode,
    this.baroValue,
  );

  private qnhLabelSub = MappedSubject.create(
    ([lightsTest, baroMode]) => {
      if (lightsTest) {
        return 'Active';
      } else if (baroMode === 0) {
        return 'Inactive';
      } else if (baroMode === 1) {
        return 'Active';
      } else {
        return 'Inactive';
      }
    },
    this.lightsTest,
    this.baroMode,
  );

  private qfeLabelSub = MappedSubject.create(
    ([lightsTest, baroMode]) => {
      if (lightsTest) {
        return 'Active';
      } else if (baroMode === 0) {
        return 'Inactive';
      } else if (baroMode === 1) {
        return 'Inactive';
      } else {
        return 'Active';
      }
    },
    this.lightsTest,
    this.baroMode,
  );

  public onAfterRender(node: VNode): void {
    super.onAfterRender(node);

    const sub = this.props.bus.getSubscriber<FcuSimvars>();

    this.baroValueMode.setConsumer(sub.on(`eisDisplay${this.props.isCaptSide ? 'Left' : 'Right'}BaroValueMode`));

    this.baroValue.setConsumer(sub.on(`eisDisplay${this.props.isCaptSide ? 'Left' : 'Right'}BaroValue`));

    this.baroMode.setConsumer(sub.on(`eisDisplay${this.props.isCaptSide ? 'Left' : 'Right'}BaroMode`));
  }

  public render(): VNode {
    return (
      <g transform={`translate(${this.props.x} ${this.props.y})`}>
        <text id="QFE" class={this.qfeLabelSub} x={345.6 * 0.16} y={217.6 * 0.23}>
          QFE
        </text>
        <text id="QNH" class={this.qnhLabelSub} x={345.6 * 0.06} y={217.6 * 0.23} text-anchor="end">
          QNH
        </text>
        <text id="Value" class="Value" x={345.6 * 0.04} y={217.6 * 0.95}>
          {this.baroValueSub}
        </text>
      </g>
    );
  }
}

interface NdDataDisplayProps {
  readonly bus: EventBus;
  readonly index: number;
  readonly x: number;
  readonly y: number;
}

class NdDataDisplay extends DisplayComponent<NdDataDisplayProps> {
  private static readonly NAVAID_1_IMAGES: Record<NavAidMode, string> = {
    [NavAidMode.Off]: '/Images/fbw-a380x/fcu/POINTER1.png',
    [NavAidMode.VOR]: '/Images/fbw-a380x/fcu/VOR1.png',
    [NavAidMode.ADF]: '/Images/fbw-a380x/fcu/ADF1.png',
  };
  private static readonly NAVAID_2_IMAGES: Record<NavAidMode, string> = {
    [NavAidMode.Off]: '/Images/fbw-a380x/fcu/POINTER2.png',
    [NavAidMode.VOR]: '/Images/fbw-a380x/fcu/VOR2.png',
    [NavAidMode.ADF]: '/Images/fbw-a380x/fcu/ADF2.png',
  };

  private readonly sub = this.props.bus.getSubscriber<FcuSimvars>();

  private readonly navaidMode1 = ConsumerSubject.create(
    this.sub.on(this.props.index === 2 ? 'eisDisplayRightNavaid1Mode' : 'eisDisplayLeftNavaid1Mode'),
    NavAidMode.Off,
  );
  private readonly navaidMode2 = ConsumerSubject.create(
    this.sub.on(this.props.index === 2 ? 'eisDisplayRightNavaid2Mode' : 'eisDisplayLeftNavaid2Mode'),
    NavAidMode.Off,
  );

  private readonly isLightTestActive = ConsumerSubject.create(this.sub.on('lightsTest'), false);

  render(): VNode | null {
    return (
      <g transform={`translate(${this.props.x} ${this.props.y})`}>
        <image x={0} y={0} width={310} xlinkHref="/Images/fbw-a380x/fcu/CSTR.png" />
        <image x={445} y={0} width={310} xlinkHref="/Images/fbw-a380x/fcu/WPT.png" />
        <image x={920} y={0} width={310} xlinkHref="/Images/fbw-a380x/fcu/VORD.png" />
        <image x={1395} y={0} width={310} xlinkHref="/Images/fbw-a380x/fcu/NDB.png" />
        <image x={1970} y={0} width={310} xlinkHref="/Images/fbw-a380x/fcu/ARPT.png" />

        <image x={0} y={275} width={310} xlinkHref={this.navaidMode1.map((v) => NdDataDisplay.NAVAID_1_IMAGES[v])} />
        <image X={445} y={275} width={310} xlinkHref="/Images/fbw-a380x/fcu/WX.png" />
        <image X={920} y={275} width={310} xlinkHref="/Images/fbw-a380x/fcu/TERR.png" />
        <image X={1395} y={275} width={310} xlinkHref="/Images/fbw-a380x/fcu/TRAF.png" />
        <image X={1870} y={275} width={310} xlinkHref={this.navaidMode2.map((v) => NdDataDisplay.NAVAID_2_IMAGES[v])} />
      </g>
    );
  }
}
