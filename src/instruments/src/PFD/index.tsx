import React, { useEffect, useState } from 'react';
import { Horizon } from './AttitudeIndicatorHorizon';
import { AttitudeIndicatorFixedUpper, AttitudeIndicatorFixedCenter } from './AttitudeIndicatorFixed';
import { LandingSystem } from './LandingSystemIndicator';
import { VerticalSpeedIndicator } from './VerticalSpeedIndicator';
import { HeadingOfftape, HeadingTape } from './HeadingIndicator';
import { AltitudeIndicatorOfftape, AltitudeIndicator } from './AltitudeIndicator';
import { AirspeedIndicatorOfftape, AirspeedIndicator } from './SpeedIndicator';
import { FMA } from './FMA';
import { getSimVar, setSimVar } from '../util.js';
import { LagFilter, RateLimiter } from './PFDUtils';
import { useSimVar } from '../Common/simVars';
import { render } from '../Common';
import './style.scss';
import { useInteractionEvent, useUpdate } from '../Common/hooks';

const AltModeSelected = () => {
    if (Simplane.getAutoPilotAltitudeManaged() && getSimVar('L:AP_CURRENT_TARGET_ALTITUDE_IS_CONSTRAINT', 'number') !== 0) {
        return false;
    }
    return true;
};

const airspeedAccFilter = new LagFilter(1.2);
const airspeedAccRateLimiter = new RateLimiter(1.2, -1.2);

declare const SimVar : {
    GetGameVarValue(name: string, unit: string, param1: number): number
};

declare const Simplane : {
    getAutoPilotDisplayedAltitudeLockValue()
    getAutoPilotAirspeedHoldValue()
    getCurrentFlightPhase()
    getAutoPilotMachHoldValue()
    getAutoPilotAltitudeManaged()
};

