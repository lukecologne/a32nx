// Copyright (c) 2021-2023 FlyByWire Simulations
//
// SPDX-License-Identifier: GPL-3.0

import { ConsumerSubject, Instrument, MappedSubject } from '@microsoft/msfs-sdk';
import { getDisplayIndex } from '../PFD';
import { Arinc429LocalVarConsumerSubject, ArincEventBus } from '@flybywiresim/fbw-sdk';
import { A32NXFgBusBaseEvents, A32NXFgBusEvents } from '@shared/publishers/A32NXFgBusPublisher';
import { FcuBusChoiceEvents } from './FcuBusChoiceProvider';

export type FgBusChoiceEvents = A32NXFgBusBaseEvents & {
  fd_engaged: boolean;
};

const fgSubjectsByKey = {
  a32nx_fg_pfd_selected_speed: ConsumerSubject.create(null, 0),
  a32nx_fg_presel_mach: ConsumerSubject.create(null, 0),
  a32nx_fg_presel_speed: ConsumerSubject.create(null, 0),
  a32nx_fg_roll_fd_command: ConsumerSubject.create(null, 0),
  a32nx_fg_pitch_fd_command: ConsumerSubject.create(null, 0),
  a32nx_fg_yaw_fd_command: ConsumerSubject.create(null, 0),
  a32nx_fg_discrete_word_5: ConsumerSubject.create(null, 0),
  a32nx_fg_discrete_word_4: ConsumerSubject.create(null, 0),
  a32nx_fg_altitude_constraint: ConsumerSubject.create(null, 0),
  a32nx_fg_ats_discrete_word: ConsumerSubject.create(null, 0),
  a32nx_fg_discrete_word_3: ConsumerSubject.create(null, 0),
  a32nx_fg_discrete_word_1: ConsumerSubject.create(null, 0),
  a32nx_fg_discrete_word_2: ConsumerSubject.create(null, 0),
  a32nx_fg_discrete_word_7: ConsumerSubject.create(null, 0),
  a32nx_fg_speed_margin_high: ConsumerSubject.create(null, 0),
  a32nx_fg_speed_margin_low: ConsumerSubject.create(null, 0),
} satisfies Record<keyof A32NXFgBusBaseEvents, ConsumerSubject<number>>;

export class FgBusProvider implements Instrument {
  private readonly sub = this.bus.getSubscriber<FcuBusChoiceEvents & A32NXFgBusEvents>();

  private readonly fcuEisDiscreteWord2 = Arinc429LocalVarConsumerSubject.create(
    this.sub.on('a32nx_fcu_eis_discrete_word_2'),
  );

  private readonly fmgc1DiscreteWord4 = Arinc429LocalVarConsumerSubject.create(
    this.sub.on('a32nx_fg_discrete_word_4_1'),
  );

  private readonly fmgc2DiscreteWord4 = Arinc429LocalVarConsumerSubject.create(
    this.sub.on('a32nx_fg_discrete_word_4_2'),
  );

  private readonly fmgc1AtsDiscreteWord = Arinc429LocalVarConsumerSubject.create(
    this.sub.on('a32nx_fg_ats_discrete_word_1'),
  );

  private readonly fmgc2AtsDiscreteWord = Arinc429LocalVarConsumerSubject.create(
    this.sub.on('a32nx_fg_ats_discrete_word_2'),
  );

  private readonly fg1ForFlightDirectorSelected = MappedSubject.create(
    ([fcuEisDiscreteWord2, fmgc1DiscreteWord4, fmgc2DiscreteWord4]) => {
      const side2 = getDisplayIndex() === 2;

      const fd1Engaged = fmgc1DiscreteWord4.bitValueOr(13, false);
      const fd2Engaged = fmgc2DiscreteWord4.bitValueOr(13, false);
      const fdOwnSelectedOn = !fcuEisDiscreteWord2.bitValueOr(23, false);

      const ownFdEngaged = side2 ? fd2Engaged : fd1Engaged;
      const oppFdEngaged = side2 ? fd1Engaged : fd2Engaged;

      const ownFdEngagedAndOn = ownFdEngaged && fdOwnSelectedOn;
      const oppFdEngagedAndOn = !ownFdEngaged && oppFdEngaged && fdOwnSelectedOn;

      return (
        (!side2 && !ownFdEngagedAndOn && !oppFdEngagedAndOn) ||
        (!side2 && ownFdEngagedAndOn) ||
        (side2 && oppFdEngagedAndOn)
      );
    },
    this.fcuEisDiscreteWord2,
    this.fmgc1DiscreteWord4,
    this.fmgc2DiscreteWord4,
  );

