/**
 * @author Manuel Gachs Balleger
 */
package Deepspace;

/**
 * @brief Armas de las que dispone una estación
 */
class Weapon {
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
    public int getUses() {return uses;}
    public float power() {return type.getPower();}
    public float useIt() {
        if (uses>0) {
            uses = uses - 1;
            return this.power();
        } else
            return 1.0f;
    }
}