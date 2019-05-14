/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;
        
class Hangar {
    private int maxElements;
    private ArrayList<Weapon> weapons = new ArrayList<>();
    private ArrayList<ShieldBooster> shieldBoosters = new ArrayList<>();
    
    Hangar(int capacity) {  maxElements = capacity; }
    
    Hangar(Hangar h) {
        maxElements = h.maxElements;
        weapons = h.weapons;
        shieldBoosters = h.shieldBoosters;
    }
    
    HangarToUI getUIversion() { return new HangarToUI(this); }
    
    private boolean spaceAvaiable() {
        return (shieldBoosters.size()+weapons.size())<maxElements;
    }
    
    public boolean addWeapon(Weapon w) {
        if (spaceAvaiable()) {
            weapons.add(w);
            return true;
        } else
            return false;
    }
    
    public boolean addShieldBooster(ShieldBooster s) {
        if (spaceAvaiable()) {
            shieldBoosters.add(s);
            return true;
        } else
            return false;
    }
    
    public int getMaxElements() { return maxElements; }
    
    public ArrayList<ShieldBooster> getShieldBoosters() { return shieldBoosters; }
    
    public ArrayList<Weapon> getWeapons() { return weapons; }
    
    public ShieldBooster removeShieldBooster(int s) {
        if (s<0 || s>=shieldBoosters.size())
            return null;
        else {
            ShieldBooster aux = shieldBoosters.get(s);
            shieldBoosters.remove(s);
            return aux;
        }
    }
    
    public Weapon removeWeapon(int w) {
        if (w<0 || w>=weapons.size())
            return null;
        else {
            Weapon aux = weapons.get(w);
            weapons.remove(w);
            return aux;
        }
    }
}
