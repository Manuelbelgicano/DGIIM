/**
 * @author Manuel Gachs Ballegeer
*/
package Deepspace;

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