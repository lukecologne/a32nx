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

export class HdgDisplay extends DisplayComponent<{ x: number; y: number; bus: EventBus }> {
  private sub = this.props.bus.getSubscriber<FcuSimvars>();

  private value = ConsumerSubject.create(this.sub.on('afsDisplayHdgTrkValue'), 0);

  private dashes = ConsumerSubject.create(this.sub.on('afsDisplayHdgTrkDashes'), false);

  private trkFpaMode = ConsumerSubject.create(this.sub.on('afsDisplayTrkFpaMode'), false);

  private trueActive = ConsumerSubject.create(this.sub.on('afsDisplayTrkFpaMode'), false);

  private lightsTest = ConsumerSubject.create(this.sub.on('lightsTest'), false);

  private trkLabelSub = MappedSubject.create(
    ([trkFpa, lightsTest]) => trkFpa || lightsTest,
    this.trkFpaMode,
    this.lightsTest,
  );
  private hdgLabelSub = MappedSubject.create(
    ([trkFpa, lightsTest]) => !trkFpa || lightsTest,
    this.trkFpaMode,
    this.lightsTest,
  );

  private valueSub = MappedSubject.create(
    ([lightsTest, dashes, value]) => {
      if (lightsTest) {
        return '8.8.8';
      } else if (dashes) {
        return '---';
      } else {
        return Math.round(value).toString().padStart(3, '0');
      }
    },
    this.lightsTest,
    this.dashes,
    this.value,
  );

  public render(): VNode {
    return (
      <g transform={`translate(${this.props.x} ${this.props.y})`}>
        <text
          id="HDG"
          class={{ Active: this.hdgLabelSub, Inactive: this.hdgLabelSub.map(SubscribableMapFunctions.not()) }}
          x={640 * 0.48}
          y={204.8 * 0.2}
        >
          HDG
        </text>
        <text
          id="TRK"
          class={{ Active: this.trkLabelSub, Inactive: this.trkLabelSub.map(SubscribableMapFunctions.not()) }}
          x={640 * 0.68}
          y={204.8 * 0.2}
        >
          TRK
        </text>
        <text
          id="TRUE"
          class={{ Active: this.trueActive, Inactive: this.trueActive.map(SubscribableMapFunctions.not()) }}
          x={640 * 0.23}
          y={204.8 * 0.97}
        >
          TRUE
        </text>
        <text id="Value" class="Value" x={640 * 0.47} y={204.8 * 0.97}>
          {this.valueSub}
        </text>
        <text
          id="Degrees"
          class={{ Active: this.dashes.map(SubscribableMapFunctions.not()), Inactive: this.dashes }}
          x={640 * 0.89}
          y={204.8 * 0.97}
        >
          &#176;
        </text>
      </g>
    );
  }
}
