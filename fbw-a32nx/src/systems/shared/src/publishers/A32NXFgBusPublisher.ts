// Copyright (c) 2024 FlyByWire Simulations
// SPDX-License-Identifier: GPL-3.0

import { EventBus, PublishPacer, SimVarPublisher, SimVarPublisherEntry, SimVarValueType } from '@microsoft/msfs-sdk';

export interface A32NXFgBusBaseEvents {
  a32nx_fg_pfd_selected_speed: number;
  a32nx_fg_presel_mach: number;
  a32nx_fg_presel_speed: number;
  a32nx_fg_roll_fd_command: number;
  a32nx_fg_pitch_fd_command: number;
  a32nx_fg_yaw_fd_command: number;
  a32nx_fg_discrete_word_5: number;
  a32nx_fg_discrete_word_4: number;
  a32nx_fg_altitude_constraint: number;
  a32nx_fg_ats_discrete_word: number;
  a32nx_fg_discrete_word_3: number;
  a32nx_fg_discrete_word_1: number;
  a32nx_fg_discrete_word_2: number;
  a32nx_fg_discrete_word_7: number;
  a32nx_fg_speed_margin_high: number;
  a32nx_fg_speed_margin_low: number;
}

type IndexedTopics = keyof A32NXFgBusBaseEvents;

type FgIndexedEventType<T extends string> = `${T}_${1 | 2}`;

type A32NXFgBusIndexedEvents = {
  [P in keyof Pick<A32NXFgBusBaseEvents, IndexedTopics> as FgIndexedEventType<P>]: A32NXFgBusBaseEvents[P];
};

interface A32NXFgBusPublisherEvents extends A32NXFgBusBaseEvents, A32NXFgBusIndexedEvents {}

/**
 * Events for A32NX FG bus local vars.
 */
export interface A32NXFgBusEvents extends Omit<A32NXFgBusBaseEvents, IndexedTopics>, A32NXFgBusIndexedEvents {}

/**
 * Publisher for A32NX FG bus local vars.
 */
export class A32NXFgBusPublisher extends SimVarPublisher<A32NXFgBusPublisherEvents> {
  /**
   * Create a publisher.
   * @param bus The EventBus to publish to
   * @param pacer An optional pacer to use to control the rate of publishing
   */
  public constructor(bus: EventBus, pacer?: PublishPacer<A32NXFgBusPublisherEvents>) {
    const simvars = new Map<keyof A32NXFgBusPublisherEvents, SimVarPublisherEntry<any>>([
      [
        'a32nx_fg_pfd_selected_speed',
        { name: 'L:A32NX_FMGC_#index#_PFD_SELECTED_SPEED', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_presel_mach',
        { name: 'L:A32NX_FMGC_#index#_PRESEL_MACH', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_presel_speed',
        { name: 'L:A32NX_FMGC_#index#_PRESEL_SPEED', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_roll_fd_command',
        { name: 'L:A32NX_FMGC_#index#_ROLL_FD_COMMAND', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_pitch_fd_command',
        { name: 'L:A32NX_FMGC_#index#_PITCH_FD_COMMAND', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_yaw_fd_command',
        { name: 'L:A32NX_FMGC_#index#_YAW_FD_COMMAND', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_discrete_word_5',
        { name: 'L:A32NX_FMGC_#index#_DISCRETE_WORD_5', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_discrete_word_4',
        { name: 'L:A32NX_FMGC_#index#_DISCRETE_WORD_4', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_altitude_constraint',
        { name: 'L:A32NX_FMGC_#index#_FM_ALTITUDE_CONSTRAINT', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_ats_discrete_word',
        { name: 'L:A32NX_FMGC_#index#_ATS_DISCRETE_WORD', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_discrete_word_3',
        { name: 'L:A32NX_FMGC_#index#_DISCRETE_WORD_3', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_discrete_word_1',
        { name: 'L:A32NX_FMGC_#index#_DISCRETE_WORD_1', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_discrete_word_2',
        { name: 'L:A32NX_FMGC_#index#_DISCRETE_WORD_2', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_discrete_word_7',
        { name: 'L:A32NX_FMGC_#index#_DISCRETE_WORD_7', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_speed_margin_high',
        { name: 'L:A32NX_FMGC_#index#_SPEED_MARGIN_HIGH', type: SimVarValueType.Enum, defaultIndex: null },
      ],
      [
        'a32nx_fg_speed_margin_low',
        { name: 'L:A32NX_FMGC_#index#_SPEED_MARGIN_LOW', type: SimVarValueType.Enum, defaultIndex: null },
      ],
    ]);

    super(simvars, bus, pacer);
  }
}
