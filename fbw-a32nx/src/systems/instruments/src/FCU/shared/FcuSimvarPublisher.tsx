import { EventBus, SimVarDefinition, SimVarValueType, SimVarPublisher } from 'msfssdk';

export interface FcuSimvars {
}

export enum FcuVars {
}

export class FCUSimvarPublisher extends SimVarPublisher<FcuSimvars> {
    private static simvars = new Map<keyof FcuSimvars, SimVarDefinition>([

    ])

    public constructor(bus: EventBus) {
        super(FCUSimvarPublisher.simvars, bus);
    }
}
