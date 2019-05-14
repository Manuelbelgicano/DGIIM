/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Clase nave enemiga
 */
class EnemyStarShip {
    private Damage damage;
    private Loot loot;
    private String name;
    private float ammoPower;
    private float shieldPower;
    
    EnemyStarShip(String n, float a, float s,Loot l,Damage d) {
        damage = d;
        loot = l;
        name = n;
        ammoPower = a;
        shieldPower = s;
    }
    
    EnemyStarShip(EnemyStarShip e) {
        damage = e.damage;
        loot = e.loot;
        name = e.name;
        ammoPower = e.ammoPower;
        shieldPower = e.shieldPower;
    }
    
    EnemyToUI getUIversion() { return new EnemyToUI(this); }
    
    public float fire() { return ammoPower; }
    
    public float getAmmoPower() { return ammoPower; }
    
    public Damage getDamage() { return damage;  }
    
    public Loot getLoot() { return loot; }
    
    public String getName() { return name; }
    
    public float getShieldPower() { return shieldPower; }
    
    public float protection() { return shieldPower; }
    
    public ShotResult recieveShot(float shot) {
        if (shieldPower<shot)
            return ShotResult.DONOTRESIST;
        else
            return ShotResult.RESIST;
    }
}
