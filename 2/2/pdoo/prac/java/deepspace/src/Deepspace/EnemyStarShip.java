/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Clase nave enemiga
 */
class EnemyStarShip implements Copyable <EnemyStarShip>, SpaceFighter {
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
    
    @Override
    public float fire() { return ammoPower; }
    
    public float getAmmoPower() { return ammoPower; }
    
    public Damage getDamage() { return damage;  }
    
    public Loot getLoot() { return loot; }
    
    public String getName() { return name; }
    
    public float getShieldPower() { return shieldPower; }
    
    @Override
    public float protection() { return shieldPower; }
    
    @Override
    public ShotResult recieveShot(float shot) {
        if (shieldPower<shot)
            return ShotResult.DONOTRESIST;
        else
            return ShotResult.RESIST;
    }
    
    @Override
    public String toString() {
        String aux = "Nombre del enemigo: "+name;
        aux += "\nPoder de disparo: "+ammoPower;
        aux += "\nPoder de escudo: "+shieldPower;
        aux += "\nDaño de la nave:\n"+damage.toString();
        aux += "\nBotín de la nave:\n"+loot.toString();
        return aux;
    }

    @Override
    public EnemyStarShip copy() {
       return new EnemyStarShip(this);
    }
}