const PFD = () => {
    const [dispIndex, setDispIndex] = useState(0);
    const [lsButtonPressed, setLsPressed] = useState(false);
    const [filteredAirspeedAcc, setAirspeedAcc] = useState(0);
    const [isAttExcessive, setAttExcessive] = useState(false);
    const [prevAirspeed, setPrevAirspeed] = useState(0);

    const [negPitch] = useSimVar('PLANE PITCH DEGREES', 'degrees');
    const pitch = -negPitch;
    const [roll] = useSimVar('PLANE BANK DEGREES', 'degrees');
    const [heading] = useSimVar('PLANE HEADING DEGREES MAGNETIC', 'degrees');

    const [unclampedAirspeed] = useSimVar('AIRSPEED INDICATED', 'knots');
    const clampedAirspeed = Math.max(unclampedAirspeed, 30);

    useEffect(() => {
        const url = document.getElementsByTagName('a32nx-pfd-element')[0].getAttribute('url') || '';
        setDispIndex(parseInt(url.substring(url.length - 1), 10));

        setLsPressed(getSimVar(`L:BTN_LS_${dispIndex}_FILTER_ACTIVE`, 'bool'));

        // for testing only
        setSimVar('L:A32NX_MachPreselVal', -1, 'mach');
        setSimVar('L:A32NX_SpeedPreselVal', -1, 'knots');
    }, []);

    useEffect(() => {
        if (!isAttExcessive && (pitch > 25 || pitch < -13 || Math.abs(roll) > 45)) {
            setAttExcessive(true);
        } else if (isAttExcessive && pitch < 22 && pitch > -10 && Math.abs(roll) < 40) {
            setAttExcessive(false);
        }
    }, [negPitch, roll]);

    useInteractionEvent(`A320_Neo_PFD_BTN_LS_${dispIndex}`, () => {
        setLsPressed(!lsButtonPressed);
        setSimVar(`L:BTN_LS_${dispIndex}_FILTER_ACTIVE`, lsButtonPressed, 'Bool');
    });

    useUpdate((deltaTime) => {
        const airspeedAcc = (clampedAirspeed - prevAirspeed) / deltaTime * 1000;
        setPrevAirspeed(clampedAirspeed);
        const rateLimitedAirspeedAcc = airspeedAccRateLimiter.step(airspeedAcc, deltaTime / 1000);
        setAirspeedAcc(airspeedAccFilter.step(rateLimitedAirspeedAcc, deltaTime / 1000));
    });

    // We shouldn't use the normal simvar getters, and simplane here. But it should be fine for no, until we have a better
    // system for the target altitude/speeds etc. The Component will be updated anyways.
    let targetAlt = Simplane.getAutoPilotDisplayedAltitudeLockValue();
    let isManaged = false;
    if (!AltModeSelected()) {
        const CSTAlt = getSimVar('L:A32NX_AP_CSTN_ALT', 'feet');
        if (Number.isFinite(CSTAlt)) {
            isManaged = true;
            targetAlt = CSTAlt;
        }
    }

    const [v2Speed] = useSimVar('L:AIRLINER_V2_SPEED', 'Knots');
    const [speedMode] = useSimVar('AUTOPILOT SPEED SLOT INDEX', 'number');
    const isSelected = speedMode === 1;
    const [isMach] = useSimVar('L:XMLVAR_AirSpeedIsInMach', 'bool');
    const [airlinerFlightPhase] = useSimVar('L:AIRLINER_FLIGHT_PHASE', 'number');
    let targetSpeed = v2Speed;
    if (isSelected) {
        if (isMach) {
            targetSpeed = SimVar.GetGameVarValue('FROM MACH TO KIAS', 'number', Simplane.getAutoPilotMachHoldValue());
        } else {
            targetSpeed = Simplane.getAutoPilotAirspeedHoldValue();
        }
    } else if (targetSpeed < 0 || airlinerFlightPhase > 2) {
        if (isMach) {
            targetSpeed = Simplane.getCurrentFlightPhase() === 6
                ? getSimVar('L:A32NX_AP_APPVLS', 'knots')
                : SimVar.GetGameVarValue('FROM MACH TO KIAS', 'number', Simplane.getAutoPilotMachHoldValue());
        } else {
            targetSpeed = Simplane.getCurrentFlightPhase() === 6
                ? getSimVar('L:A32NX_AP_APPVLS', 'knots') : Simplane.getAutoPilotAirspeedHoldValue();
        }
    }

    const [FDActive] = useSimVar(`AUTOPILOT FLIGHT DIRECTOR ACTIVE:${dispIndex}`, 'Bool');

    const [showSelectedHeading] = useSimVar('L:A320_FCU_SHOW_SELECTED_HEADING', 'number');
    const [selectedHeadingVal] = useSimVar('AUTOPILOT HEADING LOCK DIR:1', 'degrees');
    let selectedHeading = NaN;
    if (showSelectedHeading) {
        selectedHeading = selectedHeadingVal;
    }

    const [ILSCourseVal] = useSimVar('NAV LOCALIZER:3', 'degrees');
    let ILSCourse = NaN;
    if (lsButtonPressed) {
        ILSCourse = ILSCourseVal;
    }

    return (
        <svg className="pfd-svg" version="1.1" viewBox="0 0 158.75 158.75" xmlns="http://www.w3.org/2000/svg">
            <Horizon FDActive={FDActive} selectedHeading={selectedHeading} isAttExcessive={isAttExcessive} />
            <path
                id="Mask1"
                className="BackgroundFill"
                d="m32.138 101.25c7.4164 13.363 21.492 21.652 36.768 21.652 15.277 0 29.352-8.2886 36.768-21.652v-40.859c-7.4164-13.363-21.492-21.652-36.768-21.652-15.277 0-29.352 8.2886-36.768 21.652zm-32.046 57.498h158.66v-158.75h-158.66z"
            />
            <HeadingTape heading={heading} />
            <AltitudeIndicator />
            <AirspeedIndicator airspeed={clampedAirspeed} airspeedAcc={filteredAirspeedAcc} />
            <path
                id="Mask2"
                className="BackgroundFill"
                d="m32.138 145.34h73.536v10.382h-73.536zm0-44.092c7.4164 13.363 21.492 21.652 36.768 21.652 15.277 0 29.352-8.2886 36.768-21.652v-40.859c-7.4164-13.363-21.492-21.652-36.768-21.652-15.277 0-29.352 8.2886-36.768 21.652zm-32.046 57.498h158.66v-158.75h-158.66zm115.14-35.191v-85.473h15.609v85.473zm-113.33 0v-85.473h27.548v85.473z"
            />
            <LandingSystem LSButtonPressed={lsButtonPressed} />
            <AttitudeIndicatorFixedUpper />
            <AttitudeIndicatorFixedCenter FDActive={FDActive} isAttExcessive={isAttExcessive} />
            <VerticalSpeedIndicator />
            <HeadingOfftape ILSCourse={ILSCourse} selectedHeading={selectedHeading} />
            <AltitudeIndicatorOfftape targetAlt={targetAlt} altIsManaged={isManaged} />
            <AirspeedIndicatorOfftape airspeed={clampedAirspeed} airspeedAcc={filteredAirspeedAcc} targetSpeed={targetSpeed} speedIsManaged={!isSelected} />
            <FMA isAttExcessive={isAttExcessive} />
        </svg>
    );
};

render(<PFD />);
