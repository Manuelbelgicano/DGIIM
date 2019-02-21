/**
 * @author Manuel Gachs Ballegeer
 */
package deepspace;
enum CombatResult {ENEMYWINS, NOCOMBAT, STATIONESCAPES, STATIONWINS} ///< Posibles resultados del combate
enum GameCharacter {ENEMYSTARSHIP, SPACESTATION} ///< Tipos de personajes
enum ShotResult {DONOTRESIST, RESIST} ///< Resultados posibles de un disparo
/**
 * @brief Tipos de armas
 */
enum WeaponType {
    LASER(2.0f),
    MISSILE(3.0f),
    PLASMA(4.0f);
    private float power;
    WeaponType(float powerValue) {power = powerValue;}
    float getPower() {return power;}
}
/**
 *  @brief Botín al vencer a una nave enemiga
 */
class Loot {
    private int nSupplies;
    private int nWeapons;
    private int nShields;
    private int nHangars;
    private int nMedals;
    
    Loot(int suppliesNumber,int weaponsNumber,int shieldsNumber,int hangarsNumber,int medalsNumber) {
        nSupplies = suppliesNumber;
        nWeapons = weaponsNumber;
        nShields = shieldsNumber;
        nHangars = hangarsNumber;
        nMedals = medalsNumber;
    }
    public int getNSupplies() {return nSupplies;}
    public int getNWeapons() {return nWeapons;}
    public int getNShields() {return nShields;}
    public int getNHangars() {return nHangars;}
    public int getNMedals() {return nMedals;}
}
/**
 *  @brief Paquete de suministros
 */
class SuppliesPackage {
    private float ammoPower;
    private float fuelUnits;
    private float shieldPower;
    
    SuppliesPackage(float powerAmmo,float unitsFuel,float powerShield) {
        ammoPower = powerAmmo;
        fuelUnits = unitsFuel;
        shieldPower = powerShield;
    }
    SuppliesPackage(SuppliesPackage s) {
        ammoPower = s.ammoPower;
        fuelUnits = s.fuelUnits;
        shieldPower = s.shieldPower;
    }
    public float getAmmoPower() {return ammoPower;}
    public float getFuelUnits() {return fuelUnits;}
    public float getShieldPower() {return shieldPower;}        
}
/**
 * @brief Potenciadores de escudo
 */
class ShieldBooster {
    private String name;
    private float boost;
    private int uses;
    
    ShieldBooster(String BoosterName,float BoostValue,int BoosterUses) {
        name = BoosterName;
        boost = BoostValue;
        uses = BoosterUses;
    }
    ShieldBooster(ShieldBooster s) {
        name = s.name;
        boost = s.boost;
        uses = s.uses;
    }
    public float getBoost() {return boost;}
    public int getUses() {return uses;}
    public float useIt() {
        if (uses>0) {
            uses = uses - 1;
            return boost;
        } else
            return 1.0f;
    }
}
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