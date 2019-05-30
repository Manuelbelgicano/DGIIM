/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase ciudad espacial
 */
public class SpaceCity extends SpaceStation {
    private SpaceStation base;
    private ArrayList<SpaceStation> collaborators = new ArrayList<>();
    
    SpaceCity(SpaceStation _base,ArrayList<SpaceStation> rest) {
        super(_base);
        base = _base;
        collaborators = rest;
    }
    
    public ArrayList<SpaceStation> getCollaborators() { return collaborators; }
    
    @Override
    public float fire() {
        float fire_power = super.fire();
        for (SpaceStation s: collaborators)
            fire_power += s.fire();
        return fire_power;
    }
    
    @Override
    public float protection() {
        float shield_power = super.protection();
        for (SpaceStation s: collaborators)
            shield_power += s.protection();
        return shield_power;
    }
    
    @Override
    public Transformation setLoot(Loot loot) {
        super.setLoot(loot);
        return Transformation.NOTRANSFORM;
    }
    
    @Override
    public String toString() {
        String aux = "-----CIUDAD ESPACIAL-----\nCiudad base:\n";
        aux += super.toString() + "\nColaboradores:\n";
        for (SpaceStation s: collaborators)
            aux += s.toString();
        return aux;
    }
    
    @Override
    SpaceCityToUI getUIversion() { return new SpaceCityToUI(this); }
}
