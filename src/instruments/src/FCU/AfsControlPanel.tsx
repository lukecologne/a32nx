import React from 'react';
import { SpeedControl } from './SpeedControl';
import { Mode } from './Mode';
import { LateralControl } from './LateralControl';
import { VerticalControl } from './VerticalControl';

export const AfsControlPanel = () => (
    <svg className="fcu-svg" viewBox="0 0 1280 102">
        <SpeedControl />

        <LateralControl />

        <Mode />

        <VerticalControl />
    </svg>
);
