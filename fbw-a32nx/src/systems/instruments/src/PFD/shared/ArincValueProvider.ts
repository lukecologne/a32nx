// Copyright (c) 2021-2023 FlyByWire Simulations
//
// SPDX-License-Identifier: GPL-3.0

import { Publisher } from '@microsoft/msfs-sdk';
import { getDisplayIndex } from 'instruments/src/PFD/PFD';
import { Arinc429Word } from '@flybywiresim/fbw-sdk';
import { PFDSimvars } from './PFDSimvarPublisher';
import { ArincEventBus } from '../../MsfsAvionicsCommon/ArincEventBus';

export interface Arinc429Values {
    pitchAr: Arinc429Word;
    rollAr: Arinc429Word;
    altitudeAr: Arinc429Word;
    magTrack: Arinc429Word;
    magHeading: Arinc429Word;
    speedAr: Arinc429Word;
    machAr: Arinc429Word;
    vs: Arinc429Word;
    gs: Arinc429Word;
    chosenRa: Arinc429Word;
    fpa: Arinc429Word;
    da: Arinc429Word;
    landingElevation: Arinc429Word;
    latAcc: Arinc429Word;
    fcdcDiscreteWord1: Arinc429Word;
    fcdc1DiscreteWord1: Arinc429Word;
    fcdc2DiscreteWord1: Arinc429Word;
    fcdc1DiscreteWord2: Arinc429Word;
    fcdc2DiscreteWord2: Arinc429Word;
    fcdcCaptPitchCommand: Arinc429Word;
    fcdcFoPitchCommand: Arinc429Word;
    fcdcCaptRollCommand: Arinc429Word;
    fcdcFoRollCommand: Arinc429Word;
    facToUse: number;
    vAlphaMax: Arinc429Word;
    vAlphaProt: Arinc429Word;
    vStallWarn: Arinc429Word;
    vMax: Arinc429Word;
    vFeNext: Arinc429Word;
    vCTrend: Arinc429Word;
    vMan: Arinc429Word;
    v4: Arinc429Word;
    v3: Arinc429Word;
    vLs: Arinc429Word;
    estimatedBeta: Arinc429Word;
    betaTarget: Arinc429Word;
    irMaintWord: Arinc429Word;
    trueHeading: Arinc429Word;
    trueTrack: Arinc429Word;
    mdaAr: Arinc429Word;
    dhAr: Arinc429Word;
    fcuSelectedHeading: Arinc429Word;
    fcuSelectedAltitude: Arinc429Word;
    fcuSelectedAirspeed: Arinc429Word;
    fcuSelectedVerticalSpeed: Arinc429Word;
    fcuSelectedTrack: Arinc429Word;
    fcuSelectedFpa: Arinc429Word;
    fcuAtsDiscreteWord: Arinc429Word;
    fcuAtsFmaDiscreteWord: Arinc429Word;
    fcuEisDiscreteWord1: Arinc429Word;
    fcuEisDiscreteWord2: Arinc429Word;
    fcuEisBaro: Arinc429Word;
    fcuEisBaroHpa: Arinc429Word;
    fcuDiscreteWord1: Arinc429Word;
    fcuDiscreteWord2: Arinc429Word;
    fdEngaged: boolean;
    pfdSelectedSpeed: Arinc429Word;
    rollFdCommand: Arinc429Word;
    pitchFdCommand: Arinc429Word;
    yawFdCommand: Arinc429Word;
    fmgcDiscreteWord5: Arinc429Word;
    fmgc1DiscreteWord4: Arinc429Word;
    fmgc2DiscreteWord4: Arinc429Word;
    fmgcDiscreteWord4: Arinc429Word;
    fmgcFmAltitudeConstraint: Arinc429Word;
    fmgcDiscreteWord3: Arinc429Word;
    fmgcDiscreteWord1: Arinc429Word;
    fmgcDiscreteWord2: Arinc429Word;
    fmgcDiscreteWord7: Arinc429Word;
}
export class ArincValueProvider {
    private roll = new Arinc429Word(0);

    private pitch = new Arinc429Word(0);

    private magTrack = new Arinc429Word(0);

    private heading = new Arinc429Word(0);

