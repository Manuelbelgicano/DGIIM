/**
 * @author Manuel Gachs Balleger
 */
package Deepspace;

/**
 * @brief Armas de las que dispone una estación
 */
class Weapon implements Copyable <Weapon>, CombatElement {
    private String name;
    private WeaponType type;
    private int uses;
    
    Weapon(String weaponName,WeaponType weaponType,int weaponUses) {
        name = weaponName;
        type = weaponType;
        uses = weaponUses;
    }
    Weapon(Weapon w) {
        name = w.name;
        type = w.type;
        uses = w.uses;
    }
    public WeaponType getType() {return type;}
    @Override
    public int getUses() {return uses;}
    public float power() {return type.getPower();}
    @Override
    public float useIt() {
        if (uses>0) {
            uses = uses - 1;
            return this.power();
        } else
            return 1.0f;
    }
    
    WeaponToUI getUIversion() { return new WeaponToUI(this); }
    
    @Override
    public String toString() {
        String aux = "Nombre: " + name;
        aux += ", Tipo: " + type;
        aux += ", Usos: " + uses;
        return aux;
    }

    @Override
    public Weapon copy() {
        return new Weapon(this);
    }
}