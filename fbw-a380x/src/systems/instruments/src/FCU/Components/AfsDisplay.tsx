import { ComponentProps, DisplayComponent, EventBus, FSComponent, VNode } from '@microsoft/msfs-sdk';
import { HdgDisplay } from './HdgDisplay';
import { SpdDisplay } from './SpdDisplay';
import { VsDisplay } from './VsDisplay';
import { AltDisplay } from './AltDisplay';

interface AfsDisplayProps extends ComponentProps {
  bus: EventBus;
}

export class AfsDisplay extends DisplayComponent<AfsDisplayProps> {
  public render(): VNode {
    return (
      <>
        <g>
          <SpdDisplay bus={this.props.bus} x={128} y={102.4} />

          <HdgDisplay bus={this.props.bus} x={768} y={102.4} />
        </g>

        <g transform="translate(3072 0)">
          <AltDisplay bus={this.props.bus} x={0} y={102.4} />

          <VsDisplay bus={this.props.bus} x={972.8} y={102.4} />
        </g>
      </>
    );
  }
}