    private speed = new Arinc429Word(0);

    private altitude = new Arinc429Word(0);

    private mach = new Arinc429Word(0);

    private vsInert = new Arinc429Word(0);

    private vsBaro = new Arinc429Word(0);

    private groundSpeed = new Arinc429Word(0);

    private ownRadioAltitude = new Arinc429Word(0);

    private oppRadioAltitude = new Arinc429Word(0);

    private fpa = new Arinc429Word(0);

    private da = new Arinc429Word(0);

    private ownLandingElevation = new Arinc429Word(0);

    private oppLandingElevation = new Arinc429Word(0);

    private latAcc = new Arinc429Word(0);

    private fcdc1DiscreteWord1 = new Arinc429Word(0);

    private fcdc2DiscreteWord1 = new Arinc429Word(0);

    private fcdc1DiscreteWord2 = new Arinc429Word(0);

    private fcdc2DiscreteWord2 = new Arinc429Word(0);

    private fcdcToUse = 0;

    private fac1Healthy = false;

    private fac2Healthy = false;

    private fac1VAlphaMax = new Arinc429Word(0);

    private fac2VAlphaMax = new Arinc429Word(0);

    private facToUse = 0;

    private fcuEisDiscreteWord2 = new Arinc429Word(0);

    private fmgc1DiscreteWord4 = new Arinc429Word(0);

    private fmgc2DiscreteWord4 = new Arinc429Word(0);

    private fmgc1AtsDiscreteWord = new Arinc429Word(0);

    private fmgc2AtsDiscreteWord = new Arinc429Word(0);

    private fg1ForFlightDirectorSelected = false;

    private fg1Selected = false;

    constructor(private readonly bus: ArincEventBus) {

    }

