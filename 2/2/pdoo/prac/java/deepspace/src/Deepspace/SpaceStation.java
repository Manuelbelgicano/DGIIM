/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase estación espacial
 */
class SpaceStation {
    private final static int MAXFUEL = 100;
    private final static float SHIELDLOSSPERUNITSHOT = 0.1f;
    
    private float ammoPower;
    private float fuelUnits;
    private String name;
    private int nMedals = 0;
    private float shieldPower;
    private Damage pendingDamage;
    private Hangar hangar;
    private ArrayList<Weapon> weapons = new ArrayList<>();
    private ArrayList<ShieldBooster> shieldBoosters = new ArrayList<>();
    
    SpaceStation(String n,SuppliesPackage supplies) {
        hangar = null;
        pendingDamage = null;
        name = n;
        ammoPower = supplies.getAmmoPower();
        shieldPower = supplies.getFuelUnits();
        assignFuelValue(supplies.getFuelUnits());
    }
    
    private void assignFuelValue(float f) {
        fuelUnits = (f<MAXFUEL)?f:MAXFUEL;
    }
    
    private void cleanPendingDamage() {
        if (pendingDamage!=null && pendingDamage.hasNoEffect())
            pendingDamage = null;
    }
    
    public void cleanUpMountedUnits() {
        for (Weapon w: weapons)
            if (w.getUses()==0)
                weapons.remove(w);
        for (ShieldBooster s: shieldBoosters)
            if (s.getUses()==0)
                shieldBoosters.remove(s);
    }
    
    public void discardHangar() {
        if (hangar!=null)
            hangar = null;
    }
    
    public void discardShieldBooster(int i) {
        throw new UnsupportedOperationException();
    }
    
    public void discardShieldBoosterInHangar(int i) {
        if (hangar!=null)
            hangar.removeShieldBooster(i);
    }
    
    public void discardWeapon(int i) {
        throw new UnsupportedOperationException();
    }
    
    public void discardWeaponInHangar(int i) {
        if (hangar!=null)
            hangar.removeWeapon(i);
    }
    
    public float fire() {
        throw new UnsupportedOperationException();
    }
    
    public float getAmmoPower() { return ammoPower; }
    
    public float getFuelUnits() { return fuelUnits;  }
    
    public Hangar getHangar() { return hangar; }
    
    public String getName() { return name; }
    
    public int getNMedals() { return nMedals; }
    
    public Damage getPendingDamage() { return pendingDamage; }
    
    public ArrayList<ShieldBooster> getShieldBoosters() { return shieldBoosters; }
    
    public float getShieldPower() { return shieldPower; }
    
    public float getSpeed() { return fuelUnits/MAXFUEL; }
    
    SpaceStationToUI getUIversion() { return new SpaceStationToUI(this); }
    
    public ArrayList<Weapon> getWeapons() { return weapons; }
    
    public void mountShieldBooster(int i) {
        ShieldBooster aux = null;
        if (hangar!=null) {
            aux = hangar.removeShieldBooster(i);
            if (aux!=null)
                shieldBoosters.add(aux);
        }
    }
    
    public void mountWeapon(int i) {
        Weapon aux = null;
        if (hangar!=null) {
            aux = hangar.removeWeapon(i);
            if (aux!=null)
                weapons.add(aux);
        }
    }
    
    public void move() { fuelUnits = ((fuelUnits-getSpeed())<0)?0:(fuelUnits-getSpeed()); }
    
    public float protection() {
        throw new UnsupportedOperationException();
    }
    
    public void recieveHangar(Hangar h) {
        if (hangar==null)
            hangar = h;
    }
    
    public boolean recieveShieldBooster(ShieldBooster s) {
        if (hangar!=null)
            return hangar.addShieldBooster(s);
        else
            return false;
    }
    
    public ShotResult recieveShot(float shot) {
        throw new UnsupportedOperationException();
    }
    
    public void recieveSupplies(SuppliesPackage s) {
        ammoPower += s.getAmmoPower();
        shieldPower += s.getShieldPower();
        assignFuelValue(fuelUnits+s.getFuelUnits());
    }
    
    public boolean recieveWeapon(Weapon w) {
        if (hangar!=null)
            return hangar.addWeapon(w);
        else
            return false;
    }
    
    public void setLoot(Loot loot) {
        throw new UnsupportedOperationException();
    }
    
    public void setPendingDamage(Damage d) { pendingDamage = d.adjust(weapons, shieldBoosters); }
    
    public boolean validState() { return pendingDamage==null || pendingDamage.hasNoEffect(); }
}