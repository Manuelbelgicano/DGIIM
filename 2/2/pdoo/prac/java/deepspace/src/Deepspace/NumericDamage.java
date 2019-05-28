/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase daño numérico
 */
public class NumericDamage extends Damage {
    private int nWeapons;
    
    NumericDamage(int w,int s) {
        super(s);
        nWeapons = w;
    }
    
    public int getNWeapons() { return nWeapons; }
    
    @Override
    public NumericDamage copy() {
        return new NumericDamage(nWeapons,getNShields());
    }
    
    @Override
    public NumericDamageToUI getUIversion() {
        return new NumericDamageToUI(this);
    }
    
    @Override
    public NumericDamage adjust(ArrayList<Weapon> w,ArrayList<ShieldBooster> s) {
        int newShields = (getNShields()<s.size())?getNShields():s.size();
        int newWeapons = (nWeapons<w.size())?nWeapons:w.size();
        return new NumericDamage(newWeapons,newShields);
    }
    
    @Override
    public void discardWeapon(Weapon w) {
        if (nWeapons>0)
            nWeapons--;
    }
    
    @Override
    public boolean hasNoEffect() { return (super.hasNoEffect() && nWeapons==0); }
    
    @Override
    public String toString() {
        String aux = super.toString();
        aux += "\nNúmero de armas: "+nWeapons;
        return aux;
    }
}
