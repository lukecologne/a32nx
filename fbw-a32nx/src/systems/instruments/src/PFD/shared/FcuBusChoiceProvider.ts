import { getDisplayIndex } from '../PFD';
import { ConsumerSubject, EventBus, Instrument } from '@microsoft/msfs-sdk';
import { A32NXFcuBusEvents } from '@shared/publishers/A32NXFcuBusPublisher';

export interface FcuBusChoiceEvents {
  a32nx_fcu_eis_discrete_word_1: number;
  a32nx_fcu_eis_discrete_word_2: number;
  a32nx_fcu_eis_baro: number;
  a32nx_fcu_eis_baro_hpa: number;
}

export class FcuBusChoiceProvider implements Instrument {
  private readonly sub = this.bus.getSubscriber<A32NXFcuBusEvents>();

  private readonly eisDiscreteWord1 = ConsumerSubject.create(
    this.sub.on(getDisplayIndex() === 1 ? 'a32nx_fcu_eis_discrete_word_1_left' : 'a32nx_fcu_eis_discrete_word_1_right'),
    0,
  );

  private readonly eisDiscreteWord2 = ConsumerSubject.create(
    this.sub.on(getDisplayIndex() === 1 ? 'a32nx_fcu_eis_discrete_word_2_left' : 'a32nx_fcu_eis_discrete_word_2_right'),
    0,
  );

  private readonly eisBaro = ConsumerSubject.create(
    this.sub.on(getDisplayIndex() === 1 ? 'a32nx_fcu_eis_baro_left' : 'a32nx_fcu_eis_baro_right'),
    0,
  );

  private readonly eisBaroHpa = ConsumerSubject.create(
    this.sub.on(getDisplayIndex() === 1 ? 'a32nx_fcu_eis_baro_hpa_left' : 'a32nx_fcu_eis_baro_hpa_right'),
    0,
  );

  constructor(private readonly bus: EventBus) {}

  /** @inheritdoc */
  public init(): void {
    const publisher = this.bus.getPublisher<FcuBusChoiceEvents>();

    this.eisDiscreteWord1.sub((word) => publisher.pub('a32nx_fcu_eis_discrete_word_1', word), true);

    this.eisDiscreteWord2.sub((word) => publisher.pub('a32nx_fcu_eis_discrete_word_2', word), true);

    this.eisBaro.sub((word) => publisher.pub('a32nx_fcu_eis_baro', word), true);

    this.eisBaroHpa.sub((word) => publisher.pub('a32nx_fcu_eis_baro_hpa', word), true);
  }

  /** @inheritdoc */
  public onUpdate(): void {
    // noop
  }
}
