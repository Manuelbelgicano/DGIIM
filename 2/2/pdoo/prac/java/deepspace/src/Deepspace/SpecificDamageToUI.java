/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Deepspace;

import java.util.ArrayList;

/**
 *
 * @author Profe
 */
public class SpecificDamageToUI extends DamageToUI{
    private ArrayList<WeaponType> weapons;
//    private int nShields;

    SpecificDamageToUI(SpecificDamage d) {
        super(d);
        ArrayList<WeaponType> tmp=d.getWeapons();
        if (tmp!=null) {
            weapons=new ArrayList<WeaponType>(tmp);
        }
    }

    public ArrayList<WeaponType> getWeapons() {
        return weapons;
    }  
    
    @Override
    public String getWeaponInfo() {
        String aux = weapons.toString();
        return aux.substring(1, aux.length()-1);
    }
}
