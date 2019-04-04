/**
 *  @author Manuel Gachs Ballegeer
 */
package Deepspace;

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
