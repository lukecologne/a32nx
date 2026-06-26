import {
  ComponentProps,
  ConsumerSubject,
  DisplayComponent,
  EventBus,
  FSComponent,
  SubscribableMapFunctions,
  VNode,
} from '@microsoft/msfs-sdk';
import { EisDisplay } from './Components/EisDisplay';
import { AfsDisplay } from './Components/AfsDisplay';
import { FcuSimvars } from './Publishers/FcuSimvarPublisher';

import './style.scss';

interface FCUProps extends ComponentProps {
  bus: EventBus;
}

export class FCUComponent extends DisplayComponent<FCUProps> {
  private readonly sub = this.props.bus.getSubscriber<FcuSimvars>();

  private readonly fcuHealthy = ConsumerSubject.create(this.sub.on('fcuHealthy'), false);

  render(): VNode {
    return (
      <>
        <svg
          class={{
            'fcu-svg': true,
            Hide: this.fcuHealthy.map(SubscribableMapFunctions.not()),
          }}
          version="1.1"
          viewBox="0 0 2560 1280"
          xmlns="http://www.w3.org/2000/svg"
        >
          <AfsDisplay bus={this.props.bus} />
          <EisDisplay isCaptSide bus={this.props.bus} />
          <EisDisplay isCaptSide={false} bus={this.props.bus} />
        </svg>
      </>
    );
  }
}
