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

export class VsDisplay extends DisplayComponent<{ x: number; y: number; bus: EventBus }> {
  private sub = this.props.bus.getSubscriber<FcuSimvars>();

  private vsValue = ConsumerSubject.create(this.sub.on('afsDisplayVsFpaValue'), 0);

  private vsDashes = ConsumerSubject.create(this.sub.on('afsDisplayVsFpaDashes'), false);

  private trkFpaMode = ConsumerSubject.create(this.sub.on('afsDisplayTrkFpaMode'), false);

  private lightsTest = ConsumerSubject.create(this.sub.on('lightsTest'), false);

  private fpaLabelSub = MappedSubject.create(
    ([trkFpa, lightsTest]) => trkFpa || lightsTest,
    this.trkFpaMode,
    this.lightsTest,
  );
  private vsLabelSub = MappedSubject.create(
    ([trkFpa, lightsTest]) => !trkFpa || lightsTest,
    this.trkFpaMode,
    this.lightsTest,
  );

  private vsValueSub = MappedSubject.create(
    ([lightsTest, vsDashes, vsValue, trkFpaMode]) => {
      const sign = Math.sign(vsValue) >= 0 ? '+' : '~';
      const absValue = Math.abs(vsValue);

      if (lightsTest) {
        return '+*.8.8.8';
      } else if (trkFpaMode && vsDashes) {
        return '~-.-';
      } else if (trkFpaMode && !vsDashes) {
        return `${sign}${absValue.toFixed(1)}`;
      } else if (vsDashes) {
        return '~----';
      } else {
        return `${sign}${Math.floor(absValue * 0.01)
          .toString()
          .padStart(2, '0')}oo`;
      }
    },
    this.lightsTest,
    this.vsDashes,
    this.vsValue,
    this.trkFpaMode,
  );

  public render(): VNode {
    return (
      <g transform={`translate(${this.props.x} ${this.props.y})`}>
        <text
          id="VS"
          x={512 * 0.71}
          y={204.8 * 0.2}
          text-anchor="end"
          class={{ Active: this.vsLabelSub, Inactive: this.vsLabelSub.map(SubscribableMapFunctions.not()) }}
        >
          V/S
        </text>
        <text
          id="FPA"
          x={512 * 0.5}
          y={204.8 * 0.2}
          text-anchor="end"
          class={{ Active: this.fpaLabelSub, Inactive: this.fpaLabelSub.map(SubscribableMapFunctions.not()) }}
        >
          FPA
        </text>
        <text id="Value" class="Value" x={512 * 0.11} y={204.8 * 0.97}>
          {this.vsValueSub}
        </text>
      </g>
    );
  }
}
