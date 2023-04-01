import { EventBus, FSComponent } from 'msfssdk';
import { FCUSimvarPublisher } from './shared/FcuSimvarPublisher';
import { FCUComponent } from './FCU';

// eslint-disable-next-line camelcase
class A32NX_FCU extends BaseInstrument {
    private bus: EventBus;

    private simVarPublisher: FCUSimvarPublisher;

    /**
     * "mainmenu" = 0
     * "loading" = 1
     * "briefing" = 2
     * "ingame" = 3
     */
    private gameState = 0;

    constructor() {
        super();
        this.bus = new EventBus();
        this.simVarPublisher = new FCUSimvarPublisher(this.bus);

        this.simVarPublisher.subscribe('eisDisplayLeftBaroValueMode');
        this.simVarPublisher.subscribe('eisDisplayLeftBaroValue');
        this.simVarPublisher.subscribe('eisDisplayLeftBaroMode');
        this.simVarPublisher.subscribe('eisDisplayRightBaroValueMode');
        this.simVarPublisher.subscribe('eisDisplayRightBaroValue');
        this.simVarPublisher.subscribe('eisDisplayRightBaroMode');

        this.simVarPublisher.subscribe('afsDisplayTrkFpaMode');
        this.simVarPublisher.subscribe('afsDisplayMachMode');
        this.simVarPublisher.subscribe('afsDisplaySpdMachValue');
        this.simVarPublisher.subscribe('afsDisplaySpdMachManaged');
        this.simVarPublisher.subscribe('afsDisplayHdgTrkValue');
        this.simVarPublisher.subscribe('afsDisplayHdgTrkManaged');
        this.simVarPublisher.subscribe('afsDisplayAltValue');
        this.simVarPublisher.subscribe('afsDisplayLvlChManaged');
        this.simVarPublisher.subscribe('afsDisplayVsFpaValue');
    }

    get templateID(): string {
        return 'A32NX_FCU';
    }

    public connectedCallback(): void {
        super.connectedCallback();

        FSComponent.render(<FCUComponent bus={this.bus} />, document.getElementById('FCU_CONTENT'));

        // Remove "instrument didn't load" text
        document.getElementById('FCU_CONTENT').querySelector(':scope > h1').remove();
    }

    public Update(): void {
        super.Update();

        if (this.gameState !== 3) {
            const gamestate = this.getGameState();
            if (gamestate === 3) {
                this.simVarPublisher.startPublish();
            }
            this.gameState = gamestate;
        } else {
            this.simVarPublisher.onUpdate();
        }
    }
}

registerInstrument('a32nx-fcu', A32NX_FCU);
