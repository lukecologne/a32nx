import { ConsumerSubject, DisplayComponent, EventBus, FSComponent, MappedSubject, VNode } from '@microsoft/msfs-sdk';
import { FcuSimvars } from '../Publishers/FcuSimvarPublisher';

export class AltDisplay extends DisplayComponent<{ x: number; y: number; bus: EventBus }> {
  private sub = this.props.bus.getSubscriber<FcuSimvars>();

  private altValue = ConsumerSubject.create(this.sub.on('afsDisplayAltValue'), 0);

  private lightsTest = ConsumerSubject.create(this.sub.on('lightsTest'), false);

  private altValueSub = MappedSubject.create(
    ([lightsTest, altValue]) => {
      if (lightsTest) {
        return '+*.8.8.8';
      } else {
        return Math.round(altValue).toString().padStart(5, '0');
      }
    },
    this.lightsTest,
    this.altValue,
  );

  public render(): VNode {
    return (
      <g transform={`translate(${this.props.x} ${this.props.y})`}>
        <text id="ALT" class="Active" x={640 * 0.31} y={204.8 * 0.2}>
          ALT
        </text>
        <text id="Value" class="Value" x={640 * 0.04} y={204.8 * 0.97}>
          {this.altValueSub}
        </text>
      </g>
    );
  }
}
