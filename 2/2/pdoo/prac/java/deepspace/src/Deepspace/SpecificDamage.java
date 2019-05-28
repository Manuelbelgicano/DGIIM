/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase de daño específico
 */
public class SpecificDamage extends Damage {
    private ArrayList<WeaponType> weapons = new ArrayList<>();
    
    SpecificDamage(ArrayList<WeaponType> wl,int s) {
        super(s);
        weapons = wl;
    }
        
    private int arrayContainsType(ArrayList<Weapon> w,WeaponType t) {
        for (int i=0;i<w.size();i++) {
            if (w.get(i).getType()==t)
                return i;
        }
        return -1;
    }
    
    public ArrayList<WeaponType> getWeapons() { return weapons; }
    
    @Override
    public SpecificDamage copy() { return new SpecificDamage(weapons,getNShields()); }
 
    @Override
    public SpecificDamageToUI getUIversion() { return new SpecificDamageToUI(this); }
    
    @Override
    public SpecificDamage adjust(ArrayList<Weapon> w, ArrayList<ShieldBooster> s) {
        int newShields = (getNShields()<s.size())?getNShields():s.size();
        ArrayList<WeaponType> newWeapons = new ArrayList<>();
        
        for (int i=0;i<weapons.size();i++) {
            int index = arrayContainsType(w,weapons.get(i));
            if (index!=-1) {
                int tipoEnDanio = 0, tipoEnArmas = 1;
                for (WeaponType wt: newWeapons)
                    if (wt==weapons.get(i))
                        tipoEnDanio++;
                for (int j=index+1;j<w.size();j++)
                    if (w.get(j).getType()==weapons.get(i))
                        tipoEnArmas++;
                if (tipoEnDanio<tipoEnArmas)
                    newWeapons.add(weapons.get(i));
            }
        }
        
        return new SpecificDamage(newWeapons,newShields);
    }
    
    @Override
    public void discardWeapon(Weapon w) {
        boolean contained = false;
        
        for (int i=0;i<weapons.size() || !contained;i++)
            if (w.getType()==weapons.get(i)) {
                contained = true;
                weapons.remove(i);
            }
    }
    
    @Override
    public boolean hasNoEffect() { return (super.hasNoEffect() && weapons.isEmpty()); }
    
    @Override
    public String toString() {
        String aux = super.toString();
        aux += "\nArmas: ";
        for (WeaponType w: weapons) {
            aux += w.toString() + " ";
        }
        return aux;
    }
}