/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase del daño
 */
abstract class Damage {
    private int nShields;
    
    Damage(int s) {
        nShields = s;
    }

    public abstract Damage copy();   
    public abstract DamageToUI getUIversion();   
    public abstract Damage adjust(ArrayList<Weapon> w, ArrayList<ShieldBooster> s);
    public abstract void discardWeapon(Weapon w);
    
    public void discardShieldBooster() {
        if (nShields>0)
            nShields--;
    }
    
    public boolean hasNoEffect() { return nShields==0; }
    
    public int getNShields() { return nShields; }
    
    @Override
    public String toString() {
        String aux = "Número de escudos: "+nShields;
        return aux;
    }
}
