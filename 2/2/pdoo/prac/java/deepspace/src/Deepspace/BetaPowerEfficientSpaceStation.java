/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Clase nave espacial más eficiente
 */
public class BetaPowerEfficientSpaceStation extends PowerEfficientSpaceStation {
    private static final float EXTRAEFFICIENCY = 1.2f;
    
    BetaPowerEfficientSpaceStation(SpaceStation station) {
        super(station);
    }
    
    @Override
    public float fire() {
        Dice dice = new Dice();
        if (dice.extraEfficiency())
            return super.fire()*EXTRAEFFICIENCY;
        else
            return super.fire();
    }
    
    @Override
    public BetaPowerEfficientSpaceStationToUI getUIversion() { return new BetaPowerEfficientSpaceStationToUI(this); }
}
