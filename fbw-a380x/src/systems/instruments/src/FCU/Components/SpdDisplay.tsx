import {
  ConsumerSubject,
  DisplayComponent,
  EventBus,
  FSComponent,
  MappedSubject,
  SubscribableMapFunctions,
  VNode,
} from '@microsoft/msfs-sdk';
import { FcuSimvars } from '../Publishers/FcuSimvarPublisher';

export class SpdDisplay extends DisplayComponent<{ x: number; y: number; bus: EventBus }> {
  private sub = this.props.bus.getSubscriber<FcuSimvars>();

  private value = ConsumerSubject.create(this.sub.on('afsDisplaySpdMachValue'), 0);

  private dashes = ConsumerSubject.create(this.sub.on('afsDisplaySpdMachDashes'), false);

  private machActive = ConsumerSubject.create(this.sub.on('afsDisplayMachMode'), false);

  private lightsTest = ConsumerSubject.create(this.sub.on('lightsTest'), false);

  private spdLabelSub = MappedSubject.create(
    ([machActive, lightsTest]) => !machActive || lightsTest,
    this.machActive,
    this.lightsTest,
  );
  private machLabelSub = MappedSubject.create(
    ([machActive, lightsTest]) => machActive || lightsTest,
    this.machActive,
    this.lightsTest,
  );

  private valueSub = MappedSubject.create(
    ([lightsTest, dashes, value, machActive]) => {
      if (lightsTest) {
        return '8.8.8';
      } else if (machActive && !dashes) {
        return value.toFixed(2);
      } else if (dashes) {
        return '---';
      } else {
        return Math.round(value).toString().padStart(3, '0');
      }
    },
    this.lightsTest,
    this.dashes,
    this.value,
    this.machActive,
  );

  public render(): VNode {
    return (
      <g transform={`translate(${this.props.x} ${this.props.y})`}>
        <text
          id="SPD"
          class={{ Active: this.spdLabelSub, Inactive: this.spdLabelSub.map(SubscribableMapFunctions.not()) }}
          x={384 * 0.47}
          y={204.8 * 0.2}
        >
          SPD
        </text>
        <text
          id="MACH"
          class={{ Active: this.machLabelSub, Inactive: this.machLabelSub.map(SubscribableMapFunctions.not()) }}
          x={0}
          y={204.8 * 0.2}
        >
          MACH
        </text>
        <text id="Value" class="Value" x={384 * 0.06} y={204.8 * 0.97}>
          {this.valueSub}
        </text>
        <text
          id="KNOTS"
          class={{ Active: this.dashes.map(SubscribableMapFunctions.not()), Inactive: this.dashes }}
          x={384 * 0.79}
          y={204.8 * 0.97}
        >
          KT
        </text>
      </g>
    );
  }
}
