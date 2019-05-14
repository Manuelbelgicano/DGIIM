/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase del daño
 */
class Damage {
    private int nShields;
    private int nWeapons;
    private ArrayList<WeaponType> weapons = new ArrayList<>();
    
    Damage(int w, int s) {
        nWeapons = w;
        nShields = s;
    }
    
    Damage(ArrayList<WeaponType> wl,int s) {
        nWeapons = -1;
        weapons = wl;
        nShields = s;
    }
    
    Damage(Damage d) {
        nWeapons = d.nWeapons;
        nShields = d.nShields;
        weapons = d.weapons;
    }
    
    DamageToUI getUIversion() { return new DamageToUI(this); }
    
    private int arrayContainsType(ArrayList<Weapon> w,WeaponType t) {
        for (int i=0;i<w.size();i++) {
            if (w.get(i).getType()==t)
                return i;
        }
        return -1;
    }
    
    public Damage adjust(ArrayList<Weapon> w, ArrayList<ShieldBooster> s) {
        // Ajustamos los escudos
        int newNShields = (s.size()<=nShields)?s.size():nShields;
        // Ajustamos las armas
        if (weapons.isEmpty()) {
            int newNWeapons = (w.size()<=nWeapons)?w.size():nWeapons;
            return new Damage(newNWeapons,newNShields);
        } else {
            ArrayList<WeaponType> newWeapons = weapons;
            for (WeaponType wType: newWeapons) {
                if (arrayContainsType(w,wType)==-1) // No existe ese tipo de arma
                    newWeapons.remove(wType);
                else { // Existe ese tipo de arma
                    int typeCountW = 0;
                    int typeCountNW = 0;
                    for (Weapon weap: w)
                        if (weap.getType()==wType)
                            typeCountW++;
                    for (WeaponType t: newWeapons)
                        if (t==wType)
                            typeCountNW++;
                    if (typeCountW<typeCountNW)
                        newWeapons.remove(wType);
                }
            }
            return new Damage(newWeapons,newNShields);
        }
    }
    
    public void discardWeapon(Weapon w) {
        if (weapons.isEmpty()) {
            if (nWeapons<0)
                nWeapons--;
        } else {
            boolean discarded = false;
            for (int i=0;i<weapons.size() || !discarded;i++) 
                if (weapons.get(i)==w.getType()) {
                    weapons.remove(i);
                    discarded = true;
                }
        }
    }
    
    public void discardShieldBooster() {
        if (nShields>0)
            nShields--;
    }
    
    public boolean hasNoEffect() {
        if (nShields==0) {
            return weapons.isEmpty() && (nWeapons==0 || nWeapons==-1);
        }
        return false;
    }
    
    public int getNShields() { return nShields; }
    
    public int getNWeapons() { return nWeapons; }
    
    public ArrayList<WeaponType> getWeapons() { return weapons; }
    
    @Override
    public String toString() {
        String aux = "Número de escudos: "+nShields;
        aux += "\nNúmero de armas "+nWeapons;
        aux += "\nTipos de armas:";
        for (WeaponType t: weapons)
            aux += " "+t+",";
        return aux;
    }
}
