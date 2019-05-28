/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase estación espacial
 */
public class SpaceStation implements SpaceFighter {
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
        shieldPower = supplies.getShieldPower();
        assignFuelValue(supplies.getFuelUnits());
    }
    
    SpaceStation(SpaceStation station) {
        hangar = station.hangar;
        pendingDamage = station.pendingDamage;
        name = station.name;
        ammoPower = station.ammoPower;
        shieldPower = station.shieldPower;
        assignFuelValue(station.fuelUnits);
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
        if (i>=0 && i<shieldBoosters.size()) {
            if (pendingDamage!=null)
                pendingDamage.discardShieldBooster();
            shieldBoosters.remove(i);
        }
        
    }
    
    public void discardShieldBoosterInHangar(int i) {
        if (hangar!=null)
            hangar.removeShieldBooster(i);
    }
    
    public void discardWeapon(int i) {
        if (i>=0 && i<weapons.size()) {
            if (pendingDamage!=null) {
                Weapon w = weapons.get(i);
                pendingDamage.discardWeapon(w);
                cleanPendingDamage();
            }
            weapons.remove(i);
        }
    }
    
    public void discardWeaponInHangar(int i) {
        if (hangar!=null)
            hangar.removeWeapon(i);
    }
    
    @Override
    public float fire() {
        float factor = 1.0f;
        for (Weapon w: weapons)
            factor = factor*w.useIt();
        return factor;
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
    
    @Override
    public float protection() {
        float factor = 1.0f;
        for (ShieldBooster s: shieldBoosters)
            factor = factor*s.useIt();
        return factor;
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
    
    @Override
    public ShotResult recieveShot(float shot) {
        float my_protection = protection();
        if (my_protection>=shot) {
            shieldPower = ((shieldPower-shot*SHIELDLOSSPERUNITSHOT)<0.0f)?0.0f:shieldPower-shot*SHIELDLOSSPERUNITSHOT;
            return ShotResult.RESIST;
        } else {
            shieldPower = 0.0f;
            return ShotResult.DONOTRESIST;
        }
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
    
    public Transformation setLoot(Loot loot) {
        CardDealer dealer = CardDealer.getInstance();
        
        int h = loot.getNHangars();
        if (h>0) {
            Hangar hangar = dealer.nextHangar();
            recieveHangar(hangar);
        }
        
        int elements = loot.getNSupplies();
        for (int i=0;i<elements;i++) {
            SuppliesPackage sup = dealer.nextSuppliesPackage();
            recieveSupplies(sup);
        }
        
        elements = loot.getNWeapons();
        for (int i=0;i<elements;i++) {
            Weapon weap = dealer.nextWeapon();
            recieveWeapon(weap);
        }
        
        elements = loot.getNShields();
        for (int i=0;i<elements;i++) {
            ShieldBooster sh = dealer.nextShieldBooster();
            recieveShieldBooster(sh);
        }
        
        int medals = loot.getNMedals();
        nMedals += medals;
        
        if (loot.getEfficient())
            return Transformation.GETEFFICIENT;
        else if(loot.spaceCity())
            return Transformation.SPACECITY;
        else
            return Transformation.NOTRANSFORM;
    }
    
    public void setPendingDamage(Damage d) { pendingDamage = d.adjust(weapons, shieldBoosters); }
    
    public boolean validState() { return pendingDamage==null || pendingDamage.hasNoEffect(); }
   
    @Override
    public String toString() {
        String aux = "Nombre de la nave: " + name;
        aux += "\nCombustible: " + fuelUnits;
        aux += ", Potencia de disparo: " + ammoPower;
        aux += ", Potencia de escudo: " + shieldPower;
        aux += "\nMedallas: " + nMedals;
        aux += "\n--------------------------\nHangar:";
        if (hangar!=null)
            aux += hangar.toString();
        aux += "--------------------------\nArmas:\n";
         for (Weapon w: weapons)
            aux += w.toString() + "\n";
        aux += "Escudos:\n";
        for (ShieldBooster s: shieldBoosters)
            aux += s.toString() + "\n";
        aux += "Daño: ";
            if (pendingDamage!=null)
                aux += pendingDamage.toString() + "\n";
        return aux;
    }
    
}