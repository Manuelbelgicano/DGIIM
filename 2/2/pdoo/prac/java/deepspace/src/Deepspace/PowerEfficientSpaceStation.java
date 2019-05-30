/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Clase nave espacial eficiente
 */
public class PowerEfficientSpaceStation extends SpaceStation {
    private static final float EFFICIENCYFACTOR = 1.10f;
    
    PowerEfficientSpaceStation(SpaceStation station) {
        super(station);
    }
    
    @Override
    public float fire() { return super.fire()*EFFICIENCYFACTOR; }
    
    @Override
    public float protection() { return super.protection()*EFFICIENCYFACTOR; }
    
    @Override
    public Transformation setLoot(Loot loot) {
        super.setLoot(loot);
        if (loot.getEfficient())
            return Transformation.GETEFFICIENT;
        else
            return Transformation.NOTRANSFORM;
    }
    
    @Override
    public String toString() {
        String aux = "-----NAVE EFICIENTE-----\n";
        aux += super.toString();
        return aux;
    }
    
    @Override
    public PowerEfficientSpaceStationToUI getUIversion() { return new PowerEfficientSpaceStationToUI(this); }
}