    public init() {
        const publisher = this.bus.getPublisher<Arinc429Values>();
        const subscriber = this.bus.getSubscriber<PFDSimvars>();

        subscriber.on('pitch').handle((p) => {
            this.pitch = new Arinc429Word(p);
            publisher.pub('pitchAr', this.pitch);
        });
        subscriber.on('roll').handle((p) => {
            this.roll = new Arinc429Word(p);
            publisher.pub('rollAr', this.roll);
        });
        subscriber.on('magTrackRaw').handle((gt) => {
            this.magTrack = new Arinc429Word(gt);
            publisher.pub('magTrack', this.magTrack);
        });
        subscriber.on('magHeadingRaw').handle((h) => {
            this.heading = new Arinc429Word(h);
            publisher.pub('magHeading', this.heading);
        });

        subscriber.on('speed').handle((s) => {
            this.speed = new Arinc429Word(s);
            publisher.pub('speedAr', this.speed);
        });

        subscriber.on('baroCorrectedAltitude').handle((a) => {
            this.altitude = new Arinc429Word(a);
            publisher.pub('altitudeAr', this.altitude);
        });

        subscriber.on('mach').handle((m) => {
            this.mach = new Arinc429Word(m);
            publisher.pub('machAr', this.mach);
        });

        subscriber.on('vsInert').handle((ivs) => {
            this.vsInert = new Arinc429Word(ivs);

            if (this.vsInert.isNormalOperation()) {
                publisher.pub('vs', this.vsInert);
            }
        });

        subscriber.on('vsBaro').handle((vsb) => {
            this.vsBaro = new Arinc429Word(vsb);
            if (!this.vsInert.isNormalOperation()) {
                publisher.pub('vs', this.vsBaro);
            }
        });

        subscriber.on('groundSpeed').handle((gs) => {
            this.groundSpeed = new Arinc429Word(gs);
            publisher.pub('gs', this.groundSpeed);
        });

        subscriber.on('radioAltitude1').handle((ra) => {
            if (getDisplayIndex() === 1) {
                this.ownRadioAltitude = new Arinc429Word(ra);
            } else {
                this.oppRadioAltitude = new Arinc429Word(ra);
            }
            this.determineAndPublishChosenRadioAltitude(publisher);
        });

        subscriber.on('radioAltitude2').handle((ra) => {
            if (getDisplayIndex() === 2) {
                this.ownRadioAltitude = new Arinc429Word(ra);
            } else {
                this.oppRadioAltitude = new Arinc429Word(ra);
            }
            this.determineAndPublishChosenRadioAltitude(publisher);
        });

        subscriber.on('fpaRaw').handle((fpa) => {
            this.fpa = new Arinc429Word(fpa);
            publisher.pub('fpa', this.fpa);
        });

        subscriber.on('daRaw').handle((da) => {
            this.da = new Arinc429Word(da);
            publisher.pub('da', this.da);
        });

        subscriber.on('landingElevation1Raw').handle((elevation) => {
            if (getDisplayIndex() === 1) {
                this.ownLandingElevation = new Arinc429Word(elevation);
            } else {
                this.oppLandingElevation = new Arinc429Word(elevation);
            }
            this.determineAndPublishChosenLandingElevation(publisher);
        });

        subscriber.on('landingElevation2Raw').handle((elevation) => {
            if (getDisplayIndex() === 1) {
                this.ownLandingElevation = new Arinc429Word(elevation);
            } else {
                this.oppLandingElevation = new Arinc429Word(elevation);
            }
            this.determineAndPublishChosenLandingElevation(publisher);
        });

        subscriber.on('latAccRaw').handle((latAcc) => {
            this.latAcc = new Arinc429Word(latAcc);
            publisher.pub('latAcc', this.latAcc);
        });

        subscriber.on('fcdc1DiscreteWord1Raw').handle((discreteWord1) => {
            this.fcdc1DiscreteWord1 = new Arinc429Word(discreteWord1);
            this.fcdcToUse = this.determineFcdcToUse();
            publisher.pub('fcdc1DiscreteWord1', this.fcdc1DiscreteWord1);
            if (this.fcdcToUse === 1) {
                publisher.pub('fcdcDiscreteWord1', this.fcdc1DiscreteWord1);
            }
        });

        subscriber.on('fcdc2DiscreteWord1Raw').handle((discreteWord1) => {
            this.fcdc2DiscreteWord1 = new Arinc429Word(discreteWord1);
            this.fcdcToUse = this.determineFcdcToUse();
            publisher.pub('fcdc2DiscreteWord1', this.fcdc2DiscreteWord1);
            if (this.fcdcToUse === 2) {
                publisher.pub('fcdcDiscreteWord1', this.fcdc2DiscreteWord1);
            }
        });

        subscriber.on('fcdc1DiscreteWord2Raw').handle((discreteWord2) => {
            this.fcdc1DiscreteWord2 = new Arinc429Word(discreteWord2);
            publisher.pub('fcdc1DiscreteWord2', this.fcdc1DiscreteWord2);
        });

        subscriber.on('fcdc2DiscreteWord2Raw').handle((discreteWord2) => {
            this.fcdc2DiscreteWord2 = new Arinc429Word(discreteWord2);
            publisher.pub('fcdc2DiscreteWord2', this.fcdc2DiscreteWord2);
        });

        subscriber.on('fcdc1CaptPitchCommandRaw').handle((word) => {
            if (this.fcdcToUse === 1) {
                publisher.pub('fcdcCaptPitchCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fcdc2CaptPitchCommandRaw').handle((word) => {
            if (this.fcdcToUse === 2) {
                publisher.pub('fcdcCaptPitchCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fcdc1FoPitchCommandRaw').handle((word) => {
            if (this.fcdcToUse === 1) {
                publisher.pub('fcdcFoPitchCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fcdc2FoPitchCommandRaw').handle((word) => {
            if (this.fcdcToUse === 2) {
                publisher.pub('fcdcFoPitchCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fcdc1CaptRollCommandRaw').handle((word) => {
            if (this.fcdcToUse === 1) {
                publisher.pub('fcdcCaptRollCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fcdc2CaptRollCommandRaw').handle((word) => {
            if (this.fcdcToUse === 2) {
                publisher.pub('fcdcCaptRollCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fcdc1FoRollCommandRaw').handle((word) => {
            if (this.fcdcToUse === 1) {
                publisher.pub('fcdcFoRollCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fcdc2FoRollCommandRaw').handle((word) => {
            if (this.fcdcToUse === 2) {
                publisher.pub('fcdcFoRollCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1Healthy').handle((val) => {
            this.fac1Healthy = val;
            this.determineFacToUse(publisher);
        });

        subscriber.on('fac2Healthy').handle((val) => {
            this.fac2Healthy = val;
            this.determineFacToUse(publisher);
        });

        subscriber.on('fac1VAlphaMaxRaw').handle((word) => {
            this.fac1VAlphaMax = new Arinc429Word(word);
            this.determineFacToUse(publisher);
            if (this.facToUse === 1) {
                publisher.pub('vAlphaMax', this.fac1VAlphaMax);
            } else if (this.facToUse === 0) {
                publisher.pub('vAlphaMax', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VAlphaMaxRaw').handle((word) => {
            this.fac2VAlphaMax = new Arinc429Word(word);
            this.determineFacToUse(publisher);
            if (this.facToUse === 2) {
                publisher.pub('vAlphaMax', this.fac2VAlphaMax);
            }
        });

        subscriber.on('fac1VAlphaProtRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('vAlphaProt', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('vAlphaProt', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VAlphaProtRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('vAlphaProt', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1VStallWarnRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('vStallWarn', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('vStallWarn', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VStallWarnRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('vStallWarn', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1VMaxRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('vMax', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('vMax', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VMaxRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('vMax', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1VFeNextRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('vFeNext', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('vFeNext', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VFeNextRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('vFeNext', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1VCTrendRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('vCTrend', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('vCTrend', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VCTrendRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('vCTrend', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1VManRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('vMan', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('vMan', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VManRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('vMan', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1V4Raw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('v4', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('v4', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2V4Raw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('v4', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1V3Raw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('v3', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('v3', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2V3Raw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('v3', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1VLsRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('vLs', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('vLs', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2VLsRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('vLs', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1EstimatedBetaRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('estimatedBeta', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('estimatedBeta', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2EstimatedBetaRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('estimatedBeta', new Arinc429Word(word));
            }
        });

        subscriber.on('fac1BetaTargetRaw').handle((word) => {
            if (this.facToUse === 1) {
                publisher.pub('betaTarget', new Arinc429Word(word));
            } else if (this.facToUse === 0) {
                publisher.pub('betaTarget', new Arinc429Word(0));
            }
        });

        subscriber.on('fac2BetaTargetRaw').handle((word) => {
            if (this.facToUse === 2) {
                publisher.pub('betaTarget', new Arinc429Word(word));
            }
        });

        subscriber.on('irMaintWordRaw').handle((word) => {
            publisher.pub('irMaintWord', new Arinc429Word(word));
        });

        subscriber.on('trueHeadingRaw').handle((word) => {
            publisher.pub('trueHeading', new Arinc429Word(word));
        });

        subscriber.on('trueTrackRaw').handle((word) => {
            publisher.pub('trueTrack', new Arinc429Word(word));
        });

        subscriber.on('mda').handle((word) => {
            publisher.pub('mdaAr', new Arinc429Word(word));
        });

        subscriber.on('dh').handle((word) => {
            publisher.pub('dhAr', new Arinc429Word(word));
        });

        subscriber.on('fcuSelectedHeadingRaw').handle((word) => {
            publisher.pub('fcuSelectedHeading', new Arinc429Word(word));
        });

        subscriber.on('fcuSelectedAltitudeRaw').handle((word) => {
            publisher.pub('fcuSelectedAltitude', new Arinc429Word(word));
        });

        subscriber.on('fcuSelectedAirspeedRaw').handle((word) => {
            publisher.pub('fcuSelectedAirspeed', new Arinc429Word(word));
        });

        subscriber.on('fcuSelectedVerticalSpeedRaw').handle((word) => {
            publisher.pub('fcuSelectedVerticalSpeed', new Arinc429Word(word));
        });

        subscriber.on('fcuSelectedTrackRaw').handle((word) => {
            publisher.pub('fcuSelectedTrack', new Arinc429Word(word));
        });

        subscriber.on('fcuSelectedFpaRaw').handle((word) => {
            publisher.pub('fcuSelectedFpa', new Arinc429Word(word));
        });

        subscriber.on('fcuAtsDiscreteWordRaw').handle((word) => {
            publisher.pub('fcuAtsDiscreteWord', new Arinc429Word(word));
        });

        subscriber.on('fcuAtsFmaDiscreteWordRaw').handle((word) => {
            publisher.pub('fcuAtsFmaDiscreteWord', new Arinc429Word(word));
        });

        subscriber.on('fcuEisLeftDiscreteWord1Raw').handle((word) => {
            if (getDisplayIndex() === 1) {
                publisher.pub('fcuEisDiscreteWord1', new Arinc429Word(word));
            }
        });

        subscriber.on('fcuEisLeftDiscreteWord2Raw').handle((word) => {
            if (getDisplayIndex() === 1) {
                this.fcuEisDiscreteWord2 = new Arinc429Word(word);
                this.determineFmgcToUseForFlightDirector(publisher);
                publisher.pub('fcuEisDiscreteWord2', this.fcuEisDiscreteWord2);
            }
        });

        subscriber.on('fcuEisLeftBaroRaw').handle((word) => {
            if (getDisplayIndex() === 1) {
                publisher.pub('fcuEisBaro', new Arinc429Word(word));
            }
        });

        subscriber.on('fcuEisLeftBaroHpaRaw').handle((word) => {
            if (getDisplayIndex() === 1) {
                publisher.pub('fcuEisBaroHpa', new Arinc429Word(word));
            }
        });

        subscriber.on('fcuEisRightDiscreteWord1Raw').handle((word) => {
            if (getDisplayIndex() === 2) {
                publisher.pub('fcuEisDiscreteWord1', new Arinc429Word(word));
            }
        });

        subscriber.on('fcuEisRightDiscreteWord2Raw').handle((word) => {
            if (getDisplayIndex() === 2) {
                this.fcuEisDiscreteWord2 = new Arinc429Word(word);
                this.determineFmgcToUseForFlightDirector(publisher);
                publisher.pub('fcuEisDiscreteWord2', this.fcuEisDiscreteWord2);
            }
        });

        subscriber.on('fcuEisRightBaroRaw').handle((word) => {
            if (getDisplayIndex() === 2) {
                publisher.pub('fcuEisBaro', new Arinc429Word(word));
            }
        });

        subscriber.on('fcuEisRightBaroHpaRaw').handle((word) => {
            if (getDisplayIndex() === 2) {
                publisher.pub('fcuEisBaroHpa', new Arinc429Word(word));
            }
        });

        subscriber.on('fcuDiscreteWord1Raw').handle((word) => {
            publisher.pub('fcuDiscreteWord1', new Arinc429Word(word));
        });

        subscriber.on('fcuDiscreteWord2Raw').handle((word) => {
            publisher.pub('fcuDiscreteWord2', new Arinc429Word(word));
        });

        subscriber.on('fmgc1PfdSelectedSpeedRaw').handle((word) => {
            if (this.fg1Selected) {
                publisher.pub('pfdSelectedSpeed', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2PfdSelectedSpeedRaw').handle((word) => {
            if (!this.fg1Selected) {
                publisher.pub('pfdSelectedSpeed', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1RollFdCommandRaw').handle((word) => {
            if (this.fg1ForFlightDirectorSelected) {
                publisher.pub('rollFdCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2RollFdCommandRaw').handle((word) => {
            if (!this.fg1ForFlightDirectorSelected) {
                publisher.pub('rollFdCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1PitchFdCommandRaw').handle((word) => {
            if (this.fg1ForFlightDirectorSelected) {
                publisher.pub('pitchFdCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2PitchFdCommandRaw').handle((word) => {
            if (!this.fg1ForFlightDirectorSelected) {
                publisher.pub('pitchFdCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1YawFdCommandRaw').handle((word) => {
            if (this.fg1ForFlightDirectorSelected) {
                publisher.pub('yawFdCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2YawFdCommandRaw').handle((word) => {
            if (!this.fg1ForFlightDirectorSelected) {
                publisher.pub('yawFdCommand', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1DiscreteWord5Raw').handle((word) => {
            if (this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord5', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2DiscreteWord5Raw').handle((word) => {
            if (!this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord5', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1DiscreteWord4Raw').handle((word) => {
            this.fmgc1DiscreteWord4 = new Arinc429Word(word);
            this.determineFmgcToUseForFlightDirector(publisher);
            this.determineFmgcToUse();
            publisher.pub('fmgc1DiscreteWord4', new Arinc429Word(word));
            if (this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord4', this.fmgc1DiscreteWord4);
            }
        });

        subscriber.on('fmgc2DiscreteWord4Raw').handle((word) => {
            this.fmgc2DiscreteWord4 = new Arinc429Word(word);
            this.determineFmgcToUseForFlightDirector(publisher);
            this.determineFmgcToUse();
            publisher.pub('fmgc2DiscreteWord4', new Arinc429Word(word));
            if (!this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord4', this.fmgc2DiscreteWord4);
            }
        });

        subscriber.on('fmgc1FmAltitudeConstraintRaw').handle((word) => {
            if (this.fg1Selected) {
                publisher.pub('fmgcFmAltitudeConstraint', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2FmAltitudeConstraintRaw').handle((word) => {
            if (!this.fg1Selected) {
                publisher.pub('fmgcFmAltitudeConstraint', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1AtsDiscreteWordRaw').handle((word) => {
            this.fmgc1AtsDiscreteWord = new Arinc429Word(word);
            this.determineFmgcToUse();
        });

        subscriber.on('fmgc2AtsDiscreteWordRaw').handle((word) => {
            this.fmgc2AtsDiscreteWord = new Arinc429Word(word);
            this.determineFmgcToUse();
        });

        subscriber.on('fmgc1DiscreteWord3Raw').handle((word) => {
            if (this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord3', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2DiscreteWord3Raw').handle((word) => {
            if (!this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord3', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1DiscreteWord1Raw').handle((word) => {
            if (this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord1', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2DiscreteWord1Raw').handle((word) => {
            if (!this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord1', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1DiscreteWord2Raw').handle((word) => {
            if (this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord2', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2DiscreteWord2Raw').handle((word) => {
            if (!this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord2', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc1DiscreteWord7Raw').handle((word) => {
            if (this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord7', new Arinc429Word(word));
            }
        });

        subscriber.on('fmgc2DiscreteWord7Raw').handle((word) => {
            if (!this.fg1Selected) {
                publisher.pub('fmgcDiscreteWord7', new Arinc429Word(word));
            }
        });
    }

    private determineAndPublishChosenRadioAltitude(publisher: Publisher<Arinc429Values>) {
        const ownRadioAltitudeHasData = !this.ownRadioAltitude.isFailureWarning() && !this.ownRadioAltitude.isNoComputedData();
        const oppRadioAltitudeHasData = !this.oppRadioAltitude.isFailureWarning() && !this.oppRadioAltitude.isNoComputedData();
        const chosenRadioAltitude = (
            // the own RA has no data and the opposite one has data
            (!ownRadioAltitudeHasData && oppRadioAltitudeHasData)
            // the own RA has FW and the opposite has NCD
            || this.ownRadioAltitude.isFailureWarning() && this.oppRadioAltitude.isNoComputedData()
        ) ? this.oppRadioAltitude : this.ownRadioAltitude;

        publisher.pub('chosenRa', chosenRadioAltitude);
    }

    private determineAndPublishChosenLandingElevation(publisher: Publisher<Arinc429Values>) {
        const useOpposite = (this.ownLandingElevation.isFailureWarning()
            || this.ownLandingElevation.isNoComputedData())
            && !this.oppLandingElevation.isFailureWarning()
            && !this.oppLandingElevation.isNoComputedData();

        if (useOpposite) {
            publisher.pub('landingElevation', this.oppLandingElevation);
        } else {
            publisher.pub('landingElevation', this.ownLandingElevation);
        }
    }

    private determineFcdcToUse() {
        if (getDisplayIndex() === 1) {
            if (
                (this.fcdc1DiscreteWord1.isFailureWarning() && !this.fcdc2DiscreteWord1.isFailureWarning())
                || (!this.fcdc1DiscreteWord1.getBitValueOr(24, false) && this.fcdc2DiscreteWord1.getBitValueOr(24, false))) {
                return 2;
            }
            return 1;
        }
        if (!((!this.fcdc1DiscreteWord1.isFailureWarning() && this.fcdc2DiscreteWord1.isFailureWarning())
            || (this.fcdc1DiscreteWord1.getBitValueOr(24, false) && !this.fcdc2DiscreteWord1.getBitValueOr(24, false)))) {
            return 2;
        }
        return 1;
    }

    // Determine which FAC bus to use for FE function. If FAC HEALTHY discrete is low or any word is coded FW,
    // declare FAC as invalid. For simplicty reasons, only check SSM of words that use the same data, so all failure cases are
    // handled while minimizing the words that have to be checked.
    // Left PFD uses FAC 1 when both are valid, the right PFD uses FAC 2. In case of invalidity, switchover is performed.
    // If no FAC is valid, set facToUse to 0. This causes the SPD LIM flag to be displayed.
    private determineFacToUse(publisher: Publisher<Arinc429Values>) {
        const fac1Valid = this.fac1Healthy && !this.fac1VAlphaMax.isFailureWarning();
        const fac2Valid = this.fac2Healthy && !this.fac2VAlphaMax.isFailureWarning();
        if (getDisplayIndex() === 1 && fac1Valid) {
            this.facToUse = 1;
        } else if (getDisplayIndex() === 2 && fac2Valid) {
            this.facToUse = 2;
        } else if (fac1Valid) {
            this.facToUse = 1;
        } else if (fac2Valid) {
            this.facToUse = 2;
        } else {
            this.facToUse = 0;
        }

        publisher.pub('facToUse', this.facToUse);
    }

    private determineFmgcToUseForFlightDirector(publisher: Publisher<Arinc429Values>) {
        const side2 = getDisplayIndex() === 2;

        const fd1Engaged = this.fmgc1DiscreteWord4.getBitValueOr(13, false);
        const fd2Engaged = this.fmgc2DiscreteWord4.getBitValueOr(13, false);
        const fdOwnSelectedOn = this.fcuEisDiscreteWord2.getBitValueOr(23, false);

        const ownFdEngaged = side2 ? fd2Engaged : fd1Engaged;
        const oppFdEngaged = side2 ? fd1Engaged : fd2Engaged;

        const ownFdEngagedAndOn = ownFdEngaged && fdOwnSelectedOn;
        const oppFdEngagedAndOn = !ownFdEngaged && oppFdEngaged && fdOwnSelectedOn;

        this.fg1ForFlightDirectorSelected = (!side2 && !ownFdEngagedAndOn && !oppFdEngagedAndOn)
        || (!side2 && ownFdEngagedAndOn) || (side2 && oppFdEngagedAndOn);

        publisher.pub('fdEngaged', this.fg1ForFlightDirectorSelected ? fd1Engaged : fd2Engaged);
    }

    private determineFmgcToUse() {
        const side2 = getDisplayIndex() === 2;

        const ap1Engaged = this.fmgc1DiscreteWord4.getBitValueOr(12, false);
        const fd1Engaged = this.fmgc1DiscreteWord4.getBitValueOr(13, false);
        const ap2Engaged = this.fmgc2DiscreteWord4.getBitValueOr(12, false);
        const fd2Engaged = this.fmgc2DiscreteWord4.getBitValueOr(13, false);

        const fg1Inop = this.fmgc1AtsDiscreteWord.getBitValueOr(24, false) || this.fmgc1AtsDiscreteWord.isFailureWarning() || this.fmgc1DiscreteWord4.isFailureWarning();
        const fg2Inop = this.fmgc2AtsDiscreteWord.getBitValueOr(24, false) || this.fmgc2AtsDiscreteWord.isFailureWarning() || this.fmgc2DiscreteWord4.isFailureWarning();

        const apCondition = !side2 ? ap1Engaged : ap1Engaged && !ap2Engaged;
        const fdCondition = !(ap1Engaged || ap2Engaged) && (!side2 ? fd1Engaged : fd1Engaged && !fd2Engaged);
        const inopCondition = !(ap1Engaged || ap2Engaged) && !(fd1Engaged || fd2Engaged) && (!fg1Inop || fg2Inop);

        this.fg1Selected = apCondition || fdCondition || inopCondition;
    }
}