  private readonly fdEngaged = MappedSubject.create(
    ([fg1ForFlightDirectorSelected, fmgc1DiscreteWord4, fmgc2DiscreteWord4]) => {
      const fd1Engaged = fmgc1DiscreteWord4.bitValueOr(13, false);
      const fd2Engaged = fmgc2DiscreteWord4.bitValueOr(13, false);

      return fg1ForFlightDirectorSelected ? fd1Engaged : fd2Engaged;
    },
    this.fg1ForFlightDirectorSelected,
    this.fmgc1DiscreteWord4,
    this.fmgc2DiscreteWord4,
  );

  private readonly fg1Selected = MappedSubject.create(
    ([fmgc1DiscreteWord4, fmgc2DiscreteWord4, fmgc1AtsDiscreteWord, fmgc2AtsDiscreteWord]) => {
      const side2 = getDisplayIndex() === 2;

      const ap1Engaged = fmgc1DiscreteWord4.bitValueOr(12, false);
      const fd1Engaged = fmgc1DiscreteWord4.bitValueOr(13, false);
      const ap2Engaged = fmgc2DiscreteWord4.bitValueOr(12, false);
      const fd2Engaged = fmgc2DiscreteWord4.bitValueOr(13, false);

      const fg1Inop =
        fmgc1AtsDiscreteWord.bitValueOr(24, false) ||
        fmgc1AtsDiscreteWord.isFailureWarning() ||
        fmgc1DiscreteWord4.isFailureWarning();
      const fg2Inop =
        fmgc2AtsDiscreteWord.bitValueOr(24, false) ||
        fmgc2AtsDiscreteWord.isFailureWarning() ||
        fmgc2DiscreteWord4.isFailureWarning();

      const apCondition = !side2 ? ap1Engaged : ap1Engaged && !ap2Engaged;
      const fdCondition = !(ap1Engaged || ap2Engaged) && (!side2 ? fd1Engaged : fd1Engaged && !fd2Engaged);
      const inopCondition = !(ap1Engaged || ap2Engaged) && !(fd1Engaged || fd2Engaged) && (!fg1Inop || fg2Inop);

      return apCondition || fdCondition || inopCondition;
    },
    this.fmgc1DiscreteWord4,
    this.fmgc2DiscreteWord4,
    this.fmgc1AtsDiscreteWord,
    this.fmgc2AtsDiscreteWord,
  );

  private readonly fgSubjects = new Map(
    Object.entries(fgSubjectsByKey) as [keyof A32NXFgBusBaseEvents, ConsumerSubject<number>][],
  );

  constructor(private readonly bus: ArincEventBus) {}

  /** @inheritdoc */
  public init() {
    const publisher = this.bus.getPublisher<FgBusChoiceEvents>();

    this.fdEngaged.sub((fdEngaged) => {
      publisher.pub('fd_engaged', fdEngaged);
    }, true);

    this.fg1Selected.sub((fg1Selected) => {
      for (const [key, value] of this.fgSubjects) {
        if (
          key === 'a32nx_fg_pitch_fd_command' ||
          key === 'a32nx_fg_roll_fd_command' ||
          key === 'a32nx_fg_yaw_fd_command'
        ) {
          continue;
        }

        const index = fg1Selected ? 1 : 2;
        value.setConsumer(this.sub.on(`${key}_${index}`));
      }
    }, true);

    this.fg1ForFlightDirectorSelected.sub((fg1Selected) => {
      for (const [key, value] of this.fgSubjects) {
        if (
          key !== 'a32nx_fg_pitch_fd_command' &&
          key !== 'a32nx_fg_roll_fd_command' &&
          key !== 'a32nx_fg_yaw_fd_command'
        ) {
          continue;
        }

        const index = fg1Selected ? 1 : 2;
        value.setConsumer(this.sub.on(`${key}_${index}`));
      }
    }, true);

    for (const [key, value] of this.fgSubjects) {
      value.sub((word) => {
        publisher.pub(key, word);
      }, true);
    }
  }

  /** @inheritdoc */
  onUpdate(): void {}
}
